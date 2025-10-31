/**
 * @file main.cpp
 * @brief Programa principal del Sistema de Gestión Polimórfica de Sensores para IoT
 * @author Santiago Euresti
 * @date 30 de octubre de 2024
 * 
 * Este programa implementa un sistema de gestión polimórfica que maneja
 * diferentes tipos de sensores usando listas enlazadas simples genéricas.
 */

#include "../include/SensorBase.h"
#include "../include/SensorTemperatura.h"
#include "../include/SensorPresion.h"
#include "../include/ListaSensor.h"
#include <iostream>
#include <limits>

/**
 * @brief Estructura de nodo para la lista de gestión polimórfica (no genérica)
 */
struct NodoSensor {
    SensorBase* sensor;         ///< Puntero a la clase base para polimorfismo
    NodoSensor* siguiente;      ///< Puntero al siguiente nodo
    
    /**
     * @brief Constructor del nodo
     * @param s Puntero al sensor
     */
    NodoSensor(SensorBase* s) : sensor(s), siguiente(nullptr) {}
};

/**
 * @brief Clase para gestionar la lista polimórfica de sensores
 */
class ListaGestion {
private:
    NodoSensor* cabeza;         ///< Primer nodo de la lista

public:
    /**
     * @brief Constructor
     */
    ListaGestion() : cabeza(nullptr) {
        std::cout << "[Log] Lista de Gestión Polimórfica creada." << std::endl;
    }
    
    /**
     * @brief Destructor - libera toda la memoria
     */
    ~ListaGestion() {
        std::cout << "\n--- Liberación de Memoria en Cascada ---" << std::endl;
        while (cabeza != nullptr) {
            NodoSensor* temp = cabeza;
            cabeza = cabeza->siguiente;
            
            std::cout << "[Destructor General] Liberando Nodo: " 
                      << temp->sensor->obtenerNombre() << "." << std::endl;
            delete temp->sensor;  // Llama al destructor virtual apropiado
            delete temp;
        }
        std::cout << "Sistema cerrado. Memoria limpia." << std::endl;
    }
    
    /**
     * @brief Inserta un sensor en la lista de gestión
     * @param sensor Puntero al sensor a insertar
     */
    void insertarSensor(SensorBase* sensor) {
        NodoSensor* nuevoNodo = new NodoSensor(sensor);
        
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            NodoSensor* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
        
        std::cout << "Sensor '" << sensor->obtenerNombre() 
                  << "' creado e insertado en la lista de gestión." << std::endl;
    }
    
