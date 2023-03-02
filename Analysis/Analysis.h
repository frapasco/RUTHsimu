//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar  2 12:17:35 2023 by ROOT version 6.26/06
// from TTree Hits/Hits
// found on file: output.root
//////////////////////////////////////////////////////////

#ifndef analysis_h
#define analysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class analysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           EventNo;
   Double_t        XPRE;
   Double_t        YPRE;
   Double_t        ZPRE;
   Double_t        XPOST;
   Double_t        YPOST;
   Double_t        ZPOST;
   Double_t        eDep;
   Int_t           copyNo;

   // List of branches
   TBranch        *b_EventNo;   //!
   TBranch        *b_XPRE;   //!
   TBranch        *b_YPRE;   //!
   TBranch        *b_ZPRE;   //!
   TBranch        *b_XPOST;   //!
   TBranch        *b_YPOST;   //!
   TBranch        *b_ZPOST;   //!
   TBranch        *b_eDep;   //!
   TBranch        *b_copyNo;   //!

   analysis(TTree *tree=0);
   virtual ~analysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef analysis_cxx
analysis::analysis(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("output.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("output.root");
      }
      f->GetObject("Hits",tree);

   }
   Init(tree);
}

analysis::~analysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t analysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t analysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void analysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventNo", &EventNo, &b_EventNo);
   fChain->SetBranchAddress("XPRE", &XPRE, &b_XPRE);
   fChain->SetBranchAddress("YPRE", &YPRE, &b_YPRE);
   fChain->SetBranchAddress("ZPRE", &ZPRE, &b_ZPRE);
   fChain->SetBranchAddress("XPOST", &XPOST, &b_XPOST);
   fChain->SetBranchAddress("YPOST", &YPOST, &b_YPOST);
   fChain->SetBranchAddress("ZPOST", &ZPOST, &b_ZPOST);
   fChain->SetBranchAddress("eDep", &eDep, &b_eDep);
   fChain->SetBranchAddress("copyNo", &copyNo, &b_copyNo);
   Notify();
}

Bool_t analysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void analysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t analysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef analysis_cxx
