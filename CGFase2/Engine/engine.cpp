#include <stdlib.h>
#include "tinyxml2.h"
#include "engine.h"
#include "geoTransforms.h"
#include "Transformations.h"

using namespace std;
using namespace tinyxml2;

//vetor dos grupos de cada respetivo astro
vector<geoTransforms*> astros;


//função que lê um ficheiro .3d e que faz storage dos pontos todos vetor de pontos "points" para uma instância da classe geoTransforms
int readFile(string filename, geoTransforms* obj)
{
	float x, y, z;
	float r1, g1, b1, r2, g2, b2;
	string line, token;
	ifstream file(filename);
	int i;

	if (!file.is_open()) {
		cout << "Unable to open file: " << filename << "." << endl; return -1;
	}
	else
	{
		while (!file.eof())
		{
			getline(file, line);
			stringstream ss(line.c_str());

			if (line.c_str() != NULL)
			{
				i = 0;
				while (getline(ss, token, ','))
				{
					if (i == 0)
						x = stof(token);
					else if (i == 1)
						y = stof(token);
					else
						z = stof(token);
					i++;
				}
				obj->addPoint(x,y,z);
			}
		}
	//	obj.popPoints();
		file.close();
	}
	return 0;
}

//função que lê um grupo do ficheiro XML
geoTransforms* readGroup(XMLElement* group){

	XMLElement *element, *innerElement;
	float x, y, z, ang;
	float r1, g1, b1, r2, g2, b2;
	geoTransforms* obj = new geoTransforms();

	element = group->FirstChildElement();

	while (element != nullptr){

		if (strcmp(element->Value(), "translate") == 0) {

				x = element->FloatAttribute("X");
				y = element->FloatAttribute("Y");
				z = element->FloatAttribute("Z");
				obj->addTransformations("translate",x,y,z,0.0f);
		}

		else if (strcmp(element->Value(), "rotate") == 0) {
				x = element->FloatAttribute("X");
				y = element->FloatAttribute("Y");
				z = element->FloatAttribute("Z");
				ang = element->FloatAttribute("Angle");
			obj->addTransformations("rotate",x,y,z,ang);
		}

		else if (strcmp(element->Value(), "scale") == 0) {

				x = element->FloatAttribute("X");
				y = element->FloatAttribute("Y");
				z = element->FloatAttribute("Z");
				obj->addTransformations("scale",x,y,z,0.0f);
		}

		else if (strcmp(element->Value(), "models") == 0){

			innerElement = element->FirstChildElement();

			while (innerElement != nullptr){

				if (strcmp(innerElement->Value(), "model") == 0){

					string file;
					file = innerElement->Attribute("file");

					if (!file.empty() && readFile(file, obj) == -1)	return nullptr;
				}

				else if (strcmp(innerElement->Value(), "color") == 0){

					r1 = innerElement->FloatAttribute("R1");
					g1 = innerElement->FloatAttribute("G1");
					b1 = innerElement->FloatAttribute("B1");
					r2 = innerElement->FloatAttribute("R2");
					g2 = innerElement->FloatAttribute("G2");
					b2 = innerElement->FloatAttribute("B2");

					obj->setColor(r1,g1,b1,r2,g2,b2);

				}

					innerElement = innerElement->NextSiblingElement();
			}
		}

	else if (strcmp(element->Value(), "group") == 0){
		geoTransforms* chi = readGroup(element);
		obj->addChild(chi);
		}

		element = element->NextSiblingElement();
	}

	return obj;
}

//função que começa a ler o ficheiro XML
int readXML(string filename)
{
	XMLDocument doc;
	string fileDir = "../files/" + filename;
	XMLError eResult = doc.LoadFile(fileDir.c_str());
  XMLNode *pRoot;
  XMLElement *group;

	if (eResult == XML_SUCCESS)
	{
		pRoot = doc.FirstChild();
		if (pRoot != nullptr)
		{
				group = pRoot->FirstChildElement();

				while(group != nullptr){

				geoTransforms* obj = readGroup(group);
				astros.push_back(obj);
				group = group->NextSiblingElement();
			}
		}
	}
  else
    {
        return -1;
    }

    return 0;
}

