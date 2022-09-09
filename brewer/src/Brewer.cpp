
#include <Brewer.hpp>
#define Brewer_cpp

void Brewer::Br(Char_t *rawfileDir, Char_t *rawfileName, Char_t *anafileDir, Char_t *anafileName, Int_t maxEvt, Int_t firstEvt, Int_t runNumber)
{
	 RunNumber = runNumber;

	 TString rawFile = TString(rawfileDir) + TString(rawfileName) + Form("%04d", runNumber) + ".root";
	 std::cout << "Input file: " << rawFile << std::endl;

	 TFile *fin = new TFile(rawFile, "READ");
	 if (!fin->IsOpen())
	 {
			exit(1);
			std::cout << "exit" << std::endl;
	 }
	 itree = (TTree *)fin->Get("tree");

	 TString anaFile = TString(anafileDir) + TString(rawfileName) + Form("%04d", runNumber) + ".root";
	 std::cout << "Output file: " << anaFile << std::endl;

	 TFile *fout = new TFile(anaFile, "RECREATE");
	 otree = new TTree("tree", "tree");

	 Initialization();

	 Int_t nentries = itree->GetEntries();
	 Int_t neve = firstEvt;
	 Int_t peve = 10000;

	 if (runNumber == 0)
	 {
			peve = 1000;
	 }

	 std::cout << "Total number of events: " << nentries << std::endl;

	 Clear();

	 while (neve < nentries && neve < maxEvt + firstEvt)
	 { // event loop
			if (neve % peve == 0)
			{
				 std::cout << "Event processing: " << neve << "\r" << std::flush;
			}

			itree->GetEvent(neve);
			Calc();
			otree->Fill();
			Clear();
			neve++;
	 }

	 fout->Write();
	 fout->Close();

	 return;
};

void Brewer::Initialization()
{
	 std::string buf;
	 std::ifstream fin1("prmdir.txt");
	 while (getline(fin1, buf))
	 {
			if (buf.compare(0, 2, "//") == 0 || buf.size() == 0)
			{
				 continue; // comment
			}
			std::stringstream ss;
			ss << buf.c_str();
			ss >> paradir;

			break;
	 }

	 itree->SetBranchAddress("rnum", &rnum);
	 itree->SetBranchAddress("tstamp", &tstamp);
	 itree->SetBranchAddress("tbit", &tbit);
	 itree->SetBranchAddress("rf", &rf);
	 itree->SetBranchAddress("id", id);

	 vars.SetTree(otree);
	 flags.SetTree(otree);

	 vars.SetVariable(&rnum, "rnum");
	 vars.SetVariable(&tstamp, "tstamp");
	 vars.SetVariable(&tbit, "tbit");
	 vars.SetVariable(&rf, "rf");
	 vars.SetVariable(id, "id", 32);

	 calibF3.SetIOTree(itree, otree);
	 calibF3.SetFlags(&flags);
	 calibF3.SetVariable(&vars);
	 calibF3.ReadParameters(paradir, RunNumber);

	 calibF5.SetIOTree(itree, otree);
	 calibF5.SetFlags(&flags);
	 calibF5.SetVariable(&vars);
	 calibF5.ReadParameters(paradir, RunNumber);

	 calibF7.SetIOTree(itree, otree);
	 calibF7.SetFlags(&flags);
	 calibF7.SetVariable(&vars);
	 calibF7.ReadParameters(paradir, RunNumber);

	 if (!bripsmode)
	 {
			calibF8.SetIOTree(itree, otree);
			calibF8.SetFlags(&flags);
			calibF8.SetVariable(&vars);
			calibF8.ReadParameters(paradir, RunNumber);

			if (achromaticmode)
			{
				 calibF9.SetIOTree(itree, otree);
				 calibF9.SetFlags(&flags);
				 calibF9.SetVariable(&vars);
				 calibF9.ReadParameters(paradir, RunNumber);

				 //calibF10.SetIOTree(itree, otree);
				 //calibF10.SetFlags(&flags);
				 //calibF10.SetVariable(&vars);
				 //calibF10.ReadParameters(paradir, RunNumber);
			}

			calibF11.SetIOTree(itree, otree);
			calibF11.SetFlags(&flags);
			calibF11.SetVariable(&vars);
			calibF11.ReadParameters(paradir, RunNumber);
	 }

	 ReadCenterBrho37(paradir + "/Brho/Brho37.txt");
	 if (!bripsmode)
	 {
			ReadCenterBrho811(paradir + "/Brho/Brho811.txt");
	 }

	 InitBrho();
	 InitBeta();
	 InitAOQ();
	 InitZed();
	 InitZdeg();

	 vars.MakeBranch();
	 flags.MakeBranch();
};

