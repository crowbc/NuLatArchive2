/*
	Nulat.cc
	Version: 2.1.0 - start of version tracking
	Author: Brian Crow
	Date: 23Sep2022
	This code is for the NuLat detector simulation with added NaI detector in coincidence. See README for notes.
*/
// Included C++ libraries
#include <iostream>
#include <fstream>
// Included Geant4 libriaries
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
// Included simulation libraries
#include "NuLatDetectorConstruction.hh"
#include "NuLatPhysics.hh"
#include "NuLatAction.hh"
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
		// Debug Message
		//G4cout << "Running in Multithreaded mode." << G4endl;
	#else
		// construct the default run manager
		G4RunManager *runManager = new G4RunManager();
		// set mandatory initialization classes
		runManager->SetUserInitialization(new NuLatDetectorConstruction());
		runManager->SetUserInitialization(new NuLatPhysicsList());
		runManager->SetUserInitialization(new NuLatActionInitialization());
		// initialize G4 kernel if Geant4 environment is defined in single thread mode
		runManager->Initialize();
		// Debug Message
		//G4cout << "Running in Single Thread mode." << G4endl;
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
