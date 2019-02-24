#include "stdafx.h"
#include "BackLRC.h"
BackLRC *backLrc;	//当前类句柄
BOOL isMousePrees;								//鼠标是否按下
HDC mdc;
HBITMAP mainBitmap;
HGDIOBJ oldBitmap;
BLENDFUNCTION blendFunc32bpp;
ULONG token;
int mouse_cx;
int mouse_cy;
BOOL BackWindowCreate(HWND hWnd);	//窗口创建完成执行
//构造函数
BackLRC::BackLRC(HINSTANCE hInstance,HWND h_main){
	//初始化字符串
	backLrc=this;
	hwnd_main=h_main;//主窗口句柄赋值
	backhIns=hInstance;	//当前实例赋值
	LoadString(backhIns,IDC_BACKLRCWINDOWTEXT, backszWindowClass, MAX_LOADSTRING);
	//初始化GDI+
	GdiplusStartupInput GpInput;
	GpInput.GdiplusVersion=1;
	if(GdiplusStartup(&token,&GpInput,NULL)!=0){
		MessageBox(hwnd_main,_T("Fehler bem laden von GDI+!"),_T("提示"),MB_OK);
		SendMessage(hwnd_main,WM_CLOSE,NULL,NULL);	//发送关闭消息
	}
}
//析构函数
BackLRC::~BackLRC(){
	GdiplusShutdown(token);
	SelectObject(mdc,oldBitmap);
	DeleteObject(mainBitmap);
	DeleteObject(oldBitmap);
	DeleteDC(mdc);
	DestroyWindow(hwnd_BackLRC);	//销毁窗口
}

BOOL BackLRC::CreateBackLRCWindow(){
	RegisterClass();	//注册窗口
	if(!InitBackLRCWindow())	//初始化窗口
	{
		return FALSE;
	}
	return TRUE;
}
//获取句柄
HWND BackLRC::GetBackLRCHandle(){
	return hwnd_BackLRC;
}
//初始化窗口
BOOL BackLRC::InitBackLRCWindow(){
	int ScreenWidth=GetSystemMetrics(SM_CXSCREEN);	//获取屏幕宽度
	//int ScrrenHeight=GetSystemMetrics(SM_CYSCREEN);	//获取屏幕高度
	int Rwheight=GetSystemMetrics(SM_CYFULLSCREEN);	//获取可见屏幕高度(不包括任务栏)
	hwnd_BackLRC = CreateWindow(backszWindowClass, _T("LRC背景"), WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_POPUP,0, Rwheight-103, ScreenWidth, 103, NULL, NULL, NULL, NULL);

   if (!hwnd_BackLRC)
   {
      return FALSE;
   }
   SetWindowLong(hwnd_BackLRC,GWL_EXSTYLE,WS_EX_TOOLWINDOW);	//不在任务栏显示
   ShowWindow(hwnd_BackLRC, SW_SHOW);
   UpdateWindow(hwnd_BackLRC);
   return TRUE;
}

ATOM BackLRC::RegisterClass(){
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= Back_WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= backhIns;
	wcex.hIcon			= LoadIcon(backhIns, MAKEINTRESOURCE(IDI_GNORE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= backszWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_GNORE));
	return RegisterClassEx(&wcex);
}
//窗口消息处理函数
LRESULT CALLBACK Back_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
		case WM_COMMAND:
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			backLrc->MakeTrans(hWnd,hdc);	//调用绘图方法
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CLOSE:
			GdiplusShutdown(token);
			SelectObject(mdc,oldBitmap);
			DeleteObject(mainBitmap);
			DeleteObject(oldBitmap);
			DeleteDC(mdc);
			return DefWindowProc(hWnd, message, wParam, lParam);
		case WM_CREATE:
			BackWindowCreate(hWnd);
			break;
		case WM_LBUTTONDOWN:	//鼠标按下
			//mouse_cx=LOWORD(lParam);
			mouse_cy=HIWORD(lParam);
			isMousePrees=TRUE;
			break;
		case WM_LBUTTONUP:		//鼠标松开
			mouse_cy=0;
			isMousePrees=FALSE;
			break;
		case WM_MOUSEMOVE:		//鼠标移动
			if(isMousePrees){
				RECT win_re;	//窗口大小变量
				GetWindowRect(hWnd,&win_re);	//获取窗口大小
				//int MOUSE_X=LOWORD(lParam);
				int MOUSE_Y=HIWORD(lParam);
				int Y=win_re.top+(MOUSE_Y-mouse_cy);
				MoveWindow(hWnd,0,Y,win_re.right-win_re.left,win_re.bottom-win_re.top,TRUE);	//移动窗口
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

BOOL BackLRC::CloseBackLRCWindow(){
	CloseWindow(hwnd_BackLRC);	
	return TRUE;
}
//绘图方法
BOOL BackLRC::MakeTrans(HWND hWnd,HDC hdc){
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
	ImageFromIDResource(backhIns,IDB_BACK_LEFT,_T("PNG"),img);
	ImageFromIDResource(backhIns,IDB_BACK_MID,_T("PNG"),img1);
	ImageFromIDResource(backhIns,IDB_BACK_RIGHT,_T("PNG"),img2);
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
		SetWindowLong(hWnd,GWL_EXSTYLE,curWinLong^WS_EX_LAYERED);
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
	return false;
}

//从资源加载img到gdi
BOOL BackLRC::ImageFromIDResource(HINSTANCE hInst,UINT nID, LPCTSTR sTR,GpImage * &pImg){
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
//窗口创建完成执行
BOOL BackWindowCreate(HWND hWnd){
	//MakeTrans(hWnd);	//调用绘图方法
	return FALSE;
}