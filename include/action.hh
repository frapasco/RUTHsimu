#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"

#include "generator.hh"

class MyActionInitialization : public G4VUserActionInitialization{
public:
  MyActionInitialization();
  ~MyActionInitialization();
  
  virtual void Build() const; 
};

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction{
public:
  MyPrimaryGeneratorAction();
  ~MyPrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event* anEvent);
private:
  G4ParticleGun *fParticleGun;
};

#endif
