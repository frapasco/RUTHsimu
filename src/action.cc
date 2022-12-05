#include "action.hh"

MyActionInitialization::MyActionInitialization(){}
MyActionInitialization::~MyActionInitialization(){}

void MyActionInitialization::Build() const{
  PrimaryGenerator *generator = new PrimaryGenerator();
  SetUserAction(generator);
}

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction(){
  fParticleGun = new G4ParticleGun(1);//creating just 1 primary vertex per particle
}
MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction(){
  delete fParticleGun;
}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent){
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "proton";
  G4ParticleDefinition *particle = particleTable->FindParticle("proton");

  G4ThreeVector pos(0.,0.,0.);//particle generated at the origin
  G4ThreeVector mom(0.,0.,1.);//particle generated along z-direction

  fParticleGun->SetParticlePosition(pos);
  fParticleGun->SetParticleMomentumDirection(mom);
  fParticleGun->SetParticleMomentum(4.*MeV);
  fParticleGun->SetParticleDefinition(particle);

  fParticleGun->GeneratePrimaryVertex(anEvent);
}
