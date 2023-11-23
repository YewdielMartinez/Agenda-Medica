#ifndef CONSULTORIOS_H
#define CONSULTORIOS_H
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
#include "Validaciones.h"
#include "Funcionesarchivos.h"
void MenuPrincipalConsultorios();
void RegistrarConsultorios();
void MenuPrincipal();
void EditarConsultorios();
void EliminarConsultorios();
void MostrarConsultorios();
void AsignarConsultorios();
void CargarConsultorios();
void GuardarConsultorios();
struct Consultorio {
    int NumeroConsultorio;
    
};



void MenuPrincipalConsultorios(){
        int opcion {0};//Declaramos una variable local para el MenuPrincipalPacientes
        std::cout << "=== Gestión de Consultorios ===" << std::endl;
        std::cout << "1. Registrar Nuevo Consultorio" << std::endl;
        std::cout << "2. Asignar Consultorio a un Doctor" << std::endl;
        std::cout << "3. Editar Consultorio" << std::endl;
        std::cout << "4. Eliminar Consultorio" << std::endl;
        std::cout << "5. Mostrar Consultorios" << std::endl;
        std::cout << "6. Regresar al menu principal del programa. " << std::endl;
        std::cout << "7. Cerrar Programa. " << std::endl;

        opcion = pedirNumeroMC();//Aqui hace la llamada a la funcion para que pueda validar el numero
        //Aqui hacemos que un switch case para elegir la opcion y llame a su respectiva funcion
        do{
     
            switch(opcion){
            case 1:RegistrarConsultorios();break;
            case 2:AsignarConsultorios ();break;
            case 3:EditarConsultorios();break;
            case 4:EliminarConsultorios();break;
            case 5:MostrarConsultorios();break;
            case 6:MenuPrincipal();break;
            case 7: std::cout << "Saliendo del programa. ¡Hasta luego!" << std::endl; 
            cerrarPrograma();
            break;
        
            default: std:: cout <<"Elige una opcion del 1 al 7";break;

            }   
        } while (opcion!=7);
}
std::vector<Consultorio> agendaconsultorios;




void RegistrarConsultorios() {
    CargarConsultorios();  // Cargar consultorios existentes

    Consultorio consultorio;
    std::cout << "Ingrese el número del consultorio: ";
    consultorio.NumeroConsultorio = pedirNumeroM();

    auto it = std::find_if(agendaconsultorios.begin(), agendaconsultorios.end(),
                           [&consultorio](const Consultorio& c) {
                               return c.NumeroConsultorio == consultorio.NumeroConsultorio;
                           });

    if (it != agendaconsultorios.end()) {
        std::cout << "Número de consultorio ya en uso. Intente con otro número." << std::endl;
        RegistrarConsultorios();
        return;
    }

    agendaconsultorios.push_back(consultorio);
    std::cout << "Consultorio registrado correctamente." << std::endl;

    // Guardar los consultorios actualizados
    GuardarConsultorios();

    if (validarRespuesta()) {
        MenuPrincipalConsultorios();
    } else {
        RegistrarConsultorios();
    }
}


void EditarConsultorios() {
    CargarConsultorios();  // Cargar consultorios existentes

    int numeroConsultorio;
    std::cout << "Ingrese el número del consultorio que desea editar: ";
    numeroConsultorio = pedirNumeroM();

    auto it = std::find_if(agendaconsultorios.begin(), agendaconsultorios.end(),
                           [&numeroConsultorio](const Consultorio& c) {
                               return c.NumeroConsultorio == numeroConsultorio;
                           });

    if (it != agendaconsultorios.end()) {
        // Puedes editar otros campos si es necesario
        std::cout << "Consultorio editado correctamente." << std::endl;

        // Guardar los consultorios actualizados
        GuardarConsultorios();
    } else {
        std::cout << "Consultorio no encontrado. No se puede editar." << std::endl;
    }

    if (validarRespuesta()) {
        MenuPrincipalConsultorios();
    } else {
        EditarConsultorios();
    }
}

void EliminarConsultorios() {
    CargarConsultorios();  // Cargar consultorios existentes

    int numeroConsultorio;
    std::cout << "Ingrese el número del consultorio que desea eliminar: ";
    numeroConsultorio = pedirNumeroM();

    auto it = std::find_if(agendaconsultorios.begin(), agendaconsultorios.end(),
                           [&numeroConsultorio](const Consultorio& c) {
                               return c.NumeroConsultorio == numeroConsultorio;
                           });

    if (it != agendaconsultorios.end()) {
        agendaconsultorios.erase(it);
        std::cout << "Consultorio eliminado correctamente." << std::endl;

        // Guardar los consultorios actualizados
        GuardarConsultorios();
    } else {
        std::cout << "Consultorio no encontrado. No se puede eliminar." << std::endl;
    }

    if (validarRespuesta()) {
        MenuPrincipalConsultorios();
    } else {
        EliminarConsultorios();
    }
}

void MostrarConsultorios() {
    CargarConsultorios();  // Cargar consultorios existentes

    if (agendaconsultorios.empty()) {
        std::cout << "No hay consultorios registrados." << std::endl;
        MenuPrincipalConsultorios();
    } else {
        std::cout << "=== Lista de Consultorios Registrados ===" << std::endl;
        for (const auto& consultorio : agendaconsultorios) {
            std::cout << "Número de Consultorio: " << consultorio.NumeroConsultorio << std::endl;
            std::cout << "------------------------------------" << std::endl;
        }
        MenuPrincipalConsultorios();
    }

    if (validarRespuesta()) {
        MenuPrincipalConsultorios();
    } else {
        MostrarConsultorios();
    }
}

#endif 