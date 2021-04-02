#include <stdlib.h>
#include "tinyxml2.h"
#include "engine.h"
#include "geoTransforms.h"

using namespace std;
using namespace tinyxml2;
int readFile(string filename, vector<Point*> *points)
{
    string line, token;
    ifstream file(filename);
    int i, j=0;
    vector<float> tokens;

    if (!file.is_open()) {
        cout << "Unable to open file: " << filename << "." << endl; 
        return -1;
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
                while (i<3 && getline(ss, token, ','))
                {
                    tokens.push_back(stof(token));
                    i++;
                }
                Point *p = new Point (token[j++], tokens[j++], tokens[j++]);
                points->push_back(p);
            }
        }
        points->pop_back();
        file.close();
    }
    return 0;
}

Group* readXML(string filename, vector<Point*> *points)
{
    Group* group = nullptr;
    XMLDocument doc;
    XMLNode *pRoot;
    XMLElement *element;
    string fileDir = "../files/" + filename;
    XMLError eResult = doc.LoadFile(fileDir.c_str());

    if (eResult == XML_SUCCESS)
    {
        pRoot = doc.FirstChild();
        if (pRoot != nullptr)
        {
            group = new Group();
            element = pRoot->FirstChildElement("group");
            readGroup(group,element, points,0);
        }
    }
    else
    {
        cout << "Unable to open file: " << filename << "." << endl;
    }
    return group;
}

void readRotate (Group* group, XMLElement* element){
    float angle = 0;
    float x = 0;
    float y = 0;
    float z = 0;
    string type = "rotation";
    Transformation *t;
    if (element-> Attribute("angle"))
      angle = stof(element->Attribute("angle"));

    if (element-> Attribute("X"))
      x = stof(element->Attribute("X"));

    if (element-> Attribute("Y"))
      y = stof(element->Attribute("Y"));
    
    if (element-> Attribute("Z"))
      z = stof(element->Attribute("z"));     

    t = new Transformation(type,angle,x,y,z);
    group->addTransformation(t);
}

void readTranslate (Group *group, XMLElement *element, vector<Point*> *orbits, int d)
{
    float x=0, y=0, z=0;
    string type = "translation";
    Transformation *t;

    if(element->Attribute("X"))
        x = stof(element->Attribute("X"));

    if(element->Attribute("Y"))
        y = stof(element->Attribute("Y"));

    if(element->Attribute("Z"))
        z = stof(element->Attribute("Z"));

    t = new Transformation(type,0,x,y,z);
    group->addTransformation(t);

    if (d == 0 || d == 1)
    {
        Point *p = new Point(x,y,z);
        orbits->push_back(p);
    }
} 

void readScale (Group *group, XMLElement *element){
    float x=1, y=1, z=1;
    string type = "scale";
    Transformation *t;

    if(element->Attribute("X"))
        x = stof(element->Attribute("X"));

    if(element->Attribute("Y"))
        y = stof(element->Attribute("Y"));

    if(element->Attribute("Z"))
        z = stof(element->Attribute("Z"));

    t = new Transformation(type,0,x,y,z);
    group->addTransformation(t);
}

void readColour (Group *group, XMLElement *element){
    float x=1, y=1, z=1;
    string type = "colour";
    Transformation *t;

    if(element->Attribute("R"))
        x = stof(element->Attribute("R"));

    if(element->Attribute("G"))
        y = stof(element->Attribute("G"));

    if(element->Attribute("B"))
        z = stof(element->Attribute("B"));

    t = new Transformation(type,0,x,y,z);
    group->addTransformation(t);
}


void readModels (Group *group, XMLElement *element) {
    string file;
    vector<Shape*> shapes;

    element = element->FirstChildElement("model");

    if (element == nullptr) {
        cout << "XML error: Models are not available!" << endl;
        return;
    }

    while (element != nullptr) {

        file = element->Attribute("file");
        string fileDir = "../files/" + file;
        if(!file.empty()) {
            vector<Point*> points;
            readFile(fileDir, &points);

            if (points.size()) {
                Shape *shape = new Shape(points);
                shapes.push_back(shape);
            }
        }
        element = element->NextSiblingElement("model");
    }

    if (shapes.size())
        group->setShapes(shapes);
}


