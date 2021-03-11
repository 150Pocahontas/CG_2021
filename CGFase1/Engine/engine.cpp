#include <stdlib.h>
#include "tinyxml2.h"
#include "engine.h"

using namespace std;
using namespace tinyxml2;

int readFile(string filename)
{
	Point p;
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
						p.x = stof(token);
					else if (i == 1)
						p.y = stof(token);
					else
						p.z = stof(token);
					i++;
				}
				points.push_back(p);
			}
		}
		points.pop_back(); 
		file.close();
	}
	return 0;
}

int readXML(string filename)
{
	XMLDocument doc;
    XMLNode *pRoot;
    XMLElement *element, *listElement;
    string fileDir = "../../files/" + filename;
    XMLError eResult = doc.LoadFile(fileDir.c_str());
    
    if (eResult == XML_SUCCESS)
    {
        pRoot = doc.FirstChild();
        if (pRoot != nullptr)
        {
            element = pRoot->FirstChildElement("models");
            
            if (element != nullptr)
            {
                listElement = element->FirstChildElement("model");
                
                while (listElement != nullptr)
                {
                    string file;
                    file = listElement->Attribute("file");
                    
                    if (!file.empty() && readFile(file) == -1)
                        return -1;
                    
                    listElement = listElement->NextSiblingElement("model");
                }
            }
        }
    }
    else
    {
        cout << "Unable to open file: " << filename << "." << endl;
        return -1;
    }
    return 0;
}
void keyboard (unsigned char k, int i, int j){
switch (k){
    case 'a':
            radius += step;
            glutPostRedisplay();
            break;
    case 'm':
            radius -= step;
            glutPostRedisplay();
            break;
	case 'p':
            line = GL_POINT;
            glutPostRedisplay();
            break;
    case 'l':
            line = GL_LINE;
            glutPostRedisplay();
            break;
    case 'f':
            line = GL_FILL;
            glutPostRedisplay();
            break;
    default:
            break;
	}
}

void specialKey (int k, int i, int j)
{
    (void)i;(void)j;
    switch (k)
    {
        case GLUT_KEY_UP:
            if (beta < (M_PI / 2 - step))
                beta += step;
            glutPostRedisplay();
            break;

        case GLUT_KEY_DOWN:
            if (beta > -(M_PI / 2 - step))
                beta -= step;
            glutPostRedisplay();
            break;

        case GLUT_KEY_LEFT:
            alpha -= step;
            glutPostRedisplay();
            break;

        case GLUT_KEY_RIGHT:
            alpha += step;
            glutPostRedisplay();
            break;
	       
        default:
            break;
    }
}
void drawAndColor(void) {
    glBegin(GL_TRIANGLES);
    int i=0;
    bool cor = true;
    
    for (const Point pt : points)  {
        if( i==3 ) {
            cor = !cor;
            i=0;
        }
        
        if(cor) {
            glColor3f(0.2, 02, 1);
            glVertex3f(pt.x, pt.y, pt.z);
        } else {
            glColor3f(0.7, 0.7, 1);
            glVertex3f(pt.x, pt.y, pt.z);
        }
        i++;
    }
    glEnd();
}


void renderScene(void)
{

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(radius*cos(beta)*sin(alpha), radius*sin(beta), radius*cos(beta)*cos(alpha),
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, line);

    //set primitives and colors
    drawAndColor();


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
    std::cout << "                             MOVEMENTS:                               " <<std::endl;
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
    std::cout << "                               ZOOM:                                  " <<std::endl;
    std::cout << "- m :                                                                 " <<std::endl;
    std::cout << "      Zoom in                                                         " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- a :                                                                 " <<std::endl;
    std::cout << "      Zoom out                                                        " <<std::endl;
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
    glutCreateWindow("Primitive");
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
	}

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main loop
    glutMainLoop();
    return 1;
}