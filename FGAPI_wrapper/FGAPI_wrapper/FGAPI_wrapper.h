// FGAPI_wrapper.h
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <atlbase.h>

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FGAPI_headers/Geodatabase.h"
#include "FGAPI_headers/GeodatabaseManagement.h"

using namespace std;
using namespace FileGDBAPI;
using namespace System;

namespace FGAPI_wrapper {

	public ref class FGAPIDotNET
	{
		void MarshalString ( String ^ s, wstring& os ) {
			using namespace Runtime::InteropServices;
			const wchar_t* chars = 
				(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

	public :
		System::String ^test(System::String ^path)
		{
			System::String ^status;
			// Create a new geodatabase in the current directory.
			  long hr;
			  FileGDBAPI::Geodatabase geodatabase;
			  std::wstring GeoDatabase;// = path;//L"C:/Temp/GdbManagement.gdb";
			  MarshalString(path,GeoDatabase);
			  if ((hr = FileGDBAPI::CreateGeodatabase(GeoDatabase, geodatabase)) != S_OK)
			  {
				status = "An error occurred while creating the geodatabase.";
				status = status + "Error code: " + hr.ToString();
				return status;
			  }
			  status = "The geodatabase has been created.";
			  FileGDBAPI::CloseGeodatabase(geodatabase);

			return status;
		}
	};
}
