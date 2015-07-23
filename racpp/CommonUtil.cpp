#include "StdAfx.h"
#include "CommonUtil.h"
#include "UmsAgent.h"
#include "HandlerThread.h"
#include "SaveInfo.h"
#include "JSONObject.h"
#include "Mission.h"
#include <wininet.h>
#include <Winsock2.h>
#include <Iphlpapi.h>
#pragma comment(lib,"Iphlpapi")

std::string CommonUtil::user_identifier = "";

void CommonUtil::saveInfoToFile( HandlerThread* handler, std::string type, const JSONObject& info )
{
	JSONArray newdata;
	newdata.put(0, info);
	JSONObject jsonObject;
	jsonObject.put(type, newdata);
	handler->post(new Mission_Four(new SaveInfo(jsonObject)));
}

std::string CommonUtil::bindUserIdentifier(const std::string& identifier)
{
	user_identifier = identifier;
	return user_identifier;
}

std::string CommonUtil::getUserIdentifier()
{
	return user_identifier;
}

//李愿军 返回是否联网 OK
bool CommonUtil::isNetworkAvailable()
{
	DWORD flag;
	if (InternetGetConnectedState(&flag, 0))
		return true; 
	else
		return false;
}

std::string CommonUtil::getTime()
{
	SYSTEMTIME sys; 
	GetLocalTime( &sys ); 

	char *pChar = new char[200];
	ZeroMemory(pChar, 200);
	sprintf(pChar, "%04d-%02d-%02d %02d:%02d:%02d",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond);
	std::string sTime(pChar);
	delete[] pChar;
	return sTime;	//李愿军 OK
}

std::string CommonUtil::getAppKey()
{
	return UmsAgent::instance().getAppkey();
}

std::string CommonUtil::getPackageName()
{
	return "flysl";	//李愿军
}

std::string CommonUtil::getDeviceID()	//用硬盘序列号来代替
{
	return _getDiskInfo();	//李愿军 OK
}

std::string CommonUtil::getSdkVersion()
{
	return "FlyOS";	//李愿军 返回SDK版本
}

std::string CommonUtil::getCurVersion()
{
	return UmsAgent::instance().getAppVersion();		//李愿军 返回程序版本
}

std::string CommonUtil::getOsVersion()
{
	OSVERSIONINFOEX osver = {0};
	osver.dwOSVersionInfoSize = sizeof(osver);
	::GetVersionEx((OSVERSIONINFO*)&osver);
	SYSTEM_INFO sys_info = {0};
	GetNativeSystemInfo(&sys_info);
	if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 0 )
	{
		return ("Windows 2000");
	}

	if( osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1 )
	{
		return ("Windows XP");
	}

	if(osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2)
	{
		if( (osver.wProductType == VER_NT_WORKSTATION) 
			&& (sys_info.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64) )
		{
			return ("Windows XP Professional x64 Edition");
		}
		else if(GetSystemMetrics(SM_SERVERR2) == 0 )
		{
			return ("Windows Server 2003");
		}
		else if(osver.wSuiteMask & VER_SUITE_WH_SERVER )
		{
			return ("Windows Home Server");
		}
		else if(GetSystemMetrics(SM_SERVERR2) != 0 )
		{
			return ("Windows Server 2003 R2");
		}
	}

	if(osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0 )
	{
		if( osver.wProductType == VER_NT_WORKSTATION )
		{
			return ("Windows Vista");
		}
		else if( osver.wProductType != VER_NT_WORKSTATION )
		{
			return ("Windows Server 2008");
		}
	}

	if( osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1 )
	{
		if( osver.wProductType != VER_NT_WORKSTATION )
		{
			return ("Windows Server 2008 R2");
		}
		else if( osver.wProductType == VER_NT_WORKSTATION )
		{
			return ("Windows 7");
		}
	}

	if( osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2 )
	{
		if(osver.wProductType != VER_NT_WORKSTATION )
		{
			return ("Windows Server 2012");
		}
		else if( osver.wProductType == VER_NT_WORKSTATION )
		{
			return ("Windows 8");
		}
	}

	if( osver.dwMajorVersion == 6 && osver.dwMinorVersion == 3 )
	{
		if(osver.wProductType != VER_NT_WORKSTATION )
		{
			return ("Windows Server 2012 R2");
		}
		else if( osver.wProductType == VER_NT_WORKSTATION )
		{
			return ("Windows 8.1");
		} 
	}

	return ("Windows Unknown");
}


