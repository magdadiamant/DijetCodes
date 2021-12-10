#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TF1.h"
#include "TDirectory.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"
#include "Math/MinimizerOptions.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "setTDRStyle_teliko.C"
#include "TEllipse.h"

 void plot_comparison(Int_t doJSON){

 gROOT->LoadMacro("setTDRStyle_teliko.C");
 setTDRStyle_teliko();
                                     //0.14
 TPaveText *paveCMS = new TPaveText(0.16,0.96,0.96,0.99,"NDC");
 if(doJSON==1)  paveCMS->AddText(" #bf{CMS} #it{Supplementary}      137 fb^{-1}           (13 TeV)");
 paveCMS->SetFillColor(0);
 paveCMS->SetBorderSize(0);
 paveCMS->SetTextSize(0.04);


 TPaveText *paveCMS2 = new TPaveText(0.25,0.65,0.45,0.9,"NDC");
 paveCMS2->AddText("|#eta|<2.5" );
 paveCMS2->AddText("Masymmetry<0.1");
 paveCMS2->AddText("|#Delta #eta| < 1.1");
//paveCMS2->AddText("M4J > 4 TeV");
//paveCMS2->AddText("#Delta R <1.2");
 paveCMS2->SetFillColor(0);
 paveCMS2->SetBorderSize(0);
 paveCMS2->SetTextSize(0.04);

 TPaveText *paveCMS3 = new TPaveText(0.7,0.65,0.9,0.78,"NDC");
 paveCMS3->AddText("|#eta|<2.5" );
 paveCMS3->AddText("Masymmetry<0.1");
paveCMS3->AddText("|#Delta #eta| < 1.1");
//paveCMS3->AddText("M4J > 4 TeV");
//paveCMS3->AddText("#Delta R <1.2");
 paveCMS3->SetFillColor(0);
 paveCMS3->SetBorderSize(0);
 paveCMS3->SetTextSize(0.04);


 TPaveText *paveCMS7 = new TPaveText(0.5,0.65,0.7,0.9,"NDC");
 paveCMS7->AddText("|#eta|<2.5" );
 paveCMS7->AddText("Masymmetry < 0.1");
paveCMS7->AddText("|#Delta #eta| < 1.1");
//paveCMS7->AddText("M4J > 4 TeV");
 paveCMS7->SetFillColor(0);
 paveCMS7->SetBorderSize(0);
 paveCMS7->SetTextSize(0.04);

 TPaveText *paveCMS4 = new TPaveText(0.22,0.8,0.34,0.93,"NDC");
 paveCMS4->AddText("|#eta|<2.5" );
 paveCMS4->AddText("Masymmetry<0.1");
paveCMS4->AddText("|#Delta #eta| < 1.1");
//paveCMS4->AddText("M4J > 4 TeV");
//paveCMS4->AddText("#Delta R <1.2");
 paveCMS4->SetFillColor(0);
 paveCMS4->SetBorderSize(0);
 paveCMS4->SetTextSize(0.04);

 TPaveText *paveCMS5 = new TPaveText(0.39,0.80,0.51,0.93,"NDC");
 paveCMS5->AddText("|#eta|<2.5" );
 paveCMS5->AddText("Masymmetry<0.1");
 paveCMS5->AddText("|#Delta #eta| < 1.1");
//paveCMS5->AddText("M4J > 4 TeV");
//paveCMS5->AddText("#Delta R <1.2");
 paveCMS5->SetFillColor(0);
 paveCMS5->SetBorderSize(0);
 paveCMS5->SetTextSize(0.04);

 TPaveText *paveCMS6 = new TPaveText(0.39,0.80,0.51,0.93,"NDC");
 paveCMS6->AddText("|#eta|<2.5" );
paveCMS6->AddText("Masymmetry<0.1");
paveCMS6->AddText("|#Delta #eta| < 1.1");
//paveCMS6->AddText("M4J > 4 TeV");
 paveCMS6->SetFillColor(0);
 paveCMS6->SetBorderSize(0);
 paveCMS6->SetTextSize(0.04);

  float lumi;
  if(doJSON==0) lumi = 14505.;
  if(doJSON==1) lumi = 14505.;

//if(doJSON==1) fin = new TFile ("histos_4Jets_2017Data_allruns_nomjjcut_MASYMMETRY_lt_0p05.root","READ");
TFile *fin;
fin = new TFile("HISTOS_2016_17_19_M4J_1p6.root","READ");

TFile *finm;
finm= new TFile("QCD2017_Standardcuts_M4Jgt1p6_nobreak.root","READ");


 
  TH1D *h_etaphiJet1WJ_data = (TH1D*)(fin->Get("h_etaphiJet1WJ_data"));
  TH1D *h_assym_data	   = (TH1D*)(fin->Get("h_assym_data"));
  TH1D *h_METovSUMET_data = (TH1D*)(fin->Get("h_METovSUMET_data"));
  TH1D *h_METovSUMET2_data = (TH1D*)(fin->Get("h_METovSUMET2_data"));
  TH1D *h_MET_data         = (TH1D*)(fin->Get("h_MET_data"));
  TH1D *h_SUMET_data       = (TH1D*)(fin->Get("h_SUMET_data"));
  TH2D *h_METvsSUMET_data  = (TH2D*)(fin->Get("h_METvsSUMET_data"));
  TH1D *h_CHFJet1_data     = (TH1D*)(fin->Get("h_CHFJet1_data"));
  TH1D *h_NHFJet1_data     = (TH1D*)(fin->Get("h_NHFJet1_data"));

TH1D *h_NEMFJet1_data     = (TH1D*)(fin->Get("h_NEMFJet1_data"));
  TH1D *h_CEMFJet1_data     = (TH1D*)(fin->Get("h_CEMFJet1_data"));
  TH1D *h_NHFJet1_data1tev= (TH1D*)(fin->Get("h_NHFJet1_data1tev"));
  TH1D *h_NHFJet1_data4tev= (TH1D*)(fin->Get("h_NHFJet1_data4tev"));
  TH1D *h_MUFJet1_data     = (TH1D*)(fin->Get("h_MUFJet1_data"));
  TH1D *h_CMJet1_data      = (TH1D*)(fin->Get("h_CMJet1_data"));
  TH1D *h_NMJet1_data      = (TH1D*)(fin->Get("h_NMJet1_data"));
  TH1D *h_ptJet1_data      = (TH1D*)(fin->Get("h_ptJet1_data"));
  TH1D *h_PMJet1_data      = (TH1D*)(fin->Get("h_PMJet1_data"));
  TH1D *h_nVtx_data        = (TH1D*)(fin->Get("h_nVtx_data"));
  TH1D *h_ptJet1_dataAK4   = (TH1D*)(fin->Get("h_ptJet1_dataAK4"));
  TH1D *h_etaJet1_dataAK4  = (TH1D*)(fin->Get("h_etaJet1_dataAK4"));
  TH1D *h_phiJet1_dataAK4  = (TH1D*)(fin->Get("h_phiJet1_dataAK4"));
  TH1D *h_Dijet_MassAK4_data = (TH1D*)(fin->Get("h_Dijet_MassAK4_data"));
  TH1D *h_deltaETA_AK4_data  = (TH1D*)(fin->Get("h_deltaETA_AK4_data"));
  TH1D *h_deltaPHI_AK4_data  = (TH1D*)(fin->Get("h_deltaPHI_AK4_data"));
  TH1D  *h_CosThetaStar_AK4_data = (TH1D*)(fin->Get("h_CosThetaStar_AK4_data"));
  TH1D *h_ptJet1_dataWJ          = (TH1D*)(fin->Get("h_ptJet1_dataWJ"));
  TH1D *h_etaJet1_dataWJ     = (TH1D*)(fin->Get("h_etaJet1_dataWJ"));
  TH1D *h_phiJet1_dataWJ     = (TH1D*)(fin->Get("h_phiJet1_dataWJ"));
  TH1D *h_mjj_data           = (TH1D*)(fin->Get("h_mjj_data"));
  TH1D *h_deltaETAjj_data    = (TH1D*)(fin->Get("h_deltaETAjj_data"));
  TH1D *h_deltaPHIjj_data    = (TH1D*)(fin->Get("h_deltaPHIjj_data"));
  TH1D *h_deltaPHIjj_data2   = (TH1D*)(fin->Get("h_deltaPHIjj_data2"));
  TH1D *h_CosThetaStar_WJ_data  = (TH1D*)(fin->Get("h_CosThetaStar_WJ_data"));
TH1D *h_FourjetMass_data = (TH1D*)(fin->Get("h_FourjetMass"));
TH1D *h_Dijet_MassAK4_1_data = (TH1D*)(fin->Get("h_Dijet_MassAK4_1"));
TH1D *h_Dijet_MassAK4_2_data = (TH1D*)(fin->Get("h_Dijet_MassAK4_2"));
TH1D *h_MAverage_data = (TH1D*)(fin->Get("h_MAverage"));
TH2D *h_M4J_vs_M2J_data=(TH2D*)(fin->Get("h_M4J_vs_M2J"));
TH2D *h_M4J_vs_DeltaRapidity_data=(TH2D*)(fin->Get("h_M4J_vs_DeltaRapidity"));
TH1D *h_Masymmetry_data= (TH1D*)(fin->Get("h_Masymmetry"));
TH1D *h_DeltaEtaJJAK4_data = (TH1D*)(fin->Get("h_DeltaEtaJJAK4_data"));
TH1D *h_DeltaPhiJJAK4_data=(TH1D*)(fin->Get("h_DeltaPhiJJAK4_data"));
TH1D *h_DeltaRAK4_First_data=(TH1D*)(fin->Get("h_DeltaRAK4_First_data"));
TH1D *h_DeltaRAK4_Second_data = (TH1D*)(fin->Get("h_DeltaRAK4_Second_data"));
TH1D *h_ETA_1_data=(TH1D*)(fin->Get("h_ETA_1"));
TH1D *h_ETA_2_data=(TH1D*)(fin->Get("h_ETA_2"));
TH1D *h_Rapidity_1_data=(TH1D*)(fin->Get("h_Rapidity_1"));
TH1D *h_Rapidity_2_data=(TH1D*)(fin->Get("h_Rapidity_2"));
TH1D *h_DeltaRapidity_data=(TH1D*)(fin->Get("h_DeltaRapidity"));
TH1D *h_M4J_vs_MeanDR_data = (TH1D*)(fin->Get("h_M4J_vs_MeanDR"));
TH1D *h_MeanDR_vs_DY_data = (TH1D*)(fin->Get("h_MeanDR_vs_DY"));
TH1D *h_M4J_vs_MeanDR = (TH1D*)(finm->Get("h_M4J_vs_MeanDR"));
TH1D *h_MeanDR_vs_DY = (TH1D*)(finm->Get("h_MeanDR_vs_DY"));







TH1D *h_CHFJet2_data     = (TH1D*)(fin->Get("h_CHFJet2_data"));
  TH1D *h_NHFJet2_data     = (TH1D*)(fin->Get("h_NHFJet2_data"));
TH2D *h_M2J_vs_alpha_data=(TH2D*)(fin->Get("h_M2J_vs_alpha"));
TH2D *h_alpha_vs_M2J_data=(TH2D*)(fin->Get("h_alpha_vs_M2J"));

TH1D *h_NEMFJet2_data     = (TH1D*)(fin->Get("h_NEMFJet2_data"));
  TH1D *h_CEMFJet2_data     = (TH1D*)(fin->Get("h_CEMFJet2_data"));
  TH1D *h_NHFJet2_data1tev= (TH1D*)(fin->Get("h_NHFJet2_data1tev"));
  TH1D *h_NHFJet2_data4tev= (TH1D*)(fin->Get("h_NHFJet2_data4tev"));
  TH1D *h_MUFJet2_data     = (TH1D*)(fin->Get("h_MUFJet2_data"));
  TH1D *h_CMJet2_data      = (TH1D*)(fin->Get("h_CMJet2_data"));
  TH1D *h_NMJet2_data      = (TH1D*)(fin->Get("h_NMJet2_data"));
  TH1D *h_ptJet2_data      = (TH1D*)(fin->Get("h_ptJet2_data"));
  TH1D *h_PMJet2_data      = (TH1D*)(fin->Get("h_PMJet2_data"));
 // TH1D *h_nVtx_data        = (TH1D*)(fin->Get("h_nVtx_data"));
  TH1D *h_ptJet2_dataAK4   = (TH1D*)(fin->Get("h_ptJet2_dataAK4"));
  TH1D *h_etaJet2_dataAK4  = (TH1D*)(fin->Get("h_etaJet2_dataAK4"));
  TH1D *h_phiJet2_dataAK4  = (TH1D*)(fin->Get("h_phiJet2_dataAK4"));



TH1D *h_CHFJet3_data     = (TH1D*)(fin->Get("h_CHFJet3_data"));
  TH1D *h_NHFJet3_data     = (TH1D*)(fin->Get("h_NHFJet3_data"));

TH1D *h_NEMFJet3_data     = (TH1D*)(fin->Get("h_NEMFJet3_data"));
  TH1D *h_CEMFJet3_data     = (TH1D*)(fin->Get("h_CEMFJet3_data"));
  TH1D *h_MUFJet3_data     = (TH1D*)(fin->Get("h_MUFJet3_data"));
  TH1D *h_CMJet3_data      = (TH1D*)(fin->Get("h_CMJet3_data"));
  TH1D *h_NMJet3_data      = (TH1D*)(fin->Get("h_NMJet3_data"));
  TH1D *h_ptJet3_data      = (TH1D*)(fin->Get("h_ptJet3_data"));
  TH1D *h_PMJet3_data      = (TH1D*)(fin->Get("h_PMJet3_data"));
 // TH1D *h_nVtx_data        = (TH1D*)(fin->Get("h_nVtx_data"));
  TH1D *h_ptJet3_dataAK4   = (TH1D*)(fin->Get("h_ptJet3_dataAK4"));
  TH1D *h_etaJet3_dataAK4  = (TH1D*)(fin->Get("h_etaJet3_dataAK4"));
  TH1D *h_phiJet3_dataAK4  = (TH1D*)(fin->Get("h_phiJet3_dataAK4"));


TH1D *h_CHFJet4_data     = (TH1D*)(fin->Get("h_CHFJet4_data"));
  TH1D *h_NHFJet4_data     = (TH1D*)(fin->Get("h_NHFJet4_data"));

TH1D *h_NEMFJet4_data     = (TH1D*)(fin->Get("h_NEMFJet4_data"));
  TH1D *h_CEMFJet4_data     = (TH1D*)(fin->Get("h_CEMFJet4_data"));
  TH1D *h_MUFJet4_data     = (TH1D*)(fin->Get("h_MUFJet4_data"));
  TH1D *h_CMJet4_data      = (TH1D*)(fin->Get("h_CMJet4_data"));
  TH1D *h_NMJet4_data      = (TH1D*)(fin->Get("h_NMJet4_data"));
  TH1D *h_ptJet4_data      = (TH1D*)(fin->Get("h_ptJet4_data"));
  TH1D *h_PMJet4_data      = (TH1D*)(fin->Get("h_PMJet4_data"));
 // TH1D *h_nVtx_data        = (TH1D*)(fin->Get("h_nVtx_data"));
  TH1D *h_ptJet4_dataAK4   = (TH1D*)(fin->Get("h_ptJet4_dataAK4"));
  TH1D *h_etaJet4_dataAK4  = (TH1D*)(fin->Get("h_etaJet4_dataAK4"));
  TH1D *h_phiJet4_dataAK4  = (TH1D*)(fin->Get("h_phiJet4_dataAK4"));
TH2D *h_DijetMassAK4_1_vs_2_data=(TH2D*)(fin->Get("h_DijetMassAK4_1_vs_2"));
TH2D *h_M4J_vs_DeltaEta_data=(TH2D*)(fin->Get("h_M4J_vs_DeltaEta"));

TH2D *h_M4J_vs_DeltaPhi_data=(TH2D*)(fin->Get("h_M4J_vs_DeltaPhi"));
TH2D *h_Maverage_vs_DeltaEta_data=(TH2D*)(fin->Get("h_Maverage_vs_DeltaEta"));
TH2D *h_Maverage_vs_DeltaPhi_data=(TH2D*)(fin->Get("h_Maverage_vs_DeltaPhi"));
TH2D *h_DeltaR1_vs_DeltaR2_data=(TH2D*)(fin->Get("h_DeltaR1_vs_DeltaR2"));


/*TH2D *h_M4J_vs_DeltaEta=(TH2D*)(finm->Get("h_M4J_vs_DeltaEta"));

TH2D *h_M4J_vs_DeltaPhi=(TH2D*)(finm->Get("h_M4J_vs_DeltaPhi"));
TH2D *h_Maverage_vs_DeltaEta=(TH2D*)(finm->Get("h_Maverage_vs_DeltaEta"));


TH2D *h_Maverage_vs_DeltaR=(TH2D*)(finm->Get("h_Maverage_vs_DeltaR"));
TH2D *h_Maverage_vs_DeltaR_data=(TH2D*)(fin->Get("h_Maverage_vs_DeltaR"));
TH2D *h_Maverage_vs_DeltaPhi=(TH2D*)(finm->Get("h_Maverage_vs_DeltaPhi"));
TH2D *h_DeltaR1_vs_DeltaR2=(TH2D*)(finm->Get("h_DeltaR1_vs_DeltaR2"));


TH1D *h_etaphiJet1WJ = (TH1D*)(finm->Get("h_etaphiJet1WJ"));
  TH1D *h_assym	   = (TH1D*)(finm->Get("h_assym"));
  TH1D *h_METovSUMET = (TH1D*)(finm->Get("h_METovSUMET"));
  TH1D *h_METovSUMET2 = (TH1D*)(finm->Get("h_METovSUMET2"));
  TH1D *h_MET         = (TH1D*)(finm->Get("h_MET"));
  TH1D *h_SUMET       = (TH1D*)(finm->Get("h_SUMET"));
  TH2D *h_METvsSUMET  = (TH2D*)(finm->Get("h_METvsSUMET"));
  TH1D *h_CHFJet1     = (TH1D*)(finm->Get("h_CHFJet1"));
  TH1D *h_NHFJet1     = (TH1D*)(finm->Get("h_NHFJet1"));

TH1D *h_NEMFJet1     = (TH1D*)(finm->Get("h_NEMFJet1"));
  TH1D *h_CEMFJet1     = (TH1D*)(finm->Get("h_CEMFJet1"));
  TH1D *h_NHFJet11tev= (TH1D*)(finm->Get("h_NHFJet11tev"));
  TH1D *h_NHFJet14tev= (TH1D*)(finm->Get("h_NHFJet14tev"));
  TH1D *h_MUFJet1     = (TH1D*)(finm->Get("h_MUFJet1"));
  TH1D *h_CMJet1      = (TH1D*)(finm->Get("h_CMJet1"));
  TH1D *h_NMJet1      = (TH1D*)(finm->Get("h_NMJet1"));
  TH1D *h_ptJet1      = (TH1D*)(finm->Get("h_ptJet1"));
  TH1D *h_PMJet1      = (TH1D*)(finm->Get("h_PMJet1"));
  TH1D *h_nVtx        = (TH1D*)(finm->Get("h_nVtx"));
  TH1D *h_ptJet1AK4   = (TH1D*)(finm->Get("h_ptJet1AK4"));
  TH1D *h_etaJet1AK4  = (TH1D*)(finm->Get("h_etaJet1AK4"));
  TH1D *h_phiJet1AK4  = (TH1D*)(finm->Get("h_phiJet1AK4"));
  TH1D *h_Dijet_MassAK4 = (TH1D*)(finm->Get("h_Dijet_MassAK4"));
  TH1D *h_deltaETA_AK4  = (TH1D*)(finm->Get("h_deltaETA_AK4"));
  TH1D *h_deltaPHI_AK4  = (TH1D*)(finm->Get("h_deltaPHI_AK4"));
  TH1D  *h_CosThetaStar_AK4 = (TH1D*)(finm->Get("h_CosThetaStar_AK4"));
  TH1D *h_ptJet1WJ          = (TH1D*)(finm->Get("h_ptJet1WJ"));
  TH1D *h_etaJet1WJ     = (TH1D*)(finm->Get("h_etaJet1WJ"));
  TH1D *h_phiJet1WJ     = (TH1D*)(finm->Get("h_phiJet1WJ"));
  TH1D *h_mjj           = (TH1D*)(finm->Get("h_mjj"));
  TH1D *h_deltaETAjj    = (TH1D*)(finm->Get("h_deltaETAjj"));
  TH1D *h_deltaPHIjj    = (TH1D*)(finm->Get("h_deltaPHIjj"));
  TH1D *h_deltaPHIjj2   = (TH1D*)(finm->Get("h_deltaPHIjj2"));
  TH1D *h_CosThetaStar_WJ  = (TH1D*)(finm->Get("h_CosThetaStar_WJ"));
TH1D *h_FourjetMass = (TH1D*)(finm->Get("h_FourjetMass"));
TH1D *h_Dijet_MassAK4_1 = (TH1D*)(finm->Get("h_Dijet_MassAK4_1"));
TH1D *h_Dijet_MassAK4_2 = (TH1D*)(finm->Get("h_Dijet_MassAK4_2"));
TH1D *h_MAverage = (TH1D*)(finm->Get("h_MAverage"));*/
TH2D *h_M4J_vs_M2J=(TH2D*)(finm->Get("h_M4J_vs_M2J"));
//TH1D *h_Masymmetry = (TH1D*)(finm->Get("h_Masymmetry"));
//TH2D *h_M4J_vs_DeltaRapidity=(TH2D*)(finm->Get("h_M4J_vs_DeltaRapidity"));




/*TH1D *h_CHFJet2     = (TH1D*)(finm->Get("h_CHFJet2"));
  TH1D *h_NHFJet2     = (TH1D*)(finm->Get("h_NHFJet2"));

TH1D *h_NEMFJet2     = (TH1D*)(finm->Get("h_NEMFJet2"));
  TH1D *h_CEMFJet2     = (TH1D*)(finm->Get("h_CEMFJet2"));
  TH1D *h_NHFJet21tev= (TH1D*)(finm->Get("h_NHFJet21tev"));
  TH1D *h_NHFJet24tev= (TH1D*)(finm->Get("h_NHFJet24tev"));
  TH1D *h_MUFJet2     = (TH1D*)(finm->Get("h_MUFJet2"));
  TH1D *h_CMJet2      = (TH1D*)(finm->Get("h_CMJet2"));
  TH1D *h_NMJet2      = (TH1D*)(finm->Get("h_NMJet2"));
  TH1D *h_ptJet2      = (TH1D*)(finm->Get("h_ptJet2"));
  TH1D *h_PMJet2      = (TH1D*)(finm->Get("h_PMJet2"));
  TH1D *h_nVtx        = (TH1D*)(finm->Get("h_nVtx"));
  TH1D *h_ptJet2AK4   = (TH1D*)(finm->Get("h_ptJet2AK4"));
  TH1D *h_etaJet2AK4  = (TH1D*)(finm->Get("h_etaJet2AK4"));
  TH1D *h_phiJet2AK4  = (TH1D*)(finm->Get("h_phiJet2AK4"));



TH1D *h_CHFJet3     = (TH1D*)(finm->Get("h_CHFJet3"));
  TH1D *h_NHFJet3     = (TH1D*)(finm->Get("h_NHFJet3"));

TH1D *h_NEMFJet3     = (TH1D*)(finm->Get("h_NEMFJet3"));
  TH1D *h_CEMFJet3     = (TH1D*)(finm->Get("h_CEMFJet3"));
  TH1D *h_MUFJet3     = (TH1D*)(finm->Get("h_MUFJet3"));
  TH1D *h_CMJet3      = (TH1D*)(finm->Get("h_CMJet3"));
  TH1D *h_NMJet3      = (TH1D*)(finm->Get("h_NMJet3"));
  TH1D *h_ptJet3      = (TH1D*)(finm->Get("h_ptJet3"));
  TH1D *h_PMJet3      = (TH1D*)(finm->Get("h_PMJet3"));
  TH1D *h_nVtx        = (TH1D*)(finm->Get("h_nVtx"));
  TH1D *h_ptJet3AK4   = (TH1D*)(finm->Get("h_ptJet3AK4"));
  TH1D *h_etaJet3AK4  = (TH1D*)(finm->Get("h_etaJet3AK4"));
  TH1D *h_phiJet3AK4  = (TH1D*)(finm->Get("h_phiJet3AK4"));


TH1D *h_CHFJet4     = (TH1D*)(finm->Get("h_CHFJet4"));
  TH1D *h_NHFJet4     = (TH1D*)(finm->Get("h_NHFJet4"));

TH1D *h_NEMFJet4     = (TH1D*)(finm->Get("h_NEMFJet4"));
  TH1D *h_CEMFJet4     = (TH1D*)(finm->Get("h_CEMFJet4"));
  TH1D *h_MUFJet4     = (TH1D*)(finm->Get("h_MUFJet4"));
  TH1D *h_CMJet4      = (TH1D*)(finm->Get("h_CMJet4"));
  TH1D *h_NMJet4      = (TH1D*)(finm->Get("h_NMJet4"));
  TH1D *h_ptJet4      = (TH1D*)(finm->Get("h_ptJet4"));
  TH1D *h_PMJet4      = (TH1D*)(finm->Get("h_PMJet4"));
  TH1D *h_nVtx        = (TH1D*)(finm->Get("h_nVtx"));
  TH1D *h_ptJet4AK4   = (TH1D*)(finm->Get("h_ptJet4AK4"));
  TH1D *h_etaJet4AK4  = (TH1D*)(finm->Get("h_etaJet4AK4"));
  TH1D *h_phiJet4AK4  = (TH1D*)(finm->Get("h_phiJet4AK4"));*/
TH2D *h_DijetMassAK4_1_vs_2=(TH2D*)(finm->Get("h_DijetMassAK4_1_vs_2"));


TH1D *h_DeltaEtaJJAK4 = (TH1D*)(finm->Get("h_DeltaEtaJJAK4"));
TH1D *h_DeltaPhiJJAK4=(TH1D*)(finm->Get("h_DeltaPhiJJAK4"));
TH1D *h_DeltaRAK4_First=(TH1D*)(finm->Get("h_DeltaRAK4_First"));
TH1D *h_DeltaRAK4_Second = (TH1D*)(finm->Get("h_DeltaRAK4_Second"));


TH1D *h_ETA_1=(TH1D*)(finm->Get("h_ETA_1"));
TH1D *h_ETA_2=(TH1D*)(finm->Get("h_ETA_2"));
TH1D *h_Rapidity_1=(TH1D*)(finm->Get("h_Rapidity_1"));
TH1D *h_Rapidity_2=(TH1D*)(finm->Get("h_Rapidity_2"));
TH1D *h_DeltaRapidity=(TH1D*)(finm->Get("h_DeltaRapidity"));
 
  char name[100];
//RATIOS
 TH1D *hr_ptJet1WJ,*hr_etaJet1WJ,*hr_phiJet1WJ,*hr_DeltaEtaJJAK4, *hr_DeltaPhiJJAK4,*hr_CosThetaStar_WJ,*hr_METovSUMET,*hr_mjj,*hr_DeltaRAK4_First,*hr_DeltaRAK4_Second;
 
 const int nMassBins = 103;
 
 double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 4509,
     4686,  4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};
 

 //ratios
