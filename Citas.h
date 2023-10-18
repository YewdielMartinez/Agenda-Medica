#ifndef CITAS_H
#define CITAS_H
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

//Definicion de funciones 
void MostrarDoctoresDisponibles();
void MostrarPacientesDisponibles();
void MenuPrincipalCitas();
int GenerarIdentificador();
void AgregarCita();
void EditarCita();
void EliminarCita();
void MostrarCitas();
void MostrarCitasMasCercanas();
void MostrarDoctoresDisponibles() {
    std::cout << "=== Lista de Doctores Disponibles ===" << std::endl;
    for (const auto& doctor : agendadoctores) {
        std::cout << "Nombre: " << doctor.Nombre_Doctor << std::endl;
        std::cout << "Especialidad: " << doctor.Especialidad << std::endl;
        std::cout << "------------------------------------" << std::endl;
    }
}

void MostrarPacientesDisponibles() {
    std::cout << "=== Lista de Pacientes Disponibles ===" << std::endl;
    for (const auto& paciente : agendapacientes) {
        std::cout << "Nombre: " << paciente.Nombre_Pacientes << std::endl;
        std::cout << "Identificación: " << paciente.Identificacion_Paciente << std::endl;
        std::cout << "------------------------------------" << std::endl;
    }
}



struct Cita {
    
    int Identificador;
    std::string Nombre_Doctor;
    std::string Nombre_Paciente;
    std::chrono::system_clock::time_point Fecha_Hora;
};
std::vector<Cita> agendacitas;

int GenerarIdentificador() {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_int_distribution<int> distribution(1000, 9999); // Rango de identificadores

    return distribution(generator);
}





