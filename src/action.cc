#include "action.hh"
#include "const.hh"

//comment the following line if radndomized cosines are wanted
//#define RANDOMCOS

ActionInitialization::ActionInitialization(){}
ActionInitialization::~ActionInitialization(){}

void ActionInitialization::Build() const{
  PrimaryGenerator *generator = new PrimaryGenerator();
  SetUserAction(generator);

  MyRunAction *runAction = new MyRunAction();
  SetUserAction(runAction);
}

PrimaryGenerator::PrimaryGenerator(){
  fParticleGun = new G4ParticleGun(1);//creating just 1 primary vertex per particle

  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "geantino";
  G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

  G4ThreeVector mom(0.,0.,1.);//particle generated along z-direction

  fParticleGun->SetParticleMomentumDirection(mom);
  fParticleGun->SetParticleMomentum(100.*MeV);
  fParticleGun->SetParticleDefinition(particle);

}

PrimaryGenerator::~PrimaryGenerator(){
  delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event *anEvent){
  G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();

  if(particle == G4Geantino::Geantino()){
    G4int Z = 2; //alpha particle
    G4int A = 4;

    G4double charge = 2.*eplus;
    G4double energy = 4.9*MeV; //frapasco: to be fixed

    G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(charge);
  }
  
  //randomized position
  G4double x0  = 0.*mm, y0 = 0.*mm , z0 = americiumZ-0.5*AmLayerThickness;
  G4double dx0 = 0.5*coreDiameter, dy0 = 0.5*coreDiameter, dz0 = 0.5*AmLayerThickness;
  x0 += dx0*(G4UniformRand());
  y0 += dy0*(G4UniformRand());
  z0 += dz0*(G4UniformRand());

  G4ThreeVector pos(x0,y0,z0); //generated randomized around the center of Am241
  fParticleGun->SetParticlePosition(pos);
  
  #ifdef RANDOMCOS
  //randomized cosines
  G4double cosTheta = -1.0 + 2.0 * G4UniformRand();
  G4double phi = 2*CLHEP::pi*G4UniformRand();
  G4double sinTheta = sqrt(1. - cosTheta*cosTheta);
  // these are the cosines for an isotropic direction
  G4ThreeVector mom(sinTheta*cos(phi), sinTheta*sin(phi), cosTheta);
  fParticleGun -> SetParticleMomentumDirection(mom);
  #endif
  
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
