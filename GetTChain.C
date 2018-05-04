void GetTChain(){
  gSystem->Exec("ls -1 lumi_t*.root > runlist.txt");
  FILE* txtfile = fopen("runlist.txt","r");
  char filename[200];

  TChain *chain = new TChain("lumi");

  while(!feof(txtfile)){
    fscanf(txtfile,"%s\n",&filename);
    cout<< filename << endl;
    chain->Add(filename);
  }
  TFile *rootfile = TFile::Open("lumi_chained.root","RECREATE");
  chain->Write();
  rootfile->Close();
}
