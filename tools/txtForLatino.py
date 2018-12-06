#!/usr/bin/env python

import os 
import re

def makeTable(fname):
    f = file(fname)
    for line in f:
        line = [ float(l) for l in line.split() ] if len(line.split()) == 12 else [0,0]
        if len(line) != 12:
            continue
        line[8] = abs((line[4] - line[8]))
        line[9] = abs((line[4] - line[9]))
        line[10] = abs((line[6] - line[10]))
        line[11] = abs((line[6] - line[11]))
        for n in line:
            print '{:8.3f}'.format(n),
        print ''
    f.close()

if __name__ == "__main__":
    makeTable("./results/Moriond18/tnpEleID/runC_HWW/passingMVA94Xwp90isoHWW/egammaEffi.txt")
    # makeTable("./results/Moriond18/tnpEleID/runCDE_HWWSS/passingMVA94Xwp90isoSSHWW/egammaEffi.txt")
    # makeTable("./results/Moriond17/tnpEleID/run2016_POGd0dzFixmcAlt/passingTight80XTriChg/egammaEffi.txt")


