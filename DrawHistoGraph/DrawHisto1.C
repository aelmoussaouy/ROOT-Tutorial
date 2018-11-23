void DrawHisto1(){

  TFile *f = TFile::Open("energy_momentum.root");
  TTree *t_em = (TTree*)f->Get("t_em");
  TTree *t_mu = (TTree*)f->Get("t_mu");  

  // apply some calculation
  t_em->Draw("ene_em/mom_mu");

  // Conditinoal Plot
  t_em->Draw("ene_em");

  // Plot option 
 
}
