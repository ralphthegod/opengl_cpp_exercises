#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>
#include <vector>

float angleX = 0.0f;
float angleY = 0.0f;
int lastMouseX, lastMouseY;
bool isMousePressed = false;

struct Vertex {
    float x, y, z;
};

struct Face {
    Vertex v1, v2, v3, v4;
    Vertex normal;
};

float function(float x, float z) {
    // 0 singularity
    if (x == 0 && z == 0) return 0;
    return (2 * sin(sqrt(x * x + z * z))) / sqrt(x * x + z * z);
}

Vertex getNormal(const Face& face) {
    Vertex normal = {0.0f, 0.0f, 0.0f};
    std::vector<Vertex> vertices = {face.v1, face.v2, face.v3, face.v4};
    for (size_t i = 0; i < vertices.size(); ++i) {
        const Vertex& current = vertices[i];
        const Vertex& next = vertices[(i + 1) % vertices.size()];
        normal.x += (current.y - next.y) * (current.z + next.z);
        normal.y += (current.z - next.z) * (current.x + next.x);
        normal.z += (current.x - next.x) * (current.y + next.y);
    }

    float length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    if (length != 0.0f) {
        normal.x /= length;
        normal.y /= length;
        normal.z /= length;
    }

    return normal;
}

void generateNormals(std::vector<Face>& faces) {
    for (Face& face : faces) {
        face.normal = getNormal(face);
    }
}


std::vector<Vertex> generateVertices(float range, float step) {
    std::vector<Vertex> vertices;
    for (float x = -range; x <= range; x += step) {
        for (float z = -range; z <= range; z += step) {
            vertices.push_back({x, function(x, z), z});
        }
    }
    return vertices;
}

std::vector<Face> generateFaces(std::vector<Vertex>& vertices, int gridSize) {
    std::vector<Face> faces;
    for (int i = 0; i < gridSize - 1; ++i) {
        for (int j = 0; j < gridSize - 1; ++j) {
            int index = i * gridSize + j;
            faces.push_back({
                vertices[index],
                vertices[index + 1],
                vertices[index + gridSize + 1],
                vertices[index + gridSize]
            });
        }
    }
    return faces;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);
    glTranslatef(0.0f, 0.0f, -20.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float camX = sin(angleY * M_PI / 180.0) * 10.0;
    float camY = sin(angleX * M_PI / 180.0) * 10.0;
    float camZ = cos(angleY * M_PI / 180.0) * 10.0;

    gluLookAt(camX, camY, camZ, 
              0, 0, 0,          
              0, 1, 0);  

    float range = 10.0f;
    float step = 0.1f;
    
    int gridSize = (int)(2 * range / step);

    std::vector<Vertex> vertices = generateVertices(range, step);
    std::vector<Face> faces = generateFaces(vertices, gridSize);
    generateNormals(faces);

    glColor3f(1.0f, 1.0f, 1.0f);
    
    for (const Face& face : faces) {
        glBegin(GL_QUADS);
            glNormal3f(face.normal.x, face.normal.y, face.normal.z);
            glVertex3f(face.v1.x, face.v1.y, face.v1.z);
            glVertex3f(face.v2.x, face.v2.y, face.v2.z);
            glVertex3f(face.v3.x, face.v3.y, face.v3.z);
            glVertex3f(face.v4.x, face.v4.y, face.v4.z);
        glEnd();
    }

    glFlush();
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("funzione");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMotionFunc(motion);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glutMainLoop();
    return 0;
}
