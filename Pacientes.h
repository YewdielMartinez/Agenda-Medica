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
#include "Funcionesarchivos.h"

//Declaracion de funciones de pacientes
void RegistrarPaciente();
void MostrarPacientes();
void EliminarPacientes();
void EditarPacientes();
void MenuPrincipalPacientes();
void GuardarPacientes();
void CargarPacientes();
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
            cerrarPrograma();
            break;
        
            default: std:: cout <<"Elige una opcion del 1 al 6";break;

            }   
        } while (opcion!=6);
}


void RegistrarPaciente() {
      

    Pacientes paciente;
    std::cout << "Ingrese el número de identificación del paciente: ";
    int nuevoId = pedirNumero(); // Pedir el número de identificación

    // Verificar si el número de identificación ya está en uso
    auto it = std::find_if(agendapacientes.begin(), agendapacientes.end(),
                           [nuevoId](const Pacientes &p) { return p.Identificacion_Paciente == nuevoId; });

    if (it != agendapacientes.end()) {
        std::cout << "Error: El número de identificación ya está en uso. Intente con otro número." << std::endl;
        return;
    }

    paciente.Identificacion_Paciente = nuevoId;
    do {
        std::cout << "Ingrese el nombre del paciente: " << std::endl;

        std::cin.ignore();
        paciente.Nombre_Pacientes = ValidarPalabra("Por Favor Ingresar el nombre");

        if (tieneEspaciosVacios(paciente.Nombre_Pacientes)) {
            std::cout << "La cadena no debe contener espacios vacíos.Intenta de nuevo" << std::endl;
        } while (paciente.Nombre_Pacientes.empty()) {
            std::cout << "No puede dejar el espacio vacío" << std::endl;

            paciente.Nombre_Pacientes = ValidarPalabra("Volver a ingresar");
        }
    } while (tieneEspaciosVacios(paciente.Nombre_Pacientes));
    std::cout << "El Nombre se agregó correctamente." << std::endl;

    std::cout << "Ingrese la edad del paciente: ";
    paciente.Edad_Pacientes = pedirNumero(); // Aquí puedes usar tu función pedirNumero para validar la entrada.

    std::cout << "Ingrese el número de teléfono del paciente: ";

    // Cambio: Se utiliza pedirNumeroTelefono() para validar el número de teléfono
    paciente.Numero_TelefonicoPacientes = pedirNumeroTelefono();

    do {
        std::cout << "Ingrese la dirección del paciente: " << std::endl;
        std::getline(std::cin, paciente.Direccion_Pacientes);
        std::cin.ignore();

        if (tieneEspaciosVacios(paciente.Direccion_Pacientes)) {
            std::cout << "La cadena no debe contener espacios vacíos. Intente de nuevo" << std::endl;
        } while (paciente.Direccion_Pacientes.empty()) {
            std::cout << "No puede dejar el espacio vacío" << std::endl;
            std::getline(std::cin, paciente.Direccion_Pacientes);
        }
    } while (tieneEspaciosVacios(paciente.Direccion_Pacientes));
    std::cout << "La dirección se agregó correctamente." << std::endl;

    agendapacientes.push_back(paciente);

    GuardarPacientes();  // Guardar pacientes después de realizar operaciones

    std::cout << "Paciente registrado exitosamente." << std::endl;

    if (validarRespuesta()) {
        MenuPrincipalPacientes();
    } else {
        RegistrarPaciente();
    }
}
void MostrarPacientes() {
    CargarPacientes(); // Cargar pacientes antes de mostrarlos

    if (agendapacientes.empty()) {
        std::cout << "No hay pacientes registrados." << std::endl;
    } else {
        std::cout << "Lista de Pacientes Registrados:" << std::endl;
        for (const auto &paciente : agendapacientes) {
            std::cout << "Identificación: " << paciente.Identificacion_Paciente << std::endl;
            std::cout << "Nombre: " << paciente.Nombre_Pacientes << std::endl;
            std::cout << "Edad: " << paciente.Edad_Pacientes << std::endl;
            std::cout << "Teléfono: " << paciente.Numero_TelefonicoPacientes << std::endl;
            std::cout << "Dirección: " << paciente.Direccion_Pacientes << std::endl;
            std::cout << "-----------------------------" << std::endl;
        }
    }

    GuardarPacientes(); // Guardar pacientes después de mostrarlos

    if (validarRespuesta()) {
        MenuPrincipalPacientes();
    } else {
        MostrarPacientes();
    }
}
void EditarPacientes() {
    CargarPacientes();
    if (agendapacientes.empty()) {
        std::cout << "No hay pacientes registrados para editar." << std::endl;
        return;
    }

    std::cout << "Ingrese el número de identificación del paciente que desea editar: ";
    int idEditar = pedirNumero(); // Pedir el número de identificación del paciente a editar

    // Buscar al paciente por su identificación
    auto it = std::find_if(agendapacientes.begin(), agendapacientes.end(),
                           [idEditar](const Pacientes& p) { return p.Identificacion_Paciente == idEditar; });

    if (it == agendapacientes.end()) {
        std::cout << "No se encontró un paciente con ese número de identificación." << std::endl;
        return;
    }

    // Mostrar la información actual del paciente
    std::cout << "Información actual del paciente:" << std::endl;
    std::cout << "Identificación: " << it->Identificacion_Paciente << std::endl;
    std::cout << "Nombre: " << it->Nombre_Pacientes << std::endl;
    std::cout << "Edad: " << it->Edad_Pacientes << std::endl;
    std::cout << "Teléfono: " << it->Numero_TelefonicoPacientes << std::endl;
    std::cout << "Dirección: " << it->Direccion_Pacientes << std::endl;

    // Pedir al usuario que ingrese la nueva información del paciente
    do
        {
            std::cout << "Ingrese el nuevo nombre del paciente: "<<std::endl;
        
            std::cin.ignore();
            it->Nombre_Pacientes = ValidarPalabra("Por Favor Ingresar el nombre");//Aqui validamos que el nombre del doctor sea palabra y no ponga numero
            
            if (tieneEspaciosVacios(it->Nombre_Pacientes)) {
                std::cout << "La cadena no debe contener espacios vacíos.Intenta de nuevo" << std::endl;

            } 
            while(it->Nombre_Pacientes.empty()){
                std::cout << "No puede dejar el espacio vacio"<<std::endl;
                
                it->Nombre_Pacientes = ValidarPalabra("Volver a ingresar");
            }
        }while(tieneEspaciosVacios(it->Nombre_Pacientes));
        std::cout << "El Nombre se agrego correctamente." << std::endl;
    std::cout << "Ingrese la nueva edad del paciente: ";
    it->Edad_Pacientes = pedirNumero();

    std::cout << "Ingrese el nuevo número de teléfono del paciente: ";
    it->Numero_TelefonicoPacientes = pedirNumeroTelefono();

    do
    {
        std::cout << "Ingrese la direccion del paciente: "<<std::endl;
        std::getline(std::cin, it->Direccion_Pacientes);
        std::cin.ignore();
        
        
        if (tieneEspaciosVacios(it->Direccion_Pacientes)) {
            std::cout << "La cadena no debe contener espacios vacíos.Intenta de nuevo" << std::endl;

        } 
        while(it->Direccion_Pacientes.empty()){
            std::cout << "No puede dejar el espacio vacio"<<std::endl;
            std::getline(std::cin, it->Direccion_Pacientes);
            
        }
    }while(tieneEspaciosVacios(it->Direccion_Pacientes));
    std::cout << "La direccion se agrego correctamente." << std::endl;

    std::cout << "Información del paciente actualizada correctamente." << std::endl;
    GuardarPacientes();
    if (validarRespuesta()) {
        MenuPrincipalPacientes();
    } else {
        EditarPacientes();
    }
}
void EliminarPacientes() {
    CargarPacientes(); // Cargar pacientes antes de eliminar

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

    GuardarPacientes(); // Guardar pacientes después de eliminar

    if (validarRespuesta()) {
        MenuPrincipalPacientes();
    } else {
        EliminarPacientes();
    }
}




#endif