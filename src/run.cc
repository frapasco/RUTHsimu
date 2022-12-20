#include "run.hh"

MyRunAction::MyRunAction(){}

MyRunAction::~MyRunAction(){}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

   /* man->OpenFile("output.root");
man->CreateNtuple("Hits","Hits");
    man->CreateNtupleIColumn("4");
    man->CreateNtupleIColumn("4");
    man->CreateNtupleIColumn("5");
    man->CreateNtupleIColumn("6");
    man->FinishNtuple(0);*/
    man->CreateNtuple("Hits","Hits");
    man->CreateNtupleIColumn("FEvent");
    /*man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("FY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(0);*/
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}