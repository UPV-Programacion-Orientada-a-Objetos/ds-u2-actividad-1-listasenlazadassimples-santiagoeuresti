/*
 * Simulador Arduino para Sistema de Gestión Polimórfica de Sensores IoT
 * Archivo: arduino_simulador.ino
 * Autor: Santiago Euresti
 * Fecha: 30 de octubre de 2024
 * 
 * Este programa simula el envío de datos de sensores a través del puerto serial
 * para ser leídos por el sistema principal de gestión de sensores.
 * 
 * Formato de datos enviados:
 * - TEMP:<nombre_sensor>:<valor_float>
 * - PRES:<nombre_sensor>:<valor_int>
 */

// Configuración del sistema
const unsigned long INTERVALO_ENVIO = 2000;  // Envío cada 2 segundos
const int NUM_SENSORES_TEMP = 2;              // Número de sensores de temperatura
const int NUM_SENSORES_PRES = 2;              // Número de sensores de presión

// Variables para el control de tiempo
unsigned long ultimoEnvio = 0;
int contadorCiclo = 0;

// Nombres de los sensores simulados
const char* sensoresTemp[NUM_SENSORES_TEMP] = {"T-001", "T-002"};
const char* sensoresPres[NUM_SENSORES_PRES] = {"P-105", "P-106"};

// Rangos de valores para simulación
const float TEMP_MIN = 15.0;
const float TEMP_MAX = 45.0;
const int PRES_MIN = 70;
const int PRES_MAX = 110;

/**
 * @brief Configuración inicial del Arduino
 */
void setup() {
  // Inicializar comunicación serial
  Serial.begin(9600);
  
  // Inicializar generador de números aleatorios
  randomSeed(analogRead(0));
  
  // Esperar a que se establezca la conexión serial
  delay(1000);
  
  // Mensaje de inicio
  Serial.println("=== SIMULADOR ARDUINO - SENSORES IoT ===");
  Serial.println("Iniciando simulación de sensores...");
  Serial.println("Formato: TIPO:NOMBRE:VALOR");
  Serial.println("TEMP = Temperatura (float)");
  Serial.println("PRES = Presión (int)");
  Serial.println("=====================================");
  
  delay(2000);
}

/**
 * @brief Bucle principal del programa
 */
void loop() {
  unsigned long tiempoActual = millis();
  
  // Verificar si es tiempo de enviar datos
  if (tiempoActual - ultimoEnvio >= INTERVALO_ENVIO) {
    enviarDatosSensores();
    ultimoEnvio = tiempoActual;
    contadorCiclo++;
    
    // Mostrar información de estado cada 10 ciclos
    if (contadorCiclo % 10 == 0) {
      Serial.println("--- Estado del Sistema ---");
      Serial.print("Ciclos completados: ");
      Serial.println(contadorCiclo);
      Serial.print("Tiempo activo: ");
      Serial.print(millis() / 1000);
      Serial.println(" segundos");
      Serial.println("-------------------------");
    }
  }
  
  // Verificar si hay comandos desde el puerto serial
  procesarComandosSerial();
  
  // Pequeña pausa para evitar saturar el procesador
  delay(50);
}

/**
 * @brief Envía datos simulados de todos los sensores
 */
void enviarDatosSensores() {
  Serial.println("\n>>> Enviando datos de sensores <<<");
  
  // Enviar datos de sensores de temperatura
  for (int i = 0; i < NUM_SENSORES_TEMP; i++) {
    enviarDatosTemperatura(sensoresTemp[i]);
    delay(100);  // Pequeña pausa entre envíos
  }
  
  // Enviar datos de sensores de presión
  for (int i = 0; i < NUM_SENSORES_PRES; i++) {
    enviarDatosPresion(sensoresPres[i]);
    delay(100);  // Pequeña pausa entre envíos
  }
  
  Serial.println(">>> Fin del ciclo de envío <<<\n");
}

/**
 * @brief Genera y envía datos de temperatura para un sensor específico
 * @param nombreSensor Nombre del sensor de temperatura
 */
void enviarDatosTemperatura(const char* nombreSensor) {
  // Generar temperatura aleatoria con variación realista
  float temperatura = generarTemperaturaAleatoria();
  
  // Enviar en formato: TEMP:nombre:valor
  Serial.print("TEMP:");
  Serial.print(nombreSensor);
  Serial.print(":");
  Serial.println(temperatura, 1);  // 1 decimal de precisión
  
  // Log local para depuración
  Serial.print("[LOG] Temp enviada: ");
  Serial.print(nombreSensor);
  Serial.print(" = ");
  Serial.print(temperatura, 1);
  Serial.println("°C");
}

