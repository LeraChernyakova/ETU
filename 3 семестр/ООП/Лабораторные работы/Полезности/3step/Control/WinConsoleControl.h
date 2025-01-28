#pragma once
#include <windows.h>

class WinConsoleControl {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    public:
        void setcursor(bool visible, DWORD size);

        void gotoxy(int x, int y);
};


