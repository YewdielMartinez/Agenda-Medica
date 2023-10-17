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
#include "Declaraciones.h"
//#include "MenuPrincipal.h"



void MenuPrincipalDoctores(){
        int opcion {0};//Declaramos una variable local para el MenuPrincipalDoctores
        std::cout << "=== Gestión de Doctores ===" << std::endl;
        std::cout << "1. Registrar nuevo doctor" << std::endl;
        std::cout << "2. Mostrar doctores registrados" << std::endl;
        std::cout << "3. Eliminar doctor" << std::endl;
        std::cout << "4. Editar doctor" << std::endl;
        std::cout << "5. Regresar al menu principal del programa. " << std::endl;
        std::cout << "6. Cerrar Programa. " << std::endl;

        opcion = pedirNumeroM();//Aqui hace la llamada a la funcion para que pueda validar el numero
        //Aqui hacemos que un switch case para elegir la opcion y llame a su respectiva funcion
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
    //Creamos un objeto que se llama Doctor y lo agregamos al vector llamado agenda doctores
    Doctor doctorr;

    std::string Horario_EntradaStr,Horario_SalidaStr;
    const char* format = "%H:%M";
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
    

        doctorr.Especialidad = ValidarPalabra("Favor de ingresar la especialidad");//aqui validamos que la especialidad no vayan numeros
        while(doctorr.Especialidad.empty()){
                std::cout << "No puede dejar el espacio vacio"<<std::endl;
            
                doctorr.Especialidad = ValidarPalabra("Volver a ingresar");
            
        }
    // Solicitar y validar el horario de entrada del doctor
    do 
    {
        std::cout << "Ingrese el horario de entrada del doctor (HH:MM): ";
        std::getline(std::cin, Horario_EntradaStr);
        while (!ValidarHora(Horario_EntradaStr)) {
        std::cout << "Formato de hora incorrecto. Use HH:MM: ";
        std::getline(std::cin, Horario_EntradaStr);
        }
       try{
        std::tm tmEntrada = {};
        std::istringstream entradaStream(Horario_EntradaStr);
        entradaStream >> std::get_time(&tmEntrada,format);
        if(entradaStream.fail()){
            throw std::runtime_error("Error formato de hora no valido");
        }
        doctorr.Horario_Entrada = std::chrono::system_clock::from_time_t(std::mktime(&tmEntrada));
        break;
        
        }catch(const std::exception& e){
            std::cerr << "Error: "<< e.what() << std::endl;
        }
    }while(true);    
        
    do {
        std::cout << "Ingrese el horario de Salida del doctor (HH:MM): ";
        std::getline(std::cin, Horario_SalidaStr);
    while (!ValidarHora(Horario_SalidaStr)) {
        std::cout << "Formato de hora incorrecto. Use HH:MM: ";
        std::getline(std::cin, Horario_SalidaStr);
    }
        try{
        std::tm tmSalida = {};
        std::istringstream SalidaStream(Horario_SalidaStr);
        SalidaStream >> std::get_time(&tmSalida,format);
        if(SalidaStream.fail()){
            throw std::runtime_error("Error formato de hora no valido");
        }
        doctorr.Horario_Salida = std::chrono::system_clock::from_time_t(std::mktime(&tmSalida));
        break;

        }catch(const std::exception& e){
            std::cerr << "Error: "<< e.what() << std::endl;
        }
    }while(true);    
    agendadoctores.push_back(doctorr);

        std::cout << "Doctor registrado exitosamente." << std::endl;
if (validarRespuesta()){
        MenuPrincipalDoctores();
        
        }else{
        RegistrarDoctor();
        }

}
void MostrarDoctores() {
    if (agendadoctores.empty()) {
        std::cout << "No hay doctores registrados." << std::endl;
        MenuPrincipalDoctores(); // Puedes volver al menú principal después de mostrar los doctores.
    } else {
        std::cout << "=== Lista de Doctores Registrados ===" << std::endl;
        for (const auto& doctor : agendadoctores) {
            std::cout << "Nombre: " << doctor.Nombre_Doctor << std::endl;
            std::cout << "Especialidad: " << doctor.Especialidad << std::endl;

            // Convertir y mostrar horario de entrada
            auto entrada_time = std::chrono::system_clock::to_time_t(doctor.Horario_Entrada);
            std::cout << "Horario de Entrada: " << std::put_time(std::localtime(&entrada_time), "%H:%M") << std::endl;

            // Convertir y mostrar horario de salida
            auto salida_time = std::chrono::system_clock::to_time_t(doctor.Horario_Salida);
            std::cout << "Horario de Salida: " << std::put_time(std::localtime(&salida_time), "%H:%M") << std::endl;

            std::cout << "------------------------------------" << std::endl;
        }
        MenuPrincipalDoctores(); // Puedes volver al menú principal después de mostrar los doctores.
    }
}
void EliminarDoctor(){
    if (agendadoctores.empty()) {
        std::cout << "No hay doctores registrados para eliminar." << std::endl;
        return;
    }

    std::string nombre;
    std::cout << "Ingrese el nombre del doctor que desea eliminar: ";
    std::cin.ignore();
    std::getline(std::cin, nombre);

    auto it = std::find_if(agendadoctores.begin(), agendadoctores.end(),
                           [&nombre](const Doctor& doctor) {
                               return doctor.Nombre_Doctor == nombre;
                           });

    if (it != agendadoctores.end()) {
        agendadoctores.erase(it);
        std::cout << "Doctor eliminado correctamente." << std::endl;
    } else {
        std::cout << "Doctor no encontrado. No se puede eliminar." << std::endl;
    }

    if (validarRespuesta()) {
        MenuPrincipalDoctores();
    } else {
        EliminarDoctor();
    }
}
void EditarDoctor(){
    if (agendadoctores.empty()) {
        std::cout << "No hay doctores registrados para editar." << std::endl;
        return;
    }

    std::string nombre;
    std::cout << "Ingrese el nombre del doctor que desea editar: ";
    std::cin.ignore();
    std::getline(std::cin, nombre);

    auto it = std::find_if(agendadoctores.begin(), agendadoctores.end(),
                           [&nombre](const Doctor& doctor) {
                               return doctor.Nombre_Doctor == nombre;
                           });

    if (it != agendadoctores.end()) {
        Doctor& doctor = *it;

        // Permite al usuario editar los campos del doctor
        std::cout << "Ingrese el nuevo nombre del doctor: ";
        std::getline(std::cin, doctor.Nombre_Doctor);
        std::cout << "Ingrese la nueva especialidad del doctor: ";
        std::getline(std::cin, doctor.Especialidad);

        // Solicitar y validar el nuevo horario de entrada del doctor
        std::string Horario_EntradaStr;
        const char* format = "%H:%M";
        do {
            std::cout << "Ingrese el nuevo horario de entrada del doctor (HH:MM): ";
            std::getline(std::cin, Horario_EntradaStr);
            while (!ValidarHora(Horario_EntradaStr)) {
                std::cout << "Formato de hora incorrecto. Use HH:MM: ";
                std::getline(std::cin, Horario_EntradaStr);
            }
            try {
                std::tm tmEntrada = {};
                std::istringstream entradaStream(Horario_EntradaStr);
                entradaStream >> std::get_time(&tmEntrada, format);
                if (entradaStream.fail()) {
                    throw std::runtime_error("Error formato de hora no valido");
                }
                doctor.Horario_Entrada = std::chrono::system_clock::from_time_t(std::mktime(&tmEntrada));
                break;
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } while (true);

        // Solicitar y validar el nuevo horario de salida del doctor
        std::string Horario_SalidaStr;
        do {
            std::cout << "Ingrese el nuevo horario de Salida del doctor (HH:MM): ";
            std::getline(std::cin, Horario_SalidaStr);
            while (!ValidarHora(Horario_SalidaStr)) {
                std::cout << "Formato de hora incorrecto. Use HH:MM: ";
                std::getline(std::cin, Horario_SalidaStr);
            }
            try {
                std::tm tmSalida = {};
                std::istringstream SalidaStream(Horario_SalidaStr);
                SalidaStream >> std::get_time(&tmSalida, format);
                if (SalidaStream.fail()) {
                    throw std::runtime_error("Error formato de hora no valido");
                }
                doctor.Horario_Salida = std::chrono::system_clock::from_time_t(std::mktime(&tmSalida));
                break;
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } while (true);

        std::cout << "Doctor editado correctamente." << std::endl;
    } else {
        std::cout << "Doctor no encontrado. No se puede editar." << std::endl;
    }

    if (validarRespuesta()) {
        MenuPrincipalDoctores();
    } else {
        EditarDoctor();
    }
}






#endif