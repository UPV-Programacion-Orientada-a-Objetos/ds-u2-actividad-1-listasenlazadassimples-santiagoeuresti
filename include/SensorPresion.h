/**
 * @file SensorPresion.h
 * @brief Clase derivada para sensor de presión que maneja lecturas de tipo int
 * @author Santiago Euresti
 * @date 30 de octubre de 2024
 */

#ifndef SENSOR_PRESION_H
#define SENSOR_PRESION_H

#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @brief Clase concreta para sensor de presión
 * 
 * Hereda de SensorBase e implementa funcionalidad específica para
 * el manejo de lecturas de presión usando valores de tipo int
 */
class SensorPresion : public SensorBase {
private:
    ListaSensor<int> historial;  ///< Lista de lecturas de presión

public:
    /**
     * @brief Constructor por defecto
     */
    SensorPresion();
    
    /**
     * @brief Constructor con nombre del sensor
     * @param nombreSensor Nombre identificador del sensor de presión
     */
    SensorPresion(const char* nombreSensor);
    
    /**
     * @brief Destructor
     */
    virtual ~SensorPresion();
    
    /**
     * @brief Implementación del procesamiento de lecturas de presión
     * 
     * Calcula el promedio de todas las lecturas de presión registradas
     */
    virtual void procesarLectura() override;
    
    /**
     * @brief Implementación para imprimir información del sensor de presión
     */
    virtual void imprimirInfo() const override;
    
    /**
     * @brief Registra una nueva lectura de presión
     * @param presion Valor de presión a registrar
     */
    void registrarLectura(int presion);
    
    /**
     * @brief Obtiene el número de lecturas registradas
     * @return Número de lecturas en el historial
     */
    int obtenerNumeroLecturas() const;
    
    /**
     * @brief Verifica si el sensor tiene lecturas registradas
     * @return true si hay lecturas, false en caso contrario
     */
    bool tieneLecturas() const;
    
    /**
     * @brief Muestra todas las lecturas registradas
     */
    void mostrarHistorial() const;
};

#endif // SENSOR_PRESION_H