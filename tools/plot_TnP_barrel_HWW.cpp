void plot_TnP_barrel_HWW()  {

//double w_DYLL = 0.002369112;
//double w_DYLL = 0.012104527;
//double w_DYLL = 0.1131; // Scale factor for Madgraph sample (4895 pb) with number of events = 9052671 with 25 ns data Lumi = 209.23 pb-1
//double w_DYLL = 1.0242;  // Scale factor for MG sample (6025.2 pb (NLO), 4895 pb (LO)) with number of events = 9052671 with 25 ns data Lumi = 1538.78 pb-1

double w_DYLL = 0.0808;  // Scale factor for Powheg sample (1997 pb) with number of events = 49653546 with 25 ns data Lumi = 2000 pb-1
  
//TFile f1("Data_Modified.root");
//TFile f2("DY_Modified.root");

TFile f1("SingleEle_2015D_76X.root");
TFile f2("DY_Powheg_76X.root");
 
TTree *T1 = (TTree*)f1.Get("rhoTree");
TTree *T2 = (TTree*)f2.Get("rhoTree");

TFile * file = new TFile("plots_TnP.root","RECREATE"); 

//double w_DYLL = T1->GetEntries()/T2->GetEntries();  // Scale factor for MG sample (6025.2 pb (NLO), 4895 pb (LO)) with number of events = 9404390 with 25 ns data Lumi = 1538.78 pb-1

//========================================================================== canvas 1 starts =======================
 
TCanvas *c1 = new TCanvas("c1", "c1",201,27,989,682);
  c1->SetFillColor(0);
 // c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(1);
//  c1->SetFrameBorderMode(-1);
//    c1->SetLogy(1);
   TPad *pad1 = new TPad("pad1","pad1",0,0.2,1,1);
   pad1->SetBottomMargin(0.03287462);
   pad1->SetLogy(1);
   pad1->Draw();
   pad1->cd();

THStack *hs = new THStack("hs","diLepton invariant mass (GeV)");
TLegend *tleg1_8 = new TLegend(0.70,0.80,0.85,0.90,NULL,"brNDC");
TH1F *j1_1 = new TH1F("j1_1","Invariant Mass",60,60.,120.);
//  T1->Draw("Z_mass>>j1_1","1*(TightID == 1 && probe_abseta < 1.5 && tag_abseta < 1.5 && Z_mass > 60. && Z_mass <= 120. )");
  T1->Draw("Z_mass>>j1_1","1*(TightID == 1 && Z_mass > 60. && Z_mass <= 120. && probe_trkIso < 0.2 && probe_ecalIso < 0.45 && probe_hcalIso < 0.25 && tag_trkIso < 0.2 && tag_ecalIso < 0.45 && tag_hcalIso < 0.25)");  
  j1_1->SetLineColor(kBlack);
  j1_1->SetLineWidth(2);
  j1_1->SetStats(0);
  j1_1->Sumw2();

TH1F *j2_1 = new TH1F("j2_1","Invariant Mass",60,60.,120.);
//  T2->Draw("Z_mass>>j2_1","1*(TightID == 1 && probe_abseta < 1.5 && tag_abseta < 1.5 && Z_mass > 60. && Z_mass <= 120. )");
  T2->Draw("Z_mass>>j2_1","1*(TightID == 1 && Z_mass > 60. && Z_mass <= 120. && probe_trkIso < 0.2 && probe_ecalIso < 0.45 && probe_hcalIso < 0.25 && tag_trkIso < 0.2 && tag_ecalIso < 0.45 && tag_hcalIso < 0.25)");  
  j2_1->SetFillColor(kRed);
  j2_1->SetLineColor(kRed);
  j2_1->SetLineWidth(2);
  j2_1->SetStats(0);
  

hs->Add(j2_1);


//j2_1->Scale(j1_1->Integral()/j2_1->Integral());
j2_1->Scale(w_DYLL);
j1_1->Scale(1.);

cout << "MC = " << j2_1->Integral() << endl;
cout << "Data = "  << j1_1->Integral() << endl;
TH1F *h1_1 = new TH1F("h1_1","Ratio",60,60.,120.);
TH1F *h2 = (TH1F *)j1_1->Clone();
h1_1->Add(j2_1);

hs->Draw("hist");
j1_1->Draw("sames");

  tleg1_8->AddEntry(j1_1,"Data","l");
  tleg1_8->AddEntry(j2_1,"DY_Fall15","f");
 tleg1_8->SetFillColor(kWhite);
 tleg1_8->Draw("sames");
c1->cd();

TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.2);
  // TH1F *hs1=hs->Clone();
   pad2->SetGridy(1);
   pad2->SetPad(0,0.0,1.0,0.2);
   pad2->SetTopMargin(0);
   pad2->SetBottomMargin(0.5);
   pad2->Draw();
   pad2->cd();
  float yscale = (1.0-0.2)/(0.18-0);
  h2->Divide(h1_1);
  h2->SetMarkerStyle(21);
  h2->SetStats(0);
