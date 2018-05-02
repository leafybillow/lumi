#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4GDMLParser.hh"
//#include "lumiDetectorMessenger.hh"

class lumiDetectorMessenger;
class G4VPhysicalVolume;
class G4LogicalVolume;
// class G4VSensitiveDetector;

class lumiDetectorConstruction: public G4VUserDetectorConstruction{

public:
  lumiDetectorConstruction();
  virtual ~lumiDetectorConstruction();
  
  virtual G4VPhysicalVolume* Construct();
  virtual G4VPhysicalVolume* ConstructDetector();
  virtual void ConstructSDandField();

  void SetGDML(const G4String& filename);
  
private:
  G4GDMLParser gdmlParser;
  G4String gdml_filename;
  G4LogicalVolume* detector_logic;

  lumiDetectorMessenger* detectorMessenger;
};


  
