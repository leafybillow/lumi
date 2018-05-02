#include "lumiPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "g4root.hh"

lumiPrimaryGeneratorAction::lumiPrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction(),fParticleGun(NULL){

  G4int noParticles = 1;
  fParticleGun = new G4ParticleGun(noParticles);

  G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.0));
  fParticleGun->SetParticleEnergy(8.8*GeV);
}

lumiPrimaryGeneratorAction::~lumiPrimaryGeneratorAction(){
  delete fParticleGun;
}

void lumiPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
  G4double beam_z = -150*cm;
  
  G4double beam_x = 0*cm;
  G4double beam_y = 0*cm;
  //2x2 mm raster
  // G4double beam_x = 0.2*cm*(G4UniformRand()) - 0.1*cm;
  // G4double beam_y = 0.2*cm*(G4UniformRand()) - 0.1*cm;

  fParticleGun->SetParticlePosition(G4ThreeVector(beam_x,beam_y,beam_z));
  fParticleGun->GeneratePrimaryVertex(anEvent);

  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleDColumn(2,beam_x);
  analysisManager->FillNtupleDColumn(3,beam_y);
  analysisManager->FillNtupleDColumn(4,beam_z);

}
