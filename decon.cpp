/*
#include "Licensing.h"
#include "DeconvolutionLauncher.h"
#include "Callbacks.h"
*/

#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <iostream>

//using namespace microvolution;
/*
void iterationCallback(DeconvolutionCallbackStruct cbs, void* data)
{
	printf("Iteration %i\n", cbs.iteration);
}
*/
int main(int argc, char** argv)
{
	std::cout << "looking for license..." << std::endl;
	return 0;
	/*	
	// Initialize license manager
	// Only needed if changing the search path (defaults to cwd + dll path)
	Licensing* lic = Licensing::GetInstance();
	lic->SetPath("/afm01/home/uqocairn/project/decon-test");
	lic->CheckoutLicenses();

	std::cout << "*** decon licence: " << (lic->HaveValidLicense("deconvolution") ? "true" : "false") << std::endl;
	return 0;

	// Set all relevant parameters.
	DeconParameters params;
	params.nx = 512;
	params.ny = 512;
	params.nz = 32;
	params.iterations = 10;
	params.lambda = 525;
	params.dr = 100;
	params.dz = 250;
	params.NA = 0.6;
	params.RI = 1.0;
	params.ns = 1.33;
	params.psfType = PSFType::Widefield;
	params.psfModel = PSFModel::Vectorial;
	params.generatePsf = true;
	params.scaling = Scaling::U16;

	// Generate random data
	uint16_t* data = new uint16_t[params.nx*params.ny];
	srand(time(NULL));
	for (int i = 0; i < params.nx*params.ny; ++i)
		data[i] = rand() % UINT16_MAX;

	// Create launcher that holds data and runs deconvolution
	DeconvolutionLauncher launcher;

	// Set parameters
	launcher.SetParameters(params);

	// Set callback function to report iteration progress
	launcher.SetCallbacks(iterationCallback, NULL, NULL);

	// Transfer image data to launcher
	for (int i = 0; i < params.nz; ++i)
		launcher.SetImageSlice(i, data);

	// Run
	launcher.Run();

	// Transfer deconvolved image back
	for (int i = 0; i < params.nz; ++i)
		launcher.RetrieveImageSlice(i, data);

	return 0;
	*/
}
