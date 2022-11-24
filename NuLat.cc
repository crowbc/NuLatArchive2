/*
	File: Nulat.cc
	Author: Brian Crow
	Date: 23Nov2022
	Description: This code is for the NuLat detector simulation with added NaI detector in coincidence. See README for notes.
	Version: 2.2.2 secondary tracks patch (23 Nov 2022)
	Added secondary track ID to scoring Ntuple. Moved scoring Ntuple for NuLat detector to NuLatSensDet.cc. Kept scoring Ntuple for NaI in NuLatEvent.cc 
	Changed the structure of N tuples to separate PMT, scoring, NuLat and NaI information. See NuLatRun.cc for structure changes.
	Added statements to NuLatEvent.cc to clear Hit vectors in order to fix memory leaks. Later update to remove some unused vectors
	Moved NaI housing farther in -z direction in NuLatDetectorConstruction. cc. This is to account for space occupied by aluminum divider plates outside the acrylic box.
	Moved source location in NuLatGenerator.cc to compensate for moving NaI detector.
	See README.md for change log of previous updates and patches.
*/
// Included Geant4 libriaries
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4TrajectoryDrawByParticleID.hh"
#include "G4UIExecutive.hh"
// Included simulation libraries
#include "NuLatDetectorConstruction.hh"
#include "NuLatPhysics.hh"
#include "NuLatAction.hh"
// Included C++ libraries
#include <iostream>
#include <fstream>
using namespace std;
// main() function
int main(int argc, char** argv)
{
	// define UI session
	G4UIExecutive *ui = 0;
	// conditional for starting runmanager in multithread mode
	#ifdef G4MULTITHREADED
		G4MTRunManager *runManager = new G4MTRunManager();
		// set mandatory initialization classes
		runManager->SetUserInitialization(new NuLatDetectorConstruction());
		runManager->SetUserInitialization(new NuLatPhysicsList());
		runManager->SetUserInitialization(new NuLatActionInitialization());
		// put "/run/numberOfThreads <N>" in macro file, where <N> is the number of cores to use in simulation
		// put "/run/initialize" in macro file
	#else
		// construct the default run manager
		G4RunManager *runManager = new G4RunManager();
		// set mandatory initialization classes
		runManager->SetUserInitialization(new NuLatDetectorConstruction());
		runManager->SetUserInitialization(new NuLatPhysicsList());
		runManager->SetUserInitialization(new NuLatActionInitialization());
		// initialize G4 kernel if Geant4 environment is defined in single thread mode
		runManager->Initialize();
	#endif
	// strings for initializing macros
	G4String macCmd = "/control/execute ";
	G4String macName = "init_vis.mac";
	// Set default UI if no command line arguments. Otherwise leave UI set to 0
	if(argc==1)
	{
		ui = new G4UIExecutive(argc, argv);
	}
	// construct and initialize the visualization manager
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	// Draw particle by particle ID
	G4TrajectoryDrawByParticleID *model = new G4TrajectoryDrawByParticleID();
	// set track colors
	model->SetDefault("cyan");
	model->Set("gamma", "green");
	model->Set("e+", "blue");
	model->Set("e-", "red");
	model->Set("opticalphoton", G4Colour(0.0, 0.2, 0.8));
	// Register models and set trajectory models
	visManager->RegisterModel(model);
	visManager->SelectTrajectoryModel(model->Name());
	// get the pointer to the UI manager and define session
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	// select interactive mode if UI is defined. Otherwise select batch mode:
	if(ui)
	{
		// open viewer, run interactive mode
		UImanager->ApplyCommand(macCmd+macName);
		ui->SessionStart();	
	}
	else
	{
		// run in batch mode using command line to execute the specified macro. Let runtime environment handle macro exceptions
		macName=argv[1];
		UImanager->ApplyCommand(macCmd+macName);
	}
	// job termination
	delete runManager;
	delete visManager;
	delete ui;
	return 0;
}
