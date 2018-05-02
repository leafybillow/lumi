#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4LogicalVolume.hh"
#include "G4ios.hh"

class LuminosityHit: public G4VHit{
public:
  LuminosityHit();
  // LuminosityHit(G4int i);
  
  LuminosityHit(const LuminosityHit &right);
  virtual ~LuminosityHit();

  const LuminosityHit& operator=(const LuminosityHit &right);
  int operator==(const LuminosityHit &right) const;

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

  inline void SetCopyNo(G4int i) { copyNo = i;}
  inline G4int GetCopyNo() const {return copyNo;}
  
  inline void SetDetID(G4int i)  { detID = i;}
  inline G4int GetDetID() const {return detID ;}

  inline void SetEtot(G4double e){ Etot=e;}
  inline G4double GetEtot() const {return Etot;}

  inline void SetEkin(G4double e){ Ekin=e;}
  inline G4double GetEkin() const {return Ekin;}

  inline void SetTrackID(G4int i){ trackID=i;}
  inline G4int GetTrackID() const {return trackID;}

  inline void SetProcID(G4int i){ procID=i;}
  inline G4int GetProcID() const {return procID;}

private:
  G4double fEdep;
  G4bool fHitBefore;
  G4int copyNo;
  G4int detID;
  G4ThreeVector hit_pos;
  G4ThreeVector vertex_pos;

  G4double Etot;
  G4double Ekin;

  G4int trackID;
  G4int procID;
  
};

//using LuminosityHitsCollection = G4THitsCollection<LuminosityHit>;
typedef G4THitsCollection<LuminosityHit> LuminosityHitsCollection;
extern G4ThreadLocal G4Allocator<LuminosityHit>* LuminosityHitAllocator;

inline void* LuminosityHit::operator new(size_t){
  // void *aHit;
  // aHit = (void *) LuminosityHitAllocator->MallocSingle();
  // return aHit;
  if(!LuminosityHitAllocator){
    LuminosityHitAllocator = new G4Allocator<LuminosityHit>;
  }
  return (void*)LuminosityHitAllocator->MallocSingle();
}

inline void LuminosityHit::operator delete(void *aHit){
  LuminosityHitAllocator->FreeSingle((LuminosityHit*) aHit);
}
