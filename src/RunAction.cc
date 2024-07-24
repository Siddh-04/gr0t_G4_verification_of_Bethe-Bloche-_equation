
#include "RunAction.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4RootAnalysisManager.hh"



namespace G4_gr0t {
	RunAction::RunAction() {

		// Set up analysis nTuples and output files
		// 
		// access analysis manager
		auto analysisManager = G4AnalysisManager::Instance();

		// set default settings
		analysisManager->SetDefaultFileType("root");
		analysisManager->SetNtupleMerging(true);
		analysisManager->SetVerboseLevel(0);
		analysisManager->SetFileName("zeta");

		// create nTuple to store the absolute energies
		const G4int ntupleId1 = analysisManager->CreateNtuple("Absolute Energies", "abs Energies");
		// The letters D, I, S, F correspond to types
		analysisManager->CreateNtupleDColumn(ntupleId1, "AbsEnergy"); //   id = 0
		analysisManager->FinishNtuple(ntupleId1);

		// create nTuple for the relative energies relaive to the gap
		const G4int ntupleId2 = analysisManager->CreateNtuple("Relative Energies", "rell Energies"); //here gamma energies is the title of the ntuple
		analysisManager->CreateNtupleDColumn(ntupleId2, "RelEnergy");
		analysisManager->FinishNtuple(ntupleId2);

		//create nTuple for the gap energies
		const G4int ntupleId3 = analysisManager->CreateNtuple("Gap Energies", "gap Energies");
		analysisManager->CreateNtupleDColumn(ntupleId3, "GapEnergy");
		analysisManager->FinishNtuple(ntupleId3);
/*
		// creating nTuple of particle energies form using G4Track class
		const G4int ntupleId4 = analysisManager->CreateNtuple("Particle Energies", "Gamma Energies");
		analysisManager->CreateNtupleDColumn(ntupleId4, "ParticleEnergy");
		analysisManager->FinishNtuple(ntupleId4);

		// creating data of initial particle energies
		const G4int ntupleId5 = analysisManager->CreateNtuple("Initial Particle Energies", "Gamma Energies");
		analysisManager->CreateNtupleDColumn(ntupleId5, "InitialParticleEnergy");
		analysisManager->FinishNtuple(ntupleId5);
*/
		// creating nTuple for momentum of particles
		const G4int ntupleId6 = analysisManager->CreateNtuple("Particle Momenta", "Gamma Energies");
		analysisManager->CreateNtupleDColumn(ntupleId6, "ParticleMomentum");
		analysisManager->FinishNtuple(ntupleId6);

		// // creating nTuple for the number of particles
		// const G4int ntupleId7 = analysisManager->CreateNtuple("Number of Particles", "Gamma Energies");
		// analysisManager->CreateNtupleDColumn(ntupleId7, "NumberOfParticles");
		// analysisManager->FinishNtuple(ntupleId7);

		// craeting the nTuple for the dEdx values
		const G4int ntupleId8 = analysisManager->CreateNtuple("dEdx Values", "Gamma Energies");
		analysisManager->CreateNtupleDColumn(ntupleId8, "dEdx");
		analysisManager->FinishNtuple(ntupleId8);
		
		// creating the nTuple for the beta values
		const G4int ntupleId9 = analysisManager->CreateNtuple("Beta Values", "Gamma Energies");
		analysisManager->CreateNtupleDColumn(ntupleId9, "Beta");
		analysisManager->FinishNtuple(ntupleId9);

		
	}

	RunAction::~RunAction() {
	}

	void RunAction::BeginOfRunAction(const G4Run* aRun) {
		// start time
		fTimer.Start();

		auto analysisManager = G4AnalysisManager::Instance();

		analysisManager->OpenFile();
	}

	void RunAction::EndOfRunAction(const G4Run* aRun) {

		auto analysisManager = G4AnalysisManager::Instance();

		// get the mean energies
		// G4double Eabs = analysisManager->GetH1(0)->mean();
    	// G4double Egap = analysisManager->GetH1(1)->mean();
		// print out the mean energies 
		// here Egap is the mean energy of the gap between the peaks
		// and Eabs is the mean energy of the absolute energies

		// write to output file
		analysisManager->Write();
		analysisManager->CloseFile();

		// end time
		fTimer.Stop();

		// print out the time it took
		if (IsMaster()) {
			PrintTime();
		}
	}

	void RunAction::PrintTime() {
		auto time = fTimer.GetRealElapsed();

		G4cout
			<< "Elapsed time: "
			<< time
			<< " Seconds."
			<< G4endl;


	}
}