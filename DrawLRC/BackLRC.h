#pragma once
#include "resource.h"
#define MAX_LOADSTRING 100
class BackLRC{
public:
	HWND hwnd_main;		//主窗口句柄
	HWND hwnd_BackLRC;	//背景句柄
	HINSTANCE backhIns;	//当前实例
	TCHAR backszWindowClass[MAX_LOADSTRING];// 窗口类名
	BackLRC(HINSTANCE hInstance,HWND h_main);	//构造函数
	~BackLRC();	//析构函数
private:
	ATOM RegisterClass();	//注册窗口
	BOOL InitBackLRCWindow();					//初始化窗口
	BOOL ImageFromIDResource(HINSTANCE hInst,UINT nID, LPCTSTR sTR,GpImage * &pImg);//从资源加载img到gdi
public:
	HWND GetBackLRCHandle();				//获取窗口句柄
	BOOL MakeTrans(HWND hWnd,HDC hdc);			//绘图方法
	BOOL CreateBackLRCWindow();	//创建背景窗口
	BOOL CloseBackLRCWindow();	//关闭窗口
};
LRESULT CALLBACK Back_WndProc(HWND, UINT, WPARAM, LPARAM);//窗口消息处理函数