/*
Integrantes del equipo:

Guzman Garcia Ricardo
Caamaño Hernandez Miguel Angel
Valerdi Flores Alexia
Medina Lozano Edgar Rafael
*/

#include "juegoHeader.h"

void start(int op)
{
	//creacion de matrices de 50x50
    char matInicial[50][50];
    char matFinal[50][50];
    limpiarMatrices(matInicial, matFinal);

    switch (op)
    {
        case 1: //abrir archivo txt
            iniciarMatrizTXT(matInicial);
            play(matInicial, matFinal);
            break;

        case 2: //el usuario ingresa datos del teclado
            iniciarMatrizUsuario(matInicial);
            play(matInicial, matFinal);
            break;

        case 3: //modo aleatorio
            iniciarMatrizRandom(matInicial);
            play(matInicial, matFinal);
            break;

        case 0: //salir
        	printf("\n\nAdios. :)\n");
        	sleep(1);
            return;

        default:
            printf("\nOpcion incorrecta. Presiona enter para regresar.");
            getchar();
            system(CLEAR);
            break;
    }
}

int menu()
{
    int op;
    printf("\t##### El Juego de la Vida de Conway #####\n\n");
    printf("Seleccione alguna opcion para comenzar una disposicion inicial:\n\n");
    printf("1. Abrir el archivo \"juegoInicial.txt\"\n");
    printf("2. Leer entradas del teclado\n");
    printf("3. Crear una partida aleatoriamente\n");
    printf("0. Cerrar el juego\n");
    printf("> ");
    scanf("%d", &op);
    getchar();

    return op;
}

void play(char mat[][50], char newMat[][50])
{
    int op;
    char opC;

    do
    {
        system(CLEAR);
        mostrarMatriz(mat);

        printf("\nSeleccione un modo de juego:\n");
        printf("1. Hacer el proceso paso a paso\n");
        printf("2. Proceso automatico\n");
        printf("0. Salir\n");
        printf("> ");
        scanf("%d", &op);
        getchar();

        system(CLEAR);
        mostrarMatriz(mat);

        if (op == 1)	//proceso paso a paso
        {
            do
            {
                printf("\n*Presione enter para actualizar a la siguiente generacion*\n");
                printf("*Introduzca cualquier otra tecla para terminar*\n");
                printf("> ");
                opC = getchar();    //entrada del teclado
                system(CLEAR);

                if (opC == '\n')      //si es un enter, sigue con la siguiente gen., si no, se sale
                {
                    newGen(mat, newMat);
                    actualizarMatIni(mat, newMat);
                    mostrarMatriz(mat);
                }
            } while (opC == '\n');
        }
        else if (op == 2)	//proceso automatico
        {
            int cont, i;

            do
            {
                printf("\nIngrese la cantidad de iteraciones a realizar (no mayor a 300): ");
                scanf("%d", &cont);
                getchar();

                if (cont < 0 || cont > 300) //el usuario debe ingresar un numero entre 0 y 300
                {
                    printf("\nValor no valido\n");
                    sleep(1);
                }

                system(CLEAR);
                mostrarMatriz(mat);
            } while (cont <= 0 || cont > 300);

            for (i = 1; i <= cont; ++i)
            {
                system(CLEAR);
                newGen(mat, newMat);
                actualizarMatIni(mat, newMat);
                mostrarMatriz(mat);

                printf("\nIteracion %d de %d\n", i, cont);
                usleep(100000);		//funcion para dormir una decima de segundo
            }
        }
        else if (op == 0)
        {
            system(CLEAR);
        }
        else
        {
            printf("\n*Opcion no valida\n");
            sleep(1);
        }
    } while (op != 0);

    crearArchivoUltGen(mat);    //crea el archivo de la ultima generacion creada
}

void limpiarMatrices(char mat[][50], char newMat[][50])
{
    int i, j;

    //Llena las dos matrices de espacios (celulas muertas)
    for (i = 0; i < 50; ++i)
    {
        for (j = 0; j < 50; ++j)
        {
            mat[i][j] = MUERTA;
            newMat[i][j] = MUERTA;
        }
    }
}

void newGen(char mat[][50], char newMat[][50])
{
    int cont;
    int i, j;

    for (i = 0; i < 50; ++i)
    {
        for (j = 0; j < 50; ++j)
        {
            cont = contarVecinos(i, j, mat);

            if (mat[i][j] == VIVA)
            {
                //la celula vive si hay 2 o 3 celulas vecinas, si no, muere
                if (cont != 2 && cont != 3)
                {
                    newMat[i][j] = MUERTA;
                }
				else //la celula vive y se copia a la nueva matriz
                {
                    newMat[i][j] = VIVA;
                }
            }
			else if (mat[i][j] == MUERTA)
            {
                if (cont == 3) //si la celula muerta tiene 3 vecinas vivas, nace
                {
                    newMat[i][j] = VIVA;
                }
            }
        }
    }
}

