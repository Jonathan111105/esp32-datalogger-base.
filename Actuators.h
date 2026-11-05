#ifndef Actuators_h
#define Actuators_h

// ============================================================================
//  Librerías necesarias para el manejo de periféricos
//  - Wire: comunicación I2C
//  - LiquidCrystal_I2C: control de pantallas LCD mediante I2C
// ============================================================================
#include <Wire.h>               
#include <LiquidCrystal_I2C.h>  

// Crear objeto LCD con dirección I2C 0x27, 16 columnas y 2 filas
LiquidCrystal_I2C lcd ( 0x27, 16, 2 ); 

// Pin digital donde está conectado el buzzer
#define buzz_pin 2

// ============================================================================
//  Clase actuadores
//  Contiene métodos para:
//   - Configurar periféricos (LCD y buzzer)
//   - Activar el buzzer con un tono
//   - Imprimir texto en la pantalla LCD
// ============================================================================
class actuadores {
  public:
    void config ( void );                        // Configura buzzer y LCD
    void play_buzzer ( void );                   // Activa buzzer con un tono
    void imprimirtxt ( String f1, String f2 );   // Imprime dos líneas de texto en LCD
};

// ============================================================================
//  Método: config()
//  Configura el pin del buzzer como salida y prepara la pantalla LCD.
//  Inicializa la LCD, enciende la retroiluminación y muestra un mensaje inicial.
// ============================================================================
void actuadores :: config ( void ) {
  pinMode ( buzz_pin, OUTPUT );   // Configurar buzzer como salida
  lcd.init ( );                   // Inicializar LCD
  lcd.backlight ( );              // Encender retroiluminación
  lcd.setCursor ( 0, 0 );         // Posicionar cursor en primera línea
  lcd.print ( "Hola mundo" );     // Mensaje inicial
}

// ============================================================================
//  Método: play_buzzer()
//  Activa el buzzer con un tono de 262 Hz durante 500 ms.
// ============================================================================
void actuadores :: play_buzzer ( void ) {
  tone ( buzz_pin, 262, 500 );    // Generar tono en buzzer
}

// ============================================================================
//  Método: imprimirtxt()
//  Imprime dos cadenas de texto en la pantalla LCD.
//  - f1: texto en la primera línea
//  - f2: texto en la segunda línea
// ============================================================================
void actuadores :: imprimirtxt ( String f1, String f2 ) {
  lcd.clear();                    // Limpiar pantalla
  lcd.setCursor ( 0, 0 );         // Posicionar cursor en primera línea
  lcd.print ( f1 );               // Imprimir primera cadena
  lcd.setCursor ( 0, 1 );         // Posicionar cursor en segunda línea
  lcd.print ( f2 );               // Imprimir segunda cadena
}

#endif
