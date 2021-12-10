#include <iostream>
#include <fstream>

 // INPUTS WITH BRIEF EXPLANATIONS 
 // MODE      : 0 IS Clopper Pearson ,  1 is Gaussian
 // PF        : 1 DO PF JETS, 0 DO CALO JETS
 // itr       : trigger index 0 to 4 
// ***************************************************//


void trig_2017_4J_alpha( int PF, int alphabin)
{
   LoadStyle();

   //MODE = 1;
   PF   = 1;
  // itr  = 1;//trigger index 0 to 4

  // int hlt[4] = {400,450,500,550};
  // int ref[5] = {40,80,140,200,260};


   TString jet;
   if(PF == 1) jet = "pf";
   else jet = "calo";

  
 TPaveText *paveCMS = new TPaveText(0.14,0.91,0.96,0.94,"NDC");
 paveCMS->AddText(" #bf{CMS} #it{Preliminary}      2017 Data         (13 TeV)");
 paveCMS->SetFillColor(0);
 paveCMS->SetBorderSize(0);
 paveCMS->SetTextSize(0.04);


 TPaveText *paveCMS2 = new TPaveText(0.45,0.55,0.65,0.65,"NDC");
// paveCMS2->AddText("|#eta| < 2.5" );
// paveCMS2->AddText("1.5<|#Delta #eta| < 2.6");
 //paveCMS2->AddText("M_{jj} > 2438 GeV");
 paveCMS2->SetFillColor(0);
 paveCMS2->SetBorderSize(0);
 paveCMS2->SetTextSize(0.04);
   

   double scale(1.),prescale(1.);

   TString FileOut;
   TString FileOutText;
  
   TH1F *h[2];
TH1F *h_all[2];
TH1F *h_JetHT[2];
TH1F* h_JetHT/new/JetHT_all[2];



   int rebin(1);
  
   // FIT RANGES  // CHANGE IF NECESSARY 
   double minFit,maxFit,minDraw,maxDraw; 
  
   char name[1000];

   gROOT->ForceStyle();


   sprintf(name,"2018Bv2v3_PFHT1050");
   TFile *outf = new TFile(name+TString(".root"),"RECREATE");

   ofstream textfile;
   textfile.open(name+TString(".dat"));
 
  // Int_t iv_start=3;
   //if(itr==0) iv_start=5;

   //for(int ibiny=0;ibiny<5;ibiny++)
  // {//loop over y

     // for(int iv=iv_start;iv<=8;iv++)
     // {
    








 for(int fl=0; fl<7; fl++){



 
 

 
   
   if(fl==0){
       TFile *f = TFile::Open("root://eoscms//eos/cms/store/group/phys_jetmet/magda/Trigger_2016_4Jets/SingleMuon/SingleMuon__Run2016B-07Aug2017_JECV11_merged_reduced_skim.root","READ");
       assert(f && !f->IsZombie());
       
       TFile *ft = TFile::Open("root://eoscms////eos/cms/store/group/phys_jetmet/magda/Trigger_2016_4Jets/JetHT__Run2016B-07Aug2017_JECV11_merged_reduced_skim.root","READ");
       assert(ft && !ft->IsZombie());


 
}



   
   if(fl==1){
       TFile *f = TFile::Open("root://eoscms//eos/cms/store/group/phys_jetmet/magda/Trigger_2016_4Jets/SingleMuon/SingleMuon__Run2016C-07Aug2017_JECV11_merged_reduced_skim.root","READ");
       assert(f && !f->IsZombie());
       
       TFile *ft = TFile::Open("root://eoscms////eos/cms/store/group/phys_jetmet/magda/Trigger_2016_4Jets/JetHT__Run2016C-07Aug2017_JECV11_merged_reduced_skim.root","READ");
       assert(ft && !ft->IsZombie());


 
}


   
   if(fl==2){
       TFile *f = TFile::Open("root://eoscms//eos/cms/store/group/phys_jetmet/magda/Trigger_2016_4Jets/SingleMuon/SingleMuon__Run2016D-07Aug2017_JECV11_merged_reduced_skim.root","READ");
       assert(f && !f->IsZombie());
       
       TFile *ft = TFile::Open("root://eoscms////eos/cms/store/group/phys_jetmet/magda/Trigger_2016_4Jets/JetHT__Run2016D-07Aug2017_JECV11_merged_reduced_skim.root","READ");
       assert(ft && !ft->IsZombie());


 
}


   
   if(fl==3){
       TFile *f = TFile::Open("root://eoscms//eos/cms/store/group/phys_jetmet/magda/Trigger_2016_4Jets/SingleMuon/SingleMuon__Run2016E-07Aug2017_JECV11_merged_reduced_skim.root","READ");
       assert(f && !f->IsZombie());
       
       TFile *ft = TFile::Open("root://eoscms////eos/cms/store/group/phys_jetmet/magda/Trigger_2016_4Jets/JetHT__Run2016E-07Aug2017_JECV11_merged_reduced_skim.root","READ");
       assert(ft && !ft->IsZombie());


 
}


   
   if(fl==4){
       TFile *f = TFile::Open("root://eoscms//eos/cms/store/group/phys_jetmet/magda/Trigger_2016_4Jets/SingleMuon/SingleMuon__Run2016F-07Aug2017_JECV11_merged_reduced_skim.root","READ");
       assert(f && !f->IsZombie());
       
       TFile *ft = TFile::Open("root://eoscms////eos/cms/store/group/phys_jetmet/magda/Trigger_2016_4Jets/JetHT__Run2016F-07Aug2017_JECV11_merged_reduced_skim.root","READ");
       assert(ft && !ft->IsZombie());


 
}


   
   if(fl==5){
       TFile *f = TFile::Open("root://eoscms//eos/cms/store/group/phys_jetmet/magda/Trigger_2016_4Jets/SingleMuon/SingleMuon__Run2016G-07Aug2017_JECV11_merged_reduced_skim.root","READ");
       assert(f && !f->IsZombie());
       
       TFile *ft = TFile::Open("root://eoscms////eos/cms/store/group/phys_jetmet/magda/Trigger_2016_4Jets/JetHT__Run2016G-07Aug2017_JECV11_merged_reduced_skim.root","READ");
       assert(ft && !ft->IsZombie());


 
}


   
   if(fl==6){
       TFile *f = TFile::Open("root://eoscms//eos/cms/store/group/phys_jetmet/magda/Trigger_2016_4Jets/SingleMuon/SingleMuon__Run2016H-07Aug2017_JECV11_merged_reduced_skim.root","READ");
       assert(f && !f->IsZombie());
       
       TFile *ft = TFile::Open("root://eoscms////eos/cms/store/group/phys_jetmet/magda/Trigger_2016_4Jets/JetHT__Run2016H-07Aug2017_JECV11_merged_reduced_skim.root","READ");
       assert(ft && !ft->IsZombie());


 
}

}


 



      	 sprintf(name,"h_mjj_HLTpass_dR2_alpha%d_Mu45",alphabin);//ref
         h[0] = (TH1F*)f->Get(name);
if(fl==0){ h_all[0]= (TH1F*)f->Get(name);}      	

      	 sprintf(name,"h_mjj_HLTpass_dR2_alpha%d_Mu45_AllJet",alphabin);
      	h[1] = (TH1F*)f->Get(name);
if(fl==0){ h_all[1]= (TH1F*)f->Get(name);}

sprintf(name,"h_mjj_HLTpass_dR2_alpha%d_AllJet",alphabin);
h_JetHT[0]= (TH1F*)ft->Get(name);
if(fl==0){h_JetHT_all[0] = (TH1F*)ft->Get(name);}



//TFile *fe = TFile::Open("/afs/cern.ch/work/m/mdiamant/private/Trigger_Studies/final_scripts/Re-reco/JEC2017/2017CCDEF_17Nov2017-v1_PFHT1050_usingPFHT1050.root","READ");

//sprintf(name,"TrigEff_PFHT1050");
//h_PFHT1050_Run2017C = (TH1F*)fe->Get(name);
      	 
      if(fl>0)
{

h_all[0]->Add(h[0]);
h_all[1]->Add(h[1]);
h_JetHT_all[0]->Add(h_JetHT[0]);
} //end of if
}//end of fl loop
     // }
  
   //return;