/*


 sprintf(name,"hr_DeltaEtaJJAK4");
    hr_DeltaEtaJJAK4 = new TH1D(name,"",21,0.,1.1);

 sprintf(name,"hr_DeltaPhiJJAK4");
    hr_DeltaPhiJJAK4 = new TH1D(name,"",36,0.,3.1416);


 sprintf(name,"hr_DeltaRAK4_First");
    hr_DeltaRAK4_First = new TH1D(name,"",70.,0.,7.);

 sprintf(name,"hr_DeltaRAK4_Second");
    hr_DeltaRAK4_Second= new TH1D(name,"",70.,0.,7.);
    sprintf(name,"hr_mjj"); 
    hr_mjj= new TH1D(name,"",103,massBoundaries);

 sprintf(name,"hr_Masymmetry"); 
    hr_Masymmetry= new TH1D(name,"",100,0.,1.);

sprintf(name,"hr_FourjetMass"); 
    hr_FourjetMass= new TH1D(name,"",103,massBoundaries);


sprintf(name,"hr_Dijet_MassAK4_1"); 
    hr_Dijet_MassAK4_1= new TH1D(name,"",103,massBoundaries);


sprintf(name,"hr_Dijet_MassAK4_2"); 
    hr_Dijet_MassAK4_2= new TH1D(name,"",103,massBoundaries);


sprintf(name,"hr_mjj"); 
    hr_mjj= new TH1D(name,"",103,massBoundaries);

sprintf(name,"hr_DeltaRapidity");
hr_DeltaRapidity=new TH1D(name,"",60.,0.,5);

sprintf(name,"hr_Rapidity_1");
hr_Rapidity_1= new TH1D(name,"",60,-3.,3.);


sprintf(name,"hr_Rapidity_2");
hr_Rapidity_2= new TH1D(name,"",60,-3.,3.);


sprintf(name,"hr_ETA_1");
hr_ETA_1= new TH1D(name,"",80,-8.,8.);

sprintf(name,"hr_ETA_2");
hr_ETA_2= new TH1D(name,"",80,-8.,8.);


    sprintf(name,"hr_ptJet1WJ");
    hr_ptJet1WJ = new TH1D(name, "", 50,0,5.0);

 sprintf(name,"hr_ptJet1AK4");
    hr_ptJet1AK4 = new TH1D(name, "", 50,0,5.0);
sprintf(name,"hr_ptJet4AK4");
    hr_ptJet4AK4 = new TH1D(name, "", 50,0,5.0);
sprintf(name,"hr_ptJet2AK4");
    hr_ptJet3AK4 = new TH1D(name, "", 50,0,5.0);
sprintf(name,"hr_ptJet3AK4");
    hr_ptJet1AK4 = new TH1D(name, "", 50,0,5.0);
    sprintf(name,"hr_etaJet1WJ");
    hr_etaJet1WJ = new TH1D(name, "", 60,-3,3);

    sprintf(name,"hr_phiJet1WJ");
    hr_phiJet1WJ = new TH1D(name, "", 72,-3.1416,3.1416);
    sprintf(name,"hr_deltaETAjj");
    hr_deltaETAjj = new TH1D(name ,"",60,0.,1.1);
    sprintf(name,"hr_deltaPHIjj");
    hr_deltaPHIjj = new TH1D(name, "",80,0,6.3);
  
    sprintf(name,"hr_deltaPHIjj2");
    hr_deltaPHIjj2 = new TH1D(name, "",36,0,3.1416);
  
    sprintf(name,"hr_METovSUMET");
    hr_METovSUMET = new TH1D(name, "", 100,0,1.0);
    sprintf(name,"hr_CosThetaStar_WJ");
    hr_CosThetaStar_WJ = new TH1D(name,"",100,-1.3,1.3); 
 
    hr_ptJet1WJ->Sumw2();
    hr_etaJet1WJ->Sumw2();
    hr_phiJet1WJ->Sumw2();
    hr_deltaETAjj->Sumw2();
    hr_deltaPHIjj->Sumw2(); 
    hr_deltaPHIjj2->Sumw2(); 
    hr_METovSUMET->Sumw2();
    hr_CosThetaStar_WJ->Sumw2();
    hr_mjj->Sumw2();
hr_DeltaEtaJJAK4->Sumw2();
hr_DeltaPhiJJAK4->Sumw2();
hr_DeltaRAK4_First->Sumw2();
hr_DeltaRAK4_Second->Sumw2();

hr_ptJet1AK4->Sumw2();

hr_ptJet2AK4->Sumw2();

hr_ptJet3AK4->Sumw2();

hr_ptJet4AK4->Sumw2();

    hr_FourjetMass->Sumw2();
    hr_Dijet_MassAK4_1->Sumw2();
    hr_Dijet_MassAK4_2->Sumw2();
hr_ptJet1AK4->Sumw2();
hr_Masymmetry->Sumw2();



hr_DeltaRapidity->Sumw2();
hr_Rapidity_1->Sumw2();
hr_Rapidity_2->Sumw2();

hr_ETA_1->Sumw2();
hr_ETA_2->Sumw2();
 
    hr_ptJet1WJ->SetYTitle("Data/simulation");
    hr_etaJet1WJ->SetYTitle("Data/simulation");
    hr_phiJet1WJ->SetYTitle("Data/simulation");
    hr_deltaETAjj->SetYTitle("Data/simulation");
    hr_deltaPHIjj->SetYTitle("Data/simulation");
    hr_deltaPHIjj2->SetYTitle("Data/simulation");
    hr_METovSUMET->SetYTitle("Data/simulation");
    hr_CosThetaStar_WJ->SetYTitle("Data/simulation");
    hr_mjj->SetYTitle("Data/simulation");
hr_ptJet1AK4->SetYTitle("Data/simulation");
hr_ptJet2AK4->SetYTitle("Data/simulation");
hr_ptJet3AK4->SetYTitle("Data/simulation");
hr_ptJet4AK4->SetYTitle("Data/simulation");
hr_Masymmetry->SetYTitle("Data/simulation");



hr_DeltaEtaJJAK4->SetYTitle("Data/simulation");
hr_DeltaPhiJJAK4->SetYTitle("Data/simulation");
hr_DeltaRAK4_First->SetYTitle("Data/simulation");
hr_DeltaRAK4_Second->SetYTitle("Data/simulation");


hr_DeltaRapidity->SetYTitle("Data/Simulation");
hr_Rapidity_1->SetYTitle("Data/Simulation");
hr_Rapidity_2->SetYTitle("Data/Simulation");

hr_ETA_1->SetYTitle("Data/Simulation");
hr_ETA_2->SetYTitle("Data/Simulation");
//<0.9 - 0.8 cemf:*/

