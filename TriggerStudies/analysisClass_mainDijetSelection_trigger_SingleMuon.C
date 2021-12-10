#define analysisClass_cxx
#include "analysisClass.h"
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TVector2.h>
#include <TVector3.h>



analysisClass::analysisClass(string * inputList, string * cutFile, string * treeName, string * outputFileName, string * cutEfficFile)
  :baseClass(inputList, cutFile, treeName, outputFileName, cutEfficFile)
{
  std::cout << "analysisClass::analysisClass(): begins " << std::endl;

  std::string jetAlgo = getPreCutString1("jetAlgo");
  double rParam = getPreCutValue1("DeltaR");

  if( jetAlgo == "AntiKt" )
    fjJetDefinition = JetDefPtr( new fastjet::JetDefinition(fastjet::antikt_algorithm, rParam) );
  else if( jetAlgo == "Kt" )
    fjJetDefinition = JetDefPtr( new fastjet::JetDefinition(fastjet::kt_algorithm, rParam) );
  else 
    fjJetDefinition = JetDefPtr( new fastjet::JetDefinition(fastjet::cambridge_algorithm, rParam) );
    

  // For JECs
  if( int(getPreCutValue1("useJECs"))==1 )
  {
    std::cout << "Reapplying JECs on the fly" << std::endl;
   std::cout << "Using IOV implementation for periodic JEC..." << std::endl;
    
    // Using IOV JEC now. Now that's 2016. See include/IOV.h for changing versions.
    // Note that the IOV implementation can be used with just one JEC if wanted. Juska.
    
    /*
   Ranges for 2016 run periods from DAS as of 4 Nov 16.
   Periods with no certified luminosity are omitted.
   B-v2: 273150 - 275376
   C-v2: 276282 - 276279
   D-v2: 276315 - 276653
   E-v2: 276824 - 277420
   F-v1: 277816 - 278808
   G-v1: 278816 - 280385
   H-v2: 282807 - 283885
   List obtained with commands like this:
   [juska@lxplus069 workdir]$ das_client.py --query='run dataset=/JetHT/Run2016H-PromptReco-v2/MINIAOD' --limit 0
    */

    
    // IOV's updated for Summer16_V3 JEC intervals
  /*  iov = new jec::IOV("AK4PFchs");
    iov->add("BCD",1,276811,true);
    iov->add("EF",276831,278801,true);
    iov->add("G",278802,280385,true);
    iov->add("H",280919,999999,true);*/

/*iov = new jec::IOV("AK4PFchs");
    iov->add("B",297046,299329,true);
    iov->add("C",299368,302029,true);
    iov->add("D",302030,303434,true);
    iov->add("E",303824,304797,true);
    iov->add("F",305040,999999,true);*/

 iov = new jec::IOV("AK4PFchs");
   iov->add("A",315257,316995,true);
    iov->add("B",317080,319310,true);
    iov->add("C",319337,320065,true);
    iov->add("D",320497,325175,true); //for 2018



    
    JetCorrector_data = new FactorizedJetCorrector(); // Will be filled later
        
    // MC JEC done the old way for convenience. Should be updated to V8.
    // Uncertainties also from a single file for now. My best guess was to use V8p2.
    
    
   /*std::string L1Path = "data/Fall17_17Nov2017_V4_MC/Fall17_17Nov2017_V4_MC_L1FastJet_AK4PFchs.txt";
    std::string L2Path = "data/Fall17_17Nov2017_V4_MC/Fall17_17Nov2017_V4_MC_L2Relative_AK4PFchs.txt";
    std::string L3Path = "data/Fall17_17Nov2017_V4_MC/Fall17_17Nov2017_V4_MC_L3Absolute_AK4PFchs.txt";
    
    std::string L1DATAPath = "data/Fall17_17Nov2017_V4_DATA/Fall17_17Nov2017_V4_DATA_L1FastJet_AK4PFchs.txt";
    std::string L2DATAPath = "data/Fall17_17Nov2017_V4_DATA/Fall17_17Nov2017_V4_DATA_L2Relative_AK4PFchs.txt"; 
    std::string L3DATAPath = "data/Fall17_17Nov2017_V4_DATA/Fall17_17Nov2017_V4_DATA_L3Absolute_AK4PFchs.txt";
    std::string L2L3ResidualPath = "data/Fall17_17Nov2017_V4_DATA/Fall17_17Nov2017_V4_DATA_L2L3Residual_AK4PFchs.txt";*/


    
    
  /*  std::string L1DATAPath = "data/2017MC/Fall17_17Nov2017_V4_DATA_L1FastJet_AK4PFchs.txt";
    std::string L2DATAPath = "data/2017MC/Fall17_17Nov2017_V4_DATA_L2Relative_AK4PFchs.txt"; 
    std::string L3DATAPath = "data/2017MC/Fall17_17Nov2017_V4_DATA_L3Absolute_AK4PFchs.txt";
    std::string L2L3ResidualPath = "data/2017MC/Fall17_17Nov2017_V4_DATA_L2L3Residual_AK4PFchs.txt";*/


 std::string L1Path = "data/Fall17_17Nov2017_V6_MC/Fall17_17Nov2017_V6_MC_L1FastJet_AK4PFchs.txt";
    std::string L2Path = "data/Fall17_17Nov2017_V6_MC/Fall17_17Nov2017_V6_MC_L2Relative_AK4PFchs.txt";
    std::string L3Path = "data/Fall17_17Nov2017_V6_MC/Fall17_17Nov2017_V6_MC_L3Absolute_AK4PFchs.txt";



std::string L1DATAPath = "data/Fall17_17Nov2017_V6_DATA/Fall17_17Nov2017F_V6_DATA_L1FastJet_AK4PFchs.txt";
    std::string L2DATAPath = "data/Fall17_17Nov2017_V6_DATA/Fall17_17Nov2017F_V6_DATA_L2Relative_AK4PFchs.txt"; 
    std::string L3DATAPath = "data/Fall17_17Nov2017_V6_DATA/Fall17_17Nov2017F_V6_DATA_L3Absolute_AK4PFchs.txt";
    std::string L2L3ResidualPath = "data/Fall17_17Nov2017_V6_DATA/Fall17_17Nov2017F_V6_DATA_L2L3Residual_AK4PFchs.txt";
    
  


 /*std::string L1DATAPath = "data/Spring16_25nsV6_DATA/Spring16_25nsV6_DATA_L1FastJet_AK4PFchs.txt";
    std::string L2DATAPath = "data/Spring16_25nsV6_DATA/Spring16_25nsV6_DATA_L2Relative_AK4PFchs.txt"; 
    std::string L3DATAPath = "data/Spring16_25nsV6_DATA/Spring16_25nsV6_DATA_L3Absolute_AK4PFchs.txt";
    std::string L2L3ResidualPath = "data/Spring16_25nsV6_DATA/Spring16_25nsV6_DATA_L2L3Residual_AK4PFchs.txt";*/

    
    
    //uncertainty
   // unc = new JetCorrectionUncertainty("data/Spring16_V8_DATA/Spring16_25nsV8p2_DATA_Uncertainty_AK4PFchs.txt");
//unc = new JetCorrectionUncertainty("data/Fall17_17Nov2017_V6_DATA/Fall17_17Nov2017F_V6_DATA_Uncertainty_AK4PFchs.txt");

unc = new JetCorrectionUncertainty("data/Fall17_17Nov2017_V6_MC/Fall17_17Nov2017_V6_MC_Uncertainty_AK4PFchs.txt");

    
    
    //uncertainty
    //unc = new JetCorrectionUncertainty("data/Fall17_17Nov2017_V6_DATA/Fall17_17Nov2017B_V6_DATA_Uncertainty_AK4PFchs.txt");
    
  

    
    //uncertainty
   //unc = new JetCorrectionUncertainty("data/Fall17_17Nov2017_V6_DATA/RunB/Fall17_17Nov2017B_V6_DATA_Uncertainty_AK4PFchs.txt");
    
    
    L1Par = new JetCorrectorParameters(L1Path);
    L2Par = new JetCorrectorParameters(L2Path);
    L3Par = new JetCorrectorParameters(L3Path);
    
  L1DATAPar = new JetCorrectorParameters(L1DATAPath);
    L2DATAPar = new JetCorrectorParameters(L2DATAPath);
    L3DATAPar = new JetCorrectorParameters(L3DATAPath);
    L2L3Residual = new JetCorrectorParameters(L2L3ResidualPath);
    

    std::vector<JetCorrectorParameters> vPar;
    vPar.push_back(*L1Par);
    vPar.push_back(*L2Par);
    vPar.push_back(*L3Par);

      
    //residuals are applied only to data
   std::vector<JetCorrectorParameters> vPar_data;
    vPar_data.push_back(*L1DATAPar);
    vPar_data.push_back(*L2DATAPar);
    vPar_data.push_back(*L3DATAPar);
    vPar_data.push_back(*L2L3Residual);
    

   JetCorrector = new FactorizedJetCorrector(vPar); assert(JetCorrector);
   JetCorrector_data = new FactorizedJetCorrector(vPar_data); assert(JetCorrector_data);
    
  }

  //load btag scale factors
  bcalib = new BTagCalibration("CSVv2", "data/bTag_MC_ScalingFactors/CSVv2_ichep.csv");

  //medium WP
  breader_medium = new BTagCalibrationReader(BTagEntry::OP_MEDIUM,  // operating point
					     "central",             // central sys type
					     {"up", "down"});      // other sys types
  breader_medium->load(*bcalib,                // calibration instance
		       BTagEntry::FLAV_B,    // btag flavour
		       "comb");
  //tight WP
  breader_tight = new BTagCalibrationReader(BTagEntry::OP_TIGHT,  // operating point
					    "central",             // central sys type
					    {"up", "down"});      // other sys types
  breader_tight->load(*bcalib,                // calibration instance
		      BTagEntry::FLAV_B,    // btag flavour
		      "comb");
  
  
  std::cout << "analysisClass::analysisClass(): ends " << std::endl;
}

analysisClass::~analysisClass()
{
  std::cout << "analysisClass::~analysisClass(): begins " << std::endl;

  std::cout << "analysisClass::~analysisClass(): ends " << std::endl;
}

