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

#include <string>
#include <vector>
#include <memory>
#include "Export.h"

namespace microvolution {
	class Licensing_impl;

	//! Interact with the licensing backend.
	class MICROVOLUTION_EXPORT Licensing {
	public:
		~Licensing();

		//! Combination of SetPath(), SetExecPath(), and SetLicenseString()
		void Initialize(std::string path0 = "", std::string argv0 = "", std::string license0 = "");
		//! Set the directory search path for license files. Defaults to current working directory if not set
		void SetPath(std::string path);
		void SetPath(const char* path);
		//! Set path to executable or dll. Licenses will be searched in the containing folder. Defaults to location of Microvolution dll if not set
		void SetExecPath(std::string path);
		void SetExecPath(const char* path);
		//! Set string containing license information
		void SetLicenseString(std::string license);
		void SetLicenseString(const char* license);

		//! Initialize license manager with license search paths first set with SetPath(), SetExecPath(), and SetLicenseString()
		void CheckoutLicenses();

		//! Check whether particular product key (e.g. "deconvolution") has a valid license. Must CheckoutLicenses() first.
		bool HaveValidLicense(std::string key);
		bool HaveValidLicense(const char* key);

		//! Check whether particular product license is permanent. Note that permanent product keys still have a MaximumVersion() that can run without a license update.
		bool HavePermanentLicense(const char* key);

		//! Get expiration date of product license. Returns "permanent", dd-mon-yyyy, or empty.
		std::string LicenseExpirationDate(std::string key);
		//! Get expiration date of product license. Returns "false" if permanent or not valid. Otherwise, returns true and sets expiration date in pointers.
		//! @param[out] year, month, day
		bool LicenseExpirationDate(const char* key, int* year, int* month, int* day);

		std::string Activate(std::string activationKey);
		bool Activate(const char* activationKey, char* licenseBuf, int* licenseBufSize);

		//! Get host ID used for node-locked license
		///@{
		std::string HostID();
		/*!
			@param[out] id Char array to store primary host ID
			@return Required char array length
		*/
		int HostID(char* id);
		std::vector<std::string> HostIDs();
		///@}

		//! Version of the current dll
		std::string CurrentVersion();
		void CurrentVersion(char* version);
		//! Maximum version allowed for use with the current "deconvolution" license key
		std::string MaximumVersion();
		void MaximumVersion(char* version);

		//! Get global, singleton instance
		static Licensing* GetInstance();
	private:
		// Private constructor to force singleton
		Licensing();

		static Licensing* licensingSingleton;

		Licensing_impl* impl;
	};
}