/*h_mjj->Scale(-1);
h_mjj->Add(h_mjj_data);*/

 
   //h_mjj_data->Add(h_mjj,-1); 
//h_mjj_data->Divide(h_mjj_data);
  
 
   

    /* h_CHFJet1->SetLineWidth(2);
     h_CHFJet1->SetLineWidth(2);
     h_CHFJet1_data->SetLineColor(1);
     h_CHFJet1->SetLineColor(2);

     h_NHFJet1->SetLineWidth(2);
     h_NHFJet1->SetLineWidth(2);
     h_NHFJet1_data->SetLineColor(1);
     h_NHFJet1->SetLineColor(2);


 TLegend *leg1 =new TLegend(.55, .85, .65, .93);
     leg1->SetFillColor(0);
     leg1->SetBorderSize(0);
     leg1->AddEntry(h_CHFJet1_data, "Data", "p");
     leg1->AddEntry(h_CHFJet1, "MC", "L");

  TLegend *leg2 =new TLegend(.74, .8, .9, .88);
     leg2->SetFillColor(0);
     leg2->SetBorderSize(0);
     leg2->AddEntry(h_NHFJet1_data, "Data", "p");
     leg2->AddEntry(h_NHFJet1, "MC", "L");*/

  TLegend *leg3 =new TLegend(.6, .85, .8, .9);
     leg3->SetFillColor(0);
     leg3->SetBorderSize(0);   
     leg3->AddEntry(h_M4J_vs_M2J,"QCD MC","p");
     leg3->SetTextSize(0.02);
