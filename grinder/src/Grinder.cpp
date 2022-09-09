
#include <Grinder.hpp>
#define Grinder_cpp

#include "segidlist.hh"

void Grinder::Gr(Char_t *ridffileDir, Char_t *ridffileName, Char_t *rawfileDir, Char_t *rawfileName, Int_t maxEvt, Int_t firstEvt, Int_t runNumber)
{
	 TString extension;
	 if (runNumber != 0)
	 {
			if (!compression)
			{
				 extension = ".ridf";
			}
			else
			{
				 extension = ".ridf.gz";
			}
	 }

	 TString ridfFile = TString(ridffileDir) + TString(ridffileName) + Form("%04d", runNumber) + extension;
	 std::cout << "Input file: " << ridfFile << std::endl;

	 SetPara fp((Char_t *)"db/PPAC_Info.txt");
	 std::string ppacfile;

	 if (runNumber != 0)
	 {
			ppacfile = fp.GetFileName(runNumber);
	 }
	 else
	 {
			ppacfile = fp.GetFileName(10000);
	 }

	 SetPara fp2((Char_t *)"db/Pla_Info.txt");
	 std::string plasticfile;

	 if (runNumber != 0)
	 {
			plasticfile = fp2.GetFileName(runNumber);
	 }
	 else
	 {
			plasticfile = fp2.GetFileName(10000);
	 }

	 TArtEventStore *estore = new TArtEventStore();
	 if (runNumber != 0)
	 {
			estore->Open(ridfFile);
	 }
	 else
	 { // shared memory analysis for nssta
			estore->Open(0);
	 }

	 TArtBigRIPSParameters *setup = new TArtBigRIPSParameters();
	 setup->LoadParameter((Char_t *)ppacfile.c_str()); // for PPAC_Info
	 setup->LoadParameter((Char_t *)plasticfile.c_str()); // for Pla_Info
	 //setup->LoadParameter((Char_t *)"db/BigRIPSPlastic.xml");
	 setup->LoadParameter((Char_t *)"db/IC_Info.xml");
	 setup->LoadParameter((Char_t *)"db/Ge_Info.xml");
	 setup->LoadParameter((Char_t *)"db/FP_Info.xml");

	 // call after TArtBigRIPSParameters.
	 TArtCalibCoin *calibcoin = new TArtCalibCoin("EventInfo");
	 TArtCalibPPAC *cppac = new TArtCalibPPAC();
	 TArtCalibPlastic *cpla = new TArtCalibPlastic();
	 TArtCalibIC *cic = new TArtCalibIC();
	 TArtCalibGe *cge = new TArtCalibGe();
	 TArtCalibFocalPlane *cfpl = new TArtCalibFocalPlane();

	 calibcoin->SetAddress(21); // use coin with efn = 21

	 TString fileName;
	 if (runNumber != 0)
	 {
			fileName = TString(rawfileName) + Form("%04d", runNumber);
	 }
	 else
	 {
			fileName = "online";
	 }
	 if (debugmode)
	 {
			fileName = "debug";
	 }

	 TString rawFile;
	 rawFile = TString(rawfileDir) + fileName + ".root";
	 std::cout << "Output file: " << rawFile << std::endl;

	 TFile *fout = new TFile(rawFile, "RECREATE");
	 otree = new TTree("tree", "tree");

	 sman = TArtStoreManager::Instance();
	 info_array = (TClonesArray *)sman->FindDataContainer("EventInfo");
	 ppac_array = (TClonesArray *)sman->FindDataContainer("BigRIPSPPAC");
	 pla_array = (TClonesArray *)sman->FindDataContainer("BigRIPSPlastic");
	 ic_array = (TClonesArray *)sman->FindDataContainer("BigRIPSIC");
	 ge_array = (TClonesArray *)sman->FindDataContainer("BigRIPSGe");
	 fpl_array = (TClonesArray *)sman->FindDataContainer("BigRIPSFocalPlane");

	 cf3 = new ConstrF3();
	 cf3->SetTree(otree);
	 cf3->SetCalibPPAC(cppac);
	 cf3->SetCalibPlastic(cpla);
	 cf3->SetCalibFocalPlane(cfpl);

	 cf5 = new ConstrF5();
	 cf5->SetTree(otree);
	 cf5->SetCalibPPAC(cppac);
	 cf5->SetCalibPlastic(cpla);
	 cf5->SetCalibFocalPlane(cfpl);

	 cf7 = new ConstrF7();
	 cf7->SetTree(otree);
	 cf7->SetCalibPPAC(cppac);
	 cf7->SetCalibPlastic(cpla);
	 cf7->SetCalibFocalPlane(cfpl);
	 cf7->SetCalibIC(cic);
	 cf7->SetCalibGe(cge);

	 if (!bripsmode)
	 {
			cf8 = new ConstrF8();
			cf8->SetTree(otree);
			cf8->SetCalibPPAC(cppac);
			cf8->SetCalibPlastic(cpla);
			cf8->SetCalibFocalPlane(cfpl);

			cf9 = new ConstrF9();
			cf9->SetTree(otree);
			cf9->SetCalibPPAC(cppac);
			cf9->SetCalibFocalPlane(cfpl);

			//cf10 = new ConstrF10();
			//cf10->SetTree(otree);
			//cf10->SetCalibPPAC(cppac);
			//cf10->SetCalibFocalPlane(cfpl);

			cf11 = new ConstrF11();
			cf11->SetTree(otree);
			cf11->SetCalibPPAC(cppac);
			cf11->SetCalibPlastic(cpla);
			cf11->SetCalibFocalPlane(cfpl);
			cf11->SetCalibIC(cic);
	 }

	 MakeBranch();

	 time_t start_time;
	 Char_t *start_char;
	 time(&start_time);
	 start_char = ctime(&start_time);
	 std::cout << "Start to grind: " << start_char;

	 if (firstEvt > 0)
	 {
			std::cout << "skipped: " << estore->SkipEvent(firstEvt) << std::endl;
	 }

	 Int_t nEvt = firstEvt;
	 Int_t pEvt = 1000;

	 if (runNumber == 0)
	 {
			pEvt = 100;
	 }

	 while (estore->GetNextEvent() && nEvt < maxEvt + firstEvt)
	 { // event loop
			if (nEvt == firstEvt)
			{
				 puts("Type 's', to save output file.");
				 puts("Type 'q', to stop and finalize this program.");
			}

			if (nEvt % pEvt == 0)
			{
				 std::cout << "Event processing: " << nEvt << "\r" << std::flush;
				 if (kbhit())
				 {
						Int_t key = getchar();
						printf("'%c' was typed.\n", key);
						if (key == 'q')
						{
							 printf("Stop. \n");
							 break;
						}
						if (key == 's')
						{
							 printf("Write file upto %i events. \n", nEvt);
							 otree->AutoSave("SaveSelf");
						}
				 }
			}

			Clear();

			cppac->ReconstructData();
			cfpl->ReconstructData();
			cpla->ReconstructData();
			cic->ReconstructData();
			cge->ReconstructData();
			calibcoin->LoadData();

			// -------------------------------------------------------------------------

			// copy values
			rnum = ((TArtEventInfo *)info_array->At(0))->GetRunNumber();
			SetTimestamp();
			//tbit = ((TArtEventInfo *)info_array->At(0))->GetTriggerBit();
			SetTriggerbit();
			TArtPlastic *pla;
			// RF
			pla = cpla->FindPlastic((Char_t *)"RF");
			if (pla)
			{
				 rf = pla->GetTime();
			}
			for (Int_t i = 0; i < 32; i++)
			{
				 id[i] = i;
			}

			cf3->CopyVal();
			cf5->CopyVal();
			cf7->CopyVal();

			if (!bripsmode)
			{
				 cf8->CopyVal();
				 cf9->CopyVal();
				 //cf10->CopyVal();
				 cf11->CopyVal();
			}

			otree->Fill();

			cppac->ClearData();
			cpla->ClearData();
			cic->ClearData();
			cge->ClearData();
			cfpl->ClearData();
			calibcoin->ClearData();
			estore->ClearData();
			nEvt++;
	 }

	 time_t stop_time;
	 Char_t *stop_char;
	 time(&stop_time);
	 stop_char = ctime(&stop_time);
	 std::cout << "Finish to grind: " << stop_char;

	 fout->Write();
	 fout->Close();

	 return;
}

