#!/usr/bin/env python

from ROOT import gROOT, TFile, TTree, TChain, TString
from ROOT import TH2F, TH1F
from array import array

dataTree = TChain("tnpEleIDs/fitter_tree")
mcTree   = TChain("tnpEleIDs/fitter_tree")
dataTree.SetBranchStatus("*",0)
mcTree  .SetBranchStatus("*",0)
# sfFile   = TFile("egammaEffi.txt_EGM2D.root")
# sfHist   = sfFile.Get("EGamma_SF2D")

# looseDef  = '(( (abs(el_sc_abseta)< 1.497) && (el_sieie < 0.011 ) && (el_hoe < 0.06) && (el_1overEminus1overP < 0.013) && (el_reliso03 < 0.04 ) && (el_dr03TkSumPt/el_pt < 0.08 ) && (el_dr03EcalRecHitSumEt/el_pt < 0.15 ) && (el_dr03HcalDepth1TowerSumEt/el_pt < 0.12 ) && (el_mHits < 2 ) && (el_conversionVeto == 1 ) ) || ( (abs(el_sc_abseta)> 1.497) && (el_sieie < 0.03  )  &&          (el_hoe < 0.07) && (el_1overEminus1overP < 0.013) && (el_reliso03 < 0.12 ) && (el_dr03TkSumPt/el_pt < 0.08 ) && (el_dr03EcalRecHitSumEt/el_pt < 0.13 ) && (el_dr03HcalDepth1TowerSumEt/el_pt < 0.08 )       && (el_mHits < 2 ) && (el_conversionVeto == 1 ) ))'


# cutMissingInnerHits         = 'el_mHits == 0'
cutDz                       = '(( abs(el_sc_abseta) > 1.497 && abs(el_dz) < 0.2 )||( abs(el_sc_abseta) < 1.497 && abs(el_dz) < 0.1 ))'
cutDxy                      = '(( abs(el_sc_abseta) > 1.497 && abs(el_dxy) < 0.1 )||( abs(el_sc_abseta) < 1.497 && abs(el_dxy) < 0.05 ))'
# cutIsolation                = '(( abs(el_sc_abseta) > 1.497 && el_reliso03 < 0.04 )||( abs(el_sc_abseta) < 1.497 && el_reliso03 < 0.12 ))'

cutSieie                    = '(( abs(el_sc_abseta) > 1.497 && el_sieie < 0.03 )||( abs(el_sc_abseta) < 1.497 ))'
cut1overEminus1overP        = '(( abs(el_sc_abseta) > 1.497 && el_1overEminus1overP < 0.014 )||( abs(el_sc_abseta) < 1.497 ))'
# cutHoe                      = '(( abs(el_sc_abseta) > 1.497  )||( abs(el_sc_abseta) < 1.497 ))'
# cutdr03TkSumPt              = '(( abs(el_sc_abseta) > 1.497  )||( abs(el_sc_abseta) < 1.497 ))'
# cutdr03EcalRecHitSumEt      = '(( abs(el_sc_abseta) > 1.497  )||( abs(el_sc_abseta) < 1.497 ))'
# cutdr03HcalDepth1TowerSumEt = '(( abs(el_sc_abseta) > 1.497  )||( abs(el_sc_abseta) < 1.497 ))'
# cutconversionVeto           = '(( abs(el_sc_abseta) > 1.497  )||( abs(el_sc_abseta) < 1.497 ))'



passingLooseHWW = '({0}) && ({1}) && ({2}) && ({3}) && (passingVeto94X == 1)'.format(cutDxy,cutDz,cutSieie,cut1overEminus1overP)
# passingMVA94Xwp90isoHWW = '({0}) && ({1}) && ({2}) && ({3}) && (passingMVA94Xwp90iso == 1  )'.format(looseDef,cutDxy,cutDz,cutMissingInnerHits)

cutKinematicEta = '(abs(tag_sc_eta)<2.5 && abs(el_sc_eta)<2.5 && pair_mass > 60 && pair_mass < 120)'
cutKinematicPt = '(((el_pt>30 && tag_Ele_pt>20) && (el_pt > tag_Ele_pt))||((el_pt>20 && tag_Ele_pt>30) && (el_pt < tag_Ele_pt)))'
cutBase = '(tag_Ele_pt > 30 && abs(tag_sc_eta) < 2.17 && el_q*tag_Ele_q < 0)'
lowPtBin ='((el_pt > 20) || (el_pt<20 && tag_Ele_trigMVA > 0.92 && sqrt( 2*event_met_pfmet*tag_Ele_pt*(1-cos(event_met_pfphi-tag_Ele_phi))) < 45))'

