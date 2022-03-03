Double_t funexp(Double_t *x,Double_t *par)
{
  Double_t exp1 = 0;
  Double_t exp2 = 0;
  Double_t fact = 0;
  Double_t results = 0;

   exp1 = TMath::Exp(-par[1]*(x[0]-par[3]));
   exp2 = TMath::Exp(-par[2]*(x[0]-par[3]));

  fact = par[0]*((par[1]*par[2])/(par[2]-par[1]));

  results = fact*(exp1-exp2);

  if(results > 0)
    return results;
  else
  return 0;
}

void fitPulse(TString filename, Float_t fitMin=-0.1e-6, Float_t fitMax=0.8e-6)
{
  gStyle->SetOptFit(1);
  TFile *_file0 = TFile::Open(filename);
  // TFile *_file0 = TFile::Open("cylinder1_stripped.root");

  TH1F *hi;
  TF1 *fexp = new TF1("fexp",funexp,0,10000,4);

  TTree *tree = (TTree*)gFile->Get("tree");
	// TCanvas *fitcan = new TCanvas("fitcan","fitting canvas");
	// fitcan->Draw();

  int n=tree->Draw("-y:x","","goff");
  TGraph* g=new TGraph(n,tree->GetV2(),tree->GetV1());
  g->SetTitle("Pulse Fit");
  g->Draw("AL");
	fexp->SetParameter(0,1e-8);
  // These are 1/time constants for the two exponential
	fexp->SetParameter(1,100000000); // fast, rising edge
	fexp->SetParameter(2,10000000); // slower falling edge
	fexp->SetParameter(3,0);

  g->Fit("fexp","R+","",fitMin,fitMax);

  cout << "Time Constant 1 (rising): " << 1e9/(fexp->GetParameter(1)) << " ns" << endl;
  cout << "Time Constant 2 (falling): " << 1e9/(fexp->GetParameter(2)) << " ns" << endl;
}

void help(){
  cout <<"\nfitPulse(TString filename, Float_t fitMin=-0.1e-6, Float_t fitMax=0.8e-6)\n\n";
  cout <<"Fit a fast rising and slower decaying exponential to a pulse.\n";
  cout <<"'filename' should be the name of a '.root' file which contains a single pulse, as produced by 'csv2ROOT.c'.\n";
  cout <<"The range of the fit can be specified with 'fitMin' and 'fitMax'.\n";
  cout <<"The initial guesses for the time constants are 10 ns and 100 ns respectively.\n";
  cout <<"If your pulse is very different to these, you may need to change them in the code.\n"<<endl;
}