////////////////////////////////////////
  double a  = 0.3173;
  double vx[1000],vy[1000],vexl[1000],vexh[1000],veyl[1000],veyh[1000];
  for(int i=0;i<h_all[0]->GetNbinsX();i++)
    {
      double N1 = h_all[0]->GetBinContent(i+1);
      double N2 = h_all[1]->GetBinContent(i+1);
      double p  = 0;
      double eU = 0;
      double eL = 0;
      double aeff = (1-a)/2;
      double n,w;
      if (N1 > 0)
        { 
          p = N2/N1;
          n = N1+N2;
          w = N2/n;
         // if (MODE==0) // Clopper-Pearson for binomial
              

//cout<<" pass1 "<<endl;
              scale = 1.0; // makes sense only for the unprescaled trigger 
              if (N1*p>100 || N1*(1-p)>100)
                { //cout<< " pass " <<endl;
                  eU = sqrt(p*(1-p)/N1);
                  eL = sqrt(p*(1-p)/N1);
                }
              else
                {   //cout<<" pass2 "<<endl;
                  eU = (1-BetaInverse(aeff,N1-N2,N2+1))-p;
                  eL = p-(1-BetaInverse(1-aeff,N1-N2+1,N2));  
                }
         
          
        }


cout <<" i "<<h_all[0]->GetXaxis()->GetBinCenter(i+1)<<" numerator "<<N2<<" denominator "<<N1<<" efficiency "<<p<<" errorL "<<eL<<" errorU "<<eU<<endl;
     // cout <<i<<" i "<<N1<<"numerator "<<N2<<"denominator "<<p<<" efficiency "<<eL<<" errorL "<<eU<<"errorU "<<endl;

cout<<1-p<<"  inefficiency "<<endl;



      vx[i]   = h_all[0]->GetBinCenter(i+1);
      vy[i]   = p*scale;
      vexl[i] = h_all[0]->GetBinWidth(i+1)/2;
      vexh[i] = h_all[0]->GetBinWidth(i+1)/2;      
      veyl[i] = eL*scale;
      veyh[i] = eU*scale;     
    }


