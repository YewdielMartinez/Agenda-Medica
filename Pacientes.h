#ifndef PACIENTES_H
#define PACIENTES_H
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


//Declaracion de funciones de pacientes
void RegistrarPaciente();
void MostrarPacientes();
void EliminarPacientes();
void EditarPacientes();
void MenuPrincipalPacientes();

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
            case 1:RegistrarPaciente();break;
            case 2:MostrarPacientes ();break;
            case 3:EliminarPacientes();break;
            case 4:EditarPacientes();break;
            case 5:MenuPrincipal();break;
            case 6: std::cout << "Saliendo del programa. ¡Hasta luego!" << std::endl; 
            return ;
            break;
        
            default: std:: cout <<"Elige una opcion del 1 al 6";break;

            }   
        } while (opcion!=6);
}


void RegistrarPaciente() {
    Pacientes paciente;
    std::cout << "Ingrese el número de identificación del paciente: ";
    paciente.Identificacion_Paciente = pedirNumero(); // Pedir el número de identificación
    
    std::cout << "Ingrese el nombre del paciente: ";
    std::cin.ignore();
    std::getline(std::cin, paciente.Nombre_Pacientes);

    std::cout << "Ingrese la edad del paciente: ";
    paciente.Edad_Pacientes = pedirNumero(); // Aquí puedes usar tu función pedirNumero para validar la entrada.

    std::cout << "Ingrese el número de teléfono del paciente: ";
    std::getline(std::cin, paciente.Numero_TelefonicoPacientes);

    std::cout << "Ingrese la dirección del paciente: ";
    std::getline(std::cin, paciente.Direccion_Pacientes);

    agendapacientes.push_back(paciente);

    std::cout << "Paciente registrado exitosamente." << std::endl;

    if (validarRespuesta()) {
        MenuPrincipalPacientes();
    } else {
        RegistrarPaciente();
    }
}
void MostrarPacientes(){
if (agendapacientes.empty()) {
        std::cout << "No hay pacientes registrados." << std::endl;
    } else {
        std::cout << "Lista de Pacientes Registrados:" << std::endl;
        for (const auto& paciente : agendapacientes) {
            std::cout << "Identificación: " << paciente.Identificacion_Paciente << std::endl;
            std::cout << "Nombre: " << paciente.Nombre_Pacientes << std::endl;
            std::cout << "Edad: " << paciente.Edad_Pacientes << std::endl;
            std::cout << "Teléfono: " << paciente.Numero_TelefonicoPacientes << std::endl;
            std::cout << "Dirección: " << paciente.Direccion_Pacientes << std::endl;
            std::cout << "-----------------------------" << std::endl;
        }
    }
    if (validarRespuesta()) {
        MenuPrincipalPacientes();
    } else {
        MostrarPacientes();
    }
}
void EditarPacientes() {
    std::cout << "Ingrese el número de identificación del paciente que desea editar: ";
    int id = pedirNumero();
    bool encontrado = false;

    for (auto& paciente : agendapacientes) {
        if (paciente.Identificacion_Paciente == id) {
            std::cout << "Ingrese el nuevo numero de identificación del paciente: ";
            paciente.Identificacion_Paciente = pedirNumero(); // Pedir el número de identificación
            std::cout << "Ingrese el nuevo nombre del paciente: ";
            std::cin.ignore();
            std::getline(std::cin, paciente.Nombre_Pacientes);

            std::cout << "Ingrese la nueva edad del paciente: ";
            paciente.Edad_Pacientes = pedirNumero();

            std::cout << "Ingrese el nuevo número de teléfono del paciente: ";
            std::getline(std::cin, paciente.Numero_TelefonicoPacientes);

            std::cout << "Ingrese la nueva dirección del paciente: ";
            std::getline(std::cin, paciente.Direccion_Pacientes);

            std::cout << "Paciente editado exitosamente." << std::endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "Paciente no encontrado. Intente de nuevo." << std::endl;
    }

    if (validarRespuesta()) {
        MenuPrincipalPacientes();
    } else {
        EditarPacientes();
    }
}
void EliminarPacientes() {
    std::cout << "Ingrese el número de identificación del paciente que desea eliminar: ";
    int id = pedirNumero();
    auto it = std::remove_if(agendapacientes.begin(), agendapacientes.end(),
                             [id](const Pacientes& paciente) { return paciente.Identificacion_Paciente == id; });

    if (it != agendapacientes.end()) {
        agendapacientes.erase(it, agendapacientes.end());
        std::cout << "Paciente eliminado exitosamente." << std::endl;
    } else {
        std::cout << "Paciente no encontrado. Intente de nuevo." << std::endl;
    }

    if (validarRespuesta()) {
        MenuPrincipalPacientes();
    } else {
        EliminarPacientes();
    }
}





#endif