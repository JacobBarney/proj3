using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstring>
#include <math.h>
#include <sstream>

int START_YEAR = 1990;
int END_YEAR = 2005;
int YEARS = END_YEAR - START_YEAR + 1;
int WEEKS = 52;
int ROWS = 63;
int COLS = 63;
double thresh = 0.95;

struct point{
    point() : row(-1), col(-1) {}
    int row;
    int col;
    int time;
};
