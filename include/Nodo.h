/**
 * @file Nodo.h
 * @brief Definición de la estructura de nodo genérica para listas enlazadas
 * @author Santiago Euresti
 * @date 30 de octubre de 2024
 */

#ifndef NODO_H
#define NODO_H

/**
 * @brief Estructura genérica de nodo para lista enlazada simple
 * @tparam T Tipo de dato que almacena el nodo
 */
template <typename T>
struct Nodo {
    T dato;                ///< Dato almacenado en el nodo
    Nodo<T>* siguiente;    ///< Puntero al siguiente nodo en la lista
    
    /**
     * @brief Constructor del nodo
     * @param valor Valor inicial del nodo
     */
    Nodo(const T& valor) : dato(valor), siguiente(nullptr) {}
};

#endif // NODO_H