std::string CommonUtil::getScreenXY()
{
	//屏幕分辨率
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	std::stringstream ss;
	ss << width << "*" << height;
	return ss.str();
}

int CommonUtil::getReportPolicyMode()
{
	return UmsAgent::instance().getReportPolicyMode();
}

LatitudeAndLongitude CommonUtil::getLatitudeAndLongitude()
{
	LatitudeAndLongitude latitudeAndLongitude;
	return latitudeAndLongitude;	//李愿军 获取用户经纬度
}

std::string CommonUtil::getModulePath()
{
	TCHAR szDLLPath[MAX_PATH];  
	GetModuleFileName(NULL, szDLLPath, MAX_PATH); 
	return szDLLPath;
}


vec_string CommonUtil::GetINETMacAddresses()
{
	PIP_ADAPTER_ADDRESSES pAddresses = NULL;
	ULONG family = AF_INET;
	ULONG flags = GAA_FLAG_INCLUDE_PREFIX;
	ULONG outBufLen = sizeof( IP_ADAPTER_ADDRESSES );

	// Make an initial call to GetAdaptersAddresses to get the 
	// size needed into the outBufLen variable
	if ( GetAdaptersAddresses( family, flags, NULL, pAddresses, &outBufLen ) == ERROR_BUFFER_OVERFLOW )
	{
		pAddresses = static_cast<PIP_ADAPTER_ADDRESSES>( HeapAlloc( GetProcessHeap(), 0, outBufLen ) );
	}

	_ASSERT( pAddresses );
	// Make a second call to GetAdapters Addresses to get the
	// actual data we want
	DWORD dwRetVal = GetAdaptersAddresses( family, flags, NULL, pAddresses, &outBufLen );

	vec_string vAddress;
	if ( dwRetVal != ERROR_SUCCESS )
	{
		return vAddress;
	}
	PIP_ADAPTER_ADDRESSES pFirst = pAddresses;
	const int MACSESION = 6;
	while( pAddresses )
	{
		BYTE* pa = pAddresses->PhysicalAddress;
		if ( ! pa || ! pa[ 0 ] )
		{
			break;
		}
		char bAddressBytes[ MACSESION ];
		int bAddressInt [ MACSESION ];
		memset( bAddressBytes, 0, MACSESION );
		size_t nAddressSize = pAddresses->PhysicalAddressLength;
		memcpy( bAddressBytes, pa, ( nAddressSize < MACSESION ? nAddressSize : MACSESION ));
		char CommarSeperatedAddress[ MACSESION * 3 ]={0};
		for( int i = 0; i < MACSESION; ++i )
		{
			bAddressInt[ i ] = bAddressBytes[ i ];
			bAddressInt[ i ] &= 0x000000ff; // avoid "ff" leading bytes when "char" is lager then 0x7f
		}
		sprintf_s( CommarSeperatedAddress, "%02x:%02x:%02x:%02x:%02x:%02x",
			bAddressInt[ 0 ],
			bAddressInt[ 1 ],
			bAddressInt[ 2 ],
			bAddressInt[ 3 ],
			bAddressInt[ 4 ],
			bAddressInt[ 5 ]); // Should use scl::FormatString inside 
		pAddresses = pAddresses->Next ? pAddresses->Next : NULL;
		vAddress.push_back( std::string( CommarSeperatedAddress ) );
	}

	HeapFree( GetProcessHeap(), 0, pFirst );
	return vAddress;
}

BOOL __fastcall CommonUtil::DoIdentify( HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS pSCIP, PSENDCMDOUTPARAMS pSCOP, BYTE btIDCmd, BYTE btDriveNum, PDWORD pdwBytesReturned )
{
	pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;
	pSCIP->irDriveRegs.bFeaturesReg = 0;
	pSCIP->irDriveRegs.bSectorCountReg  = 1;
	pSCIP->irDriveRegs.bSectorNumberReg = 1;
	pSCIP->irDriveRegs.bCylLowReg  = 0;
	pSCIP->irDriveRegs.bCylHighReg = 0;

	pSCIP->irDriveRegs.bDriveHeadReg = (btDriveNum & 1) ? 0xB0 : 0xA0;
	pSCIP->irDriveRegs.bCommandReg = btIDCmd;
	pSCIP->bDriveNumber = btDriveNum;
	pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;

	return DeviceIoControl(	hPhysicalDriveIOCTL, 
		SMART_RCV_DRIVE_DATA,
		(LPVOID)pSCIP,
		sizeof(SENDCMDINPARAMS) - 1,
		(LPVOID)pSCOP,
		sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1,
		pdwBytesReturned, NULL);
}

