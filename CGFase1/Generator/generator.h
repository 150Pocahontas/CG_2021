#ifndef GENERATOR_GENERATOR_H
#define GENERATOR_GENERATOR_H

#include <vector>
#include <string>

using namespace std;
typedef struct point {
	float x;
	float y;
	float z;
} Point;

void writePointsFile(string filename, vector<Point> points);



#endif

