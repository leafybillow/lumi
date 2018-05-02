#include "G4UImessenger.hh"
#include "globals.hh"

class lumiDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;

class lumiDetectorMessenger: public G4UImessenger{

public:
  lumiDetectorMessenger(lumiDetectorConstruction*);
  virtual ~lumiDetectorMessenger();

  void SetNewValue(G4UIcommand*,G4String);

private:
  lumiDetectorConstruction* detectorConstruction;
  G4UIdirectory* uiDirectory;

  G4UIcmdWithAString *setGDMLCmd;

};
