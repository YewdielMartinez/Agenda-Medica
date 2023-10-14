#ifndef DOCTORES_H
#define DOCTORES_H
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
#include <cstdio>  // Incluir la librería para getchar()
#include "Validaciones.h"

//#include "MenuPrincipal.h"
//Declaracion de funciones

void RegistrarDoctor();
void MostrarDoctores();
void EliminarDoctor();
void EditarDoctor();
void MenuPrincipalDoctores();
struct Doctor {
std::string Nombre_Doctor;
std::string Especialidad;
std::tm Horario_Entrada;
std::tm Horario_Salida;

};
bool EsperarEnterParaContinuar() {
    std::cout << "Presiona enter para seguir...";
    char c = getchar(); // Leer un carácter, incluyendo el Enter
    return c == '\n'; // Verificar si el carácter es Enter
}

std::vector<Doctor> agendadoctores;
void MenuPrincipalDoctores(){
        int opcion {0};
        std::cout << "=== Gestión de Doctores ===" << std::endl;
        std::cout << "1. Registrar nuevo doctor" << std::endl;
        std::cout << "2. Mostrar doctores registrados" << std::endl;
        std::cout << "3. Eliminar doctor" << std::endl;
        std::cout << "4. Editar doctor" << std::endl;
        std::cout << "5. Regresar al menu principal del programa. " << std::endl;
        std::cout << "6. Cerrar Programa. " << std::endl;

        opcion = pedirNumeroM();//Aqui hace la llamada a la funcion para que pueda validar el numero

        do{
     
            switch(opcion){
            case 1:RegistrarDoctor();break;
            case 2:MostrarDoctores ();break;
            case 3:EliminarDoctor();break;
            case 4:EditarDoctor();break;
            //case 5:MenuPrincipal();break;
            case 5: std::cout << "Saliendo del programa. ¡Hasta luego!" << std::endl; 
            return ;
            break;
        
            default: std:: cout <<"Elige una opcion del 1 al 6";break;

            }   
        } while (opcion!=5);
}


void RegistrarDoctor()
{
  Doctor doctorr;
    //Que la estructura se guarde en doctor
   //Aqui ingresamos el nombre del doctor
    std::cout << "Ingrese el nombre del doctor: "<<std::endl;
    std::cin.ignore();
    doctorr.Nombre_Doctor = ValidarPalabra("Por Favor Ingresar el nombre");//Aqui validamos que el nombre del doctor sea palabra y no ponga numero
    while(doctorr.Nombre_Doctor.empty()){
            std::cout << "No puede dejar el espacio vacio" <<std::endl;
            std::cin.ignore();
            std::getline(std::cin ,doctorr.Nombre_Doctor);
        }
    //Aqui Ingresamos la especialidad del doctor
    std::cout << "Ingrese la especialidad del doctor: "<<std::endl;
    std::cin.ignore();
    doctorr.Especialidad = ValidarPalabra("Favor de ingresar la especialidad");//aqui validamos que la especialidad no vayan numeros
    while(doctorr.Especialidad.empty()){
            std::cout << "No puede dejar el espacio vacio"<<std::endl;
            
            doctorr.Especialidad = ValidarPalabra("Volver a ingresar");
        }
    // Solicitar y validar el horario de entrada del doctor
    std::cout << "Ingrese el horario de entrada del doctor (HH:MM): ";
    std::string Horario_EntradaStr;
    std::getline(std::cin,Horario_EntradaStr);
    while (!ValidarHora(Horario_EntradaStr)) {
        std::cout << "Formato de hora incorrecto. Use HH:MM: ";
        std::getline(std::cin, Horario_EntradaStr);
    }

    // Solicitar y validar el horario de salida del doctor
    std::cout << "Ingrese el horario de salida del doctor (HH:MM): ";
    std::string Horario_SalidaStr;
    std::getline(std::cin, Horario_SalidaStr);
    while (!ValidarHora(Horario_SalidaStr)) {
        std::cout << "Formato de hora incorrecto. Use HH:MM: ";
        std::getline(std::cin, Horario_SalidaStr);
        // Agregar el nuevo doctor al vector de doctores
        agendadoctores.push_back(doctorr);
    
        std::cout << "Doctor registrado exitosamente." << std::endl;
    }
   

    if (EsperarEnterParaContinuar()) {
        MenuPrincipalDoctores();
    }

}
void MostrarDoctores(){
//ajsa
}
void EliminarDoctor(){

}
void EditarDoctor(){
    
}






#endif