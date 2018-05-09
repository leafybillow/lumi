void RadiusScan(){

  double al_can_outer_radii = 1.92;
  double det_thickness = 0.5;
  double quartz_thickness = 1.3;
  double sam_area = 2*3;
  double z_corr = det_thickness/2.0+al_can_outer_radii-quartz_thickness/2.0;

  TFile *rootfile = TFile::Open("lumi_chained.root");
  //recontruct hits to SAMs front plane
  lumi->SetAlias("corr_y",Form("hit_y+%lf*(py/pz)",z_corr));
  lumi->SetAlias("corr_x",Form("hit_x+%lf*(px/pz)",z_corr));
  
  TH1D *h_raw = new TH1D("h_raw","h_raw",120,0,30);
  TH1D *h_e = new TH1D("h_e","h_e",120,0,30);
  h_e->GetYaxis()->SetTitle("Counts/cm^2");
  h_e->GetXaxis()->SetTitle("Distance from Center/cm");
  h_e->SetTitle("");
  h_e->SetLineColor(1);
  h_e->SetLineWidth(2);

  TH1D *h_pos = new TH1D("h_pos","h_pos",120,0,30);
  h_pos->GetYaxis()->SetTitle("Counts/cm^2");
  h_pos->GetXaxis()->SetTitle("Distance from Center/cm");
  h_pos->SetTitle("");
  h_pos->SetLineColor(2);
  h_pos->SetLineWidth(2);
  
  TH1D *h_gamma = new TH1D("h_gamma","h_gamma",120,0,30);
  h_gamma->GetYaxis()->SetTitle("Counts/cm^2");
  h_gamma->GetXaxis()->SetTitle("Distance from Center/cm");
  h_gamma->SetTitle("");
  h_gamma->SetLineColor(4);
  h_gamma->SetLineWidth(2);
  
  int nbins = h_raw->GetNbinsX();
  double bin_size = 30.0/nbins;
  double bin_content;
  double pi = TMath::Pi();
  double area;
  
  TH1D *h_sam = new TH1D("h_sam","h_sam",120,0,30);
  lumi->Draw("sqrt(corr_x**2+corr_y**2)>>h_raw","particleID==1 &&Ekin>2 && detID==3","goff");
  for(int ibin =1;ibin<=nbins;ibin++){
    bin_content = h_raw->GetBinContent(ibin);
    area = pi*((2*ibin-1)*bin_size)*bin_size;
    h_e->SetBinContent(ibin,bin_content/area);
  }

  lumi->Draw("sqrt(corr_x**2+corr_y**2)>>h_raw","particleID==2 &&Ekin>2 && detID==3","goff");
  for(int ibin =1;ibin<=nbins;ibin++){
    bin_content = h_raw->GetBinContent(ibin);
    area = pi*((2*ibin-1)*bin_size)*bin_size;
    h_pos->SetBinContent(ibin,bin_content/area);
  }

  lumi->Draw("sqrt(corr_x**2+corr_y**2)>>h_raw","particleID==0 && detID==3","goff");
  for(int ibin =1;ibin<=nbins;ibin++){
    bin_content = h_raw->GetBinContent(ibin);
    area = pi*((2*ibin-1)*bin_size)*bin_size;
    h_gamma->SetBinContent(ibin,bin_content/area);
  }

  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd();
  c1->SetLogy();

  TLegend *leg = new TLegend(0.9,0.9,0.6,0.7);
  leg->AddEntry(h_e,"Electron, Ekin>2 MeV","l");
  leg->AddEntry(h_pos,"Positron, Ekin>2 MeV","l");
  leg->AddEntry(h_gamma,"Gamma","l");

  h_e->Draw();
  h_pos->Draw("same");
  h_gamma->Draw("same");
  leg->Draw("same");

  
  // //collecting rings
  // double r0,r1,r2;
  // double dr=1.5;
  // double pi = TMath::Pi();
  // int entries;
  // TH1D *hcoll = new TH1D("hcoll","hcoll",1000,0,10000);
  // TString cut1;
  // TString cut2[3] ={"particleID==0","particleID==1 && Ekin>2","particleID==2 && Ekin>2"};

  // double rate[3][30];// counts/ cm^2
  // double rad_ctr[30];
  // for(int i=0;i<30;i++){
  //   rad_ctr[i]=i*0.5+dr;
  // }
  
  // for(int ipar=0; ipar<3;ipar++){
  //   for(int ir=0;ir<30;ir++){
  //     r0 = rad_ctr[ir];
  //     r1 = r0 -dr;
  //     r2 = r0 +dr;
  //     cut1 = Form("detID==3 && hit_y**2 +hit_x**2<%lf && hit_x**2 +hit_y**2 >%lf &&",r2**2,r1**2);
  //     cut1 = cut1+cut2[ipar].Data();
  //     lumi->Draw("Ekin>>hcoll",cut1,"goff");
  //     entries = hcoll->GetEntries();
  //     rate[ipar][ir] = entries/(pi*(r2+r1)*(r2-r1))*sam_area;
  //   }
  // }


  // TCanvas *c1  = new TCanvas("c1","c1",800,800);
  // c1->cd();
  // TGraph *g1 = new TGraph(30,rad_ctr,rate[0]);
  // g1->SetMarkerStyle(20);
  // g1->SetMarkerColor(1);
  // g1->SetLineColor(1);
  // g1->SetLineWidth(2);
  // TGraph *g2 = new TGraph(30,rad_ctr,rate[1]);
  // g2->SetMarkerStyle(20);
  // g2->SetMarkerColor(2);
  // g2->SetLineColor(2);
  // g2->SetLineWidth(2);
  // TGraph *g3 = new TGraph(30,rad_ctr,rate[2]);
  // g3->SetMarkerStyle(20);
  // g3->SetMarkerColor(4);
  // g3->SetLineColor(4);
  // g3->SetLineWidth(2);
  
  // TLegend *leg = new TLegend(0.9,0.9,0.6,0.7);
  // leg->AddEntry(g1,"Gamma","lp");
  // leg->AddEntry(g2,"Electron, Ekin>2 MeV","lp");
  // leg->AddEntry(g3,"Positron, Ekin>2 MeV","lp");
  // TMultiGraph *mg = new TMultiGraph();
  // mg->Add(g1,"lp");
  // mg->Add(g2,"lp");
  // mg->Add(g3,"lp");
  // mg->Draw("AP");
  // leg->Draw("same");  
  // mg->GetXaxis()->SetTitle("Radius/cm");
  // mg->GetYaxis()->SetTitle("Counts/SAM");
  // mg->SetTitle("Rate vs R");

  //  rootfile->Close();
}
