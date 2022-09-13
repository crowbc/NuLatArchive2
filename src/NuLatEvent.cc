// user defined header file for class
#include "NuLatEvent.hh"
// Constructor
NuLatEventAction::NuLatEventAction(NuLatRunAction*)
{
	// initialize with 0 energy
	fEdepNuLat=0.;
	fEdepNaI=0.;
	// utilize trajectories to get hit voxels and do energy deposition for voxels from when trajectory enters and leaves voxel, or count total absorption if no trajectory out
}
// Destructor
NuLatEventAction::~NuLatEventAction()
{}
// Begin of Event Action
void NuLatEventAction::BeginOfEventAction(const G4Event*)
{
	// Set energy to 0 at beginning of every event
	fEdepNuLat=0.;
	fEdepNaI=0.;
}
// End of Event Action
void NuLatEventAction::EndOfEventAction(const G4Event*)
{
	// Initialize analysis manager and fill N tuple with energy depositions
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	// NuLat Voxel Scoring
	man->FillNtupleDColumn(2, 1, fEdepNuLat);
	man->FillNtupleDColumn(2, 2, fX);
	man->FillNtupleDColumn(2, 3, fY);
	man->FillNtupleDColumn(2, 4, fZ);
	man->FillNtupleIColumn(2, 5, fID);
	// NaI Scoring
	man->FillNtupleDColumn(2, 6, fEdepNaI);
	man->AddNtupleRow(2);
}
