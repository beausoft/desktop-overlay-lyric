#include "stdafx.h"
#include "DrawLRC.h"
#include "resource.h"

ULONG token;	//GDI+句柄
HINSTANCE hInstance;	//应用程序实例句柄
HWND back_hwnd;		//背景窗口句柄
HWND show_hwnd;		//显示歌词窗口句柄
HWND lrc_hwnd;		//卡拉ok窗口句柄
BOOL isMousePrees;	//鼠标是否按下
HDC mdc;
HBITMAP mainBitmap;
HGDIOBJ oldBitmap;
BLENDFUNCTION blendFunc32bpp;
POINT mouse_xy;
//字体
GdiFont GFont;
GpFontFamily *fontFam=NULL;
GpStringFormat *strFormat=NULL;
GpPath *strPath=NULL;
Rect rclayout;
//显示窗口变量声明
HDC mdc_show=NULL;
HBITMAP mainBitmap_show=NULL;
HGDIOBJ oldBitmap_show=NULL;
GpFontFamily *fontFam_show=NULL;
GpStringFormat *strFormat_show=NULL;
GpPath *strPath_show=NULL;
GpLineGradient *Brush_show=NULL;
GpPen *pen_show=NULL;
GpGraphics *graphics_show=NULL;
HDC dc_show=NULL;	//显示窗口的DC
//卡拉ok窗口变量
HDC mdc_lrc;
HGDIOBJ oldBitmap_lrc=NULL;
HBITMAP mainBitmap_lrc=NULL;
GpFontFamily *fontFam_lrc=NULL;
GpStringFormat *strFormat_lrc=NULL;
GpPath *strPath_lrc=NULL;
GpLineGradient *Brush_lrc=NULL;
GpPen *pen_lrc=NULL;
GpGraphics *graphics_lrc=NULL;
Rect rclayout_lrc;
HDC dc_lrc=NULL;	//卡拉OK窗口的DC

//颜色变量
LRC_COLOR drawlrc_color;

//歌词文本
WCHAR *LRCText=NULL;
LONG LrcTime=0;	//歌词时间
INT str_count=0;	//字符数量
INT str_width=0;	//字符宽度

BOOL isInitLRC=FALSE;
BOOL isLocking=FALSE;

