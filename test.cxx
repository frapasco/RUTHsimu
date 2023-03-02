#include <TText.h>
#include <vector>
//number of max hits read, it shoudn't be too larger than the simulated particles for a better memory management
const Int_t nMaxTotalHits = 100;

//arrays to be filled with leaves content
vector<int> vEventNo;
vector<double> vXPRE;
vector<double> vYPRE;
vector<double> vZPRE;
vector<double> vXPOST;
vector<double> vYPOST;
vector<double> vZPOST;
vector<double> veDep;
vector<long> vcopyNo;

//methods that reads the file 
void readTTree(){ 
  TFile *inFile = new TFile("output.root");
  TTree *hitTree=(TTree*)inFile->Get("Hits");

  //leaves
  int EventNo;
  double XPRE;
  double YPRE;
  double ZPRE;
  double XPOST;
  double YPOST;
  double ZPOST;
  int eDep;
  long copyNo;
  
  //set branch addresses
  TBranch *inbranch1 = hitTree->GetBranch("EventNo");
  inbranch1->SetAddress(&EventNo);
  TBranch *inbranch2 = hitTree->GetBranch("XPRE");
  inbranch2->SetAddress(&XPRE);
  TBranch *inbranch3 = hitTree->GetBranch("YPRE");
  inbranch3->SetAddress(&YPRE);
  TBranch *inbranch4 = hitTree->GetBranch("ZPRE");
  inbranch4->SetAddress(&ZPRE);
  TBranch *inbranch5 = hitTree->GetBranch("XPOST");
  inbranch5->SetAddress(&XPOST);
  TBranch *inbranch6 = hitTree->GetBranch("YPOST");
  inbranch6->SetAddress(&YPOST);
  TBranch *inbranch7 = hitTree->GetBranch("ZPOST");
  inbranch7->SetAddress(&ZPOST);
  TBranch *inbranch8 = hitTree->GetBranch("eDep");
  inbranch8->SetAddress(&eDep);
  TBranch *inbranch9 = hitTree->GetBranch("copyNo");
  inbranch9->SetAddress(&copyNo);

  int nentries = hitTree->GetEntries();
  std::cout<<"got "<<nentries<<" events"<<std::endl;
  //filling the vectors
  for(int i=0; i<nentries;i++){
    inbranch1->GetEntry(i);
    vEventNo.push_back(EventNo);
    //PRE POS
    inbranch2->GetEntry(i);
    vXPRE.push_back(XPRE);
    inbranch3->GetEntry(i);
    vYPRE.push_back(YPRE);
    inbranch4->GetEntry(i);
    vZPRE.push_back(ZPRE);
    //POST POS
    inbranch5->GetEntry(i);
    vXPOST.push_back(XPOST);
    inbranch6->GetEntry(i);
    vYPOST.push_back(YPOST);
    inbranch7->GetEntry(i);
    vZPOST.push_back(ZPOST);

    inbranch8->GetEntry(i);
    veDep.push_back(eDep);
    inbranch9->GetEntry(i);
    vcopyNo.push_back(copyNo);

  }
  for(int i=0;i<vEventNo.size();i++){
    std::cout<<vEventNo.at(i)<<std::endl;
    std::cout<<"x"<<vXPRE.at(i)<<std::endl;
    std::cout<<"y"<<vYPRE.at(i)<<std::endl;
    std::cout<<"z"<<vZPRE.at(i)<<std::endl;
    std::cout<<"x"<<vXPOST.at(i)<<std::endl;
    std::cout<<"y"<<vYPOST.at(i)<<std::endl;
    std::cout<<"z"<<vZPOST.at(i)<<std::endl;
    std::cout<<veDep.at(i)<<std::endl;
    std::cout<<vcopyNo.at(i)<<std::endl;
  }

  inFile->Close();
}

//method to be called
void analysis(){
 /* readTTree();
  //sorting events w.r.t. EventNo
  for(int i=0; i < nMaxTotalHits; i++){
    //before target
    TVector3 PreDetectorPrePos;
    TVector3 PreDetectorPostPos;
    //after target
    TVector3 PostDetectorPrePos;
    TVector3 PostDetectorPostPos;
    std::cout<<"EventNo "<<i<<" : "<<EventNo[i]<<std::endl;
    //sorting the hits between pre and post detector
    if(copyNo[i] == 0){ //copyNo = 0 corresponds to the detector before target
      //before target
      PreDetectorPrePos.SetXYZ(XPRE[i],YPRE[i],ZPRE[i]);
      PreDetectorPostPos.SetXYZ(XPOST[i],YPOST[i],ZPOST[i]); 
    }else{
      //after target
      PostDetectorPrePos.SetXYZ(XPRE[i],YPRE[i],ZPRE[i]);
      PostDetectorPostPos.SetXYZ(XPOST[i],YPOST[i],ZPOST[i]);
    }
    std::cout<<"pre detector pre pos "<<i<<" : "<<PreDetectorPrePos.X()<<", "<<PreDetectorPrePos.Y()<<", "<<PreDetectorPrePos.Z()<<std::endl;
    std::cout<<"pre detector post pos "<<i<<" : "<<PreDetectorPostPos.X()<<", "<<PreDetectorPostPos.Y()<<", "<<PreDetectorPostPos.Z()<<std::endl;
    std::cout<<"post detector pre pos "<<i<<" : "<<PostDetectorPrePos.X()<<", "<<PostDetectorPrePos.Y()<<", "<<PostDetectorPrePos.Z()<<std::endl;
    std::cout<<"post detector post pos "<<i<<" : "<<PostDetectorPostPos.X()<<", "<<PostDetectorPostPos.Y()<<", "<<PostDetectorPostPos.Z()<<std::endl;
 */ 
}