for(int i=0;i<h_JetHT_all[0]->GetNbinsX();i++)
    {

cout<<" For JetHT "<<endl;
      
      double Number_of_events = h_JetHT_all[0]->GetBinContent(i+1);
cout <<h_all[0]->GetXaxis()->GetBinCenter(i+1)<<" "<<Number_of_events<<"  "<<endl;


if(Number_of_events>0)
cout <<1/sqrt(Number_of_events)<<" 1/sqrt(N) "<<endl; 
}
    
  
//cout <<h_all[0]->GetXaxis()->FindBin(40)<<" "<<endl;
  TGraphAsymmErrors *gEff = new TGraphAsymmErrors(i,vx,vy,vexl,vexh,veyl,veyh);
  
  sprintf(name,"test");
  gEff->SetName(name);

 // double yminfit[6], maxf[6];
double yminfit, maxf;

   minFit = FindX(gEff,0.40);
   maxFit = FindX(gEff,0.98);
  maxFit = maxFit * 1.25;  
  // if(itr>2)
//maxFit = maxFit * 2.5;
 if(maxFit>4500) maxFit = 4500;

   cout << " minfit " << minFit << " maxFit " << maxFit << endl;

  minDraw = FindX(gEff,0.01);
  maxDraw = maxFit;
  cout<<"Fit Range: "<<minFit<<" "<<maxFit<<endl;
  ////////////////////////////////////////////////////
  gStyle->SetFillStyle(0);
  gStyle->SetFillColor(0);
  gStyle->SetCanvasDefH(400);
  gStyle->SetCanvasDefW(400);

  sprintf(name,"canvas");
  TCanvas *c = new TCanvas(name,name);

  //c->Divide(2,1);

  c->cd(1);
  
  gPad->SetLogy();
  h_all[0]->GetXaxis()->SetTitle("M' (GeV)");
  h_all[0]->GetYaxis()->SetTitle("Events");
  //h_all[0]->GetXaxis()->SetNdivisions(505);
  h_all[0]->GetXaxis()->SetRangeUser(0.,8000);
  h_all[0]->SetMaximum(10000000.);
  h_JetHT_all[0]->SetLineColor(kRed);
  h_all[0]->Draw("HIST");
  h_JetHT_all[0]->Draw("same HIST");

  c->cd(); 
  ////////////////////////////////////////////////////
  //TCanvas *c1 = new TCanvas("QCDTriggerEffResPF_"+YBIN+"_"+TRIG1+"_"+TRIG2,"QCDTriggerEffResPF_"+YBIN+"_"+TRIG1+"_"+TRIG2);
  TF1 *line = new TF1("line","1.3",minDraw,5000);
  line->SetLineColor(kBlack);
  line->SetLineStyle(2);
  line->GetXaxis()->SetTitle("FourjetMass [ GeV ]");
  line->GetYaxis()->SetTitle("Trigger Efficiency");
  line->GetXaxis()->SetTitleSize(0.05);
  line->GetYaxis()->SetTitleSize(0.05);