//声明外部方法
extern "C" _declspec(dllexport) void CreateLRC();
extern "C" _declspec(dllexport) void About();
extern "C" _declspec(dllexport) void InitGDI();
extern "C" _declspec(dllexport) BOOL ReleaseDrawLRC();
extern "C" _declspec(dllexport) void DrawLRC_SHOW_TEXT(WCHAR *text);
extern "C" _declspec(dllexport) void SetLRCColor(LRC_COLOR lrc_color);
extern "C" _declspec(dllexport) void SetDrawLRCTime(LONG time);
extern "C" _declspec(dllexport) void LockingLRC();
//实现外部方法
void CreateLRC(){
	if(!isInitLRC){
		isInitLRC=TRUE;	//设置初始化完成
		//初始化字体
		GFont.FontBold=FALSE;
		GFont.FontName=_T("黑体");
		GFont.FontSize=41;
		GFont.FontWidth=0;
		GFont.LineColor=0;
		GFont.OkColor1=0;
		GFont.OKColor2=0;
		drawlrc_color=LRC_COLOR_White;
		LRC_BACK_COLOR show_color=GetShowColor(drawlrc_color);
		GFont.ForeColor1=show_color.LRC_BACK_COLOR1;
		GFont.ForeColor2=show_color.LRC_BACK_COLOR2;
		CreateLrcWindow();
		CreateShowWindow();
		CreateBackWindow();

		RECT show_rect;
		GetWindowRect(show_hwnd,&show_rect);
		RECT back_rect;
		GetWindowRect(back_hwnd,&back_rect);
		MoveWindow(back_hwnd,0,show_rect.top-(130-GFont.FontSize)/3,back_rect.right-back_rect.left,back_rect.bottom-back_rect.top,TRUE);

		SetZOrder();
	}
}
void About(){
	MessageBox(NULL,_T("本程序由韩济蓬制作，QQ:546168949。\r\n本程序不可用于商业用途，否则造成一切纠纷本人概不负责。"),_T("关于...By:韩济蓬"),MB_OK);
}
void InitGDI(){
	GdiplusStartupInput GpInput;
	GpInput.GdiplusVersion=1;
	if(GdiplusStartup(&token,&GpInput,NULL)!=0){
		MessageBox(NULL,_T("Fehler bem laden von GDI+!"),_T("提示"),MB_OK);
	}
}
BOOL ReleaseDrawLRC(){
	GdiplusShutdown(token);//释放GDI+
	//释放背景窗口
	SelectObject(mdc,oldBitmap);
	DeleteObject(mainBitmap);
	DeleteObject(oldBitmap);
	DeleteDC(mdc);
	//DestroyWindow(back_hwnd);	//销毁窗口
	//释放显示窗口
	SelectObject(mdc_show,oldBitmap_show);
	DeleteObject(mainBitmap_show);
	DeleteObject(oldBitmap_show);
	DeleteDC(mdc_show);
	GdipDeleteFontFamily(fontFam_show);
	GdipDeleteStringFormat(strFormat_show);
	GdipDeletePath(strPath_show);
	GdipDeleteBrush(Brush_show);
	GdipDeletePen(pen_show);
	GdipDeleteGraphics(graphics_show);
	return TRUE;
}
void DrawLRC_SHOW_TEXT(WCHAR *text){
	ShowWindow(lrc_hwnd,SW_HIDE);	//隐藏窗口
	KillTimer(lrc_hwnd,TIMELRC);
	//RECT lrc_rect_tmp;
	//GetWindowRect(lrc_hwnd,&lrc_rect_tmp);
	//MoveWindow(lrc_hwnd,lrc_rect_tmp.left,lrc_rect_tmp.top,0,lrc_rect_tmp.bottom-lrc_rect_tmp.top,TRUE);
	Show_DrawText(text,dc_show);
	lrc_DrawText(text,dc_lrc);
	LRCText=text;
}
void SetLRCColor(LRC_COLOR lrc_color){
	drawlrc_color=lrc_color;
	LRC_BACK_COLOR show_color=GetShowColor(lrc_color);
	GFont.ForeColor1=show_color.LRC_BACK_COLOR1;
	GFont.ForeColor2=show_color.LRC_BACK_COLOR2;
	//设置完颜色需要从绘
	Show_DrawText(LRCText,dc_show);
	//RECT lrc_rect_tmp;
	//GetWindowRect(lrc_hwnd,&lrc_rect_tmp);
	//INT ScreenWidth=GetSystemMetrics(SM_CXSCREEN);	//获取屏幕宽度
	//INT lrc_widtmp=lrc_rect_tmp.right-lrc_rect_tmp.left;
	//MoveWindow(lrc_hwnd,lrc_rect_tmp.left,lrc_rect_tmp.top,ScreenWidth,lrc_rect_tmp.bottom-lrc_rect_tmp.top,TRUE);
	lrc_DrawText(LRCText,dc_lrc);
	//MoveWindow(lrc_hwnd,lrc_rect_tmp.left,lrc_rect_tmp.top,lrc_widtmp,lrc_rect_tmp.bottom-lrc_rect_tmp.top,TRUE);
}
void SetDrawLRCTime(LONG time){
	if(LRCText!=NULL){
		KillTimer(lrc_hwnd,TIMELRC);
		LrcTime=time;

		str_count=wcslen(LRCText);
		str_width=str_count*GFont.FontSize;
		
		RECT lrc_rect_tmp;
		GetWindowRect(lrc_hwnd,&lrc_rect_tmp);
		INT ScreenWidth=GetSystemMetrics(SM_CXSCREEN);	//获取屏幕宽度
		INT Width=(ScreenWidth-str_width)/2;		
		MoveWindow(lrc_hwnd,lrc_rect_tmp.left,lrc_rect_tmp.top,Width,lrc_rect_tmp.bottom-lrc_rect_tmp.top,TRUE);
		//SetWindowPos(lrc_hwnd,HWND_TOPMOST,NULL,NULL,Width,lrc_rect_tmp.bottom-lrc_rect_tmp.top,SWP_NOMOVE);
		//UpdateWindow(lrc_hwnd);
		ShowWindow(lrc_hwnd,SW_SHOWNOACTIVATE);	//显示窗口不激活窗口
		SetTimer(lrc_hwnd,TIMELRC,10,TimerProc);	//设置定时器
	}
}
void LockingLRC(){
	LONG lrc_ret=GetWindowLong(lrc_hwnd,GWL_EXSTYLE);
	LONG show_ret=GetWindowLong(show_hwnd,GWL_EXSTYLE);

	if(!isLocking){
		lrc_ret=lrc_ret|WS_EX_LAYERED|WS_EX_TRANSPARENT;
		SetWindowLong(lrc_hwnd,GWL_EXSTYLE,lrc_ret);
		show_ret=show_ret|WS_EX_LAYERED|WS_EX_TRANSPARENT;
		SetWindowLong(show_hwnd,GWL_EXSTYLE,show_ret);
		isLocking=TRUE;
	}else{
		lrc_ret=lrc_ret^WS_EX_TRANSPARENT;
		SetWindowLong(lrc_hwnd,GWL_EXSTYLE,lrc_ret);
		show_ret=show_ret^WS_EX_TRANSPARENT;
		SetWindowLong(show_hwnd,GWL_EXSTYLE,show_ret);
		isLocking=FALSE;
	}
}

