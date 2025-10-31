/**
 * @file SensorTemperatura.h
 * @brief Clase derivada para sensor de temperatura que maneja lecturas de tipo float
 * @author Santiago Euresti
 * @date 30 de octubre de 2024
 */

#ifndef SENSOR_TEMPERATURA_H
#define SENSOR_TEMPERATURA_H

#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @brief Clase concreta para sensor de temperatura
 * 
 * Hereda de SensorBase e implementa funcionalidad específica para
 * el manejo de lecturas de temperatura usando valores de tipo float
 */
class SensorTemperatura : public SensorBase {
private:
    ListaSensor<float> historial;  ///< Lista de lecturas de temperatura

public:
    /**
     * @brief Constructor por defecto
     */
    SensorTemperatura();
    
    /**
     * @brief Constructor con nombre del sensor
     * @param nombreSensor Nombre identificador del sensor de temperatura
     */
    SensorTemperatura(const char* nombreSensor);
    
    /**
     * @brief Destructor
     */
    virtual ~SensorTemperatura();
    
    /**
     * @brief Implementación del procesamiento de lecturas de temperatura
     * 
     * Encuentra y elimina la lectura más baja, luego calcula el promedio
     * de las lecturas restantes
     */
    virtual void procesarLectura() override;
    
    /**
     * @brief Implementación para imprimir información del sensor de temperatura
     */
    virtual void imprimirInfo() const override;
    
    /**
     * @brief Registra una nueva lectura de temperatura
     * @param temperatura Valor de temperatura a registrar
     */
    void registrarLectura(float temperatura);
    
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

#endif // SENSOR_TEMPERATURA_H