void Brewer::InitBrho()
{
	 calcBrho.resize(35);

	 for (Int_t i = 0; i < (Int_t)calcBrho.size(); i++)
	 {
			calcBrho[i].SetVariable(&vars);
	 }

	 Int_t n = 0;

	 // Inputs for Delta
	 calcBrho[n].ReadParameters("Matrix/Matrix35.txt", paradir, RunNumber);
	 calcBrho[n].SetInitialPosAng("f3x", "f3y", "f3b");
	 calcBrho[n].SetFinalPosAng("f5x", "f5a");
	 // Outputs 1
	 calcBrho[n].SetDelta("delta35");
	 calcBrho[n].SetRecoAngle("recof3a");
	 // Input for Brho
	 calcBrho[n].SetCenterBrho(CBrho35);
	 // Output 2
	 calcBrho[n].SetBrho("brho35");
	 n++;

	 // Inputs for Delta
	 calcBrho[n].ReadParameters("Matrix/Matrix75.txt", paradir, RunNumber);
	 calcBrho[n].SetInitialPosAng("f7x", "f7y", "f7b");
	 calcBrho[n].SetFinalPosAng("f5x", "f5a");
	 // Outputs 1
	 calcBrho[n].SetDelta("delta57");
	 calcBrho[n].SetRecoAngle("recof7a");
	 // Input for Brho
	 calcBrho[n].SetCenterBrho(CBrho57);
	 // Output 2
	 calcBrho[n].SetBrho("brho57");
	 n++;

	 if (!bripsmode)
	 {
			if (achromaticmode)
			{
				 // Inputs for Delta
				 calcBrho[n].ReadParameters("Matrix/Matrix89.txt", paradir, RunNumber);
				 calcBrho[n].SetInitialPosAng("f8x", "f8y", "f8tb");
				 //calcBrho[n].SetInitialPosAng("f8x", "f8y", "f8b");
				 calcBrho[n].SetFinalPosAng("f9x", "f9a");
				 // Outputs 1
				 calcBrho[n].SetDelta("delta89");
				 calcBrho[n].SetRecoAngle("recof8ta");
				 //calcBrho[n].SetRecoAngle("recof8a");
				 // Input for Brho
				 calcBrho[n].SetCenterBrho(CBrho89);
				 // Output 2
				 calcBrho[n].SetBrho("brho89");
				 n++;

				 // Inputs for Delta
				 calcBrho[n].ReadParameters("Matrix/Matrix119.txt", paradir, RunNumber);
				 calcBrho[n].SetInitialPosAng("f11x", "f11y", "f11b");
				 calcBrho[n].SetFinalPosAng("f9x", "f9a");
				 // Outputs 1
				 calcBrho[n].SetDelta("delta911");
				 calcBrho[n].SetRecoAngle("recof11a");
				 // Input for Brho
				 calcBrho[n].SetCenterBrho(CBrho911);
				 // Output 2
				 calcBrho[n].SetBrho("brho911");
				 n++;
			}
			if (dispersivemode)
			{
				 // Inputs for Delta
				 calcBrho[n].ReadParameters("Matrix/Matrix811.txt", paradir, RunNumber);
				 calcBrho[n].SetInitialPosAng("f8x", "f8y", "f8tb");
				 calcBrho[n].SetFinalPosAng("f11x", "f11a");
				 // Outputs 1
				 calcBrho[n].SetDelta("delta811");
				 calcBrho[n].SetRecoAngle("recof8ta");
				 // Input for Brho
				 calcBrho[n].SetCenterBrho(CBrho811);
				 // Output 2
				 calcBrho[n].SetBrho("brho811");
				 n++;
			}
	 }

	 calcBrho.resize(n);
};

