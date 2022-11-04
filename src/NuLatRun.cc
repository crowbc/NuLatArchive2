// user defined header file for class
#include "NuLatRun.hh"
// Constructor
NuLatRunAction::NuLatRunAction()
{
	// initialize analysis manager
	G4AnalysisManager *Aman = G4AnalysisManager::Instance();
	// create N tuple for photon information - MC truth
	Aman->CreateNtuple("Photon", "Photon");
	Aman->CreateNtupleIColumn("fEvent");
	Aman->CreateNtupleDColumn("fX");
	Aman->CreateNtupleDColumn("fY");
	Aman->CreateNtupleDColumn("fZ");
	Aman->CreateNtupleDColumn("fWlen");
	Aman->FinishNtuple(0);
	// create N tuple for PMT hit information
	Aman->CreateNtuple("PMT Hits", "PMT Hits");
	Aman->CreateNtupleIColumn("fEvent");
	// PMT coords
	Aman->CreateNtupleDColumn("fX");
	Aman->CreateNtupleDColumn("fY");
	Aman->CreateNtupleDColumn("fZ");
	// PMT ID - to do: set PMT ID for NaI?
	Aman->CreateNtupleIColumn("fID");
	// To do: Needs number of hits?
	Aman->FinishNtuple(1);
	// create N tuple for energy deposition - MC truth
	Aman->CreateNtuple("Scoring", "Scoring");
	Aman->CreateNtupleIColumn("fEvent");
	Aman->CreateNtupleDColumn("fEdepNuLat");
	// Voxel coords
	Aman->CreateNtupleDColumn("fX");
	Aman->CreateNtupleDColumn("fY");
	Aman->CreateNtupleDColumn("fZ");
	// Voxel ID - can use to validate whether or not coordinates are true
	Aman->CreateNtupleIColumn("fID");
	// time of hit
	Aman->CreateNtupleDColumn("fT");
	// columns for momentum components
	Aman->CreateNtupleDColumn("fPX0");
	Aman->CreateNtupleDColumn("fPY0");
	Aman->CreateNtupleDColumn("fPZ0");
	// column for particle ID
	Aman->CreateNtupleIColumn("fPID");
	// column for NaI scoring
	Aman->CreateNtupleDColumn("fEdepNaI");
	Aman->FinishNtuple(2);
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
	// write and close the Root file !IMPORTANT!
	Aman->Write();
	Aman->CloseFile();
}
