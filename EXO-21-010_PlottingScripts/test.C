#include "TF1.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TLatex.h"
#include "setTDRStyle_teliko.C"

void test(){

	 double lumi 	     = 137000;    //35900 for 2016, 41850 for 2017, 77750 for 2016+2017
	 double startit	     = 1607;
	 double endit	     = 9067;
	 double startit_RM   = 1607;
	gROOT->LoadMacro("setTDRStyle_teliko.C");
	setTDRStyle_teliko();
	 //gStyle->SetOptFit(1111);
	  
	double gg_8TeV_obs_limit = 0.0000024;
        double qq_4TeV_obs_limit = 0.0000045;
        double qq_2TeV_obs_limit = 0.00038;
       /* double gg_8TeV_obs_limit = 0.000009;
        double qq_2TeV_obs_limit = 0.002;
        double qq_4TeV_obs_limit = 0.000017;*/
/*double gg_8TeV_obs_limit = 0.0000024;
        double qq_4TeV_obs_limit = 0.0000045;
        double qq_2TeV_obs_limit = 0.00038;*/
	 
	 
	 //ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls( 20000);   //set the number of parameter searches for convergence

	char *image_name = "_2016_2017_Shapes_tot_err_alpha12_proper";

	TFile *f_RM= new TFile("13bins/13bins/HISTOS_4J_Alldata_SR_alphabin2.root");
	TFile *f_SF_atlas= new TFile("DijetFitResult_PFDijet2017_4J_alphabin2_atlas_test.root");
        TFile *f_SF_dijet= new TFile("DijetFitResult_PFDijet2017_4J_alphabin2_dijet_test.root");
        TFile *f_SF_moddijet= new TFile("DijetFitResult_PFDijet2017_4J_alphabin2_moddijet_test.root");
        TH1D *signal_data  	      = (TH1D*)(f_RM->Get("h_FourjetMass"));
        TH1D *Blank                   = (TH1D*)(signal_data->Clone());
        //TFile *f_alpha12= new TFile("test_pulls_alpha12.root");
        //TFile *f_alpha12= new TFile("test_pulls_alpha12.root");
       // TFile *f_alpha12= new TFile("test_pulls_alpha12.root");
        TFile *f_alpha12= new TFile("test_pulls_alpha12.root");
       // TFile *f_alpha12= new TFile("test_pulls_alpha12.root");
      //  TFile *f_alpha12= new TFile("test_pulls_alpha12.root");
//TFile *f_alpha12= new TFile("test_pulls_alpha12.root");
//TFile *f_alpha12= new TFile("test_pulls_alpha12.root");
//TFile *f_alpha12= new TFile("test_pulls_alpha12.root");
//TFile *f_alpha12= new TFile("test_pulls_alpha12.root");
//TFile *f_alpha12= new TFile("test_pulls_alpha12.root");
//TFile *f_alpha12= new TFile("test_pulls_alpha12.root");
//TFile *f_alpha12= new TFile("test_pulls_alpha12.root");
// Initial roofit /afs/cern.ch/work/m/mdiamant/public/forNiki/alphagt0p1/atlas/DijetFitResults_PFDijet2017_4J_alphabin7.root");

	double massBoundaries[104] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337,
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

	
	
	//TH1D *pull_SF_moddijet_alpha12 	      = (TH1D*)(f_alpha12->Get("h_FourjetMass"));
        //TH1D *pull_SF_moddijet_alpha12 	      = (TH1D*)(f_alpha12->Get("h_FourjetMass"));
      //  TH1D *pull_SF_moddijet_alpha12 	      = (TH1D*)(f_alpha12->Get("h_FourjetMass"));
       
        TH1D *pull_SF_moddijet_alpha12 	      = (TH1D*)(f_alpha12->Get("h_FourjetMass"));
        //TH1D *pull_SF_moddijet_alpha12 	      = (TH1D*)(f_alpha12->Get("h_FourjetMass"));
//TH1D *pull_SF_moddijet_alpha12 	      = (TH1D*)(f_alpha12->Get("h_FourjetMass"));
        //TH1D *pull_SF_moddijet_alpha12 	      = (TH1D*)(f_alpha12->Get("h_FourjetMass"));
        //TH1D *pull_SF_moddijet_alpha12 	      = (TH1D*)(f_alpha12->Get("h_FourjetMass"));
       // TH1D *pull_SF_moddijet_alpha12 	      = (TH1D*)(f_alpha12->Get("h_FourjetMass"));
       // TH1D *pull_SF_moddijet_alpha12 	      = (TH1D*)(f_alpha12->Get("h_FourjetMass"));
       // TH1D *pull_SF_moddijet_alpha12 	      = (TH1D*)(f_alpha12->Get("h_FourjetMass"));
//TH1D *pull_SF_moddijet_alpha12 	      = (TH1D*)(f_alpha12->Get("h_FourjetMass"));
	
	Blank->SetMarkerColor(0); 		 //use this white-empty histogram to add blank entries on legend.
	Blank->SetLineColor(0);



	
	
       
       
	TCanvas *c1 = new TCanvas("c1","Signal region Data & Prediction",1800,800);
	
c1->cd();

c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.);
c1->SetRightMargin(0);