//função responsável pelos inputs de caracteres do teclado (afeta o movimento da camera e o draw mode)
void keyboard (unsigned char k, int i, int j){
switch (k){

	case 'w':
				    movX += sin(alpha);
			      movZ += cos(alpha);
			      break;

 	case 's':
			     	movX -= sin(alpha);
				    movZ -= cos(alpha);
       			break;

  case 'd':
	          movX += sin(alpha - M_PI / 2.0f);
		        movZ += cos(alpha -  M_PI / 2.0f);
		        break;

  case 'a':
	      		movX -= sin(alpha - M_PI / 2.0f);
	         	movZ -= cos(alpha - M_PI / 2.0f);
	          break;

	case 'q':
					  movY -= 0.5f;
					  break;

  case 'e':
					  movY += 0.5f;
					  break;

     //draw mode
     //points
	case 'p':
            line = GL_POINT;
            break;
    //lines
    case 'l':
            line = GL_LINE;
            break;

    //full
    case 'f':
            line = GL_FILL;
            break;

		default:
            break;
	}
	  glutPostRedisplay();
}

//função responsavel pelo input das setas (altera a orientação da camera)
void specialKey (int k, int i, int j)
{
    switch (k)
    {
        case GLUT_KEY_UP:
						beta += 0.1f;
						if (beta > 1.5f)
						beta = 1.5f;
						break;

        case GLUT_KEY_DOWN:
						beta -= 0.1f;
						if (beta < -1.5f)
						beta = -1.5f;
						break;

        case GLUT_KEY_LEFT:
            alpha += 0.1;
            glutPostRedisplay();
            break;

        case GLUT_KEY_RIGHT:
            alpha -= 0.1;
						break;
            break;

        default:
            break;
    }
	glutPostRedisplay();
}

//função responsavel por orientar a orientação da camera em função do movimento do rato quando este é pressionado
void mouseActiveMovEvent(int x, int y){

    mposX1 = (float)x;
    mposY1 = (float)y;

    mdeltX = (mposX1 - mposX2) * 0.001f;
    mdeltY = (mposY1 - mposY2) * 0.001f;

    alpha += mdeltX;
    beta += mdeltY;

    glutPostRedisplay();
    mposX2 = mposX1;
    mposY2 = mposY1;

}

//função que atualiza a posição do rato quando este não é pressionado
void mousePassiveMovEvent(int x, int y){
    mposX1 = (float)x;
    mposY1 = (float)y;

    mposX2 = mposX1;
    mposY2 = mposY1;
}



//função que desenha (pontos com cor) de um grupo (pode ser recursiva se o grupo tiver grupos filhos)
void drawAndColor(geoTransforms* obj) {


		glPushMatrix();


		vector<Transformations*> tran = obj->getTransformations();

		//transformações
		for (Transformations *transf : obj->getTransformations()){

		if (transf->getType() == "translate") {
			glTranslatef(transf->getX(), transf->getY(), transf->getZ());
		}
		if (transf->getType() == "scale") {
			glScalef(transf->getX(), transf->getY(), transf->getZ());
		}
		if (transf->getType() == "rotate") {
			glRotatef(transf->getAngle(), transf->getX(), transf->getY(), transf->getZ());
		}
	}

    int i=0;
    bool cor = true;

  glBegin(GL_TRIANGLES);
    for (const Point pt : obj->getPoints())  {

        if( i==3 ) {
            cor = !cor;
            i=0;
        }

        if(cor) {
            glColor3f(obj->getR1(), obj->getG1(), obj->getB1());
            glVertex3f(pt.x, pt.y, pt.z);
        } else {
            glColor3f(obj->getR2(), obj->getG2(), obj->getB2());
            glVertex3f(pt.x, pt.y, pt.z);
        }
        i++;
    }
    glEnd();

		for (geoTransforms *chi : obj->getChild()) drawAndColor(chi);

		glPopMatrix();
}


void renderScene(void)
{

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();

    gluLookAt(movX, movY, movZ ,
              movX + cos(beta)*sin(alpha), movY + sin(beta), movZ + cos(beta)*cos(alpha),
              0.0f, 1.0f, 0.0f);

    glPolygonMode(GL_FRONT_AND_BACK, line);

    //set primitives and colors
		for (geoTransforms* obj : astros) drawAndColor(obj);


    // End of frame
    glutSwapBuffers();
}

void changeSize(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char **argv)
{
    // put GLUT init here
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("Primitive");
	if (argc < 2) {
		cout << "Invalid input." << endl;
		return 0;
	}

	else if (readXML(argv[1]) == 0) {
		// put callback registration here
		glutDisplayFunc(renderScene);
		glutReshapeFunc(changeSize);
		glutIdleFunc(renderScene);
		glutSpecialFunc(specialKey);
		glutKeyboardFunc(keyboard);
		glutMotionFunc(mouseActiveMovEvent);
		glutPassiveMotionFunc(mousePassiveMovEvent);
	}

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main loop
    glutMainLoop();
    return 1;
}
