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

    	string fileDir = "../files/" + filename;
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


/*o primeiro for é para desenhar a base, isto é, a base é feita em que cada
iteração do loop desenha um triangulo a partir do ponto de origem e também dos dois
 pontos localizados pelas variáveis ang1 e ang2.
*/

// draw cone
vector<Point> cone( float raio, float altura, int fatias, int camadas) {
    vector<Point> points;
    Point p,p1,p2,p3;
    float a = altura / (float)camadas;
    float r = raio / (float)camadas;
    int i, j;
    float oy, rn;

    float ang1 = 0.0f;
    //alpha
    float ang2 = 2.0f * M_PI / (float)fatias;
		p.x = p.y = p.z = 0;


    oy = - (altura / 2.0f);
    rn = raio;

    for (i = 0; i < fatias; i++) {
        p1.x = (cos(ang1) * rn + p.x);
        p1.y = oy + p.y;
        p1.z = sin(ang1) * rn + p.z;
        p2.x = (cos(ang2) * rn + p.x);
        p2.y = oy + p.y;
        p2.z = sin(ang2) * rn + p.z;
        p3.x = p.x;
        p3.y = oy + p.y;
        p3.z = p.z;
        points.push_back(p1);
        points.push_back(p2);
        points.push_back(p3);

        ang1 += (2.0f * M_PI / (float)fatias);
        ang2 += (2.0f * M_PI / (float)fatias);

    }

    for (i = 0; i < camadas; i++) {
        for (j = 0; j < fatias; j++) {

            if (i != camadas-1) {
                p1.x = cos(ang2) * (rn -r) + p.x;
                p1.y = oy + a + p.y;
                p1.z = sin(ang2) * (rn -r) + p.z;
                p2.x = cos(ang2) * rn + p.x;
                p2.y = oy + p.y ;
                p2.z = sin(ang2) * rn + p.z;
                p3.x = cos(ang1) * (rn -r) + p.x;
                p3.y = oy + a + p.y;
                p3.z =  sin(ang1) * (rn -r) + p.z;

                points.push_back(p1);
                points.push_back(p2);
                points.push_back(p3);

            }
            p1.x = cos(ang1) * rn + p.x;
            p1.y = oy + p.y;
            p1.z = sin(ang1) * rn + p.z;
            p2.x = cos(ang1) * (rn -r) + p.x;
            p2.y = oy + a + p.y;
            p2.z = sin(ang1) * (rn -r) + p.z;
            p3.x = cos(ang2) * rn + p.x;
            p3.y = oy + p.y;
            p3.z = sin(ang2) * rn + p.z;
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);

            ang1 += (2.0f * M_PI / (float)fatias);
            ang2 += (2.0f * M_PI / (float)fatias);


        }

        oy += a;
        rn -= r;

    }

    return points;

}


