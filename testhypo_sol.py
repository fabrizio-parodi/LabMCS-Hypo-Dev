from   sys   import *
from   math  import *
from   ROOT  import *
import numpy as np
from   scipy import stats

file1 = open("s1.dat")
file2 = open("s2.dat")

h1 = TH1D("h1","",12,0,0.5)
h2 = TH1D("h2","",12,0,0.5)

x1 = np.array([])
for line in file1:
    val = line.split()
    x1 = np.append(x1,float(val[0]))
    h1.Fill(float(val[0]))

x2 = np.array([])
for line in file2:
    val = line.split()
    x2 = np.append(x2,float(val[0]))
    h2.Fill(float(val[0]))

h1.SetLineColor(kRed)    
h1.Draw("E")

h2.Draw("ESAME")
gApplication.Run(True)


# test del chi2
p = h1.Chi2Test(h2)
print("chi2Test p-value ", p)

# test unbinned KS 2 campioni
t_ks2, p_ks2 = stats.ks_2samp(x1, x2)
print("KS two-sample p-value ", p_ks2)

# test unbinned KS 1 pdf
n = stats.expon(loc=0.0,scale=0.1)
t_ks, p_ks = stats.kstest(x1, n.cdf)
print("KS p-value ", p_ks)

f = TF1("exp","[0]/[1]*exp(-x/[1])",0,0.5);
f.SetParameter(1,1)
h1.Fit("exp","L")

print(f.GetProb())
print(TMath.Prob(f.GetChisquare(),h1.GetNbinsX()-2))


