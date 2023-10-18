#ifndef DECLARACIONES_H
#define DECLARACIONES_H
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

struct Doctor {
std::string Nombre_Doctor;
std::string Especialidad;
std::string diasTrabajoStr;
std::chrono::system_clock::time_point Horario_Entrada;
std::chrono::system_clock::time_point Horario_Salida;
};
Doctor doctorr;
const char* format = "%H:%M";
std::vector<Doctor> agendadoctores;

struct Pacientes{
    std::string Nombre_Pacientes;
    int Edad_Pacientes;
    std::string Direccion_Pacientes; 
    std::string Numero_TelefonicoPacientes;
    int Identificacion_Paciente;

};
std::vector<Pacientes> agendapacientes;

void RegistrarPaciente();
void MostrarPacientes();
void EliminarPacientes();
void EditarPacientes();
void MenuPrincipalPacientes();
//Declaracion de funciones de doctores
void RegistrarDoctor();
void MostrarDoctores();
void EliminarDoctor();
void EditarDoctor();
void MenuPrincipalDoctores();
void MenuPrincipal();
void MostrarDoctoresDisponibles();
void MostrarPacientesDisponibles();
void MenuPrincipalCitas();
int GenerarIdentificador();
void AgregarCita();
void EditarCita();
void EliminarCita();
void MostrarCitas();
void MostrarCitasMasCercanas();



#endif 
