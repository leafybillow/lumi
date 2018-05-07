#include "G4UserEventAction.hh"
#include "globals.hh"

//#include <vector>

class lumiEventAction : public G4UserEventAction{

public:
  lumiEventAction();
  virtual ~lumiEventAction();

  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);

private:
  G4int CollID;
};