//  h1->SetMinimum(0.5);
//  h1->SetMaximum(1.5);
  h2->GetYaxis()->SetTitle("Data/#Sigma MC");
  h2->SetMinimum(0.4);
  h2->SetMaximum(1.6);
  h2->GetXaxis()->SetTitle("");
  h2->GetXaxis()->SetTitleOffset(1.3);
  h2->GetXaxis()->SetLabelSize(0.033*yscale);
  h2->GetXaxis()->SetTitleSize(0.036*yscale);
  h2->GetXaxis()->SetTickLength(0.03*yscale);
//h1->GetYaxis()->SetLabelFont(63);
//h1->GetYaxis()->SetLabelSize(12);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
   h2->Draw("");

c1->SaveAs("Z_mass_PP_withoutSF_forHWW.png");
c1->Write();


TCanvas *c4 = new TCanvas("c4", "c4",201,27,989,682);
  c4->SetFillColor(0);
 // c4->SetFrameFillColor(0);
  c4->SetFrameBorderSize(1);
//  c4->SetFrameBorderMode(-1);
//    c4->SetLogy(1);
   TPad *pad11 = new TPad("pad11","pad11",0,0.2,1,1);
   pad11->SetBottomMargin(0.03287462);
   pad11->SetLogy(1);
   pad11->Draw();
   pad11->cd();

THStack *hs4 = new THStack("hs4","Probe Ele PT");
TLegend *tleg4 = new TLegend(0.70,0.80,0.85,0.90,NULL,"brNDC");
TH1F *j7_1 = new TH1F("j7_1","Probe Ele PT",100,10.,210.);
  T1->Draw("probe_pt>>j7_1","1*(TightID == 1 && Z_mass > 60. && Z_mass <= 120. && probe_trkIso < 0.2 && probe_ecalIso < 0.45 && probe_hcalIso < 0.25 && tag_trkIso < 0.2 && tag_ecalIso < 0.45 && tag_hcalIso < 0.25 )");
  j7_1->SetLineColor(kBlack);
  j7_1->SetLineWidth(2);
  j7_1->SetStats(0);
  j7_1->Sumw2();

TH1F *j8_1 = new TH1F("j8_1","Probe Ele PT",100,10.,210.);
  T2->Draw("probe_pt>>j8_1","1*(TightID == 1 && Z_mass > 60. && Z_mass <= 120. && probe_trkIso < 0.2 && probe_ecalIso < 0.45 && probe_hcalIso < 0.25 && tag_trkIso < 0.2 && tag_ecalIso < 0.45 && tag_hcalIso < 0.25 )");
  j8_1->SetFillColor(kRed);
  j8_1->SetLineColor(kRed);
  j8_1->SetLineWidth(2);
  j8_1->SetStats(0);

hs4->Add(j8_1);

j8_1->Scale(w_DYLL);
j7_1->Scale(1.);


TH1F *h7_1 = new TH1F("h7_1","Ratio",100,10.,210.);
//TH1F *h8 = new TH1F("h8","",60,76.,106.);
 TH1F *h8 = (TH1F * )j7_1->Clone();
h7_1->Add(j8_1);

hs4->Draw("hist");
j7_1->Draw("sames");

  tleg4->AddEntry(j7_1,"Data","l");
  tleg4->AddEntry(j8_1,"DY_Fall15","f");
 tleg4->SetFillColor(kWhite);
 tleg4->Draw("sames");
