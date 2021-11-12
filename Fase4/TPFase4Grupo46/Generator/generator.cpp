#define _USE_MATH_DEFINES

#include "generator.h"

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <string.h>

using namespace std;
vector<Point> points;
vector<Point> normals;



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

void writePointNormalFile(string filename, std::vector<Point> points, std::vector<Point> normals) {
    ofstream file;
    string x, y, z;
        string fileDir = "../files/" + filename;
    file.open(fileDir, ios_base::trunc);

    if (!file.is_open()) {
        cout << "Error while opening the file " << filename << endl;
    }
    else {

        file << "p:\n";
        for (const Point point : points) {

            x = to_string(point.x).append(",");
            y = to_string(point.y).append(",");
            z = to_string(point.z).append("\n");

            file << x << y << z;
        }

        file << "n:\n";

        for (const Point point : normals) {

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

Point normalizeVec(point v){

Point n;
float x, y, z, max;

if (v.x < 0) x = v.x * (-1);
else x = v.x;

if (v.y < 0) y = v.y * (-1);
else y = v.y;

if (v.z < 0) z = v.z * (-1);
else z = v.z;

max = x;
if (y > max) max = y;
if (z > max) max = z;

if (max == 0) {n.x = 0.0f; n.y = 0.0f; n.z = 0.0f;}
else{
n.x = v.x / max;
n.y = v.y / max;
n.z = v.z / max;
}
return n;
}

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
vector<Point> spherePoints(float raio, int fatias, int camadas) {
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
//draw sphere
vector<Point> sphereNormals(float raio, int fatias, int camadas) {

        // VETOR: A(ponto da frente) - B(ponto de trás)
        // como o centro da esfera se situa na posição 0,0,0, as normais serão iguais

        Point p, p1, p2, p3;
     vector<Point> normals;
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

                        normals.push_back(normalizeVec(p1));
                        normals.push_back(normalizeVec(p2));
                        normals.push_back(normalizeVec(p3));


                        p1.x = cos(ang1) * or1;
                        p1.y = -oy;
                        p1.z = sin(ang1) * or1;
                        p2.x = cos(ang2) * or2;
                        p2.y = -oy - a;
                        p2.z = sin(ang2) * or2;
                        p3.x = cos(ang1) * or2;
                        p3.y = -oy - a;
                        p3.z = sin(ang1) * or2;
                        normals.push_back(normalizeVec(p1));
                        normals.push_back(normalizeVec(p2));
                        normals.push_back(normalizeVec(p3));

                        ang1 += 2.0f * M_PI / (float)fatias;
                        ang2 += 2.0f * M_PI / (float)fatias;

                }

                oy += a;

        }


        return normals;

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

vector<Point> torusPoints(float radius, float width, int stack, int slice){

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

vector<Point> torusNormals(float radius, float width, int stack, int slice){

    int i, j; //contadores
    float oy, h = 1.0f / (float) stack;
    float ang = 0.0f, delt = 2 * M_PI / slice;
    float or1, or2;
    point p1, p2, p3;
    vector<Point> normals;

    for (i = 0; i < slice; i++){

            oy = -width / 2.0f;
            h = width / stack;

            for (j = 0; j < stack; j++) {

                    or1 = sqrt( (width*width/4.0f) - oy*oy );
                    or2 = sqrt( (width*width/4.0f) - (oy+h)*(oy+h) );

                    p1.x = - or1 * sin(ang);
                    p1.y = oy;
                    p1.z = - or1 * cos(ang);

                    p2.x = - or2 * sin(ang);
                    p2.y = oy + h;
                    p2.z = - or2 * cos(ang);

                    p3.x = - or1 * sin(ang + delt);
                    p3.y = oy;
                    p3.z = - or1 * cos(ang + delt);

                    normals.push_back(normalizeVec(p1));
                    normals.push_back(normalizeVec(p2));
                    normals.push_back(normalizeVec(p3));

                    p1.x = - or2 * sin(ang);
                    p1.y = oy + h;
                    p1.z = - or2 * cos(ang);

                    p2.x = - or2 * sin(ang + delt);
                    p2.y = oy + h;
                    p2.z = - or2 * cos(ang + delt);

                    p3.x = - or1 * sin(ang + delt);
                    p3.y = oy;
                    p3.z = - or1 * cos(ang + delt);

                    normals.push_back(normalizeVec(p1));
                    normals.push_back(normalizeVec(p2));
                    normals.push_back(normalizeVec(p3));

                    p1.x = or1 * sin(ang);
                    p1.y = oy;
                    p1.z = or1 * cos(ang);

                    p2.x = or1 * sin(ang + delt);
                    p2.y = oy;
                    p2.z = or1 * cos(ang + delt );

                    p3.x = or2 * sin(ang);
                    p3.y = oy + h;
                    p3.z = or2 * cos(ang);

                    normals.push_back(normalizeVec(p1));
                    normals.push_back(normalizeVec(p2));
                    normals.push_back(normalizeVec(p3));

                    p1.x = or2 * sin(ang);
                    p1.y = oy + h;
                    p1.z = or2 * cos(ang);

                    p2.x = or1 * sin(ang + delt);
                    p2.y = oy;
                    p2.z = or1 * cos(ang + delt);

                    p3.x = or2 * sin(ang + delt);
                    p3.y = oy + h;
                    p3.z = or2 * cos(ang + delt);

                    normals.push_back(normalizeVec(p1));
                    normals.push_back(normalizeVec(p2));
                    normals.push_back(normalizeVec(p3));

                    oy += h;
            }

            ang += delt;

    }

return normals;
}

Point bezierPoint(float t, Point p0, Point p1, Point p2, Point p3){

    Point p;
    float it = 1.0f - t;
    float at = pow(it, 3);
    float bt = 3 * t * pow(it, 2);
    float ct = 3 * pow(t, 2) * it;
    float dt = pow(t, 3);

    p.x = (at*p0.x) + (bt*p1.x) + (ct*p2.x) + (dt*p3.x);
    p.y = (at*p0.y) + (bt*p1.y) + (ct*p2.y) + (dt*p3.y);
    p.z = (at*p0.z) + (bt*p1.z) + (ct*p2.z) + (dt*p3.z);

    return p;
}

Point bezierTangent(float t, Point p0, Point p1, Point p2, Point p3){

    Point p;
    float at = (-3 * t * t) + (6 * t) - 3;
    float bt = 3 - (12 * t) + (9 * t * t);
    float ct = (6 * t) - (9 * t * t);
    float dt = 3 * t * t;

    p.x = (at*p0.x) + (bt*p1.x) + (ct*p2.x) + (dt*p3.x);
    p.y = (at*p0.y) + (bt*p1.y) + (ct*p2.y) + (dt*p3.y);
    p.z = (at*p0.z) + (bt*p1.z) + (ct*p2.z) + (dt*p3.z);

    return p;
}

Point vectorProduct(point u, point v){

    point r;

    r.x = (u.y * v.z ) - (u.z * v.y);
    r.y = (u.z * v.x ) - (u.x * v.z);
    r.z = (u.x * v.y ) - (u.y * v.x);

        r = normalizeVec(r);

    return r;
}

vector<Point> createBezierSurf(int tess, vector<int> ind, vector<Point> ctrl, int ni){
        //  cout << "Ponto " << ind[i] << ": " << ctrl[ind[i]].x << " " << ctrl[ind[i]].y << " " << ctrl[ind[i]].z << "\n";
    int i, j, k;
    float intv = 1.0f / (float)tess;
    float v = 0, u = 0;
    Point p, p1, p2, p3, p4, a0, a1, a2, a3, b0, b1, b2, b3;
    float x, y, z;
    vector<Point> points;

for(k=0; k < ni; k++){

    for(i = 0; i < tess; i++){

        for(j = 0; j < tess; j++){

            a0 = bezierPoint(u, ctrl[ind[k*16]], ctrl[ind[k*16+1]], ctrl[ind[k*16+2]], ctrl[ind[k*16+3]]);
            a1 = bezierPoint(u, ctrl[ind[k*16+4]], ctrl[ind[k*16+5]], ctrl[ind[k*16+6]], ctrl[ind[k*16+7]]);
            a2 = bezierPoint(u, ctrl[ind[k*16+8]], ctrl[ind[k*16+9]], ctrl[ind[k*16+10]], ctrl[ind[k*16+11]]);
            a3 = bezierPoint(u, ctrl[ind[k*16+12]], ctrl[ind[k*16+13]], ctrl[ind[k*16+14]], ctrl[ind[k*16+15]]);

            b0 = bezierPoint(u+intv, ctrl[ind[k*16]], ctrl[ind[k*16+1]], ctrl[ind[k*16+2]], ctrl[ind[k*16+3]]);
            b1 = bezierPoint(u+intv, ctrl[ind[k*16+4]], ctrl[ind[k*16+5]], ctrl[ind[k*16+6]], ctrl[ind[k*16+7]]);
            b2 = bezierPoint(u+intv, ctrl[ind[k*16+8]], ctrl[ind[k*16+9]], ctrl[ind[k*16+10]], ctrl[ind[k*16+11]]);
            b3 = bezierPoint(u+intv, ctrl[ind[k*16+12]], ctrl[ind[k*16+13]], ctrl[ind[k*16+14]], ctrl[ind[k*16+15]]);

            p1 = bezierPoint(v, a0, a1, a2, a3);
            p2 = bezierPoint(v, b0, b1, b2, b3);
            p3 = bezierPoint(v+intv, a0, a1, a2, a3);
            p4 = bezierPoint(v+intv, b0, b1, b2, b3);

            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p4);

            points.push_back(p4);
            points.push_back(p3);
            points.push_back(p1);

            u += intv;
        }
        u = 0;
        v += intv;
    }
    v = 0;
    u = 0;
}

return points;
}

vector<Point> createBezierSurfNormals(int tess, vector<int> ind, vector<Point> ctrl, int ni){
        //  cout << "Ponto " << ind[i] << ": " << ctrl[ind[i]].x << " " << ctrl[ind[i]].y << " " << ctrl[ind[i]].z << "\n";
    int i, j, k;
    float intv = 1.0f / (float)tess;
    float v = 0, u = 0;
    vector<Point> normals;
    Point p00, p01, p02, p03, p10, p11, p12, p13, p20, p21, p22, p23, p30, p31, p32, p33, r0, r1, r2, r3;;
    Point vecu, vecv, v1, v2, v3, v4;
    float ut0, ut1, ut2, ut3, vt0, vt1, vt2, vt3;

for(k=0; k < ni; k++){

    for(i = 0; i < tess; i++){

        for(j = 0; j < tess; j++){

            p00 = ctrl[ind[k*16]]; p01 = ctrl[ind[k*16+1]]; p02 = ctrl[ind[k*16+2]]; p03 = ctrl[ind[k*16+3]];
            p10 = ctrl[ind[k*16+4]]; p11 = ctrl[ind[k*16+5]]; p12 = ctrl[ind[k*16+6]]; p13 = ctrl[ind[k*16+7]];
            p20 = ctrl[ind[k*16+8]]; p21 = ctrl[ind[k*16+9]]; p22 = ctrl[ind[k*16+10]]; p23 = ctrl[ind[k*16+11]];
            p30 = ctrl[ind[k*16+12]]; p31 = ctrl[ind[k*16+13]]; p32 = ctrl[ind[k*16+14]]; p33 = ctrl[ind[k*16+15]];

            //vetor 1

            r0 = bezierTangent(u, p00, p01, p02, p03);
            r1 = bezierTangent(u ,p10, p11, p12, p13);
            r2 = bezierTangent(u ,p20, p21, p22, p23);
            r3 = bezierTangent(u ,p30, p31, p32, p33);

            vecu = bezierPoint(v, r0, r1, r2, r3);

            r0 = bezierPoint(u, p00, p01, p02, p03);
            r1 = bezierPoint(u ,p10, p11, p12, p13);
            r2 = bezierPoint(u ,p20, p21, p22, p23);
            r3 = bezierPoint(u ,p30, p31, p32, p33);

            vecv = bezierTangent(v, r0, r1, r2, r3);

            v1 = vectorProduct(vecu, vecv);

            //vetor 2

            r0 = bezierTangent(u+intv, p00, p01, p02, p03);
            r1 = bezierTangent(u+intv ,p10, p11, p12, p13);
            r2 = bezierTangent(u+intv ,p20, p21, p22, p23);
            r3 = bezierTangent(u+intv ,p30, p31, p32, p33);

            vecu = bezierPoint(v, r0, r1, r2, r3);

            r0 = bezierPoint(u+intv, p00, p01, p02, p03);
            r1 = bezierPoint(u+intv ,p10, p11, p12, p13);
            r2 = bezierPoint(u+intv ,p20, p21, p22, p23);
            r3 = bezierPoint(u+intv ,p30, p31, p32, p33);

            vecv = bezierTangent(v, r0, r1, r2, r3);

            v2 = vectorProduct(vecu, vecv);

            //vetor 3

            r0 = bezierTangent(u, p00, p01, p02, p03);
            r1 = bezierTangent(u ,p10, p11, p12, p13);
            r2 = bezierTangent(u ,p20, p21, p22, p23);
            r3 = bezierTangent(u ,p30, p31, p32, p33);

            vecu = bezierPoint(v+intv, r0, r1, r2, r3);

            r0 = bezierPoint(u, p00, p01, p02, p03);
            r1 = bezierPoint(u ,p10, p11, p12, p13);
            r2 = bezierPoint(u ,p20, p21, p22, p23);
            r3 = bezierPoint(u ,p30, p31, p32, p33);

            vecv = bezierTangent(v+intv, r0, r1, r2, r3);

            v3 = vectorProduct(vecu, vecv);

            //vetor 4

            r0 = bezierTangent(u+intv, p00, p01, p02, p03);
            r1 = bezierTangent(u+intv ,p10, p11, p12, p13);
            r2 = bezierTangent(u+intv ,p20, p21, p22, p23);
            r3 = bezierTangent(u+intv ,p30, p31, p32, p33);

            vecu = bezierPoint(v+intv, r0, r1, r2, r3);

            r0 = bezierPoint(u+intv, p00, p01, p02, p03);
            r1 = bezierPoint(u+intv ,p10, p11, p12, p13);
            r2 = bezierPoint(u+intv ,p20, p21, p22, p23);
            r3 = bezierPoint(u+intv ,p30, p31, p32, p33);

            vecv = bezierTangent(v+intv, r0, r1, r2, r3);

            v4 = vectorProduct(vecu, vecv);

            normals.push_back(v1);
            normals.push_back(v2);
            normals.push_back(v4);

            normals.push_back(v4);
            normals.push_back(v3);
            normals.push_back(v1);

            u += intv;
        }
        u = 0;
        v += intv;
    }
    v = 0;
    u = 0;
}

return normals;
}

vector<Point> teapotPoints(int tess, string file){

    int i, c;
    int ni; //number of indices
    int nv; // number of vertices
    Point p;
    string line, token;
    vector<int> indices;
    vector<Point> bezier;

    fstream patch;
        patch.open("../files/" + file, ios::in);
        if (!patch) {
            printf("No such file\n");
        }
        else {

                //obter o numero dos indices
                getline(patch, line);
                ni = stoi(line);

                //criar vetor de indices
                i = 0;
                while (i < ni)
                {
                    getline(patch, line);
                    stringstream ss(line.c_str());
                    if (line.c_str() != NULL)
                    {
                        while (getline(ss, token, ',')) indices.push_back(stoi(token));
                        i++;
                    }
                }

                getline(patch, line);
                nv = stoi(line);

                while (!patch.eof())
                {
                    getline(patch, line);
                    stringstream ss(line.c_str());

                    if (line.c_str() != NULL)
                    {
                        i = 0;
                        while (getline(ss, token, ','))
                        {
                            if (i == 0){
                                p.x = stof(token);
                            }
                            else if (i == 1){
                                p.y = stof(token);
                            }
                            else {
                                p.z = stof(token);
                            }
                            i++;
                        }
                        bezier.push_back(p);
                    }
                }

        }
        patch.close();

        vector<Point> points = createBezierSurf(tess, indices, bezier, ni);

        return points;
}

vector<Point> teapotNormals(int tess, string file){

    int i, c;
    int ni; //number of indices
    int nv; // number of vertices
    Point p;
    string line, token;
    vector<int> indices;
    vector<Point> bezier;

    fstream patch;
        patch.open("../files/" + file, ios::in);
        if (!patch) {
            printf("No such file\n");
        }
        else {

                //obter o numero dos indices
                getline(patch, line);
                ni = stoi(line);

                //criar vetor de indices
                i = 0;
                while (i < ni)
                {
                    getline(patch, line);
                    stringstream ss(line.c_str());
                    if (line.c_str() != NULL)
                    {
                        while (getline(ss, token, ',')) indices.push_back(stoi(token));
                        i++;
                    }
                }

                getline(patch, line);
                nv = stoi(line);

                while (!patch.eof())
                {
                    getline(patch, line);
                    stringstream ss(line.c_str());

                    if (line.c_str() != NULL)
                    {
                        i = 0;
                        while (getline(ss, token, ','))
                        {
                            if (i == 0){
                                p.x = stof(token);
                            }
                            else if (i == 1){
                                p.y = stof(token);
                            }
                            else {
                                p.z = stof(token);
                            }
                            i++;
                        }
                        bezier.push_back(p);
                    }
                }

        }
        patch.close();

        vector<Point> normals = createBezierSurfNormals(tess, indices, bezier, ni);

        return normals;
}

int main (int argc, char **argv)
{
        int norm = 0;

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
            norm = 1;
            float radius = atof(argv[2]);
            int slices = atoi(argv[3]);
            int layers = atoi(argv[4]);
            file = argv[5];
            points = spherePoints(radius, slices, layers);
            normals = sphereNormals(radius, slices, layers);

    }
    else if (strcmp("plane", argv[1]) == 0 && argc == 4)
    {
            float size = atof(argv[2]);
            file = argv[3];
            points = plane(size);
    }
        else if (strcmp("torus",argv[1]) == 0 && argc == 7)
    {
                    norm = 1;
                    float radius = atof(argv[2]);
                    float width = atof(argv[3]);
                    int stack = atoi(argv[4]);
                    int slice = atoi(argv[5]);
                    file = argv[6];
                    points = torusPoints(radius, width, stack, slice);
                    normals = torusNormals(radius, width, stack, slice);
    }
     else if (strcmp("teapot", argv[1]) == 0){
         norm = 1;
         int tess = atoi(argv[2]);
         string patch = argv[3];
         file = argv[4];
         points = teapotPoints(tess, patch);
         normals = teapotNormals(tess, patch);
     }
   else {
        printf("Invalid input!\n");
        return -1;
    }
    if(points.size())
        if (norm == 1) writePointNormalFile(file, points, normals);
        else writePointsFile(file,points);
     return 0;
}
