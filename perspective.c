// Perspectiva
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#include <unistd.h>

#define LINE_WIDTH 3

void init();
void display();
void intersection(int xp, int yp, int zp, int xo, int yo, int zo, int Z_DIST, int vertex_index, float* vertices_vector);
void drawFace(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y, float p4x, float p4y, int f_id);
void connectFaces(float* vertices);
void scene1();
void scene2();
void scene3();
void scene4();
void scene5();

float vertices[8][3] = {
                        {50, 50, 0},
                        {100, 50, 0},
                        {100, 100, 0},
                        {50, 100, 0}, // ---
                        {50, 100, 50},
                        {100, 100, 50},
                        {100, 50, 50},
                        {50, 50, 50}
                    };

float observer[3] = {120, 340, 400};

int main(int argc, char** argv) {
    glutInit(&argc, argv);                              
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (512, 512);           
    glutInitWindowPosition (100, 100);                  
    glutCreateWindow ("Perspectiva");  
    init();
    glutDisplayFunc(display);
    glutMainLoop();   
}

void init() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glOrtho (0, 512, 0, 512, -1 ,1);

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 3; j++)
        vertices[i][j] *= 3.2;

}

void display(){
    // Apresenta, em loop, algumas animações para
    // demonstrar o funcionamento da projeção em
    // perspectiva
    while (1) {
        scene1();
        scene2();
        scene3();
        scene4();
        scene5();
    }
}

// Funções relacionadas ao cálculo e à renderização do cubo

// A função intersection calcula o ponto de interseção da linha formada pelo ponto P (xp, yp, zp) e o
// ponto O (), ponto do observador, com o plano (x, y, Z_DIST), um plano paralelo ao plano z que dista Z_DIST unidades
// da origem. Calculado esse ponto de interseção, suas coordenadas são adicionadas ao vetor de vértices pas-
// sado como parâmetro, utilizando o valor de vertex_index para calcular a posição em que guardar no vetor.
void intersection(int xp, int yp, int zp, int xo, int yo, int zo, int Z_DIST, int vertex_index, float* vertices_vector) {    
    // Calcula o ponto de interseção
    float t = (((float) Z_DIST - (float) zp)/((float) zo - (float) zp));
    float x = xp + t * (xo - xp);
    float y = yp + t * (yo - yp);

    // Adiciona o ponto de interseção ao vetor especificado
    vertices_vector[vertex_index*2] = x;
    vertices_vector[vertex_index*2+1] = y;
}

// Desenha uma face do cubo, formada pelos pontos passados como parâmetro: p1, p2, p3 e p4
void drawFace(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y, float p4x, float p4y, int f_id) {
    glBegin(GL_LINE_LOOP);
    // Define a cor azul se f_id = 1, ou verde, do contrário
    glColor3f(f_id ? 0.0 : 0.0, f_id ? 0.0 : 1.0, f_id ? 1.0 : 0.0);

    // Desenha as linhas, formando a face
    glVertex2f(p1x, p1y);
    glVertex2f(p2x, p2y);
    glVertex2f(p3x, p3y);
    glVertex2f(p4x, p4y);
    glEnd();
}

// Desenha 4 arestas conectando duas faces, previamente desenhadas pela função drawFace
void connectFaces(float* vertices) {
    glColor3f(1.0, 1.0, 0.0);

    glBegin(GL_LINES);
    glVertex2f(vertices[0], vertices[1]);
    glVertex2f(vertices[14], vertices[15]);

    glVertex2f(vertices[2], vertices[3]);
    glVertex2f(vertices[12], vertices[13]);

    glVertex2f(vertices[4], vertices[5]);
    glVertex2f(vertices[10], vertices[11]);

    glVertex2f(vertices[6], vertices[7]);
    glVertex2f(vertices[8], vertices[9]);
    glEnd();
}

// Funções de cena

void scene1() {
    // Esqueleto do cubo
    // Observador se movendo para a direita
    for (int k = 1; k <= 300; k++) {
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f (1.0, 1.0, 1.0);

        // Recalcula os vértices em relação à perspectiva
        float persp_vertices[16];
        for (int i = 0; i < 8; i++)
            intersection(vertices[i][0], vertices[i][1], vertices[i][2], k, observer[1], observer[2], 30, i, persp_vertices);

        glLineWidth(LINE_WIDTH);
        

        // Desenha uma face
        drawFace(persp_vertices[0],
                persp_vertices[1],
                persp_vertices[2], 
                persp_vertices[3], 
                persp_vertices[4], 
                persp_vertices[5], 
                persp_vertices[6], 
                persp_vertices[7],
                1
            );

        // "Conecta" as duas faces, criando efetivamente o cubo
        connectFaces(persp_vertices);

        // Desenha outra face
        drawFace(persp_vertices[8],
                persp_vertices[9],
                persp_vertices[10], 
                persp_vertices[11], 
                persp_vertices[12], 
                persp_vertices[13], 
                persp_vertices[14], 
                persp_vertices[15],
                0
            );

        glFlush();
        usleep(10000);
    }
}

