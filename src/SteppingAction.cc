
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

#include "G4UnitsTable.hh"

#include "DetectorConstruction.hh"
// getting the plot of dE/dx vs beta
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4EmCalculator.hh"


namespace G4_gr0t {
	SteppingAction::SteppingAction() {
	}

	SteppingAction::~SteppingAction() {
	}

	void SteppingAction::UserSteppingAction(const G4Step* step) {
    // Get the track associated with this step
    const G4Track* track = step->GetTrack();

    // Get the particle definition (e.g., electron, proton, etc.)
    const G4ParticleDefinition* particleDef = track->GetParticleDefinition();

    // Get the kinetic energy of the particle at this step
    G4double kineticEnergy = track->GetKineticEnergy();

    // // Calculate the energy loss (dE/dx) using the ComputeDEDX method
    // G4double dEdx = G4EmCalculator::ComputeDEDX(kineticEnergy,
	// 														particleDef,
	// 														step->GetPreStepPoint()->GetMaterial());

    // // Print the result (you can modify this as needed)
    // G4cout << "Particle: " << particleDef->GetParticleName()
    //        << " Kinetic Energy: " << kineticEnergy / MeV << " MeV"
    //        << " dE/dx: " << dEdx / (MeV / mm) << " MeV/mm"
    //        << G4endl;
	if (!fgr0tVolume) {
			const auto detConstruction = static_cast<const DetectorConstruction*>(
				G4RunManager::GetRunManager()->GetUserDetectorConstruction());
			fgr0tVolume = detConstruction->Getgr0tVolume();
		}

	G4LogicalVolume* currentVolume =
			step->GetPreStepPoint()->GetTouchableHandle()
			->GetVolume()->GetLogicalVolume();
		

		// set nTuple id's for analysis
		G4int absNTupleID = 0;
		G4int relNTupleID = 1;
		G4int gapNTupleID = 2;
		G4int momntumNTupleID = 3;
		G4int dEdxnTuple = 4;
		G4int betaNTuple = 5;
		// G4int 


		// get electron energy for recording relative energies
		G4double electronEnergy = step->GetPreStepPoint()->GetKineticEnergy();


		// create a list of all secondary particles created in this step
		const std::vector<const G4Track*>* secondaries
			= step->GetSecondaryInCurrentStep();

		
		for (int i = 0; i < secondaries->size(); i++) {

			const G4Track* track = (*secondaries)[i];

			G4String particleName = track->GetParticleDefinition()->GetParticleName();

			
			if (particleName == "e-") {
				G4double energy = track->GetKineticEnergy();

				// record absolute energy 
				auto analysisManager = G4AnalysisManager::Instance();
				analysisManager->FillNtupleDColumn(absNTupleID, 0, energy);
				analysisManager->AddNtupleRow(absNTupleID);

				// record relative energy
				G4double relEnergy = energy / electronEnergy;
				analysisManager->FillNtupleDColumn(relNTupleID, 0, relEnergy);
				analysisManager->AddNtupleRow(relNTupleID);

				// record gap energy
				G4double gapEnergy = energy - electronEnergy;

				analysisManager->FillNtupleDColumn(gapNTupleID, 0, gapEnergy);
				analysisManager->AddNtupleRow(gapNTupleID);

				// record momentum
				G4double momentum = track->GetMomentum().mag();

				analysisManager->FillNtupleDColumn(momntumNTupleID, 0, momentum);
				analysisManager->AddNtupleRow(momntumNTupleID);

				// record dEdx
				G4double dEdx = step->GetTotalEnergyDeposit() / 0.5;
				analysisManager->FillNtupleDColumn(dEdxnTuple, 0, dEdx);
				analysisManager->AddNtupleRow(dEdxnTuple);

				// defining beta = momentum/Mass*speed_of_light
				G4double beta = momentum / (track->GetParticleDefinition()->GetPDGMass() * c_light);
				analysisManager->FillNtupleDColumn(betaNTuple, 0, beta);
				analysisManager->AddNtupleRow(betaNTuple);




			}

			
		}


	}
	
}