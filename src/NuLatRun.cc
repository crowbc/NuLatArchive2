// user defined header file for class
#include "NuLatRun.hh"
// Constructor
NuLatRunAction::NuLatRunAction()
{
	// initialize analysis manager
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	// create N tuple for photon information - MC truth
	man->CreateNtuple("Photon", "Photon");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->CreateNtupleDColumn("fWlen");
	man->FinishNtuple(0);
	// create N tuple for PMT hit information
	man->CreateNtuple("Hits", "Hits");
	man->CreateNtupleIColumn("fEvent");
	// PMT coords
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	// PMT ID - to do: set PMT ID for NaI?
	man->CreateNtupleIColumn("fID");
	// To do: Needs number of hits?
	man->FinishNtuple(1);
	// create N tuple for energy deposition - MC truth
	man->CreateNtuple("Scoring", "Scoring");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("fEdepNuLat");
	// Voxel coords
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	// Voxel ID - can use to make map if coordinates are not true
	man->CreateNtupleIColumn("fID");
	// column for NaI scoring
	man->CreateNtupleDColumn("fEdepNaI");
	man->FinishNtuple(2);
}
// Destructor
NuLatRunAction::~NuLatRunAction()
{}
// Beginning of Run
void NuLatRunAction::BeginOfRunAction(const G4Run* NaIRun)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	G4int rNum = NaIRun->GetRunID();
	std::stringstream sRunID;
	sRunID << rNum;
	G4String name = "NuLatoutput";
	G4String ext = ".root";
	G4String fName = name + sRunID.str() + ext;
	man->OpenFile(fName);
	man->SetVerboseLevel(1);
}
// End of Run
void NuLatRunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	// write and close the Root file !IMPORTANT!
	man->Write();
	man->CloseFile();
}
