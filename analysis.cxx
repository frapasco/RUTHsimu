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

//number of max hits read, it shoudn't be too larger than the simulated particles for a better memory management
const Int_t nMaxTotalHits = 10000;

//arrays to be filled with branches content
Int_t EventNo[nMaxTotalHits]={0};
Double_t XPRE[nMaxTotalHits]={0.};
Double_t YPRE[nMaxTotalHits]={0.};
Double_t ZPRE[nMaxTotalHits]={0.};
Double_t XPOST[nMaxTotalHits]={0.};
Double_t YPOST[nMaxTotalHits]={0.};
Double_t ZPOST[nMaxTotalHits]={0.};
Double_t eDep[nMaxTotalHits]={0.};
Int_t copyNo[nMaxTotalHits]={0};

//methods that reads the file 
void readTTree(){  
  TString inputFileName="output.root";
  TFile *inFile=new TFile(inputFileName,"READ");
  
  TTree *hitTree=(TTree*)inFile->Get("Hits");
  
  //set branch addresses
  hitTree->SetBranchAddress("EventNo",&EventNo);
  hitTree->SetBranchAddress("XPRE",XPRE);
  hitTree->SetBranchAddress("YPRE",YPRE);
  hitTree->SetBranchAddress("ZPRE",ZPRE);
  hitTree->SetBranchAddress("XPOST",XPOST);
  hitTree->SetBranchAddress("YPOST",YPOST);
  hitTree->SetBranchAddress("ZPOST",ZPOST);
  hitTree->SetBranchAddress("eDep",eDep);
  hitTree->SetBranchAddress("copyNo",&copyNo);
  
  Long64_t nentries = hitTree->GetEntries();
  std::cout<<"got "<<nentries<<" events"<<std::endl;

  inFile->Close();
}

//method to be called
void analysis(){
  readTTree();
  //before target
  TVector3 PreDetectorPrePos;
  TVector3 PreDetectorPostPos;
  //after target
  TVector3 PostDetectorPrePos;
  TVector3 PostDetectorPostPos;

  //sorting the hits between pre and post detector
  if(copyNo==0){ //copyNo = 0 corresponds to the detector before target
    PreDetectorPrePos=(XPRE,YPRE,ZPRE);
    PreDetectorPostPos=(XPOST,YPOST,ZPOST);
  }else{
    PostDetectorPrePos=(XPRE,YPRE,ZPRE);
    PostDetectorPostPos=(XPOST,YPOST,ZPOST);
  }
}
