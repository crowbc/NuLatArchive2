#ifndef NULATGENERATOR_HH
#define NULATGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Geantino.hh"
#include "G4IonTable.hh"
#include "G4RunManager.hh"

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
	// constant for cone geometry, equal to 1st quadrant branch of tan^-1(158.8mm/207.5mm)
	const G4double gamma = 37.4*deg;
	// variables for particle properties
	G4double charge, energy;
	G4double eplusEn = 2.0*MeV;// minimum (roughly) for IBD positron
	G4int Z, A;
	// variables for cone geometry - alpha = 2*sin^(-1)(d*sin(gamma)/5.25*in), beta = 90*deg-alpha/2
	G4double theta, phi;
	G4double d = 1*in;
};

#endif
