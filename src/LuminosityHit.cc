#include "LuminosityHit.hh"

#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4AttDefStore.hh"
#include "G4UIcommand.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"

G4ThreadLocal G4Allocator<LuminosityHit>* LuminosityHitAllocator;

LuminosityHit::LuminosityHit() :G4VHit(){
  fEdep = -1;
  fHitBefore = false; // for a new Hit, no hit before
  copyNo = -1;
  hit_pos = G4ThreeVector(0,0,0);
  vertex_pos = G4ThreeVector(0,0,0);
  detID = -1;
  Ekin = -1;
  Etot = -1;
  trackID = -1;
  procID = -1;
  // fLogVol = nullptr;
}
// LuminosityHit::LuminosityHit(G4int i) :G4VHit(){
//   // layerID = i;
//   fEdep  = 0;
//   fLogVol = nullptr
// }
LuminosityHit::~LuminosityHit(){
}
LuminosityHit::LuminosityHit(const LuminosityHit &right)  :G4VHit(){

  fEdep = right.fEdep;
  fHitBefore = right.fHitBefore;
  hit_pos = right.hit_pos;
  vertex_pos = right.vertex_pos;
  copyNo = right.copyNo;
  detID = right.detID;
  Etot = right.Etot;
  Ekin = right.Ekin;
  trackID = right.trackID;
  procID = right.procID;
  //  fLogVol = right.fLogVol;
}

const LuminosityHit& LuminosityHit::operator=(const LuminosityHit &right){

  fEdep = right.fEdep;
  fHitBefore = right.fHitBefore;
  hit_pos = right.hit_pos;
  vertex_pos = right.vertex_pos;
  copyNo = right.copyNo;
  detID = right.detID;
  Etot = right.Etot;
  Ekin = right.Ekin;
  trackID = right.trackID;
  procID = right.procID;
  //  fLogVol = right.fLogVol;
  return *this;
}

int LuminosityHit::operator==(const LuminosityHit &right) const{
  return 0;
}

void LuminosityHit::Draw(){
  // G4VVisManager* visManager = G4VVisManager::GetConcreteInstance();
  // if(visManager){
  //   G4Circle circle(hit_pos);
  //   circle.SetScreenSize(0.04);
  //   circle.SetFillStyle(G4Circle::filled);
  //   G4Colour colour(1,0,0);
  //   G4VisAttributes visAttributes(colour);
  //   circle.SetVisAttributes(visAttributes);
  //   visManager->Draw(circle);
  // }
}
  

const  std::map<G4String, G4AttDef>* LuminosityHit::GetAttDefs() const{
  // G4bool isNew;
  // std::map<G4String,G4AttDef>* store
  //   = G4AttDefStore::GetInstance("LuminosityHit",isNew);

  // if(isNew){
  //   G4String HitType("HitType");
  //   (*store)[HitType] = G4AttDef(HitType,"HitType","Physiscs","","G4String");

  //   G4String LayerID_str("LayerID");
  //   (*store)[LayerID_str] = G4AttDef(LayerID_str,"LayerID","Physics","","G4int");

  //   G4String Position_str("Position");
  //   (*store)[Position_str] = G4AttDef(Position_str,"Position","Physics","G4BestUnit","G4ThreeVector");

  //   G4String ParticleName_str("ParticleName");
  //   (*store)[ParticleName_str] = G4AttDef(ParticleName_str,"ParticleName","Physics","","G4String");
  // }

  // return store;
}

std::vector<G4AttValue>* LuminosityHit::CreateAttValues() const{

  // std::vector<G4AttValue>* attValue = new std::vector<G4AttValue>;

  // attValue->push_back(G4AttValue("HitType","LuminosityHit",""));
  // // attValue->push_back(G4AttValue("LayerID",G4UIcommand::ConvertToString(layerID),""));
  // // attValue->push_back(G4AttValue("Position",G4BestUnit(worldPos,"Length"),""));
  // // attValue->push_back(G4AttValue("ParticleName",particleName,""));

  // return attValue;

}
void LuminosityHit::Print(){

}