void scene2() {
    // Esqueleto do cubo
    // Observador se movendo para a esquerda
    for (int k = 300; k > 0; k--) {
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f (1.0, 1.0, 1.0);

        // Recalcula os vértices em relação à perspectiva
        float persp_vertices[16];
        for (int i = 0; i < 8; i++)
            intersection(vertices[i][0], vertices[i][1], vertices[i][2], k, observer[1], observer[2], 30, i, persp_vertices);

        glLineWidth(LINE_WIDTH);
        

        // Desenha uma face
        drawFace(persp_vertices[0],
                persp_vertices[1],
                persp_vertices[2], 
                persp_vertices[3], 
                persp_vertices[4], 
                persp_vertices[5], 
                persp_vertices[6], 
                persp_vertices[7],
                1
            );

        // "Conecta" as duas faces, criando efetivamente o cubo
        connectFaces(persp_vertices);

        // Desenha outra face
        drawFace(persp_vertices[8],
                persp_vertices[9],
                persp_vertices[10], 
                persp_vertices[11], 
                persp_vertices[12], 
                persp_vertices[13], 
                persp_vertices[14], 
                persp_vertices[15],
                0
            );

        glFlush();
        usleep(10000);
    }
}

void scene3() {
     // Esqueleto do cubo
    // Observador se movendo para a esquerda
    for (int k = 1; k <= 300; k++) {
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f (1.0, 1.0, 1.0);

        // Recalcula os vértices em relação à perspectiva
        float persp_vertices[16];
        for (int i = 0; i < 8; i++)
            intersection(vertices[i][0], vertices[i][1], vertices[i][2], observer[0], k, observer[2], 30, i, persp_vertices);

        glLineWidth(LINE_WIDTH);
        

        // Desenha uma face
        drawFace(persp_vertices[0],
                persp_vertices[1],
                persp_vertices[2], 
                persp_vertices[3], 
                persp_vertices[4], 
                persp_vertices[5], 
                persp_vertices[6], 
                persp_vertices[7],
                1
            );

        // "Conecta" as duas faces, criando efetivamente o cubo
        connectFaces(persp_vertices);

        // Desenha outra face
        drawFace(persp_vertices[8],
                persp_vertices[9],
                persp_vertices[10], 
                persp_vertices[11], 
                persp_vertices[12], 
                persp_vertices[13], 
                persp_vertices[14], 
                persp_vertices[15],
                0
            );

        glFlush();
        usleep(10000);
    }
}

void scene4() {
     // Esqueleto do cubo
    // Observador se movendo para a esquerda
    for (int k = 300; k > 0; k--) {
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f (1.0, 1.0, 1.0);

        // Recalcula os vértices em relação à perspectiva
        float persp_vertices[16];
        for (int i = 0; i < 8; i++)
            intersection(vertices[i][0], vertices[i][1], vertices[i][2], observer[0], k, observer[2], 30, i, persp_vertices);

        glLineWidth(LINE_WIDTH);
        

        // Desenha uma face
        drawFace(persp_vertices[0],
                persp_vertices[1],
                persp_vertices[2], 
                persp_vertices[3], 
                persp_vertices[4], 
                persp_vertices[5], 
                persp_vertices[6], 
                persp_vertices[7],
                1
            );

        // "Conecta" as duas faces, criando efetivamente o cubo
        connectFaces(persp_vertices);

        // Desenha outra face
        drawFace(persp_vertices[8],
                persp_vertices[9],
                persp_vertices[10], 
                persp_vertices[11], 
                persp_vertices[12], 
                persp_vertices[13], 
                persp_vertices[14], 
                persp_vertices[15],
                0
            );

        glFlush();
        usleep(10000);
    }
}

void scene5() {
     // Esqueleto do cubo
    // Observador se movendo para a esquerda
    for (int k = 1; k <= 300; k++) {
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f (1.0, 1.0, 1.0);

        // Recalcula os vértices em relação à perspectiva
        float persp_vertices[16];
        for (int i = 0; i < 8; i++)
            intersection(vertices[i][0], vertices[i][1], vertices[i][2], k, k*1.1, observer[2], 30, i, persp_vertices);

        glLineWidth(LINE_WIDTH);
        

        // Desenha uma face
        drawFace(persp_vertices[0],
                persp_vertices[1],
                persp_vertices[2], 
                persp_vertices[3], 
                persp_vertices[4], 
                persp_vertices[5], 
                persp_vertices[6], 
                persp_vertices[7],
                1
            );

        // "Conecta" as duas faces, criando efetivamente o cubo
        connectFaces(persp_vertices);

        // Desenha outra face
        drawFace(persp_vertices[8],
                persp_vertices[9],
                persp_vertices[10], 
                persp_vertices[11], 
                persp_vertices[12], 
                persp_vertices[13], 
                persp_vertices[14], 
                persp_vertices[15],
                0
            );

        glFlush();
        usleep(10000);
    }
}