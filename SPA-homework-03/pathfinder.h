#pragma once
#include <utility>
#include <vector>
using namespace std;
struct abclass //yes, not a class
{
	int x = 0;
	int y = 0;
	int cols = 40;
	int rows = 20;
	void fix();
};
class pathfinder
{
private:
	static const unsigned int COLS = 40;
	static const unsigned int ROWS = 20;
	int _frame[ROWS][COLS];
	int _next_frame[ROWS][COLS];
	pair<int, int> original;
	pair<int, int> n = original;
	pair<int, int> previous;
	abclass seeker, destination;
	void pushseeker();
	bool notwall(pair<int, int> node);
	bool notwall(int i, int j);
	pair<int,int> check_nwse(pair<int, int> node);
public:
	pathfinder(abclass& a, abclass& b);
	void draw();
	void findnext();
	void findnext3();
	bool notfound();
	void seekerinfo();
};

