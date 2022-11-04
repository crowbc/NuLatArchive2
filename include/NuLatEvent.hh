// conditional to define class only once
#ifndef NULATEVENT_HH
#define NULATEVENT_HH
// Geant4 header files
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4AnalysisManager.hh"
// user defined header files
#include "NuLatRun.hh"
#include "NuLatVoxelHit.hh"
#include "NuLatPMTHit.hh"
// define the class
class NuLatEventAction : public G4UserEventAction
{
public:
	// Constructor and Destructor
	NuLatEventAction(NuLatRunAction* aRun);
	~NuLatEventAction();
	// User Event Actions
	virtual void BeginOfEventAction(const G4Event* anEvent);
	virtual void EndOfEventAction(const G4Event* anEvent);
	// functions to add energy depositions
	void AddEdepNuLat(G4double edep){ fEdepNuLat+=edep; }
	void AddEdepNaI(G4double edep){ fEdepNaI+=edep; }
private:
	// variable to store energy depositions
	G4double fEdepNuLat, fEdepNaI;
	// variables to store hit voxel coordinates, time and momentum components
	G4double fX, fY, fZ, fT, fPX0, fPY0, fPZ0;
	// variables to store PMT and Voxel hit collection ID, event ID, Voxel Hit ID, PMT Hit ID, index of hit voxel, and particle ID, and to set voxel count in x, y and z and number of PMTs
	G4int fPCHCID, fECHCID, fEvent, fVHit, fPHit, fID, fPID, xVoxels, yVoxels, zVoxels, nPMT;
};
// end of conditional to define class only once
#endif
