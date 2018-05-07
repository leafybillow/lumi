#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4LogicalVolume.hh"
#include "G4ios.hh"

class lumiDetectorHit: public G4VHit{
public:
  lumiDetectorHit();
  
  lumiDetectorHit(const lumiDetectorHit &right);
  virtual ~lumiDetectorHit();

  const lumiDetectorHit& operator=(const lumiDetectorHit &right);
  int operator==(const lumiDetectorHit &right) const;

  virtual void Draw();
  virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
  virtual std::vector<G4AttValue>* CreateAttValues() const;
  virtual void Print();
  
  inline void* operator new(size_t);
  inline void operator delete(void *aHit);

  void SetHitBefore(G4bool i) {fHitBefore = i;}
  G4bool GetHitBefore() const {return fHitBefore;}
  
  void SetEdep(G4double de) {fEdep = de;}
  void AddEdep(G4double de) {fEdep +=de;}
  G4double GetEdep() const {return fEdep;}

  // void SetLogicalVolume(G4LogicalVolume *LV) {fLogVol = LV;}
  // const G4LogicalVolume *GetLogicalVolume() const {return fLogVol;}

  inline void SetHitPos(G4ThreeVector xyz) {hit_pos =xyz;}
  inline G4ThreeVector GetHitPos() const { return hit_pos;}

  inline void SetVertexPos(G4ThreeVector xyz) {vertex_pos =xyz;}
  inline G4ThreeVector GetVertexPos() const { return vertex_pos;}

  inline void SetMomentum(G4ThreeVector xyz) {momentum =xyz;}
  inline G4ThreeVector GetMomentum() const { return momentum;}

  inline void SetDetID(G4int i)  { detID = i;}
  inline G4int GetDetID() const {return detID;}

  inline void SetEtot(G4double e){ Etot=e;}
  inline G4double GetEtot() const {return Etot;}

  inline void SetEkin(G4double e){ Ekin=e;}
  inline G4double GetEkin() const {return Ekin;}

  inline void SetTrackID(G4int i){ trackID=i;}
  inline G4int GetTrackID() const {return trackID;}

  inline void SetCreatorID(G4int i){ creatorID=i;}
  inline G4int GetCreatorID() const {return creatorID;}
  
  inline void SetParticleID(G4int i){ partID=i;}
  inline G4int GetParticleID() const {return partID;}

private:
  G4double fEdep;
  G4bool fHitBefore;
  
  G4int detID;
  G4ThreeVector hit_pos;
  G4ThreeVector vertex_pos;
  G4ThreeVector momentum;

  G4double Etot;
  G4double Ekin;

  G4int trackID;
  G4int creatorID;
  G4int partID;
};

typedef G4THitsCollection<lumiDetectorHit> lumiDetectorHitsCollection;
extern G4ThreadLocal G4Allocator<lumiDetectorHit>* lumiDetectorHitAllocator;

inline void* lumiDetectorHit::operator new(size_t){

  if(!lumiDetectorHitAllocator){
    lumiDetectorHitAllocator = new G4Allocator<lumiDetectorHit>;
  }
  return (void*)lumiDetectorHitAllocator->MallocSingle();
}

inline void lumiDetectorHit::operator delete(void *aHit){
  lumiDetectorHitAllocator->FreeSingle((lumiDetectorHit*) aHit);
}
