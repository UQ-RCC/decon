#pragma once

#include "DeconvolutionParameters.h"

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
	namespace LightSheetDirection {
		enum Type {
			LeftRight = 0,
			TopBottom = 1
		};
	}

	struct MICROVOLUTION_EXPORT LightSheetParameters : DeconParameters {
		LightSheetParameters();
		virtual ~LightSheetParameters();

		float lightSheetNA;								//!< Light sheet llumination NA
		LightSheetDirection::Type lightSheetDirection;	//!< Light sheet illumination direction
	};
}
