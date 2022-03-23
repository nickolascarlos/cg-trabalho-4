// Perspectiva
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#include <unistd.h>

#define LINE_WIDTH 3

void init();
void display();
void intersection(int xp, int yp, int zp, int plane_id, int vertex_index, float* vertices_vector);
void drawObject(float* vertices_projection);

float vertices[10][3] = {
                        {50, 50, 0},
                        {50, 100, 0},
                        {75, 100, 0},
                        {100, 100, 0},
                        {100, 50, 0}, // ---
                        {50, 50, 200},
                        {50, 100, 200},
                        {75, 125, 200},
                        {100, 100, 200},
                        {100, 50, 200}
                    };

int main(int argc, char** argv) {
    glutInit(&argc, argv);                              
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (512, 512);           
    glutInitWindowPosition (100, 100);                  
    glutCreateWindow ("Projecao Paralela");  
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}

void init() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glOrtho (0, 512, 0, 512, -1 ,1);

  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 3; j++)
        vertices[i][j] *= 2;
}

void display(){

    while(1)
    for (int plane = 0; plane <= 2; plane++) {
        // Vetor para guardar os pontos da projeção
        float vertices_projection[10*2];
        for (int i = 0; i < 10; i++)
            intersection(vertices[i][0], vertices[i][1], vertices[i][2], plane, i, vertices_projection);
        
        glColor3f(1.0, 1.0, 1.0);

        // glBegin(GL_POINTS);
        //     for (int i = 0; i < 10; i++) {
        //         glVertex2f(vertices_projection[i*2], vertices_projection[i*2+1]);
        //         printf("(%f, %f)\n", vertices_projection[i*2], vertices_projection[i*2+1]);
        //     }
        // glEnd();

        // glFlush();
        // break;

        drawObject(vertices_projection);
    
        glFlush();
        
        usleep(1000000);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    
}

// Funções relacionadas ao cálculo e à renderização

// Essa função calcula a interseção da linha dos vértices com o plano especificado por plane_id
// plane_id: 0 = Z, 1 = X, 2 = Y
void intersection(int xp, int yp, int zp, int plane_id, int vertex_index, float* vertices_vector) {    
    
    // Coordenadas do ponto de interseção com o plano especficado
    float xp_, yp_;

    // Calcula o ponto de interseção
    switch (plane_id) {
        case 0:
            // Interseção com o plano Z
            xp_ = xp;
            yp_ = yp;
        break;

        case 1:
            // Interseção com o plano X
            xp_ = yp;
            yp_ = zp + 10; // Além da transformação necessária, "levanta" o vértice em 10 unidades
        break;

        case 2:
            // Interseção com o plano Y
            xp_ = xp;
            yp_ = zp + 10; // Além da transformação necessária, "levanta" o vértice em 10 unidades
        break;
    }

    // Adiciona o ponto de interseção ao vetor especificado
    vertices_vector[vertex_index*2] = xp_;
    vertices_vector[vertex_index*2+1] = yp_;
}

// Desenha o objeto tri-dimensional a partir dos pontos recalculados de acordo com a perspectiva
void drawObject(float* vertices_projection) {
    glLineWidth(3);

    glBegin(GL_LINE_LOOP);
        glVertex2f(vertices_projection[0], vertices_projection[1]);
        glVertex2f(vertices_projection[2], vertices_projection[3]);
        glVertex2f(vertices_projection[4], vertices_projection[5]);
        glVertex2f(vertices_projection[6], vertices_projection[7]);
        glVertex2f(vertices_projection[8], vertices_projection[9]);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(vertices_projection[0], vertices_projection[1]);
        glVertex2f(vertices_projection[10], vertices_projection[11]);

        glVertex2f(vertices_projection[2], vertices_projection[3]);
        glVertex2f(vertices_projection[12], vertices_projection[13]);

        glVertex2f(vertices_projection[4], vertices_projection[5]);
        glVertex2f(vertices_projection[14], vertices_projection[15]);

        glVertex2f(vertices_projection[6], vertices_projection[5]);
        glVertex2f(vertices_projection[16], vertices_projection[17]);

        glVertex2f(vertices_projection[8], vertices_projection[5]);
        glVertex2f(vertices_projection[18], vertices_projection[19]);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(vertices_projection[10], vertices_projection[11]);
        glVertex2f(vertices_projection[12], vertices_projection[13]);
        glVertex2f(vertices_projection[14], vertices_projection[15]);
        glVertex2f(vertices_projection[16], vertices_projection[17]);
        glVertex2f(vertices_projection[18], vertices_projection[19]);
    glEnd();
}