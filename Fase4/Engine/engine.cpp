#include <stdlib.h>
#include "tinyxml2.h"
#include "engine.h"
#include "Point.h"
#include "Texture.h"
#include "geoTransforms.h"
#include "Transformations.h"
#include "Scene.h"


#define POINT 1
#define DIRECTIONAL 2

#define DIFFUSE 3
#define AMBIENT 4
#define SPECULAR 5
#define EMISSION 6

using namespace std;
using namespace tinyxml2;

//vetor dos grupos de cada respetivo astro
vector<geoTransforms*> astros;


int readFile(string filename, vector<Point*> *points,vector<Point*> *normalList, vector<float> *textureList){
	int index, j;
	string line, token;
	ifstream file(filename);
	vector<float>tokens;

	if (!file.is_open()){
		cout << "Unable to open file: " << filename << "." << endl; return -1;
	}else{
		index = 0;
        getline(file, line);
        int numVertex = atoi(line.c_str());
        for(int i=0; i < numVertex; i++){
            getline(file,line);
            stringstream ss(line);
            j = 0;

            while(j < 3 && getline(ss,token,',')) {
                tokens.push_back(stof(token));
                j++;
            }
            Point *p = new Point(tokens[index++],tokens[index++],tokens[index++]);
            points->push_back(p);
        }

        index = 0;
        getline(file, line);
        int numNormals = atoi(line.c_str());
        for(int i=0; i < numNormals; i++){
            getline(file,line);
            stringstream ss(line);
            j = 0;

            while(j < 3 && getline(ss,token,',')) {
                tokens.push_back(stof(token));
                j++;
            }
            Point *p = new Point(tokens[index++],tokens[index++],tokens[index++]);
            normalList->push_back(p);
        }

        index = 0;
        getline(file, line);
        int numTexture = atoi(line.c_str());
        for(int i=0; i < numTexture; i++){
            getline(file,line);
            stringstream ss(line);
            j = 0;

            while(j < 2 && getline(ss,token,',')) {
                j++;
                textureList->push_back(stof(token));
            }
		}
	//	obj.popPoints();
		file.close();
	}
	return 0;
}


Scene* loadXMLfile(string filename) {
    Scene *scene = nullptr;
    XMLDocument xmlDoc;
    XMLNode *pRoot;
    XMLElement *pElement;
    string fileDir = "../files/" + filename;
    XMLError eResult = xmlDoc.LoadFile(fileDir.c_str());
    
    if (eResult == XML_SUCCESS){
        geoTransforms *group = new geoTransforms();
        scene = new Scene(group);

        pRoot = xmlDoc.FirstChild();
        if (pRoot != nullptr)
        {
            pElement = pRoot->FirstChildElement("lights");
            if (pElement)
            {
                pElement->FirstChildElement();
                readLights(scene, pElement);
            }
            pElement = pRoot->FirstChildElement("group");
            readGroup(scene, group, pElement);
        }
    }
    else{
        cout << "Unable to open file: " << filename << "." << endl;
    }
    return scene;
}


void readTranslate(geoTransforms *group, XMLElement *element){
    float x=0, y=0, z=0, time = 0;
    vector<Point*> cPoints;
    Transformations *t;

    if (element->Attribute("time")){

        bool deriv = false;
        if (element->Attribute("derivative"))
            deriv = (stoi(element->Attribute("derivative"))== 1) ? true : false;
        time = stof(element->Attribute("time"));
        time = 1 / (time * 1000);
        element = element->FirstChildElement("point");

        while (element != nullptr){
            x = stof(element->Attribute("X"));
            y = stof(element->Attribute("Y"));
            z = stof(element->Attribute("Z"));

            Point *p = new Point(x,y,z);
            cPoints.push_back(p);

            element = element->NextSiblingElement("point");
        }

        t = new Transformations(time,cPoints,deriv,"translateTime");
        group->addTransformations(t);

    }else{

        if(element->Attribute("X"))
            x = stof(element->Attribute("X"));

        if(element->Attribute("Y"))
            y = stof(element->Attribute("Y"));

        if(element->Attribute("Z"))
            z = stof(element->Attribute("Z"));

        t = new Transformations("translate",0.0f,x,y,z);
        group->addTransformations(t);
    }
}

void readModels (geoTransforms *group, XMLElement *element) {
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
            vector<Point*> normal;
            vector<float> texture;
            readFile(fileDir, &points,&normal, &texture);
            
            if (points.size()) {
                Shape *shape;
                if(element->Attribute("texture"))
                    shape  = new Shape(element->Attribute("texture"),points, normal, texture);
                else
                    shape = new Shape(points, normal, texture);

                readTexture(shape, element);
                shapes.push_back(shape);
            }
        }
        element = element->NextSiblingElement("model");
    }

    if (shapes.size())
        group->setShapes(shapes);
}

