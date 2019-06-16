/*
Integrantes del equipo:

Guzman Garcia Ricardo
Caamaño Hernandez Miguel Angel 
Valerdi Flores Alexia
Medina Lozano Edgar Rafael
*/

#include <stdio.h>
#include <stdlib.h>     //para usar libreria rand
#include <time.h>       //para crear semilla aleatoria con el tiempo
#include <unistd.h>     //para funcion sleep

//definicion de celulas
#define VIVA 'x'
#define MUERTA 32       //espacio en blanco (ASCII)

//definicion de limpiar la pantalla para cada S.O./Compilador
#ifdef _WIN32
    #define CLEAR "cls"
#elif __WIN64
    #define CLEAR "cls"
#elif __APPLE__
    #define CLEAR "clear"
#elif __linux__
    #define CLEAR "clear"
#elif __CYGWIN__
    #define CLEAR "clear"
#else
#   error "Compilador desconocido"
#endif

//prototipos de funciones esenciales
int menu();
void start(int op);
void crearArchivoUltGen(char mat[][50]);
void newGen(char mat[][50], char newMat[][50]);
int contarVecinos(int x, int y, char mat[][50]);
void mostrarMatriz(char matriz[][50]);
void actualizarMatIni(char mat[][50], char newMat[][50]);
void limpiarMatrices(char mat[][50], char newMat[][50]);

void play(char mat[][50], char newMat[][50]);

//prototipos de cada modo
void iniciarMatrizTXT(char mat[][50]);
void iniciarMatrizRandom(char mat[][50]);
void iniciarMatrizUsuario(char mat[][50]);

