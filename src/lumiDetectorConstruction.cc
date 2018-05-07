#include "lumiDetectorConstruction.hh"
#include "lumiDetectorMessenger.hh"
#include "lumiDetectorSD.hh"

#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSFlatSurfaceCurrent.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4GDMLParser.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "CLHEP/Units/SystemOfUnits.h"

lumiDetectorConstruction::lumiDetectorConstruction()
  :G4VUserDetectorConstruction(){
  detectorMessenger = new lumiDetectorMessenger(this);
}

lumiDetectorConstruction::~lumiDetectorConstruction(){
  delete detectorMessenger;
}

G4VPhysicalVolume* lumiDetectorConstruction::Construct(){
  gdmlParser.SetOverlapCheck(true);
  G4cout<< gdml_filename << " is used ." <<G4endl;
  gdmlParser.Read(gdml_filename);

  G4VPhysicalVolume* world_PV = gdmlParser.GetWorldVolume();


  //  Visualization
  G4VisAttributes* motherVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  motherVisAtt->SetVisibility(true);
  motherVisAtt->SetForceWireframe(true);
  world_PV->GetLogicalVolume()->SetVisAttributes(motherVisAtt);

  G4VisAttributes* VacVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  VacVisAtt->SetVisibility(true);
  VacVisAtt->SetForceWireframe(true);
  G4VisAttributes* CuVisAtt = new G4VisAttributes(G4Colour(1.0,0.5,0.1));
  CuVisAtt->SetVisibility(true);
  CuVisAtt->SetForceSolid(true);
  G4VisAttributes* SSVisAtt = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
  SSVisAtt->SetVisibility(true);
  SSVisAtt->SetForceSolid(true);
  G4VisAttributes* AlVisAtt = new G4VisAttributes(G4Colour(0.4,0.6,0.4));
  AlVisAtt->SetVisibility(true);
  AlVisAtt->SetForceWireframe(true);
  G4VisAttributes* QtzVisAtt = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
  QtzVisAtt->SetVisibility(true);
  QtzVisAtt->SetForceSolid(true);
  G4VisAttributes* FeVisAtt = new G4VisAttributes(G4Colour(0.6,0.7,0.8));
  FeVisAtt->SetVisibility(true);
  FeVisAtt->SetForceSolid(true);
  G4VisAttributes* CW70VisAtt= new G4VisAttributes(G4Colour(0.7,0.7,0.9));
  CW70VisAtt->SetVisibility(true);
  CW70VisAtt->SetForceSolid(true);

  G4VisAttributes* visAtt[7]={VacVisAtt,CuVisAtt,SSVisAtt,AlVisAtt,QtzVisAtt,FeVisAtt,CW70VisAtt};
  G4String mat_name[7]={"Vacuum","Copper","StainlessSteel","Aluminum","Quartz","Iron","matCW70"};
  G4int nMat =7;
  G4LogicalVolume* daughter_logic;
  G4LogicalVolume* daughter2_logic;

  
  for(int iVol=0; iVol<world_PV->GetLogicalVolume()->GetNoDaughters();iVol++){
    
    daughter_logic = world_PV->GetLogicalVolume()->GetDaughter(iVol)->GetLogicalVolume();
    
    for(int imat =0; imat<nMat;imat++){
      if(daughter_logic->GetMaterial()->GetName().compare(mat_name[imat])==0){
	daughter_logic->SetVisAttributes(visAtt[imat]);	
      }
    }
    
    for(int jVol=0;jVol<daughter_logic->GetNoDaughters();jVol++){
      daughter2_logic = daughter_logic->GetDaughter(jVol)->GetLogicalVolume();
      for(int imat =0; imat<nMat;imat++){
	if(daughter2_logic->GetMaterial()->GetName().compare(mat_name[imat])==0){
	  daughter2_logic->SetVisAttributes(visAtt[imat]);	
	}
      }
    }
  }


  return world_PV;
}