BOOL sethInstance(HINSTANCE hIns){
	hInstance=hIns;
	return TRUE;
}
HWND getBACK_HWND(){
	return back_hwnd;
}
//创建背景窗口
BOOL CreateBackWindow(){
	RECT rect;
	int ScreenWidth=GetSystemMetrics(SM_CXSCREEN);	//获取屏幕宽度
	int Rwheight=GetSystemMetrics(SM_CYFULLSCREEN);	//获取可见屏幕高度(不包括任务栏)
	rect.left=0;
	rect.right=ScreenWidth;
	rect.top=Rwheight-103;
	rect.bottom=Rwheight+103;
	CreateWindowUniversal(back_hwnd,_T("lrc_back"),Back_WndProc,rect);
	HDC hdc_back;
	hdc_back=GetWindowDC(back_hwnd);
	MakeTrans(back_hwnd,hdc_back);	//绘制背景窗口
	//ShowWindow(back_hwnd,SW_SHOW);	//之前窗口是隐藏的，防止闪烁
	return TRUE;
}
//创建显示歌词窗口
BOOL CreateShowWindow(){
	RECT rect;
	int ScreenWidth=GetSystemMetrics(SM_CXSCREEN);	//获取屏幕宽度
	//int ScrrenHeight=GetSystemMetrics(SM_CYSCREEN);	//获取屏幕高度
	int Rwheight=GetSystemMetrics(SM_CYFULLSCREEN);	//获取可见屏幕高度(不包括任务栏)
	rect.left=0;
	rect.right=ScreenWidth;
	rect.top=Rwheight-103;
	rect.bottom=Rwheight+103;
	CreateWindowUniversal(show_hwnd,_T("lrc_show"),Show_WndProc,rect);
	SetWindowPos(show_hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	dc_show=GetWindowDC(show_hwnd);
	Show_DrawText(_T("黑客工程，桌面歌词"),dc_show);
	ShowWindow(show_hwnd, SW_SHOW);
	return TRUE;
}
//创建卡拉ok窗口
BOOL CreateLrcWindow(){
	RECT rect;
	int ScreenWidth=GetSystemMetrics(SM_CXSCREEN);	//获取屏幕宽度
	//int ScrrenHeight=GetSystemMetrics(SM_CYSCREEN);	//获取屏幕高度
	int Rwheight=GetSystemMetrics(SM_CYFULLSCREEN);	//获取可见屏幕高度(不包括任务栏)
	rect.left=0;
	rect.right=ScreenWidth;
	rect.top=Rwheight-103;
	rect.bottom=Rwheight+103;
	CreateWindowUniversal(lrc_hwnd,_T("lrc_lrc"),Lrc_WndProc,rect);
	SetWindowPos(lrc_hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	dc_lrc=GetWindowDC(lrc_hwnd);
	lrc_DrawText(_T("黑客工程，桌面歌词"),dc_lrc);
	//ShowWindow(lrc_hwnd, SW_SHOW);
	return TRUE;
}
//背景窗口消息处理函数
LRESULT CALLBACK Back_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
		case WM_COMMAND:
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			//MakeTrans(hWnd,hdc);	//绘制背景
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CREATE:
			SetTimer(hWnd,TIMEWINDMONITOR,100,TimerProc);	//设置定时器
			break;
		case WM_LBUTTONDOWN:	//鼠标按下
			SetCapture(hWnd);	//独占鼠标消息
			mouse_xy.y=HIWORD(lParam);
			isMousePrees=TRUE;
			break;
		case WM_LBUTTONUP:		//鼠标松开
			ReleaseCapture();	//释放独占鼠标消息
			isMousePrees=FALSE;
			break;
		case WM_MOUSEMOVE:		//鼠标移动
			if(isMousePrees){
				RECT win_re;	//窗口大小变量
				GetWindowRect(hWnd,&win_re);	//获取窗口大小
				int MOUSE_Y=HIWORD(lParam);
				if(isMouseCoordinate(0,MOUSE_Y)){
				int Y=win_re.top+(MOUSE_Y-mouse_xy.y);
				MoveWindow(hWnd,0,Y,win_re.right-win_re.left,win_re.bottom-win_re.top,TRUE);	//移动窗口
				//移动显示歌词窗口和卡拉ok窗口
				RECT show_rect;
				GetWindowRect(show_hwnd,&show_rect);
				MoveWindow(show_hwnd,show_rect.left,Y+(130-GFont.FontSize)/3,show_rect.right-show_rect.left,show_rect.bottom-show_rect.top,TRUE);
				RECT lrc_rect;
				GetWindowRect(lrc_hwnd,&lrc_rect);
				MoveWindow(lrc_hwnd,show_rect.left,Y+(130-GFont.FontSize)/3,lrc_rect.right-lrc_rect.left,lrc_rect.bottom-lrc_rect.top,TRUE);
				}
			}
			break;
		case WM_KILLFOCUS:	//窗口失去焦点
			isMousePrees=FALSE;
			break;
		case WM_ACTIVATE:	//窗口激活
			//return MA_NOACTIVATEANDEAT;
			break;
		case WM_MOUSEACTIVATE:
			//return MA_NOACTIVATEANDEAT;
			break;
		case WM_MOUSEHOVER:	//鼠标离开窗口
			isMousePrees=FALSE;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
//显示歌词处理函数
LRESULT CALLBACK Show_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	HDC hdc;
	TRACKMOUSEEVENT tme;
	switch (message)
	{
		case WM_CREATE:
			break;
		case WM_COMMAND:
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		//case WM_MOUSEMOVE:
		//	tme.cbSize=sizeof(TRACKMOUSEEVENT);
		//	tme.dwFlags=TME_HOVER|TME_LEAVE;	//注册鼠标HOVER和LEAVE消息
		//	tme.dwHoverTime=100;				//事件触发时间
		//	tme.hwndTrack=hWnd;					//当前句柄
		//	TrackMouseEvent(&tme);				//注册
		//	break;
		case WM_LBUTTONDOWN:	//鼠标按下
			/*ReleaseCapture();
			SendMessage(hWnd,WM_SYSCOMMAND,SC_MOVE|HTCAPTION,0);*/
			SetCapture(hWnd);	//独占鼠标
			mouse_xy.y=HIWORD(lParam);
			mouse_xy.x=LOWORD(lParam);
			isMousePrees=TRUE;
			break;
		case WM_LBUTTONUP:		//鼠标松开
			isMousePrees=FALSE;
			ReleaseCapture();	//释放独占鼠标
			break;
		case WM_MOUSEMOVE:		//鼠标移动
			if(isMousePrees){
				RECT win_re;	//窗口大小变量
				GetWindowRect(hWnd,&win_re);	//获取窗口大小
				int MOUSE_Y=HIWORD(lParam);
				int MOUSE_X=LOWORD(lParam);
				if(isMouseCoordinate(MOUSE_X,MOUSE_Y)){
				int Y=win_re.top+(MOUSE_Y-mouse_xy.y);
				int X=win_re.left+(MOUSE_X-mouse_xy.x);
				MoveWindow(hWnd,X,Y,win_re.right-win_re.left,win_re.bottom-win_re.top,TRUE);	//移动窗口
				//移动背景窗口和lrc窗口
				RECT back_rect;
				GetWindowRect(back_hwnd,&back_rect);
				MoveWindow(back_hwnd,0,Y-(130-GFont.FontSize)/3,back_rect.right-back_rect.left,back_rect.bottom-back_rect.top,TRUE);
				RECT lrc_rect;
				GetWindowRect(lrc_hwnd,&lrc_rect);
				MoveWindow(lrc_hwnd,X,Y,lrc_rect.right-lrc_rect.left,lrc_rect.bottom-lrc_rect.top,TRUE);
				}
			}
			break;
		//case WM_MOUSEHOVER:
		//	if(!isBackShow){
		//		ShowWindow(back_hwnd,SW_SHOW);
		//		isBackShow=TRUE;
		//	}
		//	break;
		//case WM_MOUSELEAVE:
		//	/*if(isBackShow){
		//		ShowWindow(back_hwnd,SW_HIDE);
		//		isBackShow=FALSE;
		//	}*/
		//	break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
//卡拉ok处理函数
LRESULT CALLBACK Lrc_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
		case WM_COMMAND:
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CREATE:
			break;
		case WM_LBUTTONDOWN:	//鼠标按下
			/*ReleaseCapture();
			SendMessage(hWnd,WM_SYSCOMMAND,SC_MOVE|HTCAPTION,0);*/
			SetCapture(hWnd);	//独占鼠标
			mouse_xy.y=HIWORD(lParam);
			mouse_xy.x=LOWORD(lParam);
			isMousePrees=TRUE;
			break;
		case WM_LBUTTONUP:		//鼠标松开
			isMousePrees=FALSE;
			ReleaseCapture();	//释放独占鼠标
			break;
		case WM_MOUSEMOVE:		//鼠标移动
			if(isMousePrees){
				RECT win_re;	//窗口大小变量
				GetWindowRect(hWnd,&win_re);	//获取窗口大小
				int MOUSE_Y=HIWORD(lParam);
				int MOUSE_X=LOWORD(lParam);
				if(isMouseCoordinate(MOUSE_X,MOUSE_Y)){
				int Y=win_re.top+(MOUSE_Y-mouse_xy.y);
				int X=win_re.left+(MOUSE_X-mouse_xy.x);
				MoveWindow(hWnd,X,Y,win_re.right-win_re.left,win_re.bottom-win_re.top,TRUE);	//移动窗口
				//移动显示歌词窗口和背景窗口
				RECT show_rect;
				GetWindowRect(show_hwnd,&show_rect);
				MoveWindow(show_hwnd,X,Y,show_rect.right-show_rect.left,show_rect.bottom-show_rect.top,TRUE);
				RECT back_rect;
				GetWindowRect(back_hwnd,&back_rect);
				MoveWindow(back_hwnd,0,Y-(130-GFont.FontSize)/3,back_rect.right-back_rect.left,back_rect.bottom-back_rect.top,TRUE);
				}
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
//卡拉OK绘制方法
BOOL lrc_DrawText(const WCHAR* text,HDC hdc){
	SelectObject(mdc_lrc,oldBitmap_lrc);
	DeleteObject(mainBitmap_lrc);
	DeleteObject(oldBitmap_lrc);
	DeleteDC(mdc_lrc);
	GdipDeleteFontFamily(fontFam_lrc);
	GdipDeleteStringFormat(strFormat_lrc);
	GdipDeletePath(strPath_lrc);
	GdipDeleteBrush(Brush_lrc);
	GdipDeletePen(pen_lrc);
	GdipDeleteGraphics(graphics_lrc);
	//释放资源
	BITMAPINFO tempBI;
	BLENDFUNCTION tempBlend;
	UINT lngHeight=0,lngWidth=0;
	LONG curWinLong=0;
	SIZE winSize;
	POINT srcPoint;
	//获取窗口位置
	RECT rect;
	GetWindowRect(lrc_hwnd,&rect);

	memset(&tempBI,0,sizeof(BITMAPINFO));
	tempBI.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	tempBI.bmiHeader.biBitCount=32;
	tempBI.bmiHeader.biHeight=rect.bottom-rect.top;
	tempBI.bmiHeader.biWidth=rect.right-rect.left;
	tempBI.bmiHeader.biPlanes=1;
	tempBI.bmiHeader.biCompression=BI_RGB;
	tempBI.bmiHeader.biSizeImage=tempBI.bmiHeader.biWidth * tempBI.bmiHeader.biHeight * (tempBI.bmiHeader.biBitCount / 8);

	mdc_lrc=CreateCompatibleDC(hdc);
	VOID *ppvBits;
	mainBitmap_lrc=CreateDIBSection(mdc_lrc,&tempBI,DIB_RGB_COLORS,&ppvBits,NULL,NULL);
	oldBitmap_lrc=SelectObject(mdc_lrc,mainBitmap_lrc);

	GdipCreateFromHDC(mdc_lrc,&graphics_lrc);

	//-------------------------------
	GdipSetSmoothingMode(graphics_lrc,SmoothingModeHighQuality);
	GdipCreateFontFamilyFromName(GFont.FontName,NULL,&fontFam_lrc);
	GdipCreateStringFormat(NULL,NULL,&strFormat_lrc);
	GdipSetStringFormatAlign(strFormat_lrc,StringAlignmentCenter);

	GpRectF rectf1;
	rectf1.Height=GFont.FontSize;
	rectf1.Width=GFont.FontSize;
	rectf1.X=0;
	rectf1.Y=0;
	//填充坐标
	LRC_BACK_COLOR lrc_color=GetLRCOKColor(drawlrc_color);
	GdipCreateLineBrushFromRect(&rectf1,lrc_color.LRC_BACK_COLOR1,lrc_color.LRC_BACK_COLOR2,LinearGradientModeVertical,WrapModeTileFlipXY,&Brush_lrc);

	rclayout_lrc.X=0;
	rclayout_lrc.Y=0;
	rclayout_lrc.Width=GetSystemMetrics(SM_CXSCREEN);	//获取屏幕宽度
	rclayout_lrc.Height=0;


	GdipCreatePath(FillModeAlternate,&strPath_lrc);
	GdipAddPathStringI(strPath_lrc,text,-1,fontFam_lrc,FontStyleBold,GFont.FontSize,&rclayout_lrc,strFormat_lrc);

	GdipFillPath(graphics_lrc,Brush_lrc,strPath_lrc);
	GdipDrawPath(graphics_lrc,pen_lrc,strPath_lrc);

	curWinLong=GetWindowLong(lrc_hwnd,GWL_EXSTYLE);
	if(curWinLong!=WS_EX_LAYERED)
		SetWindowLong(lrc_hwnd,GWL_EXSTYLE,curWinLong|WS_EX_LAYERED);

	srcPoint.x=0;
	srcPoint.y=0;
	winSize.cx=rect.right-rect.left;
	winSize.cy=rect.bottom-rect.top;

	blendFunc32bpp.AlphaFormat=AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags=0;
	blendFunc32bpp.BlendOp=AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha=255;
	POINT ptWinPos ={rect.left,rect.top };

	GdipDeleteGraphics(graphics_lrc);
	UpdateLayeredWindow(lrc_hwnd,hdc,&ptWinPos,&winSize,mdc_lrc,&srcPoint,0,&blendFunc32bpp,ULW_ALPHA);
	return TRUE;
}
//显示歌词绘制
BOOL Show_DrawText(const WCHAR* text,HDC hdc){
	SelectObject(mdc_show,oldBitmap_show);
	DeleteObject(mainBitmap_show);
	DeleteObject(oldBitmap_show);
	DeleteDC(mdc_show);
	GdipDeleteFontFamily(fontFam_show);
	GdipDeleteStringFormat(strFormat_show);
	GdipDeletePath(strPath_show);
	GdipDeleteBrush(Brush_show);
	GdipDeletePen(pen_show);
	GdipDeleteGraphics(graphics_show);//释放graphics占用的内存
	//释放上次使用的资源
	BITMAPINFO tempBI;
	BLENDFUNCTION tempBlend;
	long curWinLong;
	SIZE winSize;
	POINT srcPoint;

	INT Screen_Width=GetSystemMetrics(SM_CXSCREEN);	//屏幕宽度

	//获取窗口位置
	RECT rect;
	GetWindowRect(show_hwnd,&rect);
	//BITMAPINFO结构赋值
	memset(&tempBI,0,sizeof(BITMAPINFO));
	tempBI.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	tempBI.bmiHeader.biBitCount=32;
	tempBI.bmiHeader.biHeight=rect.bottom-rect.top;
	tempBI.bmiHeader.biWidth=rect.right-rect.left;
	tempBI.bmiHeader.biPlanes=1;
	tempBI.bmiHeader.biCompression=BI_RGB;
	tempBI.bmiHeader.biSizeImage=tempBI.bmiHeader.biWidth * tempBI.bmiHeader.biHeight * (tempBI.bmiHeader.biBitCount / 8);
	//创建GDI+DC
	mdc_show=CreateCompatibleDC(hdc);
	VOID *ppvBits;
	mainBitmap_show=CreateDIBSection(mdc_show,&tempBI,DIB_RGB_COLORS,&ppvBits,NULL,NULL);
	oldBitmap_show=SelectObject(mdc_show,mainBitmap_show);
	GdipCreateFromHDC(mdc_show,&graphics_show);

	GdipSetSmoothingMode(graphics_show,SmoothingModeHighQuality);
	GdipCreateFontFamilyFromName(GFont.FontName,NULL,&fontFam);
	GdipCreateStringFormat(NULL,NULL,&strFormat);
	GdipSetStringFormatAlign(strFormat,StringAlignmentCenter);

	GpRectF rectf1;
	rectf1.Height=GFont.FontSize;
	rectf1.Width=GFont.FontSize;
	rectf1.X=0;
	rectf1.Y=0;
	//填充坐标   0xFFA5DAF7, 0xC8468DCC,0xFF010101

	GdipCreateLineBrushFromRect(&rectf1,0x90000000,0x90000000,LinearGradientModeVertical,WrapModeTileFlipY,&Brush_show);
	//创建一个填充笔刷
	//创建一个描边的笔刷
	rclayout.X=1;
	rclayout.Y=1;
	rclayout.Width=Screen_Width;
	rclayout.Height=0;
	GdipCreatePath(FillModeAlternate,&strPath);
	GdipAddPathStringI(strPath,text,-1,fontFam,FontStyleBold,GFont.FontSize,&rclayout,strFormat);

	GdipFillPath(graphics_show,Brush_show,strPath);
	GdipDrawPath(graphics_show,pen_show,strPath);
	//-----------------------------1
	GdipCreateLineBrushFromRect(&rectf1,0x30000000,0x30000000,LinearGradientModeVertical,WrapModeTileFlipXY,&Brush_show);
	//创建一个填充笔刷
	//创建一个描边的笔刷
	rclayout.X=1.5;
	rclayout.Y=1.5;
	rclayout.Width=Screen_Width;
	rclayout.Height=0;

	GdipCreatePath(FillModeAlternate,&strPath);
	GdipAddPathStringI(strPath,text,-1,fontFam,FontStyleBold,GFont.FontSize,&rclayout,strFormat);
	GdipFillPath(graphics_show,Brush_show,strPath);
	GdipDrawPath(graphics_show,pen_show,strPath);
	//-----------------------------2
	GdipCreateLineBrushFromRect(&rectf1,0x20000000,0x20000000,LinearGradientModeVertical,WrapModeTileFlipXY,&Brush_show);
	//创建一个填充笔刷
	//创建一个描边的笔刷
	rclayout.X=2;
	rclayout.Y=2;
	rclayout.Width=Screen_Width;
	rclayout.Height=0;
	GdipCreatePath(FillModeAlternate,&strPath);
	GdipAddPathStringI(strPath,text,-1,fontFam,FontStyleBold,GFont.FontSize,&rclayout,strFormat);
	GdipFillPath(graphics_show,Brush_show,strPath);
	GdipDrawPath(graphics_show,pen_show,strPath);
	//----------------------------3
	GdipCreateLineBrushFromRect(&rectf1,0x10000000,0x10000000,LinearGradientModeVertical,WrapModeTileFlipXY,&Brush_show);
	//创建一个填充笔刷
	//创建一个描边的笔刷
	rclayout.X=2.2;
	rclayout.Y=2.2;
	rclayout.Width=Screen_Width;
	rclayout.Height=0;
	GdipCreatePath(FillModeAlternate,&strPath);
	GdipAddPathStringI(strPath,text,-1,fontFam,FontStyleBold,GFont.FontSize,&rclayout,strFormat);
	GdipFillPath(graphics_show,Brush_show,strPath);
	GdipDrawPath(graphics_show,pen_show,strPath);
	//----------------------------4
	GdipCreateLineBrushFromRect(&rectf1,0x40000000,0x40000000,LinearGradientModeVertical,WrapModeTileFlipXY,&Brush_show);
	//创建一个填充笔刷
	//创建一个描边的笔刷
	rclayout.X=-1;
	rclayout.Y=-1;
	rclayout.Width=Screen_Width;
	rclayout.Height=0;
	GdipCreatePath(FillModeAlternate,&strPath);
	GdipAddPathStringI(strPath,text,-1,fontFam,FontStyleBold,GFont.FontSize,&rclayout,strFormat);
	GdipFillPath(graphics_show,Brush_show,strPath);
	GdipDrawPath(graphics_show,pen_show,strPath);
	//---------------------------5
	GdipCreateLineBrushFromRect(&rectf1,0x30000000,0x30000000,LinearGradientModeVertical,WrapModeTileFlipXY,&Brush_show);
	//创建一个填充笔刷
	//创建一个描边的笔刷
	rclayout.X=-1.5;
	rclayout.Y=-1.5;
	rclayout.Width=Screen_Width;
	rclayout.Height=0;
	GdipCreatePath(FillModeAlternate,&strPath);
	GdipAddPathStringI(strPath,text,-1,fontFam,FontStyleBold,GFont.FontSize,&rclayout,strFormat);
	GdipFillPath(graphics_show,Brush_show,strPath);
	GdipDrawPath(graphics_show,pen_show,strPath);
	//---------------------------6
	GdipCreateLineBrushFromRect(&rectf1,GFont.ForeColor1,GFont.ForeColor2,LinearGradientModeVertical,WrapModeTileFlipXY,&Brush_show);
	//填充一个笔刷
	GdipCreatePen1(0x90000000,1,UnitDocument,&pen_show);
	//创建一个描边的笔刷
	rclayout.X=0;
	rclayout.Y=0;
	rclayout.Width=Screen_Width;
	rclayout.Height=0;
	GdipCreatePath(FillModeAlternate,&strPath);
	GdipAddPathStringI(strPath,text,-1,fontFam,FontStyleBold,GFont.FontSize,&rclayout,strFormat);
	GdipFillPath(graphics_show,Brush_show,strPath);
	GdipDrawPath(graphics_show,pen_show,strPath);
	curWinLong=GetWindowLong(show_hwnd,GWL_EXSTYLE);
	if(curWinLong!=WS_EX_LAYERED)
		SetWindowLong(show_hwnd,GWL_EXSTYLE,curWinLong|WS_EX_LAYERED);
	srcPoint.x=0;
	srcPoint.y=0;
	winSize.cx=rect.right-rect.left;
	winSize.cy=rect.bottom-rect.top;

	blendFunc32bpp.AlphaFormat=AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags=0;
	blendFunc32bpp.BlendOp=AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha=255;
	POINT ptWinPos ={rect.left,rect.top };

	GdipDeleteGraphics(graphics_show);
	UpdateLayeredWindow(show_hwnd,hdc,&ptWinPos,&winSize,mdc_show,&srcPoint,0,&blendFunc32bpp,ULW_ALPHA);
	return TRUE;
}
//绘制背景窗口
BOOL MakeTrans(HWND hWnd,HDC hdc){
	BITMAPINFO tempBI;
	BLENDFUNCTION tempBlend;
	UINT lngHeight=0,lngWidth=0;
	LONG curWinLong=0;
	GpImage *img=NULL,*img1=NULL,*img2=NULL;
	GpGraphics *graphics=NULL;
	SIZE winSize;
	POINT srcPoint;
	//TCHAR *pngPath=NULL,*pngPath1=NULL,*pngPath2=NULL;	//定义透明图片路径
	//TCHAR szFilePath[MAX_PATH+1];	//当前运行目录
	//GetModuleFileName(NULL,szFilePath,MAX_PATH);	//获取路径包含文件名
	//(_tcsrchr(szFilePath, _T('\\')))[1] = 0;	//删除文件名，只保留路径
	INT MidWidth,RLeft;
	//获取窗口位置
	RECT rect;
	GetWindowRect(hWnd,&rect);

	//pngPath=L"c:\\left.png";
	//pngPath1=L"c:\\mid.png";
	//pngPath2=L"c:\\right.png";
	memset(&tempBI,0,sizeof(BITMAPINFO));
	tempBI.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	tempBI.bmiHeader.biBitCount=32;
	tempBI.bmiHeader.biHeight=rect.bottom-rect.top;
	tempBI.bmiHeader.biWidth=rect.right-rect.left;
	tempBI.bmiHeader.biPlanes=1;
	tempBI.bmiHeader.biCompression=BI_RGB;
	tempBI.bmiHeader.biSizeImage=tempBI.bmiHeader.biWidth * tempBI.bmiHeader.biHeight * (tempBI.bmiHeader.biBitCount / 8);

	mdc=CreateCompatibleDC(hdc);
	VOID *ppvBits;
	mainBitmap=CreateDIBSection(mdc,&tempBI,DIB_RGB_COLORS,&ppvBits,NULL,NULL);

	oldBitmap=SelectObject(mdc,mainBitmap);

	GdipCreateFromHDC(mdc,&graphics);
	//改为从资源读取了
	ImageFromIDResource(hInstance,IDB_BACK_LEFT,_T("PNG"),img);
	ImageFromIDResource(hInstance,IDB_BACK_MID,_T("PNG"),img1);
	ImageFromIDResource(hInstance,IDB_BACK_RIGHT,_T("PNG"),img2);
	//GdipLoadImageFromFile(pngPath,&img);
	//GdipLoadImageFromFile(pngPath1,&img1);
	//GdipLoadImageFromFile(pngPath2,&img2);
	GdipGetImageHeight(img,&lngHeight);
	GdipGetImageWidth(img,&lngWidth);
	GdipDrawImageRect(graphics,img,0,0,lngWidth,lngHeight+2);

	MidWidth=(rect.right-rect.left)-lngWidth*2;

	GdipDrawImageRect(graphics,img1,lngWidth,0,MidWidth,lngHeight);

	RLeft=MidWidth + lngWidth;

	GdipDrawImageRect(graphics,img2,RLeft,0,lngWidth,lngHeight+2);

	curWinLong=GetWindowLong(hWnd,GWL_EXSTYLE);
	if(curWinLong!=WS_EX_LAYERED)
		SetWindowLong(hWnd,GWL_EXSTYLE,curWinLong|WS_EX_LAYERED);
	SetWindowPos(hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	srcPoint.x=0;
	srcPoint.y=0;
	winSize.cx=rect.right-rect.left;
	winSize.cy=rect.bottom-rect.top;

	blendFunc32bpp.AlphaFormat=AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags=0;
	blendFunc32bpp.BlendOp=AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha=255;

	POINT ptWinPos ={rect.left,rect.top };

	GdipDisposeImage(img);
	GdipDeleteGraphics(graphics);	//关闭画板
	UpdateLayeredWindow(hWnd,hdc,&ptWinPos,&winSize,mdc,&srcPoint,0,&blendFunc32bpp,ULW_ALPHA);
	return TRUE;
}
//创建通用窗口
//创建的窗口句柄win_hwnd
//窗口类名lpszClassName
//窗口事件处理函数proc
//窗口位置win_rect
BOOL CreateWindowUniversal(HWND &win_hwnd,LPCWSTR lpszClassName,WNDPROC proc,RECT win_rect){
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW | WS_EX_TOPMOST;
	wcex.lpfnWndProc	= proc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GNORE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= lpszClassName;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_GNORE));
	if(RegisterClassEx(&wcex)==0)	//注册窗口类
		return FALSE;
	win_hwnd=CreateWindow(lpszClassName, _T("LRC歌词"), WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_POPUP,win_rect.left, win_rect.top, win_rect.right-win_rect.left, win_rect.bottom-win_rect.top, NULL, NULL, NULL, NULL);
	if(!win_hwnd)
		return FALSE;
	SetWindowLong(win_hwnd,GWL_EXSTYLE,WS_EX_TOOLWINDOW);	//不在任务栏显示
	ShowWindow(win_hwnd, SW_HIDE);
	UpdateWindow(win_hwnd);
	return TRUE;
}
//从资源加载img到gdi
BOOL ImageFromIDResource(HINSTANCE hInst,UINT nID, LPCTSTR sTR,GpImage * &pImg){
	HRSRC hRsrc =FindResource(hInst,MAKEINTRESOURCE(nID),sTR);	//type
	if(!hRsrc)
		return false;
	DWORD len=SizeofResource(hInst,hRsrc);
	BYTE* lpRsrc=(BYTE*)LoadResource(hInst, hRsrc);
	if(!lpRsrc)
		return false;
	HGLOBAL m_hMem=GlobalAlloc(GMEM_FIXED,len);
	BYTE *pmem=(BYTE*)GlobalLock(m_hMem);
	memcpy(pmem,lpRsrc,len);
	IStream* pstm;
	CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);
	// load from stream
	//pImg=Gdiplus::Image::FromStream(pstm);
	GdipLoadImageFromStream(pstm,&pImg);
	// free/release stuff
	GlobalUnlock(m_hMem);
	pstm->Release();
	FreeResource(lpRsrc);
	return true;
}
//获取卡拉OK颜色
LRC_BACK_COLOR GetLRCOKColor(LRC_COLOR color){
	LRC_BACK_COLOR LRC_COLOR;
	switch(color){
		case LRC_COLOR_Blue:
			LRC_COLOR.LRC_BACK_COLOR1=0xFFBCF9FC;
			LRC_COLOR.LRC_BACK_COLOR2=0xFF67F0FC;
			break;
		case LRC_COLOR_Green:
			LRC_COLOR.LRC_BACK_COLOR1=0xFFDCFEAE;
			LRC_COLOR.LRC_BACK_COLOR2=0xFFE4FE04;
			break;
		case LRC_COLOR_Red:
			LRC_COLOR.LRC_BACK_COLOR1=0xFFFEFE65;
			LRC_COLOR.LRC_BACK_COLOR2=0xFFFEA10F;
			break;
		case LRC_COLOR_White:
			LRC_COLOR.LRC_BACK_COLOR1=0xFF62DDFF;
			LRC_COLOR.LRC_BACK_COLOR2=0xFF229CFE;
			break;
		case LRC_COLOR_Yellow:
			LRC_COLOR.LRC_BACK_COLOR1=0xFFFFFF6E;
			LRC_COLOR.LRC_BACK_COLOR2=0xFFFEA10F;
			break;
		default:
			LRC_COLOR.LRC_BACK_COLOR1=0xFFBA0000;
			LRC_COLOR.LRC_BACK_COLOR2=0xFFFF9301;
			break;
	}
	return LRC_COLOR;
}
//获取显示歌词颜色
LRC_BACK_COLOR GetShowColor(LRC_COLOR color){
	LRC_BACK_COLOR show_color;
	switch(color){
	case LRC_COLOR_Blue:
		show_color.LRC_BACK_COLOR1=0xFF013C8F;
		show_color.LRC_BACK_COLOR2=0xFF0198D4;
		break;
	case LRC_COLOR_Green:
		show_color.LRC_BACK_COLOR1=0xFF87F321;
		show_color.LRC_BACK_COLOR2=0xFF0E6700;
		break;
	case LRC_COLOR_Red:
		show_color.LRC_BACK_COLOR1=0xFFFECEFC;
		show_color.LRC_BACK_COLOR2=0xFFE144CD;
		break;
	case LRC_COLOR_White:
		show_color.LRC_BACK_COLOR1=0xFFFBFBFA;
		show_color.LRC_BACK_COLOR2=0xFFCBCBCB;
		break;
	case LRC_COLOR_Yellow:
		show_color.LRC_BACK_COLOR1=0xFFFE7A00;
		show_color.LRC_BACK_COLOR2=0xFFFF0000;
		break;
	}
	return show_color;
}
//定时器回调函数
void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime){
	if(nTimerid==TIMEWINDMONITOR){
		POINT udtPoint;
		GetCursorPos(&udtPoint);	//获取鼠标坐标
		HWND lonCurHWND=WindowFromPoint(udtPoint);	//获取鼠标上的句柄
		if(lonCurHWND!=show_hwnd&&lonCurHWND!=lrc_hwnd&&lonCurHWND!=back_hwnd){
			ShowWindow(back_hwnd,SW_HIDE);
		}else{
			ShowWindow(back_hwnd,SW_SHOWNOACTIVATE);
		}
	}else if(nTimerid==TIMELRC){
		RECT lrc_rect_tmp;
		GetWindowRect(lrc_hwnd,&lrc_rect_tmp);
		INT ScreenWidth=GetSystemMetrics(SM_CXSCREEN);	//获取屏幕宽度
		INT Width=(lrc_rect_tmp.right-lrc_rect_tmp.left)+(str_width/LrcTime/50);
		MoveWindow(lrc_hwnd,lrc_rect_tmp.left,lrc_rect_tmp.top,Width,lrc_rect_tmp.bottom-lrc_rect_tmp.top,TRUE);
		//SetWindowPos(lrc_hwnd,NULL,NULL,NULL,Width,lrc_rect_tmp.bottom-lrc_rect_tmp.top,SWP_NOMOVE|SWP_NOZORDER);
		lrc_DrawText(LRCText,mdc_lrc);
		if(Width>((ScreenWidth-str_width)/2)+str_width){
			KillTimer(lrc_hwnd,TIMELRC);
		}
	}
}

BOOL isMouseCoordinate(POINT mouse_point){
	int ScreenWidth=GetSystemMetrics(SM_CXSCREEN);	//获取屏幕宽度
	int Rwheight=GetSystemMetrics(SM_CYFULLSCREEN);	//获取可见屏幕高度(不包括任务栏)
	if(mouse_point.x<0||mouse_point.y<0||mouse_point.x>ScreenWidth||mouse_point.y>Rwheight){
		return FALSE;
	}
	return TRUE;
}
BOOL isMouseCoordinate(int mouse_x,int mouse_y){
	POINT point;
	point.x=mouse_x;
	point.y=mouse_y;
	return isMouseCoordinate(point);
}

VOID SetZOrder(){
	//SetParent(show_hwnd,lrc_hwnd);
	//SetParent(back_hwnd,show_hwnd);
	//SetWindowPos(back_hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	SetWindowPos(back_hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	SetWindowPos(show_hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	SetWindowPos(lrc_hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	/*EnableWindow(back_hwnd,FALSE);
	EnableWindow(show_hwnd,FALSE);
	EnableWindow(lrc_hwnd,FALSE);*/
}