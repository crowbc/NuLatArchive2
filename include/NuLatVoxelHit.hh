// conditional to define the class only once
#ifndef NuLatVoxelHit_HH
#define NuLatVoxelHit_HH
// included Geant4 header files
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4LogicalVolume.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4UIcommand.hh"
// included C++ header files
#include "vector"
using namespace std;
// make the class
class NuLatVoxelHit : public G4VHit
{
public:
	// Constructors
	NuLatVoxelHit();
	NuLatVoxelHit(G4int z);
	NuLatVoxelHit(const NuLatVoxelHit &right);
	// Destructor
	~NuLatVoxelHit();
	// Operators
	const NuLatVoxelHit& operator=(const NuLatVoxelHit &right);
	int operator==(const NuLatVoxelHit &right) const;
	inline void *operator new(size_t);
	inline void operator delete(void *aHit);
	// Function Declarations
	virtual void Draw();
	virtual void Print();
	virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
	virtual std::vector<G4AttValue>* CreateAttValues() const;
	// Voxel ID methods
	void SetCellID(G4int z) { fCellID = z; }
	G4int GetCellID() const { return fCellID; }
	// Energy depositions
	void SetEdep(G4double de) { eDep = de; }
	void AddEdep(G4double de) { eDep += de; }
	G4double GetEdep() const { return eDep; }
	// Position of hit
	void SetPos(G4ThreeVector xyz) { fPos = xyz; }
	G4ThreeVector GetPos() const { return fPos; }
	void SetRot(G4RotationMatrix rmat) { fRot = rmat; }
	G4RotationMatrix GetRot() const { return fRot; }
	// Logical Volume of hit
	void SetLogV(G4LogicalVolume* vol) { fPLogV = vol; }
	const G4LogicalVolume* GetLogV() const { return fPLogV; }
	// functions for storing data in structures when a hit occurs
	void PushEDepParticleTypeIDNumber(G4int ID) { eDepParticleTypeIDNumber.push_back(ID); }
	void PushEDep(G4double de) { eDepEDep.push_back(de); }
	void PushEDepXPosition(G4double X) { eDepXPosition.push_back(X); }
	void PushEDepYPosition(G4double Y) { eDepYPosition.push_back(Y); }
	void PushEDepZPosition(G4double Z) { eDepZPosition.push_back(Z); }
	void PushEDepTime(G4double time) { eDepTime.push_back(time); }
	void PushInitialXMomentum(G4double pX) { initialXMomentum.push_back(pX); }
	void PushInitialYMomentum(G4double pY) { initialYMomentum.push_back(pY); }
	void PushInitialZMomentum(G4double pZ) { initialZMomentum.push_back(pZ); }
	// functions for fetching data structures
	std::vector<G4int> GetEDepParticleTypeIDNumberVector() { return  eDepParticleTypeIDNumber; }
	std::vector<G4double> GetEDepVector() { return  eDepEDep; }
	std::vector<G4double> GetEDepXPositionVector() { return  eDepXPosition; }
	std::vector<G4double> GetEDepYPositionVector() { return  eDepYPosition; }
	std::vector<G4double> GetEDepZPositionVector() { return  eDepZPosition; }
	std::vector<G4double> GetEDepTimeVector() { return  eDepTime; }
	std::vector<G4double> GetInitialXMomentumVector() { return  initialXMomentum; }
	std::vector<G4double> GetInitialYMomentumVector() { return  initialYMomentum; }
	std::vector<G4double> GetInitialZMomentumVector() { return  initialZMomentum; }
	// functions for clearing data storage structures
	void ClearEDepParticleTypeIDNumberVector() { eDepParticleTypeIDNumber.clear(); }
	void ClearEDepVector() { eDepEDep.clear(); }
	void ClearEDepXPositionVector() { eDepXPosition.clear(); }
	void ClearEDepYPositionVector() { eDepYPosition.clear(); }
	void ClearEDepZPositionVector() { eDepZPosition.clear(); }
	void ClearEDepTimeVector() { eDepTime.clear(); }
	void ClearInitialXMomentumVector() { initialXMomentum.clear(); }
	void ClearInitialYMomentumVector() { initialYMomentum.clear(); }
	void ClearInitialZMomentumVector() { initialZMomentum.clear(); }
private:
	// variable declarations
	G4int fCellID;
	G4double eDep;
	// storage structures
	static std::vector<G4int>  eDepParticleTypeIDNumber;
	static std::vector<G4double>  eDepEDep;
	static std::vector<G4double>  eDepXPosition;
	static std::vector<G4double>  eDepYPosition;
	static std::vector<G4double>  eDepZPosition;
	static std::vector<G4double>  eDepTime;
	static std::vector<G4double>  initialXMomentum;
	static std::vector<G4double>  initialYMomentum;
	static std::vector<G4double>  initialZMomentum;
	G4ThreeVector fPos;
	G4RotationMatrix fRot;
	const G4LogicalVolume* fPLogV;
};
typedef G4THitsCollection<NuLatVoxelHit> NuLatVoxelHitsCollection;
extern G4ThreadLocal G4Allocator<NuLatVoxelHit>* NuLatVoxelHitAllocator;
inline void* NuLatVoxelHit::operator new(size_t)
{
 	if (!NuLatVoxelHitAllocator)
		NuLatVoxelHitAllocator = new G4Allocator<NuLatVoxelHit>;
	return (void*)NuLatVoxelHitAllocator->MallocSingle();
}
inline void NuLatVoxelHit::operator delete(void* aHit)
{
	NuLatVoxelHitAllocator->FreeSingle((NuLatVoxelHit*) aHit);
}
// end of conditional to define the class only once
#endif
