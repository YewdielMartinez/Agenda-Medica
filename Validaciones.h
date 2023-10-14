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
#include "Doctores.h"

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

#endif