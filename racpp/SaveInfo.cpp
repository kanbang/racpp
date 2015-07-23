#include "StdAfx.h"
#include "SaveInfo.h"
#include "CommonUtil.h"
#include <fstream>
#include <direct.h>
#include "JSONObject.h"
#include "JSONArray.h"
#include <imagehlp.h>

using namespace std;

SaveInfo::SaveInfo( JSONObject object )
{
	m_Object = object;
}

SaveInfo::~SaveInfo(void)
{
}

void SaveInfo::run()
{
	std::string sFileDir = getLogInfoDir();
	std::string sFilePathName = getLogInfoPathName();

//	MakeSureDirectoryPathExists(sFileDir.c_str());
	_mkdir(sFileDir.c_str());

	std::fstream file;
	file.open(sFilePathName, ios::in, _SH_DENYNO);

	int iFileSize = 0;
	JSONObject existJSON;

	if (file.is_open())
	{
		file.seekg(0, ios::end);
		iFileSize = file.tellg();
		char *pFileData = new char[iFileSize+1];
		file.seekg(0, ios::beg);
		file.read(pFileData, iFileSize);
		pFileData[iFileSize] = '\0';
		file.close();

		existJSON.parse(pFileData);
		delete[] pFileData;
	}

	if (iFileSize > 0)
	{
		std::map<std::string, jsonxx::Value*>& kvMap = m_Object.kv_map();

		std::string key;
		for (auto i=kvMap.begin(); i!=kvMap.end(); i++)
		{
			key = (*i).first;
			JSONArray* newData = m_Object.getJsonArr(key);
			if(newData && existJSON.hasKey(key))
			{
				JSONArray* newDataArray = existJSON.getJsonArr(key);
				if (newDataArray)
				{
					newDataArray->put(newData->get<jsonxx::Object>(0));
				}
			}
			else
			{
				existJSON.put(key, *(m_Object.getJsonArr(key)));
			}
		}

		file.open(sFilePathName, ios::out | ios::trunc, _SH_DENYRW);
		if (!file.is_open())
		{
			return;
		}

		std::string sJsonStr = existJSON.json();
		file.write(sJsonStr.c_str(), sJsonStr.length());
		file.close();
		////
// 		Iterator iterator = object.keys();
// 
// 		while(iterator.hasNext()){
// 			String key = (String) iterator.next();
// 			JSONArray newData = object.getJSONArray(key);
// 
// 			if(existJSON.has(key)){
// 				JSONArray newDataArray = existJSON.getJSONArray(key);
// 				CommonUtil.printLog("SaveInfo", newData+"");
// 				newDataArray.put(newData.get(0));
// 			}else{
// 				existJSON.put(key, object.getJSONArray(key));
// 				CommonUtil.printLog("SaveInfo", "jsonobject"+existJSON);
// 			}
// 
// 		}
// 		FileOutputStream fileOutputStream = new FileOutputStream(Environment.getExternalStorageDirectory()+"/mobclick_agent_cached_"+context.getPackageName(),false);
// 		fileOutputStream.write(existJSON.toString().getBytes());
// 		fileOutputStream.flush();
// 		fileOutputStream.close();
	}
	else
	{
		JSONObject allJSON;

		std::string key;

		std::map<std::string, jsonxx::Value*>& kvMap = m_Object.kv_map();
		for (auto i=kvMap.begin(); i!=kvMap.end(); i++)
		{
			key = (*i).first;
			JSONArray* newData = m_Object.getJsonArr(key);
			allJSON.put(key, *newData);		
		}

		ofstream ofile;
		ofile.open(sFilePathName, ios::out | ios::trunc, _SH_DENYRW);
		if (!ofile.is_open())
		{
			return;
		}

		std::string sJsonStr = allJSON.json();
		ofile.write(sJsonStr.c_str(), sJsonStr.length());
		ofile.close();

		//////////////////////////////////////////////////////////////////////////
// 		Iterator iterator = object.keys();
// 		JSONObject jsonObject = new JSONObject();
// 		while(iterator.hasNext()){
// 			String key = (String) iterator.next();
// 			JSONArray array = object.getJSONArray(key);
// 
// 			jsonObject.put(key, array);
// 
// 		}
// 		jsonObject.put("appkey", CommonUtil.getAppKey(context));
// 
// 		FileOutputStream fileOutputStream = new FileOutputStream(Environment.getExternalStorageDirectory()+"/mobclick_agent_cached_"+context.getPackageName(),false);
// 		fileOutputStream.write(jsonObject.toString().getBytes());
// 		fileOutputStream.flush();
// 		fileOutputStream.close();
	}
	
	/*
	std::ofstream file;
	file.open("./mobclick_agent_cached_"+CommonUtil::getPackageName(), std::ios::in);
	File file = new File(Environment.getExternalStorageDirectory().getAbsolutePath()+);
	if(file.exists())
	{
		CommonUtil.printLog("path", file.getAbsolutePath());
	}
	else
	{
		file.createNewFile();
		CommonUtil.printLog("path", "No path");
	}

	FileInputStream in = new FileInputStream(Environment.getExternalStorageDirectory().getAbsolutePath()+"/mobclick_agent_cached_"+context.getPackageName());
	StringBuffer sb = new StringBuffer();

	int i=0;
	byte[] s = new byte[1024*4];

	while((i=in.read(s))!=-1){

		sb.append(new String(s,0,i));
	}
	if(sb.length()!=0){
		JSONObject existJSON(sb.toString());

		Iterator iterator = object.keys();

		while(iterator.hasNext()){
			String key = (String) iterator.next();
			JSONArray newData = object.getJSONArray(key);

			if(existJSON.has(key)){
				JSONArray newDataArray = existJSON.getJSONArray(key);
				CommonUtil.printLog("SaveInfo", newData+"");
				newDataArray.put(newData.get(0));
			}else{
				existJSON.put(key, object.getJSONArray(key));
				CommonUtil.printLog("SaveInfo", "jsonobject"+existJSON);
			}

		}
		FileOutputStream fileOutputStream = new FileOutputStream(Environment.getExternalStorageDirectory()+"/mobclick_agent_cached_"+context.getPackageName(),false);
		fileOutputStream.write(existJSON.toString().getBytes());
		fileOutputStream.flush();
		fileOutputStream.close();

	}else{
		Iterator iterator = object.keys();
		JSONObject jsonObject = new JSONObject();
		while(iterator.hasNext()){
			String key = (String) iterator.next();
			JSONArray array = object.getJSONArray(key);

			jsonObject.put(key, array);

		}
		jsonObject.put("appkey", CommonUtil.getAppKey(context));

		FileOutputStream fileOutputStream = new FileOutputStream(Environment.getExternalStorageDirectory()+"/mobclick_agent_cached_"+context.getPackageName(),false);
		fileOutputStream.write(jsonObject.toString().getBytes());
		fileOutputStream.flush();
		fileOutputStream.close();
	}
	*/	//ÕÅÐÞ»ª ok
}

std::string SaveInfo::getLogInfoDir()
{
	std::string sFileDir = CommonUtil::getModulePath();
	int iLastPos = sFileDir.find_last_of('\\');
	if (iLastPos == -1)
	{
		return "";
	}

	sFileDir = sFileDir.substr(0, iLastPos) + ("\\logInfo");
	return sFileDir;
}

std::string SaveInfo::getLogInfoPathName()
{
	return getLogInfoDir() + "\\raLogInfo.txt";
}
