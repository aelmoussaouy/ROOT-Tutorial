void DrawHistoGraph(){

  TFile *f = TFile::Open("energy_momentum.root","read");
  TTree *t_em = (TTree*)f->Get("t_em");
  TTree *t_mu = (TTree*)f->Get("t_mu");

  TFile *f_new = TFile::Open("new.root","recreate");
  
  /*** 1.A Make Histogram/Grah from TTree directly ***/

  // you can set condition & option if you want...
  t_mu->Draw("ene_mu/mom_mu >> histo","","");
  t_mu->Draw("ene_mu:mom_mu >> graph","","");

  
  /*** 1.B-1 Declare Histogram object and fill it ***/
  
  // Histogram Constructor: TH1D("name","title",nBins,xMin,xMax)
  TH1D* EoverP = new TH1D("EoverP","Energy/Momentum",100,0.,3.);

  Double_t ene_mu, mom_mu;

  t_mu->SetBranchAddress("ene_mu", &ene_mu);
  t_mu->SetBranchAddress("mom_mu", &mom_mu);
  
  for (int i=0; i<t_mu->GetEntries(); i++){
    t_mu->GetEntry(i);
    EoverP->Fill(ene_mu/mom_mu);    
  }

  
  /*** 1.B-2 Collect entries in array, and make TGraph with them ***/
  
  Double_t ene_mu_Arr[10000];
  Double_t mom_mu_Arr[10000];
  
  for (int i=0; i<t_mu->GetEntries(); i++){
    t_mu->GetEntry(i);
    ene_mu_Arr[i] = ene_mu;
    mom_mu_Arr[i] = mom_mu;
  }

  // Graph Constructor: TGraph(nPoints,x_arr,y_arr)  
  TGraph* gr = new TGraph(t_mu->GetEntries(),mom_mu_Arr,ene_mu_Arr);

 
  /*** 2. Save histograms & graphs ***/
  f_new->cd();  
  f_new->Write(); // Write all objects which have a name
  gr->Write();    // TGraph does not have a name (any better idea?)

  // Close all files
  f->Close();
  f_new->Close();
}
