#include <stdlib.h>
#include "tinyxml2.h"
#include "engine.h"
#include "point.h"
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

void readTranslate(geoTransforms *group, XMLElement *element){
    float x=0, y=0, z=0, time = 0;
    vector<Point*> cPoints;
    Transformations *t;

    if (element->Attribute("time"))
    {
        bool deriv = false;
        if (element->Attribute("derivative"))
            deriv = (stoi(element->Attribute("derivative"))== 1) ? true : false;
        time = stof(element->Attribute("time"));
        time = 1 / (time * 1000);
        element = element->FirstChildElement("point");

        while (element != nullptr)
        {
            x = stof(element->Attribute("X"));
            y = stof(element->Attribute("Y"));
            z = stof(element->Attribute("Z"));

            Point *p = new Point(x,y,z);
            cPoints.push_back(p);

            element = element->NextSiblingElement("point");
        }

        t = new Transformations(time,cPoints,deriv,"translateTime");
        group->addTransformations(t);
    }
    else{   

    if(element->Attribute("X"))
        x = stof(element->Attribute("X"));

    if(element->Attribute("Y"))
        y = stof(element->Attribute("Y"));

    if(element->Attribute("Z"))
        z = stof(element->Attribute("Z"));

    t = new Transformations("translate",x,y,z,0.0f);
    group->addTransformations(t);

  }
}

void readRotate (geoTransforms *group, XMLElement *element){
    float angle = 0, x = 0, y = 0, z = 0;
    string type = "rotate";
    Transformations *t;

     if(element->Attribute("time"))
    {
        float time = stof(element->Attribute("time"));
        angle = 360 / (time * 1000);
        type = "rotateTime";
    }
    else if(element->Attribute("angle"))
        angle = stof(element->Attribute("angle"));

    if(element->Attribute("X"))
        x = stof(element->Attribute("X"));

    if(element->Attribute("Y"))
        y = stof(element->Attribute("Y"));

    if(element->Attribute("Z"))
        z = stof(element->Attribute("Z"));

 t = new Transformations(type,x,y,z, angle);
    group->addTransformations(t);
}

