/*
	File: Nulat.cc
	Author: Brian Crow
	Date: 15AUG2023
	Description: This code is for the NuLat detector simulation with added NaI detector in coincidence. See README for notes.
	Version: 2.2.4 Trajectories and Simplified Hit Tracking Patch
	See README.md for change log of previous updates and patches.
*/
// Included Geant4 libriaries
#include "G4RunManager.hh"
#include "G4RunManagerFactory.hh"
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
		G4MTRunManager *rMan = new G4MTRunManager();
		// set mandatory initialization classes
		rMan->SetUserInitialization(new NuLatDetectorConstruction());
		rMan->SetUserInitialization(new NuLatPhysicsList());
		rMan->SetUserInitialization(new NuLatActionInitialization());
		// put "/run/numberOfThreads <N>" in macro file, where <N> is the number of cores to use in simulation
		// put "/run/initialize" in macro file
	#else
		// construct the default run manager
		G4RunManager *rMan = G4RunManagerFactory::CreateRunManager();
		// set mandatory initialization classes
		rMan->SetUserInitialization(new NuLatDetectorConstruction());
		rMan->SetUserInitialization(new NuLatPhysicsList());
		rMan->SetUserInitialization(new NuLatActionInitialization());
		// initialize G4 kernel if Geant4 environment is defined in single thread mode
		rMan->Initialize();
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
	G4VisManager *visMan = new G4VisExecutive();
	visMan->Initialize();
	// Draw particle by particle ID
	G4TrajectoryDrawByParticleID *model = new G4TrajectoryDrawByParticleID();
	// set track colors
	model->SetDefault("cyan");
	model->Set("gamma", "green");
	model->Set("e+", "blue");
	model->Set("e-", "red");
	model->Set("opticalphoton", G4Colour(0.0, 0.2, 0.8));
	// Register models and set trajectory models
	visMan->RegisterModel(model);
	visMan->SelectTrajectoryModel(model->Name());
	// get the pointer to the UI manager and define session
	G4UImanager *UIman = G4UImanager::GetUIpointer();
	// select interactive mode if UI is defined. Otherwise select batch mode:
	if(ui)
	{
		// open viewer, run interactive mode
		UIman->ApplyCommand(macCmd+macName);
		ui->SessionStart();	
	}
	else
	{
		// run in batch mode using command line to execute the specified macro. Let runtime environment handle macro exceptions
		macName=argv[1];
		UIman->ApplyCommand(macCmd+macName);
	}
	// job termination
	delete rMan;
	delete visMan;
	delete ui;
	return 0;
}
