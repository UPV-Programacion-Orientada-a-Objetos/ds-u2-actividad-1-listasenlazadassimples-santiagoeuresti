/**
 * @file SensorBase.h
 * @brief Clase base abstracta para todos los tipos de sensores
 * @author Santiago Euresti
 * @date 30 de octubre de 2024
 */

#ifndef SENSOR_BASE_H
#define SENSOR_BASE_H

#include <iostream>
#include <cstring>

/**
 * @brief Clase base abstracta que define la interfaz común para todos los sensores
 * 
 * Esta clase establece los métodos virtuales puros que deben ser implementados
 * por todas las clases derivadas de sensores específicos.
 */
class SensorBase {
protected:
    char nombre[50];  ///< Identificador único del sensor

public:
    /**
     * @brief Constructor por defecto
     */
    SensorBase();
    
    /**
     * @brief Constructor con nombre del sensor
     * @param nombreSensor Nombre identificador del sensor
     */
    SensorBase(const char* nombreSensor);
    
    /**
     * @brief Destructor virtual para polimorfismo
     */
    virtual ~SensorBase();
    
    /**
     * @brief Método virtual puro para procesar lecturas del sensor
     * 
     * Cada tipo de sensor debe implementar su propia lógica de procesamiento
     */
    virtual void procesarLectura() = 0;
    
    /**
     * @brief Método virtual puro para imprimir información del sensor
     * 
     * Cada tipo de sensor debe implementar su forma de mostrar información
     */
    virtual void imprimirInfo() const = 0;
    
    /**
     * @brief Obtiene el nombre del sensor
     * @return Puntero constante al nombre del sensor
     */
    const char* obtenerNombre() const;
    
    /**
     * @brief Establece el nombre del sensor
     * @param nombreSensor Nuevo nombre para el sensor
     */
    void establecerNombre(const char* nombreSensor);
};

#endif // SENSOR_BASE_H