#include "DetectorConstruction.hh"
#include "const.hh"

DetectorConstruction::DetectorConstruction(){}
DetectorConstruction::~DetectorConstruction(){}

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name){}
SensitiveDetector::~SensitiveDetector(){}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0hist){
  G4Track *track = aStep->GetTrack();
  //track->SetTrackStatus(fStopAndKill); //to kill a particle after 

  G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
  G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

  G4double eDep = aStep->GetTotalEnergyDeposit();
  
  G4ThreeVector prePos = preStepPoint->GetPosition();
  G4ThreeVector postPos = postStepPoint->GetPosition();
  //getPDG number and keep just alphas

  G4String name =track->GetDefinition()->GetParticleName();
  const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
  G4int copyNo = touchable->GetCopyNumber();
  //  G4int evt = track->GetTrackID();
  G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  auto man = G4AnalysisManager::Instance();
  if(name=="alpha"){
    #ifdef DEBUG
    G4cout << "event number " << evt << G4endl;
    G4cout << "name " << name << G4endl;
    G4cout << "copy number " << copyNo << G4endl;
    G4cout << "Particle position at beginning : " << prePos << G4endl;
    G4cout << "Particle position at end : " << postPos << G4endl;
    #endif
    //the filling must be done with respect to the detector hit
    man->FillNtupleIColumn(0, evt);
    //PRE POSITIONS column: 1 2 3
    man->FillNtupleDColumn(1, prePos[0]);
    man->FillNtupleDColumn(2, prePos[1]);
    man->FillNtupleDColumn(3, prePos[2]);
    //POST POSITIONS column: 4 5 6 
    man->FillNtupleDColumn(4, postPos[0]);
    man->FillNtupleDColumn(5, postPos[1]);
    man->FillNtupleDColumn(6, postPos[2]);

    //energy deposited on detector
    man->FillNtupleDColumn(7, eDep);
  
    //filling with copyNo
    man->FillNtupleIColumn(8, copyNo);
    man->AddNtupleRow(0);
    }

  return true;
}

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
  
  //  G4Material* defaultMat = nist->FindOrBuildMaterial("G4_AIR");//air
  G4Material* Al = nist->FindOrBuildMaterial("G4_Al");
  G4Material* Au = nist->FindOrBuildMaterial("G4_Au");
  G4Material* Am= nist->FindOrBuildMaterial("G4_Am");
  G4Material* Ag = nist->FindOrBuildMaterial("G4_Ag");
  G4Isotope* Am241 = new G4Isotope("Am241", 95, 241, 241.056829*g/mole);
  G4Element* elAm241 = new G4Element("elAm241", "Am-241", 1);
  elAm241->AddIsotope(Am241, 100*perCent);
  G4Material* Americium241 = new G4Material("Americium241", 12 *g/cm3,1);
  Americium241->AddElement(elAm241,1);
#ifndef //Au
  G4Material* TargetMat = new G4Material("TargetMat", 79, 196.96657*g/mole, 19.32 *g/cm3);
#else //Ni
  G4Material* TargetMat = new G4Material("TargetMat", 79, 58.6934*g/mole, 	8.90*g/cm3);
