#include "LuminositySD.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"

#include "G4SDManager.hh"
#include "G4VProcess.hh"

LuminositySD::LuminositySD(G4String SDName) :G4VSensitiveDetector(SDName){
  hitsCollection = NULL;
  HCID = -1;
  collectionName.insert("LumiHitColl");
}


LuminositySD::~LuminositySD(){
}

void LuminositySD::Initialize(G4HCofThisEvent *hce){

  hitsCollection = new LuminosityHitsCollection(SensitiveDetectorName,collectionName[0]);
  if(HCID<0){
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection);
  }
  hce->AddHitsCollection(HCID,hitsCollection);
  hitsCollection->insert(new LuminosityHit());
}


G4bool LuminositySD::ProcessHits(G4Step *aStep, G4TouchableHistory *){

  const G4Track* aTrack = aStep->GetTrack();
  G4String particle_name =aTrack->GetDefinition()->GetParticleName();
  G4bool fHitBefore = (*hitsCollection)[0]->GetHitBefore();
  //  G4cout << "PartName:" << particle_name << G4endl;
  if (particle_name=="e-"){
    
    if(!fHitBefore){ // if it is the first hit
      (*hitsCollection)[0]->SetHitBefore(true);
      (*hitsCollection)[0]->SetEdep(0.0); 
      G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
      G4TouchableHistory *theTouchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
      G4VPhysicalVolume *myPV = theTouchable->GetVolume(0);
      
      G4String pvName = myPV->GetName();
      G4int name_length = strlen(pvName.data());
      pvName.remove(0,name_length-1); 
      G4int detID = atoi(pvName.data());
      (*hitsCollection)[0]->SetDetID(detID);
      
      G4ThreeVector hit_pos = preStepPoint->GetPosition();
      (*hitsCollection)[0]->SetHitPos(hit_pos);

      G4double Etot = aTrack->GetTotalEnergy();
      (*hitsCollection)[0]->SetEtot(Etot);
      G4double Ekin = aTrack->GetKineticEnergy();
      (*hitsCollection)[0]->SetEkin(Ekin);

      G4int trackID = aTrack->GetTrackID();
      (*hitsCollection)[0]->SetTrackID(trackID);

      G4ThreeVector vertex_pos = aTrack->GetVertexPosition();
      (*hitsCollection)[0]->SetVertexPos(vertex_pos);
      
      // const G4VProcess *creatorProcess = aTrack->GetCreatorProcess();
      // if(creatorProcess!=0)
      // 	G4cout<< creatorProcess->GetProcessName() <<G4endl;
    }
    
    // const G4VProcess* creatorProcess = aTrack->GetCreatorProcess();
    // G4String processName;
    // if(creatorProcess!=0) processName = creatorProcess->GetProcessName();
    G4double edep = aStep->GetTotalEnergyDeposit();
    (*hitsCollection)[0]->AddEdep(edep); // accumulate edep

  }
  return true;
}