//draw box
vector<Point>  box( float largura, float altura, float comprimento, int d) {
    vector<Point> points;
    Point p, p1, p2, p3;
    float l = largura / (float)d;
    float a = altura / (float)d;
    float c = comprimento / (float)d;

    float ox, oy, oz;
    int i, j;


    p.x = p.y = p.z = 0;

    //fundo

    ox = -largura / 2.0f;
    oy = -altura / 2.0f;
    oz = -comprimento / 2.0f;

    for (i = 0; i < d; i++) {

        for (j = 0; j < d; j++) {

            p1.x = (p.x + ox + l);
            p1.y = p.y + oy;
            p1.z = p.z + oz + c;
            p2.x = (p.x + ox);
            p2.y = p.y + oy;
            p2.z = p.z + oz + c;
            p3.x = (p.x + ox + l);
            p3.y = p.y + oy;
            p3.z = p.z + oz;
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);

            p1.x = (p.x + ox);
            p1.y = p.y + oy;
            p1.z = p.z + oz;
            p2.x = (p.x + ox + l);
            p2.y = p.y + oy;
            p2.z = p.z + oz ;
            p3.x = (p.x + ox);
            p3.y = p.y + oy;
            p3.z = p.z + oz +c ;
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);

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

            p1.x = (p.x + ox);
            p1.y = p.y + oy;
            p1.z = p.z + oz;
            p2.x = (p.x + ox);
            p2.y = p.y + oy;
            p2.z = p.z + oz + c;
            p3.x = (p.x + ox + l);
            p3.y = p.y + oy;
            p3.z = p.z + oz;
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);

            p1.x = (p.x + ox + l);
            p1.y = p.y + oy;
            p1.z = p.z + oz + c;
            p2.x = (p.x + ox +l );
            p2.y = p.y + oy;
            p2.z = p.z + oz;
            p3.x = (p.x + ox);
            p3.y = p.y + oy;
            p3.z = p.z + oz +c ;
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);

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

             p1.x = (p.x + ox + l);
            p1.y = p.y + oy;
            p1.z = p.z + oz;
            p2.x = (p.x + ox + l);
            p2.y = p.y + oy + a ;
            p2.z = p.z + oz ;
            p3.x = (p.x + ox);
            p3.y = p.y + oy + a;
            p3.z = p.z + oz;
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);

             p1.x = (p.x + ox);
            p1.y = p.y + oy;
            p1.z = p.z + oz;
            p2.x = (p.x + ox + l);
            p2.y = p.y + oy;
            p2.z = p.z + oz;
            p3.x = p.x + ox;
            p3.y = p.y + oy + a;
            p3.z = p.z + oz;
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);

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

             p1.x = (p.x + ox);
            p1.y = p.y + oy;
            p1.z = p.z + oz;
            p2.x = (p.x + ox);
            p2.y = p.y + oy + a;
            p2.z = p.z + oz;
            p3.x = (p.x + ox + l);
            p3.y = p.y + oy;
            p3.z = p.z + oz;
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);

             p1.x = (p.x + ox + l);
            p1.y = p.y + oy;
            p1.z = p.z + oz;
            p2.x = (p.x + ox);
            p2.y = p.y + oy + a;
            p2.z = p.z + oz;
            p3.x = (p.x + ox + l);
            p3.y = p.y + oy + a;
            p3.z = p.z + oz;
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);

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

            p1.x = (p.x + ox);
            p1.y = p.y + oy;
            p1.z = p.z + oz;
            p2.x = (p.x + ox);
            p2.y = p.y + oy + a;
            p2.z = p.z + oz;
            p3.x = (p.x + ox);
            p3.y = p.y + oy;
            p3.z = p.z + oz + c;
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);

            p1.x = (p.x + ox);
            p1.y = p.y + oy + a;
            p1.z = p.z + oz;
            p2.x = (p.x + ox);
            p2.y = p.y + oy + a;
            p2.z = p.z + oz + c;
            p3.x = (p.x + ox);
            p3.y = p.y + oy;
            p3.z = p.z + oz + c;
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);

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

            p1.x = (p.x + ox);
            p1.y = p.y + oy;
            p1.z = p.z + oz;
            p2.x = (p.x + ox);
            p2.y = p.y + oy;
            p2.z = p.z + oz + c;
            p3.x = (p.x + ox);
            p3.y = p.y + oy + a;
            p3.z = p.z + oz;
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);

            p1.x = (p.x + ox);
            p1.y = p.y + oy + a;
            p1.z = p.z + oz;
            p2.x = (p.x + ox);
            p2.y = p.y + oy;
            p2.z = p.z + oz + c;
            p3.x = (p.x + ox);
            p3.y = p.y + oy + a;
            p3.z = p.z + oz + c;
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);

            oz += c;
        }

        oz = -comprimento / 2.0f;
        oy += a;
    }


    return points;
}
//draw sphere
vector<Point> sphere(float raio, int fatias, int camadas) {
        Point p, p1, p2, p3;
     vector<Point> points;
        float a = (2.0f * raio) / (float)camadas; //altura de uma camada
        float ang1 = 0.0f; //ponto da
        float ang2 = 2.0f * M_PI / (float)fatias;
        float oy, or1, or2 ;
        int i, j;

        p.x = p.y = p.z = 0;

        oy = -raio;

        for (i = 0; i < camadas ; i++) {

                or1 = sqrt(raio * raio - oy * oy);
                or2 = sqrt(raio * raio - (oy + a) * (oy + a));

                for (j = 0; j < fatias; j++) {

                        p1.x = cos(ang2) * or1;
                        p1.y = oy;
                        p1.z = sin(ang2) * or1;
                        p2.x = cos(ang1) * or2;
                        p2.y = oy + a;
                        p2.z = sin(ang1) * or2;
                        p3.x = cos(ang2) * or2;
                        p3.y = oy + a;
                        p3.z = sin(ang2) * or2;

                        points.push_back(p1);
                        points.push_back(p2);
                        points.push_back(p3);


                        p1.x = cos(ang1) * or1;
                        p1.y = -oy;
                        p1.z = sin(ang1) * or1;
                        p2.x = cos(ang2) * or2;
                        p2.y = -oy - a;
                        p2.z = sin(ang2) * or2;
                        p3.x = cos(ang1) * or2;
                        p3.y = -oy - a;
                        p3.z = sin(ang1) * or2;
                        points.push_back(p1);
                        points.push_back(p2);
                        points.push_back(p3);

                        ang1 += 2.0f * M_PI / (float)fatias;
                        ang2 += 2.0f * M_PI / (float)fatias;

                }

                oy += a;

        }


        return points;

}


