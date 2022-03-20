#pragma once
#include <windows.h>

class Wnd
{
public:
	Wnd(HINSTANCE hInst = NULL);
	~Wnd();
private:
	HWND hWnd = NULL;
	HINSTANCE hInstance = NULL;
public:
	// ���ش��ڶ�����
	HWND GetHandle();
protected:
	// ��Ϣ����
	virtual LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
	// ԭʼ���ڹ���
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	BOOL Init();   // ��������
	BOOL Show();   // ��ʾ����
	BOOL Hide();   // ���ش���
};