c4->cd();

TPad *pad12 = new TPad("pad12","pad12",0,0,1,0.2);
  // TH1F *hs1=hs->Clone();
   pad12->SetGridy(1);
   pad12->SetPad(0,0.0,1.0,0.2);
   pad12->SetTopMargin(0);
   pad12->SetBottomMargin(0.5);
   pad12->Draw();
   pad12->cd();
  float yscale11 = (1.0-0.2)/(0.18-0);
  h8->Divide(h7_1);
  h8->SetMarkerStyle(21);
  h8->SetStats(0);
//  h7->SetMinimum(0.5);
//  h7->SetMaximum(1.5);
  h8->GetYaxis()->SetTitle("Data/#Sigma MC");
  h8->SetMinimum(0.4);
  h8->SetMaximum(1.6);
  h8->GetXaxis()->SetTitle("");
  h8->GetXaxis()->SetTitleOffset(1.3);
  h8->GetXaxis()->SetLabelSize(0.033*yscale11);
  h8->GetXaxis()->SetTitleSize(0.036*yscale11);
  h8->GetXaxis()->SetTickLength(0.03*yscale11);
//h7->GetYaxis()->SetLabelFont(63);
//h7->GetYaxis()->SetLabelSize(12);
h8->GetYaxis()->SetTitleOffset(0.3);
h8->GetYaxis()->SetNdivisions(5);
h8->GetYaxis()->SetLabelSize(0.033*yscale11);
h8->GetYaxis()->SetTitleSize(0.036*yscale11);
   h8->Draw("");

c4->SaveAs("probe_Ele_pt_withoutSF_forHWW.png");
c4->Write();

//=======================

TCanvas *c5 = new TCanvas("c5", "c5",201,27,989,682);
  c5->SetFillColor(0);
 // c5->SetFrameFillColor(0);
  c5->SetFrameBorderSize(1);
//  c5->SetFrameBorderMode(-1);
//    c5->SetLogy(1);
   TPad *pad13 = new TPad("pad13","pad13",0,0.2,1,1);
   pad13->SetBottomMargin(0.03287462);
   pad13->SetLogy(1);
   pad13->Draw();
   pad13->cd();

THStack *hs5 = new THStack("hs5","Tag Ele PT");
TLegend *tleg5 = new TLegend(0.70,0.80,0.85,0.90,NULL,"brNDC");
TH1F *j9_1 = new TH1F("j9_1","Tag Ele PT",100,30.,230.);
  T1->Draw("tag_pt>>j9_1","1*(TightID == 1 && Z_mass > 60. && Z_mass <= 120. && probe_trkIso < 0.2 && probe_ecalIso < 0.45 && probe_hcalIso < 0.25 && tag_trkIso < 0.2 && tag_ecalIso < 0.45 && tag_hcalIso < 0.25 )");
  j9_1->SetLineColor(kBlack);
  j9_1->SetLineWidth(2);
  j9_1->SetStats(0);
  j9_1->Sumw2();

TH1F *j10_1 = new TH1F("j10_1","Tag Ele PT",100,30.,230.);
  T2->Draw("tag_pt>>j10_1","1*(TightID == 1 && Z_mass > 60. && Z_mass <= 120. && probe_trkIso < 0.2 && probe_ecalIso < 0.45 && probe_hcalIso < 0.25 && tag_trkIso < 0.2 && tag_ecalIso < 0.45 && tag_hcalIso < 0.25 )");
  j10_1->SetFillColor(kRed);
  j10_1->SetLineColor(kRed);
  j10_1->SetLineWidth(2);
  j10_1->SetStats(0);

hs5->Add(j10_1);

j10_1->Scale(w_DYLL);
j9_1->Scale(1.);


TH1F *h9_1 = new TH1F("h9_1","Ratio",100,30.,230.);
//TH1F *h10 = new TH1F("h10","",60,76.,106.);
 TH1F *h10 = (TH1F *)j9_1->Clone();
h9_1->Add(j10_1);

hs5->Draw("hist");
j9_1->Draw("sames");

  tleg5->AddEntry(j9_1,"Data","l");
  tleg5->AddEntry(j10_1,"DY_Fall15","f");
 tleg5->SetFillColor(kWhite);
 tleg5->Draw("sames");
