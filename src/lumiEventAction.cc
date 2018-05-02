#include "lumiEventAction.hh"
#include "LuminosityHit.hh"

#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "g4root.hh" //this for G4AnalysisManager


lumiEventAction:: lumiEventAction()  :G4UserEventAction(){
  SAMCollID= -1;
  bDetCollID = -1;
}

lumiEventAction::~lumiEventAction(){
}

void lumiEventAction::BeginOfEventAction(const G4Event*){
  
  G4SDManager *sdManager = G4SDManager::GetSDMpointer();
  SAMCollID = sdManager->GetCollectionID("SAM/LumiHitColl");
  bDetCollID = sdManager->GetCollectionID("bDet/LumiHitColl");
  //  G4cout << "BOE: Set HCID" << HCID  << G4endl;
}


void lumiEventAction::EndOfEventAction(const G4Event* anEvent){
  
  G4HCofThisEvent *hce = anEvent->GetHCofThisEvent();
  LuminosityHitsCollection* SAM_hitsCollection = (LuminosityHitsCollection*)(hce->GetHC(SAMCollID));
  LuminosityHitsCollection* bDet_hitsCollection = (LuminosityHitsCollection*)(hce->GetHC(bDetCollID));
  
  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
  
  G4int nhits = SAM_hitsCollection->entries();
  //  G4cout << "Hits of This Event" << nhits << G4endl;
  G4int detID = (*SAM_hitsCollection)[0]->GetDetID();
  G4double edep =(*SAM_hitsCollection)[0]->GetEdep();
  G4double Ekin =(*SAM_hitsCollection)[0]->GetEkin();
  G4double Etot =(*SAM_hitsCollection)[0]->GetEtot();
  G4ThreeVector hit_pos = (*SAM_hitsCollection)[0]->GetHitPos();
  G4ThreeVector vertex_pos = (*SAM_hitsCollection)[0]->GetVertexPos();
  G4int trackID =(*SAM_hitsCollection)[0]->GetTrackID();
  G4int procID =(*SAM_hitsCollection)[0]->GetProcID();
  
  analysisManager->FillNtupleIColumn(0,nhits);
  analysisManager->FillNtupleDColumn(1,edep/MeV);
  analysisManager->FillNtupleDColumn(5,hit_pos.getX()/cm);
  analysisManager->FillNtupleDColumn(6,hit_pos.getY()/cm);
  analysisManager->FillNtupleDColumn(7,hit_pos.getZ()/cm);

  analysisManager->FillNtupleIColumn(8,detID);
  analysisManager->FillNtupleDColumn(9,Ekin/MeV);
  analysisManager->FillNtupleDColumn(10,Etot/MeV);

  analysisManager->FillNtupleIColumn(11,trackID);

  analysisManager->FillNtupleDColumn(12,vertex_pos.getX()/cm);
  analysisManager->FillNtupleDColumn(13,vertex_pos.getY()/cm);
  analysisManager->FillNtupleDColumn(14,vertex_pos.getZ()/cm);

  analysisManager->FillNtupleIColumn(15,procID);

  G4double bEkin =(*bDet_hitsCollection)[0]->GetEkin();
  G4double bEtot =(*bDet_hitsCollection)[0]->GetEtot();
  G4ThreeVector bhit_pos = (*bDet_hitsCollection)[0]->GetHitPos();
  G4ThreeVector bvertex_pos = (*bDet_hitsCollection)[0]->GetVertexPos();
  G4int btrackID =(*bDet_hitsCollection)[0]->GetTrackID();
  G4int bprocID =(*bDet_hitsCollection)[0]->GetProcID();

  analysisManager->FillNtupleDColumn(16,bhit_pos.getX()/cm);
  analysisManager->FillNtupleDColumn(17,bhit_pos.getY()/cm);
  analysisManager->FillNtupleDColumn(18,bhit_pos.getZ()/cm);

  analysisManager->FillNtupleDColumn(19,bvertex_pos.getX()/cm);
  analysisManager->FillNtupleDColumn(20,bvertex_pos.getY()/cm);
  analysisManager->FillNtupleDColumn(21,bvertex_pos.getZ()/cm);

  analysisManager->FillNtupleDColumn(22,Ekin/MeV);
  analysisManager->FillNtupleDColumn(23,Etot/MeV);

  analysisManager->FillNtupleIColumn(24,bprocID);
  analysisManager->FillNtupleIColumn(25,btrackID);
  //*****************
  analysisManager->AddNtupleRow();
  //*****************
  
  //G4cout << "EOE: Done" << G4endl;
}