//função que lê um grupo do ficheiro XML
geoTransforms* readGroup(XMLElement* group){

	XMLElement *element, *innerElement;
	float x, y, z, ang;
	float r1, g1, b1, r2, g2, b2;
	geoTransforms* obj = new geoTransforms();
    Transformations *t;

	element = group->FirstChildElement();

	while (element != nullptr){

		if (strcmp(element->Value(), "translate") == 0) {
           readTranslate(obj, element);
        }    

		else if (strcmp(element->Value(), "rotate") == 0) {
            readRotate(obj,element);

		}

		else if (strcmp(element->Value(), "scale") == 0) {

				x = element->FloatAttribute("X");
				y = element->FloatAttribute("Y");
				z = element->FloatAttribute("Z");
                t = new Transformations("scale",x,y,z,0.0f);
				obj->addTransformations(t);
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


void drawOrbits(Transformations *t)
{
    vector<Point*> curvePoints = t->getPointsCurve();
    glColor3f(1.0f, 1.0f, 0.94f);
    glBegin(GL_POINTS);
    for(Point *p : curvePoints){
        float x = p->getX();
        float y = p->getY();
        float z = p->getZ();
        glVertex3f(x,y,z);
    }
    glEnd();
}

void applyTransformation(Transformations *t){
    float CTime = glutGet(GLUT_ELAPSED_TIME);
    if (stop != 1)
        eTime += CTime - cTime;
    cTime = CTime;
    const char* type = t->getType().c_str();
    float x = t->getX();
    float y = t->getY();
    float z = t->getZ();
    float angle = t->getAngle();
    float time = t->getTime();
    if(!strcmp(type,"colour")){
	    glColor3f(x,y,z);
    }
    if(!strcmp(type,"translate")){
        glTranslatef(x,y,z);
    }
    if(!strcmp(type,"rotate")){
        glRotatef(angle,x,y,z);
    }
    if(!strcmp(type,"scale")){
        glScaled(x,y,z);
    }
    if(!strcmp(type,"rotateTime")){
        float nA = eTime * angle;
        glRotatef(nA,x,y,z);
    }
    if(!strcmp(type,"translateTime")){
        float p[4], deriv[4];
        float dTime = eTime *time;
        t->getGlobalCatmullRomPoint(dTime,p,deriv);
        drawOrbits(t);
        glTranslatef(p[0],p[1],p[2]);
        if(t->getDeriv()){
            float res[4];
            t->normalize(deriv);
            t->cross(deriv,t->getVetor(),res);
            t->normalize(res);
            t->cross(res,deriv,t->getVetor());
            float matrix[16];
            t->normalize(t->getVetor());
            t->rotMatrix(matrix,deriv,t->getVetor(),res);

            glMultMatrixf(matrix);
        }
    }
}
//função que desenha (pontos com cor) de um grupo (pode ser recursiva se o grupo tiver grupos filhos)
void drawAndColor(geoTransforms* obj) {


		glPushMatrix();
        for (Transformations *t: obj->getTransformations()){
        applyTransformation(t);
        }

        vector<Shape*> shapeList = obj->getShapes();
        for(vector<Shape*>::iterator shape_it = shapeList.begin(); shape_it != shapeList.end(); ++shape_it)
            (*shape_it)->draw();
        int i=0;
        bool cor = true;

    glBegin(GL_TRIANGLES);
    for (const Pt pt : obj->getPoints())  {

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

void fps() {
    int time;
    char name[30];

    frame++;
    time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        float fps = frame * 1000.0/(time - timebase);
        timebase = time;
        frame = 0;
        sprintf(name,"SOLAR SYSTEM  %.2f FPS",fps);
        glutSetWindowTitle(name);
    }
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
        fps();

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

//Engine Guide
void mouvementguide(){
    std::cout << "                            || GUIDE ||                               " << std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "                 GUIDELINE: ./engine <XML FILE>                       " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "                               FILE:                                  " <<std::endl;
    std::cout << "  Specify the path to a XML file in which the information about the   " <<std::endl;
    std::cout << "              models you wish to create are specified.                " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "                               CAMERA:                                " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- RIGHT_ARROW_KEY :                                                   " <<std::endl;
    std::cout << "             Rotate the camera to right                               " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- LEFT_ARROW_KEY :                                                    " <<std::endl;
    std::cout << "             Rotate the camera to left                                " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- DOWN_ARROW_KEY :                                                    " <<std::endl;
    std::cout << "             Rotate the camera up ( Y Axe - Positive Direction )      " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- UP_ARROW_KEY :                                                      " <<std::endl;
    std::cout << "             Rotate the camera down ( Y Axe - Negative Direction)     " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
	std::cout << "                               MOVEMENT:                              " <<std::endl;
	std::cout << "                                                                      " <<std::endl;
	std::cout << "- W :                                                                 " <<std::endl;
	std::cout << "             Move forwards                                            " <<std::endl;
	std::cout << "                                                                      " <<std::endl;
	std::cout << "- S :                                                                 " <<std::endl;
	std::cout << "             Move backwards                                           " <<std::endl;
	std::cout << "                                                                      " <<std::endl;
	std::cout << "- D :                                                                 " <<std::endl;
	std::cout << "             Move to the right                                        " <<std::endl;
	std::cout << "                                                                      " <<std::endl;
	std::cout << "- A :                                                                 " <<std::endl;
	std::cout << "             Move Up                                                  " <<std::endl;
	std::cout << "                                                                      " <<std::endl;
	std::cout << "- Q :                                                                 " <<std::endl;
	std::cout << "             Move Down                                                " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "                              FORMAT:                                 " <<std::endl;
    std::cout << "- l :                                                                 " <<std::endl;
    std::cout << "     Figure format into lines                                         " <<std::endl;
    std::cout << "- p :                                                                 " <<std::endl;
    std::cout << "     Figure format into points                                        " <<std::endl;
    std::cout << "- f :                                                                 " <<std::endl;
    std::cout << "     Fill up the figure                                               " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "                              || END ||                               " <<std::endl;
}

int main(int argc, char **argv)
{
    // put GLUT init here
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("Solar System");
    #ifndef __APPLE__
    if (glewInit() != GLEW_OK)
    {
        cout << "Some problem with GLEW!" << endl;
        return -1;
    }
    #endif
	if (argc < 2) {
		cout << "Invalid input." << endl;
		return 0;
	}
	else if(!strcmp(argv[1],"-g")){
						mouvementguide();
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
    glEnableClientState(GL_VERTEX_ARRAY);

    // enter GLUT's main loop
    glutMainLoop();
    return 1;
}
