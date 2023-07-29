// conditional statement for defining class only once
#ifndef NULATDETECTORCONSTRUCTION_HH
#define NULATDETECTORCONSTRUCTION_HH
// Header files for defining volumes
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
// Nist manager and units for material properties
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
// Header files for placements
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
// Header files for geometry types
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4IntersectionSolid.hh"
#include "G4SubtractionSolid.hh"
// Header files for sensitive detector
#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
// Header files for surfaces
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
// Header file for messenger control
#include "G4GenericMessenger.hh"
// Header files for visual attribute manager
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
// Header file for user defined libraries
#include "NuLatPMTsensDet.hh"
#include "NuLatVoxelSensDet.hh"
// Write the class
class NuLatDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	NuLatDetectorConstruction();
	~NuLatDetectorConstruction();
	// method for looking up scoring volume
	// TODO: ?
	G4LogicalVolume *GetNuLatScoringVolume() const { return fNuLatScoringVolume; }
	// construct function for detector factory
	virtual G4VPhysicalVolume* Construct();
private:
	// Volume declarations - naming convention: solidName for geometry volume definitions, logicName for logical volume definitions and physName for physical volume definitions
	G4Box *solidWorld, *solidVCBox, *solidVoxel, *solidLGBox, *solidSSDivOuter, *solidSSDivInner, *solidSSDivCut;
	// TODO: reallocate single volume for acrylic pieces and use transformations to place duplicates
	G4Box *solidAcrylicSidePlateX, *solidAcrylicSidePlateY, *solidAcrylicSidePlateZ;
	// TODO: reallocate volumes for single LG box and use transformations to place duplicates
	//G4Box *solidLGBoxPlusX, *solidLGBoxPlusY, *solidLGBoxPlusZ, *solidLGBoxMinusX, *solidLGBoxMinusY, *solidLGBoxMinusZ;
	G4Trd *solidLGTrd, *solidAcrylicPanel, *solidSSPanel, *solidSSDivPlate;
	G4Tubs *solidPMT;//, *solidAlBottom, *solidAlBarrel, *solidAlFlange, *solidNaICrystal, *solidNaIPMT;
	G4Cons *solidLGCone;
	G4IntersectionSolid *solidLG;
	G4SubtractionSolid *solidSSDiv, *solidSSDivBot, *solidSSDivTop;
	G4LogicalVolume *logicWorld, *logicVCBox, *logicVoxel, *logicLGBox, *logicLG, *logicPMT, *fNuLatScoringVolume;
	G4LogicalVolume *logicAcrylicSidePlateX, *logicAcrylicSidePlateY, *logicAcrylicSidePlateZ, *logicAcrylicPanel, *logicSSPanel, *logicSSDiv;
	//G4LogicalVolume *logicLGBoxPlusX, *logicLGBoxPlusY, *logicLGBoxPlusZ, *logicLGBoxMinusX, *logicLGBoxMinusY, *logicLGBoxMinusZ;
	//G4LogicalVolume *logicAlBottom, *logicAlBarrel, *logicAlFlange, *logicNaICrystal, *logicNaIPMT, *fScoringVolumeNaI;
	G4VPhysicalVolume *physWorld, *physVCBox, *physVoxel, *physLGBox, *physLG, *physPMT, *physAcrylicPanel, *physSSPanel, *physSSDiv;
	G4VPhysicalVolume *physAcrylicSidePlatePlusX, *physAcrylicSidePlatePlusY, *physAcrylicSidePlatePlusZ, *physAcrylicSidePlateMinusX, *physAcrylicSidePlateMinusY, *physAcrylicSidePlateMinusZ;
	//G4VPhysicalVolume *physLGBoxPlusX, *physLGBoxPlusY, *physLGBoxPlusZ, *physLGBoxMinusX, *physLGBoxMinusY, *physLGBoxMinusZ;
	//G4VPhysicalVolume *physAlBottom, *physAlBarrel, *physAlFlange, *physNaICrystal, *physNaIPMT;
	// Declare optical surfaces
	G4OpticalSurface *mirrorSurface;
	G4LogicalSkinSurface *skinBarrel, *skinBottom, *skinSidePanel;
	// Material declarations
	G4Material *air, *PVT, *acrylic, *EJ200, *stainless/*, *vacuum, *aluminum, *muMetal, *BeCuPhotoCath, *borosilicateGlass, *NaI, *NaI_Tl/**/;
	G4Element *H/*, *Be/**/, *C, *O/*, *Na, *Si/**/, *Cr, *Fe, *Ni/*, *Cu, *Mo, *I, *Tl/**/;
	//G4Isotope *Li6;
	G4MaterialPropertiesTable *mptAir, *mptPVT, *mptAcrylic, *mptAl, *mptSS/*, *mptNaI, *mptMuMetal, *mptBeCuPhotoCath, *mptMuMetalSurface/**/;
	// physical constants for computing photon energies or wavelengths:
	// divide by wavelength in nm to get energy in eV, or divide by energy in eV to get wavelength in nm
	const G4double HCNM = 1239.841939*eV;
	// conversion factor inches to mm
	const G4double in = 25.4*mm;
	// scintillation properties of PVT
	const G4double scintYieldPVT = 10000./MeV;// same constant for EJ-200. See line 142 of NuLatDetectorConstruction.cc
	const G4double stcEJ200 = 2.1*ns;
	const G4double srtEJ200 = 0.9*ns;
	// mass fractions of EJ-200 PVT - see Eljen Technology. (2016, July 27, 2018). GENERAL PURPOSE EJ-200, EJ-204, EJ-208, EJ-212. 
		// Available: https://eljentechnology.com/products/plastic-scintillators/ej-200-ej-204-ej-208-ej-212
	// Atomic Weights obtained from Atomic Number, Mass Number, and Atomic Mass Unit. (2019, June 28). https://chem.libretexts.org/@go/page/158404
		// Available: https://chem.libretexts.org/Courses/University_of_Arkansas_Little_Rock/Chem_1402%3A_General_Chemistry_1_(Kattoum)/Text/2%3A_Atoms%2C_Molecules%2C_and_Ions/2.02%3A_Atomic_Number%2C_Mass_Number%2C_and_Atomic_Mass_Unit
	const G4double Catoms_EJ200 = 0.469E23;
	const G4double Hatoms_EJ200 = 0.517E23;
	//const G4double N_A = 6.022E23;//
	const G4double uu = 1.66054E-27*kg;
	const G4double Cmass = 12.011*uu;
	const G4double Hmass = 1.0079*uu;
	G4double totalMass_EJ200 = Catoms_EJ200*Cmass+Hatoms_EJ200*Hmass;
	G4double Cfrac_EJ200 = Catoms_EJ200*Cmass/totalMass_EJ200;
	G4double Hfrac_EJ200 = Hatoms_EJ200*Hmass/totalMass_EJ200;
	// densities of various materials
	const G4double rhoAcrylic = 1.180*g/cm3;
	const G4double rhoEJ200 = 1.023*g/cm3;
	// variable declarations
	// World volume size in x, y and z dimensions
	G4double xWorld, yWorld, zWorld;
	// NuLat Detector Parameters (number of voxels in x, y and z dimensions, length in each dimension, gap size in each dimension
	G4int xVoxels, yVoxels, zVoxels;
	G4double xVoxelSize, yVoxelSize, zVoxelSize;
	G4double xVoxelSpace, yVoxelSpace, zVoxelSpace;
	G4double lenPMT, lenLGTaper, lenLGSqu, lenLGwPMT, massfracLi6;
	G4bool Li6doped, debugMsg;
	G4double xVCBoxSize, yVCBoxSize, zVCBoxSize, tAcrylicPlate;
	//G4double rMuMetal, hMuMetal, tGlass, rPMTPhotoCath, tGlassMin;
	// function declarations
	void DefineMaterials();
	void BuildVCBox();
	void BuildAcrylicBox();
	//void BuildLGandPMTBoxes();
	void BuildLGandPMT();
	//void BuildLGnoPMT();
	virtual void ConstructSDandField();
	// Pointers for SD's:
	NuLatPMTSensitiveDetector *detPMT;
	NuLatVoxelSensitiveDetector *detVoxel;
	// Pointer to Generic Messenger Object
	G4GenericMessenger *fMessenger;
	// Pointer to Visual Attribute manager object
	G4VisAttributes *attr;
};
// end of conditional for defining class only once
#endif
