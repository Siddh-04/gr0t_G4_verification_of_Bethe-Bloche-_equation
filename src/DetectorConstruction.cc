
#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"

namespace G4_gr0t
{
	G4VPhysicalVolume* DetectorConstruction::Construct()
	{
			// Get nist material manager
			G4NistManager* nist = G4NistManager::Instance();

			// world properties
			G4Material* worldMaterial = nist->FindOrBuildMaterial("G4_lH2");
			G4bool checkOverlaps = false;

			G4int worldSizeX = 50*cm;
			G4int worldSizeY = 50*cm;
			G4int worldSizeZ = 50*cm;


			// define worlds
			auto solidWorld = new G4Box("World",
					worldSizeX,                 // default is mm (it seems like)
					worldSizeY,
					worldSizeZ);

			auto logicWorld = new G4LogicalVolume(solidWorld,
					worldMaterial, "World");

			auto physWorld = new G4PVPlacement(nullptr,  // no rotation
					G4ThreeVector(),                           // at (0,0,0)
					logicWorld,                                // its logical volume
					"World",                                   // its name
					nullptr,                                   // its mother  volume
					false,                                     // no boolean operation
					0,                                         // copy number
					checkOverlaps);                            // overlaps checking

			// create envelope
			/*
			G4double env_sizeXY = 20 * cm, env_sizeZ = 30 * cm;
			G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");

			auto solidEnv = new G4Box("Envelope",                    // its name
					0.5 * env_sizeXY, 0.5 * env_sizeXY, 0.5 * env_sizeZ);  // its size

			auto logicEnv = new G4LogicalVolume(solidEnv,  // its solid
					env_mat,                                     // its material
					"Envelope");                                 // its name

			new G4PVPlacement(nullptr,  // no rotation
					G4ThreeVector(),          // at (0,0,0)
					logicEnv,                 // its logical volume
					"Envelope",               // its name
					logicWorld,               // its mother  volume
					false,                    // no boolean operation
					0,                        // copy number
					checkOverlaps);           // overlaps checking

			*/

			// detector made of water material
			G4Material* detectorMaterial = nist->FindOrBuildMaterial("G4_lH2");
			G4double detectorSizeX = worldSizeX ;
			G4double detectorSizeY = worldSizeY ;
			G4double detectorSizeZ = worldSizeY ;
			G4ThreeVector detectorPos = G4ThreeVector(0, 0, 0);

			auto solidDetector = new G4Box("Detector",
					detectorSizeX,
					detectorSizeY,
					detectorSizeZ);

			auto logicDetector = new G4LogicalVolume(solidDetector,
					detectorMaterial,
					"Detector");

			new G4PVPlacement(nullptr,    // rotation
					detectorPos,              // position
					logicDetector,            // its logical volume
					"Detector",               // its name
					logicWorld,               // its mother  volume
					false,                    // boolean operation
					0,                        // copy number
					checkOverlaps);           // overlaps checking


			// set scoring volume
			fgr0tVolume = logicDetector;

			return physWorld;
	}

}
