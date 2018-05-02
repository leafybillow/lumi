#include "G4VSensitiveDetector.hh"
#include "LuminosityHit.hh"
#include "G4Step.hh"

class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;

class LuminositySD : public G4VSensitiveDetector{
public:
  LuminositySD(G4String SDName);
  virtual ~LuminositySD();

  virtual void Initialize(G4HCofThisEvent *hce);
  virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *);

private:
  LuminosityHitsCollection* hitsCollection;
  G4int HCID;
};
