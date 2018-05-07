void Plot(){
  TFile *rootfile = TFile::Open("lumi_chained.root");


  TCanvas *c11 =new TCanvas("c11","c11",800,800);
  TCanvas *c43 =new TCanvas("c43","c43",800,600);
  TCanvas *c21 =new TCanvas("c21","c21",1200,600);
  TCanvas *c31 =new TCanvas("c31","c31",1200,900);
  c31->Divide(1,3);
  c21->SetLogy();
  
  TH2D* h2d = new TH2D("h2d","h2d",100,-10,10,100,-10,10);
  TH2D* h2d_beam = new TH2D("h2d_beam","h2d_beam",60,-30,30,60,-30,30);
  
  TH1D* h_hit_e = new TH1D("h_hit_e","h_hit_e",12,-0.5,11.5);
  TH1D* h_hit_pos = new TH1D("h_hit_pos","h_hit_pos",12,-0.5,11.5);
  TH1D* h_hit_gamma = new TH1D("h_hit_gamma","h_hit_gama",12,-0.5,11.5);
  h_hit_e->SetLineColor(1);
  h_hit_pos->SetLineColor(2);
  h_hit_gamma->SetLineColor(4);
  
  h_hit_e->SetLineWidth(2);
  h_hit_pos->SetLineWidth(2);
  h_hit_gamma->SetLineWidth(2);

  TH1D* h_ekin_e = new TH1D("h_ekin_e","h_ekin_e",1000,0,10000);
  TH1D* h_ekin_pos = new TH1D("h_ekin_pos","h_ekin_pos",1000,0,10000);
  TH1D* h_ekin_gamma = new TH1D("h_ekin_gamma","h_ekin_gamma",1000,0,10000);
  TH1D* h_ekin_prim = new TH1D("h_ekin_prim","h_ekin_prim",1000,0,10000);
  TH1D* h_ekin_sec = new TH1D("h_ekin_sec","h_ekin_sec",1000,0,10000);
  h_ekin_e->SetLineColor(1);
  h_ekin_pos->SetLineColor(2);
  h_ekin_gamma->SetLineColor(4);
  
  h_ekin_prim->SetLineColor(2);
  h_ekin_sec->SetLineColor(4);

  TLegend *leg_hit = new TLegend(0.8,0.5,1,0.6);
  leg_hit->AddEntry(h_hit_e,"electron, Ekin>2 MeV","l");
  leg_hit->AddEntry(h_hit_pos,"positron, Ekin> 2MeV","l");
  leg_hit->AddEntry(h_hit_gamma,"gamma","l");

  TLegend *leg_ekin = new TLegend(0.1,0.9,0.3,0.8);
  leg_ekin->AddEntry(h_ekin_e,"electron, Ekin>2 MeV","l");
  leg_ekin->AddEntry(h_ekin_pos,"positron, Ekin>2 MeV","l");
  leg_ekin->AddEntry(h_ekin_gamma,"gamma","l");

  TLegend *leg_electron = new TLegend(0.1,0.9,0.3,0.8);
  leg_electron->AddEntry(h_ekin_e,"Total","l");
  leg_electron->AddEntry(h_ekin_prim,"Primary","l");
  leg_electron->AddEntry(h_ekin_sec,"Secondary","l");

  ////////////////////////////////////////////////////////////////////////////
  lumi->Draw("hit_y:hit_x>>h2d","detID>10 && particleID==1 && Ekin>2","goff");
  c11->cd();
  h2d->SetTitle("SAM 2D hits, Electron, Ekin>2 MeV");
  h2d->GetYaxis()->SetTitle("Y/cm");
  h2d->GetXaxis()->SetTitle("X/cm");
  h2d->Draw("COLZ");
  c11->SaveAs("plots/SAM_2D_electron.pdf");
  ////////////////////////////////////////////////////////////////////////////
  lumi->Draw("hit_y:hit_x>>h2d","detID>10 && particleID==2 && Ekin>2","goff");
  c11->cd();
  h2d->SetTitle("SAM 2D hits, Positron, Ekin>2 MeV");
  h2d->GetYaxis()->SetTitle("Y/cm");
  h2d->GetXaxis()->SetTitle("X/cm");
  h2d->Draw("COLZ");
  c11->SaveAs("plots/SAM_2D_positron.pdf");
  ////////////////////////////////////////////////////////////////////////////
  lumi->Draw("hit_y:hit_x>>h2d","detID>10 && particleID==0","goff");
  c11->cd();
  h2d->SetTitle("SAM 2D hits, Gamma");
  h2d->GetYaxis()->SetTitle("Y/cm");
  h2d->GetXaxis()->SetTitle("X/cm");
  h2d->Draw("COLZ");
  c11->SaveAs("plots/SAM_2D_gamma.pdf");
  ////////////////////////////////////////////////////////////////////////////
  lumi->Draw("detID-10.5>>h_hit_e","detID>10 && particleID==1 && Ekin>2","goff");
  lumi->Draw("detID-10.5>>h_hit_pos","detID>10 && particleID==2 && Ekin>2","goff");
  lumi->Draw("detID-10.5>>h_hit_gamma","detID>10 && particleID==0 ","goff");
  //  c43->Clear();
  c43->cd();
  h_hit_e->SetTitle("Counts at SAMs");
  h_hit_e->GetXaxis()->SetTitle("SAM ID");
  h_hit_e->GetYaxis()->SetTitle("Counts");
  h_hit_e->Draw();
  gPad->Update(); // Update to Make sure stat box is created
  TPaveStats *ps_e =(TPaveStats*)(h_hit_e->FindObject("stats"));
  ps_e->SetY1NDC(0.85);
  ps_e->SetY2NDC(0.95);
  ps_e->SetX1NDC(0.8);
  ps_e->SetX2NDC(1);
  ps_e->SetTextColor(1);
  
  h_hit_pos->Draw();
  gPad->Update();
  TPaveStats *ps_pos =(TPaveStats*)(h_hit_pos->FindObject("stats"));
  ps_pos->SetY1NDC(0.75);
  ps_pos->SetY2NDC(0.85);
  ps_pos->SetX1NDC(0.8);
  ps_pos->SetX2NDC(1);
  ps_pos->SetTextColor(2);
  
  h_hit_gamma->Draw();
  gPad->Update();
  TPaveStats *ps_gamma =(TPaveStats*)(h_hit_gamma->FindObject("stats"));
  ps_gamma->SetY1NDC(0.65);
  ps_gamma->SetY2NDC(0.75);
  ps_gamma->SetX1NDC(0.8);
  ps_gamma->SetX2NDC(1);
  ps_gamma->SetTextColor(4);

  h_hit_e->Draw();
  h_hit_pos->Draw("same");
  h_hit_gamma->Draw("same");
  // ps_e->Draw("same");
  // ps_pos->Draw("same");
  // ps_gamma->Draw("same");
  leg_hit->Draw("same");
  c43->Update();
  c43->SaveAs("plots/SAM_hit_spec.pdf");
  ////////////////////////////////////////////////////////////////////////////
  //SAM e- e+ gamma Ekin
  lumi->Draw("Ekin>>h_ekin_e","detID>10 && particleID==1 && Ekin>2","goff");
  lumi->Draw("Ekin>>h_ekin_pos","detID>10 && particleID==2 && Ekin>2","goff");
  lumi->Draw("Ekin>>h_ekin_gamma","detID>10 && particleID==0","goff");
  
  h_ekin_gamma->SetTitle("Particles Hits at SAMs");
  h_ekin_gamma->GetXaxis()->SetTitle("Ekin/MeV");

  c21->cd();
  c21->SetLogy();
  
  h_ekin_e->Draw();
  gPad->Update(); // Update to Make sure stat box is created
  ps_e =(TPaveStats*)(h_ekin_e->FindObject("stats"));
  ps_e->SetY1NDC(0.85);
  ps_e->SetY2NDC(0.95);
  ps_e->SetX1NDC(0.85);
  ps_e->SetX2NDC(1);
  ps_e->SetTextColor(1);
  
  h_ekin_pos->Draw();
  gPad->Update();
  ps_pos =(TPaveStats*)(h_ekin_pos->FindObject("stats"));
  ps_pos->SetY1NDC(0.75);
  ps_pos->SetY2NDC(0.85);
  ps_pos->SetX1NDC(0.85);
  ps_pos->SetX2NDC(1);
  ps_pos->SetTextColor(2);
  
  h_ekin_gamma->Draw();
  gPad->Update();
  ps_gamma =(TPaveStats*)(h_ekin_gamma->FindObject("stats"));
  ps_gamma->SetY1NDC(0.65);
  ps_gamma->SetY2NDC(0.75);
  ps_gamma->SetX1NDC(0.85);
  ps_gamma->SetX2NDC(1);
  ps_gamma->SetTextColor(4);

  h_ekin_gamma->Draw();
  h_ekin_pos->Draw("same");
  h_ekin_e->Draw("same");
  leg_ekin->Draw("same");
  c21->SaveAs("plots/SAM_ekin_spec.pdf");
  ////////////////////////////////////////////////////////////////////////////
  //SAM electrons Ekin
  lumi->Draw("Ekin>>h_ekin_e","detID>10&& particleID==1 && Ekin>2","goff");
  lumi->Draw("Ekin>>h_ekin_prim","detID>10 && particleID==1 && Ekin>2 && trackID==1","goff");
  lumi->Draw("Ekin>>h_ekin_sec","detID>10 && particleID==1 && Ekin>2 && trackID>1","goff");
  c21->cd();
  c21->SetLogy();
  h_ekin_e->SetTitle("Electron Hits at SAMs, Ekin>2 MeV");
  h_ekin_e->GetXaxis()->SetTitle("Ekin/MeV");
  
  h_ekin_e->Draw();
  gPad->Update();
  TPaveStats *ps_tot =(TPaveStats*)h_ekin_e->FindObject("stats");
  ps_tot->SetY1NDC(0.95);
  ps_tot->SetY2NDC(0.85);
  ps_tot->SetX1NDC(0.85);
  ps_tot->SetX2NDC(1);
  ps_tot->SetTextColor(1);
  
  h_ekin_prim->Draw();
  gPad->Update();
  TPaveStats *ps_prim = (TPaveStats*)h_ekin_prim->FindObject("stats");
  ps_prim->SetY1NDC(0.85);
  ps_prim->SetY2NDC(0.75);
  ps_prim->SetX1NDC(0.85);
  ps_prim->SetX2NDC(1);
  ps_prim->SetTextColor(2);
  
  h_ekin_sec->Draw();
  gPad->Update();
  TPaveStats *ps_sec = (TPaveStats*)h_ekin_sec->FindObject("stats");
  ps_sec->SetY1NDC(0.75);
  ps_sec->SetY2NDC(0.65);
  ps_sec->SetX1NDC(0.85);
  ps_sec->SetX2NDC(1);
  ps_sec->SetTextColor(4);

  
  h_ekin_e->Draw();
  h_ekin_prim->Draw("same");
  h_ekin_sec->Draw("same");
  ps_tot->Draw("same");
  ps_prim->Draw("same");
  ps_sec->Draw("same");
  leg_electron->Draw("same");
  c21->SaveAs("plots/SAM_Ekin_electron.pdf");
  ////////////////////////////////////////////////////////////////////////////
  
  //beam det 1
  lumi->Draw("Ekin>>h_ekin_e","detID==1&& particleID==1 && Ekin>2","goff");
  lumi->Draw("Ekin>>h_ekin_prim","detID==1 && particleID==1 && Ekin>2 && trackID==1","goff");
  lumi->Draw("Ekin>>h_ekin_sec","detID==1 && particleID==1 && Ekin>2 && trackID>1","goff");
  c21->cd();
  c21->SetLogy();
  h_ekin_e->SetTitle("Electrons out of Target, Ekin>2 MeV");
  h_ekin_e->GetXaxis()->SetTitle("Ekin/MeV");
  h_ekin_e->Draw();
  gPad->Update();
  ps_tot = (TPaveStats*)h_ekin_e->FindObject("stats");
  ps_tot->SetY1NDC(0.95);
  ps_tot->SetY2NDC(0.85);
  ps_tot->SetX1NDC(0.85);
  ps_tot->SetX2NDC(1);
  ps_tot->SetTextColor(1);
  
  h_ekin_prim->Draw();
  h_ekin_prim->Draw();
  gPad->Update();
  ps_prim = (TPaveStats*)h_ekin_prim->FindObject("stats");
  ps_prim->SetY1NDC(0.85);
  ps_prim->SetY2NDC(0.75);
  ps_prim->SetX1NDC(0.85);
  ps_prim->SetX2NDC(1);
  ps_prim->SetTextColor(2);
  
  h_ekin_sec->Draw();
  gPad->Update();
  ps_sec = (TPaveStats*)h_ekin_sec->FindObject("stats");
  ps_sec->SetY1NDC(0.75);
  ps_sec->SetY2NDC(0.65);
  ps_sec->SetX1NDC(0.85);
  ps_sec->SetX2NDC(1);
  ps_sec->SetTextColor(4);
  
  h_ekin_e->Draw();
  h_ekin_prim->Draw("same");
  h_ekin_sec->Draw("same");
  ps_tot->Draw("same");
  ps_prim->Draw("same");
  ps_sec->Draw("same");
  leg_electron->Draw("same");
  
  c21->SaveAs("plots/bdet1_Ekin_electron.pdf");
  ////////////////////////////////////////////////////////////////////////////
  lumi->Draw("Ekin>>h_ekin_e","detID==1 && particleID==1 && Ekin>2","goff");
  lumi->Draw("Ekin>>h_ekin_pos","detID==1 && particleID==2 && Ekin>2","goff");
  lumi->Draw("Ekin>>h_ekin_gamma","detID==1 && particleID==0","goff");
  c21->cd();
  c21->SetLogy();
  h_ekin_e->SetTitle("Particles out of Target");
  h_ekin_e->GetXaxis()->SetTitle("Ekin/ MeV");
  
  h_ekin_e->Draw();
  gPad->Update(); // Update to Make sure stat box is created
  ps_e =(TPaveStats*)(h_ekin_e->FindObject("stats"));
  ps_e->SetY1NDC(0.85);
  ps_e->SetY2NDC(0.95);
  ps_e->SetX1NDC(0.85);
  ps_e->SetX2NDC(1);
  ps_e->SetTextColor(1);
  
  h_ekin_pos->Draw();
  gPad->Update();
  ps_pos =(TPaveStats*)(h_ekin_pos->FindObject("stats"));
  ps_pos->SetY1NDC(0.75);
  ps_pos->SetY2NDC(0.85);
  ps_pos->SetX1NDC(0.85);
  ps_pos->SetX2NDC(1);
  ps_pos->SetTextColor(2);
  
  h_ekin_gamma->Draw();
  gPad->Update();
  ps_gamma =(TPaveStats*)(h_ekin_gamma->FindObject("stats"));
  ps_gamma->SetY1NDC(0.65);
  ps_gamma->SetY2NDC(0.75);
  ps_gamma->SetX1NDC(0.85);
  ps_gamma->SetX2NDC(1);
  ps_gamma->SetTextColor(4);

  h_ekin_e->Draw();
  h_ekin_pos->Draw("same");
  h_ekin_gamma->Draw("same");
  leg_ekin->Draw("same");
  c21->SaveAs("plots/bdet1_Ekin_spec.pdf");
  ////////////////////////////////////////////////////////////////////////////
  //beam det 3
  lumi->Draw("Ekin>>h_ekin_e","detID==3&& particleID==1 && Ekin>2","goff");
  lumi->Draw("Ekin>>h_ekin_prim","detID==3 && particleID==1 && Ekin>2 && trackID==1","goff");
  lumi->Draw("Ekin>>h_ekin_sec","detID==3 && particleID==1 && Ekin>2 && trackID>1","goff");
  c21->cd();
  c21->SetLogy();
  h_ekin_e->SetTitle("Electrons at Beam Pipe cross section");
  h_ekin_e->GetXaxis()->SetTitle("Ekin/MeV");
  
  h_ekin_e->Draw();
  gPad->Update();
  ps_tot = (TPaveStats*)h_ekin_e->FindObject("stats");
  ps_tot->SetY1NDC(0.95);
  ps_tot->SetY2NDC(0.85);
  ps_tot->SetX1NDC(0.85);
  ps_tot->SetX2NDC(1);
  ps_tot->SetTextColor(1);
  
  h_ekin_prim->Draw();
  gPad->Update();
  ps_prim = (TPaveStats*)h_ekin_prim->FindObject("stats");
  ps_prim->SetY1NDC(0.85);
  ps_prim->SetY2NDC(0.75);
  ps_prim->SetX1NDC(0.85);
  ps_prim->SetX2NDC(1);
  ps_prim->SetTextColor(2);
  
  h_ekin_sec->Draw();
  gPad->Update();
  ps_sec = (TPaveStats*)h_ekin_sec->FindObject("stats");
  ps_sec->SetY1NDC(0.75);
  ps_sec->SetY2NDC(0.65);
  ps_sec->SetX1NDC(0.85);
  ps_sec->SetX2NDC(1);
  ps_sec->SetTextColor(4);
  
  h_ekin_e->Draw();
  h_ekin_prim->Draw("same");
  h_ekin_sec->Draw("same");
  leg_electron->Draw("same");
  c21->SaveAs("plots/bdet3_Ekin_electron.pdf");
  ////////////////////////////////////////////////////////////////////////////
  // h_ekin_e->Reset();
  // h_ekin_pos->Reset();
  // h_ekin_gamma->Reset();
  lumi->Draw("Ekin>>h_ekin_e","detID==3 && particleID==1 && Ekin>2","goff");
  lumi->Draw("Ekin>>h_ekin_pos","detID==3 && particleID==2 && Ekin>2","goff");
  lumi->Draw("Ekin>>h_ekin_gamma","detID==3 && particleID==0","goff");
  c21->cd();
  c21->SetLogy();
  h_ekin_e->SetTitle("Particles at Beam Pipe cross section");
  h_ekin_e->GetXaxis()->SetTitle("Ekin/MeV");

  h_ekin_e->Draw();
  gPad->Update(); // Update to Make sure stat box is created
  ps_e =(TPaveStats*)(h_ekin_e->FindObject("stats"));
  ps_e->SetY1NDC(0.85);
  ps_e->SetY2NDC(0.95);
  ps_e->SetX1NDC(0.85);
  ps_e->SetX2NDC(1);
  ps_e->SetTextColor(1);
  
  h_ekin_pos->Draw();
  gPad->Update();
  ps_pos =(TPaveStats*)(h_ekin_pos->FindObject("stats"));
  ps_pos->SetY1NDC(0.75);
  ps_pos->SetY2NDC(0.85);
  ps_pos->SetX1NDC(0.85);
  ps_pos->SetX2NDC(1);
  ps_pos->SetTextColor(2);
  
  h_ekin_gamma->Draw();
  gPad->Update();
  ps_gamma =(TPaveStats*)(h_ekin_gamma->FindObject("stats"));
  ps_gamma->SetY1NDC(0.65);
  ps_gamma->SetY2NDC(0.75);
  ps_gamma->SetX1NDC(0.85);
  ps_gamma->SetX2NDC(1);
  ps_gamma->SetTextColor(4);
  
  h_ekin_e->Draw();
  h_ekin_pos->Draw("same");
  h_ekin_gamma->Draw("same");
  leg_ekin->Draw("same");
  c21->SaveAs("plots/bdet3_Ekin_spec.pdf");
  ////////////////////////////////////////////////////////////////////////////
  lumi->Draw("hit_y:hit_x>>h2d_beam","detID==3 && particleID==1 && Ekin>2","goff");
  c11->cd();
  c11->SetLogz();
  h2d_beam->SetTitle("Beam Pipe cross section, Electron, Ekin>2 MeV");
  h2d_beam->GetYaxis()->SetTitle("Y/cm");
  h2d_beam->GetXaxis()->SetTitle("X/cm");
  h2d_beam->Draw("COLZ");
  c11->Update();
  c11->SaveAs("plots/bdet3_2dhits_electron.pdf");

  lumi->Draw("hit_y:hit_x>>h2d_beam","detID==3 && particleID==2 && Ekin>2","goff");
  c11->cd();
  h2d_beam->SetTitle("Beam Pipe cross section, Positron, Ekin>2 MeV");
  h2d_beam->GetYaxis()->SetTitle("Y/cm");
  h2d_beam->GetXaxis()->SetTitle("X/cm");
  h2d_beam->Draw("COLZ");
  c11->Update();
  c11->SaveAs("plots/bdet3_2dhits_positron.pdf");

  lumi->Draw("hit_y:hit_x>>h2d_beam","detID==3 && particleID==0","goff");
  c11->cd();
  h2d_beam->SetTitle("Beam Pipe cross section, Gamma");
  h2d_beam->GetYaxis()->SetTitle("Y/cm");
  h2d_beam->GetXaxis()->SetTitle("X/cm");
  h2d_beam->Draw("COLZ");
  c11->Update();
  c11->SaveAs("plots/bdet3_2dhits_gamma.pdf");

}
