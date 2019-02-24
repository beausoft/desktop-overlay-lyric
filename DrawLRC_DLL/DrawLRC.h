#define TIMEWINDMONITOR 1000	//窗口监视TIMERID
#define TIMELRC 1001			//歌词效果

BOOL CreateWindowUniversal(HWND &win_hwnd,LPCWSTR lpszClassName,WNDPROC proc,RECT win_rect);
BOOL ImageFromIDResource(HINSTANCE hInst,UINT nID, LPCTSTR sTR,GpImage * &pImg);//从资源img到gdi
BOOL CreateBackWindow();
BOOL CreateShowWindow();
BOOL CreateLrcWindow();
//背景窗口消息处理函数
LRESULT CALLBACK Back_WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Show_WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Lrc_WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL MakeTrans(HWND hWnd,HDC hdc);	//绘图方法背景
BOOL Show_DrawText(const WCHAR* text,HDC hdc);	//显示歌词方法
BOOL lrc_DrawText(const WCHAR* text,HDC hdc);	//卡拉OK方法
BOOL sethInstance(HINSTANCE hIns);
HWND getBACK_HWND();
//定义字体结构
struct GdiFont{
public:
	WCHAR* FontName;
	REAL FontSize;
	long ForeColor1;
	long ForeColor2;
	long LineColor;
	byte FontWidth;
	bool FontBold;
	long OkColor1;
	long OKColor2;
};
//定义卡拉ok颜色结构
struct LRC_BACK_COLOR{
public:
	ARGB LRC_BACK_COLOR1;
	ARGB LRC_BACK_COLOR2;
};
//颜色枚举
enum LRC_COLOR{
	LRC_COLOR_Blue=1,	//蓝色
	LRC_COLOR_Green=2,//绿色
	LRC_COLOR_Red=3,//红色
	LRC_COLOR_White=4,//白色
	LRC_COLOR_Yellow=5//黄色
};

LRC_BACK_COLOR GetLRCOKColor(LRC_COLOR color);
LRC_BACK_COLOR GetShowColor(LRC_COLOR color);
//定时器回调函数
void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime);
VOID SetZOrder();
//判断鼠标坐标是否正确
BOOL isMouseCoordinate(POINT mouse_point);
BOOL isMouseCoordinate(int mouse_x,int mouse_y);