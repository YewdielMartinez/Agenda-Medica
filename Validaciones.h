#ifndef VALIDACIONES_H
#define VALIDACIONES_H
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
#include <cstdlib> 
#include "Doctores.h"
#include "Pacientes.h"
#include "Citas.h"
#include "Declaraciones.h"
#include "Consultorios.h"
#include "Validaciones.h"
#include "Funcionesarchivos.h"
double pedirNumeroM();
double pedirNumero();
double pedirNumeroMC();
bool validarRespuesta();
void LimpiarPantalla() {
    system("cls"); // En sistemas Windows
}
double pedirNumeroMM() {
    double numero{ 0 };
    bool inputCorrecto = false;

    do {
        std::cin >> numero;
        if (std::cin.fail() || numero < 1 || numero > 5) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Por favor, ingrese un número válido del 1 al 5: ";
        } else {
            inputCorrecto = true;
        }
    } while (!inputCorrecto);

    return numero;
}
double pedirNumeroM() {
    double numero{ 0 };
    bool inputCorrecto = false;

    do {
        std::cin >> numero;
        if (std::cin.fail() || numero < 1 || numero > 6) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Por favor, ingrese un número válido del 1 al 6: ";
        } else {
            inputCorrecto = true;
        }
    } while (!inputCorrecto);

    return numero;
}
double pedirNumero()
{

  double numero{ 0 };
  // Valida que sea un numero, diferente a cero y no contenga nada despues
  do
  {
    if (std::cin >> numero && std::cin.peek() == '\n')
    {
      std::cin.ignore(); // Limpiar el buffer despues de obtener el numero
      return numero;
    }
    else
    {
      // Limpia el cin y sus errores para pedir otra vez el numero
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Ingresa solamente un numero valido por favor." << std::endl;
    }
  } while (true);

}
double pedirNumeroMC() {
    double numero{ 0 };
    bool inputCorrecto = false;

    do {
        std::cin >> numero;
        if (std::cin.fail() || numero < 1 || numero > 7) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Por favor, ingrese un número válido del 1 al 7: ";
        } else {
            inputCorrecto = true;
        }
    } while (!inputCorrecto);

    return numero;
}
bool validarRespuesta() {
    std::string respuesta;
    std::cout << "Quiere regresar al Menu Principal (SI/NO): ";
    std::cin >> respuesta;

    // Convertir la respuesta a mayúsculas usando std::transform
    std::transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::toupper);

    while (true) {
        if (respuesta == "SI") {
            return true;
        } else if (respuesta == "NO") {
            return false;
        } else {
            std::cout << "Respuesta inválida. Por favor, ingrese 'SI' o 'NO'." << std::endl;
            std::cout << "Quiere regresar al Menu Principal (SI/NO): ";
            std::cin >> respuesta;
            std::transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::toupper);
        }
    }
}
bool ValidarCaracter(const std::string& dato_ingresado) { 
    for (char es_palabra : dato_ingresado) { //Se crea una variable tipo char 'es_palabra' que recorre la cadena dato_ingresado caracter por caracter.
        if (!std::isalpha(es_palabra) && !std::isspace(es_palabra)) { //isalpha verifica caracter por caracter si es una palabra
            return false; //Si encontramos un caracter que NO es un caracter se retorna false
        }
    }
    return true; //Si llegamos hasta aqui se retorna true y la caden es una palabra valida 
}
std::string ValidarPalabra(std::string mensaje) {
    std::string palabra_ingresada; //Se crea una variable string llamada "palabra_ingresada"
    while (true) {
        std::getline(std::cin, palabra_ingresada); //La entrada del ususario se guarda en la variable palabra_ingresada
        if (ValidarCaracter(palabra_ingresada)){ //Se llama a la funcion val_caracter y se le manda el dato ingresado por el usuario
            return palabra_ingresada;//Si es una palabra se regresa la palabra ingresada por el usuario
        } else { //Si no se cumple se muesta este mensaje al usuario hasta que ingrese el dato correcto
            std::cout<<mensaje<<std::endl;
        }
    }
}
bool ValidarHora(const std::string& hora) {
    std::istringstream ss(hora);
    char colon;
    int hh, mm;
    ss >> hh >> colon >> mm;
    return ss && colon == ':' && hh >= 0 && hh <= 23 && mm >= 0 && mm <= 59;
}
std::string timePointToString(const std::chrono::time_point<std::chrono::system_clock>& tp) {
    auto tt = std::chrono::system_clock::to_time_t(tp);
    auto localTime = std::localtime(&tt);
    char buffer[10];
    std::strftime(buffer, sizeof(buffer), "%H:%M", localTime);
    return std::string(buffer);
}
bool ValidarFechaHora(const std::string& fechaHoraStr, const char* format) {
    std::tm tm = {};
    std::istringstream ss(fechaHoraStr);
    ss >> std::get_time(&tm, format);
    if (ss.fail()) {
        return false;
    }
    std::time_t time = std::mktime(&tm);
    if (time == -1) {
        return false;
    }
    return true;
}
bool tieneEspaciosVacios(const std::string& cadena) {
    return std::find_if(cadena.begin(), cadena.end(), [](char c) {
        return std::isspace(static_cast<unsigned char>(c)); // Comprueba si el carácter es un espacio en blanco
    }) != cadena.end();
}
void cerrarPrograma() {
    std::cout << "Cerrando el programa. Adiós.\n";
    exit(0); // Puedes usar otro valor si prefieres un código de salida diferente
}

double pedirNumeroTelefono() {
    double numero{ 0 };

    do {
        if (std::cin >> numero && std::cin.peek() == '\n') {
            // Verificar que el número tenga 10 dígitos
            if (std::to_string(static_cast<long long>(numero)).length() == 10) {
                std::cin.ignore(); // Limpiar el buffer después de obtener el número
                return numero;
            } else {
                std::cout << "El número de teléfono debe tener exactamente 10 dígitos. Inténtalo de nuevo." << std::endl;
            }
        } else {
            // Limpiar el cin y sus errores para pedir otra vez el número
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ingresa solamente un número válido por favor." << std::endl;
        }
    } while (true);
}
#endif