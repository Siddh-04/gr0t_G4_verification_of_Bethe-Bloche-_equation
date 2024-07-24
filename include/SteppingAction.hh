#ifndef G4_gr0t_STEPPING_ACTION_H
#define G4_gr0t_STEPPING_ACTION_H 1

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"


namespace G4_gr0t {


	class SteppingAction : public G4UserSteppingAction {
	public:
		SteppingAction();
		~SteppingAction();

		void UserSteppingAction(const G4Step*) override;

	private:
		G4LogicalVolume* fgr0tVolume = nullptr;
	};

}


#endif // !G4_gr0t_STEPPING_ACTION_H
