#include "lumiPrimaryGeneratorAction.hh"
#include "lumiPrimaryGeneratorMessenger.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "g4root.hh"

lumiPrimaryGeneratorAction::lumiPrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction(),fParticleGun(NULL),runType(-1){

  primaryMessenger = new lumiPrimaryGeneratorMessenger(this);
  
  G4int noParticles = 1;
  fParticleGun = new G4ParticleGun(noParticles);

  G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.0));
  fParticleGun->SetParticleEnergy(8.8*GeV);
}

lumiPrimaryGeneratorAction::~lumiPrimaryGeneratorAction(){
  delete primaryMessenger;
  delete fParticleGun;
}
void lumiPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
  switch(runType){
  case 0 : 
    GeneratePrimaries_origin(anEvent);
    break;
  case 1 :
    GeneratePrimaries_raster(anEvent);
    break;
  }

}

void lumiPrimaryGeneratorAction::GeneratePrimaries_origin(G4Event* anEvent){
  G4double beam_z = -150*cm;
  
  G4double beam_x = 0*cm;
  G4double beam_y = 0*cm;

  fParticleGun->SetParticlePosition(G4ThreeVector(beam_x,beam_y,beam_z));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}


void lumiPrimaryGeneratorAction::GeneratePrimaries_raster(G4Event* anEvent){
  G4double beam_z = -150*cm;

  //2.5x3 mm raster
  G4double beam_x = 0.25*cm*(G4UniformRand()) - 0.125*cm;
  G4double beam_y = 0.3*cm*(G4UniformRand()) - 0.15*cm;

  fParticleGun->SetParticlePosition(G4ThreeVector(beam_x,beam_y,beam_z));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

void lumiPrimaryGeneratorAction::SetBeamType(G4int type){
  runType = type;
}
