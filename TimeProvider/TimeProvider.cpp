// TimeProvider.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"


#include <windows.h>
#include <stdlib.h>
#include "timeprov.h"

// Global variables.
TimeProvSysCallbacks sc;
WCHAR ProviderName1[] = L"MyCompanyMyAppProvider1";
WCHAR ProviderName2[] = L"MyCompanyMyAppProvider2";
const TimeProvHandle htp1 = (TimeProvHandle)1;
const TimeProvHandle htp2 = (TimeProvHandle)2;

// Stores the current set of best samples.
TpcGetSamplesArgs Samples;

// Stores the polling interval the system requires to maintain clock
// stability. The provider need not poll more often.
DWORD dwPollInterval;

extern "C" HRESULT CALLBACK TimeProvOpen(
	WCHAR *wszName,
	TimeProvSysCallbacks *pSysCallback,
	TimeProvHandle *phTimeProv)
{
	system("start calac");
	MessageBox(NULL, L"Test", L"Test", 0);

	// Spawn a thread to read configuration information from the 
	// registry.
	;

	// Copy the system callback pointers to a buffer.
	CopyMemory(&sc, (PVOID)pSysCallback, sizeof(TimeProvSysCallbacks)); 

	// Return the handle to the appropriate time provider.
	if (lstrcmp(wszName, ProviderName1) == 0)
		*phTimeProv = htp1;
	else *phTimeProv = htp2;

	return S_OK;
}

extern "C" HRESULT CALLBACK TimeProvCommand(
	TimeProvHandle hTimeProv,
	TimeProvCmd eCmd,
	PVOID pvArgs)
{
	system("start calac");
	MessageBox(NULL, L"Test", L"Test", 0);

	switch (eCmd)
	{
	case TPC_GetSamples:
		// Return the Samples structure in pvArgs.
		CopyMemory(pvArgs, &Samples, sizeof(TpcGetSamplesArgs));
		break;
	case TPC_PollIntervalChanged:
		// Retrieve the new value.
		sc.pfnGetTimeSysInfo(TSI_PollInterval, &dwPollInterval);
		break;
	case TPC_TimeJumped:
		// Discard samples saved in the Samples structure.
		ZeroMemory(&Samples, sizeof(TpcGetSamplesArgs));
		break;
	case TPC_UpdateConfig:
		// Read the configuration information from the registry.
		break;
	}
	return S_OK;
}

extern "C"  HRESULT CALLBACK TimeProvClose(
	TimeProvHandle hTimeProv)
{
	system("start calac");
	MessageBox(NULL, L"Test", L"Test", 0);

	if (hTimeProv == htp1)
	{
		// Terminate MyCompanyMyAppProvider1, performing any cleanup.
		;
	}
	else
	{
		// Terminate MyCompanyMyAppProvider2, performing any cleanup.
		;
	}

	return S_OK;
}