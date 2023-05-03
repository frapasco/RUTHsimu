#include <TText.h>
#include <vector>

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
  readTTree();
  TCanvas *c1 = new TCanvas();
  TCanvas *c2 = new TCanvas();
  TH1D* h = new TH1D("","",200,0,200);
  c1->cd()->SetGrid();
  TCanvas *c3 = new TCanvas();
  TH1D* h1 = new TH1D("","",200000,0,200000);
  c3->cd()->SetGrid();
  TH2D* hXY = new TH2D("","",60,-60,60,60,-60,60);
  c2->cd()->SetGrid();
  TVector3 z(0,0,1);
  for(int i=0;i<vYPRE.size();i++){
    TVector3 v (vXPRE[i],vYPRE[i],vZPRE[i]);
    hXY->Fill(vXPRE[i],vYPRE[i]);
    double theta = v.Angle(z);//TMath::ACos(vZPRE[i]/TMath::Sqrt(TMath::Power(vXPRE[i],2)+TMath::Power(vYPRE[i],2)+TMath::Power(vZPRE[i],2)));
    double thetaProp = TMath::Sqrt(TMath::Power(vXPRE[i],2)+TMath::Power(vYPRE[i],2)+TMath::Power(vZPRE[i],2));
    h->Fill(theta*180/TMath::Pi());
    h1->Fill(thetaProp*180/TMath::Pi());
  }
  c1->cd(); h->Draw();
  c3->cd(); h1->Draw("COLZ");
  c2->cd(); hXY->Draw("COLZ");
}