TPaveText *pave = new TPaveText(0.1,0.0,1.,0.91,"NDC");
// pave->SetFillColor(0);
//pave->SetLineColor(0);

pave->SetFillColor(0);
pave->SetLineColor(1);
pave->SetBorderSize(1);
pave->SetFillStyle(4100);
pave->SetTextFont(42);
pave->SetTextSize(0.12);
pave->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}} ");
pave->AddText("Y -> XX -> (jj) (jj)");
pave->AddText("#bf{#bf{#alpha = Average dijet mass/Four-jet mass}}");
//pave->AddLine(0.2,0,0.2,0.99);
//pave->SetBorderSize(2);
pave->Draw("");
     	

TLegend *leg32 = new TLegend(0.6,0.92,0.98,0.93);
leg32->SetTextFont(42);
leg32->AddEntry(Blank,"#bf{#bf{138 fb^{-1} (13TeV)}}");
leg32->SetBorderSize(0);
leg32->SetTextSize(0.1);
leg32->Draw("same");






/*c1->cd();



c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.1);
c1->SetRightMargin(0);
c1->cd()->SetLogx(1);
c1->SetGridx();
c1->SetGridy();

	
pull_SF_moddijet_alpha12->GetXaxis()->SetTitle("Fourjet mass [TeV]");
pull_SF_moddijet_alpha12->GetXaxis()->SetNoExponent();
pull_SF_moddijet_alpha12->GetXaxis()->SetMoreLogLabels();
pull_SF_moddijet_alpha12->GetXaxis()->SetTitleSize(2*0.06);
pull_SF_moddijet_alpha12->GetYaxis()->SetTitleSize(2*0.06);
pull_SF_moddijet_alpha12->GetXaxis()->SetLabelSize(2*0.07);
pull_SF_moddijet_alpha12->GetYaxis()->SetLabelSize(0.09);
pull_SF_moddijet_alpha12->GetXaxis()->SetLabelOffset(1000);
pull_SF_moddijet_alpha12->GetXaxis()->SetTitleOffset(1.2);
pull_SF_moddijet_alpha12->GetYaxis()->SetTitleOffset(0.4);
pull_SF_moddijet_alpha12->GetYaxis()->SetRangeUser(-2.99,2.99);
pull_SF_moddijet_alpha12->GetYaxis()->SetNdivisions(210); 
pull_SF_moddijet_alpha12->SetLineWidth(1);


        

	

pull_SF_moddijet_alpha12->SetYTitle("");
pull_SF_moddijet_alpha12->SetFillColor(2);
pull_SF_moddijet_alpha12->Draw("same HIST");

 TPaveText *pave = new TPaveText(0.3,0.9,0.45,0.95,"NDC");
 pave->SetFillColor(0);
//pave->SetLineColor(0);
pave->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  //pave->SetTextFont(42);
  pave->SetTextSize(0.12);
  pave->AddText(" 0.10 < #alpha < 0.12");
pave->Draw("same");

TPaveText *pavechi = new TPaveText(0.85,0.05,0.9,0.25,"NDC");
 pavechi->SetFillColor(0);
//pave->SetLineColor(0);
pavechi->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  //pave->SetTextFont(42);
  pavechi->SetTextSize(0.12);
  pavechi->AddText("#splitline{#chi^{2}/NDF =}{21.8/29}");
 // pavechi->AddText("21.8/29");
pavechi->Draw("same");

 ////paveL1->SetFillColor(0);
//pave->SetLineColor(0);
////paveL1->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  //pave->SetTextFont(42);
  ////paveL1->SetTextSize(0.1);
  ////paveL1->AddText("137 fb^{-1} (13 TeV)");
////paveL1->Draw("same");









/*c1->cd();

	c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.1);
c1->SetRightMargin(0);
	c1->cd()->SetLogx(1);
	c1->SetGridx();
	c1->SetGridy();



        //
       // pull_SF_moddijet_alpha12->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha12->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha12->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha12->GetXaxis()->SetTitleSize(2*0.);
        pull_SF_moddijet_alpha12->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha12->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha12->GetYaxis()->SetLabelSize(0.09);
        pull_SF_moddijet_alpha12->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha12->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha12->GetYaxis()->SetRangeUser(-2.99,2.99);
        pull_SF_moddijet_alpha12->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha12->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha12->SetLineWidth(1);


        



        pull_SF_moddijet_alpha12->SetYTitle("");
        pull_SF_moddijet_alpha12->SetFillColor(2);
        pull_SF_moddijet_alpha12->Draw("same HIST");




	
TPaveText *pave3 = new TPaveText(0.3,0.9,0.45,0.95,"NDC");
 pave3->SetFillColor(0);
//pave->SetLineColor(0);
pave3->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  //pave->SetTextFont(42);
  pave3->SetTextSize(0.12);
  pave3->AddText(" 0.12 < #alpha < 0.14");
pave3->Draw("same");


TPaveText *pavechi2 = new TPaveText(0.8,0.15,0.85,0.25,"NDC");
 pavechi2->SetFillColor(0);
//pave->SetLineColor(0);
pavechi2->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  //pave->SetTextFont(42);
  pavechi2->SetTextSize(0.1);
  pavechi2->AddText("#chi^{2}/NDF = 20.5/28.0");
pavechi2->Draw("same");

////paveL1->Draw("same");

*/