if __name__ == '__main__':
    gROOT.LoadMacro("functionGetSF.cc+")
    from ROOT import setSFHist, sfHist, getSFPtEta

    # setSFHist("egammaEffiTight80XforHWW.txt_EGM2D.root",0)
    # setSFHist("egammapassingRECO.txt_EGM2D.root",1)


    setSFHist("/afs/cern.ch/work/p/pyu/public/hww/electronSF2017Data/egm_tnp_analysis/closureTest/dataMCMadgraphCompar/egammaEffi.txt_EGM2D_runCDE_idiso.root",0)
    # setSFHist("/afs/cern.ch/work/p/pyu/public/hww/electronSF2017Data/egm_tnp_analysis/closureTest/dataMCMadgraphCompar/egammaEffi.txt_EGM2D_runB_idiso.root",0)
    # setSFHist("/afs/cern.ch/work/p/pyu/public/hww/electronSF2017Data/egm_tnp_analysis/closureTest/dataMCMadgraphCompar/egammaEffi.txt_EGM2D_runB_passingRECO.root",1)
    # setSFHist("/afs/cern.ch/work/p/pyu/public/hww/electronSF2017Data/egm_tnp_analysis/closureTest/dataMCMadgraphCompar/egammaEffi.txt_EGM2D_runC_idiso.root",0)
    # setSFHist("/afs/cern.ch/work/p/pyu/public/hww/electronSF2017Data/egm_tnp_analysis/closureTest/dataMCMadgraphCompar/egammaEffi.txt_EGM2D_runC_passingRECO.root",1)
    # setSFHist("/afs/cern.ch/work/p/pyu/public/hww/electronSF2017Data/egm_tnp_analysis/closureTest/dataMCMadgraphCompar/egammaEffi.txt_EGM2D_runD_idiso.root",0)
    # setSFHist("/afs/cern.ch/work/p/pyu/public/hww/electronSF2017Data/egm_tnp_analysis/closureTest/dataMCMadgraphCompar/egammaEffi.txt_EGM2D_runD_passingRECO.root",1)
    # setSFHist("/afs/cern.ch/work/p/pyu/public/hww/electronSF2017Data/egm_tnp_analysis/closureTest/dataMCMadgraphCompar/egammaEffi.txt_EGM2D_runE_idiso.root",0)
    # setSFHist("/afs/cern.ch/work/p/pyu/public/hww/electronSF2017Data/egm_tnp_analysis/closureTest/dataMCMadgraphCompar/egammaEffi.txt_EGM2D_runE_passingRECO.root",1)
    # setSFHist("/afs/cern.ch/work/p/pyu/public/hww/electronSF2017Data/egm_tnp_analysis/closureTest/dataMCMadgraphCompar/egammaEffi.txt_EGM2D_runF_idiso.root",0)
    # setSFHist("/afs/cern.ch/work/p/pyu/public/hww/electronSF2017Data/egm_tnp_analysis/closureTest/dataMCMadgraphCompar/egammaEffi.txt_EGM2D_runF_passingRECO.root",1)

    # dataTree.Add("/eos/cms/store/user/pchen/HWW/TnPTrees/Moriond18_V1/data/SingleElectron/TnPTree_17Nov2017_RunB.root")
    dataTree.Add("/eos/cms/store/user/pchen/HWW/TnPTrees/Moriond18_V1/data/SingleElectron/TnPTree_17Nov2017_RunC.root")
    dataTree.Add("/eos/cms/store/user/pchen/HWW/TnPTrees/Moriond18_V1/data/SingleElectron/TnPTree_17Nov2017_RunD.root")
    dataTree.Add("/eos/cms/store/user/pchen/HWW/TnPTrees/Moriond18_V1/data/SingleElectron/TnPTree_17Nov2017_RunE.root")
    # dataTree.Add("/eos/cms/store/user/pchen/HWW/TnPTrees/Moriond18_V1/data/SingleElectron/TnPTree_17Nov2017_RunF.root")
    mcTree  .Add("/eos/cms/store/user/pchen/HWW/TnPTrees/Moriond18_V1/mc/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/TnPTree_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_all.root")

    plantBranches = ['passingVeto94X','pair_mass','event_met_pfphi','tag_Ele_phi','el_mHits','el_sc_abseta','el_sc_eta','el_dz','el_dxy','el_reliso03','el_sieie','el_dEtaIn','el_hoe','el_1overEminus1overP','el_dr03TkSumPt','el_pt','el_ecalIso','el_hcalIso','el_dr03EcalRecHitSumEt','el_dr03HcalDepth1TowerSumEt','el_conversionVeto','tag_Ele_pt','tag_sc_eta','el_q','tag_Ele_q','tag_Ele_trigMVA','event_met_pfmet','passingMVA94Xwp90iso']
    for br in plantBranches:
        dataTree.SetBranchStatus(br,1)
        mcTree  .SetBranchStatus(br,1)

    f_output = TFile("plot_DataMCnewLoose_withRecoSFs_runCDE_test.root",'RECREATE')#noLoose+notight
    # f_output = TFile("plot_DataMCnewLoose_withRecoSFs_runB_test.root",'RECREATE')#noLoose+notight
    # f_output = TFile("plot_DataMCnewLoose_withRecoSFs_runC_test.root",'RECREATE')#noLoose+notight
    # f_output = TFile("plot_DataMCnewLoose_withRecoSFs_runD_test.root",'RECREATE')#noLoose+notight
    # f_output = TFile("plot_DataMCnewLoose_withRecoSFs_runE_test.root",'RECREATE')#noLoose+notight
    # f_output = TFile("plot_DataMCnewLoose_withRecoSFs_runF_test.root",'RECREATE')#noLoose+notight

    # f_output = TFile("plot_DataMCnoSF_runBCDE.root",'RECREATE')
    # f_output = TFile("plot_DataMCwithSF_runBCDE.root",'RECREATE')
    # f_output = TFile("plot_DataMCnoSF_runF.root",'RECREATE')
    # f_output = TFile("plot_DataMCwithSF_runF.root",'RECREATE')

    # ptBin  = array('d',[   20+i*2   for i in range(51)])
    # etaBin = array('d',[ -2.6+i*0.1 for i in range(53)])
    etaBin = array('d',[-2.5,-2.0,-1.566,-1.4442, -0.8, 0.0, 0.8, 1.4442, 1.566, 2.0, 2.5])
    ptBin  = array('d',[10,20,35,50,90,150,500])

    # Data plots
    # dataCut = "(({0}) && ({1}) && (passingMVA94Xwp90iso == 1))".format(cutKinematicEta,cutKinematicPt)#only MVAID
    # dataCut = "(({0}) && ({1}) && ({2}) && (passingMVA94Xwp90iso == 1))".format(cutKinematicEta,cutKinematicPt,cutMissingInnerHits)#MVAID + missingHits
    # dataCut = "(({0}) && ({1}) && ({2}) && ({3}) && ({4}) && (passingMVA94Xwp90iso == 1))".format(cutKinematicEta,cutKinematicPt,cutMissingInnerHits,cutDxy,cutDz)#MVAID + missingHits + dxy/dz
    # dataCut = "(({0}) && ({1}) && ({2}) && ({3}) && ({4}) && ({5}) && (passingMVA94Xwp90iso == 1))".format(cutKinematicEta,cutKinematicPt,cutKinematicEta,cutDxy,cutDz,cutIsolation)#MVAID + missingHits + dxy/dz + isolation
    dataCut = "(({0}) && ({1}) && ({2}) && (passingMVA94Xwp90iso == 1))".format(cutKinematicEta,cutKinematicPt,passingLooseHWW)

    h_data_ZMass       = TH1F("h_data_ZMass"       , "" , 60            , 60      , 120)
    h_data_tagEleEta   = TH1F("h_data_tagEleEta"   , "" , 100,-2.5,2.5)
    h_data_probeScEta  = TH1F("h_data_probeScEta"  , "" , 100,-2.5,2.5)
    h_data_tagElePt    = TH1F("h_data_tagElePt "   , "" , 98,10, 500)
    h_data_probePt     = TH1F("h_data_probePt"     , "" , 98,10, 500)

    h_data_el_sieie                    = TH1F("h_data_el_sieie"             , "" , 200 , 0 , 0.04)
    h_data_el_hoe                      = TH1F("h_data_el_hoe"               , "" , 100 , 0 , 0.2)
    h_data_el_1overEminus1overP        = TH1F("h_data_el_1overEminus1overP" , "" , 100 , -0.25 , 0.25)
    h_data_el_reliso03                 = TH1F("h_data_el_reliso03"          , "" , 100 , 0 , 1)
    h_data_el_dr03TkSumPt              = TH1F("h_data_el_dr03TkSumPt"       , "" , 100 , 0 , 20)
    h_data_el_dr03EcalRecHitSumEt      = TH1F("h_data_el_dr03EcalRecHitSumEt"           , "" , 100 , 0 , 20)
    h_data_el_dr03HcalDepth1TowerSumEt = TH1F("h_data_el_dr03HcalDepth1TowerSumEt"           , "" , 100 , 0 , 20)

    dataPlots = [
        "pair_mass>>h_data_ZMass"           , 
        "tag_sc_eta>>h_data_tagEleEta" , 
        "el_sc_eta>>h_data_probeScEta"   , 
        "tag_Ele_pt>>h_data_tagElePt",
        "el_pt>>h_data_probePt"      , 
        "el_sieie>>h_data_el_sieie",
        "el_hoe>>h_data_el_hoe",
        "el_1overEminus1overP>>h_data_el_1overEminus1overP",
        "el_reliso03>>h_data_el_reliso03",
        "el_dr03TkSumPt>>h_data_el_dr03TkSumPt",
        "el_dr03EcalRecHitSumEt>>h_data_el_dr03EcalRecHitSumEt",
        "el_dr03HcalDepth1TowerSumEt>>h_data_el_dr03HcalDepth1TowerSumEt"
    ]

    for p in dataPlots:
        dataTree.Draw(p,dataCut,"goff")

    # MC plots
    mcCut = "getSFPtEta(el_pt, el_sc_eta, tag_Ele_pt, tag_sc_eta)*({0})".format(dataCut)

    # mcCut = "getSFPtEta(el_pt, el_sc_eta, tag_Ele_pt, tag_sc_eta, 0)*({0})".format(dataCut)
    # mcCut = "getSFPtEta(probe_Ele_pt, probe_sc_eta, tag_Ele_pt, tag_sc_eta )*({0})".format(dataCut)
    # mcCut = "getSFPtEta(probe_Ele_pt, probe_sc_eta, tag_Ele_pt, tag_sc_eta,1)*({0})".format(dataCut)

    h_mc_ZMass       = TH1F("h_mc_ZMass"       , "" , 60            , 60      , 120)
    h_mc_tagEleEta   = TH1F("h_mc_tagEleEta"   , "" , 100, -2.5,2.5)
    h_mc_probeScEta  = TH1F("h_mc_probeScEta"  , "" , 100, -2.5,2.5)
    h_mc_tagElePt   = TH1F("h_mc_tagElePt"     , "" , 98,10,500)
    h_mc_probePt     = TH1F("h_mc_probePt"     , "" , 98,10,500)
    h_mc_el_sieie             = TH1F("h_mc_el_sieie"             , "" , 200 , 0 , 0.04)
    h_mc_el_hoe               = TH1F("h_mc_el_hoe"               , "" , 100 , 0 , 0.2)
    h_mc_el_1overEminus1overP = TH1F("h_mc_el_1overEminus1overP" , "" , 100 , -0.25 , 0.25)
    h_mc_el_reliso03          = TH1F("h_mc_el_reliso03"          , "" , 100 , 0 , 1)
    h_mc_el_dr03TkSumPt       = TH1F("h_mc_el_dr03TkSumPt"       , "" , 100 , 0 , 20)
    h_mc_el_dr03EcalRecHitSumEt      = TH1F("h_mc_el_dr03EcalRecHitSumEt"           , "" , 100 , 0 , 20)
    h_mc_el_dr03HcalDepth1TowerSumEt = TH1F("h_mc_el_dr03HcalDepth1TowerSumEt"           , "" , 100 , 0 , 20)

    mcPlots = [
        "pair_mass>>h_mc_ZMass"           ,
        "tag_sc_eta>>h_mc_tagEleEta" ,
        "el_sc_eta>>h_mc_probeScEta"   ,
        "tag_Ele_pt>>h_mc_tagElePt",
        "el_pt>>h_mc_probePt"      ,
        "el_sieie>>h_mc_el_sieie",
        "el_hoe>>h_mc_el_hoe",
        "el_1overEminus1overP>>h_mc_el_1overEminus1overP",
        "el_reliso03>>h_mc_el_reliso03",
        "el_dr03TkSumPt>>h_mc_el_dr03TkSumPt",
        "el_dr03EcalRecHitSumEt>>h_mc_el_dr03EcalRecHitSumEt",
        "el_dr03HcalDepth1TowerSumEt>>h_mc_el_dr03HcalDepth1TowerSumEt"
    ]

    for p in mcPlots:
        mcTree.Draw(p,mcCut,"goff")

    # mcTree.Draw("getSFPtEta(el_pt, el_sc_eta , tag_Ele_pt , tag_sc_eta)>>h_mc_closureTest",dataCut)
    # mcTree.Draw("getSFPtEta(el_pt, el_sc_eta , tag_Ele_pt , tag_sc_eta , 0)>>h_mc_closureTest",dataCut)
    mcTree.Draw("getSFPtEta(el_pt, el_sc_eta , tag_Ele_pt , tag_sc_eta)>>h_mc_closureTest",dataCut)
    # mcTree.Draw("getSFPtEta(probe_Ele_pt, probe_sc_eta , tag_Ele_pt , tag_sc_eta )   >>h_mc_fullSF",dataCut)

    f_output.Write()
    f_output.Close()

