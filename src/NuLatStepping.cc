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
// User Stepping Action
void NuLatSteppingAction::UserSteppingAction(const G4Step *step)
{
	// Get volume from step, use to find scoring volume
	G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	const NuLatDetectorConstruction *detCons = static_cast<const NuLatDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	G4LogicalVolume *fScoringVolumeNuLat = detCons->GetScoringVolumeNuLat();
	G4LogicalVolume *fScoringVolumeNaI = detCons->GetScoringVolumeNaI();
	// Add energy deposit if it's in the scoring volume, otherwise return without computing
	if(volume == fScoringVolumeNaI)
	{
		G4double edep = step->GetTotalEnergyDeposit();// inaccurate: get the energy of the gammas only. look at stepping methods to improve
		// useful things to track might be found in hits collections (probably best), decay products allocators, and maybe trajectories and tracks
		fEventAction->AddEdepNaI(edep);
	}
	if(volume == fScoringVolumeNuLat)
	{
		// To do: do scoring and location for NuLat Voxels
		return;// remove return statement. put in conditional to return if volume is neither
	}
}
