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

#include <stdexcept>
#include "Export.h"

namespace microvolution {

	//! Error codes returned as part of microvolution_exception.
	namespace MicrovolutionError {
		enum Type {
			noError = 0,

			unspecified = 1,

			unsetParams = 2,
			noImage = 3,
			noPSF = 4,

			badDevice = 10,
			badDriver = 11,

			badDimensionX = 20,
			badDimensionY = 21,
			badDimensionZ = 22,
			badDR = 23,
			badDZ = 24,

			badNA = 30,
			badRI = 31,
			badNS = 32,

			badLambda = 40,
			badPinhole = 41,

			badTilingX = 50,
			badTilingY = 51,
			badTilingZ = 52,

			badPaddingX = 60,
			badPaddingY = 61,
			badPaddingZ = 62,

			badPsfType = 70,
			badPsfModel = 71,
			badScaling = 72,
			badPreFilter = 73,
			badPostFilter = 74,
			badBlind = 75,

			badRegularizationType = 80,
			badRegularizationFactor = 81,

			badBackground = 90,

			badFFT = 200,

			badNPP = 300,

			badAllocGPU = 400,
			badAllocCPU = 401,
			badAllocPinned = 402,
			badAllocOOM = 403,

			unlicensedDeconvolution = 500,
			unlicensedBlind = 501,
			unlicensedMultiGPU = 502,

			badThrust = 600,

			aborted = 700
		};
		typedef Type MicrovolutionError_t;
	}

#pragma warning(disable: 4275)
	/*! @brief Exception wrapper for old C++ runtime compatibility and attaching unique error codes
	*/
	class MICROVOLUTION_EXPORT microvolution_exception : public std::runtime_error {
	public:
		microvolution_exception(const std::string& _Message);
		microvolution_exception(const char *_Message);

		microvolution_exception(const std::string& _Message, MicrovolutionError::Type _error);
		microvolution_exception(const char *_Message, MicrovolutionError::Type _error);

		MicrovolutionError::Type error;
		MicrovolutionError::Type getError();
		int getErrorInt();
	};
#pragma warning(default: 4275)

	MICROVOLUTION_EXPORT MicrovolutionError::Type getMicrovolutionExceptionError(microvolution_exception& e);
}