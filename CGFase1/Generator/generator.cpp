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

Point drawPoints(float radius, float angle, float height) {
	Point p;
	p.x = radius * sin(angle);
	p.y = height;
	p.z = radius * cos(angle);

	return p;
}
void wirePlane(float n) {

	glBegin(GL_LINES);

	glColor3f(1.0f, 0.0f, 0.0f);

	glVertex3f(2.0f * n, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glColor3f(0.5f, 0.0f, 0.0f);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-2.0f * n, 0.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex3f(2.0f * n, 0.0f, 1.0f * n);
	glVertex3f(-2.0f * n, 0.0f, 1.0f * n);

	glVertex3f(2.0f * n, 0.0f, -1.0f * n);
	glVertex3f(-2.0f * n, 0.0f, -1.0f * n);

	glVertex3f(2.0f * n, 0.0f, 2.0f * n);
	glVertex3f(-2.0f * n, 0.0f, 2.0f * n);

	glVertex3f(2.0f * n, 0.0f, -2.0f * n);
	glVertex3f(-2.0f * n, 0.0f, -2.0f * n);

	glColor3f(0.0f, 0.0f, 1.0f);

	glVertex3f(0.0f, 0.0f, 2.0f * n);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 0.5f);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -2.0f * n);

	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex3f(1.0f * n, 0.0f, 2.0f * n);
	glVertex3f(1.0f * n, 0.0f, -2.0f * n);

	glVertex3f(-1.0f * n, 0.0f, 2.0f * n);
	glVertex3f(-1.0f * n, 0.0f, -2.0f * n);

	glVertex3f(2.0f * n, 0.0f, 2.0f * n);
	glVertex3f(2.0f * n, 0.0f, -2.0f * n);

	glVertex3f(-2.0f * n, 0.0f, 2.0f * n);
	glVertex3f(-2.0f * n, 0.0f, -2.0f * n);

	glColor3f(0.0f, 1.0f, 0.0f);

	glVertex3f(0.0f, 2.0f * n, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.5f, 0.0f);

	glVertex3f(0.0f, 0.0f * n, 0.0f);
	glVertex3f(0.0f, -2.0f * n, 0.0f);

	glEnd();
}
// draw cone
void cone(float px, float py, float pz, float raio, float altura, int fatias, int camadas) {

	float a = altura / (float)camadas;
	float r = raio / (float)camadas;
	int i, j;
	float oy, or;

	float ang1 = 0.0f;
	float ang2 = 2.0f * M_PI / (float)fatias;

	glBegin(GL_TRIANGLES);

	oy = - (altura / 2.0f);
	or = raio;

	for (i = 0; i < fatias; i++) {

		glColor3f(1.0f, 0.75f, 0.0f);
		glVertex3f(cos(ang1) + px, oy + py, sin(ang1) + pz);
		glVertex3f(cos(ang2) + px, oy + py, sin(ang2) + pz);
		glVertex3f(px, oy + py, pz);

		ang1 += (2.0f * M_PI / (float)fatias);
		ang2 += (2.0f * M_PI / (float)fatias);

	}

	for (i = 0; i < camadas; i++) {
	
		for (j = 0; j < fatias; j++) {

			if (i != camadas-1) {
				//amarelo
				glColor3f(1.0f, 0.75f, 0.0f);
				glVertex3f(cos(ang2) * (or -r) + px, oy + a + py, sin(ang2) * (or -r) + pz);
				glVertex3f(cos(ang2) * or + px, oy + py, sin(ang2) * or + pz);
				glVertex3f(cos(ang1) * (or -r) + px, oy + a + py, sin(ang1) * (or -r) + pz);
			}

			//azuis
			glColor3f(0.0f, 0.5f, 1.0f);
			glVertex3f(cos(ang1) * or + px, oy + py, sin(ang1) * or + pz);
			glVertex3f(cos(ang1) * (or -r) + px, oy + a + py, sin(ang1) * (or -r) + pz);
			glVertex3f(cos(ang2) * or + px, oy + py, sin(ang2) * or + pz);

			ang1 += (2.0f * M_PI / (float)fatias);
			ang2 += (2.0f * M_PI / (float)fatias);
		}

		oy += a;
		or -= r;

	}

	glEnd();

}


