// conditional to define the class only once
#ifndef NULATVOXELSENSDET_HH
#define NULATVOXELSENSDET_HH
// Header file for Sensitive Detectors
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4TrackingManager.hh"
#include "G4EventManager.hh"
// included user defined header files
#include "NuLatVoxelHit.hh"
// write the class
class NuLatVoxelSensitiveDetector : public G4VSensitiveDetector
{
public:
	// Constructor and Destructor
	NuLatVoxelSensitiveDetector(G4String);
	~NuLatVoxelSensitiveDetector();
	//virtual void Initialize(G4HCofThisEvent* HCE);
	//virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
	virtual G4int ParticleNameToIDNumber(G4Step* step);
private:
	// ProcessHits()
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
	// Constant for calculating wavelength in nm from energy
	const G4double HCNM = 1239.841939*eV;
	// Hit Collection object
	NuLatVoxelHitsCollection *voxelHitCollection;
	// ID variaible
	G4int voxelHitCollectionID;
};
// end of conditional to define the class only once
#endif