void readLights (Scene *scene, XMLElement *pElement)
{
    if ((pElement = pElement->FirstChildElement("light")) == nullptr){
        cout << "XML error: No lights available!" << endl;
        return;
    }

    while (pElement != nullptr)
    {
        if (pElement->Attribute("type"))
        {
            int type = -1;
            float *info = (float *) calloc (16, sizeof(float));
            vector<int> attributes;

            if (strcmp(pElement->Attribute("type"), "POINT") == 0){
                type = POINT;
                info[3] = 1.0f;
            }
            else if (strcmp(pElement->Attribute("type"), "DIRECTIONAL") == 0){
                type = DIRECTIONAL;
                info[3] = 0.0f;
            }

            // LIGHT POSITION
            if (pElement->Attribute("posX")) {
                info[0] = stof(pElement->Attribute("posX"));
            }
            if (pElement->Attribute("posY")) {
                info[1] = stof(pElement->Attribute("posY"));
            }
            if (pElement->Attribute("posZ")) {
                info[2] = stof(pElement->Attribute("posZ"));
            }

            // DIFFUSE LIGHT
            if (pElement->Attribute("diffR") || pElement->Attribute("diffG") || pElement->Attribute("diffB"))
            {
                attributes.push_back(DIFFUSE);
                if (pElement->Attribute("diffR"))
                info[4] = stof(pElement->Attribute("diffR"));
                if (pElement->Attribute("diffG"))
                    info[5] = stof(pElement->Attribute("diffG"));
                if (pElement->Attribute("diffB"))
                    info[6] = stof(pElement->Attribute("diffB"));
                info[7] = 1.0f;
            }

            // AMBIENT LIGHT
            if (pElement->Attribute("ambR") || pElement->Attribute("ambG") || pElement->Attribute("ambB"))
            {
                attributes.push_back(AMBIENT);
                if (pElement->Attribute("ambR"))
                    info[8] = stof(pElement->Attribute("ambR"));
                if (pElement->Attribute("ambG"))
                    info[9] = stof(pElement->Attribute("ambG"));
                if (pElement->Attribute("ambB"))
                    info[10] = stof(pElement->Attribute("ambB"));
                info[11] = 1.0f;
            }

            // SPECULAR LIGHT
            if (pElement->Attribute("specR") || pElement->Attribute("specG") || pElement->Attribute("specB"))
            {
                attributes.push_back(SPECULAR);
                if (pElement->Attribute("specR"))
                    info[12] = stof(pElement->Attribute("specR"));
                if (pElement->Attribute("specG"))
                    info[13] = stof(pElement->Attribute("specG"));
                if (pElement->Attribute("specB"))
                    info[14] = stof(pElement->Attribute("specB"));
                info[15] = 1.0f;
            }

            if (type != -1)
            {
                Light *light = new Light(info,attributes);
                scene->addLight(light);
            }
            else
                free(info);
        }
         pElement = pElement->NextSiblingElement("light");
    }
}

void readRotate (geoTransforms *group, XMLElement *element){
    float angle = 0, x = 0, y = 0, z = 0;
    string type = "rotation";
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

    t = new Transformations(type,angle,x,y,z);
    group->addTransformations(t);
}

// !!! é a cordenada x no scale que está mal

//função que lê um grupo do ficheiro XML
void readGroup(Scene *scene, geoTransforms *obj ,XMLElement* group){

	XMLElement *element, *innerElement;
	float x, y, z, ang;
	float r1, g1, b1, r2, g2, b2;
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
                t = new Transformations("scale",0.0f,x,y,z);
				obj->addTransformations(t);
		}

		else if (strcmp(element->Value(), "models") == 0){

			innerElement = element->FirstChildElement();

			while (innerElement != nullptr){

				if (strcmp(innerElement->Value(), "model") == 0){
					string file;
					file = innerElement->Attribute("file");
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
		}else if (strcmp(element->Value(), "group") == 0){
    		geoTransforms* child = new geoTransforms();
    		obj->addChild(child);
            readGroup(scene,child,element);
    	}

    	element = element->NextSiblingElement();
	}
}

