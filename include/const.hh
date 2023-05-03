#ifndef CONSTANTS
#define CONSTANTS

//--------------------------------------------------------
//parameters----------------------------------------------
//--------------------------------------------------------

//world volume
const G4double world_width = 15*cm;

//parameters that describe the source geometry
const G4double sourceExtDiameter = 12.7*mm;
const G4double coreDiameter = 7.*mm;
const G4double sourceTotLength = 79.*mm;
const G4double AuLayer1Thickness = 0.00051*mm;//layer A
const G4double AuLayer2Thickness = 0.0010*mm;//layer B
const G4double AmLayerThickness = 0.00051*mm;//layer C
const G4double AuLayer3Thickness = 0.0008*mm;//layer D
const G4double AgLayerThickness = 0.229*mm;//layer F

//parameters of collimators and target geometry
//C1
const G4double suppColl1X = 13.05*mm;
const G4double suppColl1Y = 25.05*mm;
const G4double collH1X = 4.05*mm;
const G4double collH1Y = 7.05*mm;
const G4double coll1Thickness = 1.55*mm;
const G4double distC1 = 16.75*mm;
//C2
const G4double suppColl2X = 13.05*mm;
const G4double suppColl2Y = 25.00*mm;
const G4double collH2X = 4.10*mm;
const G4double collH2Y = 7.05*mm;
const G4double coll2Thickness = 1.60*mm;
const G4double distC2 = 0.*mm;//it is 0 since C2 and the source are in contact
//target
const G4double targetDiameter = 25. *mm;
const G4double targetThickness = 1.68219e-6 *mm;
const G4double distTarget = 1.10*mm;

//totals
const G4double sourceThickness = AuLayer1Thickness+AuLayer2Thickness+AmLayerThickness+AuLayer3Thickness+AgLayerThickness;
const G4double totLength = sourceTotLength+distC2+coll2Thickness+distC1+coll1Thickness+distTarget+targetThickness;
//beginning of the americium layer starting from the side closer to the target
const G4double americiumZ = -(targetThickness+distTarget+coll1Thickness+distC1+coll2Thickness+distC2+AuLayer1Thickness+AuLayer2Thickness);
const G4double sourceZ = -(targetThickness+distTarget+coll1Thickness+distC1+coll2Thickness+distC2);

#endif
