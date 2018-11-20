void SingleTreeInput(){

  // Make TFile object with recreate mode
  TFile *f = TFile::Open("SingleTree_IO.root","recreate");

  // Make TTree object
  TTree *tree_em = new TTree("t_em","tree for measured e-  energy and momentum");

  // Make Branches inside TTree, which are linked to root variables (Energy & Momentum  
  Double_t ene_em, mom_em;
  
  tree_em->Branch("ene_em", &ene_em, "ene_em/D");
  tree_em->Branch("mom_em", &mom_em, "mom_em/D");
  
  // Define simple gaussian statistics for e- particle
  Double_t ene_mean_em  = 23.;
  Double_t ene_sigma_em = 6.2;
  Double_t mom_mean_em  = 32.5;
  Double_t mom_sigma_em = 4.3;
  
  // Declare random number generator
  TRandom3 rand;
  
  // Generate randum numbers and add them (entries) into tree  
  for (int i=0; i<1e4; i++){
    ene_em = rand.Gaus(ene_mean_em, ene_sigma_em);
    mom_em = rand.Gaus(mom_mean_em, mom_sigma_em);
    
    // Fill tree with entry one-by-one
    tree_em->Fill();
  }  
  
  // We will write TTree object in f (TFile) object
  f->cd();

  // Write Tree to TFile
  tree_em->Write();
  
  // Close TFile
  f->Close();
}

