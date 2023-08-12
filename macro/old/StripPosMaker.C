//From the configuration of F3 chamber, it calculates the positions of center of strip. (16x16 strip detector 50mm x 50mm)
//the output is (z, x)
// y: upper direction (not change by the detector position)
// z: beam direction
// x: direction to be right handed system

void StripPosMaker(){
  const Double_t z_ref = 899.0;
  const Double_t x_ref = 0.0; // default

  const Double_t dis = 112.5;
  const Double_t angle = -73.0;

  const Double_t deg_to_rad = TMath::Pi()/180.0;

  ofstream fout("macro/output/strip_pos.txt", ios::out);
  fout << "# created from StripPosMaker.C" << endl;
  fout << "# (z, x)" << endl;

  for(Int_t i=0; i<16; i++){
    Double_t z_tmp = dis;
    Double_t x_tmp = 50.0/16.0/2.0 + ((Double_t)i - 8.0)*50.0/16.0;

    Double_t z = z_tmp * TMath::Cos(angle * deg_to_rad) - x_tmp * TMath::Sin(angle * deg_to_rad);
    Double_t x = z_tmp * TMath::Sin(angle * deg_to_rad) + x_tmp * TMath::Cos(angle * deg_to_rad);

    z += z_ref;

    fout << "(" << z << ", " << x << ")" << endl;
  }
  fout.close();

  gROOT->ProcessLine(".q");

}