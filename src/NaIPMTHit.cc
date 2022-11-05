// included user defined header file
#include "NaIPMTHit.hh"
// Allocator
G4ThreadLocal G4Allocator<NaIPMTHit>* NaIPMTHitAllocator=0;
// Constructors
NaIPMTHit::NaIPMTHit() : G4VHit(), fPMTID(-1), peHits(0), fPos(0), fPLogV(0)
{}
vector<G4int> NaIPMTHit::PMTHitParticleIDVec;
vector<G4int> NaIPMTHit::PMTPEVec;
vector<G4int> NaIPMTHit::PMTXPEVec;
vector<G4int> NaIPMTHit::PMTYPEVec;
vector<G4int> NaIPMTHit::PMTZPEVec;
vector<G4double> NaIPMTHit::PMTHitWlenVec;
vector<G4double> NaIPMTHit::PMTHitEnergyVec;
vector<G4int> NaIPMTHit::PMTXHitVec;
vector<G4int> NaIPMTHit::PMTYHitVec;
vector<G4int> NaIPMTHit::PMTZHitVec;
vector<G4double> NaIPMTHit::PMTHitTimeVec;
NaIPMTHit::NaIPMTHit(G4int z) : G4VHit(), fPMTID(z), peHits(0), fPos(0), fPLogV(0)
{}
NaIPMTHit::NaIPMTHit(const NaIPMTHit &right) : G4VHit()
{
	fPMTID = right.fPMTID;
	peHits = right.peHits;
	fPos = right.fPos;
	fRot = right.fRot;
	fPLogV = right.fPLogV;
}
// Destructor
NaIPMTHit::~NaIPMTHit()
{}
// Operators
const NaIPMTHit& NaIPMTHit::operator=(const NaIPMTHit &right)
{
	fPMTID = right.fPMTID;
	peHits = right.peHits;
	fPos = right.fPos;
	fRot = right.fRot;
	fPLogV = right.fPLogV;
	return *this;
}
int NaIPMTHit::operator==(const NaIPMTHit &right) const
{
	return (fPMTID==right.fPMTID);
}
// Draw() function
void NaIPMTHit::Draw()
{
	G4VVisManager *pVVisManager = G4VVisManager::GetConcreteInstance();
	if(pVVisManager&&(peHits>0.))
	{
		// Draw a calorimeter cell with a color corresponding to its peHits deposit
		G4Transform3D trans(fRot.inverse(),fPos);
		G4VisAttributes atts;
		const G4VisAttributes *pVA = fPLogV->GetVisAttributes();
		if (pVA) atts = *pVA;
		G4double rcol = 2;
		if (rcol>1) rcol = 1.;
		if (rcol<0.4) rcol = 0.4;
		G4Colour colour(rcol, 0., 0.);
		atts.SetColour(colour);
		atts.SetForceSolid(true);
		pVVisManager->Draw(*fPLogV, atts, trans);
	}
}
// Functions for storage structures
const std::map<G4String,G4AttDef>* NaIPMTHit::GetAttDefs() const
{
	G4bool isNew;
	std::map<G4String,G4AttDef>* store = G4AttDefStore::GetInstance("NaIPMTHit",isNew);
	if(isNew)
	{
		(*store)["HitType"] = G4AttDef("HitType", "Hit Type", "Physics", "", "G4String");
		(*store)["peHits"] = G4AttDef("peHits", "peHits Deposited", "Physics", "G4BestUnit", "G4double");
		(*store)["Pos"] = G4AttDef("Pos", "Position", "Physics", "G4BestUnit", "G4ThreeVector");
		(*store)["LVol"] = G4AttDef("LVol", "Logical Volume", "Physics", "", "G4String");
	}
	return store;
}
std::vector<G4AttValue>* NaIPMTHit::CreateAttValues() const
{
	std::vector<G4AttValue>* values = new std::vector<G4AttValue>;
	values->push_back(G4AttValue("HitType","NaIPMTHit",""));
	values->push_back(G4AttValue("ID",G4UIcommand::ConvertToString(fPMTID),""));
	values->push_back(G4AttValue("peHits",G4BestUnit(peHits,"peHits"),""));
	values->push_back(G4AttValue("Pos",G4BestUnit(fPos,"Length"),""));
	if(fPLogV)
	{
		values->push_back(G4AttValue("LVol",fPLogV->GetName(),""));
	}
	else
	{
		values->push_back(G4AttValue("LVol"," ",""));
	}
	return values;
}
// Print() function
void NaIPMTHit::Print()
{
	// Print if feedback enabled
	if(fbOn)
	{
		G4cout << "PMT[" << fPMTID << "] hits: " << peHits << G4endl;
	}
}
