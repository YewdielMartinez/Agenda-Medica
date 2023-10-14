#ifndef DECLARACIONES.H
#define DECLARACIONES.H
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
std::vector<Doctor> agendadoctores;
Doctor doctorr;

#endif 
