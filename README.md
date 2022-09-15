# NuLatwNaI
This is a simulation of a half-instrumented 5x5x5 voxel NuLat Detector unlithiated with a NaI detector connected externally for a coincidence trigger on Co-60 decay gammas. The purpose of this simulation is for calibration of each voxel in the unlithiated 5x5x5 array using energy reconstruction. This is also based on the original NuLat simulation which can be found at https://github.com/crowbc/NuLat_archive.git, and the NaI simulation which can be found at https://github.com/crowbc/NaI.git. All simulations in these repositories are written for Geant4 v11.1 (beta) and are not backwards compatible with older Geant4 builds.

# build
The first build is just the basic 5x5x5 NuLat geometry with the acrylic side faces and light guides on the instrumented faces. The PMT's are sensitive volumes of air for the purpose of hit counting, and the voxels make up a scoring volume for total energy deposition only.

# build2
The second build added the sodium iodide detector geometry centered on the -z face of the detector just outside the acrylic box containing the voxels. A sensitive air volume to simulate the NaI detector PMT was added and the scoring volume was set to the NaI detector, which is a single volume. The NuLat voxels will be re-configured as sensitive detectors to track energy depositions by location in the detector. This will serve as a theoretical value to compare with energy reconstruction from PMT counts in simulation and with PMT pulse integrals for the experimental setup.
