#include "G4VUserActionInitialization.hh"

class lumiActionInitialization: public G4VUserActionInitialization{

public:
  lumiActionInitialization();
  virtual ~lumiActionInitialization();

  virtual void Build() const;
  virtual void BuildForMaster() const;

};
