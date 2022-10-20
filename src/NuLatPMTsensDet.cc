// Header for user defined library
#include "NuLatPMTsensDet.hh"
// Constructor
NuLatPMTSensitiveDetector::NuLatPMTSensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}
// Destructor
NuLatPMTSensitiveDetector::~NuLatPMTSensitiveDetector()
{}
// Process Hits Function - not sure I can use this method if I'm looking at something other than gammas. It will work for the NaI coincidence tagging
G4bool NuLatPMTSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist)
{
	G4bool debugMsg = false;// set to true for debug messages
	G4Track *track = aStep->GetTrack();
	// only do this for optical photons to simulate the regime the PMT is actually sensitve to
	if (track->GetDefinition()->GetParticleName()=="opticalphoton")
	{
		track->SetTrackStatus(fStopAndKill);
		// set up step points. Get true photon position of PMT hit
		G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
		G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
		// Get Photon Position, Momentum and Wavelength (MC truth)
		G4ThreeVector posPhoton = preStepPoint->GetPosition();
		G4ThreeVector momPhoton = preStepPoint->GetMomentum();
		// Calculates wavelength in nm (change constant to change unit order of magnitude)
		G4double wlen = HCNM/momPhoton.mag();
		// Debug Print if enabled
		if(debugMsg)
		{
			G4cout << "Photon position: " << posPhoton << "; Photon wavelength: " << wlen << " nm" << G4endl;
		}
		// Get index of hit PMT
		const G4VTouchable *touch = aStep->GetPreStepPoint()->GetTouchable();
		G4int copyNo = touch->GetCopyNumber();
		// Debug Print if enabled
		if(debugMsg)
		{
			G4cout << "Copy number: " << copyNo << G4endl;
		}
		// Get position of hit PMT (not photon position)
		G4VPhysicalVolume *physVol = touch->GetVolume();
		G4ThreeVector posDet = physVol->GetTranslation();
		// Debug Print if enabled
		if(debugMsg)
		{
			G4cout << "Detector position: " << posDet << G4endl;
		}
		// initialize analysis manager and fill Ntuples
		G4AnalysisManager* man = G4AnalysisManager::Instance();
		// Get event number
		G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
		// Fill Ntuple columns with photon information
		man->FillNtupleIColumn(0, 0, evt);
		man->FillNtupleDColumn(0, 1, posPhoton[0]);
		man->FillNtupleDColumn(0, 2, posPhoton[1]);
		man->FillNtupleDColumn(0, 3, posPhoton[2]);
		man->FillNtupleDColumn(0, 4, wlen);
		man->AddNtupleRow(0);
		// Fill Ntuple columns with sensitive detector hit information
		man->FillNtupleIColumn(1, 0, evt);
		man->FillNtupleDColumn(1, 1, posDet[0]);
		man->FillNtupleDColumn(1, 2, posDet[1]);
		man->FillNtupleDColumn(1, 3, posDet[2]);
		// to do: add column for time
		man->FillNtupleIColumn(1, 4, copyNo);
		man->AddNtupleRow(1);
	}
	// return value
	return true;
}
