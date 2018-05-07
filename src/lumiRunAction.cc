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
    analysisManager->CreateNtupleIColumn("ev"); // 0
    
    analysisManager->CreateNtupleIColumn("nhits"); // 1
    analysisManager->CreateNtupleIColumn("detID"); // 2
    
    analysisManager->CreateNtupleDColumn("prim_x"); //3
    analysisManager->CreateNtupleDColumn("prim_y"); //4
    analysisManager->CreateNtupleDColumn("prim_z"); //5
    
    analysisManager->CreateNtupleDColumn("hit_x"); //6
    analysisManager->CreateNtupleDColumn("hit_y"); //7
    analysisManager->CreateNtupleDColumn("hit_z"); //8

    analysisManager->CreateNtupleDColumn("vertex_x"); //9
    analysisManager->CreateNtupleDColumn("vertex_y"); //10
    analysisManager->CreateNtupleDColumn("vertex_z"); //11
    
    analysisManager->CreateNtupleDColumn("Ekin"); // 12
    analysisManager->CreateNtupleDColumn("Etot"); // 13

    analysisManager->CreateNtupleIColumn("trackID"); // 14
    analysisManager->CreateNtupleIColumn("creatorID"); // 15
    analysisManager->CreateNtupleIColumn("particleID"); // 16

    analysisManager->CreateNtupleDColumn("px"); // 17
    analysisManager->CreateNtupleDColumn("py"); // 18
    analysisManager->CreateNtupleDColumn("pz"); // 18

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