//leg->AddEntry(Blank,"m_{#chi}/M_{S}=0.25, y_{uu}=0.4,y_{x}=0.6","l");
       // leg->AddEntry(Blank,"M_{S}=8400 GeV, m_{#chi}=2100 GeV","l");*/

  TLegend *leg4 =new TLegend(.6, .85, .8, .9);
     leg4->SetFillColor(0);
     leg4->SetBorderSize(0);
     leg4->AddEntry(h_M4J_vs_M2J_data, "Data", "p");
     leg4->SetTextSize(0.03);


for(int i=1;i<nMassBins;i++)
{

cout << " BinContent " << h_FourjetMass_data->GetBinContent(i) << " Bin Center " << h_FourjetMass_data->GetBinCenter(i) <<  endl;

}


  /*
  TCanvas *pad15r = new TCanvas("pad15r","example",600,1000);
    TPad *pad7r = new TPad("pad7r","pad7r",0,0.4,1,1); 
    pad7r->SetBottomMargin(0);
    pad7r->Draw();
    pad7r->cd();  
    pad7r->cd()->SetLogy(1);
    h_METovSUMET->GetXaxis()->SetTitle("MET/SUMET");
    h_METovSUMET->GetYaxis()->SetTitle("Entries");
    h_METovSUMET->SetLineWidth(2);
    h_METovSUMET->SetLineWidth(2);
    h_METovSUMET->SetLineColor(2);  
    h_METovSUMET_data->SetLineColor(1);
    h_METovSUMET->Scale(h_METovSUMET_data->Integral()/h_METovSUMET->Integral());
    h_METovSUMET->Draw("HIST");
    h_METovSUMET_data->Draw("same e");
    paveCMS ->Draw("same");
    paveCMS3 ->Draw("same");
    leg2->Draw();
    pad15r->cd();
    TPad *pad8r = new TPad("pad8r","pad8r",0,0.02,1,0.4); 
    pad8r->SetTopMargin(0);
    pad8r->Draw();
    pad8r->cd();
    hr_METovSUMET->Divide(h_METovSUMET_data,h_METovSUMET);
    cout << " OK? METSUET " << endl;
    hr_METovSUMET->GetXaxis()->SetTitle("MET/SUMET");
    hr_METovSUMET->GetYaxis()->SetRangeUser(0.,2.);
    hr_METovSUMET->Draw("e");   
    pad15r->cd();*/
//
 

 /*TCanvas *pad19r = new TCanvas("pad19r","example",600,1000);
    TPad *pad11a2r = new TPad("pad11a2r","pad11a2r",0,0.4,1,1); 
    pad11a2r->SetBottomMargin(0);
    pad11a2r->Draw();
    pad11a2r->cd();
    pad11a2r->cd()->SetLogy(1);
pad11a2r->cd()->SetLogy(1);
     h_mjj_data->GetXaxis()->SetTitle("Dijet Mass (GeV)");
     h_mjj_data->GetYaxis()->SetTitle("Entries");
     h_mjj_data->SetLineWidth(2);
     h_mjj->SetLineWidth(2);
     h_mjj->SetLineColor(2);
     h_mjj_data->SetLineColor(1);
   // h_mjj->Scale(h_mjj_data->Integral()/h_mjj->Integral());
  //h_mjj->Scale(2.48);
    // h_mjj->GetXaxis()->SetLabelSize(0.035);
     h_mjj_data->GetXaxis()->SetRangeUser(1530.,8000.);
     h_mjj_data->GetXaxis()->SetLabelSize(0.035);
     h_mjj_data->Draw("e");
    h_mjj->Draw("same HIST");
     paveCMS ->Draw("same"); 
     paveCMS3->Draw("same");
     leg2->Draw();
     pad19r->cd(); 
    TPad *pad1003ar = new TPad("pad22ar","pad22ar",0,0.02,1,0.4); 
    pad22ar->SetTopMargin(0);
    pad22ar->Draw();
    pad22ar->cd();
    hr_mjj->Divide(h_mjj_data,h_mjj_data);//inversion for cemf>0.8
        cout << " OK? mjj " << endl;
    hr_mjj->GetXaxis()->SetTitle("Dijet Mass (GeV)");
    hr_mjj->GetXaxis()->SetRangeUser(1530.,8000.);
    hr_mjj->GetYaxis()->SetRangeUser(0.,2.0);
    hr_mjj->Draw("e");
    pad19r->cd();*/


 /*TCanvas *pad59r = new TCanvas("pad59r","example",600,1000);
    TPad *pad60r = new TPad("pad60r","pad60r",0,0.4,1,1); 
    pad60r->SetBottomMargin(0);
    pad60r->Draw();
    pad60r->cd();
    pad60r->cd()->SetLogy(1);
pad60r->cd()->SetLogy(1);
     h_Masymmetry_data->GetXaxis()->SetTitle("MAsymmetry");
     h_Masymmetry_data->GetYaxis()->SetTitle("Entries");
     h_Masymmetry_data->SetLineWidth(2);
     h_Masymmetry->SetLineWidth(2);
    h_Masymmetry->SetLineColor(2);
     h_Masymmetry_data->SetLineColor(1);
     h_Masymmetry->Scale(h_Masymmetry_data->Integral()/h_Masymmetry->Integral());
  //h_Masymmetry->Scale(2.48);
    // h_Masymmetry->GetXaxis()->SetLabelSize(0.035);
    // h_Masymmetry_data->GetXaxis()->SetRangeUser(0.,10000.);
     h_Masymmetry_data->GetXaxis()->SetLabelSize(0.035);
     h_Masymmetry_data->Draw("e");
    h_Masymmetry->Draw("same HIST");
     paveCMS ->Draw("same"); 
     paveCMS3->Draw("same");
     leg2->Draw();
     pad59r->cd(); 
    TPad *pad61 = new TPad("pad61","pad61",0,0.02,1,0.4); 
    pad61->SetTopMargin(0);
    pad61->Draw();
    pad61->cd();
    hr_Masymmetry->Divide(h_Masymmetry_data,h_Masymmetry);//inversion for cemf>0.8
        cout << " OK? mjj " << endl;
    hr_Masymmetry->GetXaxis()->SetTitle("M asymmetry");
    hr_Masymmetry->GetXaxis()->SetRangeUser(0.,10000.);
    hr_Masymmetry->GetYaxis()->SetRangeUser(0.,2.0);
    hr_Masymmetry->Draw("e");
    pad59r->cd();


TCanvas *pad50r = new TCanvas("pad50r","example",600,1000);
    TPad *pad51r = new TPad("pad51r","pad51r",0,0.4,1,1); 
    pad51r->SetBottomMargin(0);
    pad51r->Draw();
    pad51r->cd();
    pad51r->cd()->SetLogy(1);
pad51r->cd()->SetLogy(1);
     h_ptJet1_dataAK4->GetXaxis()->SetTitle("Dijet Mass (GeV)");
     h_ptJet1_dataAK4->GetYaxis()->SetTitle("Entries");
     h_ptJet1_dataAK4->SetLineWidth(2);
     h_ptJet1AK4->SetLineWidth(2);
     h_ptJet1AK4->SetLineColor(2);
     h_ptJet1_dataAK4->SetLineColor(1);
   h_ptJet1AK4->Scale(h_ptJet1_dataAK4->Integral()/h_ptJet1AK4->Integral());
  //h_ptJet1->Scale(2.48);
    // h_ptJet1->GetXaxis()->SetLabelSize(0.035);
   
     h_ptJet1_dataAK4->GetXaxis()->SetLabelSize(0.035);
     h_ptJet1_dataAK4->Draw("e");
    h_ptJet1AK4->Draw("same HIST");
     paveCMS ->Draw("same"); 
     paveCMS3->Draw("same");
     leg2->Draw();
     pad50r->cd(); 
    TPad *pad52r = new TPad("pad52r","pad52r",0,0.02,1,0.4); 
    pad52r->SetTopMargin(0);
    pad52r->Draw();
    pad52r->cd();
    hr_ptJet1AK4->Divide(h_ptJet1_dataAK4,h_ptJet1AK4);//inversion for cemf>0.8
        cout << " OK? ptJet1 " << endl;
    hr_ptJet1AK4->GetXaxis()->SetTitle("p_{T} Jet1 (GeV)");
    hr_ptJet1AK4->GetYaxis()->SetRangeUser(0.,2.0);
    hr_ptJet1AK4->Draw("e");
    pad50r->cd();
*/