    /**
     * @brief Busca un sensor por nombre
     * @param nombre Nombre del sensor a buscar
     * @return Puntero al sensor encontrado o nullptr si no existe
     */
    SensorBase* buscarSensor(const char* nombre) {
        NodoSensor* actual = cabeza;
        while (actual != nullptr) {
            if (std::strcmp(actual->sensor->obtenerNombre(), nombre) == 0) {
                return actual->sensor;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }
    
    /**
     * @brief Ejecuta el procesamiento polimórfico en todos los sensores
     */
    void ejecutarProcesamientoPolimorfico() {
        if (cabeza == nullptr) {
            std::cout << "No hay sensores registrados para procesar." << std::endl;
            return;
        }
        
        std::cout << "\n--- Ejecutando Polimorfismo ---" << std::endl;
        NodoSensor* actual = cabeza;
        while (actual != nullptr) {
            actual->sensor->procesarLectura();  // Llamada polimórfica
            actual = actual->siguiente;
        }
    }
    
    /**
     * @brief Muestra información de todos los sensores
     */
    void mostrarTodosSensores() {
        if (cabeza == nullptr) {
            std::cout << "No hay sensores registrados." << std::endl;
            return;
        }
        
        std::cout << "\n--- Lista de Sensores Registrados ---" << std::endl;
        NodoSensor* actual = cabeza;
        int contador = 1;
        while (actual != nullptr) {
            std::cout << contador << ". " << actual->sensor->obtenerNombre() << std::endl;
            actual = actual->siguiente;
            contador++;
        }
    }
    
    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool estaVacia() const {
        return cabeza == nullptr;
    }
};

/**
 * @brief Muestra el menú principal del sistema
 */
void mostrarMenu() {
    std::cout << "\n=== Sistema IoT de Monitoreo Polimórfico ===" << std::endl;
    std::cout << "1. Crear Sensor de Temperatura (FLOAT)" << std::endl;
    std::cout << "2. Crear Sensor de Presión (INT)" << std::endl;
    std::cout << "3. Registrar Lectura en Sensor" << std::endl;
    std::cout << "4. Ejecutar Procesamiento Polimórfico" << std::endl;
    std::cout << "5. Mostrar Información de Sensor" << std::endl;
    std::cout << "6. Listar Todos los Sensores" << std::endl;
    std::cout << "7. Mostrar Historial de Sensor" << std::endl;
    std::cout << "8. Cerrar Sistema (Liberar Memoria)" << std::endl;
    std::cout << "Seleccione una opción: ";
}

/**
 * @brief Función para limpiar el buffer de entrada
 */
void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Función principal del programa
 * @return Código de estado de salida
 */
int main() {
    ListaGestion listaGestion;
    int opcion;
    
    std::cout << "=== Iniciando Sistema IoT de Monitoreo Polimórfico ===" << std::endl;
    
    do {
        mostrarMenu();
        std::cin >> opcion;
        
        if (std::cin.fail()) {
            std::cout << "Error: Ingrese un número válido." << std::endl;
            limpiarBuffer();
            continue;
        }
        
        switch (opcion) {
            case 1: {
                std::cout << "\nOpción 1: Crear Sensor (Tipo Temp - FLOAT)" << std::endl;
                char nombre[50];
                std::cout << "Ingrese el nombre del sensor de temperatura: ";
                std::cin >> nombre;
                
                SensorTemperatura* sensorTemp = new SensorTemperatura(nombre);
                listaGestion.insertarSensor(sensorTemp);
                break;
            }
            
            case 2: {
                std::cout << "\nOpción 2: Crear Sensor (Tipo Presión - INT)" << std::endl;
                char nombre[50];
                std::cout << "Ingrese el nombre del sensor de presión: ";
                std::cin >> nombre;
                
                SensorPresion* sensorPresion = new SensorPresion(nombre);
                listaGestion.insertarSensor(sensorPresion);
                break;
            }
            
            case 3: {
                std::cout << "\nOpción 3: Registrar Lectura" << std::endl;
                char nombre[50];
                std::cout << "Ingrese el nombre del sensor: ";
                std::cin >> nombre;
                
                SensorBase* sensor = listaGestion.buscarSensor(nombre);
                if (sensor == nullptr) {
                    std::cout << "Error: Sensor '" << nombre << "' no encontrado." << std::endl;
                    break;
                }
                
                // Downcasting seguro para determinar el tipo de sensor
                SensorTemperatura* sensorTemp = dynamic_cast<SensorTemperatura*>(sensor);
                SensorPresion* sensorPresion = dynamic_cast<SensorPresion*>(sensor);
                
                if (sensorTemp != nullptr) {
                    float temperatura;
                    std::cout << "Ingrese la lectura de temperatura (float): ";
                    std::cin >> temperatura;
                    
                    if (std::cin.fail()) {
                        std::cout << "Error: Valor inválido para temperatura." << std::endl;
                        limpiarBuffer();
                        break;
                    }
                    
                    sensorTemp->registrarLectura(temperatura);
                    std::cout << "ID: " << nombre << ". Valor: " << temperatura << " (float)" << std::endl;
                    
                } else if (sensorPresion != nullptr) {
                    int presion;
                    std::cout << "Ingrese la lectura de presión (int): ";
                    std::cin >> presion;
                    
                    if (std::cin.fail()) {
                        std::cout << "Error: Valor inválido para presión." << std::endl;
                        limpiarBuffer();
                        break;
                    }
                    
                    sensorPresion->registrarLectura(presion);
                    std::cout << "ID: " << nombre << ". Valor: " << presion << " (int)" << std::endl;
                }
                break;
            }
            
            case 4: {
                std::cout << "\nOpción 4: Ejecutar Procesamiento Polimórfico" << std::endl;
                listaGestion.ejecutarProcesamientoPolimorfico();
                break;
            }
            
            case 5: {
                std::cout << "\nOpción 5: Mostrar Información de Sensor" << std::endl;
                char nombre[50];
                std::cout << "Ingrese el nombre del sensor: ";
                std::cin >> nombre;
                
                SensorBase* sensor = listaGestion.buscarSensor(nombre);
                if (sensor != nullptr) {
                    sensor->imprimirInfo();
                } else {
                    std::cout << "Error: Sensor '" << nombre << "' no encontrado." << std::endl;
                }
                break;
            }
            
            case 6: {
                std::cout << "\nOpción 6: Listar Todos los Sensores" << std::endl;
                listaGestion.mostrarTodosSensores();
                break;
            }
            
            case 7: {
                std::cout << "\nOpción 7: Mostrar Historial de Sensor" << std::endl;
                char nombre[50];
                std::cout << "Ingrese el nombre del sensor: ";
                std::cin >> nombre;
                
                SensorBase* sensor = listaGestion.buscarSensor(nombre);
                if (sensor == nullptr) {
                    std::cout << "Error: Sensor '" << nombre << "' no encontrado." << std::endl;
                    break;
                }
                
                SensorTemperatura* sensorTemp = dynamic_cast<SensorTemperatura*>(sensor);
                SensorPresion* sensorPresion = dynamic_cast<SensorPresion*>(sensor);
                
                if (sensorTemp != nullptr) {
                    sensorTemp->mostrarHistorial();
                } else if (sensorPresion != nullptr) {
                    sensorPresion->mostrarHistorial();
                }
                break;
            }
            
            case 8: {
                std::cout << "\nOpción 8: Cerrar Sistema (Liberar Memoria)" << std::endl;
                std::cout << "Cerrando sistema..." << std::endl;
                break;
            }
            
            default: {
                std::cout << "Error: Opción inválida. Seleccione una opción del 1 al 8." << std::endl;
                break;
            }
        }
        
    } while (opcion != 8);
    
    return 0;
}