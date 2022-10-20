// included user defined header
#include "NuLatVoxelSensDet.hh"
// Constructor
NuLatVoxelSensitiveDetector::NuLatVoxelSensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
	collectionName.insert(name);
}
// Destructor
NuLatVoxelSensitiveDetector::~NuLatVoxelSensitiveDetector()
{}
// ProcessHits()
G4bool NuLatVoxelSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist)
{
	G4bool debugMsg = false;// set to true to enable debug messages
	G4int evt, pID;
	G4double tedep = aStep->GetTotalEnergyDeposit();
	G4double xpos, ypos, zpos, time, pX0, pY0, pZ0;
	if (tedep==0.)
		return true;
	if (aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton")
		return true;
	G4TouchableHistory *touch = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
	G4VPhysicalVolume *physVol = ROHist->GetVolume();
	G4int copyNo = physVol->GetCopyNo();
	//NuLatVoxelHit *hit = (*voxelHitCollection)[copyNo];
	// check if it is first touch
	/*if (!(hit->GetLogV()))
	{
		// fill volume information
		hit->SetLogV(physVol->GetLogicalVolume());
		G4AffineTransform transform = touch->GetHistory()->GetTopTransform();
		transform.Invert();
		hit->SetRot(transform.NetRotation());
		hit->SetPos(transform.NetTranslation());
	}/**/
	// populate variables
	evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	xpos = aStep->GetTrack()->GetPosition().x();
	ypos = aStep->GetTrack()->GetPosition().y();
	zpos = aStep->GetTrack()->GetPosition().z();
	time = aStep->GetTrack()->GetGlobalTime();
	pID = ParticleNameToIDNumber(aStep);
	pX0 = aStep->GetTrack()->GetVertexMomentumDirection().theta();
	pY0 = aStep->GetTrack()->GetVertexMomentumDirection().phi();
	pZ0 = aStep->GetTrack()->GetVertexMomentumDirection().z();
	// add energy deposit to this voxel
	/*hit->AddEdep(tedep);
	hit->PushEDepParticleTypeIDNumber(pID);
	hit->PushEDep(tedep);
	hit->PushEDepXPosition(xpos);
	hit->PushEDepYPosition(ypos);
	hit->PushEDepZPosition(zpos);
	hit->PushEDepTime(time);
	hit->PushinitialXMomentum(pX0);
	hit->PushInitialYMomentum(pY0);
	hit->PushInitialZMomentum(pZ0);/**/
	// initialize analysis manager and fill Ntuples
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	// Fill Ntuple columns with Voxel energy deposition information - add column for particle ID number
	man->FillNtupleIColumn(2, 0, evt);
	man->FillNtupleDColumn(2, 1, tedep);
	man->FillNtupleDColumn(2, 2, xpos);
	man->FillNtupleDColumn(2, 3, ypos);
	man->FillNtupleDColumn(2, 4, zpos);
	man->FillNtupleIColumn(2, 5, copyNo);
	man->AddNtupleRow(2);
	// Return value
	return true;
}
/* ---------------------------------------------- */
/*  Convert a steps particle name to an ID number */
/*  specific to the NuLat analysis                */
/* ---------------------------------------------- */
G4int NuLatVoxelSensitiveDetector::ParticleNameToIDNumber(G4Step* step)
{
	G4int particleIDNumber;
	if(step->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton")
	{
		particleIDNumber=100;
	}
	else if(step->GetTrack()->GetDefinition()->GetParticleName()=="e-")
	{
		particleIDNumber=2;
	}
	else if(step->GetTrack()->GetDefinition()->GetParticleName()=="e+")
	{
		particleIDNumber=3;
	}
	else if(step->GetTrack()->GetDefinition()->GetParticleName()=="neutron")
	{
		particleIDNumber=4;
	}
	else if(step->GetTrack()->GetDefinition()->GetParticleName()=="proton")
	{
		particleIDNumber=5;
	}
	else if(step->GetTrack()->GetDefinition()->GetParticleName()=="mu+")
	{
		particleIDNumber=6;
	}
	else if(step->GetTrack()->GetDefinition()->GetParticleName()=="mu-")
	{
		particleIDNumber=7;
	}
	else if(step->GetTrack()->GetDefinition()->GetParticleName()=="alpha")
	{
		particleIDNumber=8;
	}
	else if(step->GetTrack()->GetDefinition()->GetParticleName()=="Li7")
	{
		particleIDNumber=9;
	}
	else if(step->GetTrack()->GetDefinition()->GetParticleName()=="gamma")
	{
		particleIDNumber=1;
	}
	else
	{
		particleIDNumber=0;
	}
	return (particleIDNumber);
}