//draw plane
vector<Point> plane(float s) {
    Point p, p1, p2, p3;
    vector<Point> points;
    float n = s / 2.0f;


    p.x = p.y = p.z = 0;


    p1.x = n + p.x;
    p1.y = p.y;
    p1.z = n + p.z;
    p2.x = n + p.x;
    p2.y = p.y;
    p2.z = -n + p.z;
    p3.x = -n + p.x;
    p3.y = p.y;
    p3.z = n + p.z;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);

    p1.x = -n + p.x;
    p1.y = p.y;
    p1.z = n + p.z;

    p2.x = n + p.x;
    p2.y = p.y;
    p2.z = -n + p.z;

    p3.x = -n + p.x;
    p3.y = p.y;
    p3.z = -n + p.z;

    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);

		p1.x = n + p.x;
		p1.y = p.y;
		p1.z = n + p.z;
		p2.x = -n + p.x;
		p2.y = p.y;
		p2.z = n + p.z;
		p3.x = n + p.x;
		p3.y = p.y;
		p3.z = -n + p.z;

		points.push_back(p1);
		points.push_back(p2);
		points.push_back(p3);

		p1.x = -n + p.x;
		p1.y = p.y;
		p1.z = n + p.z;

		p2.x = -n + p.x;
		p2.y = p.y;
		p2.z = -n + p.z;

		p3.x = n + p.x;
		p3.y = p.y;
		p3.z = -n + p.z;

		points.push_back(p1);
		points.push_back(p2);
		points.push_back(p3);


    return points;
}

//draw torus

vector<Point> torus(float radius, float width, int stack, int slice){

	int i, j; //contadores
	float oy, h = 1.0f / (float) stack;
	float ang = 0.0f, delt = 2 * M_PI / slice;
	float or1, or2;
 	point p1, p2, p3;
	vector<Point> points;

	for (i = 0; i < slice; i++){

			oy = -width / 2.0f;
			h = width / stack;

			for (j = 0; j < stack; j++) {

					or1 = sqrt( (width*width/4.0f) - oy*oy );
					or2 = sqrt( (width*width/4.0f) - (oy+h)*(oy+h) );

					p1.x = radius * sin(ang)  - or1 * sin(ang);
					p1.y = oy;
					p1.z = radius * cos(ang) - or1 * cos(ang);

					p2.x = radius * sin(ang) - or2 * sin(ang);
					p2.y = oy + h;
					p2.z = radius * cos(ang) - or2 * cos(ang);

					p3.x = radius * sin(ang + delt) - or1 * sin(ang + delt);
					p3.y = oy;
					p3.z = radius * cos(ang + delt) - or1 * cos(ang + delt);

					points.push_back(p1);
					points.push_back(p2);
					points.push_back(p3);

					p1.x = radius * sin(ang)  - or2 * sin(ang);
					p1.y = oy + h;
					p1.z = radius * cos(ang) - or2 * cos(ang);

					p2.x = radius * sin(ang + delt) - or2 * sin(ang + delt);
					p2.y = oy + h;
					p2.z = radius * cos(ang + delt) - or2 * cos(ang + delt);

					p3.x = radius * sin(ang + delt) - or1 * sin(ang + delt);
					p3.y = oy;
					p3.z = radius * cos(ang + delt) - or1 * cos(ang + delt);

					points.push_back(p1);
					points.push_back(p2);
					points.push_back(p3);

					p1.x = radius * sin(ang)  + or1 * sin(ang);
					p1.y = oy;
					p1.z = radius * cos(ang) + or1 * cos(ang);

					p2.x = radius * sin(ang + delt) + or1 * sin(ang + delt);
					p2.y = oy;
					p2.z = radius * cos(ang + delt) + or1 * cos(ang + delt );

					p3.x = radius * sin(ang) + or2 * sin(ang);
					p3.y = oy + h;
					p3.z = radius * cos(ang) + or2 * cos(ang);

					points.push_back(p1);
					points.push_back(p2);
					points.push_back(p3);

					p1.x = radius * sin(ang)  + or2 * sin(ang);
					p1.y = oy + h;
					p1.z = radius * cos(ang) + or2 * cos(ang);

					p2.x = radius * sin(ang + delt) + or1 * sin(ang + delt);
					p2.y = oy;
					p2.z = radius * cos(ang + delt) + or1 * cos(ang + delt);

					p3.x = radius * sin(ang + delt) + or2 * sin(ang + delt);
					p3.y = oy + h;
					p3.z = radius * cos(ang + delt) + or2 * cos(ang + delt);

					points.push_back(p1);
					points.push_back(p2);
					points.push_back(p3);

					oy += h;
			}

			ang += delt;

	}

return points;
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
        float width = atof(argv[2]);
        float height = atof(argv[3]);
        float length = atof(argv[4]);
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
		else if (strcmp("torus",argv[1]) == 0 && argc == 7)
    {
            float radius = atof(argv[2]);
						float width = atof(argv[3]);
            int slices = atoi(argv[4]);
            int layers = atoi(argv[5]);
            file = argv[6];
            points = torus(radius, width, slices, layers);
    }
    else if (strcmp("plane", argv[1]) == 0 && argc == 4)
    {
            float size = atof(argv[2]);
            file = argv[3];
            points = plane(size);
    }
   else {
        printf("Invalid input!\n");
        return -1;
    }
    if(points.size())
        writePointsFile(file,points);
     return 0;
}
