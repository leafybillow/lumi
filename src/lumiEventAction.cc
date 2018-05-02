#include "lumiEventAction.hh"
#include "LuminosityHit.hh"

#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "g4root.hh" //this for G4AnalysisManager


lumiEventAction:: lumiEventAction()  :G4UserEventAction(){
  HCID = -1;
}

lumiEventAction::~lumiEventAction(){
}

void lumiEventAction::BeginOfEventAction(const G4Event*){
  
  G4SDManager *sdManager = G4SDManager::GetSDMpointer();
  HCID = sdManager->GetCollectionID("SAM/LumiHitColl");
  //  G4cout << "BOE: Set HCID" << HCID  << G4endl;
}


void lumiEventAction::EndOfEventAction(const G4Event* anEvent){
  
  G4HCofThisEvent *hce = anEvent->GetHCofThisEvent();
  LuminosityHitsCollection* hitsCollection = (LuminosityHitsCollection*)(hce->GetHC(HCID));
  
  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
  
  G4int nhits = hitsCollection->entries();
  //  G4cout << "Hits of This Event" << nhits << G4endl;
  G4int detID = (*hitsCollection)[0]->GetDetID();
  G4double edep =(*hitsCollection)[0]->GetEdep();
  G4double Ekin =(*hitsCollection)[0]->GetEkin();
  G4double Etot =(*hitsCollection)[0]->GetEtot();
  G4ThreeVector hit_pos = (*hitsCollection)[0]->GetHitPos();
  G4ThreeVector vertex_pos = (*hitsCollection)[0]->GetVertexPos();
  G4int trackID =(*hitsCollection)[0]->GetTrackID();

  analysisManager->FillH1(0,nhits);
  analysisManager->FillH1(1,edep);
  
  analysisManager->FillNtupleIColumn(0,nhits);
  analysisManager->FillNtupleDColumn(1,edep/MeV);
  analysisManager->FillNtupleDColumn(5,hit_pos.getX()/cm);
  analysisManager->FillNtupleDColumn(6,hit_pos.getY()/cm);
  analysisManager->FillNtupleDColumn(7,hit_pos.getZ()/cm);

  analysisManager->FillNtupleIColumn(8,detID);
  analysisManager->FillNtupleDColumn(9,Ekin/GeV);
  analysisManager->FillNtupleDColumn(10,Etot/GeV);

  analysisManager->FillNtupleIColumn(11,trackID);

  analysisManager->FillNtupleDColumn(12,vertex_pos.getX()/cm);
  analysisManager->FillNtupleDColumn(13,vertex_pos.getY()/cm);
  analysisManager->FillNtupleDColumn(14,vertex_pos.getZ()/cm);

  //*****************
  analysisManager->AddNtupleRow();
  //*****************
  
  //G4cout << "EOE: Done" << G4endl;
}
