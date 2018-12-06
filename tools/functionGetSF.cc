// vim: set sw=4 sts=4 fdm=marker et:

//Author          : Po-Hsun Chen (pohsun.chen.hep@gmail.com)
//Last Modified   : 14 Nov 2018 17:26 

//double wgt(double x, double y){
    //return x+y;
//}


#include "TFile.h"
#include "TH2F.h"
#include <string>

const int nSFHist=2;
TH2F *sfHist[]={0,0};

void setSFHist(std::string fname, int iHist = 0){
    if (iHist > nSFHist) {return;}
    TFile *f = new TFile(fname.c_str());
    sfHist[iHist] = (TH2F*)f->Get("EGamma_SF2D");
    if (sfHist[iHist]==0 ){
        printf("sfHist is empty.");
    }
}

float getSFPtEta(float probePt, float probeEta, float tagPt, float tagEta, unsigned int runSFBits=(unsigned int)pow(2.,nSFHist)-1){
    double sfOut = 1.;
    for(int iSF=0; iSF<nSFHist; iSF++){
        //if (sfHist[iSF] == 0 || !(runSFBits>>iSF & 1) ){continue;}
        //if (sfHist[iSF] == 0 ||  ) ){continue;}
        float probePtB  = probePt;
        float tagPtB    = tagPt;
        if(probePt >= sfHist[iSF]->GetYaxis()->GetXmax()){
            probePtB = sfHist[iSF]->GetYaxis()->GetXmax()-0.001;
        }
        if(tagPt >= sfHist[iSF]->GetYaxis()->GetXmax()){
            tagPtB = sfHist[iSF]->GetYaxis()->GetXmax()-0.001;
        }
        if(probePtB < 25 &&  probePtB >= 15){
            probePtB = 25;
        }
        int binProbeEta = sfHist[iSF]->GetXaxis()->FindFixBin(probeEta);
        int binProbePt  = sfHist[iSF]->GetYaxis()->FindFixBin(probePtB);
        int binTagEta   = sfHist[iSF]->GetXaxis()->FindFixBin(tagEta);
        int binTagPt    = sfHist[iSF]->GetYaxis()->FindFixBin(tagPtB);
        
        //float sfTest = sfHist[iSF]->GetBinContent(binProbeEta,binProbePt)*sfHist[iSF]->GetBinContent(binTagEta,binTagPt);
        //sfOut*= sfTest;
        sfOut*= sfHist[iSF]->GetBinContent(binProbeEta,binProbePt)*sfHist[iSF]->GetBinContent(binTagEta,binTagPt);
        //printf("The %dst sfOut = %f\n",iSF,sfTest);
    }
    return sfOut;
}
