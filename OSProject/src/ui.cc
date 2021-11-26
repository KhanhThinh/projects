#include "Console.cc"
#include <Windows.h>
#include <iomanip>
#include <conio.h>

#define w 123
#define h 32
#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWidth 60

int ui::line = 0;
bool ui::esc = false;

class ui
{
private:
    static string hidePass()
    {
        string input;
        char temp;
        while (true)
        {
            temp = _getch();
            if (GetKeyState(VK_ESCAPE) & 0x8000)
            {
                while (GetKeyState(VK_ESCAPE) & 0X8000)
                {
                };
                continue;
            }
            else if (temp == '\0')
                continue;
            else if (temp == '\r')
                break;
            else if (input.length() > 0 && temp == 8)
            {
                input.pop_back();
                cout << "\b \b";
            }
            else if (input.length() == 0 && temp == 8)
                continue;
            else
            {
                cout << temp;
                Sleep(50);
                cout << "\b*";
                input.push_back(temp);
            }
        }
        return input;
    }

public:
    static int line;
    static bool esc;
    static void setWin(int height, int width)
    {
        HWND console = GetConsoleWindow();
        RECT r;
        GetWindowRect(console, &r);
        MoveWindow(console, r.left, r.top, height, width, TRUE);
    }

    static void clearBackground()
    {
        printSpace(123);
        cout << endl;
        printSpace(123);
        gotoXY(0, line + 2);
        printSpace(123);
        gotoXY(0, line + 25);
        printSpace(123);
        gotoXY(0, 31);
        printSpace(123);
        gotoXY(0, 0);
    }

    static void reset()
    {
        line = 0;
    }

    static string enterPassword()
    {
        string pass, repeatpass;
        gotoXY(0, 0);
        printTextAtMid("--------LOGIN---------");
        while (true)
        {
            gotoXY(0, 2);
            cout << " Password:  ";
            pass = hidePass();
            cout << endl;
            cout << " Re-enter your password: ";
            repeatpass = hidePass();
            cout << endl;
            if (pass.compare(repeatpass) == 0 && pass.length() >= 8)
                break;
            else
            {
                clrscr();
                gotoXY(0, 0);
                cout << " Error: Wrong password: Password should have at least 8 characters." << endl;
            }
        }

        return pass;
    }

    static void checkPassword(int i)
    {
        i %= 3;
        gotoXY(0, 5);
        switch (i)
        {
        case 0:
            cout << " Verifying.";
            break;
        case 1:
            cout << " Verifying..";
            break;
        case 2:
            cout << " Verifying...";
            break;
        }
    }

    static void printProgress(string cont, double pcent)
    {
        int val = (int)(pcent * 100);
        int lpad = (int)(pcent * PBWidth);
        int rpad = PBWidth - lpad;
        cout << cont;
        gotoXY(10 - cont.length(), whereY());
        fflush(stdout);
    }

    static void instructionScreen();
    static void printTextAtMid(string const &text, size_t const &left = 0, size_t const &right = w)
    {
        gotoXY((right - left - text.length()) / 2, whereY());
        cout << text;
    }
    static void displayParent()
    {
        cout << " ..";
        printSpace(120);

        int y = whereY();
        gotoXY(73, y);
        cout << "Folder     ";
        gotoXY(0, y + 1);
    }
};
