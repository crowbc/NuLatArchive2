// included user defined header
#include "NuLatVoxelSensDet.hh"
// Constructor
NuLatVoxelSensitiveDetector::NuLatVoxelSensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}
// Destructor
NuLatVoxelSensitiveDetector::~NuLatVoxelSensitiveDetector()
{}
// ProcessHits()
G4bool NuLatVoxelSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist)
{
	G4bool debugMsg = false;// set to true to enable debug messages
	// Fill Ntuple columns with Voxel energy deposition information
	//man->FillNtupleIColumn(2, 0, evt);
	//man->FillNtupleDColumn(2, 1, energy);// populate these variables
	//man->FillNtupleDColumn(2, 2, xpos);
	//man->FillNtupleDColumn(2, 3, ypos);
	//man->FillNtupleDColumn(2, 4, zpos);
	//man->FillNtupleIColumn(2, 5, voxNo);// populate down to here
	//man->AddNtupleRow(2);
	// Return value
	return true;
}
