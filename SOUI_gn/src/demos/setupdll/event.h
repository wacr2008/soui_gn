/**
* Copyright (C) 2014-2050 SongJia
* All rights reserved.
*
* @file       event.h
* @brief	  自定义消息
* @version    v1.0
* @author     SongJia
* @date       2015-04-23
*
* Describe     程序与NSIS脚本交互得采用消息机制，否则直接调用程序方法会阻塞主程序程序执行。
*/


#ifndef ___EVENT__H___
#define ___EVENT__H___
//设置tab视图切换
#define WM_SJTABSETSEL (WM_USER+400)
//////第一视图 Welcome 消息/////
//复选框状态变更通知
#define WM_SJONECHECKSTATUS (WM_USER+300)
//进入软件许可协议视图消息
#define WM_SJONELINKAGREEMENT (WM_USER+302)
//进入自定义安装视图消息
#define WM_SJONECUSTOMINSTALL (WM_USER+303)
//进入安装界面消息
#define WM_SJONEINSTALL (WM_USER+304)

//////第二视图 agreement 消息/////
#define WM_SJTWOSURE (WM_USER+310)

//////第三视图 choose 消息/////
//上一步消息
#define WM_SJTHREEPREVIOUS (WM_USER+320)
//进入安装界面消息
#define WM_SJTHREEINSTALL WM_SJONEINSTALL
//更新可用磁盘空间
#define WM_SJTHREEUPDATEFREESPACE (WM_USER+321)
//更新所需磁盘空间
#define WM_SJTHREEUPDATEREQUIREDSPACE (WM_USER+322)

//停止消息循环，使安装程序继续执行。
#define WM_SJMSGLOOPSTOP (WM_USER+323)

//////第四视图 installing 消息/////

//////第五视图 finish 消息/////


/////卸载///////
////第一视图 unstallstart////
#define WM_SJUNSTALLSTARTNEXT (WM_USER+353)


#endif