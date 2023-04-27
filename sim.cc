#include <iostream>
#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"

#include "DetectorConstruction.hh"
#include "physics.hh"
#include "action.hh"

//comment the following for debugging mode (verbosity in printouts)
//#define DEBUG
//comment the following line if randomized cosines are NOT wanted
//#define RANDOMCOS
//comment the following line if the LISE++ calculation is wanted
//#define AM

int main(int argc, char** argv){
  G4RunManager* runManager = new G4RunManager();
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserInitialization(new ActionInitialization());
  G4Random::setTheEngine(new CLHEP::MTwistEngine);
  runManager->Initialize();
 
  G4UIExecutive* ui = new G4UIExecutive(argc,argv);
  G4VisManager* visManager = new G4VisExecutive();
  visManager->Initialize();
  
  
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  UImanager->ApplyCommand("/control/execute macros/vis.mac");
  UImanager->ApplyCommand("/control/execute macros/run.mac");
  
  //for vidualizing axes
  //UImanager->ApplyCommand("/vis/scene/add/axes 0 0 0 20 cm ");

  ui->SessionStart();

  return 0;
}
