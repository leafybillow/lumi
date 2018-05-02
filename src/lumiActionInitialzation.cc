#include "lumiActionInitialization.hh"
#include "lumiPrimaryGeneratorAction.hh"
#include "lumiRunAction.hh"
#include "lumiEventAction.hh"

lumiActionInitialization::lumiActionInitialization()
  :G4VUserActionInitialization(){
}

lumiActionInitialization::~lumiActionInitialization(){
}

void lumiActionInitialization::Build() const{

  SetUserAction(new lumiPrimaryGeneratorAction);
  //  G4cout<< "Initialized Primary Generator Action" << G4endl;
  
  lumiEventAction *eventAction = new lumiEventAction;
  SetUserAction(eventAction);
  //  G4cout<< "Initialized Event Action" << G4endl;

  SetUserAction(new lumiRunAction(eventAction));
  //  G4cout<< "Initialized Run Action" << G4endl;
}

void lumiActionInitialization::BuildForMaster() const{

  lumiEventAction *eventAction = new lumiEventAction;
  SetUserAction(new lumiRunAction(eventAction));

}