/* TCanvas *pad42r = new TCanvas("pad42r","example",600,1000);
    TPad *pad41r = new TPad("pad41r","pad41r",0,0.4,1,1); 
    pad41r->SetBottomMargin(0);
    pad41r->Draw();
    pad41r->cd();
    pad41r->cd()->SetLogy(1);
pad41r->cd()->SetLogy(1);
     h_FourjetMass_data->GetXaxis()->SetTitle("Fourjet Mass (GeV)");
     h_FourjetMass_data->GetYaxis()->SetTitle("Entries");
     h_FourjetMass_data->SetLineWidth(2);
     h_FourjetMass->SetLineWidth(2);
    h_FourjetMass->SetLineColor(2);
     h_FourjetMass_data->SetLineColor(1);
cout << "Integal data" << h_FourjetMass_data->Integral() << endl;
cout << "Integral MC" << h_FourjetMass->Integral() << endl;
   h_FourjetMass->Scale(h_FourjetMass_data->Integral()/h_FourjetMass->Integral());
  //h_FourjetMass->Scale(2.48);
    // h_FourjetMass->GetXaxis()->SetLabelSize(0.035);
cout.precision(4);
cout << "MC at  TeV" << h_FourjetMass->Integral(86.,87.) << endl;
cout << "data at 8 TeV" << h_FourjetMass_data->Integral(86.,87.) << endl;
     h_FourjetMass_data->GetXaxis()->SetRangeUser(1455,10000.);
     h_FourjetMass_data->GetXaxis()->SetLabelSize(0.035);
     h_FourjetMass_data->Draw("e");
    h_FourjetMass->Draw("same HIST");
     paveCMS ->Draw("same"); 
     paveCMS3->Draw("same");
     leg2->Draw();
     pad42r->cd(); 
    TPad *pad1003ar = new TPad("pad1003ar","pad1003ar",0,0.02,1,0.4); 
    pad1003ar->SetTopMargin(0);
    pad1003ar->Draw();
    pad1003ar->cd();
    hr_FourjetMass->Divide(h_FourjetMass_data,h_FourjetMass);//inversion for cemf>0.8
        cout << " OK? mjj " << endl;
    hr_FourjetMass->GetXaxis()->SetTitle("Fourjet Mass (GeV)");
    hr_FourjetMass->GetXaxis()->SetRangeUser(1455.,10000.);
    hr_FourjetMass->GetYaxis()->SetRangeUser(0.,2.0);
    hr_FourjetMass->Draw("e");
    pad42r->cd();*/
