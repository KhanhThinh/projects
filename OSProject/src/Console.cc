#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <sstream>
#include <algorithm>
using namespace std;

void printSpace(int n)
{
    for (int i = 0; i < n / 10; i++)
    {
        cout << "        ";
    }

    int r = n / 10;
    n = n - r * 10;
    for (int i = 0; i < n; i++)
    {
        cout << " ";
    }
}

string numCommas(uint64_t val)
{
    string num = to_string(val);
    int insertPos = num.length() - 3;
    while (insertPos > 0)
    {
        num.insert(insertPos, ",");
        insertPos -= 3;
    }
    return num;
}

void clrscr()
{
    CONSOLE_SCREEN_BUFFER_INFO csbinfo;
    HANDLE hOut;
    COORD Home = {0, 0};
    DWORD dummy;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hOut, &csbinfo);

    FillConsoleOutputCharacter(hOut, ' ', csbinfo.dwSize.X * csbinfo.dwSize.Y, Home, &dummy);
    csbinfo.dwCursorPosition.X = 0;
    csbinfo.dwCursorPosition.Y = 0;
    SetConsoleCursorPosition(hOut, csbinfo.dwCursorPosition);
}

void gotoXY(const unsigned int &x, const unsigned int &y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

unsigned int whereX()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.X;
}

unsigned int whereY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}

void sleep(int x)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(x));
}

void fixConsole()
{
    HWND consoleWin = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWin, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWin, GWL_STYLE, style);
}

void fixSize(int width, int height)
{
    _COORD coord;
    coord.X = width;
    coord.Y = height;
    _SMALL_RECT Rectangle;
    Rectangle.Top = 0;
    Rectangle.Left = 0;
    Rectangle.Bottom = height - 100;
    Rectangle.Right = width - 1;
    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(hand, coord);
    SetConsoleWindowInfo(hand, TRUE, &Rectangle);
}

string addSalt(string pass)
{
    uint8_t salt[3] = {0x4E, 0x48, 0x54};

    int r1 = rand() % (pass.length());
    int r2 = rand() % (pass.length());
    int r3 = rand() % (pass.length());

    pass[r1] ^= salt[0];
    pass[r2] ^= salt[1];
    pass[r3] ^= salt[2];

    return pass;
}

string addPepper(string pass)
{
    char pepper = rand() % (255 + 1);
    pass += pepper;
    return pass;
}

string convert(uint8_t *s)
{
    return string((char *)s);
}