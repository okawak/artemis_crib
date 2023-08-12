// MUXParamMaker_1miss_strip.C
// this creates the MUX position parameters
// only for mux3-2 (tel5_dE2Y) pos1 (one missing strip 15 peaks)

#include <algorithm>
#include <iterator>
#include <vector>

void Usage_1miss()
{
  std::cout << "MUX position calibration" << std::endl;
  std::cout << "Usage: MUXParamMaker_1miss_strip(TH1* h1, TString output=\"prm/si26a/test/test.dat, const Int_t peaknum=15\");" << std::endl;
  std::cout << "\th1     : create position histogram before using this" << std::endl;
  std::cout << "\toutput : the name of parameter file" << std::endl;
  std::cout << "\tpeaknum: the number of peaks" << std::endl;
}

void MUXParamMaker_1miss_strip(TH1* h1=NULL, TString output="prm/si26a/test/test.dat", const Int_t peaknum=15)
{
  if(!h1){
    Usage_1miss();
    return;
  }
  if(output == "prm/si26a/test/test.dat"){
    std::cout << "Warning: output file name is DEFAULT" << std::endl;
  }

  TSpectrum *spec = new TSpectrum(peaknum,1);
  std::ofstream fout(output.Data());
  std::cout << "--Info: " << output << " is created" << std::endl;
  fout << "# " << output << " is created from MUXParamMaker_1miss_strip.C" << endl;

  Int_t nfound = spec->Search(h1, 2, "", 0.001);
  if(nfound != peaknum){
    std::cout << "Error: 33 in MUXParamMaker: cannot find " << peaknum << " peaks (only found " << nfound << " peaks)" << std::endl;
      for(Int_t i=0; i<peaknum; ++i){
        fout << "0.0 0.0" << endl;
      }
    fout.close();
    return;
  }
  Double_t *xpeaks = spec->GetPositionX();
  std::sort(xpeaks, xpeaks + peaknum);

  std::vector<Double_t> x(peaknum, 0.0);
  TF1 *f[peaknum];
  for(Int_t i=0; i<peaknum; ++i){
    TString tmp;
    tmp.Form("f[%d]",i);
    f[i] = new TF1(tmp.Data(), "gaus(0)");
    f[i]->SetRange(xpeaks[i]-10.0, xpeaks[i]+10.0);
    f[i]->SetParameters(100, xpeaks[i], 1);
    f[i]->SetParLimits(2, 0, 100);
    h1->Fit(f[i], "rq");
    x[i] = f[i]->GetParameter(1);
    f[i]->Draw("same");
  }

  fout << x[0]-10.0 << " " << (x[0] + x[1])/2.0 << endl;
  for(Int_t i=1; i<peaknum-1; ++i){
    fout << (x[i-1] + x[i])/2.0 << " " << (x[i] + x[i+1])/2.0 << endl;
    // below is the difference
    if(i == 10){
      fout << (x[i] + x[i+1])/2.0 << " " << (x[i] + x[i+1])/2.0 << endl;
    }
  }
  fout << (x[peaknum-2] + x[peaknum-1])/2.0 << " " << x[peaknum-1]+10 << endl;


  fout.close();


}
