// conditional to define the class only once
#ifndef NAIPMTSENSDET_HH
#define NAIPMTSENSDET_HH
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
#include "NaIPMTHit.hh"
// define the class
class NaIPMTSensitiveDetector : public G4VSensitiveDetector
{
public:
	// Constructor and Destructor
	NaIPMTSensitiveDetector(G4String name);
	~NaIPMTSensitiveDetector();
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
	NaIPMTHitsCollection *PMTHitCollection;
	G4int PMTHitCollectionID;
	// Total number of PMTs - should always be 1
	G4int numPMT;
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
