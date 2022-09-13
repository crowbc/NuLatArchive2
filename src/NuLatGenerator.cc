#include "NuLatGenerator.hh"

NuLatPrimaryGenerator::NuLatPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
	// define the particle
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "geantino";	
	G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
	// Place source in center of -z face, and set momentum direction straight into detector
	G4ThreeVector pos(0.,0.,-6.25*in-5*mm);
	G4ThreeVector mom(0.,0.,1.);
	// set particle gun properties
	G4double eCo60Low = 1.173*MeV;
	G4double eCo60Hi = 1.332*MeV;// Assume this will trigger the NaI detector
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	if(particle==G4Geantino::Geantino())
	{
		fParticleGun->SetParticleMomentum(0.*MeV);
	}
	else
	{
		fParticleGun->SetParticleMomentum(eCo60Low);
	}
	fParticleGun->SetParticleDefinition(particle);
}

NuLatPrimaryGenerator::~NuLatPrimaryGenerator()
{
	delete fParticleGun;
}

void NuLatPrimaryGenerator::GeneratePrimaries(G4Event *NuLatEvent)
{
	G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();
	// if statement sets default generator to Co-60 decay if particle is defined as geantino
	if(particle==G4Geantino::Geantino())
	{
		G4int Z = 27;
		G4int A = 60;
		
		G4double charge = 0.*eplus;
		G4double energy = 0.*keV;
		
		G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);
		
		fParticleGun->SetParticleDefinition(ion);
		fParticleGun->SetParticleCharge(charge);
	}
	// generate vertex
	fParticleGun->GeneratePrimaryVertex(NuLatEvent);
}
