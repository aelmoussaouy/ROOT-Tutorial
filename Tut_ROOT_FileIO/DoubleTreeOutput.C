void DoubleTreeOutput(){

  // Open TFile object with read mode
  TFile *f = TFile::Open("DoubleTree_IO.root","read");

  // retrieve trees from TFile object
  TTree *t_em = (TTree*)(f->Get("t_em"));
  TTree *t_mu = (TTree*)(f->Get("t_mu"));

  // Declare variables which will read entries in the trees
  Double_t ene_em, mom_em;
  Double_t ene_mu, mom_mu;

  // Link variables to branches
  t_em->SetBranchAddress("ene_em",&ene_em);
  t_em->SetBranchAddress("mom_em",&mom_em);
  t_mu->SetBranchAddress("ene_mu",&ene_mu);
  t_mu->SetBranchAddress("mom_mu",&mom_mu);

  // Read entries one-by-one
  Int_t NumOfEntries = t_em->GetEntries();
  for (int i=0; i<NumOfEntries; i++){
    // Read entry of i-th index
    t_em->GetEntry(i);
    t_mu->GetEntry(i);

    // Print-out values of entries
    if (i%100 == 0){
      std::cout << i << "-th particle:  " << ene_em << "  " << mom_em
		<< "  " << ene_mu << "  "<< mom_mu << std::endl;
    }
  }

  f->Close();
}
