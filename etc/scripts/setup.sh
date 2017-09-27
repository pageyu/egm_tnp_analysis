#!/usr/bin/env bash

optVer=x86_64-slc6-gcc48-opt
LCG="/cvmfs/sft.cern.ch/lcg"
ROOTSYS=${LCG}/app/releases/ROOT/6.06.06/${optVer}/root/
. ${LCG}/external/gcc/4.8.1/${optVer}/setup.sh
. ${ROOTSYS}/bin/thisroot.sh
 
#. /opt/rh/python27/enable
export PYTHONPREFIX="${LCG}/external/Python/2.7.4/x86_64-slc6-gcc48-opt"
export PATH="${PYTHONPREFIX}/bin:${PATH}"
export LD_LIBRARY_PATH="${PYTHONPREFIX}/lib:${LD_LIBRARY_PATH}"
export PYTHONPATH=.:${PYTHONPATH}
