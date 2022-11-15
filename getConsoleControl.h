#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

void clearCursor() {
    CONSOLE_CURSOR_INFO c;
    c.dwSize = 1;
    c.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}

void resizeConsole(int x, int y) {
    char chTemp[100];
    sprintf(chTemp, "mode con cols=%d lines=%d", x, y);
    system(chTemp);
}

void setCursor(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(int colorValue) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorValue);
}

