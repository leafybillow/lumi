#include "lumiDetectorConstruction.hh"
#include "lumiActionInitialization.hh"

#include "FTFP_BERT.hh"
#include "FTFP_BERT_HP.hh"
#include "QGSP_BERT_HP.hh"
#include "QBBC.hh"
#include "FTF_BIC.hh"

#include "G4StepLimiterPhysics.hh"
#include "G4UImanager.hh"
#include "Randomize.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif


int main(int argc, char** argv){

#ifdef G4UI_USE
  G4UIExecutive* uiExecutive = 0;
  if(argc ==1){
    uiExecutive =new G4UIExecutive(argc,argv);
  }
#endif
  
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  //  runManager->SetNumberOfThreads(4);
#else
  G4RunManager* runManager = new G4RunManager;
#endif
  
  lumiDetectorConstruction *detectorConstruction = new lumiDetectorConstruction;
  runManager->SetUserInitialization(detectorConstruction);
  
  G4VModularPhysicsList *physicsList = new FTFP_BERT_HP;
  //  G4VModularPhysicsList *physicsList = new QGSP_BERT_HP;
  // G4VModularPhysicsList *physicsList = new QBBC;
  //  G4VModularPhysicsList *physicsList = new FTF_BIC;
  physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);
  
  runManager->SetUserInitialization(new lumiActionInitialization());

#ifdef G4VIS_USE  
  G4VisExecutive * visManager = new G4VisExecutive;
  visManager->Initialize();
#endif
  
  G4UImanager *uiManager = G4UImanager::GetUIpointer();

  if(argc!=1){
    G4String command = "/control/execute ";
    G4String filename = argv[1];
    uiManager->ApplyCommand(command+filename);
  }
  else{
#ifdef G4UI_USE
#ifdef G4VIS_USE
  uiManager->ApplyCommand("/control/execute init_vis.mac");
#else
  uiManager->ApplyCommand("/control/execute init.mac");
#endif
  uiExecutive->SessionStart();
  delete uiExecutive;
#endif
  }
  //uiManager->ApplyCommand("/control/execute gui.mac");
#ifdef G4VIS_USE  
  delete visManager;
#endif
  delete runManager;
  return 0;

}
  
