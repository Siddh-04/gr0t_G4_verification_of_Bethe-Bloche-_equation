#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "Randomize.hh"

#include "G4UnitsTable.hh"


namespace G4_gr0t
{
	PrimaryGeneratorAction::PrimaryGeneratorAction() {
		// set up particle gun
		G4int nParticles = 1;
		fParticleGun = new G4ParticleGun(nParticles);

		// define particle properties
		const G4String& particleName = "e-";


		// Find the particle (e-) in the G4Particle table
		G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
		G4ParticleDefinition* particle
			= particleTable->FindParticle(particleName);

		// Set the particle type to the particle gun
		fParticleGun->SetParticleDefinition(particle);

		// set the particle's direction:
		G4ThreeVector momentumDirection = G4ThreeVector(0, 0, 1);
		fParticleGun->SetParticleMomentumDirection(momentumDirection);

		// (test) hardcode the energy and we'll change it in mac files
		G4double energy = 100 * MeV;
		fParticleGun->SetParticleEnergy(energy);

	}

	PrimaryGeneratorAction::~PrimaryGeneratorAction() {
		delete fParticleGun;
	}

	void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
	{
		// Randomize x and y starting point within a 1 mm diameter
		G4double radius = .0 * mm;

		// generate random x and y positions within that radius
		double x, y;

		// to avoid using slow methods like sin and cos,
		// we generate random values in a square and regect the ones
		// outside of a circle.
		do {
			x =radius;
			y = radius;
		} while (x * x + y * y > radius * radius);

		G4ThreeVector position = G4ThreeVector(x, y, -50 * cm); //defining the position of particle gun in the world volume
		// basically particle gun is placed at the origin of the world volume and that -5
		fParticleGun->SetParticlePosition(position);

		// satisfy "generate primaries" here.
		fParticleGun->GeneratePrimaryVertex(event);
	}
}