G4VPhysicalVolume* lumiDetectorConstruction::ConstructDetector(){

  G4NistManager* nistManager = G4NistManager::Instance();
  
  // World Volume
  G4double world_sizeXY = 1*m;
  G4double world_sizeZ = 100*cm;
  
  G4Material *air = nistManager->FindOrBuildMaterial("G4_AIR");
  G4double density = 1.01*g/mole;
  G4double pressure = 3.0e-18*pascal;
  G4double temperature = 300*kelvin;
  G4Material *vacuum = new G4Material("Vacuum",density,air,kStateGas,temperature,pressure);

  G4Box *world_Solid = new G4Box("World",
				 0.5*world_sizeXY,0.5*world_sizeXY,0.5*world_sizeZ);
  G4LogicalVolume *world_LV = new G4LogicalVolume(world_Solid,air,"World_LV");

  G4bool checkOverlaps = true;
  G4VPhysicalVolume *world_PV = new G4PVPlacement(0, // no rotation
						  G4ThreeVector(0.,0.,0.), // at (0.0.0)
						  world_LV, // logic Volume
						  "World_PV", //its name
						  0, // its mother volume
						  false,// no boolean operation
						  0, // copy number
						  checkOverlaps);


  //Forward Scattering Luminosity Detector at Downstream
  G4double lumi_thickness = 10*cm;
  G4double lumi_radius = 5*cm;
  G4double downstream_backward = 10*cm;
  G4Material *lumi_material = nistManager->FindOrBuildMaterial("G4_Pb"); // Just leave it now
  G4Tubs *lumi_Solid = new G4Tubs("Lumi_Solid",0.0,lumi_radius,0.5*lumi_thickness,0.*deg,360.*deg);
  G4LogicalVolume *lumi_LV = new G4LogicalVolume(lumi_Solid,lumi_material,"Lumi_LV");
  G4VPhysicalVolume *lumi_PV = new G4PVPlacement(0,
  						 G4ThreeVector(0.,0.
  							       ,0.5*world_sizeZ-downstream_backward),
  						 lumi_LV,
  						 "lumi_PV",
  						 world_LV,
  						 false,
  						 0,
  						 checkOverlaps);

  detector_logic = lumi_LV;
  // Small Angle Monitors
  // Under construction
  //
  // G4double sam_quartz_height = 1.3*cm;
  // G4double sam_quartz_width = 2.0*cm;
  // G4double sam_quartz_length = 3.0*cm;
  // G4double sam_z_pos = 567.765*cm;
  // G4ThreeVector *pos_rel_quartz_center = new G4ThreeVector(0.0,sam_quartz_mid_dist,sam_zpos);
  // G4Box *sam_quartz_box_solid = new G4Box("sam_quartz_box_solid",sam_quartz_width,sam_quartz_height,sam_quartz_length);
  // G4Material *quartz = new G4Material("Quartz",density=2.648*g/cm3,nComponents=2);
  // G4Material *Si = nistManager->FindOrBuildMaterial("G4_Si");
  // G4Materiall *O = nistManager->FindOrBuildMaterial("G4_O");
  // quartz->AddMaterial(Si,fractionmass=33.0*percent);
  // quartz->AddMaterial(0,fractionmass=67.0*percent);
  // G4LogicalVolume *sam_quartz_logic = new G4LogicalVolume(sam_quartz_box_solid,quartz,"sam_quartz_lv");
  

  
  
  // Target 
  G4double target_thickness = 1*cm;
  G4double target_radius = 5*cm;
  G4Material *target_material = nistManager->FindOrBuildMaterial("G4_Al");
  G4Tubs *target_Solid = new G4Tubs("Target_Solid",
  				    0.,target_radius,
  				    0.5*target_thickness,0.*deg,360.*deg);
  G4LogicalVolume *target_LV = new G4LogicalVolume(target_Solid,target_material,"target_LV");
  G4VPhysicalVolume *target_PV = new G4PVPlacement(0,
  						   G4ThreeVector(0.,0.,0.),
  						   target_LV,
  						   "target_PV",
  						   world_LV,
  						   false,
  						   0,
  						   checkOverlaps);

  
  G4cout << "Return World_PV" << G4endl;
  return world_PV;
}

void lumiDetectorConstruction::ConstructSDandField(){

  const G4GDMLAuxMapType* auxmap = gdmlParser.GetAuxMap();
  
  G4SDManager *sdManager = G4SDManager::GetSDMpointer();
  sdManager->SetVerboseLevel(1);
  lumiDetectorSD* samDetector = new lumiDetectorSD("SAM");
  sdManager->AddNewDetector(samDetector);
  
  char detector_name[200];
  G4int i=0;
  for(G4GDMLAuxMapType::const_iterator
	iter = auxmap->begin();
      iter !=auxmap->end(); iter++){

    G4LogicalVolume* mylogic = (*iter).first;
    for(G4GDMLAuxListType::const_iterator
	  vit = (*iter).second.begin();
	vit!=(*iter).second.end();vit++){
      if((*vit).type =="SensDet"){
	//	if((*vit).value  == "SAM")
	mylogic->SetSensitiveDetector(samDetector);

      }
    }
  }

}

void lumiDetectorConstruction::SetGDML(const G4String& filename){
  gdml_filename = filename;
}
  
