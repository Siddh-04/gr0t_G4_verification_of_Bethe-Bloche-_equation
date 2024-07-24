#ifndef G4_gr0t_DETECTOR_CONSTRUCTION_H
#define G4_gr0t_DETECTOR_CONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"

namespace G4_gr0t
{
	class DetectorConstruction : public G4VUserDetectorConstruction
	{
	public:
		DetectorConstruction() = default;
		~DetectorConstruction() override = default;

		G4VPhysicalVolume* Construct() override;

		G4LogicalVolume* Getgr0tVolume() const { return fgr0tVolume; };

	private:
		G4LogicalVolume* fgr0tVolume = nullptr;

	};
}


#endif