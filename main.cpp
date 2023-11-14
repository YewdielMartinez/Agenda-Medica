#include <iostream>
#include <conio.h>//Libreria con funciones de control de entrada y salida
#include <string.h> // Libreria para hacer todas mayusculas
#include <ctime>//Libreria para el tiempo
#include <vector>//Libreria para los vectores
#include <chrono>//Libreria que sirve para el tiempo
#include <thread> //Libreria para los hilos
#include <iomanip>//Esta Libreria es para el get time
#include <string>
#include <sstream>
#include <algorithm> 
#include <fstream>
#include <random>
#include "Doctores.h"
#include "Pacientes.h"
#include "Citas.h"
#include "Declaraciones.h"
#include "Consultorios.h"
#include "Validaciones.h"

void MenuPrincipal();




void MenuPrincipal(){
        int opcion {0};//Declaramos una variable local para el MenuPrincipalPacientes
        std::cout << "=== Hola bienvenido a la gestion de el hospital ===" << std::endl;
        std::cout << "1. Menu de doctores" << std::endl;
        std::cout << "2. Menu de pacientes" << std::endl;
        std::cout << "3. Menu de citas" << std::endl;
        std::cout << "4. Menu de consultorios" << std::endl;
        std::cout << "5. Cerrar Programa. " << std::endl;

        opcion = pedirNumeroMM();//Aqui hace la llamada a la funcion para que pueda validar el numero
        //Aqui hacemos que un switch case para elegir la opcion y llame a su respectiva funcion
        do{
     
            switch(opcion){
            case 1:MenuPrincipalDoctores();
            LimpiarPantalla();
            break;
            case 2:MenuPrincipalPacientes ();
            LimpiarPantalla();
            break;
            case 3:MenuPrincipalCitas();
            LimpiarPantalla();
            break;
            case 4:MenuPrincipalConsultorios();
            LimpiarPantalla();
            break;
            case 5: std::cout << "Saliendo del programa. ¡Hasta luego!" << std::endl; 
            cerrarPrograma();
            break;
        
            default: std:: cout <<"Elige una opcion del 1 al 5";break;

            }   
        } while (opcion!=5);

}
int main (){
        
    MenuPrincipal();
    return 0;

}
