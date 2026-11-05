#ifndef Sensor_h
#define Sensor_h 

// ============================================================================
//  Configuración del módulo de sensores
//  Este archivo define la clase "sensores" para la lectura del potenciómetro
//  y el manejo de advertencias relacionadas con valores críticos.
// ============================================================================

// Pin analógico donde está conectado el potenciómetro
#define Pot_pin   34    

// Valor máximo permitido para el potenciómetro antes de generar advertencia
#define MAXVALUE  1500  

// ============================================================================
//  Clase sensores
//  Contiene variables y métodos para:
//   - Leer el valor del potenciómetro
//   - Configurar el pin de entrada
//   - Almacenar fecha y hora de advertencias
// ============================================================================
class sensores {

  public:
    // Variables de estado
    uint16_t pot;                 // Valor leído del potenciómetro
    String hora_pot   = "";       // Hora en la que se detectó advertencia
    String fecha_pot  = "";       // Fecha en la que se detectó advertencia
    bool warning_pot  = false;    // Bandera que indica si hubo advertencia

  public:
    // Métodos principales
    uint16_t get_potV ( void );   // Devuelve el valor leído del potenciómetro
    void config ( void );         // Configura el pin y el RTC
};

// ============================================================================
//  Método: get_potV()
//  Devuelve el valor leído del potenciómetro en el pin definido.
// ============================================================================
uint16_t sensores :: get_potV ( void ) {
  return analogRead ( Pot_pin );   // Lectura analógica del pin
}

// ============================================================================
//  Método: config()
//  Configura el pin del potenciómetro como entrada y inicializa el RTC.
// ============================================================================
void sensores :: config ( void ) {
  pinMode ( Pot_pin, INPUT );      // Configurar pin como entrada
  //MIRTC.RTC_init();                // Inicializar el reloj RTC
}

#endif
