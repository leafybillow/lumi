#include "lumiDetectorMessenger.hh"
#include "lumiDetectorConstruction.hh"

#include "G4UIcmdWithAString.hh"

lumiDetectorMessenger::lumiDetectorMessenger(lumiDetectorConstruction* det)
  :G4UImessenger(), detectorConstruction(det){
  uiDirectory = new G4UIdirectory("/lumi/det/");
  uiDirectory->SetGuidance("detector control.");

  setGDMLCmd = new G4UIcmdWithAString("/lumi/det/setGDML",this);
  setGDMLCmd->SetGuidance("Set Main GDML File.");
  setGDMLCmd->SetParameterName("file_name",true);
  setGDMLCmd->SetDefaultValue("../geometry/main.gdml");
  // G4String candidateList=("main");
  //setGDMLCmd->SetCandidates(candidateList);
  setGDMLCmd->AvailableForStates(G4State_PreInit);
}


lumiDetectorMessenger::~lumiDetectorMessenger(){
  delete setGDMLCmd;
  delete uiDirectory;
}

void lumiDetectorMessenger::SetNewValue(G4UIcommand *uiCommand, G4String newValue){

  if(uiCommand==setGDMLCmd){
    detectorConstruction->SetGDML(newValue);
    G4cout << newValue << "GDML is used." << G4endl;
  }

}
