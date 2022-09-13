// conditional to define the class only once
#ifndef NULATVOXELSENSDET_HH
#define NULATVOXELSENSDET_HH
// Header file for Sensitive Detectors
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
// define the class - note: may no longer be needed
class NuLatVoxelSensitiveDetector : public G4VSensitiveDetector
{
public:
	// Constructor and Destructor
	NuLatVoxelSensitiveDetector(G4String);
	~NuLatVoxelSensitiveDetector();
private:
	// ProcessHits()
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
	// Constant for calculating wavelength from energy
	const G4double HCNM = 1239.841939*eV;
};
// end of conditional to define the class only once
#endif