void Grinder::MakeBranch()
{
	 // branches of anaroot standard
	 if (debugmode)
	 {
			otree->Branch(info_array->GetName(), &info_array);
			otree->Branch(ppac_array->GetName(), &ppac_array);
			otree->Branch(pla_array->GetName(), &pla_array);
			otree->Branch(ic_array->GetName(), &ic_array);
			otree->Branch(ge_array->GetName(), &ge_array);
			otree->Branch(fpl_array->GetName(), &fpl_array);
	 }
	 // branches defined by BigRIPS team
	 otree->Branch("rnum", &rnum, "rnum/I");
	 otree->Branch("tstamp", &tstamp, "tstamp/D");
	 otree->Branch("tbit", &tbit, "tbit/I");
	 otree->Branch("rf", &rf, "rf/D");
	 otree->Branch("id", id, "id[32]/I"); // for 2D figure, X: detector ID, Y: detector E or T

	 cf3->MakeBranch();
	 cf5->MakeBranch();
	 cf7->MakeBranch();

	 if (!bripsmode)
	 {
			cf8->MakeBranch();
			cf9->MakeBranch();
			//cf10->MakeBranch();
			cf11->MakeBranch();
	 }
};

void Grinder::Clear()
{
	 rnum = -9999;
	 tstamp = -9999;
	 tbit = -9999;
	 rf = -9999;

	 cf3->Clear();
	 cf5->Clear();
	 cf7->Clear();

	 if (!bripsmode)
	 {
			cf8->Clear();
			cf9->Clear();
			//cf10->Clear();
			cf11->Clear();
	 }
}

