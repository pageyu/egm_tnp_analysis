void plotMacro(){
    const char *fileName[3] = {
        "plot_DataMCnewLoose_IdIsoSF_RecoSF_runCDE",
        //"plot_DataMCnewLoose_IdIsoSF_RecoSF_runB",
        //"plot_DataMCnewLoose_IdIsoSF_RecoSF_runC",
        //"plot_DataMCnewLoose_IdIsoSF_RecoSF_runD",
        //"plot_DataMCnewLoose_IdIsoSF_RecoSF_runE",
        //"plot_DataMCnewLoose_IdIsoSF_RecoSF_runF",
        //"plot_DataMCnewLoose_noSFs_runF",
    };
    //const char *fileName[7] = {
        //"NoSF",
        //"IdIsoSF",
        //"IdIsoRecoSF",
        //"TightSF",
        //"TightFinnerBinSF",
        //"noSCEtafinerBinSF",
        //"noSCEtaSF"
    //};
    //
    const char *variable[11] = {
        "tagEleEta",
        //"tagElePt", 
        "probeScEta",
        "probePt",
        "ZMass",
        "el_sieie",
        "el_hoe",
        "el_1overEminus1overP",
        "el_reliso03",
        "el_dr03TkSumPt",
        "el_dr03EcalRecHitSumEt",
        "el_dr03HcalDepth1TowerSumEt"
    };
    for(int ifi = 0; ifi< 1; ifi++){
        for(int iv = 0; iv< 11; iv++){
            TCanvas *c1 = new TCanvas("c1", "c1", 201, 27, 989, 682);
            c1->SetFillColor(0);
            c1->SetFrameBorderSize(1);
            TFile *file = new TFile(TString::Format("%s.root",fileName[ifi]).Data());
            //TFile *file = new TFile(TString::Format("%s.root",fileName[ifi]).Data());
            TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1);
            pad1->SetBottomMargin(0.03287462);
            pad1->SetLogy(1);
            pad1->Draw();
            pad1->cd();

            TLegend *tleg = new TLegend(0.70, 0.80, 0.85, 0.90, NULL, "brNDC");

            TH1F *dataDist = (TH1F*)file->Get(TString::Format("h_data_%s",variable[iv]).Data());
            dataDist->SetLineColor(kBlack);
            dataDist->SetLineWidth(2);
            dataDist->SetStats(0);
            dataDist->Sumw2();

            TH1F *mcDist = (TH1F*)file->Get(TString::Format("h_mc_%s",variable[iv]).Data()); 
            mcDist->SetFillColor(kBlue);
            mcDist->SetLineColor(kBlue);
            mcDist->SetLineWidth(2);
            mcDist->SetStats(0);

            //cout << "MC = " << mcDist->GetSumOfWeights() << endl;
            //cout << "Data = " << dataDist->GetSumOfWeights() << endl;

            //mcDist->Scale(dataDist->GetSumOfWeights()/mcDist->GetSumOfWeights());
            //mcDist->Scale((5334*1000*42.186)/49125561);//Full2017
            //mcDist->Scale((5334*1000*(42.186-13.5-4.823))/(49125561*3));//haddRunCDE
            //
            //mcDist->Scale((5334*1000*4.823 )/49125561);//RunB
            //mcDist->Scale((5334*1000*9.664 )/49125561);//RunC
            //mcDist->Scale((5334*1000*4.252 )/49125561);//RunD
            mcDist->Scale((5334*1000*9.278 )/49125561);//RunE
            //mcDist->Scale((5334*1000*13.540)/49125561);//RunF
            mcDist->Draw("hist");
            dataDist->Draw("sames");

            tleg->AddEntry(dataDist, "Data", "l");
            tleg->AddEntry(mcDist, "DY_Madgraph", "f");
            tleg->SetFillColor(kWhite);
            tleg->Draw("sames");
            c1->cd();

            TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.3);
            pad2->SetGridy(1);
            pad2->SetPad(0, 0.0, 1.0, 0.3);
            pad2->SetTopMargin(0);
            pad2->SetBottomMargin(0.2);
            pad2->Draw();
            pad2->cd();
            float yscale = (1.0 - 0.2) / (0.18 - 0);
            TH1F *ratioMD=dataDist->Clone();
            ratioMD->Divide(mcDist);
            ratioMD->SetMarkerStyle(21);
            ratioMD->SetStats(0);
            ratioMD->GetYaxis()->SetTitle("Data/#Sigma MC");
            //ratioMD->SetMinimum(0);
            //ratioMD->SetMaximum(2.0);
            ratioMD->SetMinimum(0.5);
            ratioMD->SetMaximum(1.5);
            ratioMD->GetXaxis()->SetTitle("");
            ratioMD->GetXaxis()->SetTitleOffset(1.3);
            ratioMD->GetXaxis()->SetLabelSize(0.033 * yscale);
            ratioMD->GetXaxis()->SetTitleSize(0.036 * yscale);
            ratioMD->GetXaxis()->SetTickLength(0.03 * yscale);
            ratioMD->GetYaxis()->SetTitleOffset(0.3);
            ratioMD->GetYaxis()->SetNdivisions(10);
            ratioMD->GetYaxis()->SetLabelSize(0.022 * yscale);
            //ratioMD->GetYaxis()->SetLabelSize(0.033 * yscale);
            ratioMD->GetYaxis()->SetTitleSize(0.036 * yscale);
            ratioMD->Draw("");

            c1->SaveAs(TString::Format("%s%s.png",variable[iv],fileName[ifi]).Data());
        }
    }
}