void MenuPrincipalCitas(){
        int opcion {0};//Declaramos una variable local para el MenuPrincipalPacientes
        std::cout << "=== Gestión de Citas ===" << std::endl;
        std::cout << "1. Registrar nueva Citas" << std::endl;
        std::cout << "2. Mostrar Citas registradas" << std::endl;
        std::cout << "3. Eliminar Citas" << std::endl;
        std::cout << "4. Editar Citas" << std::endl;
        std::cout << "5. Regresar al menu principal del programa. " << std::endl;
        std::cout << "6. Cerrar Programa. " << std::endl;

        opcion = pedirNumeroMC();//Aqui hace la llamada a la funcion para que pueda validar el numero
        //Aqui hacemos que un switch case para elegir la opcion y llame a su respectiva funcion
        do{
     
            switch(opcion){
            case 1:AgregarCita();break;
            case 2:MostrarCitas ();break;
            case 3:EliminarCita();break;
            case 4:EditarCita();break;
            case 5:MostrarCitasMasCercanas();break;
            case 6:MenuPrincipal();break;
            case 7: std::cout << "Saliendo del programa. ¡Hasta luego!" << std::endl; 
            return ;
            break;
        
            default: std:: cout <<"Elige una opcion del 1 al 7";break;

            }   
        } while (opcion!=7);
}
void AgregarCita() {
    Cita nuevaCita;
    nuevaCita.Identificador = GenerarIdentificador();
    std::cout << "Seleccione el doctor para la cita:" << std::endl;
    MostrarDoctoresDisponibles();
    std::cout << "Ingrese el nombre del doctor: ";
    std::string nombreDoctor;
    std::cin.ignore();
    std::getline(std::cin, nombreDoctor);

    // Verificar si el doctor existe
    auto itDoctor = std::find_if(agendadoctores.begin(), agendadoctores.end(),
                                  [&nombreDoctor](const Doctor& doctor) {
                                      return doctor.Nombre_Doctor == nombreDoctor;
                                  });

    if (itDoctor == agendadoctores.end()) {
        std::cout << "Doctor no encontrado. La cita no puede ser programada." << std::endl;
        return;
    }

    nuevaCita.Nombre_Doctor = nombreDoctor;

    std::cout << "Seleccione el paciente para la cita:" << std::endl;
    MostrarPacientesDisponibles();
    std::cout << "Ingrese la identificación del paciente: ";
    int identificacionPaciente = pedirNumero();

    // Verificar si el paciente existe
    auto itPaciente = std::find_if(agendapacientes.begin(), agendapacientes.end(),
                                    [&identificacionPaciente](const Pacientes& paciente) {
                                        return paciente.Identificacion_Paciente == identificacionPaciente;
                                    });

    if (itPaciente == agendapacientes.end()) {
        std::cout << "Paciente no encontrado. La cita no puede ser programada." << std::endl;
        return;
    }

    nuevaCita.Nombre_Paciente = itPaciente->Nombre_Pacientes;

    // Solicitar y validar la fecha y hora de la cita
    std::string fechaHoraStr;
    const char* format = "%d/%m/%Y %H:%M";
    do {
        std::cout << "Ingrese la fecha y hora de la cita (dd/mm/yyyy HH:MM): ";
        std::getline(std::cin, fechaHoraStr);
        while (!ValidarFechaHora(fechaHoraStr, format)) {
            std::cout << "Formato de fecha/hora incorrecto. Use dd/mm/yyyy HH:MM: ";
            std::getline(std::cin, fechaHoraStr);
        }
        try {
            std::tm tmCita = {};
            std::istringstream citaStream(fechaHoraStr);
            citaStream >> std::get_time(&tmCita, format);
            if (citaStream.fail()) {
                throw std::runtime_error("Error formato de fecha/hora no valido");
            }
            nuevaCita.Fecha_Hora = std::chrono::system_clock::from_time_t(std::mktime(&tmCita));
            break;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } while (true);

    // Verificar si la cita coincide con el horario del doctor
    auto& doctor = *itDoctor;
    if (nuevaCita.Fecha_Hora < doctor.Horario_Entrada || nuevaCita.Fecha_Hora > doctor.Horario_Salida) {
        std::cout << "La cita no coincide con el horario del doctor. La cita no puede ser programada." << std::endl;
        return;
    }

    // Agregar la cita al vector de citas
    agendacitas.push_back(nuevaCita);
    std::cout << "Cita programada exitosamente." << std::endl;
    MenuPrincipalCitas();
}
void EditarCita() {
    if (agendacitas.empty()) {
        std::cout << "No hay citas registradas para editar." << std::endl;
        return;
    }

    std::cout << "=== Lista de Citas Registradas ===" << std::endl;
    for (const auto& cita : agendacitas) {
        std::time_t tiempocita = std::chrono::system_clock::to_time_t(cita.Fecha_Hora);
        std::cout << "Identificador: " << cita.Identificador << std::endl;
        std::cout << "Doctor: " << cita.Nombre_Doctor << std::endl;
        std::cout << "Paciente: " << cita.Nombre_Paciente << std::endl;
        std::cout << "Fecha y Hora: " << std::put_time(std::localtime(&tiempocita), "%d/%m/%Y %H:%M") << std::endl;
        std::cout << "------------------------------------" << std::endl;
    }

    std::cout << "Ingrese el identificador de la cita que desea editar: ";
    int identificadorCita = pedirNumero();

    auto itCita = std::find_if(agendacitas.begin(), agendacitas.end(),
                                [&identificadorCita](const Cita& cita) {
                                    return cita.Identificador == identificadorCita;
                                });

    if (itCita != agendacitas.end()) {
        Cita& cita = *itCita;

        // Realizar las modificaciones necesarias
        std::string nuevaFechaHoraStr;
        const char* format = "%d/%m/%Y %H:%M";
        do {
            std::cout << "Ingrese la nueva fecha y hora de la cita (dd/mm/yyyy HH:MM): ";
            std::getline(std::cin, nuevaFechaHoraStr);
            while (!ValidarFechaHora(nuevaFechaHoraStr, format)) {
                std::cout << "Formato de fecha/hora incorrecto. Use dd/mm/yyyy HH:MM: ";
                std::getline(std::cin, nuevaFechaHoraStr);
            }
            try {
                std::tm tmNuevaCita = {};
                std::istringstream nuevaCitaStream(nuevaFechaHoraStr);
                nuevaCitaStream >> std::get_time(&tmNuevaCita, format);
                if (nuevaCitaStream.fail()) {
                    throw std::runtime_error("Error formato de fecha/hora no valido");
                }
                cita.Fecha_Hora = std::chrono::system_clock::from_time_t(std::mktime(&tmNuevaCita));
                break;
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } while (true);

        std::cout << "Cita editada correctamente." << std::endl;
    } else {
        std::cout << "Cita no encontrada. No se puede editar." << std::endl;
    }
}
void EliminarCita() {
    if (agendacitas.empty()) {
        std::cout << "No hay citas registradas para eliminar." << std::endl;
        return;
    }

    std::cout << "=== Lista de Citas Registradas ===" << std::endl;
    for (const auto& cita : agendacitas) {
        std::time_t tiempocita = std::chrono::system_clock::to_time_t(cita.Fecha_Hora);
        std::cout << "Identificador: " << cita.Identificador << std::endl;
        std::cout << "Doctor: " << cita.Nombre_Doctor << std::endl;
        std::cout << "Paciente: " << cita.Nombre_Paciente << std::endl;
        std::cout << "Fecha y Hora: " << std::put_time(std::localtime(&tiempocita), "%d/%m/%Y %H:%M") << std::endl;
        std::cout << "------------------------------------" << std::endl;
    }

    std::cout << "Ingrese el identificador de la cita que desea eliminar: ";
    int identificadorCita = pedirNumero();

    auto itCita = std::find_if(agendacitas.begin(), agendacitas.end(),
                                [&identificadorCita](const Cita& cita) {
                                    return cita.Identificador == identificadorCita;
                                });

    if (itCita != agendacitas.end()) {
        agendacitas.erase(itCita);
        std::cout << "Cita eliminada correctamente." << std::endl;
    } else {
        std::cout << "Cita no encontrada. No se puede eliminar." << std::endl;
    }
}
void MostrarCitas() {
    if (agendacitas.empty()) {
        std::cout << "No hay citas registradas." << std::endl;
        return;
    }

    std::cout << "=== Lista de Citas Registradas ===" << std::endl;
    for (const auto& cita : agendacitas) {
        std::time_t tiempocita = std::chrono::system_clock::to_time_t(cita.Fecha_Hora);
        std::cout << "Identificador: " << cita.Identificador << std::endl;
        std::cout << "Doctor: " << cita.Nombre_Doctor << std::endl;
        std::cout << "Paciente: " << cita.Nombre_Paciente << std::endl;
        std::cout << "Fecha y Hora: " << std::put_time(std::localtime(&tiempocita), "%d/%m/%Y %H:%M") << std::endl;
        std::cout << "------------------------------------" << std::endl;
    }
}

void MostrarCitasMasCercanas() {
    if (agendacitas.empty()) {
        std::cout << "No hay citas registradas." << std::endl;
        return;
    }

    auto now = std::chrono::system_clock::now();
    auto twoWeeksLater = now + std::chrono::hours(24 * 14);  // Dos semanas (14 días)

    std::cout << "=== Citas para las próximas dos semanas ===" << std::endl;
    for (const auto& cita : agendacitas) {
        if (cita.Fecha_Hora >= now && cita.Fecha_Hora <= twoWeeksLater) {
            std::time_t tiempocita = std::chrono::system_clock::to_time_t(cita.Fecha_Hora);
            std::cout << "Identificador: " << cita.Identificador << std::endl;
            std::cout << "Doctor: " << cita.Nombre_Doctor << std::endl;
            std::cout << "Paciente: " << cita.Nombre_Paciente << std::endl;
            std::cout << "Fecha y Hora: " << std::put_time(std::localtime(&tiempocita), "%d/%m/%Y %H:%M") << std::endl;
            std::cout << "------------------------------------" << std::endl;
        }
    }
}

#endif 