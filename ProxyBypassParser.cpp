// ProxyParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
using std::wstring;
#include <Windows.h>
#include <winhttp.h>
#include "net/proxy/proxy_bypass_rules.h"
#include "base/strings/utf_string_conversions.h"
#pragma comment(lib, "winhttp.lib")


static bool parseAutoScript(LPWSTR autoscript_url, LPCWSTR target_url, wstring* proxyhost)
{
	HINTERNET session = ::WinHttpOpen(L"Tongbupan Simple Agent/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS,	WINHTTP_FLAG_ASYNC);
	if (session != NULL)
	{
		WINHTTP_AUTOPROXY_OPTIONS autoProxyOptions = { 0 };
		autoProxyOptions.dwFlags = WINHTTP_AUTOPROXY_CONFIG_URL;
		autoProxyOptions.lpszAutoConfigUrl = autoscript_url;
		WINHTTP_PROXY_INFO proxyinfo = { 0 };
		if (::WinHttpGetProxyForUrl(session, target_url, &autoProxyOptions, &proxyinfo))
		{
			*proxyhost = proxyinfo.lpszProxy;
			GlobalFree(proxyinfo.lpszProxy);
			GlobalFree(proxyinfo.lpszProxyBypass);
			return true;
		}
		WinHttpCloseHandle(session);
	}
	return false;
}

wstring getSystemProxyConfig(const wstring& target_url)
{
	wstring proxyhost;
	wstring wtarget_url = target_url;
	//use IE proxy setting
	WINHTTP_CURRENT_USER_IE_PROXY_CONFIG config = {0};
	if (WinHttpGetIEProxyConfigForCurrentUser( &config))
	{
		if (config.fAutoDetect)
		{
			LPWSTR autoscript_url = NULL;
			if(WinHttpDetectAutoProxyConfigUrl(WINHTTP_AUTO_DETECT_TYPE_DHCP|WINHTTP_AUTO_DETECT_TYPE_DNS_A, &autoscript_url))
			{
				if (parseAutoScript(autoscript_url, wtarget_url.c_str(), &proxyhost))
				{
					GlobalFree(autoscript_url);
					goto TheEnd;
				}
				GlobalFree(autoscript_url);
			}
		}

		if (config.lpszAutoConfigUrl != NULL)
		{
			if (parseAutoScript(config.lpszAutoConfigUrl, wtarget_url.c_str(), &proxyhost))
				goto TheEnd;			
		}

		if(config.lpszProxy != NULL)
		{
			wstring ie_proxy(config.lpszProxy);
			// we extract the first one
			size_t index = ie_proxy.find(L';');
			ie_proxy = ie_proxy.substr(0, index);
			
			//check if it bypass
			if (config.lpszProxyBypass != NULL)
			{
				net::ProxyBypassRules rules;
				rules.ParseFromString(base::WideToUTF8(config.lpszProxyBypass));
				if (rules.Matches(GURL(target_url)))
					goto TheEnd;
			}
			
			proxyhost = ie_proxy;
			goto TheEnd;		
		}
TheEnd:
		GlobalFree(config.lpszAutoConfigUrl);
		GlobalFree(config.lpszProxy);
		GlobalFree(config.lpszProxyBypass);		//ignore proxy by pass

	}
	return proxyhost;
}

int _tmain(int argc, _TCHAR* argv[])
{
	wstring proxy = getSystemProxyConfig(L"http://10.12.68.168/home/");
	wprintf(L"proxy:%ls", proxy.c_str());
	return 0;
}
