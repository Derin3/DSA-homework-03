#include "cursor.h"
using namespace std;
void setCursorPosition(int x, int y)
{
    static const HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(h, coord);
}

//void setConsoleClear()
//{
//    setCursorPosition(0, 0);
//    for (int i = 0; i < 23; ++i) {
//        for (int j = 0; j < 40; ++j) {
//            //if (i == 20 || i == 21) {
//            //    if ((i == 20) && (j <= 8|| j == 10 || j == 13 || j > 17)) {
//            //        //cout << "@";
//            //        continue; //needs output or cursor stays at the same spot, this wont work
//            //    }
//            //    if (i == 21) {
//            //        //cout << "@";
//            //        continue;
//            //    }
//            //}
//            cout << ' ';
//        }
//        if (i != 22) {
//            cout << endl;
//        }
//    }
//    setCursorPosition(0, 0);
//}

void setCursorVisible(bool b)
{
    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(handle, &cci);
    cci.bVisible = b;
    SetConsoleCursorInfo(handle, &cci);
}
