#include <iostream>
#include <fstream>
#include <TRandom3.h>
#include <TApplication.h>
#include <TH1D.h>
#include <TF1.h>
#include <TMath.h>

using namespace std;

int main(){

  // bkg 1000, 40 sig -> high stat
  // bkg  500, 20 sig -> low stat
  TRandom3 rnd;
  rnd.SetSeed(123456798);
  int nbkg=1000;
  int nsig=40;
  double tau=10;
  double xcen=15,xsig=0.6;

  ofstream f_out("out.dat");
  TApplication app("app",NULL,NULL);
  TH1D h("h","",80,0,40);
  double x;
  for (int i=0;i<nbkg;i++){
    x = rnd.Exp(tau);
    h.Fill(x);
    f_out << x << std::endl;
  }
  for (int i=0;i<nsig;i++){
    x = rnd.Gaus(xcen,xsig);
    h.Fill(x);
    f_out << x << std::endl;
  }

  TF1 f("f","1/[0]*exp(-x/[0])",0,1);
  f.SetParameter(0,tau);
  double nexp = nbkg*f.Integral(14,16);
  std::cout << nbkg*f.Integral(14,16) << std::endl;
  std::cout << nbkg*f.Integral(13,17) << std::endl;
  h.Draw();
  
  double nobs = h.GetBinContent(15)+h.GetBinContent(16);
  std::cout << nobs << std::endl;


  TF1 poi("poi","TMath::Poisson(x,[0])",0,1);
  poi.SetParameter(0,nexp);
  double prob = 0;
  for (int i=0;i<=nobs;i++){
    prob += poi.Eval(i);
  }
  prob = 1-prob;
  std::cout << "Prob " << prob << std::endl;

  double sig = nobs-nexp;
  double bkg = nexp;
  std::cout << "Significance " << -TMath::NormQuantile(prob) << std::endl;
  //ErfcInverse(x/sqrt(2.)) << std::endl;
  std::cout << "Significance S/sqrt(B) " << sig/sqrt(bkg) << std::endl;
  double S0 = sqrt(2*nobs*log(1+sig/bkg)-2*sig);
  std::cout << "Significance corr.     " << S0 << std::endl;

  double lee  = 1-pow(1-prob,15.);
  std::cout  << lee << std::endl;

  app.Run(true);
  
  return 0;

}