//line->GetXaxis()->SetRangeUser(0.,7000);
//  line->GetXaxis()->SetNdivisions(505);
//line->GetXaxis()->SetNdivisions(103);
  line->SetMinimum(0.4);
  line->SetMaximum(1.2); 
  line->SetTitle(" ");
  line->Draw();
  gEff->SetLineColor(kRed+1);  
  gEff->SetMarkerColor(kRed+1);
  gEff->SetMarkerSize(1.5);

//h_PFHT1050_Run2017C->Draw("same e");
//h_PFHT1050_Run2017C->SetLineColor(1);
  gEff->Draw("same e");
  
  sprintf(name,"HLT_PFHT1050");

  TPaveText *pave = new TPaveText(0.45,0.2,0.9,0.45,"NDC");
  //pave->AddText("#sqrt{s} = 13 TeV");
 // pave->AddText(ytitl[ibiny]);
 // pave->AddText(name);
  if(PF==0) pave->AddText("anti-k_{T} R=0.7 Calo Jets");
 // if(PF==1) pave->AddText(" PF Jets");
  pave->SetFillColor(0);
  pave->SetBorderSize(0);
  pave->SetTextFont(42);
  pave->SetTextSize(0.04);
  pave->Draw("same");


 /* TPaveText *paveCMS = new TPaveText(0.55,0.45,0.9,0.55,"NDC");
  paveCMS->AddText("CMS Data (9.2 fb^{-1})");
  paveCMS->SetFillColor(0);
  paveCMS->SetBorderSize(0);

  paveCMS->SetTextSize(0.04);*/  
 // TPaveText *pave1 = new TPaveText(0.5,0.7,0.93,0.8,"NDC");
  //sprintf(name,"M_{jj} = %1.0f GeV/c^{2}",m);
  //pave1->AddText(name);
  /*pave1->SetFillColor(0);
  pave1->SetBorderSize(0);
  pave1->SetTextSize(0.05);
  pave1->SetTextFont(42);
  pave1->SetTextColor(kBlue);
  pave1->Draw();*/
paveCMS->Draw("same");
//paveCMS2->Draw("same");


  //sprintf(name,"Mass_Mu50_vs_JetHT/new/JetHT_PFHT1050_OR_PFHT1050_PFHT1050_AK8PFHT1050");
 //c->cd(1)->Print(TString(name)+TString(".png")); 
 // c->cd(1)->Print(TString(name)+TString("_new.eps")); 

 sprintf(name,"2017C_alpha%d",alphabin);
