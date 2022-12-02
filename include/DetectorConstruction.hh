#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh" 
#include "G4Material.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"


class DetectorConstruction : public G4VUserDetectorConstruction{
public:
  DetectorConstruction();
  ~DetectorConstruction();
  
  virtual G4VPhysicalVolume* Construct();
  
private:
  G4VPhysicalVolume* PhysicalWorld;
};
#endif