/*

 TCanvas *pad43r = new TCanvas("pad43r","example",600,1000);
    TPad *pad44r = new TPad("pad44r","pad44r",0,0.4,1,1); 
    pad44r->SetBottomMargin(0);
    pad44r->Draw();
    pad44r->cd();
    pad44r->cd()->SetLogy(1);
pad44r->cd()->SetLogy(1);
     h_Dijet_MassAK4_1_data->GetXaxis()->SetTitle("Dijet Mass (GeV)");
     h_Dijet_MassAK4_1_data->GetYaxis()->SetTitle("Entries");
     h_Dijet_MassAK4_1_data->SetLineWidth(2);
     h_Dijet_MassAK4_1->SetLineWidth(2);
     h_Dijet_MassAK4_1->SetLineColor(2);
     h_Dijet_MassAK4_1_data->SetLineColor(1);
    h_Dijet_MassAK4_2_data->SetLineColor(2);
    h_Dijet_MassAK4_2_data->SetMarkerColor(2);
     
 h_Dijet_MassAK4_1->Scale(h_Dijet_MassAK4_1_data->Integral()/h_Dijet_MassAK4_1->Integral());
  //h_Dijet_MassAK4_1->Scale(2.48);
    // h_Dijet_MassAK4_1->GetXaxis()->SetLabelSize(0.035);
     h_Dijet_MassAK4_1_data->GetXaxis()->SetRangeUser(606.,2232.);
     h_Dijet_MassAK4_1_data->GetXaxis()->SetLabelSize(0.035);
     h_Dijet_MassAK4_1_data->Draw("e");
  //  h_Dijet_MassAK4_1->Draw("same HIST");
h_Dijet_MassAK4_2_data->Draw("same e");
     paveCMS ->Draw("same"); 
     paveCMS3->Draw("same");
     leg2->Draw();
     pad43r->cd(); 
    TPad *pad1004ar = new TPad("pad1004ar","pad1004ar",0,0.02,1,0.4); 
    pad1004ar->SetTopMargin(0);
    pad1004ar->Draw();
    pad1004ar->cd();
    hr_Dijet_MassAK4_1->Divide(h_Dijet_MassAK4_1_data,h_Dijet_MassAK4_2_data);//inversion for cemf>0.8
TLine *l2 = new TLine(606,1.,2232.,1.);
l2->SetLineWidth(2);
l2->SetLineColor(2);
        cout << " OK? mjj " << endl;
    hr_Dijet_MassAK4_1->GetXaxis()->SetTitle("Dijet Mass AK4 1 (GeV)");
    hr_Dijet_MassAK4_1->GetXaxis()->SetRangeUser(606.,2232);
    hr_Dijet_MassAK4_1->GetYaxis()->SetRangeUser(0.,2.0);
    hr_Dijet_MassAK4_1->Draw("e");
l2->Draw("same");
    pad43r->cd();





 /*TCanvas *pad45r = new TCanvas("pad45r","example",600,1000);
    TPad *pad46r = new TPad("pad46r","pad46r",0,0.4,1,1); 
    pad46r->SetBottomMargin(0);
    pad46r->Draw();
    pad46r->cd();
    pad46r->cd()->SetLogy(1);
pad46r->cd()->SetLogy(1);
     h_Dijet_MassAK4_2_data->GetXaxis()->SetTitle("Dijet Mass (GeV)");
     h_Dijet_MassAK4_2_data->GetYaxis()->SetTitle("Entries");
     h_Dijet_MassAK4_2_data->SetLineWidth(2);
     h_Dijet_MassAK4_2->SetLineWidth(2);
    h_Dijet_MassAK4_2->SetLineColor(2);
     h_Dijet_MassAK4_2_data->SetLineColor(1);
   h_Dijet_MassAK4_2->Scale(h_Dijet_MassAK4_2_data->Integral()/h_Dijet_MassAK4_2->Integral());
  //h_Dijet_MassAK4_2->Scale(2.48);
    // h_Dijet_MassAK4_2->GetXaxis()->SetLabelSize(0.035);
     h_Dijet_MassAK4_2_data->GetXaxis()->SetRangeUser(0.,5000.);
     h_Dijet_MassAK4_2_data->GetXaxis()->SetLabelSize(0.035);
     h_Dijet_MassAK4_2_data->Draw("e");
    h_Dijet_MassAK4_2->Draw("same HIST");
     paveCMS ->Draw("same"); 
     paveCMS3->Draw("same");
     leg2->Draw();
     pad45r->cd(); 
    TPad *pad1005ar = new TPad("pad1005ar","pad1005ar",0,0.02,1,0.4); 
    pad1005ar->SetTopMargin(0);
    pad1005ar->Draw();
    pad1005ar->cd();
    hr_Dijet_MassAK4_2->Divide(h_Dijet_MassAK4_2_data,h_Dijet_MassAK4_2);//inversion for cemf>0.8
        cout << " OK? mjj " << endl;
    hr_Dijet_MassAK4_2->GetXaxis()->SetTitle("Dijet Mass AK4 2 (GeV)");
    hr_Dijet_MassAK4_2->GetXaxis()->SetRangeUser(0.,5000.);
    hr_Dijet_MassAK4_2->GetYaxis()->SetRangeUser(0.,2.0);
    hr_Dijet_MassAK4_2->Draw("e");
    pad45r->cd();





TCanvas *pad100r = new TCanvas("pad100r","example",600,1000);
    TPad *pad101r = new TPad("pad101r","pad101r",0,0.4,1,1); 
    pad101r->SetBottomMargin(0);
    pad101r->Draw();
    pad101r->cd();
    pad101r->cd()->SetLogy(1);
pad101r->cd()->SetLogy(1);
     h_DeltaEtaJJAK4_data->GetXaxis()->SetTitle("#Delta #eta");
     h_DeltaEtaJJAK4_data->GetYaxis()->SetTitle("Entries");
     h_DeltaEtaJJAK4_data->SetLineWidth(2);
     h_DeltaEtaJJAK4->SetLineWidth(2);
    h_DeltaEtaJJAK4->SetLineColor(2);
     h_DeltaEtaJJAK4_data->SetLineColor(1);
     h_DeltaEtaJJAK4->Scale(h_DeltaEtaJJAK4_data->Integral()/h_DeltaEtaJJAK4->Integral());
  //h_DeltaEtaJJAK4->Scale(2.48);
    // h_DeltaEtaJJAK4->GetXaxis()->SetLabelSize(0.035);
     h_DeltaEtaJJAK4_data->GetXaxis()->SetLabelSize(0.035);
     h_DeltaEtaJJAK4_data->Draw("e");
    h_DeltaEtaJJAK4->Draw("same HIST");
     paveCMS ->Draw("same"); 
     paveCMS3->Draw("same");
     leg2->Draw();
     pad100r->cd(); 
    TPad *pad22ar = new TPad("pad22ar","pad22ar",0,0.02,1,0.4); 
    pad22ar->SetTopMargin(0);
    pad22ar->Draw();
    pad22ar->cd();
hr_DeltaEtaJJAK4->GetXaxis()->SetTitle("#Delta #eta");
    hr_DeltaEtaJJAK4->Divide(h_DeltaEtaJJAK4_data,h_DeltaEtaJJAK4);//inversion for cemf>0.8
        cout << " OK? mjj " << endl;
    hr_DeltaEtaJJAK4->GetYaxis()->SetRangeUser(0.,2.0);
    hr_DeltaEtaJJAK4->Draw("e");
    pad100r->cd();





 TCanvas *pad102r = new TCanvas("pad102r","example",600,1020);
    TPad *pad103r = new TPad("pad103r","pad103r",0,0.4,1,1); 
    pad103r->SetBottomMargin(0);
    pad103r->Draw();
    pad103r->cd();
    pad103r->cd()->SetLogy(1);
pad103r->cd()->SetLogy(1);
     h_DeltaPhiJJAK4_data->GetXaxis()->SetTitle("#Delta #Phi");
     h_DeltaPhiJJAK4_data->GetYaxis()->SetTitle("Entries");
     h_DeltaPhiJJAK4_data->SetLineWidth(2);
     h_DeltaPhiJJAK4->SetLineWidth(2);
    h_DeltaPhiJJAK4->SetLineColor(2);
     h_DeltaPhiJJAK4_data->SetLineColor(1);
 h_DeltaPhiJJAK4_data->GetXaxis()->SetRangeUser(0.,3.1416);
     h_DeltaPhiJJAK4->Scale(h_DeltaPhiJJAK4_data->Integral()/h_DeltaPhiJJAK4->Integral());
  //h_DeltaPhiJJAK4->Scale(2.48);
    // h_DeltaPhiJJAK4->GetXaxis()->SetLabelSize(0.035);
     h_DeltaPhiJJAK4_data->GetXaxis()->SetLabelSize(0.035);
     h_DeltaPhiJJAK4_data->Draw("e");
    h_DeltaPhiJJAK4->Draw("same HIST");
     paveCMS ->Draw("same"); 
     paveCMS4->Draw("same");
     leg1->Draw();
     pad102r->cd(); 
    TPad *pad1011ar = new TPad("pad1011ar","pad1011ar",0,0.02,1,0.4); 
    pad1011ar->SetTopMargin(0);
    pad1011ar->Draw();
    pad1011ar->cd();
hr_DeltaPhiJJAK4->GetXaxis()->SetTitle("#Delta #Phi");
    hr_DeltaPhiJJAK4->GetXaxis()->SetRangeUser(0.,3.1416);
    hr_DeltaPhiJJAK4->Divide(h_DeltaPhiJJAK4_data,h_DeltaPhiJJAK4);//inversion for cemf>0.8
        cout << " OK? mjj " << endl;
    hr_DeltaPhiJJAK4->GetYaxis()->SetRangeUser(0.,2.0);
    hr_DeltaPhiJJAK4->Draw("e");
    pad102r->cd();




/*TCanvas *pad120r = new TCanvas("pad120r","example",600,1020);
    TPad *pad121r = new TPad("pad121r","pad121r",0,0.4,1,1); 
    pad103r->SetBottomMargin(0);
    pad103r->Draw();
    pad103r->cd();
    pad103r->cd()->SetLogy(1);
pad103r->cd()->SetLogy(1);
     h_DeltaPhiJJAK4_data->GetXaxis()->SetTitle("#Delta #Phi");
     h_DeltaPhiJJAK4_data->GetYaxis()->SetTitle("Entries");
     h_DeltaPhiJJAK4_data->SetLineWidth(2);
     h_DeltaPhiJJAK4->SetLineWidth(2);
    h_DeltaPhiJJAK4->SetLineColor(2);
     h_DeltaPhiJJAK4_data->SetLineColor(1);
     h_DeltaPhiJJAK4->Scale(h_DeltaPhiJJAK4_data->Integral()/h_DeltaPhiJJAK4->Integral());
  //h_DeltaPhiJJAK4->Scale(2.48);
    // h_DeltaPhiJJAK4->GetXaxis()->SetLabelSize(0.035);
     h_DeltaPhiJJAK4_data->GetXaxis()->SetLabelSize(0.035);
     h_DeltaPhiJJAK4_data->Draw("e");
    h_DeltaPhiJJAK4->Draw("same HIST");
     paveCMS ->Draw("same"); 
     paveCMS3->Draw("same");
     leg2->Draw();
     pad102r->cd(); 
    TPad *pad1006ar = new TPad("pad1006ar","pad1006ar",0,0.02,1,0.4); 
    pad1006ar->SetTopMargin(0);
    pad1006ar->Draw();
    pad1006ar->cd();
hr_DeltaPhiJJAK4->GetXaxis()->SetTitle("#Delta #Phi");
    hr_DeltaPhiJJAK4->Divide(h_DeltaPhiJJAK4_data,h_DeltaPhiJJAK4);//inversion for cemf>0.8
        cout << " OK? mjj " << endl;
    hr_DeltaPhiJJAK4->GetYaxis()->SetRangeUser(0.,2.0);
    hr_DeltaPhiJJAK4->Draw("e");
    pad102r->cd();*/


