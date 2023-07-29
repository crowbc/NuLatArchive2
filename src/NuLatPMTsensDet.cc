// Header for user defined library
#include "NuLatPMTsensDet.hh"
// Constructor
NuLatPMTSensitiveDetector::NuLatPMTSensitiveDetector(G4String name, G4int xVox, G4int yVox, G4int zVox) : G4VSensitiveDetector(name), PMTHitCollection(0), PMTHitCollectionID(-1)
{
	collectionName.insert("NuLatPMTColl");
	xVoxels = xVox;
	yVoxels = yVox;
	zVoxels = zVox;
	numPMT = yVoxels*zVoxels + xVoxels*zVoxels + xVoxels*yVoxels;// ()*2 for fully instrumented
}
// Destructor
NuLatPMTSensitiveDetector::~NuLatPMTSensitiveDetector()
{}
// Initialze the Sensitive Detector
void NuLatPMTSensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
	PMTHitCollection = new NuLatPMTHitsCollection(SensitiveDetectorName, collectionName[0]);
	if (PMTHitCollectionID<0)
	{
		PMTHitCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(PMTHitCollection);
	}
	hce->AddHitsCollection(PMTHitCollectionID, PMTHitCollection);
	// fill NuLatPMTHits with zero energy deposition
	for (G4int i = 0; i < numPMT; i++)
	{
		NuLatPMTHit* hit = new NuLatPMTHit(i);
		PMTHitCollection->insert(hit);
	}
}
// Process Hits Function - not sure I can use this method if I'm looking at something other than gammas. It will work for the NaI coincidence tagging
G4bool NuLatPMTSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist)
{
	debugMsg = false;// set to true for debug messages - note: can use Print() function in NuLatPMTHit.cc instead
	G4Track *track = aStep->GetTrack();
	pName = track->GetDefinition()->GetParticleName();
	pID = ParticleNameToIDNumber(pName);
	// only do this for optical photons to simulate the regime where the PMT is actually sensitve - note this will be tracked when PMT processes are simulated
	// TODO: store hit info in hit class vectors. these will be read in Event manager
	if (pID == 100)
	{
		track->SetTrackStatus(fStopAndKill);// not necessary when PMT processes are simulated
		// set up step points. Get true photon position of PMT hit
		G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
		G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
		// Get Photon Position, Momentum and Wavelength (MC truth)
		posPhoton = preStepPoint->GetPosition();
		xpos = posPhoton[0];
		ypos = posPhoton[1];
		zpos = posPhoton[2];
		momPhoton = preStepPoint->GetMomentum();
		pX0 = momPhoton[0];
		pY0 = momPhoton[1];
		pZ0 = momPhoton[2];
		// Calculates wavelength in nm (change constant to change unit order of magnitude)
		wlen = HCNM/momPhoton.mag();
		// Debug Print if enabled -- relevant info should be in hit class TODO: find a more efficient way to do this than using conditionals
		if(debugMsg){
			G4cout << "Photon position: " << posPhoton << "; Photon wavelength: " << wlen << " nm" << G4endl;
		}
		// Get index of hit PMT
		const G4VTouchable *touch = aStep->GetPreStepPoint()->GetTouchable();
		fID = touch->GetCopyNumber();
		// create hit container for hit PMT, then add the hit
		/*NuLatPMTHit *hit = (*NuLatPMTHitsCollection)[fID];
		hit->AddPEHits(1);/**/
		// Debug Print if enabled -- relevant info should be in hit class TODO: find a more efficient way to do this than using conditionals
		if(debugMsg)
		{
			G4cout << "Copy number: " << fID << G4endl;
		}
		// Get position of hit PMT (not photon position)
		G4VPhysicalVolume *physVol = touch->GetVolume();
		// Check if it is first touch
		/*if (!(hit->GetLogV()))
		{
			// fill volume information for first touch
			hit->SetLogV(physVol->GetLogicalVolume());
			G4AffineTransform transform = touch->GetHistory()->GetTopTransform();
			transform.Invert();
			hit->SetRot(transform.NetRotation());
			hit->SetPos(transform.NetTranslation());
		}
		// TODO: move hit collection and hit declaration outside of conditional after PMT process simulations are implemented
		// Fill the hit vectors
		hit->PushPMTHitParticleID(pID);
		hit->PushPMTHitEnergyVec(aStep->GetTotalEnergyDeposit());// not sure how useful this will be when PMT is not simulated properly
		hit->PushPMTHitWlenVec(wlen);/**/
		// these three aren't represented yet. can get from fID mapping. can get from PMT position too. can also use the index and dump these vectors
		/*hit->PushPMTXHitVec();
		hit->PushPMTYHitVec();
		hit->PushPMTZHitVec();/**/
		posDet = physVol->GetTranslation();
		fX = posDet[0];
		fY = posDet[1];
		fZ = posDet[2];
		// Debug Print if enabled -- relevant info should be in hit class
		if(debugMsg){
			G4cout << "Detector position: " << posDet << G4endl;
		}
		// initialize analysis manager and fill Ntuples
		G4AnalysisManager* Aman = G4AnalysisManager::Instance();
		// Get event number
		fEvt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
		// Fill Ntuple columns with photon information - to do: move this function to event manager after storing hit information in vectors
		Aman->FillNtupleIColumn(0, 0, fEvt);
		Aman->FillNtupleDColumn(0, 1, xpos);
		Aman->FillNtupleDColumn(0, 2, ypos);
		Aman->FillNtupleDColumn(0, 3, zpos);
		Aman->FillNtupleDColumn(0, 4, wlen);
		Aman->AddNtupleRow(0);
		// Fill Ntuple columns with sensitive detector hit information
		Aman->FillNtupleIColumn(1, 0, fEvt);
		Aman->FillNtupleIColumn(1, 1, fID);
		Aman->FillNtupleDColumn(1, 2, fX);
		Aman->FillNtupleDColumn(1, 3, fY);
		Aman->FillNtupleDColumn(1, 4, fZ);
		Aman->FillNtupleDColumn(1, 5, fT);
		Aman->AddNtupleRow(1);
	}
	// return value
	return true;
}
// Particle Name to ID number converter
G4int NuLatPMTSensitiveDetector::ParticleNameToIDNumber(G4String name)
{
	G4int num;
	if(name == "gamma"){
		num=1;
	}
	else if(name == "e-"){
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
