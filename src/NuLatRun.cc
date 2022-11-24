// user defined header file for class
#include "NuLatRun.hh"
// Constructor
NuLatRunAction::NuLatRunAction()
{
	// initialize analysis manager
	G4AnalysisManager *Aman = G4AnalysisManager::Instance();
	// create N tuple for photon truth information in NuLat PMT hits
	Aman->CreateNtuple("NuLat_PMT_Truth", "NuLat_PMT_Truth");// Ntuple 0
	Aman->CreateNtupleIColumn("fEvent");// col 0
	Aman->CreateNtupleDColumn("fX");// col 1
	Aman->CreateNtupleDColumn("fY");// col 2
	Aman->CreateNtupleDColumn("fZ");// c0l 3
	Aman->CreateNtupleDColumn("fWlen");// col 4
	Aman->FinishNtuple(0);
	// create N tuple for PMT hit information
	Aman->CreateNtuple("NuLat_PMT_Hits", "NuLat_PMT_Hits");// Ntuple 1
	Aman->CreateNtupleIColumn("fEvent");// col 0
	// PMT ID
	Aman->CreateNtupleIColumn("fID");// col 1
	// PMT coords
	Aman->CreateNtupleDColumn("fX");// col 2
	Aman->CreateNtupleDColumn("fY");// col 3
	Aman->CreateNtupleDColumn("fZ");// col 4
	// time of hit
	Aman->CreateNtupleDColumn("fT");// col 5
	// To do: Needs number of hits?
	Aman->FinishNtuple(1);
	// create N tuple for energy deposition tracking (MC truth)
	Aman->CreateNtuple("NuLat_Scoring", "NuLat_Scoring");// Ntuple 2
	Aman->CreateNtupleIColumn("fEvent");// col 0
	// columns for particle ID and track ID
	Aman->CreateNtupleIColumn("fPID");// col 1
	Aman->CreateNtupleIColumn("fTrkID");// col 2
	// Voxel ID - can use to validate whether or not coordinates are true
	Aman->CreateNtupleIColumn("fID");// col 3
	// scoring value for energy deposition
	Aman->CreateNtupleDColumn("fEdepNuLat");// col 4
	// Voxel coords
	Aman->CreateNtupleDColumn("fX");// col 5
	Aman->CreateNtupleDColumn("fY");// col 6
	Aman->CreateNtupleDColumn("fZ");// col 7
	// time of hit
	Aman->CreateNtupleDColumn("fT");// col 8
	// columns for momentum components
	Aman->CreateNtupleDColumn("fPX0");// col 9
	Aman->CreateNtupleDColumn("fPY0");// col 10
	Aman->CreateNtupleDColumn("fPZ0");// col 11
	Aman->FinishNtuple(2);
	// create N tuple for photon truth information in NaI PMT hits
	Aman->CreateNtuple("NaI_PMT_Truth", "NaI_PMT_Truth");// Ntuple 3
	Aman->CreateNtupleIColumn("fEvent");// col 0
	Aman->CreateNtupleDColumn("fX");// col 1
	Aman->CreateNtupleDColumn("fY");// col 2
	Aman->CreateNtupleDColumn("fZ");// col 3
	Aman->CreateNtupleDColumn("fWlen");// col 4
	Aman->FinishNtuple(3);
	// create N tuple for NaI hits
	Aman->CreateNtuple("NaI_PMT_Hits", "NaI_PMT_Hits");// Ntuple 4
	Aman->CreateNtupleIColumn("fEvent");// col 0
	// PMT ID for NaI
	Aman->CreateNtupleIColumn("fID");// col 1 - should be identically 0
	// PMT coords
	Aman->CreateNtupleDColumn("fX");// col 2
	Aman->CreateNtupleDColumn("fY");// col 3
	Aman->CreateNtupleDColumn("fZ");// col 4
	// time of hit
	Aman->CreateNtupleDColumn("fT");// col 5
	Aman->FinishNtuple(4);
	// Create N Tuple for NaI scoring
	Aman->CreateNtuple("NaI_Scoring", "NaI_Scoring");// Ntuple 5 - simple scoring; just tracks total energy depositiion
	Aman->CreateNtupleIColumn("fEvent");// col 0
	// column for NaI scoring
	Aman->CreateNtupleDColumn("fEdepNaI");// col 1
	Aman->FinishNtuple(5);
}
// Destructor
NuLatRunAction::~NuLatRunAction()
{}
// Beginning of Run
void NuLatRunAction::BeginOfRunAction(const G4Run* NuLatRun)
{
	G4AnalysisManager *Aman = G4AnalysisManager::Instance();
	G4int rNum = NuLatRun->GetRunID();
	std::stringstream sRunID;
	sRunID << rNum;
	G4String name = "NuLatoutput";
	G4String ext = ".root";
	G4String fName = name + sRunID.str() + ext;
	Aman->OpenFile(fName);
	Aman->SetVerboseLevel(1);
}
// End of Run
void NuLatRunAction::EndOfRunAction(const G4Run* NuLatRun)
{
	G4AnalysisManager *Aman = G4AnalysisManager::Instance();
	// write and close the ROOT file !IMPORTANT!
	Aman->Write();
	Aman->CloseFile();
}
