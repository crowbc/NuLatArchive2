// start conditional to define class only once
#ifndef NULATRUN_HH
#define NULATRUN_HH
// Geant4 header files
#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
// C++ header files
#include <vector>
using namespace std;
// define the class
class NuLatRunAction : public G4UserRunAction
{
public:
	// Constructor and Destructor
	NuLatRunAction();
	~NuLatRunAction();
	// Vectors for voxel hit information
	std::vector<G4double> VoxEdepVec;
	std::vector<G4int> VoxPIDeDepVec;
	std::vector<G4double> xPosVoxEdepVec;
	std::vector<G4double> yPosVoxEdepVec;
	std::vector<G4double> zPosVoxEdepVec;
	std::vector<G4double> timeVoxEdepVec;
	// Vectors for PMT hit information
	std::vector<G4int> PMThitPIDVec;
	std::vector<G4int> PMThitPEVec;
	std::vector<G4double> PMThitWlenVec;
	std::vector<G4double> PMThitXposVec;
	std::vector<G4double> PMThitYposVec;
	std::vector<G4double> PMThitZposVec;
	std::vector<G4double> PMThitTimeVec;
	std::vector<G4double> PMThitPX0Vec;
	std::vector<G4double> PMThitPY0Vec;
	std::vector<G4double> PMThitPZ0Vec;
	// User Run actions
	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);
};
// end of conditional to define class only once
#endif
