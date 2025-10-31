/**
 * @file SensorPresion.cpp
 * @brief Implementación de la clase SensorPresion
 * @author Santiago Euresti
 * @date 30 de octubre de 2024
 */

#include "../include/SensorPresion.h"

SensorPresion::SensorPresion() : SensorBase("Presion_Default") {
    std::cout << "[Log] SensorPresion creado: " << nombre << std::endl;
}

SensorPresion::SensorPresion(const char* nombreSensor) : SensorBase(nombreSensor) {
    std::cout << "[Log] SensorPresion creado: " << nombre << std::endl;
}

SensorPresion::~SensorPresion() {
    std::cout << "[Destructor Sensor " << nombre << "] Liberando Lista Interna..." << std::endl;
}

void SensorPresion::procesarLectura() {
    std::cout << "-> Procesando Sensor " << nombre << "..." << std::endl;
    
    if (historial.estaVacia()) {
        std::cout << "[Sensor Presion] No hay lecturas para procesar." << std::endl;
        return;
    }
    
    int numLecturas = historial.obtenerTamaño();
    int promedio = historial.calcularPromedio();
    
    std::cout << "[" << nombre << "] (Presion): Promedio de lecturas: " 
              << promedio << " (sobre " << numLecturas << " lecturas)." << std::endl;
}

void SensorPresion::imprimirInfo() const {
    std::cout << "=== Información del Sensor de Presión ===" << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Tipo: Presión (int)" << std::endl;
    std::cout << "Lecturas registradas: " << historial.obtenerTamaño() << std::endl;
    
    if (!historial.estaVacia()) {
        std::cout << "Promedio actual: " << historial.calcularPromedio() << std::endl;
    }
    std::cout << "=========================================" << std::endl;
}

void SensorPresion::registrarLectura(int presion) {
    historial.insertar(presion);
    std::cout << "[Log] Insertando Nodo<int> en " << nombre << "." << std::endl;
}

int SensorPresion::obtenerNumeroLecturas() const {
    return historial.obtenerTamaño();
}

bool SensorPresion::tieneLecturas() const {
    return !historial.estaVacia();
}

void SensorPresion::mostrarHistorial() const {
    std::cout << "Historial de " << nombre << ": ";
    historial.imprimir();
}