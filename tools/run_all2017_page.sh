#!/usr/bin/env bash

tag="_RunB"

settings="settings_ele_2017.py"
for wp in "passingMVA94Xwp90isoHWW" "passingMVA94Xwp90isoSSHWW" 
do
    echo $wp
    python tnpEGM_fitter.py ${settings} --flag $wp --checkBins
    python tnpEGM_fitter.py ${settings} --flag $wp --createBins
    python tnpEGM_fitter.py ${settings} --flag $wp --createHists

    python tnpEGM_fitter.py ${settings} --flag $wp --doFit                  > doFit${tag}.log 2>&1 
    python tnpEGM_fitter.py ${settings} --flag $wp --doFit --mcSig --altSig > doFit_mcSig_altSig${tag}.log 2>&1
    python tnpEGM_fitter.py ${settings} --flag $wp --doFit --altSig         > doFit_altSig${tag}.log 2>&1
    python tnpEGM_fitter.py ${settings} --flag $wp --doFit --altBkg         > doFit_altBkg${tag}.log 2>&1 
    python tnpEGM_fitter.py ${settings} --flag $wp --sumUp
done

