#ifndef PACIENTES_H
#define PACIENTES_H
#include <iostream>
#include <conio.h>//Libreria con funciones de control de entrada y salida
#include <ctime>//Libreria para el tiempo
#include <vector>//Libreria para los vectores
#include <chrono>//Libreria que sirve para el tiempo
#include <thread> //Libreria para los hilos
#include <iomanip>//Esta Libreria es para el get time
#include <string>
#include <sstream>
#include <algorithm> 
#include <fstream>
#include <cstdio>  // Incluir la librería para getchar()
#include "Validaciones.h"
#include "Declaraciones.h"

void MenuPrincipalPacientes(){
        int opcion {0};//Declaramos una variable local para el MenuPrincipalPacientes
        std::cout << "=== Gestión de Pacientes ===" << std::endl;
        std::cout << "1. Registrar nuevo paciente" << std::endl;
        std::cout << "2. Mostrar pacientes registrados" << std::endl;
        std::cout << "3. Eliminar pacientes" << std::endl;
        std::cout << "4. Editar pacientes" << std::endl;
        std::cout << "5. Regresar al menu principal del programa. " << std::endl;
        std::cout << "6. Cerrar Programa. " << std::endl;

        opcion = pedirNumeroM();//Aqui hace la llamada a la funcion para que pueda validar el numero
        //Aqui hacemos que un switch case para elegir la opcion y llame a su respectiva funcion
        do{
     
            switch(opcion){
            case 1:RegistrarPacientes();break;
            case 2:MostrarPacientes ();break;
            case 3:EliminarPacientes();break;
            case 4:EditarPacientes();break;
            //case 5:MenuPrincipal();break;
            case 5: std::cout << "Saliendo del programa. ¡Hasta luego!" << std::endl; 
            return ;
            break;
        
            default: std:: cout <<"Elige una opcion del 1 al 6";break;

            }   
        } while (opcion!=5);
}









#endif