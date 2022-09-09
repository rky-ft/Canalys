
#include "TCanvas.h"
#include "TROOT.h"
#include "TRint.h"
#include "TStyle.h"
#include "TSystem.h"

void rootlogon()
{
		((TRint *)gROOT->GetApplication())->SetPrompt("Canalys [%d] ");

		//gStyle->SetOptLogz();
		//gStyle->SetOptFit(1);
		//gStyle->SetOptStat(1111111);
		//gStyle->ToggleEventStatus();
		//gStyle->ToggleToolBar();
		//gStyle->SetPalette(55);
		//gStyle->SetPadGridX(1);
		//gStyle->SetPadGridY(1);

		gStyle->SetHistFillColor(7);
		gStyle->SetHistFillStyle(3002);
		gStyle->SetHistLineColor(kBlue);
		gStyle->SetFuncColor(kRed);
		gStyle->SetFrameLineWidth(2);
		gStyle->SetPadGridX(1);
		gStyle->SetPadGridY(1);
		gStyle->SetCanvasColor(0);
		gStyle->SetTitleFillColor(0);
		gStyle->SetTitleStyle(0);
		gStyle->SetStatColor(0);
		gStyle->SetStatStyle(0);
		gStyle->SetStatX(0.9);
		gStyle->SetStatY(0.9);
		gStyle->SetPalette(55);
		gStyle->SetOptLogz(1);
		//gStyle->SetOptTitle(0);
		gStyle->SetOptFit(0);
		gStyle->SetOptStat(0);
		gStyle->SetPadBorderMode(1);
		//gStyle->SetOptDate(1);

		gStyle->SetTitleAlign(23);

		//Int_t Font_ID = 42;
		Int_t Font_ID = 132;

		gStyle->SetLabelFont(Font_ID, "XYZ");
		gStyle->SetLabelSize(0.045, "XYZ");
		gStyle->SetTitleFont(Font_ID, "XYZ");
		gStyle->SetTitleSize(0.05, "XYZ");
		gStyle->SetTextFont(Font_ID);
		gStyle->SetStatFont(Font_ID);
}
