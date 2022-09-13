// conditional to define the class only once
#ifndef NULATPMTSENSDET_HH
#define NULATPMTSENSDET_HH
// Header file for Sensitive Detectors
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
// define the class
class NuLatPMTSensitiveDetector : public G4VSensitiveDetector
{
public:
	// Constructor and Destructor
	NuLatPMTSensitiveDetector(G4String);
	~NuLatPMTSensitiveDetector();
private:
	// ProcessHits()
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
	// Constant for calculating wavelength from energy
	const G4double HCNM = 1239.841939*eV;
};
// end of conditional to define the class only once
#endif
