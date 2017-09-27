#!/usr/bin/env bash

#tag="_fineEta"
tag="_RunBCD"
#tag="_RunEF"
#tag="_RunGH"
settings="etc/config/settings_ele_page.py"

#for wp in "passingTight80X" "passingTight80XTriChg" "passingMVA80Xwp80Iso15" "passingMVA80Xwp80Iso16" "passingMVA80Xwp90Iso15" "passingMVA80Xwp90Iso16"
for wp in "passingMVA80Xwp90Iso16"
do
    echo $wp
    python tnpEGM_fitter.py ${settings} --flag $wp --checkBins
    python tnpEGM_fitter.py ${settings} --flag $wp --createBins
    python tnpEGM_fitter.py ${settings} --flag $wp --createHists

    #python tnpEGM_fitter.py ${settings} --flag $wp --doFit                  > doFit${tag}.log 2>&1 
    #python tnpEGM_fitter.py ${settings} --flag $wp --doFit --mcSig --altSig > doFit_mcSig_altSig${tag}.log 2>&1
    #python tnpEGM_fitter.py ${settings} --flag $wp --doFit --altSig         > doFit_altSig${tag}.log 2>&1
    #python tnpEGM_fitter.py ${settings} --flag $wp --doFit --altBkg         > doFit_altBkg${tag}.log 2>&1 
    #python tnpEGM_fitter.py ${settings} --flag $wp --sumUp
done