char *__fastcall CommonUtil::ConvertToString( DWORD dwDiskData[256], int nFirstIndex, int nLastIndex )
{
	static char szResBuf[1024];
	char ss[256];
	int nIndex = 0;
	int nPosition = 0;

	for(nIndex = nFirstIndex; nIndex <= nLastIndex; nIndex++)
	{
		ss[nPosition] = (char)(dwDiskData[nIndex] / 256);
		nPosition++;

		// Get low BYTE for 2nd character
		ss[nPosition] = (char)(dwDiskData[nIndex] % 256);
		nPosition++;
	}

	// End the string
	ss[nPosition] = '\0';

	int i, index=0;
	for(i=0; i<nPosition; i++)
	{
		if(ss[i]==0 || ss[i]==32)	continue;
		szResBuf[index]=ss[i];
		index++;
	}
	szResBuf[index]=0;

	return szResBuf;
}

std::string CommonUtil::_getDiskInfo()
{
	const WORD IDE_ATAPI_IDENTIFY = 0xA1;   // 读取ATAPI设备的命令
	const WORD IDE_ATA_IDENTIFY   = 0xEC;   // 读取ATA设备的命令

	std::string sFilePath("\\\\.\\PHYSICALDRIVE0");//读第一物理驱动

	HANDLE hFile = INVALID_HANDLE_VALUE;
	hFile = ::CreateFile(sFilePath.c_str(), 
		GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		NULL, OPEN_EXISTING,
		0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)	
		return "";

	DWORD dwBytesReturned;
	GETVERSIONINPARAMS gvopVersionParams;
	DeviceIoControl(hFile, 
		SMART_GET_VERSION,
		NULL, 
		0, 
		&gvopVersionParams,
		sizeof(gvopVersionParams),
		&dwBytesReturned, NULL);

	if(gvopVersionParams.bIDEDeviceMap <= 0)	
		return "";

	// IDE or ATAPI IDENTIFY cmd
	int btIDCmd = 0;
	SENDCMDINPARAMS InParams;
	int nDrive =0;
	btIDCmd = (gvopVersionParams.bIDEDeviceMap >> nDrive & 0x10) ? IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;
	// 输出参数
	BYTE btIDOutCmd[sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];

	if(DoIdentify(hFile,
		&InParams, 
		(PSENDCMDOUTPARAMS)btIDOutCmd,
		(BYTE)btIDCmd, 
		(BYTE)nDrive, &dwBytesReturned) == FALSE)
		return "";
	::CloseHandle(hFile);

	DWORD dwDiskData[256];
	USHORT *pIDSector;

	pIDSector = (USHORT*)((SENDCMDOUTPARAMS*)btIDOutCmd)->bBuffer;
	for(int i=0; i < 256; i++)	
		dwDiskData[i] = pIDSector[i];

	// 硬盘物理序列号
	std::string szSerialNumber;
	szSerialNumber.assign(64, ' ');

	char* tmp = ConvertToString(dwDiskData, 10, 19);
	szSerialNumber = tmp;

	return szSerialNumber;
}

std::string CommonUtil::getCManufacturerAndProduct()
{
	LPCTSTR dataSet = "HARDWARE\\DESCRIPTION\\System\\BIOS\\";
	LPCTSTR subKey_Manu = "SystemManufacturer";
	LPCTSTR subKey_Product = "SystemProductName";
	HKEY hAppKey;
	char str_Mau[64];
	char str_Product[64];

	if (ERROR_SUCCESS == RegOpenKeyEx (HKEY_LOCAL_MACHINE, dataSet, 0, KEY_READ, &hAppKey))
	{
		ULONG cbSize = MAX_PATH*sizeof(TCHAR);
		DWORD dwFlag_Mau = RegQueryValueEx (hAppKey, subKey_Manu, NULL, NULL, (LPBYTE)str_Mau, &cbSize);
		DWORD dwFlag_Pro = RegQueryValueEx (hAppKey, subKey_Product, NULL, NULL, (LPBYTE)str_Product, &cbSize);

		RegCloseKey (hAppKey);

		if (ERROR_SUCCESS == dwFlag_Mau)
		{
			std::string strMaAndPro = "制造商:";
			strMaAndPro.append(str_Mau);

			if (ERROR_SUCCESS == dwFlag_Pro)
			{
				strMaAndPro.append("型号:");
				strMaAndPro.append(str_Product);
			}

			return strMaAndPro;
		}
	}

	return "";
}
