/*
Integrantes del equipo:

Guzman Garcia Ricardo
Caamaño Hernandez Miguel Angel 
Valerdi Flores Alexia
Medina Lozano Edgar Rafael
*/


#include "juego.h"

int main()
{
    int op;

    do
    {
        op = menu(); //llama el menu y guarda la opcion en 'op'
        start(op);	//llama start mandandole la opcion seleccionada
    } while (op != 0);

    return 0;
}
