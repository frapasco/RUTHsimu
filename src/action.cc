#include "action.hh"

ActionInitialization::ActionInitialization(){}
ActionInitialization::~ActionInitialization(){}

void ActionInitialization::Build() const{
  PrimaryGenerator *generator = new PrimaryGenerator();
  SetUserAction(generator);
}

PrimaryGenerator::PrimaryGenerator(){
  fParticleGun = new G4ParticleGun(1);//creating just 1 primary vertex per particle

  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "proton";
  G4ParticleDefinition *particle = particleTable->FindParticle("geantino");
  
  G4ThreeVector pos(0.,0.,0.);//particle generated at the origin
  G4ThreeVector mom(0.,0.,1.);//particle generated along z-direction

  fParticleGun->SetParticlePosition(pos);
  fParticleGun->SetParticleMomentumDirection(mom);
  fParticleGun->SetParticleMomentum(0.*MeV);
  fParticleGun->SetParticleDefinition(particle);

}
PrimaryGenerator::~PrimaryGenerator(){
  delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event *anEvent){
  G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();

  if(particle == G4Geantino::Geantino()){
    G4int Z = 2;
    G4int A = 4;

    G4double charge = 2.*eplus;
    G4double energy = 0.*MeV;

    G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(charge);
  }
  
  fParticleGun->GeneratePrimaryVertex(anEvent);
}