c5->cd();

TPad *pad14 = new TPad("pad14","pad14",0,0,1,0.2);
  // TH1F *hs1=hs->Clone();
   pad14->SetGridy(1);
   pad14->SetPad(0,0.0,1.0,0.2);
   pad14->SetTopMargin(0);
   pad14->SetBottomMargin(0.5);
   pad14->Draw();
   pad14->cd();
  float yscale12 = (1.0-0.2)/(0.18-0);
  h10->Divide(h9_1);
  h10->SetMarkerStyle(21);
  h10->SetStats(0);
//  h9->SetMinimum(0.5);
//  h9->SetMaximum(1.5);
  h10->GetYaxis()->SetTitle("Data/#Sigma MC");
  h10->SetMinimum(0.4);
  h10->SetMaximum(1.6);
  h10->GetXaxis()->SetTitle("");
  h10->GetXaxis()->SetTitleOffset(1.3);
  h10->GetXaxis()->SetLabelSize(0.033*yscale12);
  h10->GetXaxis()->SetTitleSize(0.036*yscale12);
  h10->GetXaxis()->SetTickLength(0.03*yscale12);
//h9->GetYaxis()->SetLabelFont(63);
//h9->GetYaxis()->SetLabelSize(12);
h10->GetYaxis()->SetTitleOffset(0.3);
h10->GetYaxis()->SetNdivisions(5);
h10->GetYaxis()->SetLabelSize(0.033*yscale12);
h10->GetYaxis()->SetTitleSize(0.036*yscale12);
   h10->Draw("");

c5->SaveAs("tag_Ele_pt_withoutSF_forHWW.png");
c5->Write();

//=========================
TCanvas *c9 = new TCanvas("c9", "c9",201,27,989,682);
  c9->SetFillColor(0);
 // c7->SetFrameFillColor(0);
  c9->SetFrameBorderSize(1);
//  c7->SetFrameBorderMode(-1);
//    c7->SetLogy(1);
   TPad *pad19 = new TPad("pad19","pad19",0,0.2,1,1);
   pad19->SetBottomMargin(0.03287462);
   pad19->SetLogy(1);
   pad19->Draw();
   pad19->cd();

THStack *hs13 = new THStack("hs13","Probe Eta");
TLegend *tleg9 = new TLegend(0.85,0.80,0.95,0.90,NULL,"brNDC");
TH1F *j13_3 = new TH1F("j13_3","Probe Eta",50,-2.5,2.5);
  T1->Draw("probe_eta>>j13_3","1*(TightID == 1  && Z_mass > 60. && Z_mass <= 120. )");
  j13_3->SetLineColor(kBlack);
  j13_3->SetLineWidth(2);
  j13_3->SetStats(0);
  j13_3->Sumw2();

TH1F *j14_3 = new TH1F("j14_3","Probe Eta",50,-2.5,2.5);
  T2->Draw("probe_eta>>j14_3","1*(TightID == 1 && Z_mass > 60. && Z_mass <= 120. )");
  j14_3->SetFillColor(kRed);
  j14_3->SetLineColor(kRed);
  j14_3->SetLineWidth(2);
  j14_3->SetStats(0);

hs13->Add(j14_3);

j14_3->Scale(j13_3->Integral()/j14_3->Integral());
j13_3->Scale(1.);


TH1F *h13_3 = new TH1F("h13_3","Ratio",50,-2.5,2.5);
//TH1F *h14 = new TH1F("h14","",60,76.,106.);
 TH1F *h14 = (TH1F *)j13_3->Clone();
h13_3->Add(j14_3);

hs13->Draw("hist");
j13_3->Draw("sames");

  tleg9->AddEntry(j13_3,"Data","l");
  tleg9->AddEntry(j14_3,"DY_Fall15","f");
 tleg9->SetFillColor(kWhite);
 tleg9->Draw("sames");
c9->cd();