void Brewer::InitBeta()
{
	 calcBeta.resize(64);

	 for (Int_t i = 0; i < (Int_t)calcBeta.size(); i++)
	 {
			calcBeta[i].SetVariable(&vars);
	 }

	 Int_t n = 0;

	 // Inputs for TOF
	 calcBeta[n].SetStartTiming("f3pla_tl", "f3pla_tr");
	 calcBeta[n].SetStartCharge("f3pla_ql", "f3pla_qr");
	 calcBeta[n].SetStopTiming("f7pla_tl", "f7pla_tr");
	 calcBeta[n].SetStopCharge("f7pla_ql", "f7pla_qr");
	 calcBeta[n].SetTimeStamp("tstamp");
	 calcBeta[n].ReadParameters(paradir + "/TOF/TOF37.txt", RunNumber);
	 // Output 1
	 calcBeta[n].SetTOF("tof37");
	 // Inputs for Beta
	 calcBeta[n].SetDiffQ();
	 calcBeta[n].SetBrho("brho35", "brho57");
	 calcBeta[n].SetFLCenter(23488., 23488.);
	 calcBeta[n].ReadParameters("Matrix/Matrix35.txt", "Matrix/Matrix75.txt", paradir, RunNumber);
	 calcBeta[n].SetPosAngDeltaFirstHalf("f3x", "f3a", "f3y", "f3b", "delta35");
	 calcBeta[n].SetPosAngDeltaSecondHalf("f7x", "f7a", "f7y", "f7b", "delta57");
	 // Outputs 2
	 calcBeta[n].SetBeta("beta35", "beta57");
	 calcBeta[n].SetGamma("gamma35", "gamma57");
	 calcBeta[n].SetFL("fl35", "fl57");
	 n++;

	 if (!bripsmode)
	 {
			if (achromaticmode)
			{
				 // Inputs for TOF
				 calcBeta[n].SetStartTiming("f8pla_tl", "f8pla_tr");
				 calcBeta[n].SetStartCharge("f8pla_ql", "f8pla_qr");
				 calcBeta[n].SetStopTiming("f11pla_tl", "f11pla_tr");
				 calcBeta[n].SetStopCharge("f11pla_ql", "f11pla_qr");
				 calcBeta[n].SetTimeStamp("tstamp");
				 calcBeta[n].ReadParameters(paradir + "/TOF/TOF811.txt", RunNumber);
				 // Output 1
				 calcBeta[n].SetTOF("tof811");
				 // Inputs for Beta
				 calcBeta[n].SetBrho("brho89", "brho911");
				 calcBeta[n].SetFLCenter(13474., 23510.);
				 calcBeta[n].ReadParameters("Matrix/Matrix89.txt", "Matrix/Matrix119.txt", paradir, RunNumber);
				 calcBeta[n].SetPosAngDeltaFirstHalf("f8x", "f8ta", "f8y", "f8tb", "delta89");
				 //calcBeta[n].SetPosAngDeltaFirstHalf("f8x", "f8a", "f8y", "f8b", "delta89");
				 calcBeta[n].SetPosAngDeltaSecondHalf("f11x", "f11a", "f11y", "f11b", "delta911");
				 // Outputs 2
				 calcBeta[n].SetBeta("beta89", "beta911");
				 calcBeta[n].SetGamma("gamma89", "gamma911");
				 calcBeta[n].SetFL("fl89", "fl911");
				 n++;
			}
			if (dispersivemode)
			{
				 // Inputs for TOF
				 calcBeta[n].SetStartTiming("f8pla_tl", "f8pla_tr");
				 calcBeta[n].SetStartCharge("f8pla_ql", "f8pla_qr");
				 calcBeta[n].SetStopTiming("f11pla_tlm", "f11pla_trm");
				 calcBeta[n].SetStopCharge("f11pla_qla", "f11pla_qra");
				 calcBeta[n].ReadParameters(paradir + "/TOF/TOF811.txt", RunNumber);
				 // Output 1
				 calcBeta[n].SetTOF("tof811");
				 // Inputs for Beta
				 calcBeta[n].SetFLCenter(36983.);
				 calcBeta[n].ReadParameters("Matrix/Matrix811.txt", paradir, RunNumber);
				 calcBeta[n].SetPosAngDeltaFirstHalf("f8x", "f8ta", "f8y", "f8tb", "delta811");
				 // Outputs 2
				 calcBeta[n].SetBeta("beta811");
				 calcBeta[n].SetGamma("gamma811");
				 calcBeta[n].SetFL("fl811");
				 n++;
			}
	 }

	 calcBeta.resize(n);
};

void Brewer::InitAOQ()
{
	 calcAOQ.resize(12);

	 for (Int_t i = 0; i < (Int_t)calcAOQ.size(); i++)
	 {
			calcAOQ[i].SetVariable(&vars);
	 }

	 Int_t n = 0;

	 // Inputs
	 calcAOQ[n].SetBrho("brho35");
	 calcAOQ[n].SetBeta("beta35");
	 calcAOQ[n].SetGamma("gamma35");
	 // Output
	 calcAOQ[n].SetAOQ("aoq35");
	 n++;

	 // Inputs
	 calcAOQ[n].SetBrho("brho57");
	 calcAOQ[n].SetBeta("beta57");
	 calcAOQ[n].SetGamma("gamma57");
	 // Output
	 calcAOQ[n].SetAOQ("aoq57");
	 n++;

	 if (!bripsmode)
	 {
			if (achromaticmode)
			{
				 // Inputs
				 calcAOQ[n].SetBrho("brho911");
				 calcAOQ[n].SetBeta("beta911");
				 calcAOQ[n].SetGamma("gamma911");
				 // Output
				 calcAOQ[n].SetAOQ("aoq911");
				 n++;
			}
			if (dispersivemode)
			{
				 // Inputs
				 calcAOQ[n].SetBrho("brho811");
				 calcAOQ[n].SetBeta("beta811");
				 calcAOQ[n].SetGamma("gamma811");
				 // Output
				 calcAOQ[n].SetAOQ("aoq811");
				 n++;
			}
	 }

	 calcAOQ.resize(n);
};

