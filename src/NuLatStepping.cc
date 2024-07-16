// user defined header file for class
#include "NuLatStepping.hh"
// Constructor
NuLatSteppingAction::NuLatSteppingAction(NuLatEventAction* eventAction)
{
	fEventAction = eventAction;
}
// Destructor
NuLatSteppingAction::~NuLatSteppingAction()
{}
// User Stepping Action - NaI scoring deprecated
void NuLatSteppingAction::UserSteppingAction(const G4Step* aStep)
{
	// Get volume from step, use to find scoring volume
	G4LogicalVolume *volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	const NuLatDetectorConstruction *detCons = static_cast<const NuLatDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	G4LogicalVolume *fNuLatScoringVolume = detCons->GetNuLatScoringVolume();
	// Get particle name and ID
	pName = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();
	pID = ParticleNameToIDNumber(pName);
	// initialize analysis manager to fill Ntuple columns
	G4AnalysisManager* Aman = G4AnalysisManager::Instance();
	// Add energy deposit if it's in the scoring volume, otherwise return without computing
	if((volume != fNuLatScoringVolume))
	{
		return;
	}
	if(volume == fNuLatScoringVolume)
	{
		// do not score optical photons - disabled
		/*if (pID==100)
			return;/**/
		// Get scoring from step and record
		eDepTot = aStep->GetTotalEnergyDeposit();
		Aman->FillNtupleDColumn(2, 4, eDepTot);
		return;
	}
}
// Particle Name to ID number converter
G4int NuLatSteppingAction::ParticleNameToIDNumber(G4String name)
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
