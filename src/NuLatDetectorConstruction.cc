// Included header files written for simulation
#include "NuLatDetectorConstruction.hh"
// Constructor
NuLatDetectorConstruction::NuLatDetectorConstruction()
{
	// Set Parameter Default Values - to do: set default values in the messenger
	xVoxels = 5;
	yVoxels = 5;
	zVoxels = 5;
	// default geometry dimensions
	xVoxelSize = 2.495*in;
	yVoxelSize = 2.495*in;
	zVoxelSize = 2.495*in;
	xVoxelSpace = 0.005*in;
	yVoxelSpace = 0.005*in;
	zVoxelSpace = 0.005*in;
	// default PMT and light guide (LG) dimensions - PMT dimensions determined by manufacturer, Hamamatsu (type H-10534)
	lenPMT = 200.*mm;
	lenLGTaper = 35.*mm;
	lenLGSqu = 5.*mm;
	lenLGwPMT = lenPMT+lenLGTaper+lenLGSqu;
	xVCBoxSize = xVoxels*(xVoxelSize+xVoxelSpace)+xVoxelSpace;
	yVCBoxSize = yVoxels*(yVoxelSize+yVoxelSpace)+yVoxelSpace;
	zVCBoxSize = zVoxels*(zVoxelSize+zVoxelSpace)+zVoxelSpace;
	// Set world volume to needed size
	xWorld = 2*xVCBoxSize;
	yWorld = 2*yVCBoxSize;
	zWorld = 2*zVCBoxSize;
	Li6doped = false;// Doping of cubes not implemented
	// Li-6 dopant fractional mass (default was 0.5% in old simulation code)
	massfracLi6 = 0.5*perCent;
	// Acrylic side plate thickness
	tAcrylicPanel = 0.0625*in;
	// Define the messenger and declare properties
	fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");//set up /voxel and other subdirectories
	fMessenger->DeclareProperty("xVoxels", xVoxels, "Number of voxels (cubes) in the x-dimension");
	fMessenger->DeclareProperty("yVoxels", yVoxels, "Number of voxels (cubes) in the y-dimension");
	fMessenger->DeclareProperty("zVoxels", zVoxels, "Number of voxels (cubes) in the z-dimension");
	//fMessenger->DeclareProperty("Li6doped", Li6doped, "Toggle Li-6 doping in PVT voxels (Off by default)");// uncomment when implemented
	//fMessenger->DeclareProperty("massfracLi6", massfracLi6, "Mass fraction of Li-6 doping in PVT (0.5*perCent by default)");// uncomment when implemented
	// Define Detector Construction Materials
	DefineMaterials();
}
// Destructor
NuLatDetectorConstruction::~NuLatDetectorConstruction()
{}
// DefineMaterials function
void NuLatDetectorConstruction::DefineMaterials()
{
	// Boolean to toggle debug messages
	debugMsg = false;
	if(debugMsg){
		// Strings for debug messages
		G4String wlenNMStr = "Wavelength (nm:) ";
		G4String eStr = "; Energy (eV:) ";
	}
	G4NistManager *nist = G4NistManager::Instance();
	// size_t variable for property array lengths
	const size_t nI = 182;
	// Photon energy range for energy dependent material responses - corresponds to a range of 220 nm to 609 nm
	G4double photonEnergy[nI] = {
		2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV, 2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV, 2.341*eV, 2.386*eV, //10
		2.433*eV, 2.481*eV, 2.487*eV, 2.496*eV, 2.506*eV, 2.516*eV, 2.524*eV, 2.531*eV, 2.539*eV, 2.547*eV, //20
		2.554*eV, 2.561*eV, 2.569*eV, 2.577*eV, 2.586*eV, 2.595*eV, 2.605*eV, 2.614*eV, 2.622*eV, 2.630*eV, //30
		2.638*eV, 2.646*eV, 2.653*eV, 2.660*eV, 2.669*eV, 2.676*eV, 2.681*eV, 2.688*eV, 2.693*eV, 2.698*eV, //40
		2.703*eV, 2.706*eV, 2.711*eV, 2.718*eV, 2.723*eV, 2.731*eV, 2.742*eV, 2.755*eV, 2.768*eV, 2.782*eV, //50
		2.793*eV, 2.803*eV, 2.811*eV, 2.819*eV, 2.829*eV, 2.837*eV, 2.845*eV, 2.853*eV, 2.860*eV, 2.867*eV, //60
		2.875*eV, 2.882*eV, 2.888*eV, 2.894*eV, 2.900*eV, 2.907*eV, 2.913*eV, 2.919*eV, 2.924*eV, 2.930*eV, //70
		2.937*eV, 2.942*eV, 2.948*eV, 2.954*eV, 2.960*eV, 2.968*eV, 2.976*eV, 2.983*eV, 2.991*eV, 3.001*eV, //80
		3.008*eV, 3.017*eV, 3.028*eV, 3.038*eV, 3.048*eV, 3.055*eV, 3.070*eV, 3.087*eV, 3.103*eV, 3.121*eV, //90
		3.138*eV, 3.155*eV, 3.173*eV, 3.191*eV, 3.220*eV, 3.250*eV, 3.281*eV, 3.313*eV, 3.344*eV, 3.375*eV, //100
		3.403*eV, 3.439*eV, 3.479*eV, 3.522*eV, 3.566*eV, 3.611*eV, 3.644*eV, 3.684*eV, 3.731*eV, 3.780*eV, //110
		3.831*eV, 3.868*eV, 3.892*eV, 3.910*eV, 3.921*eV, 3.934*eV, 3.946*eV, 3.957*eV, 3.970*eV, 3.994*eV, //120
		4.044*eV, 4.102*eV, 4.160*eV, 4.202*eV, 4.236*eV, 4.267*eV, 4.298*eV, 4.328*eV, 4.357*eV, 4.387*eV, //130
		4.422*eV, 4.455*eV, 4.494*eV, 4.563*eV, 4.607*eV, 4.616*eV, 4.624*eV, 4.627*eV, 4.628*eV, 4.633*eV, //140
		4.640*eV, 4.642*eV, 4.649*eV, 4.656*eV, 4.661*eV, 4.666*eV, 4.678*eV, 4.685*eV, 4.692*eV, 4.699*eV, //150
		4.706*eV, 4.713*eV, 4.720*eV, 4.727*eV, 4.740*eV, 4.751*eV, 4.763*eV, 4.775*eV, 4.788*eV, 4.798*eV, //160
		4.813*eV, 4.828*eV, 4.840*eV, 4.853*eV, 4.869*eV, 4.886*eV, 4.905*eV, 4.928*eV, 4.953*eV, 5.015*eV, //170
		5.099*eV, 5.143*eV, 5.174*eV, 5.202*eV, 5.235*eV, 5.265*eV, 5.294*eV, 5.330*eV, 5.413*eV, 5.493*eV, //180
		5.556*eV, 5.611*eV}; //182
	G4double wlenNM[nI];
	// Fast scintillation properties, no reference and were here with the original file Materials.hh (find a reference for using this)
	// Possible reference match: graph found on Eljen's website for EJ-200 iight curve
	// note: maximum transmission at 425 nm wavelength confirmed. See photon_energy_wlens.ods for detailed matching of fc to wavelength
	// note: fcEJ200 table may need to be built piecewise (see graph file EJ-200_emspec.png)
	G4double scEJ200[nI] = {
		0.000,  0.000,  0.000,  0.000,  0.000,  0.010,  0.020,  0.035,  0.050,  0.060, //10
		0.070,  0.085,  0.090,  0.095,  0.098,  0.100,  0.110,  0.120,  0.130,  0.140, //20
		0.150,  0.160,  0.170,  0.180,  0.200,  0.220,  0.240,  0.250,  0.270,  0.290, //30  
		0.300,  0.320,  0.340,  0.350,  0.360,  0.390,  0.400,  0.420,  0.430,  0.440, //40  
		0.445,  0.450,  0.460,  0.470,  0.480,  0.500,  0.550,  0.600,  0.630,  0.700, //50  
		0.730,  0.750,  0.800,  0.830,  0.850,  0.870,  0.900,  0.920,  0.940,  0.950, //60  
		0.960,  0.970,  0.980,  0.985,  0.990,  0.995,  1.000,  1.000,  1.000,  0.995, //70  
		0.990,  0.985,  0.980,  0.970,  0.960,  0.930,  0.900,  0.870,  0.850,  0.800, //80 
		0.700,  0.600,  0.500,  0.400,  0.300,  0.220,  0.130,  0.070,  0.010,  0.000, //90  
		0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //100
		0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //110  
		0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //120  
		0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //130  
		0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //140  
		0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //150  
		0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //160  
		0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //170  
		0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //180  
		0.000,  0.000}; //182
	// Arrays for material properties
	G4double rindexAir[nI];
	// Comment in Materials.hh of original NuLat code for acrylic...
	// 2012 J. Phys.: Conf. Ser. 356 012049 for acrylic optical properties - note: this reference is for films, not bulk material
	G4double rindexAcrylic[nI];
	G4double aLenAcrylic[nI];
	// See PVTproperties.txt for notes on material property tables used in this simulation
	G4double rindexPVT[nI];
	G4double aLenPVT[nI];
	G4double reflSS[nI];
	G4double reflAl[nI];
	// PMT material properties variables
	// Mu-metal Surface Properties
	G4double reflMuMetal[nI], effMuMetal[nI], specularLopeMuMetal[nI], specularSpikeMuMetal[nI], backscatterMuMetal[nI];
	G4double rindexBeCuPhotoCath[nI], aLenBeCuPhotoCath[nI];
	G4double rindexBorosilicateGlass[nI], aLenBorosilicateGlass[nI];
	// Define Elements
	H = nist->FindOrBuildElement("H");
	Be = nist->FindOrBuildElement("Be");
	C = nist->FindOrBuildElement("C");
	O = nist->FindOrBuildElement("O");
	//Na = nist->FindOrBuildElement("Na");
	Si = nist->FindOrBuildElement("Si");/**/
	Cr = nist->FindOrBuildElement("Cr");
	Fe = nist->FindOrBuildElement("Fe");
	Ni = nist->FindOrBuildElement("Ni");
	Cu = nist->FindOrBuildElement("Cu");
	Mo = nist->FindOrBuildElement("Mo");
	/*I = nist->FindOrBuildElement("I");
	Tl = nist->FindOrBuildElement("Tl");/**/
	Pb = nist->FindOrBuildElement("Pb");
	// Define Materials
	air = nist->FindOrBuildMaterial("G4_AIR");
	vacuum = nist->FindOrBuildMaterial("G4_GALACTIC");
	//PVT = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
	EJ200 = new G4Material("EJ200", rhoEJ200, 2);
	EJ200->AddElement(C, Cfrac_EJ200*100*perCent);
	EJ200->AddElement(H, Hfrac_EJ200*100*perCent);
	aluminum = nist->FindOrBuildMaterial("G4_Al");
	stainless = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
	lead = nist->FindOrBuildMaterial("G4_Pb");
	acrylic = new G4Material("acrylic", rhoAcrylic, 3);
	acrylic->AddElement(O, 2);
	acrylic->AddElement(C, 5);
	acrylic->AddElement(H, 8);
	// PMT metal materials
	muMetal = new G4Material("muMetal", 8.77*g/cm3, 4);
	muMetal->AddElement(Fe, 16.*perCent);
	muMetal->AddElement(Ni, 77.*perCent);
	muMetal->AddElement(Cu, 5.*perCent);
	muMetal->AddElement(Mo, 2.*perCent);
	BeCuPhotoCath = new G4Material("BeCuPhotoCath", 5./50000*g/cm3, 2);
	BeCuPhotoCath->AddElement(Be, 1);
	BeCuPhotoCath->AddElement(Cu, 1);/**/
	// Set Material Properties
	for (size_t i = 0; i<nI; i++){
		// Calculate wavelength (in nm) from photon energy
		wlenNM[i] = HCNM/photonEnergy[i];// Energy is input directly above. Note: energy is displayed as a factor of 1E-06 too small in the G4cout statement!
		rindexAir[i] = 1.;
		rindexAcrylic[i] = 1.492;// taken from Materials.hh
		aLenAcrylic[i] = 10.*m;// taken from Materials.hh - look for correct values
		rindexPVT[i] = 1.58;
		aLenPVT[i] = 380.0*cm;// note: the Materials.hh header has this at 90 cm with a note that it needs to be tuned. 380 cm is also the attenuation length mentioned in chapter 8 of Knoll
		reflAl[i] = 0.95;// taken from Materials.hh - look for correct values (approximately true for polished Al in the wavelengths we're concerned with)
		reflSS[i] = 1.0;// look for correct values for ~ 300 - 600 nm range
		// PMT properties -- Disable block comment to toggle on
		reflMuMetal[i] = 0.0;// taken from Materials.hh - look for correct values
		effMuMetal[i] = 0.;// taken from Materials.hh - look for correct values
		specularLopeMuMetal[i] = 0.0;// taken from Materials.hh - look for correct values
		specularSpikeMuMetal[i] = 0.;// taken from Materials.hh - look for correct values
		backscatterMuMetal[i] = 0.0;// taken from Materials.hh - look for correct values
		rindexBeCuPhotoCath[i] = 2.7;// taken from Materials.hh
		aLenBeCuPhotoCath[i] = 0.001*mm;// taken from Materials.hh
		rindexBorosilicateGlass[i] = 1.55;// taken from Materials.hh - look for dispersion formula
		aLenBorosilicateGlass[i] = 10.*m;// taken from Materials.hh
		/**/
		// TODO: find more efficient method of enable/disable debug feedback
		/*if(debugMsg)
		{
			G4cout << wlenNMStr << wlenNM[i] << eStr << photonEnergy[i]*1E06 << G4endl;
		}/**/
	}
	// Declare material properties tables and populate with values. Assign tables to materials
	mptAir = new G4MaterialPropertiesTable();
	mptAir->AddProperty("RINDEX", photonEnergy, rindexAir, nI);
	air->SetMaterialPropertiesTable(mptAir);
	mptAcrylic = new G4MaterialPropertiesTable();
	mptAcrylic->AddProperty("RINDEX", photonEnergy, rindexAcrylic, nI);
	mptAcrylic->AddProperty("ABSLENGTH", photonEnergy, aLenAcrylic, nI);
	acrylic->SetMaterialPropertiesTable(mptAcrylic);
	mptPVT = new G4MaterialPropertiesTable();
	mptPVT->AddProperty("RINDEX", photonEnergy, rindexPVT, nI);
	mptPVT->AddProperty("ABSLENGTH", photonEnergy, aLenPVT, nI);
	mptPVT->AddProperty("SCINTILLATIONCOMPONENT1", photonEnergy, scEJ200, nI, true);
	mptPVT->AddConstProperty("SCINTILLATIONYIELD", scintYieldPVT);
	mptPVT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", stcEJ200);
	mptPVT->AddConstProperty("SCINTILLATIONRISETIME1", srtEJ200);
	mptPVT->AddConstProperty("RESOLUTIONSCALE", 1.0);
	mptPVT->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
	//PVT->SetMaterialPropertiesTable(mptPVT);
	EJ200->SetMaterialPropertiesTable(mptPVT);
	mptAl = new G4MaterialPropertiesTable();
	mptAl->AddProperty("REFLECTIVITY", photonEnergy, reflAl, nI);
	aluminum->SetMaterialPropertiesTable(mptAl);/**/
	mptSS = new G4MaterialPropertiesTable();
	mptSS->AddProperty("REFLECTIVITY", photonEnergy, reflSS, nI);
	stainless->SetMaterialPropertiesTable(mptSS);
	// Phototube mu Metal and photocathode MPT's - disable block comment to use
	mptMuMetalSurface = new G4MaterialPropertiesTable();
	mptMuMetalSurface->AddProperty("REFLECTIVITY", photonEnergy, reflMuMetal, nI);   //overall
	mptMuMetalSurface->AddProperty("SPECULARLOBECONSTANT", photonEnergy, specularLopeMuMetal, nI);   //normal of micro-facet
	mptMuMetalSurface->AddProperty("SPECULARSPIKECONSTANT", photonEnergy, specularSpikeMuMetal, nI);   //mirror
	mptMuMetalSurface->AddProperty("BACKSCATTERCONSTANT", photonEnergy, backscatterMuMetal, nI);   //backscatter
	mptMuMetalSurface->AddProperty("EFFICIENCY",photonEnergy,effMuMetal, nI);
	muMetal->SetMaterialPropertiesTable(mptMuMetalSurface);
	mptBeCuPhotoCath = new G4MaterialPropertiesTable();
	mptBeCuPhotoCath->AddProperty("RINDEX", photonEnergy, rindexBeCuPhotoCath, nI);
	mptBeCuPhotoCath->AddProperty("ABSLENGTH", photonEnergy, aLenBeCuPhotoCath, nI);
	BeCuPhotoCath->SetMaterialPropertiesTable(mptBeCuPhotoCath);
	// optical surface properties
	AlSurface = new G4OpticalSurface("AlSurface");
	AlSurface->SetType(dielectric_metal);
	AlSurface->SetFinish(ground);
	AlSurface->SetModel(unified);
	AlSurface->SetMaterialPropertiesTable(mptAl);
	SSSurface = new G4OpticalSurface("SSSurface");
	SSSurface->SetType(dielectric_metal);
	SSSurface->SetFinish(ground);
	SSSurface->SetModel(unified);
	SSSurface->SetMaterialPropertiesTable(mptSS);
}
// Voxelated Array Constructor
void NuLatDetectorConstruction::BuildVCBox()
{
	// Define position variables
	G4double xPos, yPos, zPos;
	// Define Visual Attributes object for adjusting coloring and visibility of various components
	attr = new G4VisAttributes(G4Colour(0.9,0.0,0.0,0.05));
	// Define Calorimeter
	solidVCBox = new G4Box("solidVCBox", xVCBoxSize/2, yVCBoxSize/2, zVCBoxSize/2);
	logicVCBox = new G4LogicalVolume(solidVCBox, air, "logicVCBox");
	// make VCBox red in color
	logicVCBox->SetVisAttributes(attr);
	physVCBox = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicVCBox, "physVCBox", logicWorld, false, 0, true);
	// Do Voxel Parameterization
	solidVoxel = new G4Box("solidVoxel", xVoxelSize/2, yVoxelSize/2, zVoxelSize/2);
	logicVoxel = new G4LogicalVolume(solidVoxel, EJ200, "logicVoxel");
	// make yellow colored voxels
	attr = new G4VisAttributes(G4Colour(0.9,0.9,0.0,0.4));
	logicVoxel->SetVisAttributes(attr);
	// Set NuLat voxel as NuLat scoring volume
	fNuLatScoringVolume = logicVoxel;
	// for loop to create 5X5X5 array of Voxel Physical Volumes; TODO: use parameterized volume
	for(G4int k=0; k<zVoxels; k++)
	{
		zPos = (k+1.)*zVoxelSpace+(k+0.5)*zVoxelSize-zVCBoxSize/2;
		for(G4int j=0; j<yVoxels; j++)
		{
			yPos = (j+1.)*yVoxelSpace+(j+0.5)*yVoxelSize-yVCBoxSize/2;
			for(G4int i=0; i<xVoxels; i++)
			{
				xPos = (i+1.)*xVoxelSpace+(i+0.5)*xVoxelSize-xVCBoxSize/2;
				physVoxel = new G4PVPlacement(0, G4ThreeVector(xPos, yPos, zPos), logicVoxel, "physVoxel", logicVCBox, false, i+j*xVoxels+k*xVoxels*yVoxels, true);
			}
		}
	}
}
// Acrylic Box constructor
void NuLatDetectorConstruction::BuildAcrylicBox()
{
	// Define and build acrylic side panels - to do: redefine as trapezoidal solids using single volume and set rotation matrices. Set trapzoids in positions so bevels touch
	attr = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.2));
	// Define variables and vectors to construct rotation matrix
	G4double phi = 90*deg;
	G4ThreeVector u = G4ThreeVector(0., 0., 1.);
	G4ThreeVector v = G4ThreeVector(-std::sin(phi), std::cos(phi), 0);
	G4ThreeVector w = G4ThreeVector(std::cos(phi), std::sin(phi), 0);
	// Define Rotation Matrices
	G4RotationMatrix *yRot = new G4RotationMatrix(u, v, w);
	G4RotationMatrix *zRot = new G4RotationMatrix(u, w, -v);
	// Define volume for acrilic box plates
	solidAcrylicPanel = new G4Box("solidAcrylicPanel", tAcrylicPanel, yVCBoxSize/2, zVCBoxSize/2);
	logicAcrylicPanel = new G4LogicalVolume(solidAcrylicPanel, acrylic, "logicAcrylicPanel");
	logicAcrylicPanel->SetVisAttributes(attr);
	G4double xPos = xVCBoxSize/2+tAcrylicPanel;
	G4double yPos = yVCBoxSize/2+tAcrylicPanel;
	G4double zPos = zVCBoxSize/2+tAcrylicPanel;
	physAcrylicPanel = new G4PVPlacement(0, G4ThreeVector(xPos, 0., 0.), logicAcrylicPanel, "physAcrylicPanel", logicWorld, false, 0, true);
	physAcrylicPanel = new G4PVPlacement(0, G4ThreeVector(-xPos, 0., 0.), logicAcrylicPanel, "physAcrylicPanel", logicWorld, false, 1, true);
	physAcrylicPanel = new G4PVPlacement(yRot, G4ThreeVector(0., yPos, 0.), logicAcrylicPanel, "physAcrylicPanel", logicWorld, false, 2, true);
	physAcrylicPanel = new G4PVPlacement(yRot, G4ThreeVector(0., -yPos, 0.), logicAcrylicPanel, "physAcrylicPanel", logicWorld, false, 3, true);
	physAcrylicPanel = new G4PVPlacement(zRot, G4ThreeVector(0., 0., zPos), logicAcrylicPanel, "physAcrylicPanel", logicWorld, false, 4, true);
	physAcrylicPanel = new G4PVPlacement(zRot, G4ThreeVector(0., 0., -zPos), logicAcrylicPanel, "physAcrylicPanel", logicWorld, false, 5, true);
}
//  Light Guide with PMT constructor
void NuLatDetectorConstruction::BuildLGandPMT()
{
	// Define Visual Attributes object for adjusting coloring and visibility of various components
	G4double dx1 = xVoxelSize+xVoxelSpace-0.05*in;
	G4double dx2 = 46.*mm;
	G4double dy1 = yVoxelSize+yVoxelSpace-0.05*in;
	G4double dy2 = 46.*mm;
	G4double dz = lenLGTaper;
	G4double xPos, yPos, zPos;
	// Declace rotation angle
	G4double phi = 90*deg;
	// Declare vectors to construct rotation matrices
	G4ThreeVector u = G4ThreeVector(0, 0, -1);
	G4ThreeVector v = G4ThreeVector(-std::sin(phi), std::cos(phi), 0);
	G4ThreeVector w = G4ThreeVector(std::cos(phi), std::sin(phi), 0);
	// Declare rotation matrices to use for LG's and PMT sensitive volumes, with yRot rotating to the -yface
	G4RotationMatrix *xRot = new G4RotationMatrix(-u, v, w);
	G4RotationMatrix *yRot = new G4RotationMatrix(v, u, w);
	// Define the trapezoidal solid and cone solid for the light guides
	solidLGTrd = new G4Trd("solidLGTrd", dx1/2, dx2/2, dy1/2, dy2/2, dz/2);
	G4double r1 = 3.465*in/2;
	G4double r2 = 1.811*in/2;
	solidLGCone = new G4Cons("solidLGCone", 0.*cm, r1, 0.*cm, r2, dz/2, 0, 360*deg);
	// Define the light guide from the intersection of the two solids defined above
	solidLG = new G4IntersectionSolid("solidLG", solidLGTrd, solidLGCone);
	logicLG = new G4LogicalVolume(solidLG, acrylic, "logicLG");
	// make these orange just to stand out
	attr = new G4VisAttributes(G4Colour(0.7,0.3,0.0,0.4));
	logicLG->SetVisAttributes(attr);
	// stainless steel plate
	/*solidSSPlate = new G4Box("solidSSPlate", xdim, ydim, zdim);
	solidSSPlateHole = new G4Tubs("solidSSPlateHole", 0, router, 0., 360.*deg);
	solidSSPanel = new G4SubtractionSolid("solidSSPanel", solidSSPlate, solidSSPlateHole, params);
	logicSSPanel = new G4LogicalVolume(solidSSPanel, stainless, "logicSSPanel");
	// make PMT plates gray
	attr = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.5));
	logicSSPMTPlate->SetVisAttributes(attr);/**/
	// Aluminum dividers - do not use Jack's code for this! Overlaps abound!
	/*solidAlDivPlate = new G4Trd("solidAlDivPlate", xVCBoxSize/2, xVCBoxSize/2, yVoxelSpace/2, yVoxelSpace/2, lenLGwPMT/2-1*in);// change second (upper) x dimension to aluminum sidewall width/2
	solidAlDivCut = new G4Box("solidAlDivCut", xVoxelSpace/2, yVoxelSpace/2, lenLGwPMT/4-0.5*in);
	solidAlDivOuter = new G4Box("solidAlDivOuter", dx1/2 + 0.025*in, dy1/2 + 0.025*in, 6.5*in/2);// dx1=xVoxelSize+xVoxelSpace-0.127*cm; dy1=yVoxelSize+yVoxelSpace-0.127*cm
	solidAlDivInner = new G4Box("solidAlDivInner", dx1/2, dy1/2, 6.5*in/2);
	solidAlDiv = new G4SubtractionSolid("solidAlDiv", solidAlDivOuter, solidAlDivInner, 0, G4ThreeVector(0., 0., 0.));
	logicAlDiv = new G4LogicalVolume(solidSSDiv, aluminum, "logicAlDiv");/**/
	// make divider plates light gray
	/*attr = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.7));
	logicAlDiv->SetVisAttributes(attr);/**/
	// make +z light guides
	zPos = zVCBoxSize/2+2*tAcrylicPanel+dz/2;
	for (G4int i=0; i<xVoxels; i++)
	{
		xPos = -xVCBoxSize/2+i*(xVoxelSize+xVoxelSpace)+xVoxelSpace+xVoxelSize/2;
		for(G4int j=0; j<yVoxels; j++)
		{
			yPos = -yVCBoxSize/2+j*(yVoxelSize+yVoxelSpace)+yVoxelSpace+yVoxelSize/2;
			physLG = new G4PVPlacement(0, G4ThreeVector(xPos, yPos, zPos), logicLG, "physLG", logicWorld, false, i*yVoxels+j, true);
			//physAlDiv = new G4PVPlacement(0, G4ThreeVector(xPos, yPos, zPos + 58.7*mm), logicSSDiv, "physSSDiv", logicWorld, false, i*yVoxels+j, true);
		}
	}
	// make +x light guides
	xPos = xVCBoxSize/2+2*tAcrylicPanel+dz/2;
	for (G4int i=0; i<yVoxels; i++)
	{
		yPos = -yVCBoxSize/2+i*(yVoxelSize+yVoxelSpace)+yVoxelSpace+yVoxelSize/2;
		for(G4int j=0; j<zVoxels; j++)
		{
			zPos = -zVCBoxSize/2+j*(zVoxelSize+zVoxelSpace)+zVoxelSpace+zVoxelSize/2;
			physLG = new G4PVPlacement(xRot, G4ThreeVector(xPos, yPos, zPos), logicLG, "physLG", logicWorld, false, i*zVoxels+j+xVoxels*yVoxels, true);
			//physAlDiv = new G4PVPlacement(xRot, G4ThreeVector(xPos + 58.7*mm, yPos, zPos), logicSSDiv, "physSSDiv", logicWorld, false, i*zVoxels+j+xVoxels*yVoxels, true);
		}
	}
	// make -y light guides
	yPos = -yVCBoxSize/2-2*tAcrylicPanel-dz/2;
	for (G4int i=0; i<xVoxels; i++)
	{
		xPos = -xVCBoxSize/2+i*(xVoxelSize+xVoxelSpace)+xVoxelSpace+xVoxelSize/2;
		for(G4int j=0; j<zVoxels; j++)
		{
			zPos = -zVCBoxSize/2+j*(zVoxelSize+zVoxelSpace)+zVoxelSpace+zVoxelSize/2;
			physLG = new G4PVPlacement(yRot, G4ThreeVector(xPos, yPos, zPos), logicLG, "physLG", logicWorld, false, i*zVoxels+j+xVoxels*yVoxels+yVoxels*zVoxels, true);
			//physAlDiv = new G4PVPlacement(yRot, G4ThreeVector(xPos, yPos + 58.7*mm, zPos), logicSSDiv, "physSSDiv", logicWorld, false, i*zVoxels+j+xVoxels*yVoxels+yVoxels*zVoxels, true);
		}
	}
	// Define PMT's
	solidPMT = new G4Tubs("solidPMT", 0, r2, lenPMT/2, 0, 360*deg);
	logicPMT = new G4LogicalVolume(solidPMT, air, "logicPMT");
	// make PMT volumes purple cylinders
	attr = new G4VisAttributes(G4Colour(0.5,0.0,0.5,0.5));
	logicPMT->SetVisAttributes(attr);
	// make +z PMT's
	zPos = zVCBoxSize/2+2*tAcrylicPanel+dz+lenPMT/2;
	for (G4int i=0; i<xVoxels; i++)
	{
		xPos = -xVCBoxSize/2+i*(xVoxelSize+xVoxelSpace)+xVoxelSpace+xVoxelSize/2;
		for(G4int j=0; j<yVoxels; j++)
		{
			yPos = -yVCBoxSize/2+j*(yVoxelSize+yVoxelSpace)+yVoxelSpace+yVoxelSize/2;
			physPMT = new G4PVPlacement(0, G4ThreeVector(xPos, yPos, zPos), logicPMT, "physPMT", logicWorld, false, i*yVoxels+j, true);
		}
	}
	// make +x PMT's
	xPos = xVCBoxSize/2+2*tAcrylicPanel+dz+lenPMT/2;
	for (G4int i=0; i<yVoxels; i++)
	{
		yPos = -yVCBoxSize/2+i*(yVoxelSize+yVoxelSpace)+yVoxelSpace+yVoxelSize/2;
		for(G4int j=0; j<zVoxels; j++)
		{
			zPos = -zVCBoxSize/2+j*(zVoxelSize+zVoxelSpace)+zVoxelSpace+zVoxelSize/2;
			physPMT = new G4PVPlacement(xRot, G4ThreeVector(xPos, yPos, zPos), logicPMT, "physPMT", logicWorld, false, i*zVoxels+j+xVoxels*yVoxels, true);
		}
	}
	// make -y PMT's
	yPos = -yVCBoxSize/2-2*tAcrylicPanel-dz-lenPMT/2;
	for (G4int i=0; i<xVoxels; i++)
	{
		xPos = -xVCBoxSize/2+i*(xVoxelSize+xVoxelSpace)+xVoxelSpace+xVoxelSize/2;
		for(G4int j=0; j<zVoxels; j++)
		{
			zPos = -zVCBoxSize/2+j*(zVoxelSize+zVoxelSpace)+zVoxelSpace+zVoxelSize/2;
			physPMT = new G4PVPlacement(yRot, G4ThreeVector(xPos, yPos, zPos), logicPMT, "physPMT", logicWorld, false, i*zVoxels+j+xVoxels*yVoxels+yVoxels*zVoxels, true);
		}
	}
	// TODO: re-define all PMT's and LG's with LG boxes as mother volumes (maybe not necessary) 
}
// Light Guide with no PMT constructor\
//void NuLatDetectorConstruction::BuildLGnoPMT()
// Light Guide (LG) and PMT constructor for mother volumes (not used - reimplement if needed)
/*void NuLatDetectorConstruction::BuildLGandPMTBoxes()
{
	// Define Visual Attributes object for adjusting coloring and visibility of various components - set to false to make components invisible
	attr = new G4VisAttributes(false);
	// Define mother volume for +x LG and PMT bank
	solidLGBoxPlusX = new G4Box("solidLGBoxPlusX", lenLGwPMT/2, yVCBoxSize/2, zVCBoxSize/2);
	logicLGBoxPlusX = new G4LogicalVolume(solidLGBoxPlusX, air, "logicLGBoxPlusX");
	// make LGBox mother volume invisible (do for all)
	logicLGBoxPlusX->SetVisAttributes(attr);// let this one show for testing
	G4double xPos = xVCBoxSize/2+lenLGwPMT/2+0.01*in;
	physLGBoxPlusX = new G4PVPlacement(0, G4ThreeVector(xPos, 0., 0.), logicLGBoxPlusX, "physLGBoxPlusX", logicWorld, false, 0, true);
	// Define mother volume for +y LG bank - no PMT's
	solidLGBoxPlusY = new G4Box("solidLGBoxPlusY", xVCBoxSize/2, lenLGwPMT/2, zVCBoxSize/2);
	logicLGBoxPlusY = new G4LogicalVolume(solidLGBoxPlusY, air, "logicLGBoxPlusY");
	logicLGBoxPlusY->SetVisAttributes(attr);
	G4double yPos = yVCBoxSize/2+lenLGwPMT/2+0.01*in;
	physLGBoxPlusY = new G4PVPlacement(0, G4ThreeVector(0., yPos, 0.), logicLGBoxPlusY, "physLGBoxPlusY", logicWorld, false, 0, true);
	// Define mother volume for +z LG and PMT bank
	solidLGBoxPlusZ = new G4Box("solidLGBoxPlusZ", xVCBoxSize/2, yVCBoxSize/2, lenLGwPMT/2);
	logicLGBoxPlusZ = new G4LogicalVolume(solidLGBoxPlusZ, air, "logicLGBoxPlusZ");
	logicLGBoxPlusZ->SetVisAttributes(attr);
	G4double zPos = zVCBoxSize/2+lenLGwPMT/2+0.01*in;
	physLGBoxPlusZ = new G4PVPlacement(0, G4ThreeVector(0., 0., zPos), logicLGBoxPlusZ, "physLGBoxPlusZ", logicWorld, false, 0, true);
	// Define mother volume for -x LG bank - no PMT's
	solidLGBoxMinusX = new G4Box("solidLGBoxMinusX", lenLGwPMT/2, yVCBoxSize/2, zVCBoxSize/2);
	logicLGBoxMinusX = new G4LogicalVolume(solidLGBoxMinusX, air, "logicLGBoxMinusX");
	logicLGBoxMinusX->SetVisAttributes(attr);
	physLGBoxMinusX = new G4PVPlacement(0, G4ThreeVector(-xPos, 0., 0.), logicLGBoxMinusX, "physLGBoxMinusX", logicWorld, false, 0, true);
	// Define mother volume for -y LG and PMT bank
	solidLGBoxMinusY = new G4Box("solidLGBoxMinusY", xVCBoxSize/2, lenLGwPMT/2, zVCBoxSize/2);
	logicLGBoxMinusY = new G4LogicalVolume(solidLGBoxMinusY, air, "logicLGBoxMinusY");
	logicLGBoxMinusY->SetVisAttributes(attr);
	physLGBoxMinusY = new G4PVPlacement(0, G4ThreeVector(0., -yPos, 0.), logicLGBoxMinusY, "physLGBoxMinusY", logicWorld, false, 0, true);
	// Define mother volume for -z LG bank - no PMT's
	solidLGBoxMinusZ = new G4Box("solidLGBoxMinusZ", xVCBoxSize/2, yVCBoxSize/2, lenLGwPMT/2);
	logicLGBoxMinusZ = new G4LogicalVolume(solidLGBoxMinusZ, air, "logicLGBoxMinusZ");
	logicLGBoxMinusZ->SetVisAttributes(attr);
	physLGBoxMinusZ = new G4PVPlacement(0, G4ThreeVector(0., 0., -zPos), logicLGBoxMinusZ, "physLGBoxMinusZ", logicWorld, false, 0, true);
	// Call function to build LG's and PMT's
	BuildLGandPMT();
}*/
// Detector Construct() function
G4VPhysicalVolume* NuLatDetectorConstruction::Construct()
{
	// Define Visual Attributes object for adjusting coloring and visibility of various components - set to false to make components invisible
	attr = new G4VisAttributes(false);
	// World Volume - min size 1m
	if(xWorld<0.5*m)
	{
		xWorld = 0.5*m;
	}
	if(yWorld<0.5*m)
	{
		yWorld = 0.5*m;
	}
	if(zWorld<0.5*m)
	{
		zWorld = 0.5*m;
	}
	solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
	logicWorld =  new G4LogicalVolume(solidWorld, air, "logicWorld");
	// make world volume invisible
	logicWorld->SetVisAttributes(attr);
	physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);
	// Calorimeter and Voxels
	BuildVCBox();
	// Acrylic box
	BuildAcrylicBox();
	// Light Guide and PMT's
	BuildLGandPMT();
	// return value
	return physWorld;
}
// Sensitive Detector Function
void NuLatDetectorConstruction::ConstructSDandField()
{
	// Get SDM pointer for creating new detectors
	G4SDManager *SDman = G4SDManager::GetSDMpointer();
	// Define PMT's as sensitive volumes
	detPMT = new NuLatPMTSensitiveDetector("/NuLatPMT", xVoxels, yVoxels, zVoxels);
	SDman->AddNewDetector(detPMT);
	logicPMT->SetSensitiveDetector(detPMT);
	// Define Voxels as sensitive volumes
	detVoxel = new NuLatVoxelSensitiveDetector("/NuLatVoxel", xVoxels, yVoxels, zVoxels);
	SDman->AddNewDetector(detVoxel);
	logicVoxel->SetSensitiveDetector(detVoxel);
}
