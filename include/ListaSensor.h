/**
 * @file ListaSensor.h
 * @brief Implementación de lista enlazada simple genérica para sensores
 * @author Santiago Euresti
 * @date 30 de octubre de 2024
 */

#ifndef LISTA_SENSOR_H
#define LISTA_SENSOR_H

#include "Nodo.h"
#include <iostream>

/**
 * @brief Clase genérica para lista enlazada simple de sensores
 * @tparam T Tipo de dato que almacena la lista (int, float, double, etc.)
 */
template <typename T>
class ListaSensor {
private:
    Nodo<T>* cabeza;    ///< Puntero al primer nodo de la lista
    int tamaño;         ///< Número de elementos en la lista

public:
    /**
     * @brief Constructor por defecto
     */
    ListaSensor();
    
    /**
     * @brief Constructor de copia
     * @param otra Lista a copiar
     */
    ListaSensor(const ListaSensor<T>& otra);
    
    /**
     * @brief Operador de asignación
     * @param otra Lista a asignar
     * @return Referencia a esta lista
     */
    ListaSensor<T>& operator=(const ListaSensor<T>& otra);
    
    /**
     * @brief Destructor - libera toda la memoria
     */
    ~ListaSensor();
    
    /**
     * @brief Inserta un elemento al final de la lista
     * @param valor Valor a insertar
     */
    void insertar(const T& valor);
    
    /**
     * @brief Busca un elemento en la lista
     * @param valor Valor a buscar
     * @return true si encuentra el elemento, false en caso contrario
     */
    bool buscar(const T& valor) const;
    
    /**
     * @brief Elimina el primer elemento con el valor especificado
     * @param valor Valor a eliminar
     * @return true si se eliminó el elemento, false si no se encontró
     */
    bool eliminar(const T& valor);
    
    /**
     * @brief Obtiene el número de elementos en la lista
     * @return Número de elementos
     */
    int obtenerTamaño() const;
    
    /**
     * @brief Verifica si la lista está vacía
     * @return true si la lista está vacía, false en caso contrario
     */
    bool estaVacia() const;
    
    /**
     * @brief Calcula el promedio de los elementos en la lista
     * @return Promedio de los elementos (0 si la lista está vacía)
     */
    T calcularPromedio() const;
    
    /**
     * @brief Encuentra y elimina el valor mínimo de la lista
     * @return El valor mínimo eliminado (valor por defecto si la lista está vacía)
     */
    T eliminarMinimo();
    
    /**
     * @brief Imprime todos los elementos de la lista
     */
    void imprimir() const;
    
    /**
     * @brief Libera toda la memoria de la lista
     */
    void limpiar();

private:
    /**
     * @brief Copia los elementos de otra lista
     * @param otra Lista a copiar
     */
    void copiar(const ListaSensor<T>& otra);
};

// Implementación de métodos template

template <typename T>
ListaSensor<T>::ListaSensor() : cabeza(nullptr), tamaño(0) {
    std::cout << "[Log] ListaSensor<T> creada." << std::endl;
}

template <typename T>
ListaSensor<T>::ListaSensor(const ListaSensor<T>& otra) : cabeza(nullptr), tamaño(0) {
    copiar(otra);
}

template <typename T>
ListaSensor<T>& ListaSensor<T>::operator=(const ListaSensor<T>& otra) {
    if (this != &otra) {
        limpiar();
        copiar(otra);
    }
    return *this;
}

template <typename T>
ListaSensor<T>::~ListaSensor() {
    limpiar();
    std::cout << "[Log] ListaSensor<T> destruida." << std::endl;
}

template <typename T>
void ListaSensor<T>::insertar(const T& valor) {
    Nodo<T>* nuevoNodo = new Nodo<T>(valor);
    
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    } else {
        Nodo<T>* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
    
    tamaño++;
    std::cout << "[Log] Insertando Nodo<T> con valor: " << valor << std::endl;
}

template <typename T>
bool ListaSensor<T>::buscar(const T& valor) const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        if (actual->dato == valor) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

template <typename T>
bool ListaSensor<T>::eliminar(const T& valor) {
    if (cabeza == nullptr) {
        return false;
    }
    
    if (cabeza->dato == valor) {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        tamaño--;
        std::cout << "[Log] Nodo<T> " << valor << " liberado." << std::endl;
        return true;
    }
    
    Nodo<T>* actual = cabeza;
    while (actual->siguiente != nullptr && actual->siguiente->dato != valor) {
        actual = actual->siguiente;
    }
    
    if (actual->siguiente != nullptr) {
        Nodo<T>* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        delete temp;
        tamaño--;
        std::cout << "[Log] Nodo<T> " << valor << " liberado." << std::endl;
        return true;
    }
    
    return false;
}

template <typename T>
int ListaSensor<T>::obtenerTamaño() const {
    return tamaño;
}

template <typename T>
bool ListaSensor<T>::estaVacia() const {
    return cabeza == nullptr;
}

template <typename T>
T ListaSensor<T>::calcularPromedio() const {
    if (estaVacia()) {
        return T{};
    }
    
    T suma = T{};
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        suma += actual->dato;
        actual = actual->siguiente;
    }
    
    return suma / static_cast<T>(tamaño);
}

template <typename T>
T ListaSensor<T>::eliminarMinimo() {
    if (estaVacia()) {
        return T{};
    }
    
    // Encontrar el valor mínimo
    T minimo = cabeza->dato;
    Nodo<T>* actual = cabeza->siguiente;
    while (actual != nullptr) {
        if (actual->dato < minimo) {
            minimo = actual->dato;
        }
        actual = actual->siguiente;
    }
    
    // Eliminar el primer nodo con el valor mínimo
    eliminar(minimo);
    return minimo;
}

template <typename T>
void ListaSensor<T>::imprimir() const {
    std::cout << "Lista: ";
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->dato << " ";
        actual = actual->siguiente;
    }
    std::cout << std::endl;
}

template <typename T>
void ListaSensor<T>::limpiar() {
    while (cabeza != nullptr) {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->siguiente;
        std::cout << "[Log] Nodo<T> " << temp->dato << " liberado." << std::endl;
        delete temp;
    }
    tamaño = 0;
}

template <typename T>
void ListaSensor<T>::copiar(const ListaSensor<T>& otra) {
    Nodo<T>* actual = otra.cabeza;
    while (actual != nullptr) {
        insertar(actual->dato);
        actual = actual->siguiente;
    }
}

#endif // LISTA_SENSOR_H