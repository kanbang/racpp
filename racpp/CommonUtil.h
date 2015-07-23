#pragma once
#include "LatitudeAndLongitude.h"
#include <vector>
#include <string>
#include <winioctl.h>

class JSONObject;
class HandlerThread;
typedef std::vector<std::string> vec_string;

class CommonUtil
{
public:
	static void saveInfoToFile(HandlerThread* handler, std::string type, const JSONObject& info);
	static std::string bindUserIdentifier(const std::string& identifier);
	static std::string getUserIdentifier();
	static bool isNetworkAvailable();
	static std::string getTime();
	static std::string getAppKey();
	static std::string getPackageName();
	static std::string getDeviceID();
	static std::string getSdkVersion();
	static std::string getCurVersion();
	static int getReportPolicyMode();
	static LatitudeAndLongitude getLatitudeAndLongitude();
	static std::string getModulePath();
	static std::string getScreenXY();
	static std::string getOsVersion();
	static vec_string GetINETMacAddresses();
	static std::string getCManufacturerAndProduct();

private:
	static BOOL __fastcall DoIdentify( HANDLE hPhysicalDriveIOCTL, 
		PSENDCMDINPARAMS pSCIP,
		PSENDCMDOUTPARAMS pSCOP, 
		BYTE btIDCmd, 
		BYTE btDriveNum,
		PDWORD pdwBytesReturned);

	static char *__fastcall ConvertToString(DWORD dwDiskData[256], int nFirstIndex, int nLastIndex);
	static std::string _getDiskInfo();

protected:
	static std::string user_identifier;
};