TPad *pad20 = new TPad("pad20","pad20",0,0,1,0.2);
  // TH1F *hs1=hs->Clone();
   pad20->SetGridy(1);
   pad20->SetPad(0,0.0,1.0,0.2);
   pad20->SetTopMargin(0);
   pad20->SetBottomMargin(0.5);
   pad20->Draw();
   pad20->cd();
  float yscale20 = (1.0-0.2)/(0.18-0);
  h14->Divide(h13_3);
  h14->SetMarkerStyle(21);
  h14->SetStats(0);
//  h13->SetMinimum(0.5);
//  h13->SetMaximum(1.5);
  h14->GetYaxis()->SetTitle("Data/#Sigma MC");
  h14->SetMinimum(0.4);
  h14->SetMaximum(1.6);
  h14->GetXaxis()->SetTitle("");
  h14->GetXaxis()->SetTitleOffset(1.3);
  h14->GetXaxis()->SetLabelSize(0.033*yscale20);
  h14->GetXaxis()->SetTitleSize(0.036*yscale20);
  h14->GetXaxis()->SetTickLength(0.03*yscale20);
//h13->GetYaxis()->SetLabelFont(63);
//h13->GetYaxis()->SetLabelSize(12);
h14->GetYaxis()->SetTitleOffset(0.3);
h14->GetYaxis()->SetNdivisions(5);
h14->GetYaxis()->SetLabelSize(0.033*yscale20);
h14->GetYaxis()->SetTitleSize(0.036*yscale20);
   h14->Draw("");

c9->SaveAs("probe_Ele_eta.png");
c9->Write();

 
TCanvas *c7 = new TCanvas("c7", "c7",201,27,989,682);
  c7->SetFillColor(0);
 // c7->SetFrameFillColor(0);
  c7->SetFrameBorderSize(1);
//  c7->SetFrameBorderMode(-1);
//    c7->SetLogy(1);
   TPad *pad17 = new TPad("pad17","pad17",0,0.2,1,1);
   pad17->SetBottomMargin(0.03287462);
   pad17->SetLogy(1);
   pad17->Draw();
   pad17->cd();

THStack *hs10 = new THStack("hs10","Tag Eta");
TLegend *tleg7 = new TLegend(0.85,0.80,0.95,0.90,NULL,"brNDC");
TH1F *j13_1 = new TH1F("j13_1","Tag Eta",50,-2.5,2.5);
  T1->Draw("tag_eta>>j13_1","1*(TightID == 1  && Z_mass > 60. && Z_mass <= 120. )");
  j13_1->SetLineColor(kBlack);
  j13_1->SetLineWidth(2);
  j13_1->SetStats(0);
  j13_1->Sumw2();

TH1F *j14_1 = new TH1F("j14_1","Tag Eta",50,-2.5,2.5);
  T2->Draw("tag_eta>>j14_1","1*(TightID == 1  && Z_mass > 60. && Z_mass <= 120. )");
  j14_1->SetFillColor(kRed);
  j14_1->SetLineColor(kRed);
  j14_1->SetLineWidth(2);
  j14_1->SetStats(0);

hs10->Add(j14_1);

j14_1->Scale(j13_1->Integral()/j14_1->Integral());
j13_1->Scale(1.);


TH1F *h13_1 = new TH1F("h13_1","Ratio",50,-2.5,2.5);
//TH1F *h16 = new TH1F("h16","",60,76.,106.);
 TH1F *h16 = (TH1F *)j13_1->Clone();
h13_1->Add(j14_1);

hs10->Draw("hist");
j13_1->Draw("sames");

  tleg7->AddEntry(j13_1,"Data","l");
  tleg7->AddEntry(j14_1,"DY_Fall15","f");
 tleg7->SetFillColor(kWhite);
 tleg7->Draw("sames");
c7->cd();

TPad *pad18 = new TPad("pad18","pad18",0,0,1,0.2);
  // TH1F *hs1=hs->Clone();
   pad18->SetGridy(1);
   pad18->SetPad(0,0.0,1.0,0.2);
   pad18->SetTopMargin(0);
   pad18->SetBottomMargin(0.5);
   pad18->Draw();
   pad18->cd();
  float yscale18 = (1.0-0.2)/(0.18-0);
  h16->Divide(h13_1);
  h16->SetMarkerStyle(21);
  h16->SetStats(0);
