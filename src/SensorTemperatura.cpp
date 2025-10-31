/**
 * @file SensorTemperatura.cpp
 * @brief Implementación de la clase SensorTemperatura
 * @author Santiago Euresti
 * @date 30 de octubre de 2024
 */

#include "../include/SensorTemperatura.h"

SensorTemperatura::SensorTemperatura() : SensorBase("Temp_Default") {
    std::cout << "[Log] SensorTemperatura creado: " << nombre << std::endl;
}

SensorTemperatura::SensorTemperatura(const char* nombreSensor) : SensorBase(nombreSensor) {
    std::cout << "[Log] SensorTemperatura creado: " << nombre << std::endl;
}

SensorTemperatura::~SensorTemperatura() {
    std::cout << "[Destructor Sensor " << nombre << "] Liberando Lista Interna..." << std::endl;
}

void SensorTemperatura::procesarLectura() {
    std::cout << "-> Procesando Sensor " << nombre << "..." << std::endl;
    
    if (historial.estaVacia()) {
        std::cout << "[Sensor Temp] No hay lecturas para procesar." << std::endl;
        return;
    }
    
    int numLecturas = historial.obtenerTamaño();
    
    if (numLecturas == 1) {
        float promedio = historial.calcularPromedio();
        std::cout << "[Sensor Temp] Promedio calculado sobre " << numLecturas 
                  << " lectura (" << promedio << ")." << std::endl;
    } else {
        // Eliminar el valor mínimo y calcular promedio de los restantes
        float minimo = historial.eliminarMinimo();
        
        if (!historial.estaVacia()) {
            float promedio = historial.calcularPromedio();
            std::cout << "[" << nombre << "] (Temperatura): Lectura más baja (" 
                      << minimo << ") eliminada. Promedio restante: " << promedio << "." << std::endl;
        } else {
            std::cout << "[" << nombre << "] (Temperatura): Única lectura (" 
                      << minimo << ") procesada y eliminada." << std::endl;
        }
    }
}

void SensorTemperatura::imprimirInfo() const {
    std::cout << "=== Información del Sensor de Temperatura ===" << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Tipo: Temperatura (float)" << std::endl;
    std::cout << "Lecturas registradas: " << historial.obtenerTamaño() << std::endl;
    
    if (!historial.estaVacia()) {
        std::cout << "Promedio actual: " << historial.calcularPromedio() << std::endl;
    }
    std::cout << "=============================================" << std::endl;
}

void SensorTemperatura::registrarLectura(float temperatura) {
    historial.insertar(temperatura);
    std::cout << "[Log] Insertando Nodo<float> en " << nombre << "." << std::endl;
}

int SensorTemperatura::obtenerNumeroLecturas() const {
    return historial.obtenerTamaño();
}

bool SensorTemperatura::tieneLecturas() const {
    return !historial.estaVacia();
}

void SensorTemperatura::mostrarHistorial() const {
    std::cout << "Historial de " << nombre << ": ";
    historial.imprimir();
}