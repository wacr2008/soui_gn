// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

#define  _CRT_SECURE_NO_WARNINGS
#define	 DLL_SOUI
#include <souistd.h>
#include <core/SHostDialog.h>
#include <control/SMessageBox.h>
#include <control/souictrls.h>
#include <res.mgr/sobjdefattr.h>
#include <com-cfg.h>
#include "resource.h"
#define R_IN_CPP	//定义这个开关来
#include "res\resource.h"

// 拓展 tileview 基类
#include <helper/SAdapterBase.h>

// stl
#include <vector>
#include <memory>
#include <set>

// 定义网格横纵格数
#define NET_ROW_NUMBER  7
#define NET_COL_NUMBER	8

// 定义四种图像按钮皮肤
#define SKIN_STAR		L"skin_btn_star"
#define SKIN_HEART		L"skin_btn_heart"
#define SKIN_SWORD		L"skin_btn_sword"
#define SKIN_SHIELD		L"skin_btn_shield"
#define SKIN_DELETE		L"skin_btn_delete"

// 定义计时器
#define TIMER_LAND		100

using namespace SOUI;