/*
TCanvas *pad130r = new TCanvas("pad130r","example",600,1020);
   TPad *pad150r = new TPad("pad150r","pad150r",0,0.4,1,1); 
    pad150r->SetBottomMargin(0);
   pad150r->Draw();
   // pad130r->cd();
    //pad130r->cd()->SetLogy(1);
pad150r->cd()->SetLogy(1);
     h_DeltaRapidity_data->GetXaxis()->SetTitle("#Delta Rapidity");
     h_DeltaRapidity_data->GetYaxis()->SetTitle("Entries");
     h_DeltaRapidity_data->SetLineWidth(2);
     h_DeltaRapidity->SetLineWidth(2);
    h_DeltaRapidity->SetLineColor(2);
     h_DeltaRapidity_data->SetLineColor(1);
     h_DeltaRapidity->Scale(h_DeltaRapidity_data->Integral()/h_DeltaRapidity->Integral());
  //h_DeltaRapidity->Scale(2.48);
    // h_DeltaRapidity->GetXaxis()->SetLabelSize(0.035);
     h_DeltaRapidity_data->GetXaxis()->SetLabelSize(0.035);
     h_DeltaRapidity_data->Draw("e");
   h_DeltaRapidity->Draw("same HIST");
     paveCMS ->Draw("same"); 
     paveCMS3->Draw("same");
     leg2->Draw();
     pad130r->cd(); 
    TPad *pad1007ar = new TPad("pad1007ar","pad1007ar",0,0.02,1,0.4); 
    pad1007ar->SetTopMargin(0);
    pad1007ar->Draw();
    pad1007ar->cd();
hr_DeltaRapidity->GetXaxis()->SetTitle("#Delta Rapidity");
    hr_DeltaRapidity->Divide(h_DeltaRapidity_data,h_DeltaRapidity);//inversion for cemf>0.8
        cout << " OK? mjj " << endl;
    hr_DeltaRapidity->GetYaxis()->SetRangeUser(0.,2.0);
    hr_DeltaRapidity->Draw("e");
    pad130r->cd();




TCanvas *pad122r = new TCanvas("pad122r","example",600,1020);
  TPad *pad123r = new TPad("pad123r","pad123r",0,0.4,1,1); 
    pad123r->SetBottomMargin(0);
    pad123r->Draw();
    pad123r->cd();
    pad123r->cd()->SetLogy(1);
//pad122r->cd()->SetLogy(1);
     h_Rapidity_1_data->GetXaxis()->SetTitle("Rapidity 1");
     h_Rapidity_1_data->GetYaxis()->SetTitle("Entries");
     h_Rapidity_1_data->SetLineWidth(2);
     h_Rapidity_1->SetLineWidth(2);
    h_Rapidity_1->SetLineColor(2);
     h_Rapidity_1_data->SetLineColor(1);
    h_Rapidity_1->Scale(h_Rapidity_1_data->Integral()/h_Rapidity_1->Integral());
  //h_Rapidity_1->Scale(2.48);
    // h_Rapidity_1->GetXaxis()->SetLabelSize(0.035);
     h_Rapidity_1_data->GetXaxis()->SetLabelSize(0.035);
     h_Rapidity_1_data->Draw("e");
    h_Rapidity_1->Draw("same HIST");
     paveCMS ->Draw("same"); 
     paveCMS3->Draw("same");
     leg2->Draw();
     pad122r->cd(); 
    TPad *pad1008ar = new TPad("pad1008ar","pad1008ar",0,0.02,1,0.4); 
    pad1008ar->SetTopMargin(0);
    pad1008ar->Draw();
    pad1008ar->cd();
hr_Rapidity_1->GetXaxis()->SetTitle("Rapidity 1");
    hr_Rapidity_1->Divide(h_Rapidity_1_data,h_Rapidity_1);//inversion for cemf>0.8
        cout << " OK? mjj " << endl;
    hr_Rapidity_1->GetYaxis()->SetRangeUser(0.,2.0);
    hr_Rapidity_1->Draw("e");
    pad122r->cd();







TCanvas *pad124r = new TCanvas("pad124r","example",600,1020);
   TPad *pad125r = new TPad("pad125r","pad125r",0,0.4,1,1); 
    pad125r->SetBottomMargin(0);
    pad125r->Draw();
    pad125r->cd();
    pad125r->cd()->SetLogy(1);
//pad124r->cd()->SetLogy(1);
     h_Rapidity_2_data->GetXaxis()->SetTitle("Rapidity 2");
     h_Rapidity_2_data->GetYaxis()->SetTitle("Entries");
     h_Rapidity_2_data->SetLineWidth(2);
     h_Rapidity_2->SetLineWidth(2);
    h_Rapidity_2->SetLineColor(2);
     h_Rapidity_2_data->SetLineColor(1);
     h_Rapidity_2->Scale(h_Rapidity_2_data->Integral()/h_Rapidity_2->Integral());
  //h_Rapidity_2->Scale(2.48);
    // h_Rapidity_2->GetXaxis()->SetLabelSize(0.035);
     h_Rapidity_2_data->GetXaxis()->SetLabelSize(0.035);
     h_Rapidity_2_data->Draw("e");
    h_Rapidity_2->Draw("same HIST");
     paveCMS ->Draw("same"); 
     paveCMS3->Draw("same");
     leg2->Draw();
     pad124r->cd(); 
   TPad *pad1009ar = new TPad("pad1009ar","pad1009ar",0,0.02,1,0.4); 
    pad1009ar->SetTopMargin(0);
    pad1009ar->Draw();
    pad1009ar->cd();
hr_Rapidity_2->GetXaxis()->SetTitle("Rapidity 2");
    hr_Rapidity_2->Divide(h_Rapidity_2_data,h_Rapidity_2);//inversion for cemf>0.8
        cout << " OK? mjj " << endl;
    hr_Rapidity_2->GetYaxis()->SetRangeUser(0.,2.0);
    hr_Rapidity_2->Draw("e");
    pad124r->cd();



TCanvas *pad126r = new TCanvas("pad126r","example",600,1020);
    TPad *pad127r = new TPad("pad127r","pad127r",0,0.4,1,1); 
    pad127r->SetBottomMargin(0);
    pad127r->Draw();
    pad127r->cd();
    pad127r->cd()->SetLogy(1);
//pad126r->cd()->SetLogy(1);
     h_ETA_2_data->GetXaxis()->SetTitle("ETA 2");
     h_ETA_2_data->GetYaxis()->SetTitle("Entries");
     h_ETA_2_data->SetLineWidth(2);
     h_ETA_2->SetLineWidth(2);
    h_ETA_2->SetLineColor(2);
     h_ETA_2_data->SetLineColor(1);
     h_ETA_2->Scale(h_ETA_2_data->Integral()/h_ETA_2->Integral());
  //h_ETA_2->Scale(2.48);
    // h_ETA_2->GetXaxis()->SetLabelSize(0.035);
     h_ETA_2_data->GetXaxis()->SetLabelSize(0.035);
     h_ETA_2_data->Draw("e");
    h_ETA_2->Draw("same HIST");
     paveCMS ->Draw("same"); 
     paveCMS3->Draw("same");
     leg2->Draw();
     pad126r->cd(); 
    TPad *pad1010ar = new TPad("pad1010ar","pad1010ar",0,0.02,1,0.4); 
    pad1010ar->SetTopMargin(0);
    pad1010ar->Draw();
    pad1010ar->cd();
hr_ETA_2->GetXaxis()->SetTitle("Eta2");
    hr_ETA_2->Divide(h_ETA_2_data,h_ETA_2);//inversion for cemf>0.8
        cout << " OK? mjj " << endl;
    hr_ETA_2->GetYaxis()->SetRangeUser(0.,2.0);
    hr_ETA_2->Draw("e");
    pad126r->cd();



TCanvas *pad128r = new TCanvas("pad128r","example",600,1020);
    TPad *pad129r = new TPad("pad129r","pad129r",0,0.4,1,1); 
    pad129r->SetBottomMargin(0);
    pad129r->Draw();
    pad129r->cd();
    pad129r->cd()->SetLogy(1);
//pad128r->cd()->SetLogy(1);
     h_ETA_1_data->GetXaxis()->SetTitle("ETA 1");
     h_ETA_1_data->GetYaxis()->SetTitle("Entries");
     h_ETA_1_data->SetLineWidth(2);
     h_ETA_1->SetLineWidth(2);
    h_ETA_1->SetLineColor(2);
     h_ETA_1_data->SetLineColor(1);
    h_ETA_1->Scale(h_ETA_1_data->Integral()/h_ETA_1->Integral());
  //h_ETA_1->Scale(2.48);
    // h_ETA_1->GetXaxis()->SetLabelSize(0.035);
     h_ETA_1_data->GetXaxis()->SetLabelSize(0.035);
     h_ETA_1_data->Draw("e");
   h_ETA_1->Draw("same HIST");
     paveCMS ->Draw("same"); 
     paveCMS3->Draw("same");
     leg2->Draw();
  pad128r->cd(); 
    TPad *pad1000ar = new TPad("pad1000ar","pad1000ar",0,0.02,1,0.4); 
    pad1000ar->SetTopMargin(0);
    pad1000ar->Draw();
    pad1000ar->cd();
hr_ETA_1->GetXaxis()->SetTitle("Eta1");
    hr_ETA_1->Divide(h_ETA_1_data,h_ETA_1);//inversion for cemf>0.8
        cout << " OK? mjj " << endl;
    hr_ETA_1->GetYaxis()->SetRangeUser(0.,2.0);
    hr_ETA_1->Draw("e");
    pad128r->cd();



 TCanvas *pad104r = new TCanvas("pad104r","example",600,1040);
    TPad *pad105r = new TPad("pad105r","pad105r",0,0.4,1,1); 
    pad105r->SetBottomMargin(0);
    pad105r->Draw();
    pad105r->cd();
    pad105r->cd()->SetLogy(1);
pad105r->cd()->SetLogy(1);
     h_DeltaRAK4_First_data->GetXaxis()->SetTitle("#Delta R First");
     h_DeltaRAK4_First_data->GetYaxis()->SetTitle("Entries");
     h_DeltaRAK4_First_data->SetLineWidth(2);
     h_DeltaRAK4_First->SetLineWidth(2);
    h_DeltaRAK4_First->SetLineColor(2);
     h_DeltaRAK4_First_data->SetLineColor(1);
   h_DeltaRAK4_First->Scale(h_DeltaRAK4_First_data->Integral()/h_DeltaRAK4_First->Integral());
  //h_DeltaRAK4_First->Scale(2.48);
    // h_DeltaRAK4_First->GetXaxis()->SetLabelSize(0.035);
     h_DeltaRAK4_First_data->GetXaxis()->SetLabelSize(0.035);
     h_DeltaRAK4_First_data->Draw("e");
    h_DeltaRAK4_First->Draw("same HIST");
     paveCMS ->Draw("same"); 
     paveCMS3->Draw("same");
     leg2->Draw();
     pad104r->cd(); 
    TPad *pad1001ar = new TPad("pad1001ar","pad1001ar",0,0.02,1,0.4); 
    pad1001ar->SetTopMargin(0);
    pad1001ar->Draw();
    pad1001ar->cd();
 hr_DeltaRAK4_First->GetXaxis()->SetTitle("#Delta R First");
    hr_DeltaRAK4_First->Divide(h_DeltaRAK4_First_data,h_DeltaRAK4_First);//inversion for cemf>0.8
        cout << " OK? mjj " << endl;
    hr_DeltaRAK4_First->GetYaxis()->SetRangeUser(0.,2.0);
    hr_DeltaRAK4_First->Draw("e");
    pad104r->cd();






 TCanvas *pad106r = new TCanvas("pad106r","example",600,1060);
    TPad *pad107r = new TPad("pad107r","pad107r",0,0.4,1,1); 
    pad107r->SetBottomMargin(0);
    pad107r->Draw();
    pad107r->cd();
    pad107r->cd()->SetLogy(1);
pad107r->cd()->SetLogy(1);
     h_DeltaRAK4_Second_data->GetXaxis()->SetTitle("#Delta #Phi");
     h_DeltaRAK4_Second_data->GetYaxis()->SetTitle("Entries");
     h_DeltaRAK4_Second_data->SetLineWidth(2);
     h_DeltaRAK4_Second->SetLineWidth(2);
    h_DeltaRAK4_Second->SetLineColor(2);
     h_DeltaRAK4_Second_data->SetLineColor(1);
    h_DeltaRAK4_Second->Scale(h_DeltaRAK4_Second_data->Integral()/h_DeltaRAK4_Second->Integral());
  //h_DeltaRAK4_Second->Scale(2.48);
    // h_DeltaRAK4_Second->GetXaxis()->SetLabelSize(0.035);
     h_DeltaRAK4_Second_data->GetXaxis()->SetLabelSize(0.035);
     h_DeltaRAK4_Second_data->Draw("e");
    h_DeltaRAK4_Second->Draw("same HIST");
     paveCMS ->Draw("same"); 
     paveCMS3->Draw("same");
     leg2->Draw();
     pad106r->cd(); 
    TPad *pad1002ar = new TPad("pad1002ar","pad1002ar",0,0.02,1,0.4); 
    pad1002ar->SetTopMargin(0);
    pad1002ar->Draw();
    pad1002ar->cd();
hr_DeltaRAK4_Second->GetXaxis()->SetTitle("#Delta R Second");
    hr_DeltaRAK4_Second->Divide(h_DeltaRAK4_Second_data,h_DeltaRAK4_Second);//inversion for cemf>0.8
        cout << " OK? mjj " << endl;
    hr_DeltaRAK4_Second->GetYaxis()->SetRangeUser(0.,2.0);
    hr_DeltaRAK4_Second->Draw("e");
    pad106r->cd();



*/


//
/*
     TCanvas *pad0 = new TCanvas("pad0", "",1);
     pad0->cd();
     pad0->cd()->SetLogy(1);
     h_assym->GetXaxis()->SetTitle("(p_{T}^{1}-p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
     h_assym->GetYaxis()->SetTitle("Entries");
h_assym->GetYaxis()->SetRangeUser(0.,10000000.);
     h_assym->SetLineWidth(2);
     h_assym->SetLineWidth(2);
     h_assym_data->SetLineColor(1);
     h_assym->SetLineColor(2);
     h_assym->Scale(h_assym_data->Integral()/h_assym->Integral());
     h_assym->Draw();
     h_assym_data->Draw("same e");
     paveCMS ->Draw("same");
     paveCMS3->Draw("same");
     leg1->Draw();*/