/*c1->cd();

	
c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.1);
c1->SetRightMargin(0);
	
	c1->cd()->SetLogx(1);
	c1->SetGridx();
	c1->SetGridy();

	


        //
       // pull_SF_moddijet_alpha12->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha12->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha12->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha12->GetXaxis()->SetTitleSize(2*0.0);
        pull_SF_moddijet_alpha12->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha12->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha12->GetYaxis()->SetLabelSize(0.09);
        pull_SF_moddijet_alpha12->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha12->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha12->GetYaxis()->SetRangeUser(-2.99,2.99);
        pull_SF_moddijet_alpha12->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha12->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha12->SetLineWidth(1);


        

	


        pull_SF_moddijet_alpha12->SetYTitle("");
        pull_SF_moddijet_alpha12->SetFillColor(2);
        pull_SF_moddijet_alpha12->Draw("same HIST");


TPaveText *pave3 = new TPaveText(0.3,0.9,0.45,0.95,"NDC");
 pave3->SetFillColor(0);
//pave->SetLineColor(0);
pave3->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  //pave->SetTextFont(42);
  pave3->SetTextSize(0.12);
  pave3->AddText(" 0.14 < #alpha < 0.16");
pave3->Draw("same");


TPaveText *pavechi2 = new TPaveText(0.8,0.15,0.85,0.25,"NDC");
 pavechi2->SetFillColor(0);
//pave->SetLineColor(0);
pavechi2->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  //pave->SetTextFont(42);
  pavechi2->SetTextSize(0.1);
  pavechi2->AddText("#chi^{2}/NDF = 20.3/30.0");
pavechi2->Draw("same");

*/	



