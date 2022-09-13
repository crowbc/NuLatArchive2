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
private:
	NuLatEventAction *fEventAction;
};

#endif