int contarVecinos(int x, int y, char mat[][50])
{
    int i, j;
    int xPos, yPos;
    int cont = 0;

    for (i = -1; i <= 1; ++i)
    {
        for (j = -1; j <= 1; ++j)
        {
            xPos = x + i; //xPos y yPos indican la posicion de las celulas vecinas
            yPos = y + j;

            //checa si xPos o yPos son distintos de 'x' y 'y' porque seria la celda en si
            //y si xPos y yPos no se salen de la matriz
            if ((xPos != x || yPos != y) && (xPos != -1 && yPos != -1 && xPos != 50 && yPos != 50))
            {
                //checa si la entrada en la matriz es una celula viva e incrementa contador
                if (mat[xPos][yPos] == VIVA)
                {
                    cont++;
                }
            }
        }
    }
    return cont;
}

void mostrarMatriz(char matriz[][50])
{
    int i, j;

    for (i = 0; i < 50; ++i)
    {
        for (j = 0; j < 50; ++j)
        {
            printf("%c", matriz[i][j]);
        }
        printf("|\n"); //imprime borde derecho
    }
    for (i = 0; i < 50; ++i)
    {
        printf("-"); //imprime borde de abajo
    }
    printf("+"); //esquina
    printf("\n");
}

void actualizarMatIni(char mat[][50], char newMat[][50])
{
    int i, j;

    for (i = 0; i < 50; ++i)	//copia toda la matriz nueva a la matriz inicial
    {
        for (j = 0; j < 50; ++j)
        {
            mat[i][j] = newMat[i][j];
        }
    }
}

void crearArchivoUltGen(char mat[][50])
{
    int i, j;
    FILE *ultimaGen;

    ultimaGen = fopen("ultimaGeneracion.txt", "w"); //lo abre como w (escritura) y reemplaza archivo anterior

    for (i = 0; i < 50; ++i)
    {
        for (j = 0; j < 50; ++j)
        {
            fprintf(ultimaGen, "%c", mat[i][j]);
        }
        fprintf(ultimaGen, "\r\n"); //añade salto de linea
    }

    fclose(ultimaGen);
}



//funciones de cada modo de juego

void iniciarMatrizRandom(char mat[][50])
{
    srand(time(NULL));      //creacion de la semilla
    int posEnX[200], posEnY[200];
    int i;

    //rellena los arreglos con numeros que van de 0 a 49, que representan las coordenadas para 'x' y 'y'
    for (i = 0; i < 200; ++i)
    {
        posEnX[i] = rand() % 50;
        posEnY[i] = rand() % 50;
    }

    //crea las celulas vivas a partir de las coordenadas generadas
    for (i = 0; i < 200; ++i)
    {
        mat[posEnX[i]][posEnY[i]] = VIVA;
    }

}

void iniciarMatrizUsuario(char mat[][50])
{
    int i, j;

    system(CLEAR);
    mostrarMatriz(mat);

    do
    {
        printf("\nIngrese las coordenadas para insertar celulas vivas (fila, columna)\n");
        printf("(Ingrese un numero negativo para terminar)\n");
        
        printf("\ni: ");
        scanf("%d", &i);
        printf("j: ");
        scanf("%d", &j);

        if (i > 49 || j > 49)
        {
            printf("\n*Por favor ingrese numeros entre 0 y 49\n");
            sleep(2);
        }
        else if (i >= 0 && j >= 0 && i < 50 && j < 50) //checa si no se sale de los limites de la matriz
        {
            mat[i][j] = VIVA;
        }

        system(CLEAR);
        mostrarMatriz(mat);

    } while (i >= 0 && j >= 0);
}

void iniciarMatrizTXT(char mat[][50])
{
    int i, j;

    FILE *juegoInicial;

    if ((juegoInicial = fopen("juegoInicial.txt", "r")) == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        sleep(1);
        exit(1);
    }
    else
    {
        printf("\nArchivo abierto con exito.\n");
        sleep(1);
    }

    //Copia lo que hay en el archivo txt adentro de la matriz
    for (i = 0; i < 50 && !feof(juegoInicial); ++i)
        fgets(mat[i], 50, juegoInicial);

    //Reemplaza las celdas basura con espacios (como \n y el \0)
    for (i = 0; i < 50; ++i)
    {
        for (j = 0; j < 50; ++j)
        {
            if (mat[i][j] != VIVA && mat[i][j] != MUERTA)
                mat[i][j] = MUERTA;
        }
    }

    fclose(juegoInicial); //cierra archivo
}
