#include "TRandom.h"

void SingleTree_Output(){

  // Make TFile object                               
  TFile *f = TFile::Open("tut.root","recreate");

  // Make TTree object
  TTree *t = new TTree("tree","tree for electron's energy and momentum");

  Double_t Energy;
  Double_t Momentum;

  // Make Branches inside TTree, which are linked to root variables (Energy & Momentum)

  t->Branch("Energy", &Energy, "Energy/D" );
  t->Branch("Momentum", &Momentum, "Momentum/D");

  // Define simple gaussian statistics for e- particle
  Double_t E_mean_em = 23.;
  Double_t E_sigma_em = 6.;
  Double_t P_mean_em = 22.5;
  Double_t P_sigma_em = 4;

  TRandom3 rand;
  
  // Generate randum numbers and add them into tree
  for (int i=0; i<1e3; i++){
	Energy = rand.Gaus(E_mean_em, E_sigma_em);
	Momentum = rand.Gaus(P_mean_em, P_sigma_em);

	t->Fill();
  }
  
  f->cd();

  // Write Tree to TFile
  t->Write();

  // Close TFile
  f->Close();
}

