// user defined header file for class
#include "NuLatEvent.hh"
// Constructor
NuLatEventAction::NuLatEventAction(NuLatRunAction* aRun) : G4UserEventAction(), fPCHCID(-1), fECHCID(-1)
{
	// initialize with 0 energy
	fEdepNuLat=0.;
	fEdepNaI=0.;
	// assume 5x5x5 array. Set a way to pass these from detector construction
	xVoxels = 5;
	yVoxels = 5;
	zVoxels = 5;
	nPMT = yVoxels*zVoxels + xVoxels*zVoxels + xVoxels*yVoxels;// ()*2 for fully instrumented detector
}
// Destructor
NuLatEventAction::~NuLatEventAction()
{}
// Begin of Event Action
void NuLatEventAction::BeginOfEventAction(const G4Event* anEvent)
{
	// Set energy to 0 at beginning of every event
	fEdepNuLat=0.;
	fEdepNaI=0.;
	// Get event number, print event number for every 1000th event
	fEvent = anEvent->GetEventID();
	if(fEvent%1000 == 0)
	{
		if (fEvent == 0) G4cout << "Beginning of Run..." << G4endl << G4endl;
		G4cout << "Beginning of event # " << fEvent << G4endl;
	}
	if (fECHCID==-1)
	{
		G4SDManager *SDman = G4SDManager::GetSDMpointer();
		fECHCID = SDman->GetCollectionID("NuLatVoxel/NuLatVoxelColl");
	}
	if (fPCHCID==-1)
	{
		G4SDManager *SDman = G4SDManager::GetSDMpointer();
		fPCHCID = SDman->GetCollectionID("NuLatPMT/NuLatPMTColl");
	}
}
// End of Event Action
void NuLatEventAction::EndOfEventAction(const G4Event* anEvent)
{
	// Initialize analysis manager and fill N tuple with energy depositions
	G4AnalysisManager *Aman = G4AnalysisManager::Instance();// to do: fill all N-tuples with event manager, not SD
	// Get hit collection of the event
	G4HCofThisEvent *hce = anEvent->GetHCofThisEvent();// to do: get particle ID from hits (not primaries - at least not yet)
	// Zero Hit counters
	fVHit = 0;
	fPHit = 0;
	// Get Voxel and PMT Hit collections from hce
	NuLatVoxelHitsCollection *VoxHC = static_cast<NuLatVoxelHitsCollection*>(hce->GetHC(fECHCID));
	NuLatPMTHitsCollection *PMTHC = static_cast<NuLatPMTHitsCollection*>(hce->GetHC(fPCHCID));
	// Populate PMT Hit containers - to do: write a function for this
	for(G4int i = 0; i < nPMT; i++)
	{
		NuLatPMTHit *hit = (*PMTHC)[i];
		// Get the number of photoelectrons registering a hit
		G4double peHits = hit->GetPEHits();
		// To do:
		// (1) handle x, y and z index for hit location based on i
		// (2) populate local vectors with values from the hits collection
		// (3) fPHit = peHits?
	}
	// Fill Hit MC Truth N-tuple
	Aman->FillNtupleIColumn(2, 0, fEvent);
	// NuLat Scoring
	Aman->FillNtupleDColumn(2, 1, fEdepNuLat);
	Aman->FillNtupleDColumn(2, 2, fX);
	Aman->FillNtupleDColumn(2, 3, fY);
	Aman->FillNtupleDColumn(2, 4, fZ);
	Aman->FillNtupleDColumn(2, 5, fT);
	Aman->FillNtupleIColumn(2, 6, fID);
	Aman->FillNtupleDColumn(2, 7, fPX0);
	Aman->FillNtupleDColumn(2, 8, fPY0);
	Aman->FillNtupleDColumn(2, 9, fPZ0);
	// Particle ID
	Aman->FillNtupleIColumn(2, 10, fPID);
	// NaI Scoring
	Aman->FillNtupleDColumn(2, 11, fEdepNaI);
	Aman->AddNtupleRow(2);
	// to do: clear Hit Vectors after end of event output files are written
}
