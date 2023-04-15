// included user defined header file
#include "NuLatGenerator.hh"
// Constructor
NuLatPrimaryGenerator::NuLatPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
	// define the particle
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "gamma";//"opticalphoton";"geantino";"e-";"e+";
	G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
	// set ion properties for Co-60 decay source
	Z = 27;
	A = 60;
	charge = 0.*eplus;
	energy = 0.*MeV;
	if(particleName=="ion")
	{
		particle = G4IonTable::GetIonTable()->GetIon(Z, A, energy);
	}
	// Place source on +z face of NaI detector. Set initial momentum straight into the NuLat detector for single 1.173 MeV gamma, assuming that the 1.332 MeV triggers the NaI.
	G4ThreeVector pos(0.,0.,-6.25*in-207.5*mm);
	// Initial momentum. Set on random cone into the detector from GeneratePrimaries()
	G4ThreeVector mom(0.,0.,1.);
	// set particle gun properties
	G4double eCo60Lo = 1.173*MeV;
	G4double eCo60Hi = 1.332*MeV;// Assume this will trigger the NaI detector
	G4double eminusEn = 1.0*MeV;
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	if(particle==G4Geantino::Geantino())
	{
		fParticleGun->SetParticleMomentum(energy);
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
	if(particleName == "e-")
	{
		fParticleGun->SetParticleMomentum(eminusEn);
	}
	if(particleName == "e+")
	{
		fParticleGun->SetParticleMomentum(eplusEn);
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
	// if statement sets default generator to Co-60 decay if particle is defined as geantino - deprecated (used for NaI coincidence detector)
	/*if(particle==G4Geantino::Geantino())
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
	}/**/
	// to be truly uniform in theta, must use inverse cosine of random number between 1 and cos(gamma)
	theta = G4UniformRand()*gamma;
	phi = G4UniformRand()*360*deg;
	G4ThreeVector mom(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
	// Use Randomly Generated Momentum Direction
	fParticleGun->SetParticleMomentumDirection(mom);
	// generate vertex
	fParticleGun->GeneratePrimaryVertex(NuLatEvent);
}
