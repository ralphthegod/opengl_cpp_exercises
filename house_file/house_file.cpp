#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

struct Vertex {
    float x, y, z;
};

struct Face {
    std::vector<int> vertices;
    Vertex normal;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
};

bool showNormals = true;
float angleX = 0.0f;
float angleY = 0.0f;
int lastMouseX, lastMouseY;
bool isMousePressed = false;

Vertex calculateFaceNormal(const Mesh& mesh, const Face& face) {
    Vertex const& v1 = mesh.vertices[face.vertices[0]];
    Vertex const& v2 = mesh.vertices[face.vertices[1]];
    Vertex const& v3 = mesh.vertices[face.vertices[2]];

    Vertex vec1 = {v2.x - v1.x, v2.y - v1.y, v2.z - v1.z};
    Vertex vec2 = {v3.x - v1.x, v3.y - v1.y, v3.z - v1.z};

    Vertex normal = {
        vec1.y * vec2.z - vec1.z * vec2.y,
        vec1.z * vec2.x - vec1.x * vec2.z,
        vec1.x * vec2.y - vec1.y * vec2.x
    };

    float length = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    normal.x /= length;
    normal.y /= length;
    normal.z /= length;

    return normal;
}

Mesh loadOBJ(const std::string& filename) {
    Mesh mesh;
    std::ifstream objFile(filename);
    std::string line;

    if (!objFile.is_open()) {
        std::cerr << "Error" << std::endl;
        return mesh;
    }

    while (std::getline(objFile, line)) {
        std::istringstream lineStream(line);
        std::string lineType;
        lineStream >> lineType;

        if (lineType == "v") {
            Vertex v;
            lineStream >> v.x >> v.y >> v.z;
            mesh.vertices.push_back(v);
        } else if (lineType == "f") {
            Face f;
            std::string vertexIndex;
            while (lineStream >> vertexIndex) {
                size_t slashPos = vertexIndex.find('/');
                if (slashPos != std::string::npos) {
                    vertexIndex = vertexIndex.substr(0, slashPos);
                }
                int index = std::stoi(vertexIndex);
                f.vertices.push_back(index - 1);
            }
            f.normal = calculateFaceNormal(mesh, f);
            mesh.faces.push_back(f);
        }
    }

    objFile.close();

    return mesh;
}

void drawMesh(const Mesh& mesh) {
    
    for (const Face& face : mesh.faces) {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POLYGON);
        glNormal3f(face.normal.x, face.normal.y, face.normal.z);
        for (int vertexIndex : face.vertices) {
            const Vertex& vertex = mesh.vertices[vertexIndex];
            glVertex3f(vertex.x, vertex.y, vertex.z);
        }
        glEnd();
    
        if(showNormals){
            Vertex center = {0.0f, 0.0f, 0.0f};
            for(int vertexIndex : face.vertices)
            {
                center.x += mesh.vertices[vertexIndex].x;
                center.y += mesh.vertices[vertexIndex].y;
                center.z += mesh.vertices[vertexIndex].z;
            }
            center.x /= face.vertices.size();
            center.y /= face.vertices.size();
            center.z /= face.vertices.size();

            Vertex normal = {center.x + face.normal.x * 3, center.y + face.normal.y * 3, center.z + face.normal.z * 3};
            
            glColor3f(1.0, 0.0, 1.0);
            glBegin(GL_LINES);
            glVertex3f(center.x, center.y, center.z);
            glVertex3f(normal.x, normal.y, normal.z);
            glEnd();
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-0.0f, -0.0f, -40.0f);
    glRotatef(45, 1.0, -1.0, 0.0);

    float camX = sin(angleY * M_PI / 180.0) * 10.0;
    float camY = sin(angleX * M_PI / 180.0) * 10.0;
    float camZ = cos(angleY * M_PI / 180.0) * 10.0;

    gluLookAt(camX, camY, camZ, 
              0, 0, 0,          
              0, 1, 0);    

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_FLAT);

    static Mesh houseMesh = loadOBJ("house.obj");

    drawMesh(houseMesh);

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isMousePressed = true;
            lastMouseX = x;
            lastMouseY = y;
        } else {
            isMousePressed = false;
        }
    }
}

void motion(int x, int y) {
    if (isMousePressed) {
        float deltaX = x - lastMouseX;
        float deltaY = y - lastMouseY;

        angleY += deltaX * 0.5f;
        angleX += deltaY * 0.5f;

        if (angleX > 60.0f) angleX = 60.0f;
        if (angleX < -60.0f) angleX = -60.0f;
        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("house");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);


    glutMainLoop();

    return 0;

    return 0;
}
