// user defined header file for class
#include "NuLatRun.hh"
// Constructor
NuLatRunAction::NuLatRunAction()
{
	// initialize analysis manager
	G4AnalysisManager *Aman = G4AnalysisManager::Instance();
	// create N tuple for photon truth information in NuLat PMT hits
	Aman->CreateNtuple("NuLat PMT Truth", "NuLat PMT Truth");
	Aman->CreateNtupleIColumn("fEvent");
	Aman->CreateNtupleDColumn("fX");
	Aman->CreateNtupleDColumn("fY");
	Aman->CreateNtupleDColumn("fZ");
	Aman->CreateNtupleDColumn("fWlen");
	Aman->FinishNtuple(0);
	// create N tuple for PMT hit information
	Aman->CreateNtuple("NuLat PMT Hits", "NuLat PMT Hits");
	Aman->CreateNtupleIColumn("fEvent");
	// PMT coords
	Aman->CreateNtupleDColumn("fX");
	Aman->CreateNtupleDColumn("fY");
	Aman->CreateNtupleDColumn("fZ");
	// time of hit
	Aman->CreateNtupleDColumn("fT");
	// PMT ID - to do: add N-Tuple for NaI Hits
	Aman->CreateNtupleIColumn("fID");
	// To do: Needs number of hits?
	Aman->FinishNtuple(1);
	// create N tuple for energy deposition tracking (MC truth)
	Aman->CreateNtuple("Scoring", "Scoring");
	Aman->CreateNtupleIColumn("fEvent");
	Aman->CreateNtupleDColumn("fEdepNuLat");
	// Voxel coords
	Aman->CreateNtupleDColumn("fX");
	Aman->CreateNtupleDColumn("fY");
	Aman->CreateNtupleDColumn("fZ");
	// time of hit
	Aman->CreateNtupleDColumn("fT");
	// Voxel ID - can use to validate whether or not coordinates are true
	Aman->CreateNtupleIColumn("fID");
	// columns for momentum components
	Aman->CreateNtupleDColumn("fPX0");
	Aman->CreateNtupleDColumn("fPY0");
	Aman->CreateNtupleDColumn("fPZ0");
	// column for particle ID
	Aman->CreateNtupleIColumn("fPID");
	// column for NaI scoring
	Aman->CreateNtupleDColumn("fEdepNaI");
	Aman->FinishNtuple(2);
	// create N tuple for photon truth information in NaI PMT hits
	Aman->CreateNtuple("NaI PMT Truth", "NaI PMT Truth");
	Aman->CreateNtupleIColumn("fEvent");
	Aman->CreateNtupleDColumn("fX");
	Aman->CreateNtupleDColumn("fY");
	Aman->CreateNtupleDColumn("fZ");
	Aman->CreateNtupleDColumn("fWlen");
	Aman->FinishNtuple(3);
	// create N tuple for NaI hits
	Aman->CreateNtuple("NaI PMT Hits", "NaI PMT Hits");
	Aman->CreateNtupleIColumn("fEvent");
	// PMT coords
	Aman->CreateNtupleDColumn("fX");
	Aman->CreateNtupleDColumn("fY");
	Aman->CreateNtupleDColumn("fZ");
	// time of hit
	Aman->CreateNtupleDColumn("fT");
	// PMT ID for NaI
	Aman->CreateNtupleIColumn("fID");
	Aman->FinishNtuple(4);
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
