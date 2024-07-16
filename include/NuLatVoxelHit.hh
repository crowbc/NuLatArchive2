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
	void PushVoxEDepPIDVec(G4int ID) { voxEDepPIDVec.push_back(ID); }
	void PushEDep(G4double de) { voxEDepVec.push_back(de); }
	void PushxPosVoxEDepVec(G4double X) { xPosVoxEDepVec.push_back(X); }
	void PushyPosVoxEDepVec(G4double Y) { yPosVoxEDepVec.push_back(Y); }
	void PushzPosVoxEDepVec(G4double Z) { zPosVoxEDepVec.push_back(Z); }
	void PushtimeVoxEDepVec(G4double time) { timeVoxEDepVec.push_back(time); }
	void PushpX0VoxEDepVec(G4double pX) { pX0VoxEDepVec.push_back(pX); }
	void PushpY0VoxEDepVec(G4double pY) { pY0VoxEDepVec.push_back(pY); }
	void PushpZ0VoxEDepVec(G4double pZ) { pZ0VoxEDepVec.push_back(pZ); }
	// functions for fetching data structures
	std::vector<G4int> GetVoxEDepPIDVec() { return  voxEDepPIDVec; }
	std::vector<G4double> GetEDepVector() { return  voxEDepVec; }
	std::vector<G4double> GetxPosVoxEDepVec() { return  xPosVoxEDepVec; }
	std::vector<G4double> GetyPosVoxEDepVec() { return  yPosVoxEDepVec; }
	std::vector<G4double> GetzPosVoxEDepVec() { return  zPosVoxEDepVec; }
	std::vector<G4double> GettimeVoxEDepVec() { return  timeVoxEDepVec; }
	std::vector<G4double> GetpX0VoxEDepVec() { return  pX0VoxEDepVec; }
	std::vector<G4double> GetpY0VoxEDepVec() { return  pY0VoxEDepVec; }
	std::vector<G4double> GetpZ0VoxEDepVec() { return  pZ0VoxEDepVec; }
	// functions for clearing data storage structures
	void ClearvoxEDepPIDVec() { voxEDepPIDVec.clear(); }
	void ClearEDepVec() { voxEDepVec.clear(); }
	void ClearxPosVoxEDepVec() { xPosVoxEDepVec.clear(); }
	void ClearyPosVoxEDepVec() { yPosVoxEDepVec.clear(); }
	void ClearzPosVoxEDepVec() { zPosVoxEDepVec.clear(); }
	void CleartimeVoxEDepVec() { timeVoxEDepVec.clear(); }
	void ClearpX0VoxEDepVec() { pX0VoxEDepVec.clear(); }
	void ClearpY0VoxEDepVec() { pY0VoxEDepVec.clear(); }
	void ClearpZ0VoxEDepVec() { pZ0VoxEDepVec.clear(); }
private:
	// variable declarations
	G4int fCellID;
	G4double eDep;
	G4bool fbOn = true;
	// storage structures
	static std::vector<G4int>  voxEDepPIDVec;
	static std::vector<G4double>  voxEDepVec;
	static std::vector<G4double>  xPosVoxEDepVec;
	static std::vector<G4double>  yPosVoxEDepVec;
	static std::vector<G4double>  zPosVoxEDepVec;
	static std::vector<G4double>  timeVoxEDepVec;
	static std::vector<G4double>  pX0VoxEDepVec;
	static std::vector<G4double>  pY0VoxEDepVec;
	static std::vector<G4double>  pZ0VoxEDepVec;
	G4ThreeVector fPos;
	G4RotationMatrix fRot;
	const G4LogicalVolume *fPLogV;
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
