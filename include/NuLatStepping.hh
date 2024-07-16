// Conditional to define class only once
#ifndef NULATSTEPPING_HH
#define NULATSTEPPING_HH
// Geant4 header files
#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
// user defined header files
#include "NuLatDetectorConstruction.hh"
#include "NuLatEvent.hh"
// Class definition
class NuLatSteppingAction : public G4UserSteppingAction
{
public:
	// Constructor and Destructor
	NuLatSteppingAction(NuLatEventAction* eventAction);
	~NuLatSteppingAction();
	// User Stepping Action
	virtual void UserSteppingAction(const G4Step*);
	virtual G4int ParticleNameToIDNumber(G4String name);
private:
	NuLatEventAction *fEventAction;
	// variable for particle name
	G4String pName;
	// variable for particle ID
	G4int pID;
	// variable for energy deposit
	G4double eDepTot;
};

#endif
