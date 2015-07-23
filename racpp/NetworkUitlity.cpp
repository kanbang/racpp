#include "StdAfx.h"
#include "NetworkUitlity.h"
#include "restclient\restclient.h"

long NetworkUitlity::paramleng = 256L;
//std::string NetworkUitlity::DEFAULT_CHARSET = " HTTP.UTF_8";
NetworkUitlity::NetworkUitlity(void)
{
}


NetworkUitlity::~NetworkUitlity(void)
{
}

MyMessage NetworkUitlity::PostMsg( std::string url, std::string data )
{
	MyMessage message;

	RestClient::response resp = RestClient::post(url, "application/x-www-form-urlencoded", "content="+data);
	std::string returnContent = resp.body;
	int status = resp.code;

	switch (status) 
	{
		case 200:
			message.setFlag(true);
			message.setMsg(returnContent);
			break;

		default:
			message.setFlag(false);
			message.setMsg(returnContent);
			break;
	}

	return message;
	// 		HttpClient httpclient = new DefaultHttpClient();
	// 		HttpPost httppost = new HttpPost(url);
	// 		try {
	// 			StringEntity se = new StringEntity("content="+data, HTTP.UTF_8);
	// 			CommonUtil.printLog("postdata", "content="+data);
	// 			se.setContentType("application/x-www-form-urlencoded");
	// 			httppost.setEntity(se);
	// 			HttpResponse response = httpclient.execute(httppost);
	// 			int status = response.getStatusLine().getStatusCode();
	// 			CommonUtil.printLog("ums",status+"");
	// 			String returnXML = EntityUtils.toString(response.getEntity());
	// 			returnContent = URLDecoder.decode(returnXML);
	// 			switch (status) {
	// 			case 200:
	// 				message.setFlag(true);
	// 				message.setMsg(returnContent);
	// 				break;
	// 
	// 			default:
	// 				Log.e("error", status+returnContent);
	// 				message.setFlag(false);
	// 				message.setMsg(returnContent);
	// 				break;
	// 			}
	// 		} catch (Exception e) {	
	// 			JSONObject jsonObject = new JSONObject();
	// 
	// 				jsonObject.put("err", e.toString());
	// 				returnContent = jsonObject.toString();
	// 				message.setFlag(false);
	// 				message.setMsg(returnContent);
	// 
	// 		}
	//张修华 ok
}

std::string NetworkUitlity::Post( std::string url, std::string data )
{
// 	HttpClient httpclient = new DefaultHttpClient();
// 	HttpPost httppost = new HttpPost(url);
// 	StringEntity se = new StringEntity("content="+data, HTTP.UTF_8);
// 	CommonUtil.printLog("postdata", "content="+data);
// 	se.setContentType("application/x-www-form-urlencoded");
// 	httppost.setEntity(se);
// 	HttpResponse response = httpclient.execute(httppost);
	RestClient::response resp = RestClient::post(url, "application/x-www-form-urlencoded", "content="+data);
	return resp.body;
	//张修华 ok
}
