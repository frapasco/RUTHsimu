#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction(){}
DetectorConstruction::~DetectorConstruction(){}

G4VPhysicalVolume* DetectorConstruction::Construct(){
  //--------------------------------------------------------
  //visualization attributes--------------------------------
  //--------------------------------------------------------
  G4VisAttributes* solidGreen = new G4VisAttributes(G4Colour(0.3,0.8,0.1));
  solidGreen->SetVisibility(true);
  solidGreen->SetForceSolid(TRUE);
  
  G4VisAttributes* solidBlue = new G4VisAttributes(G4Colour(0.2,0.3,0.8));
  solidBlue->SetVisibility(true);
  solidBlue->SetForceSolid(TRUE);
  
  G4VisAttributes* solidYellow = new G4VisAttributes(G4Colour(255/255., 255/255.,0/255.));
  solidYellow->SetVisibility(true);
  solidYellow->SetForceSolid(TRUE);

  
  //--------------------------------------------------------
  //materials-----------------------------------------------
  //--------------------------------------------------------
  G4NistManager* nist = G4NistManager::Instance();
  
  G4Material* defaultMat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* Al = nist->FindOrBuildMaterial("G4_Al");
  G4Material* Au = nist->FindOrBuildMaterial("G4_Au");
  G4Material* Am = nist->FindOrBuildMaterial("G4_Am");
  G4Material* Ag = nist->FindOrBuildMaterial("G4_Ag");
  //vacuum
  G4double atomicNumber = 1.;
  G4double massOfMole = 1.008*g/mole;
  G4double density = 1.e-25*g/cm3;
  G4double temperature = 2.73*kelvin;
  G4double pressure = 3.e-18*pascal;
  G4Material* vacuum = new G4Material("interGalactic", atomicNumber, massOfMole, density, kStateGas, temperature, pressure);

  //--------------------------------------------------------
  //world volume--------------------------------------------
  //--------------------------------------------------------
  G4Box* worldBox = new G4Box("World", 20*cm,20*cm,20*cm);
  G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, defaultMat, "WorldLog");
  PhysicalWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), worldLog, "physWorld", 0, false, 0, true);
  
  //--------------------------------------------------------
  //source support------------------------------------------
  //--------------------------------------------------------
  //mother volume
  G4Box* sourceSuportMother = new G4Box("supportMother", 0.5*(32.45*mm), 0.5*(104.05*mm), 0.5*(70.05*mm+31.25*mm));

  //--------------------------------------------------------
  //source--------------------------------------------------
  //--------------------------------------------------------
  //parameters that describe the source geometry
  G4double sourceExtDiameter = 12.7*mm;
  G4double coreDiameter = 7.*mm;
  G4double sourceTotLength = 79.*mm;
  G4double AuLayer1Thickness = 0.00051*mm;//layer A
  G4double AuLayer2Thickness = 0.0010*mm;//layer B
  G4double AmLayerThickness = 0.00051*mm;//layer C
  G4double AuLayer3Thickness = 0.0008*mm;//layer D
  G4double AgLayerThickness = 0.229*mm;//layer F
  G4double sourceThickness = AuLayer1Thickness+AuLayer2Thickness+AmLayerThickness+AuLayer3Thickness+AgLayerThickness;

  //mother volume
  G4Tubs* sourceMother = new G4Tubs("sourceMother", 0*mm, 0.5*sourceExtDiameter, 0.5*sourceTotLength, 0.*deg, 360.*deg);
  G4LogicalVolume* sourceLog = new G4LogicalVolume(sourceMother, defaultMat, "sourceMotherLog");
  new G4PVPlacement(0, G4ThreeVector(0.*mm, 0.*mm, 0.*mm), sourceLog, "source", worldLog, false, 0);
  
  //case
  G4Tubs* caseCyl = new G4Tubs("caseCyl", 0.*mm, 0.5*sourceExtDiameter, 0.5*(sourceTotLength-sourceThickness-1.*mm), 0.*deg, 360.*deg);
  G4Tubs* caseTube = new G4Tubs("caseTube", 0.5*coreDiameter, 0.5*sourceExtDiameter, 0.5*(sourceThickness+1.*mm), 0.*deg, 360.*deg);
  G4LogicalVolume* caseCylLog = new G4LogicalVolume(caseCyl, Al, "caseCylLog");
  G4LogicalVolume* caseTubeLog = new G4LogicalVolume(caseTube, Al, "caseCylLog");
  caseCylLog->SetVisAttributes(solidBlue);
  caseTubeLog->SetVisAttributes(solidBlue);
  new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, -0.5*(sourceThickness+1.*mm)),/*shifted of the thickness of the source plus the extra 1*mm, which is multiplied by 0.5 also in the tube part, so the whole volume is centered in the mother volume*/
		    caseCylLog, "sourceCaseCyl", sourceLog, false, 0);
  new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, 0.5*(sourceTotLength-sourceThickness-1.*mm)),
		    caseTubeLog, "sourceCaseTube", sourceLog, false, 0);

  //source core
  G4Tubs* sourceCore = new G4Tubs("sourceCore", 0.*mm, 0.5*coreDiameter, 0.5*sourceThickness, 0.*deg, 360.*deg);
  G4LogicalVolume* sourceCoreLog = new G4LogicalVolume(sourceCore, defaultMat, "AgLayerLog");
  sourceCoreLog->SetVisAttributes(solidGreen);
  new G4PVPlacement(0, G4ThreeVector(0., 0.,
				     0.5*(sourceTotLength-sourceThickness)-1.*mm),/*added at the end of the cylinder and inside the tube*/
		    sourceCoreLog, "sourceCore", sourceLog, false, 0);
  //for positioning the core elements one has to consider that each layer is after the full lenght of the previous one,
  //   and since the G4Tubs is positioned in the middle of his length one has to multiply by 0.5 the thickness
  //   of the layer that one wants to add.
  
  //Au1
  G4Tubs* AuLayer1 = new G4Tubs("AuLayer1", 0.*mm, 0.5*coreDiameter, 0.5*AuLayer1Thickness, 0.*deg, 360.*deg);
  G4LogicalVolume* AuLayer1Log = new G4LogicalVolume(AuLayer1, Au, "AuLayer1Log");
  AuLayer1Log->SetVisAttributes(solidYellow);
  new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m,
				     0.5*sourceThickness-0.5*AuLayer1Thickness), AuLayer1Log, "AuLayer1", sourceCoreLog, false, 0);

  //Au2
  G4Tubs* AuLayer2 = new G4Tubs("AuLayer2", 0.*mm, 0.5*coreDiameter, 0.5*AuLayer2Thickness, 0.*deg, 360.*deg);
  G4LogicalVolume* AuLayer2Log = new G4LogicalVolume(AuLayer2, Au, "AuLayer2Log");
  AuLayer2Log->SetVisAttributes(solidBlue);
  new G4PVPlacement(0,
		    G4ThreeVector(0.*m, 0.*m,
				  0.5*sourceThickness-AuLayer1Thickness-0.5*AuLayer2Thickness),
		    AuLayer1Log, "AuLayer2", sourceCoreLog, false, 0);

  //Am
  G4Tubs* AmLayer = new G4Tubs("AmLayer", 0.*mm, 0.5*coreDiameter, 0.5*AmLayerThickness, 0.*deg, 360.*deg);
  G4LogicalVolume* AmLayerLog = new G4LogicalVolume(AmLayer, Au, "AmLayerLog");
  AmLayerLog->SetVisAttributes(solidYellow);
  new G4PVPlacement(0,
		    G4ThreeVector(0.*m, 0.*m,
				  0.5*sourceThickness-AuLayer1Thickness-AuLayer2Thickness-0.5*AmLayerThickness),
		    AuLayer1Log, "AmLayer", sourceCoreLog, false, 0);

  //Au3
  G4Tubs* AuLayer3 = new G4Tubs("AuLayer3", 0.*mm, 0.5*coreDiameter, 0.5*AuLayer3Thickness, 0.*deg, 360.*deg);
  G4LogicalVolume* AuLayer3Log = new G4LogicalVolume(AuLayer3, Au, "AuLayer3Log");
  AuLayer3Log->SetVisAttributes(solidBlue);
  new G4PVPlacement(0,
		    G4ThreeVector(0.*m, 0.*m,
				  0.5*sourceThickness-AuLayer1Thickness-AuLayer2Thickness
				  -AmLayerThickness-0.5*AuLayer3Thickness),
		    AuLayer1Log, "AuLayer3", sourceCoreLog, false, 0);

  //Ag
  G4Tubs* AgLayer = new G4Tubs("AgLayer", 0.*mm, 0.5*coreDiameter, 0.5*AgLayerThickness, 0.*deg, 360.*deg);
  G4LogicalVolume* AgLayerLog = new G4LogicalVolume(AgLayer, Ag, "AgLayerLog");
  AgLayerLog->SetVisAttributes(solidYellow);
  new G4PVPlacement(0,
		    G4ThreeVector(0.*m, 0.*m,
				  0.5*sourceThickness-AuLayer1Thickness-AuLayer2Thickness
				  -AmLayerThickness-AuLayer3Thickness-0.5*AgLayerThickness),
		    AuLayer1Log, "AgLayer", sourceCoreLog, false, 0);

  return PhysicalWorld;
}