c->cd()->Print(TString(name)+TString(".png"));
  //c->cd(2)->Print(TString(name)+TString(".eps")); 
 
 // h_JetHT/new/JetHT_all[0]->SetName("h_mjj_HLTpass_M2primeCut_0p9noTrig");
 // h_all[1]->SetName("MassHigh");
  gEff->SetName("TrigEff_PFHT1050");
 
  outf->cd(); 
  //h_JetHT/new/JetHT_all[0]->Write();
  h_all[0]->Write();
  gEff->Write();
  //fit->Write();
  
 //}//loop over y
  outf->Close();
  textfile.close();
}
//////////////////////////////////////////////////
double FindX(TGraphAsymmErrors *g, double Z)
{
  double result(0.0);
  double x,y;
  double safe_low_lim;
  safe_low_lim=150;
 // if(itr>1)  
//safe_low_lim=400;
  for(int i=0;i<g->GetN();i++)
    {
      g->GetPoint(i,x,y); 
      if (y > Z && x > safe_low_lim) // avoid low mass crazy points !!

        return x;
    } 
  return result;
}
//////////////////////////////////////////////////
double BetaInverse(double x,double p, double q)
{
  double result(0.0);
  double dy = 0.001;
  double eMin = 100;
  for(int i=0;i<1000;i++)
    {
      double y = i*dy;
      double e = fabs(TMath::BetaIncomplete(y,p,q)-x);
      if (e<eMin)
        {
          eMin = e;
          result = y;
        }
    }
  return result; 
}
//////////////////////////////////////////////////////////////////////////////
void LoadStyle()
{
   //gROOT->Reset();

   gStyle->SetPalette(1);
   gStyle->SetPaperSize(21,28);

   gStyle->SetPadColor(10);
   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);
   gStyle->SetPadGridX(0);
   gStyle->SetPadGridY(0);
 
   gStyle->SetFillColor(10);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetCanvasBorderSize(0);
   gStyle->SetCanvasColor(10);
   
   //gStyle->SetHistFillColor(2);
   //gStyle->SetHistFillStyle(1001);//solid
   //gStyle->SetHistFillStyle(3004);//nice hatch style
     
   //gStyle->SetFrameFillColor(10);
   gStyle->SetFrameFillColor(18);
   gStyle->SetFrameLineWidth(1.5);
   

   gStyle->SetLegendBorderSize(0);   

   gStyle->SetStatColor(10);   
   gStyle->SetStatBorderSize(1);   
   //gStyle->SetOptStat(1111111);
   gStyle->SetOptStat(0);
   //gStyle->SetStatX(0.87);   
   //gStyle->SetStatY(0.87);   
   gStyle->SetStatX(0.9);   
   gStyle->SetStatY(0.985);   
   gStyle->SetStatW(0.19);   
   gStyle->SetStatH(0.1);   

   gStyle->SetTitleX(0.05);   
   gStyle->SetTitleY(0.985);   
   //gStyle->SetTitleW(0.2);   
   //gStyle->SetTitleH(0.09);   
   gStyle->SetTitleFillColor(10);
   gStyle->SetTitleBorderSize(0);
   //gStyle->SetOptTitle(0);

   //gStyle->SetTitleSize(0.09,"yz");
   //gStyle->SetTitleSize(0.09,"x");
   //gStyle->SetTitleOffset(0.53,"x");
   //gStyle->SetTitleOffset(0.6,"y");

   //gStyle->SetLabelSize(0.06,"X");
   //gStyle->SetLabelSize(0.05,"Y");
   //gStyle->SetLabelSize(0.05,"Z");
   //gStyle->SetLabelOffset(0.01,"X");
   //gStyle->SetLabelOffset(0.01,"Y");

   gStyle->SetLabelSize(0.04,"X");
   gStyle->SetLabelSize(0.04,"Y");
   gStyle->SetLabelSize(0.03,"Z");

   //gStyle->SetMarkerColor(2);
   //gStyle->SetMarkerSize(3);
   gROOT->ForceStyle();   
   
   gStyle->SetLabelFont(42,"xyz");
   gStyle->SetTitleFont(42);
   gStyle->SetTitleFont(42,"xyz");
   gStyle->SetStatFont(42);
   gStyle->SetFrameFillColor(10);
   gROOT->ForceStyle();
}
//////////////////////////////////////////////////////////////////////////////
