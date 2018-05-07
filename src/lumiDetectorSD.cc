#include "lumiDetectorSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"

#include "G4SDManager.hh"
#include "G4VProcess.hh"

lumiDetectorSD::lumiDetectorSD(G4String SDName) :G4VSensitiveDetector(SDName){
  hitsCollection = NULL;
  HCID = -1;
  collectionName.insert("LumiHitColl");
}


lumiDetectorSD::~lumiDetectorSD(){
}

void lumiDetectorSD::Initialize(G4HCofThisEvent *hce){
  
  hitsCollection = new lumiDetectorHitsCollection(SensitiveDetectorName,collectionName[0]);
  if(HCID<0){
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection);
  }
  hce->AddHitsCollection(HCID,hitsCollection);
}

G4bool lumiDetectorSD::ProcessHits(G4Step *aStep, G4TouchableHistory *){
  const G4Track* aTrack = aStep->GetTrack();
  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();

  if(preStepPoint->GetStepStatus()==fGeomBoundary){  
    lumiDetectorHit *this_hit = new lumiDetectorHit();
    
    G4TouchableHistory *theTouchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
    G4VPhysicalVolume *myPV = theTouchable->GetVolume(0);
    G4String pvName = myPV->GetName();
    G4int name_length = strlen(pvName.data());
    //    G4cout << pvName << G4endl;
    pvName.remove(0,name_length-2); 
    G4int detID = atoi(pvName.data());
    //    G4cout << detID << G4endl;
    this_hit->SetDetID(detID);
    
    G4String particle_name =aTrack->GetDefinition()->GetParticleName();
    if(particle_name=="gamma")
      this_hit->SetParticleID(0);
    if(particle_name=="e-")
      this_hit->SetParticleID(1);
    if(particle_name=="e+")
      this_hit->SetParticleID(2);
  //  G4bool fHitBefore = (*hitsCollection)[0]->GetHitBefore();
  //  if (particle_name=="e-"){
  //if(!fHitBefore){ // if it is the first hit
    //    (*hitsCollection)[0]->SetHitBefore(true);
    //    (*hitsCollection)[0]->SetEdep(0.0); 
      
    G4ThreeVector hit_pos = preStepPoint->GetPosition();
    this_hit->SetHitPos(hit_pos);


    G4double Etot = aTrack->GetTotalEnergy();
    this_hit->SetEtot(Etot);
    G4double Ekin = aTrack->GetKineticEnergy();
    this_hit->SetEkin(Ekin);

    G4int trackID = aTrack->GetTrackID();
    this_hit->SetTrackID(trackID);

    G4ThreeVector vertex_pos = aTrack->GetVertexPosition();
    this_hit->SetVertexPos(vertex_pos);

    G4ThreeVector momentum = aTrack->GetMomentum();
    this_hit->SetMomentum(momentum);
    
    const G4VProcess *creatorProcess = aTrack->GetCreatorProcess();
    if(creatorProcess!=0){
      G4String processName = creatorProcess->GetProcessName();
      if(processName=="eIoni")
	this_hit->SetCreatorID(1);
      else if(processName=="compt")
	this_hit->SetCreatorID(2);
      else if(processName=="conv")
	this_hit->SetCreatorID(3);
      else if(processName=="phot")
	this_hit->SetCreatorID(4);
      else if(processName=="eBrem")
	this_hit->SetCreatorID(5);
      else if(processName=="annihil")
	this_hit->SetCreatorID(6);
      else if(processName=="electronNuclear")
	this_hit->SetCreatorID(7);
      else if(processName=="photonNuclear")
	this_hit->SetCreatorID(8);
      else if(processName=="Decay")
	this_hit->SetCreatorID(9);
      else if(processName=="hIoni")
	this_hit->SetCreatorID(9);
      else{
	G4cout << processName << G4endl;
      	this_hit->SetCreatorID(-1);
      }
    }
    else
      this_hit->SetCreatorID(0); // Primary Source?

    hitsCollection->insert(this_hit);
    return true;
  }
  else
    return false;
  //}
    // if(detID ==this_hit->GetDetID()){
    //   G4double edep = aStep->GetTotalEnergyDeposit();
    //   this_hit->AddEdep(edep);
    // }
  //}

}
