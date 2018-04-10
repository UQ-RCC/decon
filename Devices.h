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

#include "Export.h"
#include <memory>
#include <string>

namespace microvolution {
	class Devices_impl;

	//! Enumerate and control which GPUs are used.
	class MICROVOLUTION_EXPORT Devices {
	public:
		~Devices();

		//! Get global, singleton instance
		static Devices* GetInstance();

		/*! @brief Set GPU device to use for deconvolution.

		  If unset, system primary device will be used. An exception will be thrown if trying to set an unavailable device.
		  This call is thread-safe and can be called from DeconvolutionLauncher::SetDevice().
		*/
		void SetDevice(int device);

		//! Returns which GPU is active in the current system thread.
		int GetCurrentDevice();

		//! Number of CUDA-enabled GPUs in the system.
		int NumDevices();

		//! Name of GPU
		std::string Name(int device);
		void Name(int device, char* name);

		//! Total GPU RAM for device
		size_t TotalMemory(int device);

		//! Allocatable GPU memory on current device, in bytes
		size_t CurrentFreeMemory();

		//! CUDA compute capability of device. Only 2.0 and greater are supported
		float ComputeCapability(int device);

		//! NVIDIA driver version. Must be 345 or greater
		float DriverVersion();

		bool TeslaTCC(int i);
		bool CanAccessPeer(int i, int j);

		//! Hard reset of current GPU
		void ResetDevice();

	private:
		Devices();

		static Devices* devicesSingleton;

		Devices_impl* impl;
	};
}
