# NuLat
This is a Geant4 simulation of a half-instrumented 5x5x5 unlithiated voxel NuLat Detector with a NaI detector connected externally for a coincidence trigger on Co-60 decay gammas. The purpose of this simulation is for calibration of each voxel in the unlithiated 5x5x5 array using energy reconstruction. This is also based on the original NuLat simulation which can be found at https://github.com/crowbc/NuLat_archive.git, and the NaI simulation which can be found at https://github.com/crowbc/NaI.git. All simulations in these repositories are written for Geant4 v11.1 (beta) and are not backwards compatible with older Geant4 builds than v11.0.

# build
The first build is just the basic 5x5x5 NuLat geometry with the acrylic side faces and light guides on the instrumented faces. The PMT's are sensitive volumes of air for the purpose of hit counting, and the voxels make up a scoring volume for total energy deposition only. Note: energy deposition is obtained in this build by getting total energy deposited for each event tracking step, and will overcount due to counting optical photons from scintillation.

# build2
The second build added the sodium iodide detector geometry centered on the -z face of the detector just outside the acrylic box containing the voxels. A sensitive air volume to simulate the NaI detector PMT was added and the scoring volume was set to the NaI detector, which is a single volume. The NuLat voxels will be re-configured as sensitive detectors to track energy depositions by location in the detector. This will serve as a theoretical value to compare with energy reconstruction from PMT counts in simulation and with PMT pulse integrals for the experimental setup.

Change Log:
2.2.2 MC Track Info Update (22 FEB 2023)
	test commit for updated token

2.2.1 - macros update (17 Nov 2022)
	Moved macro location to macros subdirectory. The cmake command still copies these to the binary directory, so run in batch mode by typing the macro name after ./NuLat like before
	Corrected issue in event manager that was causing segmentation fault when calling the GetPEHits() function from NuLatPMTHit.cc
	
2.2.0 NaI Hit Tracking Update (09 Nov 2022)
	Added Hit Class for NaI PMT to track hits independently from NuLat PMTs
	Populated separate N-tuples for NaI PMT hits and truth data
	Constructed separate PMT sensitive detector in detector construction (Note: NuLat and NaI PMT Hit classes are not fully implemented for simulating PMT hits)
	Corrected N-tuple columns in event manager to be in same order as created in run manager
	
2.1.1 - Voxel Hit Tracking Patch (04 Nov 2022)
	Corrected Event Manager to properly initialize sensitive detector and hit tracking classes
	Moving N-tuple filling to Event Manager planned for patch 2.2.1
	
2.1.0 - start of version tracking (23 Sep 2022)
	Added Hit Scoring classes for NuLat PMT's and NuLat Voxels
	Added Sensitive detector classes for NuLat PMT's and NuLat Voxels
	Set Generator to use a Co-60 source as the default when the particle is defined as a geantino
	Added Gaussian model for NaI scintillation component centered on 410 nm with FWHM of 110 nm
