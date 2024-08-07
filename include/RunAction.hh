#ifndef G4_gr0t_RUN_ACTION_HH
#define G4_gr0t_RUN_ACTION_HH

#include "G4UserRunAction.hh"

#include "G4AnalysisManager.hh"

// timing the run
#include "G4Timer.hh"



namespace G4_gr0t {

	class HitsCollection;

	class RunAction : public G4UserRunAction {
	public:
		RunAction();
		~RunAction();

		void BeginOfRunAction(const G4Run* aRun) override;
		void EndOfRunAction(const G4Run* aRun) override;

	private:

		G4Timer fTimer;

		void PrintTime();

	};


}

#endif // !G4_gr0t_RUN_ACTION_HH