//  h13->SetMinimum(0.5);
//  h13->SetMaximum(1.5);
  h16->GetYaxis()->SetTitle("Data/#Sigma MC");
  h16->SetMinimum(0.4);
  h16->SetMaximum(1.6);
  h16->GetXaxis()->SetTitle("");
  h16->GetXaxis()->SetTitleOffset(1.3);
  h16->GetXaxis()->SetLabelSize(0.033*yscale18);
  h16->GetXaxis()->SetTitleSize(0.036*yscale18);
  h16->GetXaxis()->SetTickLength(0.03*yscale18);
//h13->GetYaxis()->SetLabelFont(63);
//h13->GetYaxis()->SetLabelSize(12);
h16->GetYaxis()->SetTitleOffset(0.3);
h16->GetYaxis()->SetNdivisions(5);
h16->GetYaxis()->SetLabelSize(0.033*yscale18);
h16->GetYaxis()->SetTitleSize(0.036*yscale18);
   h16->Draw("");

c7->SaveAs("tag_Ele_eta.png");
c7->Write();
//===============================

TCanvas *c17 = new TCanvas("c17", "c17",201,27,989,682);
  c17->SetFillColor(0);
 // c7->SetFrameFillColor(0);
  c17->SetFrameBorderSize(1);
//  c7->SetFrameBorderMode(-1);
//    c7->SetLogy(1);
   TPad *pad27 = new TPad("pad27","pad27",0,0.2,1,1);
   pad27->SetBottomMargin(0.03287462);
   pad27->SetLogy(1);
   pad27->Draw();
   pad27->cd();

THStack *hs20 = new THStack("hs20","Tag Phi");
TLegend *tleg17 = new TLegend(0.85,0.80,0.95,0.90,NULL,"brNDC");
TH1F *j23_1 = new TH1F("j23_1","Tag Phi",50,-3.1415,3.1415);
  T1->Draw("tag_phi>>j23_1","1*(TightID == 1  && Z_mass > 60. && Z_mass <= 120. )");
  j23_1->SetLineColor(kBlack);
  j23_1->SetLineWidth(2);
  j23_1->SetStats(0);
  j23_1->Sumw2();

TH1F *j24_1 = new TH1F("j24_1","Tag Phi",50,-3.1415,3.1415);
  T2->Draw("tag_phi>>j24_1","1*(TightID == 1  && Z_mass > 60. && Z_mass <= 120. )");
  j24_1->SetFillColor(kRed);
  j24_1->SetLineColor(kRed);
  j24_1->SetLineWidth(2);
  j24_1->SetStats(0);

hs20->Add(j24_1);

j24_1->Scale(j23_1->Integral()/j24_1->Integral());
j23_1->Scale(1.);


TH1F *h23_1 = new TH1F("h23_1","Ratio",50,-3.1415,3.1415);
//TH1F *h16 = new TH1F("h16","",60,76.,106.);
 TH1F *h26 = (TH1F *)j23_1->Clone();
h23_1->Add(j24_1);

hs20->Draw("hist");
j23_1->Draw("sames");

  tleg17->AddEntry(j23_1,"Data","l");
  tleg17->AddEntry(j24_1,"DY_Fall15","f");
 tleg17->SetFillColor(kWhite);
 tleg17->Draw("sames");
c17->cd();

TPad *pad28 = new TPad("pad28","pad28",0,0,1,0.2);
  // TH1F *hs1=hs->Clone();
   pad28->SetGridy(1);
   pad28->SetPad(0,0.0,1.0,0.2);
   pad28->SetTopMargin(0);
   pad28->SetBottomMargin(0.5);
   pad28->Draw();
   pad28->cd();
  float yscale28 = (1.0-0.2)/(0.18-0);
  h26->Divide(h23_1);
  h26->SetMarkerStyle(21);
  h26->SetStats(0);
//  h13->SetMinimum(0.5);
//  h13->SetMaximum(1.5);
  h26->GetYaxis()->SetTitle("Data/#Sigma MC");
  h26->SetMinimum(0.4);
  h26->SetMaximum(1.6);
  h26->GetXaxis()->SetTitle("");
  h26->GetXaxis()->SetTitleOffset(1.3);
  h26->GetXaxis()->SetLabelSize(0.033*yscale18);
  h26->GetXaxis()->SetTitleSize(0.036*yscale18);
  h26->GetXaxis()->SetTickLength(0.03*yscale18);
