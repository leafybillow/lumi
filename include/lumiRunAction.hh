#include "G4UserRunAction.hh"
#include "globals.hh"


class lumiEventAction;
class G4Run;

class lumiRunAction : public G4UserRunAction{
public:
  lumiRunAction(lumiEventAction* eventAction);
  virtual ~lumiRunAction();
  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);

private:
  lumiEventAction* fEventAction;

};
