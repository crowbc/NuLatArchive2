// included user defined header
#include "NuLatVoxelSensDet.hh"
// Constructor
NuLatVoxelSensitiveDetector::NuLatVoxelSensitiveDetector(G4String name, G4int xVox, G4int yVox, G4int zVox) : G4VSensitiveDetector(name), voxelHitCollection(0), voxelHitCollectionID(-1)
{
	collectionName.insert("NuLatVoxelColl");
	xVoxels = xVox;
	yVoxels = yVox;
	zVoxels = zVox;
	// Debug Message - can't see how it changes here. Maybe use SDM pointer?
	//G4cout << "Voxel SD collection name: " << name << "; inserted string: " << collectionName[0] << G4endl;
}
// Destructor
NuLatVoxelSensitiveDetector::~NuLatVoxelSensitiveDetector()
{}
// Initialze the Sensitive Detector
void NuLatVoxelSensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
	voxelHitCollection = new NuLatVoxelHitsCollection(SensitiveDetectorName, collectionName[0]);
	if (voxelHitCollectionID<0)
	{
		voxelHitCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(voxelHitCollection);
	}
	hce->AddHitsCollection(voxelHitCollectionID, voxelHitCollection);
	// fill NuLatVoxelHits with zero energy deposition
	for (G4int i = 0; i < xVoxels*yVoxels*zVoxels; i++)
	{
		NuLatVoxelHit* hit = new NuLatVoxelHit(i);
		voxelHitCollection->insert(hit);
	}
}
// Process Hits in the Sensitive Detector
G4bool NuLatVoxelSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist)
{
	G4int evt, pID;
	G4double tedep = aStep->GetTotalEnergyDeposit();
	G4double xpos, ypos, zpos, time, pX0, pY0, pZ0;
	G4Track *track = aStep->GetTrack();
	G4String pName = track->GetDefinition()->GetParticleName();
	pID = ParticleNameToIDNumber(pName);
	//G4ThreeVector posHit, momHit;
	if (tedep == 0.)
		return true;
	if (pID == 100)
		return true;
	//G4TouchableHistory *touch = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
	const G4VTouchable *touch = aStep->GetPreStepPoint()->GetTouchable();
	G4VPhysicalVolume *physVol = touch->GetVolume();
	G4int copyNo = physVol->GetCopyNo();
	NuLatVoxelHit *hit = (*voxelHitCollection)[copyNo];
	// check if it is first touch
	if (!(hit->GetLogV()))
	{
		// fill volume information
		hit->SetLogV(physVol->GetLogicalVolume());
		G4AffineTransform transform = touch->GetHistory()->GetTopTransform();
		transform.Invert();
		hit->SetRot(transform.NetRotation());
		hit->SetPos(transform.NetTranslation());
	}
	// populate variables
	evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	//posHit = aStep->GetTrack()->GetPosition();
	xpos = aStep->GetTrack()->GetPosition().x();
	ypos = aStep->GetTrack()->GetPosition().y();
	zpos = aStep->GetTrack()->GetPosition().z();
	time = aStep->GetTrack()->GetGlobalTime();
	pX0 = aStep->GetTrack()->GetVertexMomentumDirection().theta();
	pY0 = aStep->GetTrack()->GetVertexMomentumDirection().phi();
	pZ0 = aStep->GetTrack()->GetVertexMomentumDirection().z();
	// add energy deposit to this voxel
	hit->AddEdep(tedep);
	hit->PushEDepParticleTypeIDNumber(pID);
	hit->PushEDep(tedep);
	hit->PushEDepXPosition(xpos);
	hit->PushEDepYPosition(ypos);
	hit->PushEDepZPosition(zpos);
	hit->PushEDepTime(time);
	hit->PushInitialXMomentum(pX0);
	hit->PushInitialYMomentum(pY0);
	hit->PushInitialZMomentum(pZ0);
	// initialize analysis manager and fill Ntuples
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	// Fill Ntuple columns with Voxel energy deposition information - add columns for particle ID number, momentum components - do in NuLatEvent.cc
	/*man->FillNtupleIColumn(2, 0, evt);
	man->FillNtupleDColumn(2, 1, tedep);
	man->FillNtupleDColumn(2, 2, xpos);
	man->FillNtupleDColumn(2, 3, ypos);
	man->FillNtupleDColumn(2, 4, zpos);
	man->FillNtupleIColumn(2, 5, copyNo);
	man->AddNtupleRow(2);/**/
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
		num=1;
	}
	else if(name == "e"){
		num=2;
	}
	else if(name == "e+"){
		num=3;
	}
	else if(name == "neutron"){
		num=4;
	}
	else if(name == "proton"){
		num=5;
	}
	else if(name == "mu+"){
		num=6;
	}
	else if(name == "mu-"){
		num=7;
	}
	else if(name == "alpha"){
		num=8;
	}
	else if(name == "Li7"){
		num=9;
	}
	else if(name == "opticalphoton"){
		num=100;
	}
	else num=0;
	return num;
}
