// user defined header file for class
#include "NuLatStepping.hh"
// Constructor
NuLatSteppingAction::NuLatSteppingAction(NuLatEventAction* eventAction)
{
	fEventAction = eventAction;
}
// Destructor
NuLatSteppingAction::~NuLatSteppingAction()
{}
// User Stepping Action - NaI scoring deprecated
void NuLatSteppingAction::UserSteppingAction(const G4Step* aStep)
{
	// Get volume from step, use to find scoring volume
	G4LogicalVolume *volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	const NuLatDetectorConstruction *detCons = static_cast<const NuLatDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	G4LogicalVolume *fScoringVolumeNuLat = detCons->GetScoringVolumeNuLat();
	// Add energy deposit if it's in the scoring volume, otherwise return without computing
	if((volume != fScoringVolumeNuLat))
	{
		return;
	}
	if(volume == fScoringVolumeNuLat)
	{
		// Nothing to do. Scoring done in NuLatSensDet.cc
		return;
	}
}
