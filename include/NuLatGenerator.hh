#ifndef NULATGENERATOR_HH
#define NULATGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Geantino.hh"
#include "G4IonTable.hh"

class NuLatPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
	NuLatPrimaryGenerator();
	~NuLatPrimaryGenerator();
	
	virtual void GeneratePrimaries(G4Event*);
	
private:
	G4ParticleGun* fParticleGun;
	// useful constants
	const G4double in = 25.4*mm;
};

#endif
