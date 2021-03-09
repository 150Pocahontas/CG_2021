#define _USE_MATH_DEFINES

#include "generator.h"

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <string.h>

using namespace std;
vector<Point> points;



void writePointsFile(string filename, std::vector<Point> points) {
	ofstream file;

    	string fileDir = "../../files/" + filename;
	file.open(fileDir, ios_base::trunc);

	if (!file.is_open()) {
		cout << "Error while opening the file " << filename << endl;
	}
	else {
		for (const Point point : points) {
			string x, y, z;

			x = to_string(point.x).append(",");
			y = to_string(point.y).append(",");
			z = to_string(point.z).append("\n");

			file << x << y << z;
		}
		file.close();
		cout << filename << " file was created!" << endl;
	}
}


float quadrants[8][3] = {
		{ 1,  1,  1},
		{ 1,  1, -1},
		{-1,  1, -1},
		{-1,  1,  1},
		{ 1, -1,  1},
		{ 1, -1, -1},
		{-1, -1, -1},
		{-1, -1,  1},
};

Point drawPoints(float radius, float angle, float height) {
	Point p;
	p.x = radius * sin(angle);
	p.y = height;
	p.z = radius * cos(angle);

	return p;
}

// draw cone


//draw box


//draw sphere


//draw plane


int main (int argc, char **argv)
{
        if (argc < 2)
    {
        printf("Not enough arguments!\n");
        return -1;
    }

    vector<Point> points;
    string file;

    if (strcmp("cone",argv[1]) == 0 && argc == 7)
    {
        float radius = atof(argv[2]);
        float height = atof(argv[3]);
        int slices = atoi(argv[4]);
        int layers = atoi(argv[5]);
        file = argv[6];
        points = cone(radius,height,slices,layers);
    }
    else if (strcmp("box", argv[1]) == 0 && argc == 7)
    {
        float length = atof(argv[2]), width = atof(argv[3]), height = atof(argv[4]);
        int divisions = atoi(argv[5]);
        file = argv[6];
        points = box(length,width,height,divisions);
    }
    else if (strcmp("sphere",argv[1]) == 0 && argc == 6)
    {
            float radius = atof(argv[2]);
            int slices = atoi(argv[3]);
            int layers = atoi(argv[4]);
            file = argv[5];
            points = sphere(radius, slices, layers);
    }
    else if (strcmp("plane", argv[1]) == 0 && argc == 4)
    {
            float size = atof(argv[2]);
            file = argv[3];
            points = plane(size / 2);
    }
    else{
        printf("Invalid input!\n");
        return -1;
    }
     return 0;
}