//h13->GetYaxis()->SetLabelFont(63);
//h13->GetYaxis()->SetLabelSize(12);
h26->GetYaxis()->SetTitleOffset(0.3);
h26->GetYaxis()->SetNdivisions(5);
h26->GetYaxis()->SetLabelSize(0.033*yscale18);
h26->GetYaxis()->SetTitleSize(0.036*yscale18);
   h26->Draw("");

c17->SaveAs("tag_Ele_phi.png");
c17->Write();

//===========================
TCanvas *c27 = new TCanvas("c27", "c27",201,27,989,682);
  c27->SetFillColor(0);
 // c7->SetFrameFillColor(0);
  c27->SetFrameBorderSize(1);
//  c7->SetFrameBorderMode(-1);
//    c7->SetLogy(1);
   TPad *pad37 = new TPad("pad37","pad37",0,0.2,1,1);
   pad37->SetBottomMargin(0.03287462);
   pad37->SetLogy(1);
   pad37->Draw();
   pad37->cd();

THStack *hs30 = new THStack("hs30","Probe Phi");
TLegend *tleg27 = new TLegend(0.85,0.80,0.95,0.90,NULL,"brNDC");
TH1F *j33_1 = new TH1F("j33_1","Probe Phi",50,-3.1415,3.1415);
  T1->Draw("probe_phi>>j33_1","1*(TightID == 1  && Z_mass > 60. && Z_mass <= 120. )");
  j33_1->SetLineColor(kBlack);
  j33_1->SetLineWidth(2);
  j33_1->SetStats(0);
  j33_1->Sumw2();

TH1F *j34_1 = new TH1F("j34_1","Probe Phi",50,-3.1415,3.1415);
  T2->Draw("probe_phi>>j34_1","1*(TightID == 1  && Z_mass > 60. && Z_mass <= 120. )");
  j34_1->SetFillColor(kRed);
  j34_1->SetLineColor(kRed);
  j34_1->SetLineWidth(2);
  j34_1->SetStats(0);

hs30->Add(j34_1);

j34_1->Scale(j33_1->Integral()/j34_1->Integral());
j33_1->Scale(1.);


TH1F *h33_1 = new TH1F("h33_1","Ratio",50,-3.1415,3.1415);
//TH1F *h16 = new TH1F("h16","",60,76.,106.);
 TH1F *h36 = (TH1F *)j33_1->Clone();
h33_1->Add(j34_1);

hs30->Draw("hist");
j33_1->Draw("sames");

  tleg27->AddEntry(j33_1,"Data","l");
  tleg27->AddEntry(j34_1,"DY_Fall15","f");
 tleg27->SetFillColor(kWhite);
 tleg27->Draw("sames");
c27->cd();

TPad *pad38 = new TPad("pad38","pad38",0,0,1,0.2);
  // TH1F *hs1=hs->Clone();
   pad38->SetGridy(1);
   pad38->SetPad(0,0.0,1.0,0.2);
   pad38->SetTopMargin(0);
   pad38->SetBottomMargin(0.5);
   pad38->Draw();
   pad38->cd();
  float yscale38 = (1.0-0.2)/(0.18-0);
  h36->Divide(h33_1);
  h36->SetMarkerStyle(21);
  h36->SetStats(0);
//  h13->SetMinimum(0.5);
//  h13->SetMaximum(1.5);
  h36->GetYaxis()->SetTitle("Data/#Sigma MC");
  h36->SetMinimum(0.4);
  h36->SetMaximum(1.6);
  h36->GetXaxis()->SetTitle("");
  h36->GetXaxis()->SetTitleOffset(1.3);
  h36->GetXaxis()->SetLabelSize(0.033*yscale18);
  h36->GetXaxis()->SetTitleSize(0.036*yscale18);
  h36->GetXaxis()->SetTickLength(0.03*yscale18);
//h13->GetYaxis()->SetLabelFont(63);
//h13->GetYaxis()->SetLabelSize(12);
h36->GetYaxis()->SetTitleOffset(0.3);
h36->GetYaxis()->SetNdivisions(5);
h36->GetYaxis()->SetLabelSize(0.033*yscale18);
h36->GetYaxis()->SetTitleSize(0.036*yscale18);
   h36->Draw("");

