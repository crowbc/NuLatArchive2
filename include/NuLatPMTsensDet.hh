// conditional to define the class only once
#ifndef NULATPMTSENSDET_HH
#define NULATPMTSENSDET_HH
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
// User defined header files
#include "NuLatPMTHit.hh"
// define the class
class NuLatPMTSensitiveDetector : public G4VSensitiveDetector
{
public:
	// Constructor and Destructor
	NuLatPMTSensitiveDetector(G4String name, G4int xVox, G4int yVox, G4int zVox);
	~NuLatPMTSensitiveDetector();
	// Initialize the Sensitive Detector
	virtual void Initialize(G4HCofThisEvent* hce);
	// ProcessHits()
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
	// convert particle name string to number
	virtual G4int ParticleNameToIDNumber(G4String name);
private:
	// Constant for calculating wavelength from energy
	const G4double HCNM = 1239.841939*eV;
	// Boolean switch for debug messages
	G4bool debugMsg;
	// Hit collection object pointer and ID variable
	NuLatPMTHitsCollection *PMTHitCollection;
	G4int PMTHitCollectionID;
	// Voxels in each dimension, total number of PMTs
	G4int xVoxels, yVoxels, zVoxels, numPMT;
	// Variables for particle information
	G4int pID, fEvt, fID;
	G4String pName;
	// MC truth
	G4double xpos, ypos, zpos, pX0, pY0, pZ0, wlen;
	G4ThreeVector posPhoton, momPhoton;
	// PMT location
	G4double fX, fY, fZ, fT;
	G4ThreeVector posDet;
};
// end of conditional to define the class only once
#endif
