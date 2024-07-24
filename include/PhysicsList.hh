#ifndef G4_gr0t_PHYSICS_LIST_H
#define G4_gr0t_PHYSICS_LIST_H 1

#include "G4VModularPhysicsList.hh"


namespace G4_gr0t
{
	class PhysicsList : public G4VModularPhysicsList
	{
	public:
		PhysicsList();
		virtual ~PhysicsList() override = default;

		// Mandatory methods to override;
		virtual void ConstructParticle() override;
		virtual void ConstructProcess() override;

	};
}

#endif