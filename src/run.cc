#include "run.hh"

MyRunAction::MyRunAction(){
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  
  man->CreateNtuple("Hits","Hits");
  man->CreateNtupleIColumn("EventNo");
  
  //PRE POSITIONS column: 1 2 3 
  man->CreateNtupleDColumn("XPRE");
  man->CreateNtupleDColumn("YPRE");
  man->CreateNtupleDColumn("ZPRE");
  //POST POSITIONS column: 4 5 6
  man->CreateNtupleDColumn("XPOST");
  man->CreateNtupleDColumn("YPOST");
  man->CreateNtupleDColumn("ZPOST");
  
  //energy deposited on detector
  man->CreateNtupleDColumn("eDep");
  
  //in order to divide the hits of the two detectors they are all recorded in both vectors, but later on in analysis one has to sort them with copyNo
  man->CreateNtupleIColumn("copyNo");
  man->FinishNtuple(0);


}

MyRunAction::~MyRunAction(){}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->OpenFile("output.root"); 
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    
    man->CloseFile();
}
