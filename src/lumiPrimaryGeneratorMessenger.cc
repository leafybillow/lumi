#include "lumiPrimaryGeneratorMessenger.hh"
#include "lumiPrimaryGeneratorAction.hh"

#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"

lumiPrimaryGeneratorMessenger::lumiPrimaryGeneratorMessenger(lumiPrimaryGeneratorAction* pga)
  :G4UImessenger(), primaryGenAction(pga){

  gunDir = new G4UIdirectory("/lumi/gun/");
  gunDir->SetGuidance("PrimaryGenerator control");

  setGunCmd = new G4UIcmdWithAnInteger("/lumi/gun/beamtype",this);
  setGunCmd->SetParameterName("beamType",true);
  setGunCmd->SetDefaultValue(0);
  setGunCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

lumiPrimaryGeneratorMessenger::~lumiPrimaryGeneratorMessenger(){
  delete gunDir;
  delete setGunCmd;
}

void lumiPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue){

  if(command==setGunCmd){
    primaryGenAction->SetBeamType(setGunCmd->GetNewIntValue(newValue));
  }

}

