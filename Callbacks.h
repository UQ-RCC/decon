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

namespace microvolution {

	struct DeconvolutionCallbackStruct {
		int iteration;	//!< Current iteration, 0-indexed
		int subvolume;	//!< Current subvolume, 0-indexed
	};

	typedef void(*IterationCallbackType)(DeconvolutionCallbackStruct, void*);

	namespace DeconvolutionState {
		enum Type {
			Init,
			Running,
			Cleanup,
			Finished
		};
	}

	typedef void(*StateCallbackType)(DeconvolutionState::Type, void*);
}