//draw box
void caixa(float px, float py, float pz, float largura, float altura, float comprimento, int d) { 

	float l = largura / (float)d;
	float a = altura / (float)d;
	float c = comprimento / (float)d;

	float ox, oy, oz;
	int i, j;

	glBegin(GL_TRIANGLES);

	//fundo

	ox = -largura / 2.0f;
	oy = -altura / 2.0f;
	oz = -comprimento / 2.0f;

	for (i = 0; i < d; i++) {
	
		for (j = 0; j < d; j++) {

			//amarelo
			glColor3f(1.0f, 0.75f, 0.0f);
			glVertex3f(px + ox + l, py + oy, pz + oz + c);
			glVertex3f(px + ox, py + oy, pz + oz + c);
			glVertex3f(px + ox + l, py + oy, pz + oz);

			//azul
			glColor3f(0.0f, 0.5f, 1.0f);
			glVertex3f(px + ox, py + oy, pz + oz);
			glVertex3f(px + ox + l, py + oy, pz + oz);
			glVertex3f(px + ox, py + oy, pz + oz + c);

			ox += l;
		}

		ox = -largura / 2.0f;
		oz += c;
	}

	//fundo

	ox = -largura / 2.0f;
	oy = altura / 2.0f;
	oz = -comprimento / 2.0f;

	for (i = 0; i < d; i++) {

		for (j = 0; j < d; j++) {

			//amarelo
			glColor3f(1.0f, 0.75f, 0.0f);
			glVertex3f(px + ox, py + oy, pz + oz);
			glVertex3f(px + ox, py + oy, pz + oz + c);
			glVertex3f(px + ox + l, py + oy, pz + oz);

			//azul
			glColor3f(0.0f, 0.5f, 1.0f);
			glVertex3f(px + ox + l, py + oy, pz + oz + c);
			glVertex3f(px + ox + l, py + oy, pz + oz);
			glVertex3f(px + ox, py + oy, pz + oz + c);

			ox += l;
		}

		ox = -largura / 2.0f;
		oz += c;
	}

	//frente

	ox = -largura / 2.0f;
	oy = -altura / 2.0f;
	oz = comprimento / 2.0f;

	for (i = 0; i < d; i++) {

		for (j = 0; j < d; j++) {

			//amarelo
			glColor3f(1.0f, 0.75f, 0.0f);
			glVertex3f(px + ox + l, py + oy, pz + oz);
			glVertex3f(px + ox + l, py + oy + a, pz + oz);
			glVertex3f(px + ox, py + oy + a, pz + oz);

			//azul
			glColor3f(0.0f, 0.5f, 1.0f);
			glVertex3f(px + ox, py + oy, pz + oz);
			glVertex3f(px + ox + l, py + oy, pz + oz);
			glVertex3f(px + ox, py + oy + a, pz + oz);

			ox += l;
		}

		ox = -largura / 2.0f;
		oy += a;
	}

	//trás

	ox = -largura / 2.0f;
	oy = -altura / 2.0f;
	oz = -comprimento / 2.0f;

	for (i = 0; i < d; i++) {

		for (j = 0; j < d; j++) {

			//amarelo			
			glColor3f(1.0f, 0.75f, 0.0f);
			glVertex3f(px + ox, py + oy, pz + oz);
			glVertex3f(px + ox, py + oy + a, pz + oz);
			glVertex3f(px + ox + l, py + oy, pz + oz);

			//azul
			glColor3f(0.0f, 0.5f, 1.0f);
			glVertex3f(px + ox + l, py + oy, pz + oz);
			glVertex3f(px + ox, py + oy + a, pz + oz);
			glVertex3f(px + ox + l, py + oy + a, pz + oz);

			ox += l;
		}

		ox = -largura / 2.0f;
		oy += a;
	}

	//direita

	ox = largura / 2.0f;
	oy = -altura / 2.0f;
	oz = -comprimento / 2.0f;

	for (i = 0; i < d; i++) {

		for (j = 0; j < d; j++) {

			//amarelo
			glColor3f(1.0f, 0.75f, 0.0f);
			glVertex3f(px + ox, py + oy, pz + oz );
			glVertex3f(px + ox, py + oy + a, pz + oz);
			glVertex3f(px + ox, py + oy, pz + oz + c);

			//azul
			glColor3f(0.0f, 0.5f, 1.0f);
			glVertex3f(px + ox, py + oy + a, pz + oz);
			glVertex3f(px + ox, py + oy + a, pz + oz + c);
			glVertex3f(px + ox, py + oy, pz + oz + c);

			oz += c;
		}

		oz = -comprimento / 2.0f;
		oy += a;
	}

	//esquerda

	ox = -largura / 2.0f;
	oy = -altura / 2.0f;
	oz = -comprimento / 2.0f;

	for (i = 0; i < d; i++) {

		for (j = 0; j < d; j++) {

			//amarelo
			glColor3f(1.0f, 0.75f, 0.0f);
			glVertex3f(px + ox, py + oy, pz + oz);
			glVertex3f(px + ox, py + oy, pz + oz + c);
			glVertex3f(px + ox, py + oy + a, pz + oz);

			//azul
			glColor3f(0.0f, 0.5f, 1.0f);
			glVertex3f(px + ox, py + oy + a, pz + oz);
			glVertex3f(px + ox, py + oy, pz + oz + c);
			glVertex3f(px + ox, py + oy + a, pz + oz + c);

			oz += c;
		}

		oz = -comprimento / 2.0f;
		oy += a;
	}

	glEnd();
}


