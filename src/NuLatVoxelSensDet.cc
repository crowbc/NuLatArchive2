// included user defined header
#include "NuLatVoxelSensDet.hh"
// Constructor
NuLatVoxelSensitiveDetector::NuLatVoxelSensitiveDetector(G4String name, G4int xVox, G4int yVox, G4int zVox) : G4VSensitiveDetector(name), voxHitColl(0), voxHitCollID(-1)
{
	collectionName.insert("NuLatVoxelColl");
	xVoxels = xVox;
	yVoxels = yVox;
	zVoxels = zVox;
	nVox = xVoxels*yVoxels*zVoxels;
	// Debug Message - can't see how it changes here. Maybe use SDM pointer?
	//G4cout << "Voxel SD collection name: " << name << "; inserted string: " << collectionName[0] << G4endl;
}
// Destructor
NuLatVoxelSensitiveDetector::~NuLatVoxelSensitiveDetector()
{}
// Initialze the Sensitive Detector
void NuLatVoxelSensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
	voxHitColl = new NuLatVoxelHitsCollection(SensitiveDetectorName, collectionName[0]);
	if (voxHitCollID<0)
	{
		voxHitCollID = G4SDManager::GetSDMpointer()->GetCollectionID(voxHitColl);
	}
	hce->AddHitsCollection(voxHitCollID, voxHitColl);
	// fill NuLatVoxelHits with zero energy deposition
	for (G4int i = 0; i < nVox; i++)
	{
		NuLatVoxelHit* hit = new NuLatVoxelHit(i);
		voxHitColl->insert(hit);
	}
}
// Process Hits in the Sensitive Detector
G4bool NuLatVoxelSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist)
{
	G4int evt, pID, trkID;
	G4double eDep = aStep->GetTotalEnergyDeposit();
	G4double xPos, yPos, zPos, time, pX0, pY0, pZ0;
	G4Track *track = aStep->GetTrack();
	trkID = track->GetTrackID();
	G4String pName = track->GetDefinition()->GetParticleName();
	pID = ParticleNameToIDNumber(pName);
	//G4ThreeVector posHit, momHit;
	if (eDep == 0.)
	{
		return true;
	}
	if (pID == 100)
	{
		return true;
	}
	const G4VTouchable *touch = aStep->GetPreStepPoint()->GetTouchable();
	G4VPhysicalVolume *physVol = touch->GetVolume();
	G4int copyNo = physVol->GetCopyNo();
	NuLatVoxelHit *hit = (*voxHitColl)[copyNo];
	// check if it is first touch - commented out the conditional to get all hits, not just first touches
	//if (!(hit->GetLogV()))
	//{
		// fill volume information
		hit->SetLogV(physVol->GetLogicalVolume());
		G4AffineTransform transform = touch->GetHistory()->GetTopTransform();
		transform.Invert();
		hit->SetRot(transform.NetRotation());
		hit->SetPos(transform.NetTranslation());
	//}
	// populate variables
	evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	//posHit = aStep->GetTrack()->GetPosition();
	xPos = aStep->GetTrack()->GetPosition().x();
	yPos = aStep->GetTrack()->GetPosition().y();
	zPos = aStep->GetTrack()->GetPosition().z();
	time = aStep->GetTrack()->GetGlobalTime();
	pX0 = aStep->GetTrack()->GetVertexMomentumDirection().x();
	pY0 = aStep->GetTrack()->GetVertexMomentumDirection().y();
	pZ0 = aStep->GetTrack()->GetVertexMomentumDirection().z();
	// add energy deposit to this voxel
	hit->AddEdep(eDep);
	hit->PushVoxEDepPIDVec(pID);
	hit->PushEDep(eDep);
	hit->PushxPosVoxEDepVec(xPos);
	hit->PushyPosVoxEDepVec(yPos);
	hit->PushzPosVoxEDepVec(zPos);
	hit->PushtimeVoxEDepVec(time);
	hit->PushpX0VoxEDepVec(pX0);
	hit->PushpY0VoxEDepVec(pY0);
	hit->PushpZ0VoxEDepVec(pZ0);
	// initialize analysis manager and fill Ntuples
	G4AnalysisManager *aMan = G4AnalysisManager::Instance();
	// Fill Ntuple columns with Voxel energy deposition information - to do: add columns for other MC information (can I store track objects like in Rat-Pac?)
	aMan->FillNtupleIColumn(2, 0, evt);
	aMan->FillNtupleIColumn(2, 1, pID);
	aMan->FillNtupleIColumn(2, 2, trkID);
	aMan->FillNtupleIColumn(2, 3, copyNo);
	aMan->FillNtupleDColumn(2, 4, eDep);
	aMan->FillNtupleDColumn(2, 5, xPos);
	aMan->FillNtupleDColumn(2, 6, yPos);
	aMan->FillNtupleDColumn(2, 7, zPos);
	aMan->FillNtupleDColumn(2, 8, time);
	aMan->FillNtupleDColumn(2, 9, pX0);
	aMan->FillNtupleDColumn(2, 10, pY0);
	aMan->FillNtupleDColumn(2, 11, pZ0);
	aMan->AddNtupleRow(2);
	// Return value
	return true;
}
/* ---------------------------------------------- */
/*  Convert a steps particle name to an ID number */
/*  specific to the NuLat analysis                */
/* ---------------------------------------------- */
G4int NuLatVoxelSensitiveDetector::ParticleNameToIDNumber(G4String name)
{
	G4int num;
	if(name == "gamma"){
		num = 1;
	}
	else if(name == "e"){
		num = 2;
	}
	else if(name == "e+"){
		num = 3;
	}
	else if(name == "neutron"){
		num = 4;
	}
	else if(name == "proton"){
		num = 5;
	}
	else if(name == "mu+"){
		num = 6;
	}
	else if(name == "mu-"){
		num = 7;
	}
	else if(name == "alpha"){
		num = 8;
	}
	else if(name == "Li7"){
		num = 9;
	}
	else if(name == "opticalphoton"){
		num = 100;
	}
	else{
		num = 0;
	}
	return num;
}
