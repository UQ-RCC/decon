#pragma once
#include "Export.h"

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

namespace microvolution {

	namespace PSFType {
		enum Type {
			Widefield = 0,
			Confocal = 1,
			TwoPhoton = 2
		};
	}

	namespace PSFModel {
		enum Type {
			BornWolf = 0,	//!< Use Born-Wolf PSF model
			Vectorial = 1	//!< Use Vectorial PSF model -- requires sample refractive index to be set in DeconParameters::ns. Recommended with high NA objectives
		};
	}

	namespace Scaling {
		enum Type {
			None = 0,	//!< Apply no scaling after deconvolution -- maintain full 32-bit (single precision float) range
			U16 = 1,	//!< Scale image to fit in 16-bit range if necessary, and round to nearest value
			U8 = 2		//!< Scale image to fit in 8-bit range if necessary, and round to nearest value
		};
	}

	namespace PreFilter {
		enum Type {
			None = 0,
			GaussianImage = 1,			//!< Apply 3x3 Gaussian filter to image before deconvolution
			GaussianImageAndPSF = 2,	//!< Apply 3x3 Gaussian filter to both image and PSF before deconvolution. Recommended option for more quantitative comparisons with noise suppression
			MedianImage = 3				//!< Apply 3x3 median filter to image before deconvolution
		};
	}

	namespace PostFilter {
		enum Type {
			None = 0,
			Gaussian = 1,		//!< Apply 3x3 Gaussian filter to image after deconvolution
			Median = 2,			//!< Apply 3x3 median filter to image after deconvolution
			SharpenFilter = 3	//!< Apply 3x3 sharpen filter to image after deconvolution
		};
	}

	namespace RegularizationType {
		enum Type {
			None = 0,	//!< No regularization
			TV = 1,		//!< Total Variation regularization
			Entropy = 2	//!< Entropy regularization. Recommended over RegularizationType::TV
		};
	}

	/*! @brief Holds all parameters for deconvolution.
	*/
	struct MICROVOLUTION_EXPORT DeconParameters {
		DeconParameters();
		virtual ~DeconParameters();

		int nx;			//!< Width of image in pixels
		int ny;			//!< Height of image in pixels
		int nz;			//!< Number of Z planes. Set to 0 or 1 for 2D deconvolution

		int iterations;	//!< Number of iterations to run. Set to 0 to perform all setup and data transfer stages but skip actual deconvolution

		int xPadding;	//!< Minimum padding in pixels added to both left and right sides of image to minimize edge artifacts
		int yPadding;	//!< Minimum padding in pixels added to both top and bottom sides of image to minimize edge artifacts
		int zPadding;	//!< Minimum padding in pixels added to both top and bottom planes of image to minimize edge artifacts
		int xTiles;		//!< Number of subvolumes in X direction. Set to 0 or 1 for no subvolume tiling
		int yTiles;		//!< Number of subvolumes in Y direction. Set to 0 or 1 for no subvolume tiling
		int zTiles;		//!< Number of subvolumes in Z direction. Set to 0 or 1 for no subvolume tiling

		float lambda;	//!< Wavelength for PSF generation, in nanometers
		float dr;		//!< Lateral pixel spacing, in nanometers/pixel
		float dz;		//!< Axial pixel spacing, in nanometers/plane
		float NA;		//!< Numerical aperture of the objective
		float RI;		//!< Refractive index of the objective immersion medium, e.g. 1.0 for air, 1.33 for water, 1.515 for oil
		float ns;		//!< Refractive index of the sample's immersion medium, e.g. 1.33 for water, 1.45 for Vectashield

		float zdepth;	//!< Currently unused. Z depth of particle. 
		bool imagingUp;	//!< Currently unused. Imaging direction. 

		float pinhole;	//!< Backprojected pinhole size in nanometers. Required for confocal model, not used for widefield or two photon

		PSFType::Type psfType;		//!< Widefield, confocal, or two-photon theoretical model. PSFType::Confocal requires DeconParameters::pinhole
		PSFModel::Type psfModel;	//!< Born-Wolf (scalar) or vectorial theoretical PSF model. PSFModel::Vectorial requires DeconParameters::ns
		bool generatePsf;			//!< Enable theoretical PSF generation. When false, DeconParameters::psfNx etc. should be set

		bool blind;		//!< Enable/disable blind deconvolution

		Scaling::Type scaling;	//!< Intensity scaling and rounding of deconvolution output 

		PreFilter::Type preFilter;		//!< Filtering applied before deconvolution
		PostFilter::Type postFilter;	//!< Filtering applied after deconvolution

		RegularizationType::Type regularizationType;	//!< Set regularization method for noise reduction
		float regularization;							//!< Set regularization scale parameter to control intensity.
														//!< Set to -1 for automatic parameter estimation (adaptive).
														//!< Values greater than 0 are reciprocal (reg=100 is stronger than reg=1000).

		float background;	//!< Intensity of background to include as parameter in deconvolution; background is never directly subtracted. 

		int psfNx;		//!< Width of empirical PSF in pixels. Should be set when not generating a theoretical PSF.
		int psfNy;		//!< Height of empirical PSF in pixels. Should be set when not generating a theoretical PSF.
		int psfNz;		//!< Depth of empirical PSF in pixels. Should be set when not generating a theoretical PSF.
		float psfDr;	//!< Lateral spacing of empirical PSF in nm/pixel
		float psfDz;	//!< Axial spacing of empirical PSF in nm/plane
	};
}
