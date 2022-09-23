// included user defined header file
#include "NuLatGenerator.hh"
// Constructor
NuLatPrimaryGenerator::NuLatPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
	// define the particle
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "geantino";//"gamma";//"ion";
	G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
	// set ion properties for Co-60 decay source
	Z = 27;
	A = 60;
	charge = 0.*eplus;
	energy = 0.*keV;
	if(particleName=="ion")
	{
		particle = G4IonTable::GetIonTable()->GetIon(Z, A, energy);
	}
	// Place source in center of -z face, and set momentum direction straight into detector
	G4ThreeVector pos(0.,0.,-6.25*in-7.5*mm);
	G4ThreeVector mom(0.,0.,-1.);
	// set particle gun properties
	G4double eCo60Lo = 1.173*MeV;
	G4double eCo60Hi = 1.332*MeV;// Assume this will trigger the NaI detector
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	if(particle==G4Geantino::Geantino())
	{
		fParticleGun->SetParticleMomentum(0.*MeV);
	}
	else
	{
		fParticleGun->SetParticleMomentum(eCo60Lo);
	}
	fParticleGun->SetParticleDefinition(particle);
}
// Destructor
NuLatPrimaryGenerator::~NuLatPrimaryGenerator()
{
	delete fParticleGun;
}
// GeneratePrimaries()
void NuLatPrimaryGenerator::GeneratePrimaries(G4Event *NuLatEvent)
{
	G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();
	// if statement sets default generator to Co-60 decay if particle is defined as geantino
	if(particle==G4Geantino::Geantino())
	{
		// ion properties
		Z = 27;
		A = 60;
		charge = 0.*eplus;
		energy = 0.*keV;
		// define ion
		G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);
		// put ion in particle gun
		fParticleGun->SetParticleDefinition(ion);
		fParticleGun->SetParticleCharge(charge);
	}
	// generate vertex
	fParticleGun->GeneratePrimaryVertex(NuLatEvent);
}
