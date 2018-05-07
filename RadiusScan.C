void RadiusScan(){

  double al_can_outer_radii = 1.92;
  double det_thickness = 0.5;
  double quartz_thickness = 1.3;
  double sam_area = 2*3;
  double z_corr = det_thickness+al_can_outer_radii-quartz_thickness/2.0;

  TFile *rootfile = TFile::Open("lumi_chained.root");
  //recontruct hits to SAMs front surface
  lumi->SetAlias("corr_y",Form("hit_y+%lf*(py/pz)",z_corr));
  lumi->SetAlias("corr_x",Form("hit_x+%lf*(px/pz)",z_corr));
  //collecting rings

  double r0,r1,r2;
  double dr=1.5;
  double pi = TMath::Pi();
  int entries;
  TH1D *hcoll = new TH1D("hcoll","hcoll",1000,0,10000);
  TString cut1;
  TString cut2[3] ={"particleID==0","particleID==1 && Ekin>2","particleID==2 && Ekin>2"};

  double rate[3][20];// counts/ cm^2
  double rad_ctr[20];
  for(int i=0;i<20;i++){
    rad_ctr[i]=i+dr;
  }
  
  for(int ipar=0; ipar<3;ipar++){
    for(int ir=0;ir<20;ir++){
      r0 = rad_ctr[ir];
      r1 = r0 -dr;
      r2 = r0 +dr;
      cut1 = Form("detID==3 && corr_y**2 +corr_x**2<%lf && corr_x**2 +corr_y**2 >%lf &&",r2**2,r1**2);
      cut1 = cut1+cut2[ipar].Data();
      lumi->Draw("Ekin>>hcoll",cut1,"goff");
      entries = hcoll->GetEntries();
      rate[ipar][ir] = entries/(pi*(r2+r1)*(r2-r1))*sam_area;
    }
  }

  TGraph *g1 = new TGraph(20,rad_ctr,rate[0]);
  g1->SetMarkerStyle(20);
  g1->SetMarkerColor(1);
  g1->SetLineColor(1);
  g1->SetLineWidth(2);
  TGraph *g2 = new TGraph(20,rad_ctr,rate[1]);
  g2->SetMarkerStyle(20);
  g2->SetMarkerColor(2);
  g2->SetLineColor(2);
  g2->SetLineWidth(2);
  TGraph *g3 = new TGraph(20,rad_ctr,rate[2]);
  g3->SetMarkerStyle(20);
  g3->SetMarkerColor(4);
  g3->SetLineColor(4);
  g3->SetLineWidth(2);
  
  TLegend *leg = new TLegend(0.9,0.9,0.6,0.7);
  leg->AddEntry(g1,"Gamma","lp");
  leg->AddEntry(g2,"Electron, Ekin>2 MeV","lp");
  leg->AddEntry(g3,"Positron, Ekin>2 MeV","lp");
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(g1,"lp");
  mg->Add(g2,"lp");
  mg->Add(g3,"lp");
  mg->Draw("AP");
  leg->Draw("same");  
  mg->GetXaxis()->SetTitle("Radius/cm");
  mg->GetYaxis()->SetTitle("Counts/SAM");
  mg->SetTitle("Rate vs R");

}