c27->SaveAs("probe_Ele_phi.png");
c27->Write();

//==================

TCanvas *c8 = new TCanvas("c8", "c8",201,27,989,682);
  c8->SetFillColor(0);
 // c7->SetFrameFillColor(0);
  c8->SetFrameBorderSize(1);
//  c7->SetFrameBorderMode(-1);
//    c7->SetLogy(1);
   TPad *pad7 = new TPad("pad7","pad7",0,0.2,1,1);
   pad7->SetBottomMargin(0.03287462);
   pad7->SetLogy(1);
   pad7->Draw();
   pad7->cd();

THStack *hs7 = new THStack("hs7","Di-Lepton PT");
TLegend *tleg8 = new TLegend(0.70,0.80,0.85,0.90,NULL,"brNDC");
TH1F *j13_2 = new TH1F("j13_2","Di-Lepton PT",100,0.,200.);
  T1->Draw("Z_pt>>j13_2","1*(TightID == 1 && probe_abseta < 1.5 && tag_abseta < 1.5 && Z_mass > 60. && Z_mass <= 120. )");
  j13_2->SetLineColor(kBlack);
  j13_2->SetLineWidth(2);
  j13_2->SetStats(0);
  j13_2->Sumw2();

TH1F *j14_2 = new TH1F("j14_2","Di-Lepton PT",100,0.,200.);
  T2->Draw("Z_pt>>j14_2","1*(TightID == 1 && probe_abseta < 1.5 && tag_abseta < 1.5 && Z_mass > 60. && Z_mass <= 120. )");
  j14_2->SetFillColor(kRed);
  j14_2->SetLineColor(kRed);
  j14_2->SetLineWidth(2);
  j14_2->SetStats(0);

hs7->Add(j14_2);

j14_2->Scale(j13_2->Integral()/j14_2->Integral());
j13_2->Scale(1.);


TH1F *h13_2 = new TH1F("h13_2","Ratio",100,0.,200.);
//TH1F *h18 = new TH1F("h18","",60,76.,106.);
 TH1F *h18 = (TH1F *) j13_2->Clone();
h13_2->Add(j14_2);

hs7->Draw("hist");
j13_2->Draw("sames");

  tleg8->AddEntry(j13_2,"Data","l");
  tleg8->AddEntry(j14_2,"DY_Fall15","f");
 tleg8->SetFillColor(kWhite);
 tleg8->Draw("sames");
c8->cd();

TPad *pad8 = new TPad("pad8","pad8",0,0,1,0.2);
  // TH1F *hs1=hs->Clone();
   pad8->SetGridy(1);
   pad8->SetPad(0,0.0,1.0,0.2);
   pad8->SetTopMargin(0);
   pad8->SetBottomMargin(0.5);
   pad8->Draw();
   pad8->cd();
  float yscale7 = (1.0-0.2)/(0.18-0);
  h18->Divide(h13_2);
  h18->SetMarkerStyle(21);
  h18->SetStats(0);
//  h13->SetMinimum(0.5);
//  h13->SetMaximum(1.5);
  h18->GetYaxis()->SetTitle("Data/#Sigma MC");
  h18->SetMinimum(0.4);
  h18->SetMaximum(1.6);
  h18->GetXaxis()->SetTitle("");
  h18->GetXaxis()->SetTitleOffset(1.3);
  h18->GetXaxis()->SetLabelSize(0.033*yscale7);
  h18->GetXaxis()->SetTitleSize(0.036*yscale7);
  h18->GetXaxis()->SetTickLength(0.03*yscale7);
//h13->GetYaxis()->SetLabelFont(63);
//h13->GetYaxis()->SetLabelSize(12);
h18->GetYaxis()->SetTitleOffset(0.3);
h18->GetYaxis()->SetNdivisions(5);
h18->GetYaxis()->SetLabelSize(0.033*yscale7);
h18->GetYaxis()->SetTitleSize(0.036*yscale7);
   h18->Draw("");

c8->SaveAs("pair_pt_barrel_PP.png");
c8->Write();

file->Close();
}
