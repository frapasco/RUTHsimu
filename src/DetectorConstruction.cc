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

  G4VisAttributes* solidSilver = new G4VisAttributes(G4Colour(192/255.,192/255.,192/255.));
  solidSilver->SetVisibility(true);
  solidSilver->SetForceSolid(TRUE);

  
  //--------------------------------------------------------
  //materials-----------------------------------------------
  //--------------------------------------------------------
  G4NistManager* nist = G4NistManager::Instance();
  
  G4Material* defaultMat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* Al = nist->FindOrBuildMaterial("G4_Al");
  G4Material* Au = nist->FindOrBuildMaterial("G4_Au");
  G4Material* Am = nist->FindOrBuildMaterial("G4_Am");//frapasco->to be modified with the correct isotope, for simplicity let's approx Am+Au layer to just Am since we don't have the proportions of the alloy
  G4Material* Ag = nist->FindOrBuildMaterial("G4_Ag");
  G4Isotope* Am241 = new G4Isotope("Am241", 95, 241, 241.056829*g/mole); // atomic number, number of nucleons, mass of mole
  G4Element* elAm241 = new G4Element("elAm241", "Am-241", 1); //name, symbol, number of isotopes
  elAm241->AddIsotope(Am241, 100*perCent); //name, abundance
  G4Material* Americio241 = new G4Material("Americio241", 12 *g/cm3,1);
  Americio241->AddElement(elAm241,1);
  G4Material* AuTarget = new G4Material("AuTarget", 79, 196.96657*g/mole, 325.e-6 *g/cm3);

  //vacuum da modificare
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
  //parameters of collimators and target geometry
  G4double coll1X = 4 *mm;
  G4double coll1Y = 7 *mm;
  G4double coll2X = 4 *mm;
  G4double coll2Y = 7 *mm;
  G4double targetDiameter = 25. *mm;
  G4double targetThickness = 0.5 *mm;

  //mother volume
  G4Tubs* sourceMother = new G4Tubs("sourceMother", 0*mm, 0.5*sourceExtDiameter, 0.5*sourceTotLength, 0.*deg, 360.*deg);
  G4LogicalVolume* sourceLog = new G4LogicalVolume(sourceMother, defaultMat, "sourceMotherLog");
  new G4PVPlacement(0, G4ThreeVector(0.*mm, 0.*mm, 0.*mm), sourceLog, "source", worldLog, false, 0);//frapasco->positioning of the full source
  
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
  new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, 0.5*sourceThickness-0.5*AuLayer1Thickness), 
              AuLayer1Log, "AuLayer1", sourceCoreLog, false, 0);

  //Au2
  G4Tubs* AuLayer2 = new G4Tubs("AuLayer2", 0.*mm, 0.5*coreDiameter, 0.5*AuLayer2Thickness, 0.*deg, 360.*deg);
  G4LogicalVolume* AuLayer2Log = new G4LogicalVolume(AuLayer2, Au, "AuLayer2Log");
  AuLayer2Log->SetVisAttributes(solidYellow);
  new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, 0.5*sourceThickness-AuLayer1Thickness-0.5*AuLayer2Thickness), 
              AuLayer2Log, "AuLayer2", sourceCoreLog, false, 0);

  //Am
  G4Tubs* AmLayer = new G4Tubs("AmLayer", 0.*mm, 0.5*coreDiameter, 0.5*AmLayerThickness, 0.*deg, 360.*deg);
  G4LogicalVolume* AmLayerLog = new G4LogicalVolume(AmLayer, Americio241, "AmLayerLog");
  AmLayerLog->SetVisAttributes(solidSilver);
  new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, 0.5*sourceThickness-AuLayer1Thickness-AuLayer2Thickness-0.5*AmLayerThickness),
		          AmLayerLog, "AmLayer", sourceCoreLog, false, 0);

  //Au3
  G4Tubs* AuLayer3 = new G4Tubs("AuLayer3", 0.*mm, 0.5*coreDiameter, 0.5*AuLayer3Thickness, 0.*deg, 360.*deg);
  G4LogicalVolume* AuLayer3Log = new G4LogicalVolume(AuLayer3, Au, "AuLayer3Log");
  AuLayer3Log->SetVisAttributes(solidYellow);
  new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, 0.5*sourceThickness-AuLayer1Thickness-AuLayer2Thickness-AmLayerThickness-0.5*AuLayer3Thickness),
		          AuLayer3Log, "AuLayer3", sourceCoreLog, false, 0);

  //Ag
  G4Tubs* AgLayer = new G4Tubs("AgLayer", 0.*mm, 0.5*coreDiameter, 0.5*AgLayerThickness, 0.*deg, 360.*deg);
  G4LogicalVolume* AgLayerLog = new G4LogicalVolume(AgLayer, Ag, "AgLayerLog");
  AgLayerLog->SetVisAttributes(solidSilver);
  new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, 1*sourceThickness-AuLayer1Thickness-AuLayer2Thickness-AmLayerThickness-AuLayer3Thickness-0.5*AgLayerThickness),
		          AgLayerLog, "AgLayer", sourceCoreLog, false, 0);

  //Collimator1
  G4VSolid* suppColl1 = new G4Box("SupportCollimator1", 10*mm, 10*mm, 1*mm);
  G4VSolid* holeColl1 = new G4Box("HoleCollimator2", 0.5*coll1X, 0.5*coll1Y, 1*mm);
  G4VSolid* Collimator1 = new G4SubtractionSolid("SupportCollimator1-HoleCollimator1", suppColl1, holeColl1, 0, G4ThreeVector(0.,0.,0.)); //l4rnone->non sono sicura del threevector
  G4LogicalVolume* Coll1Log = new G4LogicalVolume(Collimator1, Al, "Coll1Log");
  Coll1Log->SetVisAttributes(solidSilver); //non capisco perchè colora anche il buco
  new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, 1.1*sourceThickness-AuLayer1Thickness-AuLayer2Thickness-AmLayerThickness-AuLayer3Thickness-0.5*AgLayerThickness+45*mm),
		          Coll1Log, "Collimator1", sourceCoreLog, false, 0); //da cambiare G4ThreeVector
  
  //Collimator2
  G4VSolid* suppColl2 = new G4Box("SupportCollimator2", 10*mm, 10*mm, 1*mm);
  G4VSolid* holeColl2 = new G4Box("HoleCollimator2", 0.5*coll2X, 0.5*coll2Y, 1*mm);
  G4VSolid* Collimator2 = new G4SubtractionSolid("SupportCollimator2-HoleCollimator2", suppColl2, holeColl2, 0, G4ThreeVector(0.,0.,0.)); 
  G4LogicalVolume* Coll2Log = new G4LogicalVolume(Collimator2, Al, "Coll2Log");
  Coll2Log->SetVisAttributes(solidSilver);
  new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, 0.5*sourceThickness-AuLayer1Thickness-AuLayer2Thickness-AmLayerThickness-AuLayer3Thickness-0.5*AgLayerThickness+16*mm),
		          Coll2Log, "Collimator2", sourceCoreLog, false, 0); //da cambiare G4ThreeVector
  
  //Target
  G4Tubs* Target = new G4Tubs("Target", 0.*mm, 0.5*targetDiameter, 0.5*targetThickness, 0.*deg, 360.*deg);
  G4LogicalVolume* TargetLog = new G4LogicalVolume(Target, AuTarget, "TargetLog");
  TargetLog->SetVisAttributes(solidYellow);
  new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, 0.5*sourceThickness-AuLayer1Thickness-AuLayer2Thickness-AmLayerThickness-AuLayer3Thickness-0.5*AgLayerThickness+77*mm),
		          TargetLog, "Target", sourceCoreLog, false, 0); //da cambiare G4ThreeVector

  return PhysicalWorld;
}
