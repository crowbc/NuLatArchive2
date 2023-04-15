// user defined header file for class
#include "NuLatEvent.hh"
// Constructor
NuLatEventAction::NuLatEventAction(NuLatRunAction* aRun) : G4UserEventAction(), fPCHCID(-1), fECHCID(-1)
{
	// initialize with 0 energy
	fEdepNuLat=0.;
	// assume 5x5x5 array. Set a way to pass these from detector construction
	xVoxels = 5;
	yVoxels = 5;
	zVoxels = 5;
	nPMT = yVoxels*zVoxels + xVoxels*zVoxels + xVoxels*yVoxels;// ()*2 for fully instrumented detector
	nVox = xVoxels*yVoxels*zVoxels;
}
// Destructor
NuLatEventAction::~NuLatEventAction()
{}
// Begin of Event Action
void NuLatEventAction::BeginOfEventAction(const G4Event* anEvent)
{
	// Set energy to 0 at beginning of every event
	fEdepNuLat=0.;
	// Get event number, print event number for every 1000th event
	fEvent = anEvent->GetEventID();
	G4int rNum;// = anEvent->command to get the run->GetRunID();
	if(fEvent%1000 == 0)
	{
		if (fEvent == 0) G4cout << "Beginning of run... "/*# " << rNum*/ << G4endl << G4endl;
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
	// Fill NuLat scoring N-tuple
	Aman->FillNtupleIColumn(2, 0, fEvent);
	// Populate Voxel Hit containers and write to N tuple
	for(G4int i = 0; i < nVox; i++)
	{
		// Deprecated method - hit scoring is done directly in NuLatVoxelSensDet.cc and output Ntuples are written there
		NuLatVoxelHit *hit = (*VoxHC)[i];
		// Clear vectors to handle memory leaks
		hit->ClearvoxEDepPIDVec();
		hit->ClearEDepVec();
		hit->ClearxPosVoxEDepVec();
		hit->ClearyPosVoxEDepVec();
		hit->ClearzPosVoxEDepVec();
		hit->ClearpX0VoxEDepVec();
		hit->ClearpY0VoxEDepVec();
		hit->ClearpZ0VoxEDepVec();/**/
	}
	// finish NuLat Scoring
	Aman->AddNtupleRow(2);
	NuLatPMTHitsCollection *PMTHC = static_cast<NuLatPMTHitsCollection*>(hce->GetHC(fPCHCID));
	// Populate PMT Hit containers - to do: write a function for this
	for(G4int i = 0; i < nPMT; i++)
	{
		// Deprecated method - hit scoring is done directly in NuLatPMTsensDet.cc and output Ntuples are written there
		NuLatPMTHit *hit = (*PMTHC)[i];
		// Get the number of photoelectrons registering a hit
		G4double peHits = hit->GetPEHits();
		// To do:
		// Clear vectors to handle memory leaks
		hit->ClearPMTHitPID();
		hit->ClearPMTHitEnergyVec();
		hit->ClearPMTHitWlenVec();
		hit->ClearxPosPMTHitVec();
		hit->ClearyPosPMTHitVec();
		hit->ClearzPosPMTHitVec();
		hit->ClearPMTHitTimeVec();/**/
	}
	// to do: ...
}
