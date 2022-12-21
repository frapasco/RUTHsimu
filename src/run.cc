#include "run.hh"

MyRunAction::MyRunAction(){}

MyRunAction::~MyRunAction(){}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->OpenFile("output.root");
    man->CreateNtuple("Hits","Hits");
    man->CreateNtupleIColumn("fPostEvent");
    man->CreateNtupleDColumn("fPost1X");
    man->CreateNtupleDColumn("fPost1Y");
    man->CreateNtupleDColumn("fPost1Z");
    man->CreateNtupleDColumn("fPost2X");
    man->CreateNtupleDColumn("fPost2Y");
    man->CreateNtupleDColumn("fPost2Z");
    man->CreateNtupleDColumn("fPreX");
    man->CreateNtupleDColumn("fPreY");
    man->CreateNtupleDColumn("fPreZ");
    man->FinishNtuple(0);
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}