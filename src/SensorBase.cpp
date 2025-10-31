/**
 * @file SensorBase.cpp
 * @brief Implementación de la clase base abstracta SensorBase
 * @author Santiago Euresti
 * @date 30 de octubre de 2024
 */

#include "../include/SensorBase.h"

SensorBase::SensorBase() {
    std::strcpy(nombre, "Sensor_Default");
    std::cout << "[Log] SensorBase creado: " << nombre << std::endl;
}

SensorBase::SensorBase(const char* nombreSensor) {
    std::strncpy(nombre, nombreSensor, sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';  // Asegurar terminación nula
    std::cout << "[Log] SensorBase creado: " << nombre << std::endl;
}

SensorBase::~SensorBase() {
    std::cout << "[Log] SensorBase destruido: " << nombre << std::endl;
}

const char* SensorBase::obtenerNombre() const {
    return nombre;
}

void SensorBase::establecerNombre(const char* nombreSensor) {
    std::strncpy(nombre, nombreSensor, sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';  // Asegurar terminación nula
}