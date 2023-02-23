// included user defined header file
#include "NuLatGenerator.hh"
// Constructor
NuLatPrimaryGenerator::NuLatPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
	// define the particle
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "gamma";//"opticalphoton";"geantino";
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
	// Place source on +x side of NaI detector 1 inch back from its +z face, and set momentum direction straight into NuLat detector
	G4ThreeVector pos(2.625*in+5*mm,0.,-7.25*in-207.5*mm);
	theta = G4UniformRand()*gamma;
	phi = (G4UniformRand()*120-60)*deg;// fully parameterized, phi = (G4UniformRand()*(180-alpha)-beta)*deg, less some tolerance to make sure the 1.332 doesn't miss the NaI
	// changed for random initial direction in 20-degree cone in +z, +/- 60 degrees in +x only
	G4ThreeVector mom(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
	// set particle gun properties
	G4double eCo60Lo = 1.173*MeV;
	G4double eCo60Hi = 1.332*MeV;// Assume this will trigger the NaI detector
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	if(particle==G4Geantino::Geantino())
	{
		fParticleGun->SetParticleMomentum(0.*MeV);
	}
	if(particleName=="gamma")
	{
		fParticleGun->SetParticleMomentum(eCo60Lo);
	}
	fParticleGun->SetParticleDefinition(particle);
	if(particleName=="ion")
	{
		fParticleGun->SetParticleMomentum(0.*MeV);
		fParticleGun->SetParticleCharge(charge);
	}
	if(particleName=="opticalphoton")
	{
		fParticleGun->SetParticleMomentum(2.95*eV);
	}
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
