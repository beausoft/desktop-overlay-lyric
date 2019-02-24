#pragma once

#include "resource.h"
//宏
#define MAX_LOADSTRING 100

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);//主窗口消息处理函数
BOOL WindowCreate(HWND hWnd);//窗口创建完成执行
BOOL ShowCreateWindow(HINSTANCE hInstance,int nCmdShow);	//创建主窗口
BOOL WindowCommand(UINT msg,WPARAM wParam,LPARAM lParam);			//主窗口COMMAND处理

//全局变量
HINSTANCE hIns;	//当前实例
TCHAR szTitle[MAX_LOADSTRING];// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];// 主窗口类名
HWND hWnd;		//主窗口句柄

BackLRC *back_lrc;