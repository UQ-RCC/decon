#pragma once

/*
* Copyright (C) Microvolution, LLC - All Rights Reserved
*
* Confidential and proprietary
*
* Microvolution, LLC retains all intellectual property and proprietary rights
* in and to this software and related documentation and any modifications
* thereto. The intellectual and technical concepts contained herein are
* proprietary to Microvolution, LLC and are protected by trade secret or
* copyright law.
* Any use, reproduction, disclosure, or distribution of this software and
* related documentation without an express license agreement from
* Microvolution, LLC is strictly prohibited.
*/

#include <memory>
#include <vector>
#include <stdint.h>

#include "Export.h"
#include "DeconvolutionParameters.h"
#include "Callbacks.h"

namespace microvolution {

	class DeconvolutionLauncher_impl;

	/*! @brief Main controlling class for a deconvolution run

	  This class is (largely) thread-safe, i.e. multiple threads can each have their own launcher with \b independent devices set with SetDevice.
	  These launchers then can process different images & parameters independently.
	*/
	class MICROVOLUTION_EXPORT DeconvolutionLauncher {
	public:

		DeconvolutionLauncher();
		~DeconvolutionLauncher();

		/*! @brief Cleans all temporary memory used by deconvolution on CPU and GPU.

		  If the same launcher object is to be used again, must call SetParameters() again.
		  This function should not be used while deconvolution is in progress.
		  \sa Abort()
		*/
		void Reset();
		void CleanHost();
		void CleanDevice();
		void CleanImage();
		void CleanPsf();

		/*! @brief Set all deconvolution parameters. Parameters must be set before running deconvolution.

		  Changing any parameters that involve a change of image size (DeconParameters::nx, DeconParameters::xPadding, etc) will reset and rebuild all temporary memory in use.
		  Otherwise, this function is lightweight and calling again with same parameters does not force a rebuild.
		*/
		///@{
		void SetParameters(DeconParameters& params);
		//! As with SetParameters(DeconParameters params), but directly passing a filled buffer with image data; *psf can be set to null for generated PSF.
		void SetParameters(DeconParameters& params, float* img, float* psf);
		///@}

		/*!
		  @brief Copy image to launcher from CPU pointer, slice by slice.
		  
		  Dimensions must match what has been set through SetParameters() and DeconParameters::nx etc.
		  @param i Z slice
		  @param[in] ptr Source buffer
		*/
		///@{
		void SetImageSlice(int i, float* ptr);
		void SetImageSlice(int i, uint16_t* ptr);
		void SetImageSlice(int i, uint8_t* ptr);
		///@}

		/*!
		  @brief Copy PSF to launcher, slice by slice.
		
		  Dimensions must match what has been set through SetParameters() and DeconParameters::psfNx etc.
		*/
		///@{
		void SetPsfSlice(int i, float* ptr);
		void SetPsfSlice(int i, uint16_t* ptr);
		void SetPsfSlice(int i, uint8_t* ptr);
		///@}

		float* GetImage();
		float* GetImageSlice(int i);
		void   RetrieveImage(float* ptr);

		/*! 
		  @brief Copy image slices from launcher to destination pointer after deconvolution.
		  
		  DeconParameters::scaling should be set to match the destination bit depth, or overflow/truncation may occur.
		  Destination pointer must be sufficiently allocated for DeconParameters::nx * DeconParameters::ny * sizeof(ptr)
		  @param i Z slice
		  @param[out] ptr Destination buffer, pre-allocated
		*/
		///@{
		void   RetrieveImageSlice(int i, float* ptr);
		void   RetrieveImageSlice(int i, uint16_t* ptr);
		void   RetrieveImageSlice(int i, uint8_t* ptr);
		///@}

		/*! @brief Set GPU device to use for deconvolution.

		  If unset, system primary device will be used. An exception will be thrown if trying to set an unavailable device.
		  Different launcher objects in different system threads can safely initialize distinct devices.
		  Setting the same device from multiple objects/threads is undefined.
		*/
		void SetDevice(int dev);
		void SetDevices(std::vector<int> devs);

		//! Run deconvolution after SetParameters() and SetImageSlice() have been used.
		void Run();
		void Run(float* image, float* psf);

		//! Iterations from previous run. Will differ from DeconParameters::iterations only if attempting auto stop feature (not recommended, particularly with subvolume tiling).
		std::vector<int> LastRunIterations();

		/*! @brief Attempt to stop a deconvolution in progress.

		  While GPU is active, abort can only be triggered at the start of a new iteration (i.e. abort is not forced).
		  Note: Abort() only works when IterationCallbackType is set in DeconvolutionLauncher::SetCallbacks(),
		  and must be followed by a Reset() and SetParameters() to continue using the same launcher object.
		*/
		void Abort();

		/*! Set callbacks to monitor deconvolution progress.
		  @param callback Function pointer to monitor current iteration and subvolume number
		  @param stateCallback Function pointer to monitor general deconvolution state, e.g. initializing or running
		  @param pUserData Opaque data that is passed back through callback and stateCallback

		  Example:
		  @code
		  auto iterationCallback = [](DeconvolutionCallbackStruct s, void* p) { printf("Iteration %i\n",s.iteration); };
		  launcher.SetCallbacks(iterationCallback, nullptr, nullptr);
		  @endcode
		*/
		void SetCallbacks(IterationCallbackType callback, StateCallbackType stateCallback, void* pUserData);

		//! Generate PSF on GPU and return all data in *psf
		//! @param params Same parameters struct that would be used in SetParameters(). Be sure to have DeconParameters::generatePsf set to 'true'
		//! @param[out] psf Pointer to buffer with space for full psfNx*psfNy*psfNz*sizeof(float)
		void MakePSF(DeconParameters& params, float* psf);

		///@{

		//! Allocate space for PSF on host and copy the PSF from GPU to CPU memory at end of run.
		//! If using tiling, only the first tile's PSF is retrieved.
		void KeepPsf(bool keep);

		//! @return Whether or not the launcher will retrieve its PSF into CPU memory.
		bool KeepPsf();

		/*! @brief Retrieve the PSF that was used, particularly useful when running blind decon.

		  This will have the same dimensions & spacing as the input image.
		  If using tiling, only the first tile's PSF is retrieved.
		  If the retrieved PSF is smaller than the input image (due to tiling), then the PSF is padded with 0.
		  If the internal PSF is larger than the input image (due to padding), then the PSF is cropped.
		*/
		void RetrievePsfSlice(int i, float* ptr);
		///@}

	private:
		DeconvolutionLauncher_impl* impl;
	};

} /* namespace microvolution */
