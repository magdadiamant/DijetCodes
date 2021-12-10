

#include <iostream>
#include <fstream>

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
#include "TSystem.h"
#include "TROOT.h"
#include "TLatex.h"

void fisher_Dim()


{
  double chisquare2 = 1637. ;
  double chisquare3 =14.4;
  double chisquare4 = 14.8;
  double chisquare5 = 42.4;
  double chisquare6 = 42.0519;
  double chisquare7 = 42.9576;
 
 /* double RSS3 = 520622 ;
  double RSS4 = 408632 ;
//  double RSS3 = 20881.2 ;
//  double RSS4 = 16246.6   ;


 
  double RSS5 = 377520;
  double RSS6 = 353322;
  double RSS7 = 361130;*/

  
   
   
  double upper_limit = 1e4;
 
  int N = 44 ; // number of bins
 // int N = 31 ; // number of bins



  double p32, p43, p54, p65, p76 ; 
  double ptilde43, ptilde54, ptilde65, ptilde76 ; 
 
  double p53;

  double F32 = (chisquare2 - chisquare3)*(N-3)/(chisquare3);
  double F43 = (chisquare3 - chisquare4)*(N-4)/(chisquare4);
  double F54 = (chisquare4 - chisquare5)*(N-5)/(chisquare5);
  double F65 = (chisquare5 - chisquare6)*(N-6)/(chisquare6);
  double F76 = (chisquare6 - chisquare7)*(N-7)/(chisquare7);

  double F53 = ((chisquare3 - chisquare5)/(2.0))/((chisquare5)/(N-5));

 /* double Ftilde43 = (RSS3 - RSS4)*(N-4)/(RSS4);
  double Ftilde54 = (RSS4 - RSS5)*(N-5)/(RSS5);
  double Ftilde65 = (RSS5 - RSS6)*(N-6)/(RSS6);
  double Ftilde76 = (RSS6 - RSS7)*(N-7)/(RSS7);*/

 TF1 *f32 = new TF1("f32","ROOT::Math::fdistribution_pdf(x,1,42)",0,upper_limit);
 TF1 *f43 = new TF1("f43","ROOT::Math::fdistribution_pdf(x,1,41)",0,upper_limit);
 TF1 *f54 = new TF1("f54","ROOT::Math::fdistribution_pdf(x,1,40)",0,upper_limit);
 TF1 *f65 = new TF1("f65","ROOT::Math::fdistribution_pdf(x,1,39)",0,upper_limit);
 TF1 *f76 = new TF1("f76","ROOT::Math::fdistribution_pdf(x,1,34)",0,upper_limit);
 
 TF1 *f53 = new TF1("f53","ROOT::Math::fdistribution_pdf(x,2,36)",0,upper_limit);
 
 /*TF1 *ftilde43 = new TF1("ftilde43","ROOT::Math::fdistribution_pdf(x,1,37)",0,upper_limit);
 // TF1 *ftilde43 = new TF1("ftilde43","ROOT::Math::fdistribution_pdf(x,1,27)",0,upper_limit);
 TF1 *ftilde54 = new TF1("ftilde54","ROOT::Math::fdistribution_pdf(x,1,36)",0,upper_limit);
 TF1 *ftilde65 = new TF1("ftilde65","ROOT::Math::fdistribution_pdf(x,1,35)",0,upper_limit);
 TF1 *ftilde76 = new TF1("ftilde76","ROOT::Math::fdistribution_pdf(x,1,34)",0,upper_limit);*/
 
 p43 = f43 -> Integral(F43,upper_limit);
 p54 = f54 -> Integral(F54,upper_limit);
 p65 = f65 -> Integral(F65,upper_limit);
 p76 = f76 -> Integral(F76,upper_limit);

 p53 = f53 -> Integral(F53,upper_limit);

/* ptilde43 = ftilde43 -> Integral(Ftilde43,upper_limit);
 ptilde54 = ftilde54 -> Integral(Ftilde54,upper_limit);
 ptilde65 = ftilde65 -> Integral(Ftilde65,upper_limit);
 ptilde76 = ftilde76 -> Integral(Ftilde76,upper_limit);*/



cout << " =============== Chi square test ============= " << endl;


cout << " F32 = " << F32 << " p32 =  " << p32 << endl;
cout << " F43 = " << F43 << " p43 =  " << p43 << endl;
cout << " F54 = " << F54 << " p54 =  " << p54 << endl;
cout << " F65 = " << F65 << " p65 =  " << p65 << endl;
cout << " F76 = " << F76 << " p76 =  " << p76 << endl;

cout << " F53 = " << F53 << " p53 =  " << p53 << endl;

/*cout << " =============== RSS test ============= " << endl;

cout << " Ftilde43 = " << Ftilde43 << " ptilde43 =  " << ptilde43 << endl;
cout << " Ftilde54 = " << Ftilde54 << " ptilde54 =  " << ptilde54 << endl;
cout << " Ftilde65 = " << Ftilde65 << " ptilde65 =  " << ptilde65 << endl;
cout << " Ftilde76 = " << Ftilde76 << " ptilde76 =  " << ptilde76 << endl;*/

/*


TCanvas *c1 = new TCanvas();
c1 -> Divide(2,2);
c1 -> cd(1);
f43->SetRange(0,10);
f43 -> SetTitle("F-distribution for F43;F;a.u.");
f43 -> Draw();
TLine *l43 = new TLine(F43,0,F43,1.8);
l43 -> SetLineColor(kGreen);
l43 -> Draw("same");

c1 -> cd(2);
f54->SetRange(0,10);
f54 -> SetTitle("F-distribution for F54;F;a.u.");
f54 -> Draw();
TLine *l54 = new TLine(F54,0,F54,1.8);
l54 -> SetLineColor(kGreen);
l54 -> Draw("same");

c1 -> cd(3);
f65->SetRange(0,10);
f65 -> SetTitle("F-distribution for F65;F;a.u.");
f65 -> Draw();
TLine *l65 = new TLine(F65,0,F65,1.8);
l65 -> SetLineColor(kGreen);
l65 -> Draw("same");

c1 -> cd(4);
f76->SetRange(0,10);
f76 -> SetTitle("F-distribution for F76;F;a.u.");
f76 -> Draw();
TLine *l76 = new TLine(F76,0,F76,1.8);
l76 -> SetLineColor(kGreen);
l76 -> Draw("same");

TCanvas *c2 = new TCanvas();
c2 -> cd();
f53->SetRange(0,10);
f53 -> SetTitle("F-distribution for F53;F;a.u.");
f53 -> Draw();
TLine *l53 = new TLine(F53,0,F53,1);
l53 -> SetLineColor(kGreen);
l53 -> Draw("same");
*/
  
  
}  //  This is the end / Beautiful friend 
