#include "lumiRunAction.hh"
#include "lumiEventAction.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "g4root.hh"

lumiRunAction::lumiRunAction(lumiEventAction* eventAction)
  :G4UserRunAction(),fEventAction(eventAction){

  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
  
  //analysisManager->SetNtupleMerging(true);
  // Mute Merging for gcc-4.4.7
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("lumi");

  G4cout << "Creating ROOT file" << G4endl;
  
  if (fEventAction){
    analysisManager->CreateNtuple("lumi","Hits");
    analysisManager->CreateNtupleIColumn("Hits"); // 0
    analysisManager->CreateNtupleDColumn("Edep"); // 1

    analysisManager->CreateNtupleDColumn("prim_x"); //2
    analysisManager->CreateNtupleDColumn("prim_y"); //3
    analysisManager->CreateNtupleDColumn("prim_z"); //4
    
    analysisManager->CreateNtupleDColumn("hit_x"); //5
    analysisManager->CreateNtupleDColumn("hit_y"); //6
    analysisManager->CreateNtupleDColumn("hit_z"); //7

    analysisManager->CreateNtupleIColumn("samID"); // 8

    analysisManager->CreateNtupleDColumn("Ekin"); // 9
    analysisManager->CreateNtupleDColumn("Etot"); // 10

    analysisManager->CreateNtupleIColumn("trackID"); // 11

    analysisManager->CreateNtupleDColumn("vertex_x"); //12
    analysisManager->CreateNtupleDColumn("vertex_y"); //13
    analysisManager->CreateNtupleDColumn("vertex_z"); //14

    analysisManager->CreateNtupleIColumn("procID"); // 15

    //beamline detector
    analysisManager->CreateNtupleDColumn("bhit_x"); // 16
    analysisManager->CreateNtupleDColumn("bhit_y"); // 17
    analysisManager->CreateNtupleDColumn("bhit_z"); // 18

    analysisManager->CreateNtupleDColumn("bvertex_x"); // 19
    analysisManager->CreateNtupleDColumn("bvertex_y"); // 20
    analysisManager->CreateNtupleDColumn("bvertex_z"); // 21
    
    analysisManager->CreateNtupleDColumn("bdet_Ekin"); // 22
    analysisManager->CreateNtupleDColumn("bdet_Etot"); // 23
    
    analysisManager->CreateNtupleIColumn("bdet_procID"); // 24
    analysisManager->CreateNtupleIColumn("bdet_trackID"); // 25
    
    analysisManager->FinishNtuple();
  }
}

lumiRunAction::~lumiRunAction(){
  delete G4AnalysisManager::Instance();
}


void lumiRunAction::BeginOfRunAction(const G4Run*){
  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile();
}

void lumiRunAction::EndOfRunAction(const G4Run*){
  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}
