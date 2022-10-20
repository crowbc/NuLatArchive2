// included header file
#include "NuLatVoxelHit.hh"
// Hit Allocator
G4ThreadLocal G4Allocator<NuLatVoxelHit>* NuLatVoxelHitAllocator=0;
// Constructor
NuLatVoxelHit::NuLatVoxelHit(): G4VHit(), fCellID(-1), eDep(0), fPos(0), fPLogV(0)
{}
// data structures
vector<G4int> NuLatVoxelHit::eDepParticleTypeIDNumber;
vector<G4double>  NuLatVoxelHit::eDepEDep;
vector<G4double>  NuLatVoxelHit::eDepXPosition;
vector<G4double>  NuLatVoxelHit::eDepYPosition;
vector<G4double>  NuLatVoxelHit::eDepZPosition;
vector<G4double>  NuLatVoxelHit::eDepTime;
vector<G4double>  NuLatVoxelHit::initialXMomentum;
vector<G4double>  NuLatVoxelHit::initialYMomentum;
vector<G4double>  NuLatVoxelHit::initialZMomentum;
// Constructor with parameter
NuLatVoxelHit::NuLatVoxelHit(G4int z): G4VHit(), fCellID(z), eDep(0), fPos(0), fPLogV(0)
{}
// Constructor with hit object
NuLatVoxelHit::NuLatVoxelHit(const NuLatVoxelHit &right):
G4VHit()
{
	fCellID = right.fCellID;
	eDep    = right.eDep;
	fPos    = right.fPos;
	fRot    = right.fRot;
	fPLogV  = right.fPLogV;
}
// Destructor
NuLatVoxelHit::~NuLatVoxelHit()
{}
// Operators
const NuLatVoxelHit& NuLatVoxelHit::operator= (const NuLatVoxelHit &right)
{
	fCellID  = right.fCellID;
	eDep     = right.eDep;
	fPos     = right.fPos;
	fRot     = right.fRot;
	fPLogV   = right.fPLogV;
	return *this;
}
int NuLatVoxelHit::operator==(const NuLatVoxelHit &right) const
{
	return (fCellID==right.fCellID);
}
// Draw() method
void NuLatVoxelHit::Draw()
{
	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
	if (pVVisManager&&(eDep>0.))
	{
		// Draw a calorimeter cell with a color corresponding to its energy deposit
		G4Transform3D trans(fRot.inverse(),fPos);
		G4VisAttributes attribs;
		const G4VisAttributes* pVA = fPLogV->GetVisAttributes();
		if (pVA) attribs = *pVA;
		G4double rcol = eDep/(100*keV);
		if (rcol>1.) rcol = 1.;
		if (rcol<0.4) rcol = 0.4;
		G4Colour colour(rcol,0.,0.);
		attribs.SetColour(colour);
		attribs.SetForceSolid(true);
		pVVisManager->Draw(*fPLogV,attribs,trans);
	}
}
// map fetcher
const std::map<G4String,G4AttDef>* NuLatVoxelHit::GetAttDefs() const
{
	G4bool isNew;
	std::map<G4String,G4AttDef>* store = G4AttDefStore::GetInstance("NuLatVoxelHit",isNew);
	if (isNew)
	{
		(*store)["HitType"]  = G4AttDef("HitType","Hit Type","Physics","","G4String");
		(*store)["Energy"] = G4AttDef("Energy", "Energy Deposited", "Physics", "G4BestUnit", "G4double");
		(*store)["Pos"] = G4AttDef("Pos", "Position", "Physics","G4BestUnit", "G4ThreeVector");
		(*store)["LVol"] = G4AttDef("LVol","Logical Volume","Physics","","G4String");
	}
	return store;
}
// value populator
std::vector<G4AttValue>* NuLatVoxelHit::CreateAttValues() const
{
	std::vector<G4AttValue>* values = new std::vector<G4AttValue>;
	values->push_back(G4AttValue("HitType","NuLatVoxelHit",""));
	values->push_back(G4AttValue("ID",G4UIcommand::ConvertToString(fCellID),""));   
	values->push_back(G4AttValue("Energy",G4BestUnit(eDep,"Energy"),""));
	values->push_back(G4AttValue("Pos",G4BestUnit(fPos,"Length"),""));
	if (fPLogV)
		values->push_back(G4AttValue("LVol",fPLogV->GetName(),""));
	else
		values->push_back(G4AttValue("LVol"," ",""));
	return values;
}
// Print() method
void NuLatVoxelHit::Print()
{
	// only print if feedback enabled
	if(fbOn)
	{
		G4cout << "  Cell[" << fCellID << "] " << eDep/MeV << " (MeV)" << G4endl;
	}
}
