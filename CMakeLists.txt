# CMakeLists.txt para Sistema de Gestión Polimórfica de Sensores IoT
# Autor: Santiago Euresti
# Fecha: 30 de octubre de 2024

cmake_minimum_required(VERSION 3.16)

# Información del proyecto
project(SensorIoTSystem 
    VERSION 1.0.0
    DESCRIPTION "Sistema de Gestión Polimórfica de Sensores para IoT"
    LANGUAGES CXX)

# Configuración del estándar C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configuraciones de compilación
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Opciones de compilador
if(MSVC)
    # Configuración para Visual Studio/MSVC
    add_compile_options(/W4)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(/Od /Zi)
    else()
        add_compile_options(/O2)
    endif()
else()
    # Configuración para GCC/Clang
    add_compile_options(-Wall -Wextra -Wpedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0)
    else()
        add_compile_options(-O3)
    endif()
endif()

# Directorio de encabezados
include_directories(${CMAKE_SOURCE_DIR}/include)

# Archivos fuente
set(SOURCES
    src/main.cpp
    src/SensorBase.cpp
    src/SensorTemperatura.cpp
    src/SensorPresion.cpp
)

# Archivos de encabezado (para IDEs)
set(HEADERS
    include/Nodo.h
    include/ListaSensor.h
    include/SensorBase.h
    include/SensorTemperatura.h
    include/SensorPresion.h
)

# Crear el ejecutable principal
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Propiedades del ejecutable
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "sensor_iot_system"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Configuración para diferentes sistemas operativos
if(WIN32)
    # Configuración específica para Windows
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN)
elseif(UNIX AND NOT APPLE)
    # Configuración específica para Linux
    target_link_libraries(${PROJECT_NAME} pthread)
elseif(APPLE)
    # Configuración específica para macOS
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME "Sensor IoT System"
    )
endif()

# Instalación (opcional)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    COMPONENT Runtime
)

# Información de configuración
message(STATUS "========================================")
message(STATUS "Proyecto: ${PROJECT_NAME}")
message(STATUS "Versión: ${PROJECT_VERSION}")
message(STATUS "Descripción: ${PROJECT_DESCRIPTION}")
message(STATUS "Compilador: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Estándar C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "Tipo de compilación: ${CMAKE_BUILD_TYPE}")
message(STATUS "Directorio de fuentes: ${CMAKE_SOURCE_DIR}")
message(STATUS "Directorio de compilación: ${CMAKE_BINARY_DIR}")
message(STATUS "========================================")

# Opción para generar archivos de compilación detallados
option(VERBOSE_BUILD "Enable verbose build output" OFF)
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

# Configuración para Doxygen (si está disponible)
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
    message(STATUS "Doxygen encontrado: ${DOXYGEN_EXECUTABLE}")
    
    # Configurar la generación de documentación
    set(DOXYGEN_INPUT_DIR ${CMAKE_SOURCE_DIR})
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/docs)
    
    # Target personalizado para generar documentación
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generando documentación con Doxygen"
        VERBATIM
    )
    
    message(STATUS "Target 'docs' disponible para generar documentación")
else()
    message(STATUS "Doxygen no encontrado - documentación no disponible")
endif()

# Target para limpiar completamente el directorio de compilación
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}
    COMMENT "Limpiando completamente el directorio de compilación"
)

# Información de uso
message(STATUS "")
message(STATUS "Comandos útiles:")
message(STATUS "  make sensor_iot_system  - Compilar el programa")
message(STATUS "  make docs              - Generar documentación (si Doxygen está disponible)")
message(STATUS "  make clean             - Limpiar archivos compilados")
message(STATUS "  make clean-all         - Limpiar completamente el directorio build")
message(STATUS "")