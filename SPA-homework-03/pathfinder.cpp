#include "pathfinder.h"
#include <iostream>
#include <utility>
#include <windows.h>
using namespace std;

pathfinder::pathfinder(abclass& a, abclass& b)
{
    //m.emplace(pair<int, int>(a.x, a.y), 0);
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (j == a.x && i == a.y) {
                _frame[i][j] = 2;
            }
            else if (j == b.x && i == b.y) {
                _frame[i][j] = 3;
            }
            else {
                _frame[i][j] = 0;
            }
            _next_frame[i][j] = _frame[i][j];
        }
    }
    // hard coded walls
    _next_frame[0][9] = 1;
    _next_frame[1][9] = 1;
    _next_frame[2][9] = 1;
    _next_frame[3][9] = 1;
    _next_frame[4][9] = 1;


    _next_frame[0][11] = 1;
    _next_frame[1][11] = 1;
    _next_frame[2][11] = 1;
    _next_frame[3][11] = 1;
    _next_frame[4][11] = 1;

    _next_frame[5][11] = 1;
    _next_frame[6][11] = 1;
    _next_frame[8][11] = 1;
    _next_frame[9][11] = 1;

    _next_frame[5][11] = 1;
    _next_frame[6][11] = 1;
    _next_frame[8][11] = 1;
    _next_frame[9][11] = 1;


    this->seeker = a; //seeker is A input
    this->destination = b; //destination is B input
    original.first = a.x;
    original.second = a.y;
}

void pathfinder::draw() //integer based grid
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(console_color, 0);
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            switch (_next_frame[i][j]) {
            case 0:// empty cell color
                SetConsoleTextAttribute(console_color, 0); //7 default, 8 grey, 0 black
                cout << '-';
                break;
            case 1:
                SetConsoleTextAttribute(console_color, 12);
                cout << '*';
                break;
            case 2:
                SetConsoleTextAttribute(console_color, 46);
                cout << 'A';
                break;
            case 3:
                SetConsoleTextAttribute(console_color, 46);
                cout << 'B';
                break;
            case 4:
                SetConsoleTextAttribute(console_color, 10);
                cout << 'x';
                break;
            default:
                SetConsoleTextAttribute(console_color, 7);
                cout << 'D';
                break;
            }
        }
        cout << endl;
    }
    SetConsoleTextAttribute(console_color, 7);
}

void pathfinder::findnext() //default pathfinder
{
    //_next_frame[seeker.y][seeker.x] = 4;
    if (seeker.x != destination.x) {
        if (seeker.x > destination.x) {
            --seeker.x;
            pushseeker();
            return;
        }
        else if (seeker.x < destination.x) {
            ++seeker.x;
            pushseeker();
            return;
        }
    }
    if (seeker.y != destination.y) {
        if (seeker.y > destination.y) {
            --seeker.y;
            pushseeker();
            return;
        }
        else if (seeker.y < destination.y) {
            ++seeker.y;
            pushseeker();
            return;
        }
    } 
}

bool pathfinder::notfound()
{
    return !((seeker.x == destination.x) && (seeker.y == destination.y));
}

void pathfinder::pushseeker()
{
    _next_frame[seeker.y][seeker.x] = 4;
    //cout << seeker.y << seeker.x << endl;
}

void abclass::fix() // fixes coordinate input to match index (1 into 0)
{
    if ((x > 0) && (x <= cols)) {
        --this->x;
    }
    else {
        throw exception("out of range");
    }
    if ((y > 0) && (y <= rows)) {
        --this->y;
    }
    else {
        throw exception("out of range");
    }
}
bool pathfinder::notwall(pair<int, int> node)
{
    return !(_next_frame[node.second][node.first] == 1);
    //                   ROWS y         COLS x
}
bool pathfinder::notwall(int i, int j)
{
    return !(_next_frame[i][j] == 1);
}


pair<int,int> pathfinder::check_nwse(pair<int, int> node)//check north west south east for wall
{
    //top
    // i0 , j39

    //top
    if (node.second != 0) { //if not first row
        if (!notwall(node.second - 1, node.first)) { //mid
            pair<int, int> wallnode = { node.first,node.second - 1 };
            return wallnode;
        };

    }

    //mid
    if (node.first != 0) {
        if (!notwall(node.second, node.first - 1)) { //left
            pair<int, int> wallnode = { node.first - 1,node.second };
            return wallnode;
        };
    }
    if (node.first != COLS - 1) {
        if (!notwall(node.second, node.first + 1)) { //right
            pair<int, int> wallnode = { node.first + 1,node.second };
            return wallnode;
        };
    }

    //bot
    if (node.second != ROWS - 1) {

        if (!notwall(node.second + 1, node.first)) { //mid
            pair<int, int> wallnode = { node.first,node.second + 1 };
            return wallnode;
        };
    }
    return original; //return A pos which is never a wall
}

void pathfinder::findnext3() { //wall adapted version
    n = check_nwse({ seeker.x,seeker.y });
    if(_next_frame[n.second][n.first] != 1) {
        findnext(); //runs default if no wall
    }
    else { //if wall present
        pair<int, int> temp = { seeker.x - n.first, seeker.y - n.second }; //coordinate delta
        // 9,0    10,0   up down
        //
        previous = { seeker.x, seeker.y };
        bool left = true,
            right = true,
              up = true,
            down = true;
        if (temp.first < 0) {
            right = false;
        }
        if (temp.first > 0) {
            left = false;
        }
        if (temp.second < 0) {
            down = false;
        }
        if (temp.second > 0) {
            up = false;
        }

        if ((!right || !left) && ((seeker.x <= destination.x) || (seeker.x > destination.x))) {
            if ((seeker.y != ROWS - 1 && down) && (_next_frame[seeker.y + 1][seeker.x] != 4)) { //move right
                ++seeker.y; //down
                pushseeker();
                return;
            }
            else if ((seeker.y != 0 && up) && (_next_frame[seeker.y - 1][seeker.x] != 4)) {
                --seeker.y; //up
                pushseeker();
                return;
            }
        }
        if ((!up || !down) && ((seeker.y <= destination.y) || (seeker.y > destination.y))) {

            if ((seeker.x != 0 && left) && (_next_frame[seeker.y][seeker.x - 1] != 4)) { //need to remember previous
                --seeker.x; //left
                pushseeker();
                return;
            }
            else if ((seeker.x != COLS - 1 && right) && (_next_frame[seeker.y][seeker.x + 1] != 4)) {
                ++seeker.x; //right
                pushseeker();
                return;
            }
        }
    }
}

void pathfinder::seekerinfo() // outputs coordinate data to console
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 11);
    cout << "Seeker x: "; 
    if (seeker.x != destination.x) {
        SetConsoleTextAttribute(console_color, 12);
    }
    else {
        SetConsoleTextAttribute(console_color, 10);
    }
    cout << seeker.x << " ";
    SetConsoleTextAttribute(console_color, 11);
    cout << "y: ";
    if (seeker.y != destination.y) {
        SetConsoleTextAttribute(console_color, 12);
    }
    else {
        SetConsoleTextAttribute(console_color, 10);
    }
    cout << seeker.y << endl;
    SetConsoleTextAttribute(console_color, 11);
    cout << "Destination x: ";
    SetConsoleTextAttribute(console_color, 7);
    cout << destination.x << " ";
    SetConsoleTextAttribute(console_color, 11);
    cout << "y: ";
    SetConsoleTextAttribute(console_color, 7);
    cout << destination.y << endl;
    //SetConsoleTextAttribute(console_color, 7);
}