#endif
 
  G4double atomicNumber = 1.;
  G4double massOfMole = 1.008*g/mole;
  G4double density = 1.e-25*g/cm3;
  G4double temperature = 300*kelvin;
  G4double pressure = 3.e-8*bar;
  G4Material* vacuum = new G4Material("interGalactic", atomicNumber, massOfMole, density, kStateGas, temperature, pressure);

  G4Material* defaultMat=vacuum;

  //--------------------------------------------------------
  //world volume--------------------------------------------
  //--------------------------------------------------------
  G4Box* solidWorld = new G4Box("World", world_width,world_width,world_width);
  G4LogicalVolume* worldLog = new G4LogicalVolume(solidWorld, defaultMat, "WorldLog");
  PhysicalWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), worldLog, "physWorld", 0, false, 0, true);
  
  //--------------------------------------------------------
  //source support------------------------------------------
  //--------------------------------------------------------
  //mother volume
  G4Box* support = new G4Box("support", 12.05*mm, 30.*mm, 0.5*totLength);
  G4LogicalVolume* supportLog = new G4LogicalVolume(support, defaultMat, "supportLog");
  new G4PVPlacement(0, G4ThreeVector(0.*mm, 0.*mm, -0.5*totLength), supportLog, "support", worldLog, false, 0);
  
  //--------------------------------------------------------
  //source--------------------------------------------------
  //--------------------------------------------------------

  
  //mother volume
  G4Tubs* sourceMother = new G4Tubs("sourceMother", 0*mm, 0.5*sourceExtDiameter, 0.5*sourceTotLength, 0.*deg, 360.*deg);
  G4LogicalVolume* sourceLog = new G4LogicalVolume(sourceMother, defaultMat, "sourceMotherLog");
  new G4PVPlacement(0, G4ThreeVector(0.*mm, 0.*mm, 0.5*totLength-targetThickness-distTarget-coll1Thickness-distC1-coll2Thickness-distC2-0.5*sourceTotLength), sourceLog, "source", supportLog, false, 0);
  
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
  G4LogicalVolume* sourceCoreLog = new G4LogicalVolume(sourceCore, defaultMat, "sourceCore");
  sourceCoreLog->SetVisAttributes(solidGreen);
  new G4PVPlacement(0, G4ThreeVector(0., 0.,
				     0.5*(sourceTotLength-sourceThickness)-1.*mm),//added at the end of the cylinder and inside the tube
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
  G4LogicalVolume* AmLayerLog = new G4LogicalVolume(AmLayer, Americium241, "AmLayerLog");
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
  new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, 0.5*sourceThickness-AuLayer1Thickness-AuLayer2Thickness-AmLayerThickness-AuLayer3Thickness-0.5*AgLayerThickness),
		    AgLayerLog, "AgLayer", sourceCoreLog, false, 0);

  //Collimator 1
  G4VSolid* suppColl1 = new G4Box("SupportCollimator1", 0.5*suppColl1X, 0.5*suppColl1Y, 0.5*coll1Thickness);
  G4VSolid* holeColl1 = new G4Box("HoleCollimator2", 0.5*collH1X, 0.5*collH1Y, coll1Thickness);
  G4VSolid* Collimator1 = new G4SubtractionSolid("SupportCollimator1-HoleCollimator1", suppColl1, holeColl1, 0, G4ThreeVector(0.*mm,-0.5*suppColl1Y+0.5*collH1Y+2.60*mm,0.*mm));
  G4LogicalVolume* Coll1Log = new G4LogicalVolume(Collimator1, Al, "Coll1Log");
  Coll1Log->SetVisAttributes(solidSilver);
  new G4PVPlacement(0, G4ThreeVector(0, 0.5*sourceExtDiameter, 0.5*totLength-targetThickness-distTarget-0.5*coll1Thickness),
		    Coll1Log, "Collimator1", supportLog, false, 0);
  
  //Collimator 2
  G4VSolid* suppColl2 = new G4Box("SupportCollimator2", 0.5*suppColl2X, 0.5*suppColl2Y, 0.5*coll2Thickness);
  G4VSolid* holeColl2 = new G4Box("HoleCollimator2", 0.5*collH2X, 0.5*collH2Y, coll2Thickness);
  G4VSolid* Collimator2 = new G4SubtractionSolid("SupportCollimator2-HoleCollimator2", suppColl2, holeColl2, 0, G4ThreeVector(0.*mm,-0.5*suppColl2Y+0.5*collH2Y+2.55*mm,0.*mm)); 
  G4LogicalVolume* Coll2Log = new G4LogicalVolume(Collimator2, Al, "Coll2Log");
  Coll2Log->SetVisAttributes(solidSilver);
  new G4PVPlacement(0, G4ThreeVector(0,0.5*sourceExtDiameter,0.5*totLength-targetThickness-distTarget-coll1Thickness-distC1-0.5*coll2Thickness),
		    Coll2Log, "Collimator2", supportLog, false, 0);

#ifndef DEBUG
  //Target
  G4Tubs* Target = new G4Tubs("Target", 0.*mm, 0.5*targetDiameter, 0.5*targetThickness, 0.*deg, 360.*deg);
  G4LogicalVolume* TargetLog = new G4LogicalVolume(Target, TargetMat, "TargetLog");
  TargetLog->SetVisAttributes(solidYellow);
  new G4PVPlacement(0, G4ThreeVector(0,0,0.5*totLength-0.5*targetThickness),
		    TargetLog, "Target", supportLog, false, 0);
#endif

  //--------------------------------------------------------
  //Detector------------------------------------------------
  //--------------------------------------------------------

  //D2
  /*G4Box* PostDet = new G4Box("Post-Detector", 0.5 * 40* mm, 0.5* 40* mm, 0.5 *4*mm); //frapasco: to be changed to non hard-coded version*/
  G4VSolid* PostDet = new G4Sphere("SphereDetPost", 0.5*77.70*mm, 0.5*80*mm, 0*deg,360*deg, 0*deg, 150*deg);
  PostDetLog = new G4LogicalVolume(PostDet, defaultMat, "PostDetLog");
    
  new G4PVPlacement(0, G4ThreeVector(0., 0., 0.*mm), PostDetLog, "phys_PostDet", worldLog, false, 1, true);
  

  return PhysicalWorld;
}

//frapasco: remove inline in the definition (line33 in .hh)

void DetectorConstruction::ConstructSDandField()
{
  //SensitiveDetector *sensPreDet = new SensitiveDetector("sensitivePreDet");
  G4String name = "sensitivePostDet";
  SensitiveDetector *sensPostDet = new SensitiveDetector("sensitivePostDet");
  //PreDetLog->SetSensitiveDetector(sensPreDet);
  PostDetLog->SetSensitiveDetector(sensPostDet);

}

