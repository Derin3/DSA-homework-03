#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <chrono>
#include <windows.h> //title

#include "pathfinder.h"
#include "cursor.h" // cursor functions

using namespace std;
using namespace std::chrono;

int main() {
	SetConsoleTitle(TEXT("Pathfinder DSA-homework-03"));
	abclass a, b; //stores x , y , row , col
	steady_clock::time_point start;
	steady_clock::time_point end;
	system("color B"); //simpler here
	setCursorVisible(true);
	cout << "-- PATHFINDER --" << endl;
	cout << "Coordinates from 1 - 40 x | 1 - 20 y" << endl; //1,1   40,1
	cout << "Enter A (x coordinate): ";
	cin >> a.x;
	cout << "Enter A (y coordinate): ";
	cin >> a.y;
	cout << "Enter B (x coordinate): ";
	cin >> b.x;
	cout << "Enter B (y coordinate): ";
	cin >> b.y;
	try { // fixes coordinate input to match index (1 into 0)
		a.fix();
		b.fix();
	}
	catch (exception& e) {
		system("color C"); //reset color
		cout << endl << e.what() << endl;
		return -1;
	}
	pathfinder path(a,b); //create path

	start = high_resolution_clock::now();
	end = start;
	int interval = 100; //time interval in ms
	setCursorVisible(false); //hides console cursor
	while (path.notfound()) {
		if (duration_cast<milliseconds> (end - start).count() > interval) {
			system("cls");
			//setConsoleClear(); no
			path.draw();
			path.findnext3();
			path.seekerinfo();
			start = high_resolution_clock::now();
		}
		else {
			end = high_resolution_clock::now();
		}
	}
	setCursorVisible(true);
	cout << endl << endl << "Program complete!" << endl;
	system("pause"); //dont exit on end
	return 0;
}