#include "lumiEventAction.hh"
#include "lumiDetectorHit.hh"

#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "g4root.hh" //this for G4AnalysisManager


lumiEventAction:: lumiEventAction()  :G4UserEventAction(){
  CollID = -1;
}

lumiEventAction::~lumiEventAction(){
}

void lumiEventAction::BeginOfEventAction(const G4Event*){
  
  G4SDManager *sdManager = G4SDManager::GetSDMpointer();
  CollID = sdManager->GetCollectionID("SAM/LumiHitColl");
  //  G4cout << "BOE: Set HCID" << HCID  << G4endl;
}


void lumiEventAction::EndOfEventAction(const G4Event* anEvent){
  
  G4HCofThisEvent *hce = anEvent->GetHCofThisEvent();
  lumiDetectorHitsCollection* hitsCollection = (lumiDetectorHitsCollection*)(hce->GetHC(CollID));
  
  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
  
  G4int nhits = hitsCollection->entries();
  G4ThreeVector prim_pos = anEvent->GetPrimaryVertex()->GetPosition();
  G4int ev_id = anEvent->GetEventID();
  
  for(int ihit=0;ihit<nhits;ihit++){
    
    G4int detID = (*hitsCollection)[ihit]->GetDetID();
    //  G4double edep =(*hitsCollection)[ihit]->GetEdep();
    G4double Ekin =(*hitsCollection)[ihit]->GetEkin();
    G4double Etot =(*hitsCollection)[ihit]->GetEtot();

    G4ThreeVector hit_pos = (*hitsCollection)[ihit]->GetHitPos();
    G4ThreeVector vertex_pos = (*hitsCollection)[ihit]->GetVertexPos();
    G4ThreeVector momentum = (*hitsCollection)[ihit]->GetMomentum();
    G4double px =momentum.getX();
    G4double py =momentum.getY();
    G4double pz =momentum.getZ();
    
    G4int trackID =(*hitsCollection)[ihit]->GetTrackID();
    G4int creatorID =(*hitsCollection)[ihit]->GetCreatorID();
    G4int particleID =(*hitsCollection)[ihit]->GetParticleID();

    analysisManager->FillNtupleIColumn(0,ev_id);
    analysisManager->FillNtupleIColumn(1,nhits);

    analysisManager->FillNtupleIColumn(2,detID);
    
    analysisManager->FillNtupleDColumn(3,prim_pos.getX()/cm);
    analysisManager->FillNtupleDColumn(4,prim_pos.getY()/cm);
    analysisManager->FillNtupleDColumn(5,prim_pos.getZ()/cm);

    analysisManager->FillNtupleDColumn(6,hit_pos.getX()/cm);
    analysisManager->FillNtupleDColumn(7,hit_pos.getY()/cm);
    analysisManager->FillNtupleDColumn(8,hit_pos.getZ()/cm);

    analysisManager->FillNtupleDColumn(9,vertex_pos.getX()/cm);
    analysisManager->FillNtupleDColumn(10,vertex_pos.getY()/cm);
    analysisManager->FillNtupleDColumn(11,vertex_pos.getZ()/cm);

    analysisManager->FillNtupleDColumn(12,Ekin/MeV);
    analysisManager->FillNtupleDColumn(13,Etot/MeV);

    analysisManager->FillNtupleIColumn(14,trackID);
    analysisManager->FillNtupleIColumn(15,creatorID);
    analysisManager->FillNtupleIColumn(16,particleID);

    analysisManager->FillNtupleDColumn(17,px);
    analysisManager->FillNtupleDColumn(18,py);
    analysisManager->FillNtupleDColumn(19,pz);


    analysisManager->AddNtupleRow();
  }

}
