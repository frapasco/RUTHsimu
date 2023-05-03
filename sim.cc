#include <iostream>
#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"

#include "DetectorConstruction.hh"
#include "physics.hh"
#include "action.hh"

#include "macros.hh"

int main(int argc, char** argv){
  #ifdef RANDOMSEED
  //Get current time
  time_t rawtime;
  time(&rawtime);
  struct tm* timeinfo = localtime(&rawtime);
  //Use current time as seed for the random number generator
  G4long seed = (timeinfo->tm_hour * 3600 + timeinfo->tm_min * 60 + timeinfo->tm_sec) * 1000000 + getpid();//getpid it is necessary for the multithreaded case
  G4cout << "Random seed: " << seed << G4endl;
  CLHEP::HepRandom::setTheSeed(seed);
  #endif
  G4RunManager* runManager = new G4RunManager();
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserInitialization(new ActionInitialization());
    
  runManager->Initialize();
 
  G4UIExecutive* ui = new G4UIExecutive(argc,argv);

  G4VisManager* visManager = new G4VisExecutive();
  visManager->Initialize();

  
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  UImanager->ApplyCommand("/control/execute macros/vis.mac");
  UImanager->ApplyCommand("/control/execute macros/run.mac");

#ifdef AXES
  UImanager->ApplyCommand("/vis/scene/add/axes 0 0 0 20 cm ");
#endif
  
  ui->SessionStart();

  return 0;
}
