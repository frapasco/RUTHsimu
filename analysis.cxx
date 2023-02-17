#include "vector"
#include "fstream"

#include <TDatabasePDG.h>
#include <TEveManager.h>
#include <TGeoManager.h>
#include <TRandom.h>
#include <TVector3.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TVirtualMagField.h>
#include <TClonesArray.h>
#include <TApplication.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TText.h>

const Int_t nMaxTotalHits = 500;
void analysis(){
Int_t EventNo[nMaxTotalHits]={0};
Double_t XPreStepPoint[nMaxTotalHits]={0.};
Double_t YPreStepPoint[nMaxTotalHits]={0.};
Double_t ZPreStepPoint[nMaxTotalHits]={0.};
Double_t XPostStepPoint[nMaxTotalHits]={0.};
Double_t YPostStepPoint[nMaxTotalHits]={0.};
Double_t ZPostStepPoint[nMaxTotalHits]={0.};
Double_t eDep[nMaxTotalHits]={0.};
Int_t copyNo[nMaxTotalHits]={0};

TString inputFileName="output.root";
TFile *inFile=new TFile(inputFileName,"READ");
  
TTree *hitTree=(TTree*)inFile->Get("hitTree");

// Set branch addresses.
hitTree->SetBranchAddress("EventNo",&EventNo);
hitTree->SetBranchAddress("XPreStepPoint",XPreStepPoint);
hitTree->SetBranchAddress("YPreStepPoint",YPreStepPoint);
hitTree->SetBranchAddress("ZPreStepPoint",ZPreStepPoint);
hitTree->SetBranchAddress("XPostStepPoint",XPostStepPoint);
hitTree->SetBranchAddress("YPostStepPoint",YPostStepPoint);
hitTree->SetBranchAddress("ZPostStepPoint",ZPostStepPoint);
hitTree->SetBranchAddress("eDep",eDep);
hitTree->SetBranchAddress("copyNo",&copyNo);
    
Long64_t nentries = hitTree->GetEntries();
std::cout<<"got "<<nentries<<" events"<<std::endl;
}
