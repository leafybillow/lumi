#include "lumiPrimaryGeneratorMessenger.hh"
#include "lumiPrimaryGeneratorAction.hh"

#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
#include "G4SystemOfUnits.hh"

lumiPrimaryGeneratorMessenger::lumiPrimaryGeneratorMessenger(lumiPrimaryGeneratorAction* pga)
  :G4UImessenger(), primaryGenAction(pga){

  gunDir = new G4UIdirectory("/lumi/gun/");
  gunDir->SetGuidance("PrimaryGenerator control");

  setGunType = new G4UIcmdWithAnInteger("/lumi/gun/beamtype",this);
  setGunType->SetParameterName("beamType",true);
  setGunType->SetDefaultValue(0);
  setGunType->AvailableForStates(G4State_PreInit,G4State_Idle);

  // setGunEnergy = new G4UIcmdWithADoubleAndUnit("/lumi/gun/energy",this);
  // setGunEnergy->SetParameterName("Energy",true);
  // setGunEnergy->SetDefaultValue(1.0*GeV);
  // setGunEnergy->AvailableForStates(G4State_PreInit,G4State_Idle);
}

lumiPrimaryGeneratorMessenger::~lumiPrimaryGeneratorMessenger(){
  delete gunDir;
  delete setGunType;
  // delete setGunEnergy;
}

void lumiPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue){

  if(command==setGunType){
    primaryGenAction->SetBeamType(setGunType->GetNewIntValue(newValue));
  }

  // if(command==setGunEnergy){
  //   primaryGenAction->SetBeamEnergy(setGunEnergy->GetNewDoubleValue(newValue));
  // }
    
}

