#include "stdafx.h"
#include "device_io.h"


boolean getDevicePath()
{
	HDEVINFO							HardwareDeviceInfo;
	SP_DEVICE_INTERFACE_DATA			DeviceInterfaceData;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	DeviceInterfaceDetailData = NULL;
	ULONG								Length, RequiredLength = 0;
	BOOL								bResult;
	HRESULT								hr;

	LPGUID InterfaceGuid = (LPGUID)&GUID_DEVINTERFACE_BIOMETRIC_READER;

	HardwareDeviceInfo = SetupDiGetClassDevs(InterfaceGuid, NULL, NULL, (DIGCF_PRESENT | DIGCF_DEVICEINTERFACE));

	if (HardwareDeviceInfo == NULL) {
		printf("\n GetDevicePath() : SetupDiGetClassDevs failed!\n");
		return FALSE;
	}

	DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

	bResult = SetupDiEnumDeviceInterfaces(HardwareDeviceInfo, 0, InterfaceGuid, 0, &DeviceInterfaceData);

	if (bResult == FALSE) {
		LPVOID lpMsgBuf;

		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0,
			NULL)) {

			//printf(" SetupDiEnumInterfaces failed: %s\n", (LPSTR)lpMsgBuf);
			printf("\n GetDevicePath() : SetupDiEnumInterfaces, error - %d\n", GetLastError());
			LocalFree(lpMsgBuf);
		}

		SetupDiDestroyDeviceInfoList(HardwareDeviceInfo);
		return FALSE;
	}

	SetupDiGetDeviceInterfaceDetail(HardwareDeviceInfo, &DeviceInterfaceData, NULL, 0, &RequiredLength, NULL);

	DeviceInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LMEM_FIXED, RequiredLength);

	if (DeviceInterfaceDetailData == NULL) {
		SetupDiDestroyDeviceInfoList(HardwareDeviceInfo);
		printf("\n GetDevicePath() : Failed to allocate memory.\n");
		return FALSE;
	}

	DeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

	Length = RequiredLength;

	bResult = SetupDiGetDeviceInterfaceDetail(HardwareDeviceInfo, &DeviceInterfaceData, DeviceInterfaceDetailData, Length, &RequiredLength, NULL);

	if (bResult == FALSE) {

		LPVOID lpMsgBuf;

		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0,
			NULL)) {
			printf("\n GetDevicePath() : SetupDiEnumInterfaces failed: %s\n", (LPSTR)lpMsgBuf);
			LocalFree(lpMsgBuf);
		}

		SetupDiDestroyDeviceInfoList(HardwareDeviceInfo);
		LocalFree(DeviceInterfaceDetailData);
		return FALSE;
	}

	hr = StringCchCopy(deviceName, countof(deviceName), DeviceInterfaceDetailData->DevicePath);
	if (FAILED(hr)) {
		SetupDiDestroyDeviceInfoList(HardwareDeviceInfo);
		LocalFree(DeviceInterfaceDetailData);
		return FALSE;
	}

	SetupDiDestroyDeviceInfoList(HardwareDeviceInfo);
	LocalFree(DeviceInterfaceDetailData);

	return TRUE;
}