/**
 * @brief Genera y envía datos de presión para un sensor específico
 * @param nombreSensor Nombre del sensor de presión
 */
void enviarDatosPresion(const char* nombreSensor) {
  // Generar presión aleatoria dentro del rango
  int presion = generarPresionAleatoria();
  
  // Enviar en formato: PRES:nombre:valor
  Serial.print("PRES:");
  Serial.print(nombreSensor);
  Serial.print(":");
  Serial.println(presion);
  
  // Log local para depuración
  Serial.print("[LOG] Presión enviada: ");
  Serial.print(nombreSensor);
  Serial.print(" = ");
  Serial.print(presion);
  Serial.println(" bar");
}

/**
 * @brief Genera una temperatura aleatoria con variación realista
 * @return Valor de temperatura simulada
 */
float generarTemperaturaAleatoria() {
  // Generar variación base
  float temperatura = random(TEMP_MIN * 10, TEMP_MAX * 10) / 10.0;
  
  // Añadir pequeña variación decimal para mayor realismo
  float variacion = random(-5, 6) / 10.0;  // Variación de ±0.5°C
  temperatura += variacion;
  
  // Asegurar que esté dentro del rango
  if (temperatura < TEMP_MIN) temperatura = TEMP_MIN;
  if (temperatura > TEMP_MAX) temperatura = TEMP_MAX;
  
  return temperatura;
}

/**
 * @brief Genera una presión aleatoria dentro del rango especificado
 * @return Valor de presión simulada
 */
int generarPresionAleatoria() {
  return random(PRES_MIN, PRES_MAX + 1);
}

/**
 * @brief Procesa comandos recibidos desde el puerto serial
 */
void procesarComandosSerial() {
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();  // Eliminar espacios en blanco
    
    if (comando.equalsIgnoreCase("STATUS")) {
      mostrarEstadoSistema();
    }
    else if (comando.equalsIgnoreCase("RESET")) {
      reiniciarContadores();
    }
    else if (comando.equalsIgnoreCase("HELP")) {
      mostrarAyuda();
    }
    else if (comando.equalsIgnoreCase("TEST")) {
      ejecutarPruebaManual();
    }
    else if (comando.length() > 0) {
      Serial.print("Comando no reconocido: ");
      Serial.println(comando);
      Serial.println("Escriba HELP para ver comandos disponibles");
    }
  }
}

/**
 * @brief Muestra el estado actual del sistema simulador
 */
void mostrarEstadoSistema() {
  Serial.println("\n=== ESTADO DEL SIMULADOR ===");
  Serial.print("Ciclos completados: ");
  Serial.println(contadorCiclo);
  Serial.print("Tiempo activo: ");
  Serial.print(millis() / 1000);
  Serial.println(" segundos");
  Serial.print("Intervalo de envío: ");
  Serial.print(INTERVALO_ENVIO);
  Serial.println(" ms");
  Serial.print("Sensores de temperatura: ");
  Serial.println(NUM_SENSORES_TEMP);
  Serial.print("Sensores de presión: ");
  Serial.println(NUM_SENSORES_PRES);
  Serial.println("============================\n");
}

/**
 * @brief Reinicia los contadores del sistema
 */
void reiniciarContadores() {
  contadorCiclo = 0;
  Serial.println("Contadores reiniciados.");
}

/**
 * @brief Muestra la ayuda con comandos disponibles
 */
void mostrarAyuda() {
  Serial.println("\n=== COMANDOS DISPONIBLES ===");
  Serial.println("STATUS  - Mostrar estado del sistema");
  Serial.println("RESET   - Reiniciar contadores");
  Serial.println("HELP    - Mostrar esta ayuda");
  Serial.println("TEST    - Ejecutar prueba manual");
  Serial.println("============================\n");
}

/**
 * @brief Ejecuta una prueba manual de envío de datos
 */
void ejecutarPruebaManual() {
  Serial.println("\n=== PRUEBA MANUAL ===");
  Serial.println("Enviando datos de prueba...");
  
  enviarDatosTemperatura("TEST-T");
  delay(200);
  enviarDatosPresion("TEST-P");
  
  Serial.println("Prueba completada.");
  Serial.println("===================\n");
}

/**
 * @brief Función auxiliar para simular fallos ocasionales (opcional)
 */
void simularFallosOcasionales() {
  // 1% de probabilidad de simular un fallo
  if (random(1, 101) == 1) {
    Serial.println("[ERROR] Fallo simulado en sensor");
    delay(500);
  }
}