void analysisClass::Loop()
{
   std::cout << "analysisClass::Loop() begins" <<std::endl;   
    
   if (fChain == 0) return;
   
   //////////book histos here

   // TH1F *h_nJetFinal = new TH1F ("h_nJetFinal","",10,0,10);
   // h_nJetFinal->Sumw2();      
   // TH1F *h_nVtx = new TH1F ("h_nVtx","",30,0,30);
   // h_nVtx->Sumw2(); 
   // TH1F *h_trueVtx = new TH1F ("h_trueVtx","",40,0,40);
   // h_trueVtx->Sumw2();  
   // TH1F *h_pT1stJet = new TH1F ("h_pT1stJet","",100,0,3000);
   // h_pT1stJet->Sumw2();
   // TH1F *h_pT2ndJet = new TH1F ("h_pT2ndJet","",100,0,3000);
   // h_pT2ndJet->Sumw2();
   // TH1F *h_eta1stJet = new TH1F ("h_eta1stJet","",5,-2.5,2.5);
   // h_eta1stJet->Sumw2();
   // TH1F *h_eta2ndJet = new TH1F ("h_eta2ndJet","",5,-2.5,2.5);
   // h_eta2ndJet->Sumw2();
   // TH1F *h_DijetMass = new TH1F ("h_DijetMass","",600,0,6000);
   // h_DijetMass->Sumw2();
   // TH1F *h_DeltaETAjj = new TH1F ("h_DeltaETAjj","",120,0,3.);
   // h_DeltaETAjj->Sumw2();

   // variable binning for mjj trigger efficiency plots
   const int nMassBins = 103;

   double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607, 1687,
     1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 4509,
     4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072, 10430, 
     10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

   
  char* HLTname[50]    = {"noTrig","PFHT1050","PFJet550","Mu50", "AK8PFJet550","CaloJet550","Mu50_AllJet","PFHT1050_not_OR_from_others","PFJet550_not_OR_from_others","AK8PFJet550_not_OR_from_others","CaloJet550_not_OR_from_others","PFHT1050_OR_AK8PFJet550","PFHT1050_OR_PFJet550","PFHT1050_OR_CaloJet550"};
 

   
    char name_histoHLT_dR2[50];
   TH1F* h_mjj_HLTpass_dR2[14];
   TH1F* h_mjj_HLTpass_dR2_bb[14];
 char name_histoHLT_dR2_bb[50];






char name_histoHLT_dR2_alpha1[50];
   TH1F* h_mjj_HLTpass_dR2_alpha1[14];
   TH1F* h_mjj_HLTpass_dR2_alpha1_bb[14];
 char name_histoHLT_dR2_alpha1_bb[50];

char name_histoHLT_dR2_alpha2[50];
   TH1F* h_mjj_HLTpass_dR2_alpha2[14];
   TH1F* h_mjj_HLTpass_dR2_alpha2_bb[14];
 char name_histoHLT_dR2_alpha2_bb[50];


char name_histoHLT_dR2_alpha3[50];
TH1F* h_mjj_HLTpass_dR2_alpha3[14];
   TH1F* h_mjj_HLTpass_dR2_alpha3_bb[14];
 char name_histoHLT_dR2_alpha3_bb[50];


char name_histoHLT_dR2_alpha4[50];
   TH1F* h_mjj_HLTpass_dR2_alpha4[14];
   TH1F* h_mjj_HLTpass_dR2_alpha4_bb[14];
 char name_histoHLT_dR2_alpha4_bb[50];

char name_histoHLT_dR2_alpha5[50];
   TH1F* h_mjj_HLTpass_dR2_alpha5[14];
   TH1F* h_mjj_HLTpass_dR2_alpha5_bb[14];
 char name_histoHLT_dR2_alpha5_bb[50];


char name_histoHLT_dR2_alpha6[50];
   TH1F* h_mjj_HLTpass_dR2_alpha6[14];
   TH1F* h_mjj_HLTpass_dR2_alpha6_bb[14];
 char name_histoHLT_dR2_alpha6_bb[50];


char name_histoHLT_dR2_alpha7[50];
   TH1F* h_mjj_HLTpass_dR2_alpha7[14];
   TH1F* h_mjj_HLTpass_dR2_alpha7_bb[14];
 char name_histoHLT_dR2_alpha7_bb[50];


char name_histoHLT_dR2_alpha8[50];
   TH1F* h_mjj_HLTpass_dR2_alpha8[14];
   TH1F* h_mjj_HLTpass_dR2_alpha8_bb[14];
 char name_histoHLT_dR2_alpha8_bb[50];


char name_histoHLT_dR2_alpha9[50];
   TH1F* h_mjj_HLTpass_dR2_alpha9[14];
   TH1F* h_mjj_HLTpass_dR2_alpha9_bb[14];
 char name_histoHLT_dR2_alpha9_bb[50];


char name_histoHLT_dR2_alpha10[50];
   TH1F* h_mjj_HLTpass_dR2_alpha10[14];
   TH1F* h_mjj_HLTpass_dR2_alpha10_bb[14];
 char name_histoHLT_dR2_alpha10_bb[50];


char name_histoHLT_dR2_alpha11[50];
   TH1F* h_mjj_HLTpass_dR2_alpha11[14];
   TH1F* h_mjj_HLTpass_dR2_alpha11_bb[14];
 char name_histoHLT_dR2_alpha11_bb[50];




char name_histoHLT_dR2_alpha12[50];
   TH1F* h_mjj_HLTpass_dR2_alpha12[14];
   TH1F* h_mjj_HLTpass_dR2_alpha12_bb[14];
 char name_histoHLT_dR2_alpha12_bb[50];


char name_histoHLT_dR2_alpha13[50];
   TH1F* h_mjj_HLTpass_dR2_alpha13[14];
   TH1F* h_mjj_HLTpass_dR2_alpha13_bb[14];
 char name_histoHLT_dR2_alpha13_bb[50];


for (int i=0; i<14; i++){  
     sprintf(name_histoHLT_dR2,"h_mjj_HLTpass_dR2_%s",HLTname[i]);
     h_mjj_HLTpass_dR2[i]= new TH1F(name_histoHLT_dR2,"",103,massBoundaries);
sprintf(name_histoHLT_dR2_bb,"h_mjj_HLTpass_dR2_bb_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_bb[i]= new TH1F(name_histoHLT_dR2_bb,"",103,massBoundaries);




sprintf(name_histoHLT_dR2_alpha1,"h_mjj_HLTpass_dR2_alpha1_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha1[i]= new TH1F(name_histoHLT_dR2_alpha1,"",103,massBoundaries);
sprintf(name_histoHLT_dR2_alpha1_bb,"h_mjj_HLTpass_dR2_alpha1_bb_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha1_bb[i]= new TH1F(name_histoHLT_dR2_alpha1_bb,"",103,massBoundaries);



sprintf(name_histoHLT_dR2_alpha2,"h_mjj_HLTpass_dR2_alpha2_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha2[i]= new TH1F(name_histoHLT_dR2_alpha2,"",103,massBoundaries);
sprintf(name_histoHLT_dR2_alpha2_bb,"h_mjj_HLTpass_dR2_alpha2_bb_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha2_bb[i]= new TH1F(name_histoHLT_dR2_alpha2_bb,"",103,massBoundaries);



sprintf(name_histoHLT_dR2_alpha3,"h_mjj_HLTpass_dR2_alpha3_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha3[i]= new TH1F(name_histoHLT_dR2_alpha3,"",103,massBoundaries);
sprintf(name_histoHLT_dR2_alpha3_bb,"h_mjj_HLTpass_dR2_alpha3_bb_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha3_bb[i]= new TH1F(name_histoHLT_dR2_alpha3_bb,"",103,massBoundaries);



sprintf(name_histoHLT_dR2_alpha4,"h_mjj_HLTpass_dR2_alpha4_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha4[i]= new TH1F(name_histoHLT_dR2_alpha4,"",103,massBoundaries);
sprintf(name_histoHLT_dR2_alpha4_bb,"h_mjj_HLTpass_dR2_alpha4_bb_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha4_bb[i]= new TH1F(name_histoHLT_dR2_alpha4_bb,"",103,massBoundaries);



sprintf(name_histoHLT_dR2_alpha5,"h_mjj_HLTpass_dR2_alpha5_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha5[i]= new TH1F(name_histoHLT_dR2_alpha5,"",103,massBoundaries);
sprintf(name_histoHLT_dR2_alpha5_bb,"h_mjj_HLTpass_dR2_alpha5_bb_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha5_bb[i]= new TH1F(name_histoHLT_dR2_alpha5_bb,"",103,massBoundaries);



sprintf(name_histoHLT_dR2_alpha6,"h_mjj_HLTpass_dR2_alpha6_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha6[i]= new TH1F(name_histoHLT_dR2_alpha6,"",103,massBoundaries);
sprintf(name_histoHLT_dR2_alpha6_bb,"h_mjj_HLTpass_dR2_alpha6_bb_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha6_bb[i]= new TH1F(name_histoHLT_dR2_alpha6_bb,"",103,massBoundaries);



sprintf(name_histoHLT_dR2_alpha7,"h_mjj_HLTpass_dR2_alpha7_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha7[i]= new TH1F(name_histoHLT_dR2_alpha7,"",103,massBoundaries);
sprintf(name_histoHLT_dR2_alpha7_bb,"h_mjj_HLTpass_dR2_alpha7_bb_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha7_bb[i]= new TH1F(name_histoHLT_dR2_alpha7_bb,"",103,massBoundaries);



sprintf(name_histoHLT_dR2_alpha8,"h_mjj_HLTpass_dR2_alpha8_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha8[i]= new TH1F(name_histoHLT_dR2_alpha8,"",103,massBoundaries);
sprintf(name_histoHLT_dR2_alpha8_bb,"h_mjj_HLTpass_dR2_alpha8_bb_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha8_bb[i]= new TH1F(name_histoHLT_dR2_alpha8_bb,"",103,massBoundaries);



sprintf(name_histoHLT_dR2_alpha9,"h_mjj_HLTpass_dR2_alpha9_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha9[i]= new TH1F(name_histoHLT_dR2_alpha9,"",103,massBoundaries);
sprintf(name_histoHLT_dR2_alpha9_bb,"h_mjj_HLTpass_dR2_alpha9_bb_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha9_bb[i]= new TH1F(name_histoHLT_dR2_alpha9_bb,"",103,massBoundaries);



sprintf(name_histoHLT_dR2_alpha10,"h_mjj_HLTpass_dR2_alpha10_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha10[i]= new TH1F(name_histoHLT_dR2_alpha10,"",103,massBoundaries);
sprintf(name_histoHLT_dR2_alpha10_bb,"h_mjj_HLTpass_dR2_alpha10_bb_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha10_bb[i]= new TH1F(name_histoHLT_dR2_alpha10_bb,"",103,massBoundaries);



sprintf(name_histoHLT_dR2_alpha11,"h_mjj_HLTpass_dR2_alpha11_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha11[i]= new TH1F(name_histoHLT_dR2_alpha11,"",103,massBoundaries);
sprintf(name_histoHLT_dR2_alpha11_bb,"h_mjj_HLTpass_dR2_alpha11_bb_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha11_bb[i]= new TH1F(name_histoHLT_dR2_alpha11_bb,"",103,massBoundaries);



sprintf(name_histoHLT_dR2_alpha12,"h_mjj_HLTpass_dR2_alpha12_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha12[i]= new TH1F(name_histoHLT_dR2_alpha12,"",103,massBoundaries);
sprintf(name_histoHLT_dR2_alpha12_bb,"h_mjj_HLTpass_dR2_alpha12_bb_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha12_bb[i]= new TH1F(name_histoHLT_dR2_alpha12_bb,"",103,massBoundaries);


sprintf(name_histoHLT_dR2_alpha13,"h_mjj_HLTpass_dR2_alpha13_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha13[i]= new TH1F(name_histoHLT_dR2_alpha13,"",103,massBoundaries);
sprintf(name_histoHLT_dR2_alpha13_bb,"h_mjj_HLTpass_dR2_alpha13_bb_%s",HLTname[i]);
     h_mjj_HLTpass_dR2_alpha13_bb[i]= new TH1F(name_histoHLT_dR2_alpha13_bb,"",103,massBoundaries);


   }









TH1F* h_CEMF_test1 = new TH1F("h_CEMF_test1", "h_CEMF_test1", 50, 0, 1.0);
   // h_CEMF_test1->Sumw2(); 

   TH1F* h_CEMF_test2 = new TH1F("h_CEMF_test2", "h_CEMF_test2", 50, 0, 1.0);

   //book histos for btagged analysis
   TH1F* h_mjj_btag0_m = new TH1F("h_mjj_btag0_m","h_mjj_btag0_m",10000,0,10000);
   TH1F* h_mjj_btag1_m = new TH1F("h_mjj_btag1_m","h_mjj_btag1_m",10000,0,10000);
   TH1F* h_mjj_btag2_m = new TH1F("h_mjj_btag2_m","h_mjj_btag2_m",10000,0,10000);
   TH1F* h_mjj_btag0_t = new TH1F("h_mjj_btag0_t","h_mjj_btag0_t",10000,0,10000);
   TH1F* h_mjj_btag1_t = new TH1F("h_mjj_btag1_t","h_mjj_btag1_t",10000,0,10000);
   TH1F* h_mjj_btag2_t = new TH1F("h_mjj_btag2_t","h_mjj_btag2_t",10000,0,10000);
   TH1F* h_mjj_btag0_mt = new TH1F("h_mjj_btag0_mt","h_mjj_btag0_mt",10000,0,10000);
   TH1F* h_mjj_btag1_mt = new TH1F("h_mjj_btag1_mt","h_mjj_btag1_mt",10000,0,10000);
   TH1F* h_mjj_btag2_mt = new TH1F("h_mjj_btag2_mt","h_mjj_btag2_mt",10000,0,10000);

  

   /////////initialize variables

   Long64_t nentries = fChain->GetEntriesFast();
   std::cout << "analysisClass::Loop(): nentries = " << nentries << std::endl;   

   ////// The following ~7 lines have been taken from rootNtupleClass->Loop() /////
   ////// If the root version is updated and rootNtupleClass regenerated,     /////
   ////// these lines may need to be updated.                                 /////    
   Long64_t nbytes = 0, nb = 0;
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) { //event loop
  // for (Long64_t jentry=0; jentry<50000;jentry++) {
   //for (Long64_t jentry=0; jentry<nentries;jentry=jentry+10) {   //takes every 10th en
   
     Long64_t ientry = LoadTree(jentry);

     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     if(jentry < 10 || jentry%500000 == 0) std::cout << "analysisClass::Loop(): jentry = " << jentry << std::endl;   
     // if (Cut(ientry) < 0) continue;

     ////////////////////// User's code starts here ///////////////////////

     ///Stuff to be done for every event

     size_t no_jets_ak4=jetPtAK4->size();

     vector<TLorentzVector> widejets;
     TLorentzVector wj1, wj2, wdijet; 
     TLorentzVector wj1_shift, wj2_shift, wdijet_shift; 

     vector<TLorentzVector> AK4jets;    
     TLorentzVector ak4j1, ak4j2, ak4j3, ak4j4; 
     TLorentzVector ak4dijet1_[3][1],  ak4dijet2_[3][1], ak4fourjet; 
     TLorentzVector b, c, d;

     resetCuts();

     //find intime BX
     int idx_InTimeBX=-1;
     for(size_t j=0; j<PileupOriginBX->size(); ++j)
       {
	 //cout << PileupOriginBX->at(j) << endl;	 
	 if(PileupOriginBX->at(j)==0)
	   {
	     idx_InTimeBX = j;
	     //cout << "idx_InTimeBX: " << idx_InTimeBX << endl; 
	   }
       }

     std::vector<double> jecFactors;
     std::vector<double> jecUncertainty;
     // new JECs could change the jet pT ordering. the vector below
     // holds sorted jet indices after the new JECs had been applied
     std::vector<unsigned> sortedJetIdx;
     bool isData = 0;

     if(idx_InTimeBX > -1 ) isData = 0;
     else isData = 1;
 
     if( int(getPreCutValue1("useJECs"))==1 )
       {
	 // sort jets by increasing pT
	 std::multimap<double, unsigned> sortedJets;
	 for(size_t j=0; j<no_jets_ak4; ++j)
	   {
	    JetCorrector->setJetEta(jetEtaAK4->at(j));
	     JetCorrector->setJetPt(jetPtAK4->at(j)/jetJecAK4->at(j)); //pTraw
	     JetCorrector->setJetA(jetAreaAK4->at(j));
	     JetCorrector->setRho(rho);
	     
  JetCorrector_data = iov->get(runNo); // Get IOV dependent JEC

        
  	     JetCorrector_data->setJetEta(jetEtaAK4->at(j));
	     JetCorrector_data->setJetPt(jetPtAK4->at(j)/jetJecAK4->at(j)); //pTraw
	     JetCorrector_data->setJetA(jetAreaAK4->at(j));
	     JetCorrector_data->setRho(rho);


  	     //nominal value of JECs
	     double correction;//, old_correction, nominal_correction;
	     //if( int(getPreCutValue1("shiftJECs"))==0 ){
	     if (isData == 1) correction = JetCorrector_data->getCorrection();
                              
	     else correction = JetCorrector->getCorrection();

//cout << correction << endl;
	     //nominal_correction=correction;
	     //old_correction = jetJecAK4->at(j);u
	     //}
	     //JEC uncertainties
	     unc->setJetEta(jetEtaAK4->at(j));
	     unc->setJetPt(jetPtAK4->at(j)/jetJecAK4->at(j)*correction);
	     double uncertainty = unc->getUncertainty(true);
	     jecUncertainty.push_back(uncertainty); 

	     // std::cout << "run:" << runNo << "    lumi:" << lumi << "   event:" << evtNo << "   jet pt:" << jetPtAK4->at(j)/jetJecAK4->at(j)*correction << "   correction:" << correction <<   "   uncertainty:" <<  uncertainty  << "  nominal correction:" << nominal_correction  << " old correction: " << old_correction << std::endl;
	     //use "shifted" JECs for study of systematic uncertainties 
	     if( int(getPreCutValue1("shiftJECs"))==1 ){
	       //flat shift
	       //if (isData == 1) correction = JetCorrector_data->getCorrection() * getPreCutValue2("shiftJECs");
	       //else correction = JetCorrector->getCorrection() * getPreCutValue2("shiftJECs");
	       //shift of the corresponding unc
	       correction = correction + getPreCutValue2("shiftJECs")*uncertainty*correction;
	       //  std::cout << "run:" << runNo << "    lumi:" << lumi << "   event:" << evtNo << "   jet pt:" << jetPtAK3->at(j)/jetJecAK4->at(j)*correction << "   correction:" << correction << "   uncertainty:" <<  uncertainty  << std::endl << std::endl;
	       
	   }

	 jecFactors.push_back(correction);
	 sortedJets.insert(std::make_pair((jetPtAK4->at(j)/jetJecAK4->at(j))*correction, j));

       }
     // get jet indices in decreasing pT order
     for(std::multimap<double, unsigned>::const_reverse_iterator it = sortedJets.rbegin(); it != sortedJets.rend(); ++it)
	 sortedJetIdx.push_back(it->second);
     
     }
     else if( int(getPreCutValue1("noJECs"))==1  )
       {
	 // sort jets by increasing pT
	 std::multimap<double, unsigned> sortedJets;
	 for(size_t j=0; j<no_jets_ak4; ++j) //same ordering of original root trees
	   {
	     jecUncertainty.push_back(0.); 
	     jecFactors.push_back(1.);
	     sortedJets.insert(std::make_pair((jetPtAK4->at(j)/jetJecAK4->at(j)), j)); //raw
	   }       
	 // get jet indices in decreasing pT order
	 for(std::multimap<double, unsigned>::const_reverse_iterator it = sortedJets.rbegin(); it != sortedJets.rend(); ++it)
	   sortedJetIdx.push_back(it->second);
       }
     else
       {
	 for(size_t j=0; j<no_jets_ak4; ++j) //same ordering of original root trees
	   {
	     jecFactors.push_back(jetJecAK4->at(j));
	     jecUncertainty.push_back(0.); 
	     sortedJetIdx.push_back(j);
	   }
       }


     //#############################################################
     //########## NOTE: from now on sortedJetIdx[ijet] should be used
     //#############################################################

     // if(no_jets_ak4>=2){
     //  if(!(fabs(jetEtaAK4->at(0)) < getPreCutValue1("jetFidRegion") && idTAK4->at(0) == getPreCutValue1("tightJetID"))){
     //    std::cout << " JET 0 FAIL " << jetEtaAK4->at(0) << " JET 0  ID " << idTAK4->at(0) << std::endl;
     //  }
     //  if(!(fabs(jetEtaAK4->at(1)) < getPreCutValue1("jetFidRegion") && idTAK4->at(1) == getPreCutValue1("tightJetID"))){
     //    std::cout << " JET 1 FAIL " << jetEtaAK4->at(1) << " JET 1  ID " << idTAK4->at(1) << std::endl;
     //  }  
     // }

     //count ak4 jets passing pt threshold and id criteria
     int Nak4 = 0;
     double HTak4 = 0;
     for(size_t ijet=0; ijet<no_jets_ak4; ++ijet)
       {
	  //cout << "ijet=" << ijet << " , sortedJetIdx[ijet]=" << sortedJetIdx[ijet] 
	  //     << " , raw pT=" << jetPtAK4->at(sortedJetIdx[ijet])/jetJecAK4->at(sortedJetIdx[ijet]) 
	  //     << " , final corrected pT - old =" << jetPtAK4->at(sortedJetIdx[ijet] ) 
	  //     << " , final corrected pT - new =" << (jecFactors[sortedJetIdx[ijet]]/jetJecAK4->at(sortedJetIdx[ijet]))*jetPtAK4->at(sortedJetIdx[ijet])
	  //     << endl;

	 //////////////cout << "id Tight jet" << sortedJetIdx[1] << " = " << idTAK4->at(sortedJetIdx[1]) << endl;
	 if(fabs(jetEtaAK4->at(sortedJetIdx[ijet])) < getPreCutValue1("jetFidRegion")
	    && idTAK4->at(sortedJetIdx[ijet]) == getPreCutValue1("tightJetID") && jetCemfAK4->at(sortedJetIdx[ijet]) < 0.8
	    && (jecFactors[sortedJetIdx[ijet]]/jetJecAK4->at(sortedJetIdx[ijet]))*jetPtAK4->at(sortedJetIdx[ijet]) > getPreCutValue1("ptCut"))
	   {
	     Nak4 += 1;
	     HTak4 += (jecFactors[sortedJetIdx[ijet]]/jetJecAK4->at(sortedJetIdx[ijet]))*jetPtAK4->at(sortedJetIdx[ijet]);
	   }
       }


     if( int(getPreCutValue1("useFastJet"))==1 )
     {
       // vector of ak4 jets used for wide jet clustering
       std::vector<fastjet::PseudoJet> fjInputs, fjInputs_shift;

       for(size_t j=0; j<no_jets_ak4; ++j)
       {
	 if( !(jetEtaAK4->at(sortedJetIdx[j]) < getPreCutValue1("jetFidRegion")
	       && idTAK4->at(sortedJetIdx[j]) == getPreCutValue1("tightJetID") && jetCemfAK4->at(sortedJetIdx[j]) < 0.8 ) ) continue;

	 double rescale = (jecFactors[sortedJetIdx[j]]/jetJecAK4->at(sortedJetIdx[j]));

	 if( j==0 && !( rescale*jetPtAK4->at(sortedJetIdx[j]) > getPreCutValue1("pt0Cut")) ) continue;
	 else if( j==1 && !( rescale*jetPtAK4->at(sortedJetIdx[j]) > getPreCutValue1("pt1Cut")) ) continue;
	 else if( !( rescale*jetPtAK4->at(sortedJetIdx[j]) > getPreCutValue1("ptCut")) ) continue;

	 TLorentzVector tempJet, tempJet_shift;

	 tempJet.SetPtEtaPhiM( rescale*jetPtAK4->at(sortedJetIdx[j]) , jetEtaAK4->at(sortedJetIdx[j]) , jetPhiAK4->at(sortedJetIdx[j]) , rescale*jetMassAK4->at(sortedJetIdx[j]));
	 tempJet_shift.SetPtEtaPhiM( (1+jecUncertainty[sortedJetIdx[j]])* rescale*jetPtAK4->at(sortedJetIdx[j]) , jetEtaAK4->at(sortedJetIdx[j]) , jetPhiAK4->at(sortedJetIdx[j]) ,  (1+jecUncertainty[sortedJetIdx[j]])* rescale*jetMassAK4->at(sortedJetIdx[j]));

	 fjInputs.push_back(fastjet::PseudoJet(tempJet.Px(),tempJet.Py(),tempJet.Pz(),tempJet.E()));
	 fjInputs_shift.push_back(fastjet::PseudoJet(tempJet_shift.Px(),tempJet_shift.Py(),tempJet_shift.Pz(),tempJet_shift.E()));
       }

       fjClusterSeq = ClusterSequencePtr( new fastjet::ClusterSequence( fjInputs, *fjJetDefinition ) );
       fjClusterSeq_shift = ClusterSequencePtr( new fastjet::ClusterSequence( fjInputs_shift, *fjJetDefinition ) );

       std::vector<fastjet::PseudoJet> inclusiveWideJets = fastjet::sorted_by_pt( fjClusterSeq->inclusive_jets(0.) );
       std::vector<fastjet::PseudoJet> inclusiveWideJets_shift = fastjet::sorted_by_pt( fjClusterSeq_shift->inclusive_jets(0.) );

       if( inclusiveWideJets.size()>1 )
       {
	 wj1.SetPxPyPzE(inclusiveWideJets.at(0).px(), inclusiveWideJets.at(0).py(), inclusiveWideJets.at(0).pz(), inclusiveWideJets.at(0).e());
	 wj2.SetPxPyPzE(inclusiveWideJets.at(1).px(), inclusiveWideJets.at(1).py(), inclusiveWideJets.at(1).pz(), inclusiveWideJets.at(1).e());
	 wj1_shift.SetPxPyPzE(inclusiveWideJets_shift.at(0).px(), inclusiveWideJets_shift.at(0).py(), inclusiveWideJets_shift.at(0).pz(), inclusiveWideJets_shift.at(0).e());
	 wj2_shift.SetPxPyPzE(inclusiveWideJets_shift.at(1).px(), inclusiveWideJets_shift.at(1).py(), inclusiveWideJets_shift.at(1).pz(), inclusiveWideJets_shift.at(1).e());
       }
     }
     else
     {
       TLorentzVector wj1_tmp, wj2_tmp;
       TLorentzVector wj1_shift_tmp, wj2_shift_tmp;
       double wideJetDeltaR_ = getPreCutValue1("DeltaR");

       if(no_jets_ak4>=2)
	 {
	   if(fabs(jetEtaAK4->at(sortedJetIdx[0])) < getPreCutValue1("jetFidRegion")  &&  jetCemfAK4->at(sortedJetIdx[0]) < 0.8 && idTAK4->at(sortedJetIdx[0]) == getPreCutValue1("tightJetID")
	      && (jecFactors[sortedJetIdx[0]]/jetJecAK4->at(sortedJetIdx[0]))*jetPtAK4->at(sortedJetIdx[sortedJetIdx[0]]) > getPreCutValue1("pt0Cut"))
	     {
	       if(fabs(jetEtaAK4->at(sortedJetIdx[1])) < getPreCutValue1("jetFidRegion") && jetCemfAK4->at(sortedJetIdx[1]) < 0.8 && idTAK4->at(sortedJetIdx[1]) == getPreCutValue1("tightJetID")
		  && (jecFactors[sortedJetIdx[1]]/jetJecAK4->at(sortedJetIdx[1]))*jetPtAK4->at(sortedJetIdx[1]) > getPreCutValue1("pt1Cut"))
		 {
		   TLorentzVector jet1, jet2, jet1_shift, jet2_shift;
		   jet1.SetPtEtaPhiM( (jecFactors[sortedJetIdx[0]]/jetJecAK4->at(sortedJetIdx[0])) *jetPtAK4->at(sortedJetIdx[0])
				      ,jetEtaAK4->at(sortedJetIdx[0]),jetPhiAK4->at(sortedJetIdx[0])
				      , (jecFactors[sortedJetIdx[0]]/jetJecAK4->at(sortedJetIdx[0])) * jetMassAK4->at(sortedJetIdx[0]));
		   jet2.SetPtEtaPhiM( (jecFactors[sortedJetIdx[1]]/jetJecAK4->at(sortedJetIdx[1])) *jetPtAK4->at(sortedJetIdx[1])
				      ,jetEtaAK4->at(sortedJetIdx[1]),jetPhiAK4->at(sortedJetIdx[1])
				      , (jecFactors[sortedJetIdx[1]]/jetJecAK4->at(sortedJetIdx[1])) * jetMassAK4->at(sortedJetIdx[1]));
		   jet1_shift.SetPtEtaPhiM( (1+jecUncertainty[sortedJetIdx[0]])*(jecFactors[sortedJetIdx[0]]/jetJecAK4->at(sortedJetIdx[0])) *jetPtAK4->at(sortedJetIdx[0])
				      ,jetEtaAK4->at(sortedJetIdx[0]),jetPhiAK4->at(sortedJetIdx[0])
				      , (1+jecUncertainty[sortedJetIdx[0]])*(jecFactors[sortedJetIdx[0]]/jetJecAK4->at(sortedJetIdx[0])) * jetMassAK4->at(sortedJetIdx[0]));
		   jet2_shift.SetPtEtaPhiM( (1+jecUncertainty[sortedJetIdx[1]])* (jecFactors[sortedJetIdx[1]]/jetJecAK4->at(sortedJetIdx[1])) *jetPtAK4->at(sortedJetIdx[1])
				      ,jetEtaAK4->at(sortedJetIdx[1]),jetPhiAK4->at(sortedJetIdx[1])
				      , (1+jecUncertainty[sortedJetIdx[0]])*(jecFactors[sortedJetIdx[1]]/jetJecAK4->at(sortedJetIdx[1])) * jetMassAK4->at(sortedJetIdx[1]));
		   
		   for(Long64_t ijet=0; ijet<no_jets_ak4; ijet++)
		     { //jet loop for ak4
		       TLorentzVector currentJet;
		       
		       if(fabs(jetEtaAK4->at(sortedJetIdx[ijet])) < getPreCutValue1("jetFidRegion") 
			  && idTAK4->at(sortedJetIdx[ijet]) == getPreCutValue1("tightJetID") && jetCemfAK4->at(sortedJetIdx[ijet]) < 0.8
			  && (jecFactors[sortedJetIdx[ijet]]/jetJecAK4->at(sortedJetIdx[ijet]))*jetPtAK4->at(sortedJetIdx[ijet]) > getPreCutValue1("ptCut"))
			 {
			   TLorentzVector currentJet, currentJet_shift;
			   currentJet.SetPtEtaPhiM( (jecFactors[sortedJetIdx[ijet]]/jetJecAK4->at(sortedJetIdx[ijet])) *jetPtAK4->at(sortedJetIdx[ijet])
						    ,jetEtaAK4->at(sortedJetIdx[ijet]),jetPhiAK4->at(sortedJetIdx[ijet])
						    , (jecFactors[sortedJetIdx[ijet]]/jetJecAK4->at(sortedJetIdx[ijet])) *jetMassAK4->at(sortedJetIdx[ijet]));   
			   currentJet_shift.SetPtEtaPhiM( (1+jecUncertainty[sortedJetIdx[ijet]])*(jecFactors[sortedJetIdx[ijet]]/jetJecAK4->at(sortedJetIdx[ijet])) *jetPtAK4->at(sortedJetIdx[ijet])
						    ,jetEtaAK4->at(sortedJetIdx[ijet]),jetPhiAK4->at(sortedJetIdx[ijet])
						    , (1+jecUncertainty[sortedJetIdx[ijet]])*(jecFactors[sortedJetIdx[ijet]]/jetJecAK4->at(sortedJetIdx[ijet])) *jetMassAK4->at(sortedJetIdx[ijet]));   
			   
			   double DeltaR1 = currentJet.DeltaR(jet1);
			   double DeltaR2 = currentJet.DeltaR(jet2);
			   
			   if(DeltaR1 < DeltaR2 && DeltaR1 < wideJetDeltaR_)
			     {
			       wj1_tmp += currentJet;
			       wj1_shift_tmp += currentJet_shift;
			     }
			   else if(DeltaR2 < wideJetDeltaR_)
			     {
			       wj2_tmp += currentJet;
			       wj2_shift_tmp += currentJet_shift;
			     }			 
			 } // if AK4 jet passes fid and jetid.
		     } //end of ak4 jet loop		     

		   // if(wj1_tmp.Pt()==0 && wj2_tmp.Pt() ==0) 
		   // std::cout << " wj1_tmp.Pt() IN  " <<wj1_tmp.Pt()  << " wj2_tmp.Pt() " <<  wj2_tmp.Pt()  << std::endl;		     

		 } //fid, jet id, pt cut
	     } //fid, jet id, pt cut
	 } // end of two jets.
	 
       // Re-order the wide jets in pt
       if( wj1_tmp.Pt() > wj2_tmp.Pt())
	 {
	   wj1 = wj1_tmp;
	   wj2 = wj2_tmp;
	   wj1_shift = wj1_shift_tmp;
	   wj2_shift = wj2_shift_tmp;
	 }
       else
	 {
	   wj1 = wj2_tmp;
	   wj2 = wj1_tmp;
	   wj1_shift = wj2_shift_tmp;
	   wj2_shift = wj1_shift_tmp;
	 }
     }

     double MJJWide = 0; 
     double DeltaEtaJJWide = 0;
     double DeltaPhiJJWide = 0;
     double MJJWide_shift = 0; 
     if( wj1.Pt()>0 && wj2.Pt()>0 )
     {
       // Create dijet system
       wdijet = wj1 + wj2;
       MJJWide = wdijet.M();
       DeltaEtaJJWide = fabs(wj1.Eta()-wj2.Eta());
       DeltaPhiJJWide = fabs(wj1.DeltaPhi(wj2));
       
       wdijet_shift = wj1_shift + wj2_shift;
       MJJWide_shift = wdijet_shift.M();

       // Put widejets in the container
       widejets.push_back( wj1 );
       widejets.push_back( wj2 );
     }

     //AK4 jets
     if(no_jets_ak4>=4){
     //cout << "eta j1 " << jetEtaAK4->at(sortedJetIdx[0]) << endl;
       //cout << "pt j1 " << (jecFactors[sortedJetIdx[0]]/jetJecAK4->at(sortedJetIdx[0])) *jetPtAK4->at(sortedJetIdx[0]) << endl;

	 if(fabs(jetEtaAK4->at(sortedJetIdx[0])) < getPreCutValue1("jetFidRegion") && jetCemfAK4->at(sortedJetIdx[0]) < 0.8 && idTAK4->at(sortedJetIdx[0]) == getPreCutValue1("tightJetID")
	    && (jecFactors[sortedJetIdx[0]]/jetJecAK4->at(sortedJetIdx[0]))*jetPtAK4->at(sortedJetIdx[0]) > getPreCutValue1("pt0Cut")){

	     if(fabs(jetEtaAK4->at(sortedJetIdx[1])) < getPreCutValue1("jetFidRegion")  && jetCemfAK4->at(sortedJetIdx[1]) < 0.8 &&  idTAK4->at(sortedJetIdx[1]) == getPreCutValue1("tightJetID")
		&& (jecFactors[sortedJetIdx[1]]/jetJecAK4->at(sortedJetIdx[1]))*jetPtAK4->at(sortedJetIdx[1]) > getPreCutValue1("pt1Cut")){

 		 if(fabs(jetEtaAK4->at(sortedJetIdx[2])) < getPreCutValue1("jetFidRegion")  && jetCemfAK4->at(sortedJetIdx[2]) < 0.8 &&  idTAK4->at(sortedJetIdx[2]) == getPreCutValue1("tightJetID")
		&& (jecFactors[sortedJetIdx[2]]/jetJecAK4->at(sortedJetIdx[2]))*jetPtAK4->at(sortedJetIdx[2]) > getPreCutValue1("pt2Cut")){

 		    if(fabs(jetEtaAK4->at(sortedJetIdx[3])) < getPreCutValue1("jetFidRegion")  && jetCemfAK4->at(sortedJetIdx[3]) < 0.8 &&  idTAK4->at(sortedJetIdx[3]) == getPreCutValue1("tightJetID")
		&& (jecFactors[sortedJetIdx[3]]/jetJecAK4->at(sortedJetIdx[3]))*jetPtAK4->at(sortedJetIdx[3]) > getPreCutValue1("pt3Cut")){
 			
		 //cout << "filling ak4j1 and ak4j2" << endl;
		 //cout << "pt ak4 j1 = " << (jecFactors[sortedJetIdx[0]]/jetJecAK4->at(sortedJetIdx[0])) *jetPtAK4->at(sortedJetIdx[0]) << endl;
		 	  ak4j1.SetPtEtaPhiM( (jecFactors[sortedJetIdx[0]]/jetJecAK4->at(sortedJetIdx[0])) *jetPtAK4->at(sortedJetIdx[0])
				     ,jetEtaAK4->at(sortedJetIdx[0])
				     ,jetPhiAK4->at(sortedJetIdx[0])
				     , (jecFactors[sortedJetIdx[0]]/jetJecAK4->at(sortedJetIdx[0])) *jetMassAK4->at(sortedJetIdx[0]));
			  ak4j2.SetPtEtaPhiM( (jecFactors[sortedJetIdx[1]]/jetJecAK4->at(sortedJetIdx[1])) *jetPtAK4->at(sortedJetIdx[1])
				     ,jetEtaAK4->at(sortedJetIdx[1])
				     ,jetPhiAK4->at(sortedJetIdx[1])
				     , (jecFactors[sortedJetIdx[1]]/jetJecAK4->at(sortedJetIdx[1])) *jetMassAK4->at(sortedJetIdx[1]));

                 	  ak4j3.SetPtEtaPhiM( (jecFactors[sortedJetIdx[2]]/jetJecAK4->at(sortedJetIdx[2])) *jetPtAK4->at(sortedJetIdx[2])
				     ,jetEtaAK4->at(sortedJetIdx[2])
				     ,jetPhiAK4->at(sortedJetIdx[2])
				     , (jecFactors[sortedJetIdx[2]]/jetJecAK4->at(sortedJetIdx[2])) *jetMassAK4->at(sortedJetIdx[2]));
                 	  ak4j4.SetPtEtaPhiM( (jecFactors[sortedJetIdx[3]]/jetJecAK4->at(sortedJetIdx[3])) *jetPtAK4->at(sortedJetIdx[3])
				     ,jetEtaAK4->at(sortedJetIdx[3])
				     ,jetPhiAK4->at(sortedJetIdx[3])
				     , (jecFactors[sortedJetIdx[3]]/jetJecAK4->at(sortedJetIdx[3])) *jetMassAK4->at(sortedJetIdx[3]));
		        }
	         }
            } 
         }
      }  //end of 4jets 


     double MJJAK4 = 0; 
     double MJJAK4_1_[3][1]={0}; double MJJAK4_2_[3][1]={0};
     double MJJAK4_1=0; double MJJAK4_2=0;      
     
     double M4J_AK4=0; double Maverage=0;
     double Masymmetry=0; double Masymmetry_[3][1]={0}; 
     double DDR=0; double DdR2_[3][1]={0};
     double DeltaR=0; double DeltaR_[3][1]={0}; double Delta_1=0; double Delta_2=0;
          
     double PT_firstcomb_1=0; double PT_firstcomb_2=0; double PT_secondcomb_1=0; double PT_secondcomb_2=0;

     double DeltaPhiJJAK4=0; double DeltaEtaJJAK4=0;   
     double ETA_1=0; double ETA_2=0;
      
     double Rapidity_1=0; double Rapidity_2=0; double DeltaRapidity=0;
     double DeltaRAK4_First=0; double DeltaRAK4_Second=0; double DeltaRAK4_1_[3][1]={0}; double DeltaRAK4_2_[3][1]={0};
      
   if( ak4j1.Pt()>0 && ak4j2.Pt()>0  && ak4j3.Pt()>0 && ak4j4.Pt()>0){ // Create 4jet system, create 3 combinations
   //cout<<ak4j1.Pt()<<" "<<ak4j2.Pt()<<" "<<ak4j3.Pt()<<" "<<ak4j4.Pt()<<endl;  

     for(int comb=0; comb<3; comb++){ //for 5 jets pool: loop over 4 combinations: 1->2, 1->3, 1->4, 1->5

       for(int ijet=0; ijet<1; ijet++){//for 5 jets pool: loop over 3 cases: i.e. for 1->2 combinations the cases are 3->4, 3->5, 4->5
     
         if(comb==0){
	   b=ak4j2;
	   if(ijet==0){c=ak4j3;d=ak4j4;}
           //if(ijet==1){c=ak4j3;d=ak4j5;}
           //if(ijet==2){c=ak4j4;d=ak4j5;}
         }if(comb==1){
	   b=ak4j3;
	   if(ijet==0){c=ak4j2;d=ak4j4;}
           //if(ijet==1){c=ak4j2;d=ak4j5;}
           //if(ijet==2){c=ak4j4;d=ak4j5;}
         }if(comb==2){
           b=ak4j4;
	   if(ijet==0){c=ak4j2;d=ak4j3;}
           //if(ijet==1){c=ak4j2;d=ak4j5;}
           //if(ijet==2){c=ak4j3;d=ak4j5;}
         }
/* 	if(comb==3){
	   b=ak4j5;
 	   if(ijet==0){c=ak4j2;d=ak4j3;}
           if(ijet==1){c=ak4j2;d=ak4j4;}
           if(ijet==2){c=ak4j3;d=ak4j4;}
         }      
*/
       ak4dijet1_[comb][ijet] = ak4j1 + b;
       ak4dijet2_[comb][ijet]=  c + d;  
 
       MJJAK4_1_[comb][ijet] = ak4dijet1_[comb][ijet].M();
       MJJAK4_2_[comb][ijet] = ak4dijet2_[comb][ijet].M();
       Masymmetry_[comb][ijet]=fabs((MJJAK4_1_[comb][ijet]-MJJAK4_2_[comb][ijet])/(MJJAK4_1_[comb][ijet]+MJJAK4_2_[comb][ijet]));
              
       DeltaRAK4_1_[comb][ijet]=ak4j1.DeltaR(b);//edw DeltaR metaxy jets tou 1ou zevgous
       DeltaRAK4_2_[comb][ijet]=c.DeltaR(d);//edw DeltaR metaxy jets tou 2ou zevgous
       //cout<<DeltaRAK4_1_[comb][ijet]<<" "<<DeltaRAK4_2_[comb][ijet]<<endl; 
       DdR2_[comb][ijet] = fabs(DeltaRAK4_1_[comb][ijet]-DeltaRAK4_2_[comb][ijet]);
       DeltaR_[comb][ijet] = fabs(DeltaRAK4_1_[comb][ijet]-0.8) + fabs(DeltaRAK4_2_[comb][ijet]-0.8);  //EXO-17-021
     
       }//end of ijet loop:  different cases for the 1st combination

     } //end of combination loop

     double DdR2_minimum=1000.0; double Masymmetry_minimum=1000; double DeltaR_minimum=1000; int comb_min,ijet_min, comb_min_Mas, ijet_min_Mas, comb_min_DR, ijet_min_DR;
     for(int comb=0; comb<3; comb++){ //for 5 jets pool: loop over 4 combinations: 1->2, 1->3, 1->4, 1->5
       for(int ijet=0; ijet<1; ijet++){//for 5 jets pool: loop over 3 cases: i.e. for 1->2 combinations the cases are 3->4, 3->5, 4->5
     
	 if(DdR2_[comb][ijet] < DdR2_minimum) {
           DdR2_minimum = DdR2_[comb][ijet];
	   comb_min=comb; ijet_min=ijet;
         }
         if(Masymmetry_[comb][ijet] < Masymmetry_minimum) {
           Masymmetry_minimum = Masymmetry_[comb][ijet];
	   comb_min_Mas=comb; ijet_min_Mas=ijet;
         }
	 if(DeltaR_[comb][ijet] < DeltaR_minimum){
	   DeltaR_minimum = DeltaR_[comb][ijet];
	   comb_min_DR=comb; ijet_min_DR=ijet;
	 }
         
       }//end of ijet loop:  different cases for the 1st combination
     } //end of combination loop
/*
     cout << jentry<<endl;
     cout<<comb_min<<" "<<ijet_min<<" "<<DdR2_minimum << endl;
     cout<<comb_min_Mas<<" "<<ijet_min_Mas<<" "<<Masymmetry_minimum << endl;
     cout<<comb_min_DR<<" "<<ijet_min_DR<<" "<<DeltaR_minimum << endl;
*/
     for(int comb=0; comb<3; comb++){ //for 5 jets pool: loop over 4 combinations: 1->2, 1->3, 1->4, 1->5
       for(int ijet=0; ijet<1; ijet++){//for 5 jets pool: loop over 3 cases: i.e. for 1->2 combinations the cases are 3->4, 3->5, 4->5
    
         if(comb==comb_min_DR && ijet==ijet_min_DR){

           if(comb==0){
	     b=ak4j2;
	     if(ijet==0){c=ak4j3;d=ak4j4;}
             //if(ijet==1){c=ak4j3;d=ak4j5;}
             //if(ijet==2){c=ak4j4;d=ak4j5;}
           }if(comb==1){
	     b=ak4j3;
	     if(ijet==0){c=ak4j2;d=ak4j4;}
             //if(ijet==1){c=ak4j2;d=ak4j5;}
             //if(ijet==2){c=ak4j4;d=ak4j5;}
           }if(comb==2){
             b=ak4j4;
	     if(ijet==0){c=ak4j2;d=ak4j3;}
             //if(ijet==1){c=ak4j2;d=ak4j5;}
             //if(ijet==2){c=ak4j3;d=ak4j5;}
           }
/*
	     if(comb==3){
	     b=ak4j5;
 	     if(ijet==0){c=ak4j2;d=ak4j3;}
             if(ijet==1){c=ak4j2;d=ak4j4;}
             if(ijet==2){c=ak4j3;d=ak4j4;}
           }  
*/
     	   MJJAK4_1=MJJAK4_1_[comb][ijet]; 
    	   MJJAK4_2=MJJAK4_2_[comb][ijet];
           ak4fourjet=ak4j1+b+c+d;  
   	   M4J_AK4=ak4fourjet.M();  
    	   Maverage=(MJJAK4_1_[comb][ijet]+MJJAK4_2_[comb][ijet])/2.;
    	   Masymmetry=Masymmetry_[comb][ijet]; 
    	   DDR=DdR2_[comb_min][ijet];  
    	   DeltaEtaJJAK4=fabs(ak4dijet1_[comb][ijet].Eta()-ak4dijet2_[comb][ijet].Eta());// edw Delta ETA metaxy zevgwn
    	   DeltaPhiJJAK4 = fabs(ak4dijet1_[comb][ijet].DeltaPhi(ak4dijet2_[comb][ijet]));

    	   PT_firstcomb_1=ak4j1.Pt();
    	   PT_firstcomb_2=b.Pt();
    	   PT_secondcomb_1=c.Pt();
     	   PT_secondcomb_2=d.Pt();

    	   ETA_1=ak4dijet1_[comb][ijet].Eta();
     	   ETA_2=ak4dijet2_[comb][ijet].Eta();

     	   Rapidity_1=ak4dijet1_[comb][ijet].Rapidity();
     	   Rapidity_2=ak4dijet2_[comb][ijet].Rapidity();
     	   DeltaRapidity=fabs(ak4dijet1_[comb][ijet].Rapidity()-ak4dijet2_[comb][ijet].Rapidity());

     	   DeltaRAK4_First=DeltaRAK4_1_[comb][ijet];
     	   DeltaRAK4_Second=DeltaRAK4_2_[comb][ijet];
	   DeltaR=DeltaR_[comb][ijet];


//cout<<MJJAK4_1<<"  "<<MJJAK4_2<<"  "<<M4J_AK4<<"  "<<Maverage<<"  "<<Masymmetry<<" "<<DDR<<"  "<<DeltaEtaJJAK4<<"  "<<DeltaPhiJJAK4<<"  "<<ETA_1<<"  "<<ETA_2<<  " "<<DeltaRAK4_First<<"   "<<DeltaRAK4_Second<<endl;

//cout << "deltaR first combination " << sqrt(((ak4j1.Eta()-ak4j2.Eta())*(ak4j1.Eta()-ak4j2.Eta()))+ ((Phi_mpi_pi(ak4j1.Phi()-ak4j2.Phi())*(Phi_mpi_pi(ak4j1.Phi()-ak4j2.Phi()))));

//dphi = abs(ak4j1.Phi()-ak4j2.Phi());
 //if (dphi>3.14) dphi-=2*3.14; 
//cout << "deltaR first combination " << sqrt(((ak4j1.Eta()-ak4j2.Eta())*(ak4j1.Eta()-ak4j2.Eta()))+ (dphi*dphi));

	   //=============== EXO-17-021 ===============
       	   Delta_1=PT_firstcomb_1+PT_firstcomb_2-Maverage;
           Delta_2=PT_secondcomb_1+PT_secondcomb_2-Maverage;

       	   // Put in the container
           AK4jets.push_back(ak4j1);
           AK4jets.push_back(ak4j2);
           AK4jets.push_back(ak4j3);
           AK4jets.push_back(ak4j4);

	 }//end of if min
       }//end of ijet	
     }//end of comb
   }//end of 5jet system with pt>0

       //== Fill Variables ==

     fillVariableWithValue("run",runNo);     
     fillVariableWithValue("event",evtNo);     
     fillVariableWithValue("lumi",lumi);     
     fillVariableWithValue("nVtx",nvtx);     
     fillVariableWithValue("nJet",widejets.size());
     fillVariableWithValue("metSig",metSig);
     fillVariableWithValue("Nak4",Nak4);
     fillVariableWithValue ( "PassJSON", passJSON (runNo, lumi, isData));

  /*   if( AK4jets.size() >=1 ){
       cout << " edw 1" << "AK4jets.size() " <<  AK4jets.size() << endl;
       //cout << "IdTight_j1 : " << idTAK4->at(sortedJetIdx[0]) << endl;
       fillVariableWithValue( "IdTight_j1",idTAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "pTAK4_j1", AK4jets[0].Pt());
       fillVariableWithValue( "etaAK4_j1", AK4jets[0].Eta());
       fillVariableWithValue( "phiAK4_j1", AK4jets[0].Phi());
       
       //fillVariableWithValue( "jetPtAK4matchCaloJet_j1", jetPtAK4matchCaloJet->at(sortedJetIdx[0]));
       
       fillVariableWithValue( "jetJecAK4_j1", jecFactors[sortedJetIdx[0]] );
       fillVariableWithValue( "jetJecUncAK4_j1", jecUncertainty[sortedJetIdx[0]] );
       
       fillVariableWithValue( "jetCSVAK4_j1", jetCSVAK4->at(sortedJetIdx[0]) );
       fillVariableWithValue("jetHflavour_j1",hFlavourAK4->at(sortedJetIdx[0]));

       //jetID
       fillVariableWithValue( "neutrHadEnFrac_j1", jetNhfAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "chargedHadEnFrac_j1", jetChfAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "photonEnFrac_j1", jetPhfAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "eleEnFract_j1", jetElfAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "muEnFract_j1", jetMufAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "neutrElectromFrac_j1", jetNemfAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "chargedElectromFrac_j1", jetCemfAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "chargedMult_j1", chMultAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "neutrMult_j1", neMultAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "photonMult_j1", phoMultAK4->at(sortedJetIdx[0]));
     }
     if( AK4jets.size() >=2 ){//edw 4-jets
 cout << "edw 2" << "AK4jets.size() " <<  AK4jets.size() << endl;
       //cout << "IdTight_j2 : " << idTAK4->at(sortedJetIdx[1]) << endl << endl;
       fillVariableWithValue( "IdTight_j2",idTAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "pTAK4_j2", AK4jets[1].Pt() );
       fillVariableWithValue( "etaAK4_j2", AK4jets[1].Eta());
       fillVariableWithValue( "phiAK4_j2", AK4jets[1].Phi());
       //fillVariableWithValue( "jetPtAK4matchCaloJet_j2", jetPtAK4matchCaloJet->at(sortedJetIdx[1]));
       fillVariableWithValue( "jetJecAK4_j2", jecFactors[sortedJetIdx[1]]); 
       fillVariableWithValue( "jetJecUncAK4_j2", jecUncertainty[sortedJetIdx[1]] );
       fillVariableWithValue( "jetCSVAK4_j2", jetCSVAK4->at(sortedJetIdx[1]) );
       fillVariableWithValue("jetHflavour_j2",hFlavourAK4->at(sortedJetIdx[1]));

       //jetID
       fillVariableWithValue( "neutrHadEnFrac_j2", jetNhfAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "chargedHadEnFrac_j2", jetChfAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "photonEnFrac_j2", jetPhfAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "eleEnFract_j2", jetElfAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "muEnFract_j2", jetMufAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "neutrElectromFrac_j2", jetNemfAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "chargedElectromFrac_j2", jetCemfAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "chargedMult_j2", chMultAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "neutrMult_j2", neMultAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "photonMult_j2", phoMultAK4->at(sortedJetIdx[1]));
       //dijet
      // fillVariableWithValue( "Dijet_MassAK4", MJJAK4) ; 
      // fillVariableWithValue( "CosThetaStarAK4", TMath::TanH( (AK4jets[0].Eta()-AK4jets[1].Eta())/2 )); 
      // fillVariableWithValue( "deltaETAjjAK4", DeltaEtaJJAK4 ) ;
      // fillVariableWithValue( "deltaPHIjjAK4", DeltaPhiJJAK4 ) ;
     }


 if( AK4jets.size() >=3 ){//edw 4-jets
 cout << " edw 3" <<  "AK4jets.size() " <<  AK4jets.size() << endl;
       //cout << "IdTight_j3 : " << idTAK4->at(sortedJetIdx[2]) << endl << endl;
       fillVariableWithValue( "IdTight_j3",idTAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "pTAK4_j3", AK4jets[2].Pt() );
       fillVariableWithValue( "etaAK4_j3", AK4jets[2].Eta());
       fillVariableWithValue( "phiAK4_j3", AK4jets[2].Phi());
       //fillVariableWithValue( "jetPtAK4matchCaloJet_j3", jetPtAK4matchCaloJet->at(sortedJetIdx[2]));
       fillVariableWithValue( "jetJecAK4_j3", jecFactors[sortedJetIdx[2]]); 
       fillVariableWithValue( "jetJecUncAK4_j3", jecUncertainty[sortedJetIdx[2]] );
       fillVariableWithValue( "jetCSVAK4_j3", jetCSVAK4->at(sortedJetIdx[2]) );
       fillVariableWithValue("jetHflavour_j3",hFlavourAK4->at(sortedJetIdx[2]));

       //jetID
       fillVariableWithValue( "neutrHadEnFrac_j3", jetNhfAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "chargedHadEnFrac_j3", jetChfAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "photonEnFrac_j3", jetPhfAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "eleEnFract_j3", jetElfAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "muEnFract_j3", jetMufAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "neutrElectromFrac_j3", jetNemfAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "chargedElectromFrac_j3", jetCemfAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "chargedMult_j3", chMultAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "neutrMult_j3", neMultAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "photonMult_j3", phoMultAK4->at(sortedJetIdx[2]));
       //dijet
       //fillVariableWithValue( "Dijet_MassAK4", MJJAK4) ; 
       //fillVariableWithValue( "CosThetaStarAK4", TMath::TanH( (AK4jets[1].Eta()-AK4jets[2].Eta())/2 )); 
      // fillVariableWithValue( "deltaETAjjAK4", DeltaEtaJJAK4 ) ;
      // fillVariableWithValue( "deltaPHIjjAK4", DeltaPhiJJAK4 ) ;
     }

*/

     if( AK4jets.size() >=4 ){//edw 5-jets analysis ( I chose 4 out of 5 jets)

       //cout << "IdTight_j4 : " << idTAK4->at(sortedJetIdx[3]) << endl << endl;
       //cout << " edw 4 " << "AK4jets.size() " <<  AK4jets.size() << endl;
       //cout << "IdTight_j1 : " << idTAK4->at(sortedJetIdx[0]) << endl;
       fillVariableWithValue( "IdTight_j1",idTAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "pTAK4_j1", AK4jets[0].Pt());
       fillVariableWithValue( "etaAK4_j1", AK4jets[0].Eta());
       fillVariableWithValue( "phiAK4_j1", AK4jets[0].Phi());
       
       //fillVariableWithValue( "jetPtAK4matchCaloJet_j1", jetPtAK4matchCaloJet->at(sortedJetIdx[0]));
       
       fillVariableWithValue( "jetJecAK4_j1", jecFactors[sortedJetIdx[0]] );
       fillVariableWithValue( "jetJecUncAK4_j1", jecUncertainty[sortedJetIdx[0]] );
       
       fillVariableWithValue( "jetCSVAK4_j1", jetCSVAK4->at(sortedJetIdx[0]) );
       fillVariableWithValue("jetHflavour_j1",hFlavourAK4->at(sortedJetIdx[0]));

       //jetID
       fillVariableWithValue( "neutrHadEnFrac_j1", jetNhfAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "chargedHadEnFrac_j1", jetChfAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "photonEnFrac_j1", jetPhfAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "eleEnFract_j1", jetElfAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "muEnFract_j1", jetMufAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "neutrElectromFrac_j1", jetNemfAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "chargedElectromFrac_j1", jetCemfAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "chargedMult_j1", chMultAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "neutrMult_j1", neMultAK4->at(sortedJetIdx[0]));
       fillVariableWithValue( "photonMult_j1", phoMultAK4->at(sortedJetIdx[0]));
     
       fillVariableWithValue( "IdTight_j2",idTAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "pTAK4_j2", AK4jets[1].Pt() );
       fillVariableWithValue( "etaAK4_j2", AK4jets[1].Eta());
       fillVariableWithValue( "phiAK4_j2", AK4jets[1].Phi());
       //fillVariableWithValue( "jetPtAK4matchCaloJet_j2", jetPtAK4matchCaloJet->at(sortedJetIdx[1]));
       fillVariableWithValue( "jetJecAK4_j2", jecFactors[sortedJetIdx[1]]); 
       fillVariableWithValue( "jetJecUncAK4_j2", jecUncertainty[sortedJetIdx[1]] );
       fillVariableWithValue( "jetCSVAK4_j2", jetCSVAK4->at(sortedJetIdx[1]) );
       fillVariableWithValue("jetHflavour_j2",hFlavourAK4->at(sortedJetIdx[1]));

       //jetID
       fillVariableWithValue( "neutrHadEnFrac_j2", jetNhfAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "chargedHadEnFrac_j2", jetChfAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "photonEnFrac_j2", jetPhfAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "eleEnFract_j2", jetElfAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "muEnFract_j2", jetMufAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "neutrElectromFrac_j2", jetNemfAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "chargedElectromFrac_j2", jetCemfAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "chargedMult_j2", chMultAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "neutrMult_j2", neMultAK4->at(sortedJetIdx[1]));
       fillVariableWithValue( "photonMult_j2", phoMultAK4->at(sortedJetIdx[1]));

       fillVariableWithValue( "IdTight_j3",idTAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "pTAK4_j3", AK4jets[2].Pt() );
       fillVariableWithValue( "etaAK4_j3", AK4jets[2].Eta());
       fillVariableWithValue( "phiAK4_j3", AK4jets[2].Phi());
       //fillVariableWithValue( "jetPtAK4matchCaloJet_j3", jetPtAK4matchCaloJet->at(sortedJetIdx[2]));
       fillVariableWithValue( "jetJecAK4_j3", jecFactors[sortedJetIdx[2]]); 
       fillVariableWithValue( "jetJecUncAK4_j3", jecUncertainty[sortedJetIdx[2]] );
       fillVariableWithValue( "jetCSVAK4_j3", jetCSVAK4->at(sortedJetIdx[2]) );
       fillVariableWithValue("jetHflavour_j3",hFlavourAK4->at(sortedJetIdx[2]));

       //jetID
       fillVariableWithValue( "neutrHadEnFrac_j3", jetNhfAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "chargedHadEnFrac_j3", jetChfAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "photonEnFrac_j3", jetPhfAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "eleEnFract_j3", jetElfAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "muEnFract_j3", jetMufAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "neutrElectromFrac_j3", jetNemfAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "chargedElectromFrac_j3", jetCemfAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "chargedMult_j3", chMultAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "neutrMult_j3", neMultAK4->at(sortedJetIdx[2]));
       fillVariableWithValue( "photonMult_j3", phoMultAK4->at(sortedJetIdx[2]));
            
       fillVariableWithValue( "IdTight_j4",idTAK4->at(sortedJetIdx[3]));
       fillVariableWithValue( "pTAK4_j4", AK4jets[3].Pt() );
       fillVariableWithValue( "etaAK4_j4", AK4jets[3].Eta());
       fillVariableWithValue( "phiAK4_j4", AK4jets[3].Phi());
       //fillVariableWithValue( "jetPtAK4matchCaloJet_j4", jetPtAK4matchCaloJet->at(sortedJetIdx[3]));
       fillVariableWithValue( "jetJecAK4_j4", jecFactors[sortedJetIdx[3]]); 
       fillVariableWithValue( "jetJecUncAK4_j4", jecUncertainty[sortedJetIdx[3]] );
       fillVariableWithValue( "jetCSVAK4_j4", jetCSVAK4->at(sortedJetIdx[3]) );
       fillVariableWithValue("jetHflavour_j4",hFlavourAK4->at(sortedJetIdx[3]));

       //jetID
       fillVariableWithValue( "neutrHadEnFrac_j4", jetNhfAK4->at(sortedJetIdx[3]));
       fillVariableWithValue( "chargedHadEnFrac_j4", jetChfAK4->at(sortedJetIdx[3]));
       fillVariableWithValue( "photonEnFrac_j4", jetPhfAK4->at(sortedJetIdx[3]));
       fillVariableWithValue( "eleEnFract_j4", jetElfAK4->at(sortedJetIdx[3]));
       fillVariableWithValue( "muEnFract_j4", jetMufAK4->at(sortedJetIdx[3]));
       fillVariableWithValue( "neutrElectromFrac_j4", jetNemfAK4->at(sortedJetIdx[3]));
       fillVariableWithValue( "chargedElectromFrac_j4", jetCemfAK4->at(sortedJetIdx[3]));
       fillVariableWithValue( "chargedMult_j4", chMultAK4->at(sortedJetIdx[3]));
       fillVariableWithValue( "neutrMult_j4", neMultAK4->at(sortedJetIdx[3]));
       fillVariableWithValue( "photonMult_j4", phoMultAK4->at(sortedJetIdx[3]));
      
       //dijet MjjAK4_1=MjjAK4_a1;
       //MjjAK4_2=MjjAK4_a2;
       //M4J_AK4=M4J_AK4_a;
       fillVariableWithValue( "Dijet_MassAK4_1", MJJAK4_1) ;
       fillVariableWithValue( "Dijet_MassAK4_2", MJJAK4_2) ;  
       fillVariableWithValue( "FourjetMass", M4J_AK4) ; 
       fillVariableWithValue("alpha",Maverage/M4J_AK4);
       fillVariableWithValue("Masymmetry" ,Masymmetry);
       fillVariableWithValue("Maverage", Maverage);
       fillVariableWithValue("DeltaEtaJJAK4", DeltaEtaJJAK4);
       fillVariableWithValue("DeltaRAK4_First",DeltaRAK4_First);
       fillVariableWithValue("DeltaRAK4_Second",DeltaRAK4_Second);
       fillVariableWithValue("DeltaPhiJJAK4",DeltaPhiJJAK4);
       fillVariableWithValue("ETA_1",ETA_1);
       fillVariableWithValue("ETA_2",ETA_2);
       fillVariableWithValue("Rapidity_1",Rapidity_1);
       fillVariableWithValue("Rapidity_2",Rapidity_2);
       fillVariableWithValue("DeltaRapidity",DeltaRapidity);
       fillVariableWithValue("PT_firstcomb_1",PT_firstcomb_1);
       fillVariableWithValue("PT_firstcomb_2",PT_firstcomb_2);
       fillVariableWithValue("PT_secondcomb_1",PT_secondcomb_1);
       fillVariableWithValue("PT_secondcomb_2",PT_secondcomb_2);
       fillVariableWithValue("DDR",DDR);
       fillVariableWithValue("DeltaR",DeltaR);
       fillVariableWithValue("Delta_1", Delta_1);
       fillVariableWithValue("Delta_2", Delta_2);
          
     }//end of 4-jets 

     if( widejets.size() >= 1 ){
         fillVariableWithValue( "pTWJ_j1", widejets[0].Pt() );
         fillVariableWithValue( "etaWJ_j1", widejets[0].Eta());
	 //no cuts on these variables, just to store in output
         fillVariableWithValue( "massWJ_j1", widejets[0].M());
         fillVariableWithValue( "phiWJ_j1", widejets[0].Phi());
       }

     if( widejets.size() >= 2 ){
         fillVariableWithValue( "pTWJ_j2", widejets[1].Pt() );
         fillVariableWithValue( "etaWJ_j2", widejets[1].Eta());
	 fillVariableWithValue( "deltaETAjj", DeltaEtaJJWide ) ;
         fillVariableWithValue( "mjj", MJJWide ) ;
         fillVariableWithValue( "mjj_shiftJEC", MJJWide_shift ) ;
	 //no cuts on these variables, just to store in output
         fillVariableWithValue( "massWJ_j2", widejets[1].M());
         fillVariableWithValue( "phiWJ_j2", widejets[1].Phi());	
	 //dijet
         fillVariableWithValue( "CosThetaStarWJ", TMath::TanH( (widejets[0].Eta()-widejets[1].Eta())/2 )); 
	 fillVariableWithValue( "deltaPHIjj", DeltaPhiJJWide ) ;
	 //fillVariableWithValue( "Dijet_MassAK8", mjjAK8 ) ;  
	 //fillVariableWithValue( "Dijet_MassC", mjjCA8 ) ;
	 // if(wdijet.M()<1){
	 //    std::cout << " INV MASS IS " << wdijet.M() << std::endl;
	 //    std::cout << " Delta Eta IS " << DeltaEtaJJWide << " n is  " << widejets.size() << std::endl;
	 //    std::cout << " INV MASS FROM NTUPLE AK8 " << mjjAK8 << std::endl;
	 //    //std::cout << " INV MASS FROM NTUPLE CA8 " << mjjCA8 << std::endl;
       }


     //no cuts on these variables, just to store in output
     if(!isData)
       fillVariableWithValue("trueVtx",PileupInteractions->at(idx_InTimeBX));
     else if(isData)
       fillVariableWithValue("trueVtx",999);     

     fillVariableWithValue("MET",met);
     //double METoverHTAK4=double(met/htAK4);
     double METoverHTAK4=double(met/HTak4);
     fillVariableWithValue("METoverHTAK4",METoverHTAK4);
     //fillVariableWithValue("HTAK4",htAK4);
     fillVariableWithValue("HTAK4",HTak4);
     fillVariableWithValue("ptHat",ptHat);

     int NtriggerBits = triggerResult->size();
     //cout << " NtriggerBits is " <<  NtriggerBits << " isData " << isData  << endl;
     if( NtriggerBits > 0 && isData )//change this 11/7/2017
       fillVariableWithValue("passHLT_PFHT780",triggerResult->at(triggerMap_.find("HLT_PFHT780_v*")->second));
     if( NtriggerBits > 1 && isData)
       fillVariableWithValue("passHLT_PFHT890",triggerResult->at(triggerMap_.find("HLT_PFHT890_v*")->second));
     if( NtriggerBits > 2 && isData)
       fillVariableWithValue("passHLT_PFHT1050",triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second));
     if( NtriggerBits > 3 && isData)
       fillVariableWithValue("passHLT_PFJet400",triggerResult->at(triggerMap_.find("HLT_PFJet400_v*")->second));
     if( NtriggerBits > 4 && isData)
       fillVariableWithValue("passHLT_PFJet450",triggerResult->at(triggerMap_.find("HLT_PFJet450_v*")->second));
     if( NtriggerBits > 5 && isData)
       fillVariableWithValue("passHLT_PFJet500",triggerResult->at(triggerMap_.find("HLT_PFJet500_v*")->second));
     if( NtriggerBits > 6 && isData)
       fillVariableWithValue("passHLT_PFJet550",triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second));
     if( NtriggerBits > 7 && isData)
       fillVariableWithValue("passHLT_Mu50",triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second));
     if( NtriggerBits > 8 && isData)
       fillVariableWithValue("passHLT_AK8PFJet320",triggerResult->at(triggerMap_.find("HLT_AK8PFJet320_v*")->second));
     if( NtriggerBits > 9 && isData)
       fillVariableWithValue("passHLT_AK8PFJet400",triggerResult->at(triggerMap_.find("HLT_AK8PFJet400_v*")->second));
     if( NtriggerBits > 10 && isData)
       fillVariableWithValue("passHLT_AK8PFJet450",triggerResult->at(triggerMap_.find("HLT_AK8PFJet450_v*")->second));
     if( NtriggerBits > 11 && isData)
       fillVariableWithValue("passHLT_AK8PFJet500",triggerResult->at(triggerMap_.find("HLT_AK8PFJet500_v*")->second));
     if( NtriggerBits > 12 && isData)
       fillVariableWithValue("passHLT_AK8PFJet550",triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second));
     if( NtriggerBits > 13 && isData)
       fillVariableWithValue("passHLT_CaloJet500_NoJetID",triggerResult->at(triggerMap_.find("HLT_CaloJet500_NoJetID_v*")->second));
     if( NtriggerBits > 14 && isData)
       fillVariableWithValue("passHLT_CaloJet550_NoJetID",triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second));
  
     // Evaluate cuts (but do not apply them)
     evaluateCuts();
     
     // optional call to fill a skim with the full content of the input roottuple
     //if( passedCut("nJetFinal") ) fillSkimTree();

  
bool fullAnalysis_dR2 = ( passedCut("PassJSON")
			   && passedCut("nVtx") 
			   && passedCut("IdTight_j1")
			   && passedCut("IdTight_j2")
                           && passedCut("IdTight_j3")
			   && passedCut("IdTight_j4")
                           && getVariableValue("pTAK4_j1")  > getPreCutValue1("pTAK4_j1_forTrig")
                           && getVariableValue("pTAK4_j2")   > getPreCutValue1("pTAK4_j2_forTrig") 
                           && getVariableValue("pTAK4_j3")    > getPreCutValue1("pTAK4_j3_forTrig")
                           && getVariableValue("pTAK4_j4")   > getPreCutValue1("pTAK4_j4_forTrig") 
                          && getVariableValue("etaAK4_j1")   > getPreCutValue1("etaAK4_j1_forTrig")
                           && getVariableValue("etaAK4_j1")   < getPreCutValue2("etaAK4_j1_forTrig")
                       && getVariableValue("etaAK4_j2")   > getPreCutValue1("etaAK4_j2_forTrig")
                           && getVariableValue("etaAK4_j2")   < getPreCutValue2("etaAK4_j2_forTrig")  
                        && getVariableValue("etaAK4_j3")   > getPreCutValue1("etaAK4_j3_forTrig")
                           && getVariableValue("etaAK4_j3")   < getPreCutValue2("etaAK4_j3_forTrig")   
                          && getVariableValue("etaAK4_j4")   > getPreCutValue1("etaAK4_j4_forTrig")
                           && getVariableValue("etaAK4_j4")   < getPreCutValue2("etaAK4_j4_forTrig") 
                          && passedCut("nJet")
                           && getVariableValue("DeltaEtaJJAK4")  <  getPreCutValue1("DetaJJforTrig")
                           &&  getVariableValue("Masymmetry")  <  getPreCutValue1("MasymmetryforTrig")
                           && getVariableValue("DeltaRAK4_First")  <  getPreCutValue1("DeltaR1_2_forTrig")
                            && getVariableValue("DeltaRAK4_Second")  <  getPreCutValue1("DeltaR2_2_forTrig"));
                         


bool fullAnalysis_dR2_alpha1 = ( passedCut("PassJSON")
			   && passedCut("nVtx") 
			   && passedCut("IdTight_j1")
			   && passedCut("IdTight_j2")
                           && passedCut("IdTight_j3")
			   && passedCut("IdTight_j4")
                           && getVariableValue("pTAK4_j1")  > getPreCutValue1("pTAK4_j1_forTrig")
                           && getVariableValue("pTAK4_j2")   > getPreCutValue1("pTAK4_j2_forTrig") 
                           && getVariableValue("pTAK4_j3")    > getPreCutValue1("pTAK4_j3_forTrig")
                           && getVariableValue("pTAK4_j4")   > getPreCutValue1("pTAK4_j4_forTrig") 
                          && getVariableValue("etaAK4_j1")   > getPreCutValue1("etaAK4_j1_forTrig")
                           && getVariableValue("etaAK4_j1")   < getPreCutValue2("etaAK4_j1_forTrig")
                       && getVariableValue("etaAK4_j2")   > getPreCutValue1("etaAK4_j2_forTrig")
                           && getVariableValue("etaAK4_j2")   < getPreCutValue2("etaAK4_j2_forTrig")  
                        && getVariableValue("etaAK4_j3")   > getPreCutValue1("etaAK4_j3_forTrig")
                           && getVariableValue("etaAK4_j3")   < getPreCutValue2("etaAK4_j3_forTrig")   
                          && getVariableValue("etaAK4_j4")   > getPreCutValue1("etaAK4_j4_forTrig")
                           && getVariableValue("etaAK4_j4")   < getPreCutValue2("etaAK4_j4_forTrig") 
                          && passedCut("nJet")
                           && getVariableValue("DeltaEtaJJAK4")  <  getPreCutValue1("DetaJJforTrig")
                           &&  getVariableValue("Masymmetry")  <  getPreCutValue1("MasymmetryforTrig")
                           && getVariableValue("DeltaRAK4_First")  <  getPreCutValue1("DeltaR1_2_forTrig")
                            && getVariableValue("DeltaRAK4_Second")  <  getPreCutValue1("DeltaR2_2_forTrig")
                            && getVariableValue("alpha")  >  getPreCutValue1("alpha1_forTrig")
                            && getVariableValue("alpha")  <  getPreCutValue2("alpha1_forTrig"));



bool fullAnalysis_dR2_alpha2 = ( passedCut("PassJSON")
			   && passedCut("nVtx") 
			   && passedCut("IdTight_j1")
			   && passedCut("IdTight_j2")
                           && passedCut("IdTight_j3")
			   && passedCut("IdTight_j4")
                           && getVariableValue("pTAK4_j1")  > getPreCutValue1("pTAK4_j1_forTrig")
                           && getVariableValue("pTAK4_j2")   > getPreCutValue1("pTAK4_j2_forTrig") 
                           && getVariableValue("pTAK4_j3")    > getPreCutValue1("pTAK4_j3_forTrig")
                           && getVariableValue("pTAK4_j4")   > getPreCutValue1("pTAK4_j4_forTrig") 
                          && getVariableValue("etaAK4_j1")   > getPreCutValue1("etaAK4_j1_forTrig")
                           && getVariableValue("etaAK4_j1")   < getPreCutValue2("etaAK4_j1_forTrig")
                       && getVariableValue("etaAK4_j2")   > getPreCutValue1("etaAK4_j2_forTrig")
                           && getVariableValue("etaAK4_j2")   < getPreCutValue2("etaAK4_j2_forTrig")  
                        && getVariableValue("etaAK4_j3")   > getPreCutValue1("etaAK4_j3_forTrig")
                           && getVariableValue("etaAK4_j3")   < getPreCutValue2("etaAK4_j3_forTrig")   
                          && getVariableValue("etaAK4_j4")   > getPreCutValue1("etaAK4_j4_forTrig")
                           && getVariableValue("etaAK4_j4")   < getPreCutValue2("etaAK4_j4_forTrig") 
                          && passedCut("nJet")
                           && getVariableValue("DeltaEtaJJAK4")  <  getPreCutValue1("DetaJJforTrig")
                           &&  getVariableValue("Masymmetry")  <  getPreCutValue1("MasymmetryforTrig")
                           && getVariableValue("DeltaRAK4_First")  <  getPreCutValue1("DeltaR1_2_forTrig")
                            && getVariableValue("DeltaRAK4_Second")  <  getPreCutValue1("DeltaR2_2_forTrig")
                            && getVariableValue("alpha")  >  getPreCutValue1("alpha2_forTrig")
                            && getVariableValue("alpha")  <  getPreCutValue2("alpha2_forTrig"));



bool fullAnalysis_dR2_alpha3 = ( passedCut("PassJSON")
			   && passedCut("nVtx") 
			   && passedCut("IdTight_j1")
			   && passedCut("IdTight_j2")
                           && passedCut("IdTight_j3")
			   && passedCut("IdTight_j4")
                           && getVariableValue("pTAK4_j1")  > getPreCutValue1("pTAK4_j1_forTrig")
                           && getVariableValue("pTAK4_j2")   > getPreCutValue1("pTAK4_j2_forTrig") 
                           && getVariableValue("pTAK4_j3")    > getPreCutValue1("pTAK4_j3_forTrig")
                           && getVariableValue("pTAK4_j4")   > getPreCutValue1("pTAK4_j4_forTrig") 
                          && getVariableValue("etaAK4_j1")   > getPreCutValue1("etaAK4_j1_forTrig")
                           && getVariableValue("etaAK4_j1")   < getPreCutValue2("etaAK4_j1_forTrig")
                       && getVariableValue("etaAK4_j2")   > getPreCutValue1("etaAK4_j2_forTrig")
                           && getVariableValue("etaAK4_j2")   < getPreCutValue2("etaAK4_j2_forTrig")  
                        && getVariableValue("etaAK4_j3")   > getPreCutValue1("etaAK4_j3_forTrig")
                           && getVariableValue("etaAK4_j3")   < getPreCutValue2("etaAK4_j3_forTrig")   
                          && getVariableValue("etaAK4_j4")   > getPreCutValue1("etaAK4_j4_forTrig")
                           && getVariableValue("etaAK4_j4")   < getPreCutValue2("etaAK4_j4_forTrig") 
                          && passedCut("nJet")
                           && getVariableValue("DeltaEtaJJAK4")  <  getPreCutValue1("DetaJJforTrig")
                           &&  getVariableValue("Masymmetry")  <  getPreCutValue1("MasymmetryforTrig")
                           && getVariableValue("DeltaRAK4_First")  <  getPreCutValue1("DeltaR1_2_forTrig")
                            && getVariableValue("DeltaRAK4_Second")  <  getPreCutValue1("DeltaR2_2_forTrig")
                            && getVariableValue("alpha")  >  getPreCutValue1("alpha3_forTrig")
                            && getVariableValue("alpha")  <  getPreCutValue2("alpha3_forTrig"));



bool fullAnalysis_dR2_alpha4 = ( passedCut("PassJSON")
			   && passedCut("nVtx") 
			   && passedCut("IdTight_j1")
			   && passedCut("IdTight_j2")
                           && passedCut("IdTight_j3")
			   && passedCut("IdTight_j4")
                           && getVariableValue("pTAK4_j1")  > getPreCutValue1("pTAK4_j1_forTrig")
                           && getVariableValue("pTAK4_j2")   > getPreCutValue1("pTAK4_j2_forTrig") 
                           && getVariableValue("pTAK4_j3")    > getPreCutValue1("pTAK4_j3_forTrig")
                           && getVariableValue("pTAK4_j4")   > getPreCutValue1("pTAK4_j4_forTrig") 
                          && getVariableValue("etaAK4_j1")   > getPreCutValue1("etaAK4_j1_forTrig")
                           && getVariableValue("etaAK4_j1")   < getPreCutValue2("etaAK4_j1_forTrig")
                       && getVariableValue("etaAK4_j2")   > getPreCutValue1("etaAK4_j2_forTrig")
                           && getVariableValue("etaAK4_j2")   < getPreCutValue2("etaAK4_j2_forTrig")  
                        && getVariableValue("etaAK4_j3")   > getPreCutValue1("etaAK4_j3_forTrig")
                           && getVariableValue("etaAK4_j3")   < getPreCutValue2("etaAK4_j3_forTrig")   
                          && getVariableValue("etaAK4_j4")   > getPreCutValue1("etaAK4_j4_forTrig")
                           && getVariableValue("etaAK4_j4")   < getPreCutValue2("etaAK4_j4_forTrig") 
                          && passedCut("nJet")
                           && getVariableValue("DeltaEtaJJAK4")  <  getPreCutValue1("DetaJJforTrig")
                           &&  getVariableValue("Masymmetry")  <  getPreCutValue1("MasymmetryforTrig")
                           && getVariableValue("DeltaRAK4_First")  <  getPreCutValue1("DeltaR1_2_forTrig")
                            && getVariableValue("DeltaRAK4_Second")  <  getPreCutValue1("DeltaR2_2_forTrig")
                            && getVariableValue("alpha")  >  getPreCutValue1("alpha4_forTrig")
                            && getVariableValue("alpha")  <  getPreCutValue2("alpha4_forTrig"));



bool fullAnalysis_dR2_alpha5 = ( passedCut("PassJSON")
			   && passedCut("nVtx") 
			   && passedCut("IdTight_j1")
			   && passedCut("IdTight_j2")
                           && passedCut("IdTight_j3")
			   && passedCut("IdTight_j4")
                           && getVariableValue("pTAK4_j1")  > getPreCutValue1("pTAK4_j1_forTrig")
                           && getVariableValue("pTAK4_j2")   > getPreCutValue1("pTAK4_j2_forTrig") 
                           && getVariableValue("pTAK4_j3")    > getPreCutValue1("pTAK4_j3_forTrig")
                           && getVariableValue("pTAK4_j4")   > getPreCutValue1("pTAK4_j4_forTrig") 
                          && getVariableValue("etaAK4_j1")   > getPreCutValue1("etaAK4_j1_forTrig")
                           && getVariableValue("etaAK4_j1")   < getPreCutValue2("etaAK4_j1_forTrig")
                       && getVariableValue("etaAK4_j2")   > getPreCutValue1("etaAK4_j2_forTrig")
                           && getVariableValue("etaAK4_j2")   < getPreCutValue2("etaAK4_j2_forTrig")  
                        && getVariableValue("etaAK4_j3")   > getPreCutValue1("etaAK4_j3_forTrig")
                           && getVariableValue("etaAK4_j3")   < getPreCutValue2("etaAK4_j3_forTrig")   
                          && getVariableValue("etaAK4_j4")   > getPreCutValue1("etaAK4_j4_forTrig")
                           && getVariableValue("etaAK4_j4")   < getPreCutValue2("etaAK4_j4_forTrig") 
                          && passedCut("nJet")
                           && getVariableValue("DeltaEtaJJAK4")  <  getPreCutValue1("DetaJJforTrig")
                           &&  getVariableValue("Masymmetry")  <  getPreCutValue1("MasymmetryforTrig")
                           && getVariableValue("DeltaRAK4_First")  <  getPreCutValue1("DeltaR1_2_forTrig")
                            && getVariableValue("DeltaRAK4_Second")  <  getPreCutValue1("DeltaR2_2_forTrig")
                            && getVariableValue("alpha")  >  getPreCutValue1("alpha5_forTrig")
                            && getVariableValue("alpha")  <  getPreCutValue2("alpha5_forTrig"));



bool fullAnalysis_dR2_alpha6 = ( passedCut("PassJSON")
			   && passedCut("nVtx") 
			   && passedCut("IdTight_j1")
			   && passedCut("IdTight_j2")
                           && passedCut("IdTight_j3")
			   && passedCut("IdTight_j4")
                           && getVariableValue("pTAK4_j1")  > getPreCutValue1("pTAK4_j1_forTrig")
                           && getVariableValue("pTAK4_j2")   > getPreCutValue1("pTAK4_j2_forTrig") 
                           && getVariableValue("pTAK4_j3")    > getPreCutValue1("pTAK4_j3_forTrig")
                           && getVariableValue("pTAK4_j4")   > getPreCutValue1("pTAK4_j4_forTrig") 
                          && getVariableValue("etaAK4_j1")   > getPreCutValue1("etaAK4_j1_forTrig")
                           && getVariableValue("etaAK4_j1")   < getPreCutValue2("etaAK4_j1_forTrig")
                       && getVariableValue("etaAK4_j2")   > getPreCutValue1("etaAK4_j2_forTrig")
                           && getVariableValue("etaAK4_j2")   < getPreCutValue2("etaAK4_j2_forTrig")  
                        && getVariableValue("etaAK4_j3")   > getPreCutValue1("etaAK4_j3_forTrig")
                           && getVariableValue("etaAK4_j3")   < getPreCutValue2("etaAK4_j3_forTrig")   
                          && getVariableValue("etaAK4_j4")   > getPreCutValue1("etaAK4_j4_forTrig")
                           && getVariableValue("etaAK4_j4")   < getPreCutValue2("etaAK4_j4_forTrig") 
                          && passedCut("nJet")
                           && getVariableValue("DeltaEtaJJAK4")  <  getPreCutValue1("DetaJJforTrig")
                           &&  getVariableValue("Masymmetry")  <  getPreCutValue1("MasymmetryforTrig")
                           && getVariableValue("DeltaRAK4_First")  <  getPreCutValue1("DeltaR1_2_forTrig")
                            && getVariableValue("DeltaRAK4_Second")  <  getPreCutValue1("DeltaR2_2_forTrig")
                            && getVariableValue("alpha")  >  getPreCutValue1("alpha6_forTrig")
                            && getVariableValue("alpha")  <  getPreCutValue2("alpha6_forTrig"));




bool fullAnalysis_dR2_alpha7 = ( passedCut("PassJSON")
			   && passedCut("nVtx") 
			   && passedCut("IdTight_j1")
			   && passedCut("IdTight_j2")
                           && passedCut("IdTight_j3")
			   && passedCut("IdTight_j4")
                           && getVariableValue("pTAK4_j1")  > getPreCutValue1("pTAK4_j1_forTrig")
                           && getVariableValue("pTAK4_j2")   > getPreCutValue1("pTAK4_j2_forTrig") 
                           && getVariableValue("pTAK4_j3")    > getPreCutValue1("pTAK4_j3_forTrig")
                           && getVariableValue("pTAK4_j4")   > getPreCutValue1("pTAK4_j4_forTrig") 
                          && getVariableValue("etaAK4_j1")   > getPreCutValue1("etaAK4_j1_forTrig")
                           && getVariableValue("etaAK4_j1")   < getPreCutValue2("etaAK4_j1_forTrig")
                       && getVariableValue("etaAK4_j2")   > getPreCutValue1("etaAK4_j2_forTrig")
                           && getVariableValue("etaAK4_j2")   < getPreCutValue2("etaAK4_j2_forTrig")  
                        && getVariableValue("etaAK4_j3")   > getPreCutValue1("etaAK4_j3_forTrig")
                           && getVariableValue("etaAK4_j3")   < getPreCutValue2("etaAK4_j3_forTrig")   
                          && getVariableValue("etaAK4_j4")   > getPreCutValue1("etaAK4_j4_forTrig")
                           && getVariableValue("etaAK4_j4")   < getPreCutValue2("etaAK4_j4_forTrig") 
                          && passedCut("nJet")
                           && getVariableValue("DeltaEtaJJAK4")  <  getPreCutValue1("DetaJJforTrig")
                           &&  getVariableValue("Masymmetry")  <  getPreCutValue1("MasymmetryforTrig")
                           && getVariableValue("DeltaRAK4_First")  <  getPreCutValue1("DeltaR1_2_forTrig")
                            && getVariableValue("DeltaRAK4_Second")  <  getPreCutValue1("DeltaR2_2_forTrig")
                            && getVariableValue("alpha")  >  getPreCutValue1("alpha7_forTrig")
                            && getVariableValue("alpha")  <  getPreCutValue2("alpha7_forTrig"));


bool fullAnalysis_dR2_alpha8 = ( passedCut("PassJSON")
			   && passedCut("nVtx") 
			   && passedCut("IdTight_j1")
			   && passedCut("IdTight_j2")
                           && passedCut("IdTight_j3")
			   && passedCut("IdTight_j4")
                           && getVariableValue("pTAK4_j1")  > getPreCutValue1("pTAK4_j1_forTrig")
                           && getVariableValue("pTAK4_j2")   > getPreCutValue1("pTAK4_j2_forTrig") 
                           && getVariableValue("pTAK4_j3")    > getPreCutValue1("pTAK4_j3_forTrig")
                           && getVariableValue("pTAK4_j4")   > getPreCutValue1("pTAK4_j4_forTrig") 
                          && getVariableValue("etaAK4_j1")   > getPreCutValue1("etaAK4_j1_forTrig")
                           && getVariableValue("etaAK4_j1")   < getPreCutValue2("etaAK4_j1_forTrig")
                       && getVariableValue("etaAK4_j2")   > getPreCutValue1("etaAK4_j2_forTrig")
                           && getVariableValue("etaAK4_j2")   < getPreCutValue2("etaAK4_j2_forTrig")  
                        && getVariableValue("etaAK4_j3")   > getPreCutValue1("etaAK4_j3_forTrig")
                           && getVariableValue("etaAK4_j3")   < getPreCutValue2("etaAK4_j3_forTrig")   
                          && getVariableValue("etaAK4_j4")   > getPreCutValue1("etaAK4_j4_forTrig")
                           && getVariableValue("etaAK4_j4")   < getPreCutValue2("etaAK4_j4_forTrig") 
                          && passedCut("nJet")
                           && getVariableValue("DeltaEtaJJAK4")  <  getPreCutValue1("DetaJJforTrig")
                           &&  getVariableValue("Masymmetry")  <  getPreCutValue1("MasymmetryforTrig")
                           && getVariableValue("DeltaRAK4_First")  <  getPreCutValue1("DeltaR1_2_forTrig")
                            && getVariableValue("DeltaRAK4_Second")  <  getPreCutValue1("DeltaR2_2_forTrig")
                            && getVariableValue("alpha")  >  getPreCutValue1("alpha8_forTrig")
                            && getVariableValue("alpha")  <  getPreCutValue2("alpha8_forTrig"));


bool fullAnalysis_dR2_alpha9 = ( passedCut("PassJSON")
			   && passedCut("nVtx") 
			   && passedCut("IdTight_j1")
			   && passedCut("IdTight_j2")
                           && passedCut("IdTight_j3")
			   && passedCut("IdTight_j4")
                           && getVariableValue("pTAK4_j1")  > getPreCutValue1("pTAK4_j1_forTrig")
                           && getVariableValue("pTAK4_j2")   > getPreCutValue1("pTAK4_j2_forTrig") 
                           && getVariableValue("pTAK4_j3")    > getPreCutValue1("pTAK4_j3_forTrig")
                           && getVariableValue("pTAK4_j4")   > getPreCutValue1("pTAK4_j4_forTrig") 
                          && getVariableValue("etaAK4_j1")   > getPreCutValue1("etaAK4_j1_forTrig")
                           && getVariableValue("etaAK4_j1")   < getPreCutValue2("etaAK4_j1_forTrig")
                       && getVariableValue("etaAK4_j2")   > getPreCutValue1("etaAK4_j2_forTrig")
                           && getVariableValue("etaAK4_j2")   < getPreCutValue2("etaAK4_j2_forTrig")  
                        && getVariableValue("etaAK4_j3")   > getPreCutValue1("etaAK4_j3_forTrig")
                           && getVariableValue("etaAK4_j3")   < getPreCutValue2("etaAK4_j3_forTrig")   
                          && getVariableValue("etaAK4_j4")   > getPreCutValue1("etaAK4_j4_forTrig")
                           && getVariableValue("etaAK4_j4")   < getPreCutValue2("etaAK4_j4_forTrig") 
                          && passedCut("nJet")
                           && getVariableValue("DeltaEtaJJAK4")  <  getPreCutValue1("DetaJJforTrig")
                           &&  getVariableValue("Masymmetry")  <  getPreCutValue1("MasymmetryforTrig")
                           && getVariableValue("DeltaRAK4_First")  <  getPreCutValue1("DeltaR1_2_forTrig")
                            && getVariableValue("DeltaRAK4_Second")  <  getPreCutValue1("DeltaR2_2_forTrig")
                            && getVariableValue("alpha")  >  getPreCutValue1("alpha9_forTrig")
                            && getVariableValue("alpha")  <  getPreCutValue2("alpha9_forTrig"));


bool fullAnalysis_dR2_alpha10 = ( passedCut("PassJSON")
			   && passedCut("nVtx") 
			   && passedCut("IdTight_j1")
			   && passedCut("IdTight_j2")
                           && passedCut("IdTight_j3")
			   && passedCut("IdTight_j4")
                           && getVariableValue("pTAK4_j1")  > getPreCutValue1("pTAK4_j1_forTrig")
                           && getVariableValue("pTAK4_j2")   > getPreCutValue1("pTAK4_j2_forTrig") 
                           && getVariableValue("pTAK4_j3")    > getPreCutValue1("pTAK4_j3_forTrig")
                           && getVariableValue("pTAK4_j4")   > getPreCutValue1("pTAK4_j4_forTrig") 
                          && getVariableValue("etaAK4_j1")   > getPreCutValue1("etaAK4_j1_forTrig")
                           && getVariableValue("etaAK4_j1")   < getPreCutValue2("etaAK4_j1_forTrig")
                       && getVariableValue("etaAK4_j2")   > getPreCutValue1("etaAK4_j2_forTrig")
                           && getVariableValue("etaAK4_j2")   < getPreCutValue2("etaAK4_j2_forTrig")  
                        && getVariableValue("etaAK4_j3")   > getPreCutValue1("etaAK4_j3_forTrig")
                           && getVariableValue("etaAK4_j3")   < getPreCutValue2("etaAK4_j3_forTrig")   
                          && getVariableValue("etaAK4_j4")   > getPreCutValue1("etaAK4_j4_forTrig")
                           && getVariableValue("etaAK4_j4")   < getPreCutValue2("etaAK4_j4_forTrig") 
                          && passedCut("nJet")
                           && getVariableValue("DeltaEtaJJAK4")  <  getPreCutValue1("DetaJJforTrig")
                           &&  getVariableValue("Masymmetry")  <  getPreCutValue1("MasymmetryforTrig")
                           && getVariableValue("DeltaRAK4_First")  <  getPreCutValue1("DeltaR1_2_forTrig")
                            && getVariableValue("DeltaRAK4_Second")  <  getPreCutValue1("DeltaR2_2_forTrig")
                            && getVariableValue("alpha")  >  getPreCutValue1("alpha10_forTrig")
                            && getVariableValue("alpha")  <  getPreCutValue2("alpha10_forTrig"));


bool fullAnalysis_dR2_alpha11 = ( passedCut("PassJSON")
			   && passedCut("nVtx") 
			   && passedCut("IdTight_j1")
			   && passedCut("IdTight_j2")
                           && passedCut("IdTight_j3")
			   && passedCut("IdTight_j4")
                           && getVariableValue("pTAK4_j1")  > getPreCutValue1("pTAK4_j1_forTrig")
                           && getVariableValue("pTAK4_j2")   > getPreCutValue1("pTAK4_j2_forTrig") 
                           && getVariableValue("pTAK4_j3")    > getPreCutValue1("pTAK4_j3_forTrig")
                           && getVariableValue("pTAK4_j4")   > getPreCutValue1("pTAK4_j4_forTrig") 
                          && getVariableValue("etaAK4_j1")   > getPreCutValue1("etaAK4_j1_forTrig")
                           && getVariableValue("etaAK4_j1")   < getPreCutValue2("etaAK4_j1_forTrig")
                       && getVariableValue("etaAK4_j2")   > getPreCutValue1("etaAK4_j2_forTrig")
                           && getVariableValue("etaAK4_j2")   < getPreCutValue2("etaAK4_j2_forTrig")  
                        && getVariableValue("etaAK4_j3")   > getPreCutValue1("etaAK4_j3_forTrig")
                           && getVariableValue("etaAK4_j3")   < getPreCutValue2("etaAK4_j3_forTrig")   
                          && getVariableValue("etaAK4_j4")   > getPreCutValue1("etaAK4_j4_forTrig")
                           && getVariableValue("etaAK4_j4")   < getPreCutValue2("etaAK4_j4_forTrig") 
                          && passedCut("nJet")
                           && getVariableValue("DeltaEtaJJAK4")  <  getPreCutValue1("DetaJJforTrig")
                           &&  getVariableValue("Masymmetry")  <  getPreCutValue1("MasymmetryforTrig")
                           && getVariableValue("DeltaRAK4_First")  <  getPreCutValue1("DeltaR1_2_forTrig")
                            && getVariableValue("DeltaRAK4_Second")  <  getPreCutValue1("DeltaR2_2_forTrig")
                            && getVariableValue("alpha")  >  getPreCutValue1("alpha11_forTrig")
                            && getVariableValue("alpha")  <  getPreCutValue2("alpha11_forTrig"));


bool fullAnalysis_dR2_alpha12 = ( passedCut("PassJSON")
			   && passedCut("nVtx") 
			   && passedCut("IdTight_j1")
			   && passedCut("IdTight_j2")
                           && passedCut("IdTight_j3")
			   && passedCut("IdTight_j4")
                           && getVariableValue("pTAK4_j1")  > getPreCutValue1("pTAK4_j1_forTrig")
                           && getVariableValue("pTAK4_j2")   > getPreCutValue1("pTAK4_j2_forTrig") 
                           && getVariableValue("pTAK4_j3")    > getPreCutValue1("pTAK4_j3_forTrig")
                           && getVariableValue("pTAK4_j4")   > getPreCutValue1("pTAK4_j4_forTrig") 
                          && getVariableValue("etaAK4_j1")   > getPreCutValue1("etaAK4_j1_forTrig")
                           && getVariableValue("etaAK4_j1")   < getPreCutValue2("etaAK4_j1_forTrig")
                       && getVariableValue("etaAK4_j2")   > getPreCutValue1("etaAK4_j2_forTrig")
                           && getVariableValue("etaAK4_j2")   < getPreCutValue2("etaAK4_j2_forTrig")  
                        && getVariableValue("etaAK4_j3")   > getPreCutValue1("etaAK4_j3_forTrig")
                           && getVariableValue("etaAK4_j3")   < getPreCutValue2("etaAK4_j3_forTrig")   
                          && getVariableValue("etaAK4_j4")   > getPreCutValue1("etaAK4_j4_forTrig")
                           && getVariableValue("etaAK4_j4")   < getPreCutValue2("etaAK4_j4_forTrig") 
                          && passedCut("nJet")
                           && getVariableValue("DeltaEtaJJAK4")  <  getPreCutValue1("DetaJJforTrig")
                           &&  getVariableValue("Masymmetry")  <  getPreCutValue1("MasymmetryforTrig")
                           && getVariableValue("DeltaRAK4_First")  <  getPreCutValue1("DeltaR1_2_forTrig")
                            && getVariableValue("DeltaRAK4_Second")  <  getPreCutValue1("DeltaR2_2_forTrig")
                            && getVariableValue("alpha")  >  getPreCutValue1("alpha12_forTrig")
                            && getVariableValue("alpha")  <  getPreCutValue2("alpha12_forTrig"));


bool fullAnalysis_dR2_alpha13 = ( passedCut("PassJSON")
			   && passedCut("nVtx") 
			   && passedCut("IdTight_j1")
			   && passedCut("IdTight_j2")
                           && passedCut("IdTight_j3")
			   && passedCut("IdTight_j4")
                           && getVariableValue("pTAK4_j1")  > getPreCutValue1("pTAK4_j1_forTrig")
                           && getVariableValue("pTAK4_j2")   > getPreCutValue1("pTAK4_j2_forTrig") 
                           && getVariableValue("pTAK4_j3")    > getPreCutValue1("pTAK4_j3_forTrig")
                           && getVariableValue("pTAK4_j4")   > getPreCutValue1("pTAK4_j4_forTrig") 
                          && getVariableValue("etaAK4_j1")   > getPreCutValue1("etaAK4_j1_forTrig")
                           && getVariableValue("etaAK4_j1")   < getPreCutValue2("etaAK4_j1_forTrig")
                       && getVariableValue("etaAK4_j2")   > getPreCutValue1("etaAK4_j2_forTrig")
                           && getVariableValue("etaAK4_j2")   < getPreCutValue2("etaAK4_j2_forTrig")  
                        && getVariableValue("etaAK4_j3")   > getPreCutValue1("etaAK4_j3_forTrig")
                           && getVariableValue("etaAK4_j3")   < getPreCutValue2("etaAK4_j3_forTrig")   
                          && getVariableValue("etaAK4_j4")   > getPreCutValue1("etaAK4_j4_forTrig")
                           && getVariableValue("etaAK4_j4")   < getPreCutValue2("etaAK4_j4_forTrig") 
                          && passedCut("nJet")
                           && getVariableValue("DeltaEtaJJAK4")  <  getPreCutValue1("DetaJJforTrig")
                           &&  getVariableValue("Masymmetry")  <  getPreCutValue1("MasymmetryforTrig")
                           && getVariableValue("DeltaRAK4_First")  <  getPreCutValue1("DeltaR1_2_forTrig")
                            && getVariableValue("DeltaRAK4_Second")  <  getPreCutValue1("DeltaR2_2_forTrig")
                            && getVariableValue("alpha")  >  getPreCutValue1("alpha13_forTrig"));
                           

                          



 if (fullAnalysis_dR2)
       {
	 h_mjj_HLTpass_dR2[0] -> Fill(M4J_AK4); //noTrig
h_CEMF_test1->Fill(jetCemfAK4->at(sortedJetIdx[0]));
h_CEMF_test2->Fill(jetCemfAK4->at(sortedJetIdx[1]));
	 if(isData && triggerResult->size()>10) // only run on data 
        // cout << " NtriggerBits is " <<  NtriggerBits << " isData 2 " << isData  << endl;
 
	   fillTriggerPlots_dR2(h_mjj_HLTpass_dR2,M4J_AK4);
	 
	 //cout << " NtriggerBits is " <<  NtriggerBits << " isData 3 " << isData  << endl;
	 

	


	 


       } //end full analysis including deltaEta


 if (fullAnalysis_dR2_alpha1)
       {
	 h_mjj_HLTpass_dR2_alpha1[0] -> Fill(M4J_AK4); //noTrig
h_CEMF_test1->Fill(jetCemfAK4->at(sortedJetIdx[0]));
h_CEMF_test2->Fill(jetCemfAK4->at(sortedJetIdx[1]));
	 if(isData && triggerResult->size()>10) // only run on data 
        // cout << " NtriggerBits is " <<  NtriggerBits << " isData 2 " << isData  << endl;
 
	   fillTriggerPlots_dR2_alpha1(h_mjj_HLTpass_dR2_alpha1,M4J_AK4);
	 
	 //cout << " NtriggerBits is " <<  NtriggerBits << " isData 3 " << isData  << endl;
	 

	 


       } //end full analysis including deltaEta alpha1



//alpha 2

if (fullAnalysis_dR2_alpha2)
       {
	 h_mjj_HLTpass_dR2_alpha2[0] -> Fill(M4J_AK4); //noTrig
h_CEMF_test1->Fill(jetCemfAK4->at(sortedJetIdx[0]));
h_CEMF_test2->Fill(jetCemfAK4->at(sortedJetIdx[1]));
	 if(isData && triggerResult->size()>10) // only run on data 
        // cout << " NtriggerBits is " <<  NtriggerBits << " isData 2 " << isData  << endl;
 
	   fillTriggerPlots_dR2_alpha2(h_mjj_HLTpass_dR2_alpha2,M4J_AK4);
	 
	 //cout << " NtriggerBits is " <<  NtriggerBits << " isData 3 " << isData  << endl;
	 

	

       } //end full analysis including deltaEta



//alpha3

if (fullAnalysis_dR2_alpha3)
       {
	 h_mjj_HLTpass_dR2_alpha3[0] -> Fill(M4J_AK4); //noTrig
h_CEMF_test1->Fill(jetCemfAK4->at(sortedJetIdx[0]));
h_CEMF_test2->Fill(jetCemfAK4->at(sortedJetIdx[1]));
	 if(isData && triggerResult->size()>10) // only run on data 
        // cout << " NtriggerBits is " <<  NtriggerBits << " isData 2 " << isData  << endl;
 
	   fillTriggerPlots_dR2_alpha3(h_mjj_HLTpass_dR2_alpha3,M4J_AK4);
	 
	 //cout << " NtriggerBits is " <<  NtriggerBits << " isData 3 " << isData  << endl;
	 

	
	 


       } //end full analysis including deltaEta



//alpha4


if (fullAnalysis_dR2_alpha4)
       {
	 h_mjj_HLTpass_dR2_alpha4[0] -> Fill(M4J_AK4); //noTrig
h_CEMF_test1->Fill(jetCemfAK4->at(sortedJetIdx[0]));
h_CEMF_test2->Fill(jetCemfAK4->at(sortedJetIdx[1]));
	 if(isData && triggerResult->size()>10) // only run on data 
        // cout << " NtriggerBits is " <<  NtriggerBits << " isData 2 " << isData  << endl;
 
	   fillTriggerPlots_dR2_alpha4(h_mjj_HLTpass_dR2_alpha4,M4J_AK4);
	 
	 //cout << " NtriggerBits is " <<  NtriggerBits << " isData 3 " << isData  << endl;
	 

	
	 


       } //end full analysis including deltaEta


//alpha 5


if (fullAnalysis_dR2_alpha5)
       {
	 h_mjj_HLTpass_dR2_alpha5[0] -> Fill(M4J_AK4); //noTrig
h_CEMF_test1->Fill(jetCemfAK4->at(sortedJetIdx[0]));
h_CEMF_test2->Fill(jetCemfAK4->at(sortedJetIdx[1]));
	 if(isData && triggerResult->size()>10) // only run on data 
        // cout << " NtriggerBits is " <<  NtriggerBits << " isData 2 " << isData  << endl;
 
	   fillTriggerPlots_dR2_alpha5(h_mjj_HLTpass_dR2_alpha5,M4J_AK4);
	 
	 //cout << " NtriggerBits is " <<  NtriggerBits << " isData 3 " << isData  << endl;
	 

	 
	 


       } //end full analysis including deltaEta

//alpha6


if (fullAnalysis_dR2_alpha6)
       {
	 h_mjj_HLTpass_dR2_alpha6[0] -> Fill(M4J_AK4); //noTrig
h_CEMF_test1->Fill(jetCemfAK4->at(sortedJetIdx[0]));
h_CEMF_test2->Fill(jetCemfAK4->at(sortedJetIdx[1]));
	 if(isData && triggerResult->size()>10) // only run on data 
        // cout << " NtriggerBits is " <<  NtriggerBits << " isData 2 " << isData  << endl;
 
	   fillTriggerPlots_dR2_alpha6(h_mjj_HLTpass_dR2_alpha6,M4J_AK4);
	 
	 //cout << " NtriggerBits is " <<  NtriggerBits << " isData 3 " << isData  << endl;
	 

	


       } //end full analysis including deltaEta





//alpha7

if (fullAnalysis_dR2_alpha7)
       {
	 h_mjj_HLTpass_dR2_alpha7[0] -> Fill(M4J_AK4); //noTrig
h_CEMF_test1->Fill(jetCemfAK4->at(sortedJetIdx[0]));
h_CEMF_test2->Fill(jetCemfAK4->at(sortedJetIdx[1]));
	 if(isData && triggerResult->size()>10) // only run on data 
        // cout << " NtriggerBits is " <<  NtriggerBits << " isData 2 " << isData  << endl;
 
	   fillTriggerPlots_dR2_alpha7(h_mjj_HLTpass_dR2_alpha7,M4J_AK4);
	 
	 //cout << " NtriggerBits is " <<  NtriggerBits << " isData 3 " << isData  << endl;
	 

	
	 


       } //end full analysis including deltaEta


//alpha 8


if (fullAnalysis_dR2_alpha8)
       {
	 h_mjj_HLTpass_dR2_alpha8[0] -> Fill(M4J_AK4); //noTrig
h_CEMF_test1->Fill(jetCemfAK4->at(sortedJetIdx[0]));
h_CEMF_test2->Fill(jetCemfAK4->at(sortedJetIdx[1]));
	 if(isData && triggerResult->size()>10) // only run on data 
        // cout << " NtriggerBits is " <<  NtriggerBits << " isData 2 " << isData  << endl;
 
	   fillTriggerPlots_dR2_alpha8(h_mjj_HLTpass_dR2_alpha8,M4J_AK4);
	 
	 //cout << " NtriggerBits is " <<  NtriggerBits << " isData 3 " << isData  << endl;
	 

	
	 


       } //end full analysis including deltaEta



//alpha 9


if (fullAnalysis_dR2_alpha9)
       {
	 h_mjj_HLTpass_dR2_alpha9[0] -> Fill(M4J_AK4); //noTrig
h_CEMF_test1->Fill(jetCemfAK4->at(sortedJetIdx[0]));
h_CEMF_test2->Fill(jetCemfAK4->at(sortedJetIdx[1]));
	 if(isData && triggerResult->size()>10) // only run on data 
        // cout << " NtriggerBits is " <<  NtriggerBits << " isData 2 " << isData  << endl;
 
	   fillTriggerPlots_dR2_alpha9(h_mjj_HLTpass_dR2_alpha9,M4J_AK4);
	 
	 //cout << " NtriggerBits is " <<  NtriggerBits << " isData 3 " << isData  << endl;
	 

	 
	 


       } //end full analysis including deltaEta

//alpha 10

if (fullAnalysis_dR2_alpha10)
       {
	 h_mjj_HLTpass_dR2_alpha10[0] -> Fill(M4J_AK4); //noTrig
h_CEMF_test1->Fill(jetCemfAK4->at(sortedJetIdx[0]));
h_CEMF_test2->Fill(jetCemfAK4->at(sortedJetIdx[1]));
	 if(isData && triggerResult->size()>10) // only run on data 
        // cout << " NtriggerBits is " <<  NtriggerBits << " isData 2 " << isData  << endl;
 
	   fillTriggerPlots_dR2_alpha10(h_mjj_HLTpass_dR2_alpha10,M4J_AK4);
	 
	 //cout << " NtriggerBits is " <<  NtriggerBits << " isData 3 " << isData  << endl;
	 

	 	 
  /*if(M4J_AK4>1607 && M4J_AK4<1687 &&  (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) {
cout << " event OR 1st " << evtNo << "run OR" << runNo << "lumi OR" << lumi << endl;



}

if (M4J_AK4>1607 && M4J_AK4<1687 && (triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second))) 
{cout.precision(25);
cout << " event 1st " << evtNo << "run" << runNo << "lumi" << lumi << endl;



}*/



       } //end full analysis including deltaEta

//alpha 11

if (fullAnalysis_dR2_alpha11)
       {
	 h_mjj_HLTpass_dR2_alpha11[0] -> Fill(M4J_AK4); //noTrig
h_CEMF_test1->Fill(jetCemfAK4->at(sortedJetIdx[0]));
h_CEMF_test2->Fill(jetCemfAK4->at(sortedJetIdx[1]));
	 if(isData && triggerResult->size()>10) // only run on data 
        // cout << " NtriggerBits is " <<  NtriggerBits << " isData 2 " << isData  << endl;
 
	   fillTriggerPlots_dR2_alpha11(h_mjj_HLTpass_dR2_alpha11,M4J_AK4);
	 
	 //cout << " NtriggerBits is " <<  NtriggerBits << " isData 3 " << isData  << endl;
	 

	 
	 


       } //end full analysis including deltaEta


//alpha12
if (fullAnalysis_dR2_alpha12)
       {
	 h_mjj_HLTpass_dR2_alpha12[0] -> Fill(M4J_AK4); //noTrig
h_CEMF_test1->Fill(jetCemfAK4->at(sortedJetIdx[0]));
h_CEMF_test2->Fill(jetCemfAK4->at(sortedJetIdx[1]));
	 if(isData && triggerResult->size()>10) // only run on data 
        // cout << " NtriggerBits is " <<  NtriggerBits << " isData 2 " << isData  << endl;
 
	   fillTriggerPlots_dR2_alpha12(h_mjj_HLTpass_dR2_alpha12,M4J_AK4);
	 
	 //cout << " NtriggerBits is " <<  NtriggerBits << " isData 3 " << isData  << endl;

//cout << "EDW " << endl;

	/* if(M4J_AK4>1770 && M4J_AK4<1856 &&  (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) {
cout << " event OR 1st " << evtNo << "run OR" << runNo << "lumi OR" << lumi << endl;



}

if (M4J_AK4>1770 && M4J_AK4<1856 && (triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second))) 
{cout.precision(25);
cout << " event 1st " << evtNo << "run" << runNo << "lumi" << lumi << endl;


cout << "pT_jet1 =  " << AK4jets[0].Pt() << "    eta_jet1 = " << AK4jets[0].Eta() << "\tphi_jet1 = " << AK4jets[0].Phi() << "  chf_jet1 = " << jetChfAK4->at(sortedJetIdx[0]) << "\tcemf_jet1 = " << jetCemfAK4->at(sortedJetIdx[0])  << "  nhf_jet1 = " << jetNhfAK4->at(sortedJetIdx[0]) << " nemf_jet1 = " << jetNemfAK4->at(sortedJetIdx[0]) << "\tmuf_jet1 = " << jetMufAK4->at(sortedJetIdx[0]) << " phf_jet1 = " << jetMufAK4->at(sortedJetIdx[0]) << "  NM = " << neMultAK4->at(sortedJetIdx[0]) << "CM = " << chMultAK4->at(sortedJetIdx[0])<< "PM = " << phoMultAK4->at(sortedJetIdx[0]) << endl;

cout << "pT_jet2 =  " << AK4jets[1].Pt() << "   eta_jet2 = " << AK4jets[1].Eta() << "\tphi_jet2 = " << AK4jets[1].Phi() << " chf_jet2 = " << jetChfAK4->at(sortedJetIdx[1]) << "\tcemf_jet2 = " << jetCemfAK4->at(sortedJetIdx[1])  << " nhf_jet2 = " << jetNhfAK4->at(sortedJetIdx[1]) << " nemf_jet2 = " << jetNemfAK4->at(sortedJetIdx[1]) << "\tmuf_jet2 = " << jetMufAK4->at(sortedJetIdx[1]) <<  " phf_jet2 = " << jetPhfAK4->at(sortedJetIdx[1]) << " NM = " << neMultAK4->at(sortedJetIdx[1]) << " CM = " << chMultAK4->at(sortedJetIdx[1])<< " PM = " << phoMultAK4->at(sortedJetIdx[1]) << endl;

cout << "pT_jet3 =  " << AK4jets[2].Pt() << "   eta_jet3 = " << AK4jets[2].Eta() << "\tphi_jet3 = " << AK4jets[2].Phi() << " chf_jet3 = " << jetChfAK4->at(sortedJetIdx[2]) << "\tcemf_jet3 = " << jetCemfAK4->at(sortedJetIdx[2])  << " nhf_jet3 = " << jetNhfAK4->at(sortedJetIdx[2]) << " nemf_jet3 = " << jetNemfAK4->at(sortedJetIdx[2]) << "\tmuf_jet3 = " << jetMufAK4->at(sortedJetIdx[2]) <<  " phf_jet3 = " << jetPhfAK4->at(sortedJetIdx[2]) << " NM = " << neMultAK4->at(sortedJetIdx[2]) << " CM = " << chMultAK4->at(sortedJetIdx[2])<< " PM = " << phoMultAK4->at(sortedJetIdx[2]) << endl;

cout << "pT_jet4 =  " << AK4jets[3].Pt() << "   eta_jet4 = " << AK4jets[3].Eta() << "\tphi_jet4 = " << AK4jets[3].Phi() << " chf_jet4 = " << jetChfAK4->at(sortedJetIdx[3]) << "\tcemf_jet4 = " << jetCemfAK4->at(sortedJetIdx[3])  << " nhf_jet4 = " << jetNhfAK4->at(sortedJetIdx[3]) << " nemf_jet4 = " << jetNemfAK4->at(sortedJetIdx[3]) << "\tmuf_jet4 = " << jetMufAK4->at(sortedJetIdx[3]) <<  " phf_jet4 = " << jetPhfAK4->at(sortedJetIdx[3]) << " NM = " << neMultAK4->at(sortedJetIdx[3]) << " CM = " << chMultAK4->at(sortedJetIdx[3])<< " PM = " << phoMultAK4->at(sortedJetIdx[3]) << endl;

}
*/	 


       } //end full analysis including deltaEta


if (fullAnalysis_dR2_alpha13)
       {
	 h_mjj_HLTpass_dR2_alpha13[0] -> Fill(M4J_AK4); //noTrig
h_CEMF_test1->Fill(jetCemfAK4->at(sortedJetIdx[0]));
h_CEMF_test2->Fill(jetCemfAK4->at(sortedJetIdx[1]));
	 if(isData && triggerResult->size()>10) // only run on data 
        // cout << " NtriggerBits is " <<  NtriggerBits << " isData 2 " << isData  << endl;
 
	   fillTriggerPlots_dR2_alpha13(h_mjj_HLTpass_dR2_alpha13,M4J_AK4);
	 
	 //cout << " NtriggerBits is " <<  NtriggerBits << " isData 3 " << isData  << endl;

//cout << "EDW " << endl;

	
	 if(M4J_AK4>1530 && M4J_AK4<1607 &&  (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) {
cout << " event OR 1st " << evtNo << "run OR" << runNo << "lumi OR" << lumi << endl;



}

if (M4J_AK4>1530 && M4J_AK4<1607 && (triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second))) 
{cout.precision(25);
cout << " event 1st " << evtNo << "run" << runNo << "lumi" << lumi << endl;


cout << "pT_jet1 =  " << AK4jets[0].Pt() << "    eta_jet1 = " << AK4jets[0].Eta() << "\tphi_jet1 = " << AK4jets[0].Phi() << "  chf_jet1 = " << jetChfAK4->at(sortedJetIdx[0]) << "\tcemf_jet1 = " << jetCemfAK4->at(sortedJetIdx[0])  << "  nhf_jet1 = " << jetNhfAK4->at(sortedJetIdx[0]) << " nemf_jet1 = " << jetNemfAK4->at(sortedJetIdx[0]) << "\tmuf_jet1 = " << jetMufAK4->at(sortedJetIdx[0]) << " phf_jet1 = " << jetMufAK4->at(sortedJetIdx[0]) << "  NM = " << neMultAK4->at(sortedJetIdx[0]) << "CM = " << chMultAK4->at(sortedJetIdx[0])<< "PM = " << phoMultAK4->at(sortedJetIdx[0]) << endl;

cout << "pT_jet2 =  " << AK4jets[1].Pt() << "   eta_jet2 = " << AK4jets[1].Eta() << "\tphi_jet2 = " << AK4jets[1].Phi() << " chf_jet2 = " << jetChfAK4->at(sortedJetIdx[1]) << "\tcemf_jet2 = " << jetCemfAK4->at(sortedJetIdx[1])  << " nhf_jet2 = " << jetNhfAK4->at(sortedJetIdx[1]) << " nemf_jet2 = " << jetNemfAK4->at(sortedJetIdx[1]) << "\tmuf_jet2 = " << jetMufAK4->at(sortedJetIdx[1]) <<  " phf_jet2 = " << jetPhfAK4->at(sortedJetIdx[1]) << " NM = " << neMultAK4->at(sortedJetIdx[1]) << " CM = " << chMultAK4->at(sortedJetIdx[1])<< " PM = " << phoMultAK4->at(sortedJetIdx[1]) << endl;

cout << "pT_jet3 =  " << AK4jets[2].Pt() << "   eta_jet3 = " << AK4jets[2].Eta() << "\tphi_jet3 = " << AK4jets[2].Phi() << " chf_jet3 = " << jetChfAK4->at(sortedJetIdx[2]) << "\tcemf_jet3 = " << jetCemfAK4->at(sortedJetIdx[2])  << " nhf_jet3 = " << jetNhfAK4->at(sortedJetIdx[2]) << " nemf_jet3 = " << jetNemfAK4->at(sortedJetIdx[2]) << "\tmuf_jet3 = " << jetMufAK4->at(sortedJetIdx[2]) <<  " phf_jet3 = " << jetPhfAK4->at(sortedJetIdx[2]) << " NM = " << neMultAK4->at(sortedJetIdx[2]) << " CM = " << chMultAK4->at(sortedJetIdx[2])<< " PM = " << phoMultAK4->at(sortedJetIdx[2]) << endl;

cout << "pT_jet4 =  " << AK4jets[3].Pt() << "   eta_jet4 = " << AK4jets[3].Eta() << "\tphi_jet4 = " << AK4jets[3].Phi() << " chf_jet4 = " << jetChfAK4->at(sortedJetIdx[3]) << "\tcemf_jet4 = " << jetCemfAK4->at(sortedJetIdx[3])  << " nhf_jet4 = " << jetNhfAK4->at(sortedJetIdx[3]) << " nemf_jet4 = " << jetNemfAK4->at(sortedJetIdx[3]) << "\tmuf_jet4 = " << jetMufAK4->at(sortedJetIdx[3]) <<  " phf_jet4 = " << jetPhfAK4->at(sortedJetIdx[3]) << " NM = " << neMultAK4->at(sortedJetIdx[3]) << " CM = " << chMultAK4->at(sortedJetIdx[3])<< " PM = " << phoMultAK4->at(sortedJetIdx[3]) << endl;

}


       } //end full analysis including deltaEta




     
     // optional call to fill a skim with a subset of the variables defined in the cutFile (use flag SAVE)
    if( passedAllPreviousCuts("mjj") && passedCut("mjj") ) 
      {
	// fillReducedSkimTree();

	 // ===== Take a look at this =====
	 // //Example on how to investigate quickly the data
	 // if(getVariableValue("mjj")>4000)
	 //   {
	 //     //fast creation and filling of histograms
	 //     CreateAndFillUserTH1D("h_dphijj_mjjgt4000", 100, 0, 3.15, getVariableValue("deltaPHIjj"));
	 //     CreateAndFillUserTH1D("h_htak4_mjjgt4000", 1000, 0, 10000, getVariableValue("HTAK4"));
	 //     CreateAndFillUserTH1D("h_nvtx_mjjgt4000", 31, -0.5, 30.5, getVariableValue("nVtx"));
	 //   }

       }

     // ===== Example of mjj spectrum after HLT selection =====
     // if( passedAllPreviousCuts("mjj") )
     //   {
     // 	 if(getVariableValue("passHLT")>0)
     // 	   {
     // 	     //fast creation and filling of histograms
     // 	     CreateAndFillUserTH1D("h_mjj_passHLT", getHistoNBins("mjj"), getHistoMin("mjj"), getHistoMax("mjj"), getVariableValue("mjj"));
     // 	   }
     //   }

     // reject events that did not pass level 0 cuts
     //if( !passedCut("0") ) continue;
     // ......
     
     // reject events that did not pass level 1 cuts
     //if( !passedCut("1") ) continue;
     // ......

     // reject events that did not pass the full cut list
     //if( !passedCut("all") ) continue;
     // ......

     // if( widejets.size() >= 2) {
     //  h_nJetFinal->Fill(widejets.size());
     //  h_DijetMass->Fill(wdijet.M());
     //  h_pT1stJet->Fill(widejets[0].Pt());
     //  h_pT2ndJet->Fill(widejets[1].Pt());
     //  h_eta1stJet->Fill(widejets[0].Eta());
     //  h_eta2ndJet->Fill(widejets[1].Eta());
     // }
     ////////////////////// User's code ends here ///////////////////////

   } // End loop over events

   //////////write histos 
   for (int i=0; i<14; i++){//
     
     h_mjj_HLTpass_dR2[i]->Write();
     h_mjj_HLTpass_dR2_alpha1[i]->Write();
     h_mjj_HLTpass_dR2_alpha2[i]->Write();
h_mjj_HLTpass_dR2_alpha3[i]->Write();
h_mjj_HLTpass_dR2_alpha4[i]->Write();
h_mjj_HLTpass_dR2_alpha5[i]->Write();
h_mjj_HLTpass_dR2_alpha6[i]->Write();
h_mjj_HLTpass_dR2_alpha7[i]->Write();
h_mjj_HLTpass_dR2_alpha8[i]->Write();
h_mjj_HLTpass_dR2_alpha9[i]->Write();
h_mjj_HLTpass_dR2_alpha10[i]->Write();
h_mjj_HLTpass_dR2_alpha11[i]->Write();
h_mjj_HLTpass_dR2_alpha12[i]->Write();
h_mjj_HLTpass_dR2_alpha13[i]->Write();
 
   }

   

   // h_nVtx->Write();
   // h_trueVtx->Write();
   // h_nJetFinal->Write();
   // h_pT1stJet->Write();
   // h_pT2ndJet->Write();
   // h_DijetMass->Write();
   // h_eta1stJet->Write();
   // h_eta2ndJet->Write();

   // //pT of both jets, to be built using the histograms produced automatically by baseClass
   // TH1F * h_pTJets = new TH1F ("h_pTJets","", getHistoNBins("pT1stJet"), getHistoMin("pT1stJet"), getHistoMax("pT1stJet"));
   // h_pTJets->Add( & getHisto_noCuts_or_skim("pT1stJet") ); // all histos can be retrieved, see other getHisto_xxxx methods in baseClass.h
   // h_pTJets->Add( & getHisto_noCuts_or_skim("pT2ndJet") );
   // //one could also do:  *h_pTJets = getHisto_noCuts_or_skim("pT1stJet") + getHisto_noCuts_or_skim("pT2ndJet");
   // h_pTJets->Write();
   // //one could also do:   const TH1F& h = getHisto_noCuts_or_skim// and use h

   std::cout << "analysisClass::Loop() ends" <<std::endl;   
}



// ------------ method that calculates the event weight based on the number of b-tagged jets in MC and the expected number of b-tags among the two leading jets  ------------
double
analysisClass::bTagEventWeight(const vector<double>& SFsForBTaggedJets, const unsigned int nBTags)
{
  if( SFsForBTaggedJets.size() > 2 )
    {
      std::cout << "Only two leading jets are considered. Hence, the number of b-tagged jets cannot exceed 2.";
      return 1;
    }
  if( nBTags > 2 )
    {
      std::cout << "Only two leading jets are considered. Hence, the number of b-tags cannot exceed 2.";
      return 1;
    }
  /*
    ##################################################################
    Event weight matrix:
    ------------------------------------------------------------------
    nBTags\b-tagged jets  |    0        1             2
    ------------------------------------------------------------------
      0                   |    1      1-SF      (1-SF1)(1-SF2)
                          |
      1                   |    0       SF    SF1(1-SF2)+(1-SF1)SF2
                          |
      2                   |    0        0           SF1SF2
    ##################################################################
  */
  
  if( nBTags > SFsForBTaggedJets.size() ) return 0;

  if( nBTags==0 && SFsForBTaggedJets.size()==0 ) return 1;

  double weight = 0;

  if( SFsForBTaggedJets.size()==1 )
    {
      double SF = SFsForBTaggedJets.at(0);

      for( unsigned int i=0; i<=1; ++i )
	{
	  if( i != nBTags ) continue;

	  weight += pow(SF,i)*pow(1-SF,1-i);
	}
    }
  else if( SFsForBTaggedJets.size()==2 )
    {
      double SF1 = SFsForBTaggedJets.at(0);
      double SF2 = SFsForBTaggedJets.at(1);
    
      for( unsigned int i=0; i<=1; ++i )
	{
	  for( unsigned int j=0; j<=1; ++j )
	    {
	      if( (i+j) != nBTags ) continue;

	      weight += pow(SF1,i)*pow(1-SF1,1-i)*pow(SF2,j)*pow(1-SF2,1-j);
	    }
	}
    }
  return weight;
}





void
analysisClass::fillTriggerPlots_dR2(TH1F* h_mjj_HLTpass_dR2[], double M4J_AK4) {//change this 11/7/2017

if(triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2[1] -> Fill(M4J_AK4);


if(triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) ) h_mjj_HLTpass_dR2[2] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)&& triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2[3] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2[4] -> Fill(M4J_AK4);
if(triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2[5] -> Fill(M4J_AK4);





//all currently unprescaled triggers
/*

if ( triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet500_v*")->second) ||    
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet400_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
        triggerResult->at(triggerMap_.find("HLT_PFJet500_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_CaloJet500_NoJetID_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second)
       
     )  h_mjj_HLTpass_dR2[12] -> Fill(M4J_AK4);*/


//or of expected unprescaled triggers
if ( (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) 
     )  h_mjj_HLTpass_dR2[6] -> Fill(M4J_AK4);






}



void
analysisClass::fillTriggerPlots_dR2_alpha1(TH1F* h_mjj_HLTpass_dR2_alpha1[], double M4J_AK4) {//change this 11/7/2017

if(triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha1[1] -> Fill(M4J_AK4);


if(triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) ) h_mjj_HLTpass_dR2_alpha1[2] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)&& triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha1[3] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha1[4] -> Fill(M4J_AK4);
if(triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha1[5] -> Fill(M4J_AK4);





//all currently unprescaled triggers
/*

if ( triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet500_v*")->second) ||    
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet400_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
        triggerResult->at(triggerMap_.find("HLT_PFJet500_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_CaloJet500_NoJetID_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second)
       
     )  h_mjj_HLTpass_dR2_alpha1[12] -> Fill(M4J_AK4);*/


//or of expected unprescaled triggers
if ( (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) 
     )  h_mjj_HLTpass_dR2_alpha1[6] -> Fill(M4J_AK4);





}



void
analysisClass::fillTriggerPlots_dR2_alpha2(TH1F* h_mjj_HLTpass_dR2_alpha2[], double M4J_AK4) {//change this 11/7/2017

if(triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha2[1] -> Fill(M4J_AK4);


if(triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) ) h_mjj_HLTpass_dR2_alpha2[2] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)&& triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha2[3] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha2[4] -> Fill(M4J_AK4);
if(triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha2[5] -> Fill(M4J_AK4);





//all currently unprescaled triggers
/*

if ( triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet500_v*")->second) ||    
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet400_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
        triggerResult->at(triggerMap_.find("HLT_PFJet500_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_CaloJet500_NoJetID_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second)
       
     )  h_mjj_HLTpass_dR2_alpha2[12] -> Fill(M4J_AK4);*/


//or of expected unprescaled triggers
if ( (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) 
     )  h_mjj_HLTpass_dR2_alpha2[6] -> Fill(M4J_AK4);






}


void
analysisClass::fillTriggerPlots_dR2_alpha3(TH1F* h_mjj_HLTpass_dR2_alpha3[], double M4J_AK4) {//change this 11/7/2017

if(triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha3[1] -> Fill(M4J_AK4);


if(triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) ) h_mjj_HLTpass_dR2_alpha3[2] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)&& triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha3[3] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha3[4] -> Fill(M4J_AK4);
if(triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha3[5] -> Fill(M4J_AK4);





//all currently unprescaled triggers
/*

if ( triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet500_v*")->second) ||    
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet400_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
        triggerResult->at(triggerMap_.find("HLT_PFJet500_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_CaloJet500_NoJetID_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second)
       
     )  h_mjj_HLTpass_dR2_alpha3[12] -> Fill(M4J_AK4);*/


//or of expected unprescaled triggers
if ( (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) 
     )  h_mjj_HLTpass_dR2_alpha3[6] -> Fill(M4J_AK4);






}


void
analysisClass::fillTriggerPlots_dR2_alpha4(TH1F* h_mjj_HLTpass_dR2_alpha4[], double M4J_AK4) {//change this 11/7/2017

if(triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha4[1] -> Fill(M4J_AK4);


if(triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) ) h_mjj_HLTpass_dR2_alpha4[2] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)&& triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha4[3] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha4[4] -> Fill(M4J_AK4);
if(triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha4[5] -> Fill(M4J_AK4);





//all currently unprescaled triggers
/*

if ( triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet500_v*")->second) ||    
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet400_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
        triggerResult->at(triggerMap_.find("HLT_PFJet500_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_CaloJet500_NoJetID_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second)
       
     )  h_mjj_HLTpass_dR2_alpha4[12] -> Fill(M4J_AK4);*/


//or of expected unprescaled triggers
if ( (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) 
     )  h_mjj_HLTpass_dR2_alpha4[6] -> Fill(M4J_AK4);





}


void
analysisClass::fillTriggerPlots_dR2_alpha5(TH1F* h_mjj_HLTpass_dR2_alpha5[], double M4J_AK4) {//change this 11/7/2017

if(triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha5[1] -> Fill(M4J_AK4);


if(triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) ) h_mjj_HLTpass_dR2_alpha5[2] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)&& triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha5[3] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha5[4] -> Fill(M4J_AK4);
if(triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha5[5] -> Fill(M4J_AK4);





//all currently unprescaled triggers
/*

if ( triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet500_v*")->second) ||    
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet400_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
        triggerResult->at(triggerMap_.find("HLT_PFJet500_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_CaloJet500_NoJetID_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second)
       
     )  h_mjj_HLTpass_dR2_alpha5[12] -> Fill(M4J_AK4);*/


//or of expected unprescaled triggers
if ( (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) 
     )  h_mjj_HLTpass_dR2_alpha5[6] -> Fill(M4J_AK4);





}


void
analysisClass::fillTriggerPlots_dR2_alpha6(TH1F* h_mjj_HLTpass_dR2_alpha6[], double M4J_AK4) {//change this 11/7/2017

if(triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha6[1] -> Fill(M4J_AK4);


if(triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) ) h_mjj_HLTpass_dR2_alpha6[2] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)&& triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha6[3] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha6[4] -> Fill(M4J_AK4);
if(triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha6[5] -> Fill(M4J_AK4);





//all currently unprescaled triggers
/*

if ( triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet500_v*")->second) ||    
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet400_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
        triggerResult->at(triggerMap_.find("HLT_PFJet500_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_CaloJet500_NoJetID_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second)
       
     )  h_mjj_HLTpass_dR2_alpha6[12] -> Fill(M4J_AK4);*/


//or of expected unprescaled triggers
if ( (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) 
     )  h_mjj_HLTpass_dR2_alpha6[6] -> Fill(M4J_AK4);





}


void
analysisClass::fillTriggerPlots_dR2_alpha7(TH1F* h_mjj_HLTpass_dR2_alpha7[], double M4J_AK4) {//change this 11/7/2017

if(triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha7[1] -> Fill(M4J_AK4);


if(triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) ) h_mjj_HLTpass_dR2_alpha7[2] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)&& triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha7[3] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha7[4] -> Fill(M4J_AK4);
if(triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha7[5] -> Fill(M4J_AK4);





//all currently unprescaled triggers
/*

if ( triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet500_v*")->second) ||    
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet400_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
        triggerResult->at(triggerMap_.find("HLT_PFJet500_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_CaloJet500_NoJetID_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second)
       
     )  h_mjj_HLTpass_dR2_alpha7[12] -> Fill(M4J_AK4);*/


//or of expected unprescaled triggers
if ( (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) 
     )  h_mjj_HLTpass_dR2_alpha7[6] -> Fill(M4J_AK4);





}


void
analysisClass::fillTriggerPlots_dR2_alpha8(TH1F* h_mjj_HLTpass_dR2_alpha8[], double M4J_AK4) {//change this 11/7/2017

if(triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha8[1] -> Fill(M4J_AK4);


if(triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) ) h_mjj_HLTpass_dR2_alpha8[2] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)&& triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha8[3] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha8[4] -> Fill(M4J_AK4);
if(triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha8[5] -> Fill(M4J_AK4);





//all currently unprescaled triggers
/*

if ( triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet500_v*")->second) ||    
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet400_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
        triggerResult->at(triggerMap_.find("HLT_PFJet500_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_CaloJet500_NoJetID_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second)
       
     )  h_mjj_HLTpass_dR2_alpha8[12] -> Fill(M4J_AK4);*/


//or of expected unprescaled triggers
if ( (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) 
     )  h_mjj_HLTpass_dR2_alpha8[6] -> Fill(M4J_AK4);



}

void
analysisClass::fillTriggerPlots_dR2_alpha9(TH1F* h_mjj_HLTpass_dR2_alpha9[], double M4J_AK4) {//change this 11/7/2017

if(triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha9[1] -> Fill(M4J_AK4);


if(triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) ) h_mjj_HLTpass_dR2_alpha9[2] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)&& triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha9[3] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha9[4] -> Fill(M4J_AK4);
if(triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha9[5] -> Fill(M4J_AK4);





//all currently unprescaled triggers
/*

if ( triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet500_v*")->second) ||    
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet400_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
        triggerResult->at(triggerMap_.find("HLT_PFJet500_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_CaloJet500_NoJetID_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second)
       
     )  h_mjj_HLTpass_dR2_alpha9[12] -> Fill(M4J_AK4);*/


//or of expected unprescaled triggers
if ( (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) 
     )  h_mjj_HLTpass_dR2_alpha9[6] -> Fill(M4J_AK4);



}

void
analysisClass::fillTriggerPlots_dR2_alpha10(TH1F* h_mjj_HLTpass_dR2_alpha10[], double M4J_AK4) {//change this 11/7/2017

if(triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha10[1] -> Fill(M4J_AK4);


if(triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) ) h_mjj_HLTpass_dR2_alpha10[2] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)&& triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha10[3] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha10[4] -> Fill(M4J_AK4);
if(triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha10[5] -> Fill(M4J_AK4);





//all currently unprescaled triggers
/*

if ( triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet500_v*")->second) ||    
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet400_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
        triggerResult->at(triggerMap_.find("HLT_PFJet500_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_CaloJet500_NoJetID_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second)
       
     )  h_mjj_HLTpass_dR2_alpha10[12] -> Fill(M4J_AK4);*/


//or of expected unprescaled triggers
if ( (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) 
     )  h_mjj_HLTpass_dR2_alpha10[6] -> Fill(M4J_AK4);



}

void
analysisClass::fillTriggerPlots_dR2_alpha11(TH1F* h_mjj_HLTpass_dR2_alpha11[], double M4J_AK4) {//change this 11/7/2017

if(triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha11[1] -> Fill(M4J_AK4);


if(triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) ) h_mjj_HLTpass_dR2_alpha11[2] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)&& triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha11[3] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha11[4] -> Fill(M4J_AK4);
if(triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha11[5] -> Fill(M4J_AK4);





//all currently unprescaled triggers
/*

if ( triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet500_v*")->second) ||    
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet400_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
        triggerResult->at(triggerMap_.find("HLT_PFJet500_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_CaloJet500_NoJetID_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second)
       
     )  h_mjj_HLTpass_dR2_alpha11[12] -> Fill(M4J_AK4);*/


//or of expected unprescaled triggers
if ( (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) 
     )  h_mjj_HLTpass_dR2_alpha11[6] -> Fill(M4J_AK4);







}



void
analysisClass::fillTriggerPlots_dR2_alpha12(TH1F* h_mjj_HLTpass_dR2_alpha12[], double M4J_AK4) {//change this 11/7/2017

if(triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha12[1] -> Fill(M4J_AK4);


if(triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) ) h_mjj_HLTpass_dR2_alpha12[2] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)&& triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha12[3] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha12[4] -> Fill(M4J_AK4);
if(triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha12[5] -> Fill(M4J_AK4);





//all currently unprescaled triggers
/*

if ( triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet500_v*")->second) ||    
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet400_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
        triggerResult->at(triggerMap_.find("HLT_PFJet500_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_CaloJet500_NoJetID_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second)
       
     )  h_mjj_HLTpass_dR2_alpha12[12] -> Fill(M4J_AK4);*/


//or of expected unprescaled triggers
if ( (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) 
     )  h_mjj_HLTpass_dR2_alpha12[6] -> Fill(M4J_AK4);






}


void
analysisClass::fillTriggerPlots_dR2_alpha13(TH1F* h_mjj_HLTpass_dR2_alpha13[], double M4J_AK4) {//change this 11/7/2017

if(triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha13[1] -> Fill(M4J_AK4);


if(triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) ) h_mjj_HLTpass_dR2_alpha13[2] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)&& triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha13[3] -> Fill(M4J_AK4);

if(triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha13[4] -> Fill(M4J_AK4);
if(triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second) && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second)) h_mjj_HLTpass_dR2_alpha13[5] -> Fill(M4J_AK4);





//all currently unprescaled triggers
/*

if ( triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet500_v*")->second) ||    
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_AK8PFJet400_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
        triggerResult->at(triggerMap_.find("HLT_PFJet500_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet450_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_CaloJet500_NoJetID_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second)
       
     )  h_mjj_HLTpass_dR2_alpha12[12] -> Fill(M4J_AK4);*/


//or of expected unprescaled triggers
if ( (triggerResult->at(triggerMap_.find("HLT_AK8PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFJet550_v*")->second) ||
       triggerResult->at(triggerMap_.find("HLT_PFHT1050_v*")->second) ||
triggerResult->at(triggerMap_.find("HLT_CaloJet550_NoJetID_v*")->second))
      && triggerResult->at(triggerMap_.find("HLT_Mu50_v*")->second) 
     )  h_mjj_HLTpass_dR2_alpha13[6] -> Fill(M4J_AK4);






}