/*c1->cd();
c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.1);
c1->SetRightMargin(0);
	
	
	c1->cd()->SetLogx(1);
	c1->SetGridx();
	c1->SetGridy();

	


        //
        //pull_SF_moddijet_alpha12->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha12->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha12->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha12->GetXaxis()->SetTitleSize(2*0.0);
        pull_SF_moddijet_alpha12->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha12->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha12->GetYaxis()->SetLabelSize(0.09);
        pull_SF_moddijet_alpha12->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha12->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha12->GetYaxis()->SetRangeUser(-2.99,2.99);
        pull_SF_moddijet_alpha12->GetYaxis()->SetTitleOffset(0.4);

      /*  pull_SF_moddijet_alpha12->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha12->SetLineWidth(1);


        




        pull_SF_moddijet_alpha12->SetYTitle("");
        pull_SF_moddijet_alpha12->SetFillColor(2);
        pull_SF_moddijet_alpha12->Draw("same HIST");*/

	
/*TPaveText *pave5 = new TPaveText(0.3,0.9,0.45,0.95,"NDC");
 pave5->SetFillColor(0);
//pave->SetLineColor(0);
pave5->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  //pave->SetTextFont(42);
  pave5->SetTextSize(0.12);
  pave5->AddText(" 0.16 < #alpha < 0.18");
pave5->Draw("same");

TPaveText *pavechi4 = new TPaveText(0.8,0.15,0.85,0.25,"NDC");
 pavechi4->SetFillColor(0);
//pave->SetLineColor(0);
pavechi4->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  //pave->SetTextFont(42);
  pavechi4->SetTextSize(0.1);
  pavechi4->AddText("#chi^{2}/NDF = 21.8/27.0");
pavechi4->Draw("same");

////paveL1->Draw("same");

*/


/*c1->cd();


c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.1);
c1->SetRightMargin(0);
	
	c1->cd()->SetLogx(1);
	c1->SetGridx();
	c1->SetGridy();

	


        //
        //pull_SF_moddijet_alpha12->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha12->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha12->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha12->GetXaxis()->SetTitleSize(2*0.0);
        pull_SF_moddijet_alpha12->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha12->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha12->GetYaxis()->SetLabelSize(0.09);
        pull_SF_moddijet_alpha12->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha12->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha12->GetYaxis()->SetRangeUser(-2.99,2.99);
        pull_SF_moddijet_alpha12->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha12->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha12->SetLineWidth(1);


        



        pull_SF_moddijet_alpha12->SetYTitle("");
        pull_SF_moddijet_alpha12->SetFillColor(2);
        pull_SF_moddijet_alpha12->Draw("same HIST");

	
TPaveText *pave6 = new TPaveText(0.3,0.9,0.45,0.95,"NDC");
 pave6->SetFillColor(0);
//pave->SetLineColor(0);
pave6->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  //pave->SetTextFont(42);
  pave6->SetTextSize(0.12);
  pave6->AddText(" 0.18 < #alpha < 0.20");
pave6->Draw("same");

TPaveText *pavechi5 = new TPaveText(0.8,0.15,0.85,0.25,"NDC");
 pavechi5->SetFillColor(0);
//pave->SetLineColor(0);
pavechi5->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  //pave->SetTextFont(42);
  pavechi5->SetTextSize(0.1);
  pavechi5->AddText("#chi^{2}/NDF = 22.3/29.0");
pavechi5->Draw("same");
*/


