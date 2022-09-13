#ifndef NULATPHYSICS_HH
#define NULATPHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

class NuLatPhysicsList : public G4VModularPhysicsList
{
public:
	NuLatPhysicsList();
	~NuLatPhysicsList();
};

#endif
