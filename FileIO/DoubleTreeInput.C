void DoubleTreeInput(){

  // Make TFile object with recreate mode      
  TFile *f = TFile::Open("DoubleTree_IO.root","recreate");

  // Make TTree object
  TTree *t_em = new TTree("t_em","tree for measured e-  energy and momentum");
  TTree *t_mu = new TTree("t_mu","tree for measured mu- energy and momentum");

  // Make Branches inside TTree, which are linked to root variables (Energy & Momentum
  Double_t ene_em, mom_em;
  Double_t ene_mu, mom_mu;

  t_em->Branch("ene_em", &ene_em, "ene_em/D");
  t_em->Branch("mom_em", &mom_em, "mom_em/D");
  t_mu->Branch("ene_mu", &ene_mu, "ene_mu/D");
  t_mu->Branch("mom_mu", &mom_mu, "mom_mu/D");
  
  // Define simple gaussian statistics for e- particle
  Double_t ene_mean_em  = 23.;
  Double_t ene_sigma_em = 6.2;
  Double_t mom_mean_em  = 32.5;
  Double_t mom_sigma_em = 4.3;

  // Define simple gaussian statistics for mu- particle
  Double_t ene_mean_mu  = 27.3;
  Double_t ene_sigma_mu = 8.2;
  Double_t mom_mean_mu  = 36.5;
  Double_t mom_sigma_mu = 6.7;

  // declare random number generator
  TRandom3 rand;
  
  // Generate randum numbers and add them (entries) into tree
  for (int i=0; i<1e4; i++){
    ene_em = rand.Gaus(ene_mean_em, ene_sigma_em);
    mom_em = rand.Gaus(mom_mean_em, mom_sigma_em);
    
    ene_mu = rand.Gaus(ene_mean_mu, ene_sigma_mu);
    mom_mu = rand.Gaus(mom_mean_mu, mom_sigma_mu);

    // Fill tree with entry one-by-one
    t_em->Fill();
    t_mu->Fill();
  }

  // We will write TTree object in f (TFile) object
  f->cd();

  // Write Tree to TFile
  t_em->Write();
  t_mu->Write();
  
  // Close TFile
  f->Close();
}

