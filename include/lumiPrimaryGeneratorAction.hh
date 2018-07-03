#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class lumiPrimaryGeneratorMessenger;

class lumiPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction{
public:
  lumiPrimaryGeneratorAction();
  virtual ~lumiPrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event *event);
  void GeneratePrimaries_origin(G4Event *event);
  void GeneratePrimaries_raster(G4Event *event);
  void GeneratePrimaries_remollAl(G4Event *event);
  void SetBeamType(G4int);
  // void SetBeamEnergy(G4double);
private:
  G4ParticleGun* fParticleGun;
  G4int runType;
  G4double energy;
  lumiPrimaryGeneratorMessenger *primaryMessenger;
};
