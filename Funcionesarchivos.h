#ifdef FUNCIONESARCHIVOS_H
#define FUNCIONESARCHIVOS_H
#include <fstream>
void GuardarDoctores() {
    std::ofstream archivo("doctores.txt");

    if (archivo.is_open()) {
        for (const auto& doctor : agendadoctores) {
            archivo << doctor.Nombre_Doctor << " ";
            archivo << doctor.Especialidad << " ";

            for (bool dia : doctor.Dias_Trabajo) {
                archivo << dia << " ";
            }

            auto entrada_time = std::chrono::system_clock::to_time_t(doctor.Horario_Entrada);
            archivo << std::put_time(std::localtime(&entrada_time), "%H:%M") << " ";

            auto salida_time = std::chrono::system_clock::to_time_t(doctor.Horario_Salida);
            archivo << std::put_time(std::localtime(&salida_time), "%H:%M") << " ";

            archivo << doctor.NumeroConsultorio << std::endl;
        }

        archivo.close();
    } else {
        std::cerr << "Error al abrir el archivo para guardar doctores." << std::endl;
    }
}
void CargarDoctores() {
    agendadoctores.clear(); // Limpiar el vector antes de cargar

    std::ifstream archivo("doctores.txt");

    if (archivo.is_open()) {
        while (!archivo.eof()) {
            Doctor doctor;
            std::string entrada;

            archivo >> doctor.Nombre_Doctor;
            archivo >> doctor.Especialidad;

            for (size_t i = 0; i < dias_semana.size(); ++i) {
                bool dia;
                archivo >> dia;
                doctor.Dias_Trabajo[i] = dia;
            }

            archivo >> entrada;
            std::tm tmEntrada = {};
            std::istringstream entradaStream(entrada);
            entradaStream >> std::get_time(&tmEntrada, "%H:%M");
            doctor.Horario_Entrada = std::chrono::system_clock::from_time_t(std::mktime(&tmEntrada));

            archivo >> entrada;
            std::tm tmSalida = {};
            std::istringstream salidaStream(entrada);
            salidaStream >> std::get_time(&tmSalida, "%H:%M");
            doctor.Horario_Salida = std::chrono::system_clock::from_time_t(std::mktime(&tmSalida));

            archivo >> doctor.NumeroConsultorio;

            if (!archivo.eof()) {
                agendadoctores.push_back(doctor);
            }
        }

        archivo.close();
    } else {
        std::cerr << "Error al abrir el archivo para cargar doctores." << std::endl;
    }
}
// Función para cargar citas desde un archivo
void CargarCitas() {
    std::ifstream archivo("citas.txt"); // Nombre del archivo donde se guardan las citas

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo de citas." << std::endl;
        return;
    }

    agendacitas.clear(); // Limpiar el vector de citas antes de cargar nuevas citas

    Cita cita;
    while (archivo >> cita.Identificador >> cita.Nombre_Doctor >> cita.Nombre_Paciente) {
        // Leer la fecha y hora como una cadena y luego convertirla a std::chrono::system_clock::time_point
        std::string fechaHoraStr;
        archivo >> fechaHoraStr;
        const char* format = "%d/%m/%Y %H:%M";
        std::tm tmCita = {};
        std::istringstream fechaHoraStream(fechaHoraStr);
        fechaHoraStream >> std::get_time(&tmCita, format);
        cita.Fecha_Hora = std::chrono::system_clock::from_time_t(std::mktime(&tmCita));

        archivo >> cita.NumeroConsultorio;

        agendacitas.push_back(cita);
    }

    archivo.close();
}

// Función para guardar citas en un archivo
void GuardarCitas() {
    std::ofstream archivo("citas.txt"); // Nombre del archivo donde se guardarán las citas

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo de citas para guardar." << std::endl;
        return;
    }

    for (const auto& cita : agendacitas) {
        archivo << cita.Identificador << " "
                << cita.Nombre_Doctor << " "
                << cita.Nombre_Paciente << " "
                << std::put_time(std::localtime(&std::chrono::system_clock::to_time_t(cita.Fecha_Hora)), "%d/%m/%Y %H:%M") << " "
                << cita.NumeroConsultorio << "\n";
    }

    archivo.close();
}
// Función para guardar la información de los pacientes en un archivo
void GuardarPacientes() {
    std::ofstream archivo("pacientes.txt", std::ios::out);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar pacientes." << std::endl;
        return;
    }

    for (const auto& paciente : agendapacientes) {
        archivo << paciente.Identificacion_Paciente << ","
                << paciente.Nombre_Pacientes << ","
                << paciente.Edad_Pacientes << ","
                << paciente.Numero_TelefonicoPacientes << ","
                << paciente.Direccion_Pacientes << "\n";
    }

    archivo.close();
}

// Función para cargar la información de los pacientes desde un archivo
void CargarPacientes() {
    agendapacientes.clear(); // Limpiar el vector antes de cargar nuevos pacientes

    std::ifstream archivo("pacientes.txt", std::ios::in);

    if (!archivo.is_open()) {
        std::cerr << "No se encontró el archivo de pacientes. Creando uno nuevo." << std::endl;
        return;
    }

    while (!archivo.eof()) {
        Pacientes paciente;
        archivo >> paciente.Identificacion_Paciente;
        archivo.ignore(); // Ignorar la coma
        std::getline(archivo, paciente.Nombre_Pacientes, ',');
        archivo >> paciente.Edad_Pacientes;
        archivo.ignore(); // Ignorar la coma
        archivo >> paciente.Numero_TelefonicoPacientes;
        archivo.ignore(); // Ignorar la coma
        std::getline(archivo, paciente.Direccion_Pacientes);

        if (!paciente.Nombre_Pacientes.empty()) {
            agendapacientes.push_back(paciente);
        }
    }

    archivo.close();
}
// Función para guardar consultorios en un archivo
void GuardarConsultorios() {
    std::ofstream archivo("consultorios.txt");

    if (archivo.is_open()) {
        for (const auto& consultorio : agendaconsultorios) {
            archivo << consultorio.NumeroConsultorio << std::endl;
        }

        std::cout << "Consultorios guardados correctamente en consultorios.txt" << std::endl;
        archivo.close();
    } else {
        std::cout << "Error al abrir el archivo para guardar consultorios." << std::endl;
    }
}

// Función para cargar consultorios desde un archivo
void CargarConsultorios() {
    agendaconsultorios.clear();  // Limpiar consultorios existentes

    std::ifstream archivo("consultorios.txt");

    if (archivo.is_open()) {
        int numeroConsultorio;
        while (archivo >> numeroConsultorio) {
            Consultorio consultorio;
            consultorio.NumeroConsultorio = numeroConsultorio;
            agendaconsultorios.push_back(consultorio);
        }

        std::cout << "Consultorios cargados correctamente desde consultorios.txt" << std::endl;
        archivo.close();
    } else {
        std::cout << "No se encontró el archivo de consultorios. Se creará uno nuevo." << std::endl;
    }
}
#endif 