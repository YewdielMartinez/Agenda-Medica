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
#include "Doctores.h"
#include "Pacientes.h"
#include "Validaciones.h"
//Declaracion de funciones de doctores
void RegistrarDoctor();
void MostrarDoctores();
void EliminarDoctor();
void EditarDoctor();
void MenuPrincipalDoctores();
//Declaracion de funciones de pacientes
void RegistrarPacientes();
void MostrarPacientes();
void EliminarPacientes();
void EditarPacientes();
void MenuPrincipalPacientes();


struct Doctor {
std::string Nombre_Doctor;
std::string Especialidad;
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
    int Numero_TelefonicoPacientes;

};

#endif 