void Brewer::InitZed()
{
	 calcZed.resize(13);

	 for (Int_t i = 0; i < (Int_t)calcZed.size(); i++)
	 {
			calcZed[i].SetVariable(&vars);
	 }

	 Int_t n = 0;

	 if (!dispersivemode)
	 {
			// Inputs
			calcZed[n].SetDeltaE("f7ic_e");
			calcZed[n].SetBeta("beta57");
			calcZed[n].ReadParameters(paradir + "/IC/F7IC.txt", RunNumber);
			// Output
			calcZed[n].SetZed("z7");
			n++;
	 }
	 if (!bripsmode)
	 {
			// Inputs
			calcZed[n].SetDeltaE("f11ic_e");
			if (achromaticmode)
			{
				 calcZed[n].SetBeta("beta911");
				 calcZed[n].SetDelta("delta911");
			}
			if (dispersivemode)
			{
				 calcZed[n].SetTotE("f11ic_esum");
				 calcZed[n].SetBeta("beta811");
			}
			calcZed[n].ReadParameters(paradir + "/IC/F11IC.txt", RunNumber);
			// Output
			calcZed[n].SetZed("z11");
			calcZed[n].SetNValid("f11ic_nvalid");
			n++;
	 }

	 calcZed.resize(n);
};

void Brewer::InitZdeg()
{
	 calcZdeg.resize(5);

	 for (Int_t i = 0; i < (Int_t)calcZdeg.size(); i++)
	 {
			calcZdeg[i].SetVariable(&vars);
	 }

	 Int_t n = 0;

	 // Inputs
	 calcZdeg[n].SetBrho("brho35", "brho57");
	 calcZdeg[n].SetBeta("beta35", "beta57");
	 calcZdeg[n].SetPosAng("f5x", "f5a");
	 // Output
	 calcZdeg[n].SetZdeg("zdeg");
	 calcZdeg[n].ReadParameters(paradir + "/Deg/F5Deg.txt", RunNumber);
	 n++;

	 calcZdeg.resize(n);
};

void Brewer::Calc()
{
	 calibF3.Calc();
	 calibF5.Calc();
	 calibF7.Calc();

	 if (!bripsmode)
	 {
			calibF8.Calc();
			if (achromaticmode)
			{
				 calibF9.Calc();
				 //calibF10.Calc();
			}
			calibF11.Calc();
	 }

	 for (Int_t i = 0; i < (Int_t)calcBrho.size(); i++)
	 {
			calcBrho[i].Calc();
	 }

	 for (Int_t i = 0; i < (Int_t)calcBeta.size(); i++)
	 {
			calcBeta[i].Calc();
	 }

	 for (Int_t i = 0; i < (Int_t)calcAOQ.size(); i++)
	 {
			calcAOQ[i].Calc();
	 }

	 for (Int_t i = 0; i < (Int_t)calcZed.size(); i++)
	 {
			calcZed[i].Calc();
	 }

	 for (Int_t i = 0; i < (Int_t)calcZdeg.size(); i++)
	 {
			calcZdeg[i].Calc();
	 }

	 return;
};

void Brewer::Clear()
{
	 vars.Clear();
	 flags.Clear();
}

void Brewer::ReadCenterBrho37(std::string filename)
{
	 ReadPara rp;
	 std::string parameterlist;
	 Int_t size;

	 parameterlist = rp.ReadParameterList(filename.c_str(), RunNumber);
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss;
			ss << parameterlist;
			ss >> CBrho35 >> CBrho57;
	 }

	 return;
};

void Brewer::ReadCenterBrho811(std::string filename)
{
	 ReadPara rp;
	 std::string parameterlist;
	 Int_t size;

	 parameterlist = rp.ReadParameterList(filename.c_str(), RunNumber);
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss;
			ss << parameterlist;
			ss >> CBrho89 >> CBrho911;
	 }
	 if (dispersivemode)
	 {
			CBrho811 = (CBrho89 + CBrho911) / 2;
	 }

	 return;
};
