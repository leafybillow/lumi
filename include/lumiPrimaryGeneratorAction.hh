#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class lumiPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction{

public:
  lumiPrimaryGeneratorAction();
  virtual ~lumiPrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event *event);

private:
  G4ParticleGun* fParticleGun;

};