/*c1->cd();

c1->cd();
c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.1);
c1->SetRightMargin(0);

	
c1->cd()->SetLogx(1);
	c1->SetGridx();
	c1->SetGridy();


        //
       // pull_SF_moddijet_alpha12->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha12->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha12->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha12->GetXaxis()->SetTitleSize(2*0.);
        pull_SF_moddijet_alpha12->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha12->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha12->GetYaxis()->SetLabelSize(0.09);
        pull_SF_moddijet_alpha12->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha12->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha12->GetYaxis()->SetRangeUser(-2.99,2.99);
        pull_SF_moddijet_alpha12->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha12->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha12->SetLineWidth(1);


        



        pull_SF_moddijet_alpha12->SetYTitle("");
        pull_SF_moddijet_alpha12->SetFillColor(2);
        pull_SF_moddijet_alpha12->Draw("same HIST");




	
TPaveText *pave14 = new TPaveText(0.3,0.9,0.45,0.95,"NDC");
 pave14->SetFillColor(0);
//pave->SetLineColor(0);
pave14->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  //pave->SetTextFont(42);
  pave14->SetTextSize(0.11);
  pave14->AddText("0.18 < #alpha < 0.20");
pave14->Draw("same");


TPaveText *pavechi7 = new TPaveText(0.85,0.05,0.9,0.25,"NDC");
 pavechi7->SetFillColor(0);
//pave->SetLineColor(0);
pavechi7->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  //pave->SetTextFont(42);
 pavechi7->SetTextSize(0.12);
  pavechi7->AddText("#splitline{#chi^{2} / NDF =}{22.3 / 29}");
 // pavechi->AddText("21.8/29");
pavechi7->Draw("same");

////paveL1->Draw("same");

TLatex *xLab1 = new TLatex();
	xLab1->SetTextAlign(22);
	xLab1->SetTextFont(42);
	xLab1->SetTextSize(2*0.08);         
	xLab1->DrawLatex(2000, -3.4, "2");
	xLab1->DrawLatex(3000, -3.4, "3");
	xLab1->DrawLatex(4000, -3.4, "4");
	xLab1->DrawLatex(5000, -3.4, "5");
	xLab1->DrawLatex(6000, -3.4, "6");
	xLab1->DrawLatex(7000, -3.4, "7");
	xLab1->DrawLatex(8000, -3.4, "8");*/

/*c1->cd();

c1->cd();
c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.1);
c1->SetRightMargin(0);

	
c1->cd()->SetLogx(1);
	c1->SetGridx();
	c1->SetGridy();



	


        //
       // pull_SF_moddijet_alpha12->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha12->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha12->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha12->GetXaxis()->SetTitleSize(2*0.0);
        pull_SF_moddijet_alpha12->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha12->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha12->GetYaxis()->SetLabelSize(0.09);
        pull_SF_moddijet_alpha12->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha12->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha12->GetYaxis()->SetRangeUser(-2.99,2.99);
        pull_SF_moddijet_alpha12->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha12->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha12->SetLineWidth(1);


        

	


        pull_SF_moddijet_alpha12->SetYTitle("");
        pull_SF_moddijet_alpha12->SetFillColor(2);
        pull_SF_moddijet_alpha12->Draw("same HIST");

	
//TPaveText *pave8 = new TPaveText(0.3,0.9,0.45,0.95,"NDC");
TPaveText *pave8 = new TPaveText(0.23,0.88,0.38,0.93,"NDC");//0.3, 0.45
 pave8->SetFillColor(0);
//pave->SetLineColor(0);
pave8->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  //pave->SetTextFont(42);
  pave8->SetTextSize(0.11);//0.12
  pave8->AddText("0.32 < #alpha < 0.34");
pave8->Draw("same");




TPaveText *pavechi7 = new TPaveText(0.83,0.05,0.89,0.25,"NDC");//0.15-0.35
 pavechi7->SetFillColor(0);
//pave->SetLineColor(0);
pavechi7->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  //pave->SetTextFont(42);
 pavechi7->SetTextSize(0.12);//0.12
  pavechi7->AddText("#splitline{#chi^{2} / NDF =}{26.0 / 25}");
 // pavechi->AddText("21.8/29");
pavechi7->Draw("same");


TLatex *xLab1 = new TLatex();
	xLab1->SetTextAlign(22);
	xLab1->SetTextFont(42);
	xLab1->SetTextSize(2*0.07);         
	xLab1->DrawLatex(2000, -3.4, "2");
	xLab1->DrawLatex(3000, -3.4, "3");
	xLab1->DrawLatex(4000, -3.4, "4");
	xLab1->DrawLatex(5000, -3.4, "5");
	xLab1->DrawLatex(6000, -3.4, "6");
	xLab1->DrawLatex(7000, -3.4, "7");
	xLab1->DrawLatex(8000, -3.4, "8");
//xLab1->DrawLatex(9000, -3.4, "9");

////paveL1->Draw("same");

*/

TFile *fout;

 fout = new TFile("pad1_margin_V3.root","RECREATE");


fout->cd();
c1->Write();
fout->Close();

}