//draw sphere

void esfera(float px, float py, float pz, float raio, int fatias, int camadas) {

	float a = (2.0f * raio) / (float)camadas;
	float ang1 = 0.0f;
	float ang2 = 2.0f * M_PI / (float)fatias;
	float oy, or1, or2 ;
	int i, j;

	glBegin(GL_TRIANGLES);

	oy = -raio;
	
	for (i = 0; i < camadas ; i++) {

		or1 = sqrt(raio * raio - oy * oy);
		or2 = sqrt(raio * raio - (oy + a) * (oy + a));

		for (j = 0; j < fatias; j++) {

			glColor3f(1.0f, 0.75f, 0.0f);
			glVertex3f(cos(ang1) * or1, oy, sin(ang1) * or1);
			glVertex3f(cos(ang1) * or2, oy + a, sin(ang1) * or2);
			glVertex3f(cos(ang2) * or1, oy, sin(ang2) * or1);

			glColor3f(0.0f, 0.5f, 1.0f);
			glVertex3f(cos(ang1) * or2, oy + a, sin(ang1) * or2);
			glVertex3f(cos(ang2) * or2, oy + a, sin(ang2) * or2);
			glVertex3f(cos(ang2) * or1, oy, sin(ang2) * or1);

			ang1 += 2.0f * M_PI / (float)fatias;
			ang2 += 2.0f * M_PI / (float)fatias;

		}

		oy += a;

	}

	glEnd();

}

//draw plane
void plano(float x, float y, float z, float s) {

	float n = s / 2.0f;

	glBegin(GL_TRIANGLES);

	//triangulo amarelo
	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex3f(n + x, y, n + z);
	glVertex3f(n + x, y, -n + z);
	glVertex3f(-n + x, y, n + z);

	//triangulo azul
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex3f(-n + x, y, n + z);
	glVertex3f(n + x, y, -n + z);
	glVertex3f(-n + x, y, -n + z);

	glEnd();
}


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

