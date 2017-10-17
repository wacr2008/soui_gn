/**
* Copyright (C) 2014-2050 SongJia
* All rights reserved.
*
* @file       Utils.h
* @brief	  工具类
* @version    v1.0
* @author     SongJia
* @date       2015-04-23
*
* Describe     解决字符转码、方便对NSIS脚本程序与插件交互堆栈结构变量stack_t存取。
*/

#ifndef ___UTILS__H___
#define ___UTILS__H___
#include <string>
using namespace std;
#include "pluginapi.h" // nsis plugin



void Wchar_tToString(std::string& szDst, wchar_t *wchar)
{
    wchar_t * wText = wchar;
    DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte的运用
    char *psText;  // psText为char*的临时数组，作为赋值给std::string的中间变量
    psText = new char[dwNum];
    WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte的再次运用
    szDst = psText;// std::string赋值
    delete[]psText;// psText的清除
}

// string to wstring
void StringToWstring(std::wstring& szDst, std::string str)
{
    std::string temp = str;
    int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, NULL, 0);
    wchar_t * wszUtf8 = new wchar_t[len + 1];
    memset(wszUtf8, 0, len * 2 + 2);
    MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, (LPWSTR)wszUtf8, len);
    szDst = wszUtf8;
    std::wstring r = wszUtf8;
    delete[] wszUtf8;
}
void PopString(std::wstring& szDst)
{
    char tmpPathA[1024];
    ZeroMemory(tmpPathA, 1024);
    popstringA(tmpPathA);
    string tmpStr = tmpPathA;
    StringToWstring(szDst, tmpStr);
    //MessageBox(NULL, szDst.c_str(),_T("8"), MB_OK);
}

void PushString(std::wstring& szDst)
{
    string tmp;
    wstring s = szDst;
    wchar_t a[1024];
    ZeroMemory(a, 1024);
    lstrcpynW(a, s.c_str(), s.length() + 1);
    Wchar_tToString(tmp, a);
    pushstringA(tmp.c_str());
}


#endif
