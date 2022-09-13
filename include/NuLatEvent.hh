// conditional to define class only once
#ifndef NULATEVENT_HH
#define NULATEVENT_HH
// Geant4 header files
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
// user defined header files
#include "NuLatRun.hh"
// define the class
class NuLatEventAction : public G4UserEventAction
{
public:
	// Constructor and Destructor
	NuLatEventAction(NuLatRunAction*);
	~NuLatEventAction();
	// User Event Actions
	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);
	// functions to add energy depositions
	void AddEdepNuLat(G4double edep){ fEdepNuLat+=edep; }
	void AddEdepNaI(G4double edep){ fEdepNaI+=edep; }
private:
	// variable to store energy depositions
	G4double fEdepNuLat, fEdepNaI;
	// variables to store hit voxel coordinates
	G4double fX, fY, fZ;
	// variable to store index of hit voxel
	G4int fID;
};
// end of conditional to define class only once
#endif