void Grinder::SetTimestamp()
{
	 ts = ((TArtEventInfo *)info_array->At(0))->GetTimeStamp();
	 tstamp = (Double_t)ts * 1e-8;

	 if (ts < 1)
	 { // timestamp is not included in the event info
			unsigned long long int ts0 = 0;
			unsigned long long int ts1 = 0;

			TArtRawEventObject *fEvent = (TArtRawEventObject *)sman->FindDataContainer("RawEvent");
			for (Int_t i = 0; i < fEvent->GetNumSeg(); i++)
			{
				 TArtRawSegmentObject *seg = fEvent->GetSegment(i);
				 Int_t device = seg->GetDevice();
				 Int_t fpl = seg->GetFP();
				 Int_t detector = seg->GetDetector();
				 Int_t module = seg->GetModule();

				 if (device == 0 && fpl == 63 && detector == 60 && module == 42)
				 { // timestamp module (LUPO)
						for (Int_t j = 0; j < seg->GetNumData(); j++)
						{
							 TArtRawDataObject *d = seg->GetData(j);
							 if (j == 0)
							 {
									ts0 = (unsigned long long int)d->GetVal();
							 }
							 if (j == 1)
							 {
									ts1 = (unsigned long long int)d->GetVal();
							 }
						}
				 }

				 if (ts0 > 0)
				 {
						break;
				 }
			}

			ts = (ts0 << 32) + ts1;
			tstamp = (Double_t)ts * 1e-8;
	 }

	 return;
}

void Grinder::SetTriggerbit()
{
	 tbit = ((TArtEventInfo *)info_array->At(0))->GetTriggerBit();

	 if (tbit < 1)
	 { // triggerbit is not included in the event info
			Int_t triggerbit = 0;

			TArtRawEventObject *fEvent = (TArtRawEventObject *)sman->FindDataContainer("RawEvent");
			for (int i = 0; i < fEvent->GetNumSeg(); i++)
			{
				 TArtRawSegmentObject *seg = fEvent->GetSegment(i);
				 Int_t fpl = seg->GetFP();
				 Int_t detector = seg->GetDetector();

				 if (fpl == 63 && detector == 10)
				 {
						for (int j = 0; j < seg->GetNumData(); j++)
						{
							 TArtRawDataObject *d = seg->GetData(j);
							 triggerbit = d->GetVal();
						}
				 }
			}

			tbit = triggerbit;
	 }

	 return;
}

Int_t Grinder::kbhit(void)
{
	 struct termios oldt, newt;
	 Int_t ch;
	 Int_t oldf;

	 tcgetattr(STDIN_FILENO, &oldt);
	 newt = oldt;
	 newt.c_lflag &= ~(ICANON | ECHO);
	 tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	 oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	 fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	 ch = getchar();

	 tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	 fcntl(STDIN_FILENO, F_SETFL, oldf);

	 if (ch != EOF)
	 {
			ungetc(ch, stdin);
			return 1;
	 }

	 return 0;
}