//

   /*  TCanvas *pad1 = new TCanvas("pad1", "",1);
     pad1->cd();
     pad1->cd()->SetLogy(1);
     h_CHFJet1->GetXaxis()->SetTitle("CHF leading jets");
     h_CHFJet1->GetYaxis()->SetTitle("Entries");
 //h_CHFJet1->GetYaxis()->SetRangeUser(0.,10000000.);
     h_CHFJet1->SetLineWidth(2);
     h_CHFJet1->SetLineWidth(2);
     h_CHFJet1_data->SetLineColor(1);
     h_CHFJet1->SetLineColor(2);
     h_CHFJet1->Scale(h_CHFJet1_data->Integral()/h_CHFJet1->Integral());
      h_CHFJet1->Draw();
     h_CHFJet1_data->Draw("same e");
     paveCMS ->Draw("same");
     paveCMS7->Draw("same");
     leg1->Draw();
//
     TCanvas *pad2 = new TCanvas("pad2", "",1);
     pad2->cd();
     pad2->cd()->SetLogy(1);
     h_NHFJet1->GetXaxis()->SetTitle("NHF leading jets");
     h_NHFJet1->GetYaxis()->SetTitle("Entries");
     h_NHFJet1->SetLineWidth(2);
     h_NHFJet1->SetLineWidth(2);
     h_NHFJet1_data->SetLineColor(1);
     h_NHFJet1->SetLineColor(2);
     h_NHFJet1->Scale(h_NHFJet1_data->Integral()/h_NHFJet1->Integral());
     h_NHFJet1->Draw();
     h_NHFJet1_data->Draw("same e");
     paveCMS ->Draw("same");
     paveCMS2->Draw("same");
     leg2->Draw();
//  
     TCanvas *pad3 = new TCanvas("pad3", "",1);
     pad3->cd();
     pad3->cd()->SetLogy(1);
     h_CEMFJet1->GetXaxis()->SetTitle("CEMF leading jets");
     h_CEMFJet1->GetYaxis()->SetTitle("Entries");
     h_CEMFJet1->SetLineWidth(2);
     h_CEMFJet1->SetLineWidth(2);
     h_CEMFJet1_data->SetLineColor(1);
     h_CEMFJet1->SetLineColor(2);
     h_CEMFJet1->Scale(h_CEMFJet1_data->Integral()/h_CEMFJet1->Integral());
     h_CEMFJet1->Draw();
     h_CEMFJet1_data->Draw("same e");
     paveCMS ->Draw("same");
     paveCMS2->Draw("same");
     leg2->Draw();
//
     TCanvas *pad4 = new TCanvas("pad4", "",1);
     pad4->cd();
     pad4->cd()->SetLogy(1);
     h_NEMFJet1->GetXaxis()->SetTitle("NEMF leading jets");
     h_NEMFJet1->GetYaxis()->SetTitle("Entries");
     h_NEMFJet1->SetLineWidth(2);
     h_NEMFJet1->SetLineWidth(2);
     h_NEMFJet1_data->SetLineColor(1);
     h_NEMFJet1->SetLineColor(2);
    h_NEMFJet1->Scale(h_NEMFJet1_data->Integral()/h_NEMFJet1->Integral());
     h_NEMFJet1->Draw();
     h_NEMFJet1_data->Draw("same e");
     paveCMS ->Draw("same");
     paveCMS3->Draw("same");
     leg2->Draw();
 // 
     TCanvas *pad5 = new TCanvas("pad5", "",1);
     pad5->cd();
     pad5->cd()->SetLogy(1);
     h_MUFJet1->GetXaxis()->SetTitle("MUF leading jets");
     h_MUFJet1->GetYaxis()->SetTitle("Entries");
     h_MUFJet1->SetLineWidth(2);
     h_MUFJet1->SetLineWidth(2);
     h_MUFJet1_data->SetLineColor(1);
     h_MUFJet1->SetLineColor(2);
    h_MUFJet1->Scale(h_MUFJet1_data->Integral()/h_MUFJet1->Integral());
     h_MUFJet1->Draw();
     h_MUFJet1_data->Draw("same e");
     paveCMS ->Draw("same");
     paveCMS2->Draw("same");
     leg2->Draw();
//
 

     TCanvas *pad10 = new TCanvas("pad10", "",1);
     pad10->cd();
     pad10->cd()->SetLogy(1);
     h_etaJet1_dataAK4->GetXaxis()->SetTitle("#eta leading jets AK4");
     h_etaJet1_dataAK4->GetYaxis()->SetTitle("Entries");
     h_etaJet1_dataAK4->SetLineWidth(2);
     h_etaJet1_dataAK4->SetLineWidth(2);
     h_etaJet1_dataAK4->SetLineColor(1);
     h_etaJet1AK4->SetLineColor(2);
    h_etaJet1AK4->Scale(h_etaJet1_dataAK4->Integral()/h_etaJet1AK4->Integral());
     h_etaJet1_dataAK4->Draw("e");
     h_etaJet1AK4->Draw("same");
     paveCMS ->Draw("same");
     paveCMS4->Draw("same");
     leg2->Draw();

     TCanvas *pad11 = new TCanvas("pad11", "",1);
     pad11->cd();
     pad11->cd()->SetLogy(1);
     h_phiJet1_dataAK4->GetXaxis()->SetTitle("#phi leading jets AK4");
     h_phiJet1_dataAK4->GetYaxis()->SetTitle("Entries");
     h_phiJet1_dataAK4->SetLineWidth(2);
     h_phiJet1_dataAK4->SetLineWidth(2);
     h_phiJet1_dataAK4->SetLineColor(1);
     h_phiJet1AK4->SetLineColor(2);
    h_phiJet1AK4->Scale(h_phiJet1_dataAK4->Integral()/h_phiJet1AK4->Integral());
     h_phiJet1_dataAK4->Draw("e");
     h_phiJet1AK4->Draw("same");
     paveCMS ->Draw("same");
     paveCMS2->Draw("same");
     leg2->Draw();

   TCanvas *pad24 = new TCanvas("pad24", "",1);
     pad24->cd();
     pad24->cd()->SetLogy(1);
     h_CMJet1->GetXaxis()->SetTitle("CM leading jets");
     h_CMJet1->GetYaxis()->SetTitle("Entries");
     h_CMJet1->SetLineWidth(2);
     h_CMJet1->SetLineWidth(2);
     h_CMJet1_data->SetLineColor(1);
     h_CMJet1->SetLineColor(2);
    h_CMJet1->Scale(h_CMJet1_data->Integral()/h_CMJet1->Integral());
     h_CMJet1->Draw();
     h_CMJet1_data->Draw("same e");
     paveCMS ->Draw("same");
     paveCMS3->Draw("same");
     leg2->Draw();

     TCanvas *pad25 = new TCanvas("pad25", "",1);
     pad25->cd();
     pad25->cd()->SetLogy(1);
     h_NMJet1->GetXaxis()->SetTitle("NM leading jets");
     h_NMJet1->GetYaxis()->SetTitle("Entries");
     h_NMJet1->SetLineWidth(2);
     h_NMJet1->SetLineWidth(2);
     h_NMJet1_data->SetLineColor(1);
     h_NMJet1->SetLineColor(2);
  h_NMJet1->Scale(h_NMJet1_data->Integral()/h_NMJet1->Integral());
     h_NMJet1->Draw();
     h_NMJet1_data->Draw("same e");
     paveCMS ->Draw("same");
     paveCMS3->Draw("same");
     leg2->Draw();

     TCanvas *pad26 = new TCanvas("pad26", "",1);
     pad26->cd();
     pad26->cd()->SetLogy(1);
     h_PMJet1->GetXaxis()->SetTitle("PM leading jets");
     h_PMJet1->GetYaxis()->SetTitle("Entries");
     h_PMJet1->SetLineWidth(2);
     h_PMJet1->SetLineWidth(2);
     h_PMJet1_data->SetLineColor(1);
     h_PMJet1->SetLineColor(2);
     h_PMJet1->Scale(h_PMJet1_data->Integral()/h_PMJet1->Integral());
     h_PMJet1->Draw();
     h_PMJet1_data->Draw("same e");
     paveCMS ->Draw("same");
     paveCMS3->Draw("same");
     leg2->Draw();



   TCanvas *pad150 = new TCanvas("pad150", "",1);
     pad150->cd();
     h_etaphiJet1WJ->GetXaxis()->SetTitle("#eta vs #phi of Wide Jets (Simulation)");
     h_etaphiJet1WJ->SetYTitle("#phi");
     h_etaphiJet1WJ->SetXTitle("#eta");
     h_etaphiJet1WJ->Draw("colz");
     leg3->Draw();  
     TCanvas *pad151 = new TCanvas("pad151", "",1);
     pad151->cd();
     h_etaphiJet1WJ_data->GetXaxis()->SetTitle("#eta vs #phi of Wide Jets (data)");
     h_etaphiJet1WJ_data->SetYTitle("#phi");
     h_etaphiJet1WJ_data->SetXTitle("#eta");
     h_etaphiJet1WJ_data->Draw("colz");
     leg4->Draw();
*/







TCanvas *pad67 = new TCanvas("pad67", "",1);
pad67->cd()->SetRightMargin(0.18);
pad67->cd()->SetLogz(1);
h_M2J_vs_alpha_data->GetXaxis()->SetTitle("4J vs 2J");
h_M2J_vs_alpha_data->GetXaxis()->SetRangeUser(0.05,0.45);
h_M2J_vs_alpha_data->GetYaxis()->SetRangeUser(0.,3000.);
//h_M2J_vs_alpha_data->GetZaxis()->SetRangeUser(0.,1200);
h_M2J_vs_alpha_data->SetMinimum(0.0001);
//h_M2J_vs_alpha_data->GetZaxis()->SetRangeUser(0.,13057178);
//h_M2J_vs_alpha_data->SetMaximum(13057178);
h_M2J_vs_alpha_data->SetYTitle("Average Dijet Mass [GeV]");
h_M2J_vs_alpha_data->SetXTitle("#alpha");
h_M2J_vs_alpha_data->Draw("colz");
leg4->Draw("same");
paveCMS->Draw("same");







 

  

 pad67->SaveAs("example.png");
 pad67->SaveAs("example.pdf");


 