void readTexture(Shape* shape, XMLElement* element) {
    Transformations* diffuse = NULL;
    Transformations* ambient = NULL;
    Transformations* specular = new Transformations(0, 0, 0);
    Transformations* emission = new Transformations(0, 0, 0);


    // Diffuse
    if(element->Attribute("diffR") || element->Attribute("diffG") || element->Attribute("diffB")) {
        diffuse = new Transformations(0.8f, 0.8f, 0.8f);
        if (element->Attribute("diffR"))
            diffuse->setX(stof(element->Attribute("diffR")));
        if (element->Attribute("diffG"))
            diffuse->setY(stof(element->Attribute("diffG")));
        if (element->Attribute("diffB"))
            diffuse->setZ(stof(element->Attribute("diffB")));
    }

    // Ambient
    if(element->Attribute("ambR") || element->Attribute("ambG") || element->Attribute("ambB")) {
        ambient = new Transformations(0.2f, 0.2f, 0.2f);
        if (element->Attribute("ambR"))
            ambient->setX(stof(element->Attribute("ambR")));
        if (element->Attribute("ambG"))
            ambient->setY(stof(element->Attribute("ambG")));
        if (element->Attribute("ambB"))
            ambient->setZ(stof(element->Attribute("ambB")));
    }


    // Specular
    if(element->Attribute("specR"))
        specular->setX(stof(element->Attribute("specR")));
    if(element->Attribute("specG"))
        specular->setY(stof(element->Attribute("specG")));
    if(element->Attribute("specB"))
        specular->setZ(stof(element->Attribute("specB")));

    // Emission
    if(element->Attribute("emiR"))
        emission->setX(stof(element->Attribute("emiR")));
    if(element->Attribute("emiG"))
        emission->setY(stof(element->Attribute("emiG")));
    if(element->Attribute("emiB"))
        emission->setZ(stof(element->Attribute("emiB")));


    Texture* m = new Texture(diffuse, ambient, specular, emission);
    shape->setParseMat(m);
}

//função que começa a ler o ficheiro XML
Scene* readXML(string filename){
    Scene *scene = nullptr;
	XMLDocument doc;
	string fileDir = "../files/" + filename;
	XMLError eResult = doc.LoadFile(fileDir.c_str());
    XMLNode *pRoot;
    XMLElement *element;

	if (eResult == XML_SUCCESS)
	{
        geoTransforms *group = new geoTransforms();
        scene = new Scene(group);

		pRoot = doc.FirstChild();
		if (pRoot != nullptr)
		{
			element = pRoot->FirstChildElement("ligths");
            if(element){
                element->FirstChildElement();
                readLights(scene, element);

            }
            element = pRoot->FirstChildElement("group");
            readGroup(scene,group,element);
		}
	}else{
        cout << "Unable to open file: " << filename << "." << endl;
    }
    return scene;
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
    float cor[4]={0.2f,0.2f,0.2f,1.0f};

    glPushAttrib(GL_LIGHTING_BIT);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cor);
    glBegin(GL_LINE_LOOP);
    for(Point *p : curvePoints){
        float normal[3] = { -p->getX(),
            -p->getY(),
            -p->getZ()};
        t->normalize(normal);
        glNormal3fv(normal);
        float x = p->getX();
        float y = p->getY();
        float z = p->getZ();
        glVertex3f(x,y,z);
    }
    glEnd();
    glPopAttrib();
}

//é a cordenada z que dá merda
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
        Transformations* diffuse = NULL;
        Transformations* ambient = NULL;
        Transformations* specular = new Transformations(0, 0, 0);
        Transformations* emission = new Transformations(0, 0, 0);
        Texture *m = new Texture(diffuse,ambient,specular,emission);
        m->draw();
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
void drawAndColor(Scene * scene, geoTransforms* obj) {

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

	for (geoTransforms *chi : obj->getChild()) drawAndColor(scene,chi);

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

void renderScene(void){

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();

    gluLookAt(movX, movY, movZ ,
              movX + cos(beta)*sin(alpha), movY + sin(beta), movZ + cos(beta)*cos(alpha),
              0.0f, 1.0f, 0.0f);

    glPolygonMode(GL_FRONT_AND_BACK, line);
    
    scene->applyLights();
    fps();

    //set primitives and colors
	drawAndColor(scene,scene->getMainGroup());


    // End of frame
    glutSwapBuffers();
}

void changeSize(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0) h = 1;

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

void init(){
    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_FILL);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    glEnable(GL_NORMALIZE);
    glEnable(GL_RESCALE_NORMAL);
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
	}else if (readXML(argv[1]) == 0) {
        init();

        scene = readXML(argv[1]);
        if(scene == nullptr) return 0;

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
