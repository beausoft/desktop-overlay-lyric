#include <windows.h>
#include <iostream>
#include "../lyric/lyric.h"

int main() {
    HLRC lrc = CreateLyric();
    LyricShow(lrc);
    SetLyricTextA(lrc, "ҹ����ȴ�������������´�,������������Ϊ������˷ִ硣");
    SetLyricFontA(lrc, "����", 42);
    SetLyricColorStyle(lrc, 3);
    SetLyricScale(lrc, 0.8f);
    LyricUpdate(lrc);
    //SetLyricLock(lrc, true);
    //FreeLyric(lrc);
    //OverlayLyric lrc;
    //lrc.SetText(L"ҹ����ȴ�������������´�,������������Ϊ������˷ִ硣");
    //lrc.SetFont(L"����", 42);
    //lrc.SetScale(1.0f);
    //lrc.SetLock(TRUE);
    //lrc.SetLock(FALSE);
    //lrc.SetDefaultStyle(DefaultColorStyle::White);

    //int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    //int screenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
    //int cx = int(float(screenWidth) * 0.8f);
    //int cy = int(60 * 1.8f);
    //int x = screenWidth / 2 - cx / 2;
    //int y = screenHeight - cy;
    //lrc.SetWndPos(x, y, cx, cy);
    // lrc.Update();
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
