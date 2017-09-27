void TreeFiller() {
//TFile f("PileUpHisto.root");
//TH1F *h = (TH1F*)f.Get("j1_1");

TFile f("CutBasedID_TightWP_76X_forHWW_Final.txt_SF2D.root");
TH2F *h = (TH2F*)f.Get("EGamma_SF2D");
 
//TFile f1("DY_MG_25ns_4Nov.root");
TFile f1("/tmp/arun/eos/cms/store/group/phys_higgs/cmshww/arun/SingleEle_ReReco_76X/SingleElectron/crab_SingleEle_ReReco_76X/160202_171225/0000/Data_2015_SingleEle_76X.root");
//TFile f1("/tmp/arun/eos/cms/store/group/phys_higgs/cmshww/arun/DYLL_Poweheg_76X_17Feb/DYToEE_NNPDF30_13TeV-powheg-pythia8/crab_DYLL_Powheg_76X_17Feb/160217_102744/0000/DYLL_76X_Powheg_17Feb.root");
TTree *T1 = (TTree*)f1.Get("GsfElectronToRECO/fitter_tree");

TFile *file = new TFile("SingleEle_2015D_76X.root","RECREATE");
//TFile *file = new TFile("DY_Powheg_76X.root","RECREATE");
TTree *rhoTree = new TTree("rhoTree"," after preselections tree");

 
 int event_nPV;
 float event_rho;
 float pair_mass;
 int passingTight;
 float probe_sc_eta;
 float tag_sc_eta;
 float probe_Ele_fullr9;
 float tag_Ele_fullr9;
 float probe_sc_rawE;
 float tag_sc_rawE;
 float probe_sc_abseta;
 float tag_sc_abseta;
 float probe_Ele_pt;
 float probe_Ele_eta;
 float probe_Ele_phi;
 float probe_Ele_e;
 float tag_Ele_e;
 float tag_Ele_pt;
 float pair_pt;
 float pair_eta;
 float tag_Ele_phi;
 double totWeight;
float probe_Ele_trkIso;
float probe_Ele_ecalIso;
float probe_Ele_hcalIso; 
float tag_Ele_trkIso;
float tag_Ele_ecalIso;
float tag_Ele_hcalIso;

 double Nvtx_weight;
 float rho;
 float Z_mass;
 int TightID;
 int NPV;
 float probe_eta;
 float tag_eta;
 float probe_fullr9;
 float tag_fullr9;
 float probe_rawE;
 float tag_rawE;
 float probe_abseta;
 float tag_abseta;
 float probe_e;
 float tag_e;
 float Z_rawmass;
 float Z_pt;
 float tag_pt;
 float Z_eta;
 float probe_pt;
 float tag_phi;
 float probe_phi;
 float idSF;
float probe_trkIso;
float probe_ecalIso;
float probe_hcalIso;
float tag_trkIso;
float tag_ecalIso;
float tag_hcalIso; 

 
T1->SetBranchAddress("event_nPV", &event_nPV);
T1->SetBranchAddress("event_rho", &event_rho);
T1->SetBranchAddress("passingTight", &passingTight);
T1->SetBranchAddress("pair_mass", &pair_mass);
T1->SetBranchAddress("probe_sc_eta",&probe_sc_eta);
T1->SetBranchAddress("tag_sc_eta",&tag_sc_eta);
T1->SetBranchAddress("tag_Ele_fullr9",&tag_Ele_fullr9);
T1->SetBranchAddress("probe_Ele_fullr9",&probe_Ele_fullr9);
T1->SetBranchAddress("probe_sc_abseta",&probe_sc_abseta);
T1->SetBranchAddress("tag_sc_abseta",&tag_sc_abseta);
T1->SetBranchAddress("tag_sc_rawE",&tag_sc_rawE);
T1->SetBranchAddress("probe_sc_rawE",&probe_sc_rawE);
T1->SetBranchAddress("probe_Ele_e",&probe_Ele_e);
T1->SetBranchAddress("tag_Ele_e",&tag_Ele_e);
 T1->SetBranchAddress("pair_pt", &pair_pt);
 T1->SetBranchAddress("tag_Ele_pt",&tag_Ele_pt);
 T1->SetBranchAddress("pair_eta", &pair_eta);
 T1->SetBranchAddress("tag_Ele_pt",&tag_Ele_pt);
 T1->SetBranchAddress("probe_Ele_pt",&probe_Ele_pt);
 T1->SetBranchAddress("tag_Ele_phi",&tag_Ele_phi);
 T1->SetBranchAddress("probe_Ele_phi",&probe_Ele_phi);
T1->SetBranchAddress("totWeight",&totWeight);
 T1->SetBranchAddress("probe_Ele_trkIso",&probe_Ele_trkIso);
 T1->SetBranchAddress("probe_Ele_ecalIso",&probe_Ele_ecalIso);
 T1->SetBranchAddress("probe_Ele_hcalIso",&probe_Ele_hcalIso);
 T1->SetBranchAddress("tag_Ele_trkIso",&tag_Ele_trkIso);
 T1->SetBranchAddress("tag_Ele_ecalIso",&tag_Ele_ecalIso);
 T1->SetBranchAddress("tag_Ele_hcalIso",&tag_Ele_hcalIso);  


rhoTree->Branch("Nvtx_weight", &Nvtx_weight ,"Nvtx_weight/D");
rhoTree->Branch("rho", &rho ,"rho/F");
rhoTree->Branch("Z_mass",&Z_mass,"Z_mass/F");
 rhoTree->Branch("TightID",&TightID,"TightID/I"); 
 rhoTree->Branch("NPV",&NPV,"NPV/I");
 rhoTree->Branch("tag_eta",&tag_eta,"tag_eta/F");
 rhoTree->Branch("probe_eta",&probe_eta,"probe_eta/F");
 rhoTree->Branch("tag_fullr9",&tag_fullr9,"tag_fullr9/F");
 rhoTree->Branch("tag_abseta",&tag_abseta,"tag_abseta/F");
 rhoTree->Branch("probe_abseta",&probe_abseta,"probe_abseta/F");
 rhoTree->Branch("probe_rawE",&probe_rawE,"probe_rawE/F");
 rhoTree->Branch("tag_rawE",&tag_rawE,"tag_rawE/F");
 rhoTree->Branch("probe_fullr9",&probe_fullr9,"probe_fullr9/F");
 rhoTree->Branch("Z_rawmass",&Z_rawmass,"Z_rawmass/F");
 rhoTree->Branch("Z_pt",&Z_pt,"Z_pt/F");
 rhoTree->Branch("tag_pt",&tag_pt,"tag_pt/F");
 rhoTree->Branch("Z_eta",&Z_eta,"Z_eta/F");
 rhoTree->Branch("probe_pt",&probe_pt,"probe_pt/F");
 rhoTree->Branch("probe_phi",&probe_phi,"probe_phi/F");
 rhoTree->Branch("tag_phi",&tag_phi,"tag_phi/F");
 rhoTree->Branch("idSF",&idSF,"idSF/F");
rhoTree->Branch("probe_trkIso",&probe_trkIso,"probe_trkIso/F");
 rhoTree->Branch("probe_ecalIso",&probe_ecalIso,"probe_ecalIso/F");
rhoTree->Branch("probe_hcalIso",&probe_hcalIso,"probe_hcalIso/F");
rhoTree->Branch("tag_trkIso",&tag_trkIso,"tag_trkIso/F");
 rhoTree->Branch("tag_ecalIso",&tag_ecalIso,"tag_ecalIso/F");
rhoTree->Branch("tag_hcalIso",&tag_hcalIso,"tag_hcalIso/F");
 
 int nentries = T1->GetEntries();
cout << "nentries = " << nentries << endl;
 for (unsigned int j = 1; j <= nentries ; j++ ) {
   T1->GetEntry(j);

if(j%100000 == 0) cout << "Events Processed = " << j << endl;
   
   //float weight_pileupnew = 1.;
// int binidx = h->FindBin(event_nPV);
//Nvtx_weight = h->GetBinContent(binidx);
//if(Nvtx_weight ==0) 
//Nvtx_weight = 1 ;

   Nvtx_weight = totWeight;
   rho = event_rho;
   Z_mass = pair_mass;
   TightID = passingTight;
   NPV = event_nPV;
   probe_eta = probe_sc_eta;
   tag_eta = tag_sc_eta;
   tag_fullr9 = tag_Ele_fullr9;
   probe_fullr9 = probe_Ele_fullr9;
   tag_rawE = tag_sc_rawE;
   probe_rawE = probe_sc_rawE;
   probe_abseta = probe_sc_abseta;
   tag_abseta = tag_sc_abseta;
   probe_e = probe_Ele_e;
   tag_e = tag_Ele_e;
   Z_rawmass = Z_mass * sqrt(probe_rawE/probe_e * tag_rawE/tag_e);
   Z_pt = pair_pt;
   tag_pt = tag_Ele_pt;
   Z_eta = pair_eta;
   probe_pt = probe_Ele_pt;
   tag_phi = tag_Ele_phi;
   probe_phi = probe_Ele_phi;

if(tag_pt > 200) tag_pt = 199;
if(probe_pt > 200) probe_pt = 199;

  Int_t binTagX = h->GetXaxis()->FindFixBin(tag_abseta);
  Int_t binTagY = h->GetYaxis()->FindFixBin(tag_pt);
 // return hist->GetBinError(binX, binY);
//int bintag = h->FindBinX(tab_abseta,tag_pt);
float idsftag = h->GetBinContent(binTagX,binTagY);

  Int_t binProbeX = h->GetXaxis()->FindFixBin(probe_abseta);
  Int_t binProbeY = h->GetYaxis()->FindFixBin(probe_pt);

float idsfprobe = h->GetBinContent(binProbeX,binProbeY);

//idSF = idsftag*idsfprobe;

idSF = 1.;

//cout << "idSF = " << idSF << endl;

   //   cout << " Raw Mass = " << Z_mass * sqrt(probe_rawE/probe_e * tag_rawE/tag_e) << endl;
   // cout << " Mass = " << Z_mass << endl;

probe_trkIso = probe_Ele_trkIso;
probe_ecalIso = probe_Ele_ecalIso;
probe_hcalIso = probe_Ele_hcalIso;
tag_trkIso = tag_Ele_trkIso;
tag_ecalIso = tag_Ele_ecalIso;
tag_hcalIso = tag_Ele_hcalIso;

   rhoTree->Fill();
   
}
 file->Write();
}

