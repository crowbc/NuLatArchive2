#include "NuLatAction.hh"

NuLatActionInitialization::NuLatActionInitialization()
{}

NuLatActionInitialization::~NuLatActionInitialization()
{}

void NuLatActionInitialization::BuildForMaster() const
{
	// Do only Run Action for Master Thread
	NuLatRunAction *runAction = new NuLatRunAction();
	SetUserAction(runAction);
}

void NuLatActionInitialization::Build() const
{
	// Generator Action
	NuLatPrimaryGenerator *generator = new NuLatPrimaryGenerator();
	SetUserAction(generator);
	// Run Action
	NuLatRunAction *runAction = new NuLatRunAction();
	SetUserAction(runAction);
	// Event Action
	NuLatEventAction *eventAction = new NuLatEventAction(runAction);
	SetUserAction(eventAction);
	// Stepping Action
	NuLatSteppingAction *steppingAction = new NuLatSteppingAction(eventAction);
	SetUserAction(steppingAction);
}