void readGroup (Group *group, XMLElement *gElement, vector<Point*> *orbits, int d)
{
    XMLElement *element = gElement->FirstChildElement();

    while (element)
    {
        if (strcmp(element->Name(),"translate") == 0)
            readTranslate(group,element,orbits,d);

        else if (strcmp(element->Name(),"scale") == 0)
            readScale(group,element);

        else if (strcmp(element->Name(),"rotate") == 0)
            readRotate(group,element);

        else if (strcmp(element->Name(),"models") == 0)
            readModels(group, element);

    else if (strcmp(element->Name(),"colour") == 0)
            readColour(group, element);

        else if (strcmp(element->Name(),"group") == 0)
        {
            Group *child = new Group();
            group->addGroup(child);
            readGroup(child,element,orbits,d+1);
        }

        element = gElement->NextSiblingElement();
    }
}

/*
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
*/
void drawScene(Group* scene){
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor3f(0.5f, 0.5f, 1.0f);
    for (Transformation *t : scene ->getTrans())
    {
        t->apply();
    }
    for (Shape *shape : scene->getShapes()){

        for (Point *p : shape->getPoints())
            glVertex3f(p->getX(), p->getY(), p->getZ());
    }
    glEnd();

    for (Group *g : scene->getGroups())
        drawScene(g);
    glPopMatrix();
}




void drawOrbits()
{
    glColor3f(1.0f, 1.0f, 0.94f);

    for(auto const& p : orbits){
        glBegin(GL_POINTS);
        for (int j = 0 ; j < 200 ; j++)
        {
            float x = p->getX() * p->getX();
            float y = p->getY() * p->getY();
            float z = p->getZ() * p->getZ();
            float radius = sqrtf(x + y + z);
            float alpha = j * 2 * M_PI / 200;
            glVertex3f(radius * cos(alpha), 0, radius * sin(alpha));
        }
        glEnd();
    }
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

    //axes
   // wirePlane(2.0f);

    //set primitives and colors
    
        drawScene(scene);
        drawOrbits();

    // End of frame
    glutSwapBuffers();
}
void keyboard (unsigned char k, int i, int j){
switch (k){
        //reset
        case 'r':
                alpha = 0.7f;
                beta = 0.3f;
                step = 0.08f;
                glutPostRedisplay();
                break;



    //zoom
    case 'o':
            radius += step;
            glutPostRedisplay();
            break;
    case 'i':
            radius -= step;
            glutPostRedisplay();
            break;

     //draw mode
     //points
    case 'p':
            line = GL_POINT;
            glutPostRedisplay();
            break;
    //lines
    case 'l':
            line = GL_LINE;
            glutPostRedisplay();
            break;

    //full
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
    std::cout << "- i :                                                                 " <<std::endl;
    std::cout << "      Zoom in                                                         " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- o :                                                                 " <<std::endl;
    std::cout << "      Zoom out                                                        " <<std::endl;
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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("SOLAR SYSTEM");

    if (argc < 2) {
        cout << "Invalid input." << endl;
        return 0;
    }
    else if(!strcmp(argv[1],"-g")){
            mouvementguide();
            return 0;
        }
    scene = readXML(argv[1],&orbits);
    if(scene == nullptr) return 0;  
    // put GLUT init here
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glClearColor(0,0,0,0) ;
    glClear(GL_COLOR_BUFFER_BIT);
		// put callback registration here
		glutDisplayFunc(renderScene);
		glutReshapeFunc(changeSize);
		glutIdleFunc(renderScene);
        glutKeyboardFunc(keyboard);
        glutSpecialFunc(specialKey);
	

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main loop
    glutMainLoop();
    return 1;
}
