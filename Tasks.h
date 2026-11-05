#ifndef Task_h
#define Task_h
/*****************************************************************************************
*      DESCRIPCIÓN DE LA LIBRERÍA:                                                       *
*                                                                                        *
*  El objetivo de esta librería es generar tiempos de espera de ejecución sin usar       *
*  la función "delay()". Se implementa un sistema de tareas basadas en el conteo de      *
*  "millis()", permitiendo la ejecución periódica de funciones sin bloquear el flujo     *
*  del programa.                                                                         *
******************************************************************************************/

// Constantes de tiempo en milisegundos para cada tarea
#define TIEMPO_POT      4000    // Lectura de potenciómetro cada 4 segundos
#define TIEMPO_BUZZ     2000    // Activación de buzzer cada 2 segundos
#define TIEMPO_WARNING  1000    // Verificación de alerta cada 1 segundo
#define TIEMPO_LCD      5000    // Actualización de LCD cada 5 segundos
#define TIEMPO_RTC      1000    // Actualización de reloj cada 1 segundo
#define TIEMPO_MSD      2000    // Guardado en microSD cada 2 segundos
#define TIEMPO_MQTT     5000    // Publicación MQTT cada 5 segundos

// Clase principal que gestiona las tareas basadas en millis()
class millis_tasks {

  public:
    // Variables de control de tiempo para cada tarea
      uint64_t  tiempo_anterior_pot        = 0,   // Última lectura de potenciómetro
                tiempo_anterior_buzz       = 0,   // Última activación del buzzer
                tiempo_anterior_buzzwarning= 0,   // Última verificación de alerta
                tiempo_anterior_lcd        = 0,   // Última actualización de LCD
                tiempo_anterior_rtc        = 0,   // Última actualización de RTC
                tiempo_anterior_msd        = 0,   // Última escritura en microSD
                tiempo_anterior_mqtt       = 0,   // Última publicación MQTT
                tiempo_actual              = 0;   // Tiempo actual obtenido de millis()

  public:
    // Métodos que representan las tareas periódicas
    void tarea_pot ( void );          // Lectura del potenciómetro
    void tarea_buzz ( void );         // Activación del buzzer
    void tarea_buzzwarning ( void );  // Verificación de alerta con buzzer
    void tarea_lcd ( void );          // Actualización de LCD
    void tarea_rtc ( void );          // Actualización del RTC
    void tarea_msd ( void );          // Guardado en microSD
    void tarea_mqtt ( void );         // Publicación en MQTT
    void actualizar_tareas ( void );  // Actualiza el contador de millis()
};

/*~~~~~~~~~~~~~~~~~~~~~~~~ 1.- tarea_pot - Lectura periódica del potenciómetro ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: tarea_pot ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_pot ) >= TIEMPO_POT ) {
     Serial.print ( "1.- Ejecutando tarea pot: " );
     Serial.println ( SEN.get_potV() );   // Lectura del valor del potenciómetro
     tiempo_anterior_pot = tiempo_actual;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~ 2.- tarea_buzz - Activación periódica del buzzer ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: tarea_buzz ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_buzz ) >= TIEMPO_BUZZ ) {
     Serial.println ( "2.- Ejecutando tarea buzzer" );
     ACT.play_buzzer();   // Activar buzzer
     tiempo_anterior_buzz = tiempo_actual;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~ 3.- tarea_buzzwarning - Verificación de alerta con buzzer ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: tarea_buzzwarning ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_buzzwarning ) >= TIEMPO_WARNING ) {
     Serial.print ( "3.- Ejecutando tarea buzzer warning: " );
     Serial.println ( SEN.get_potV() );
     tiempo_anterior_buzzwarning = tiempo_actual;

     // Si el potenciómetro supera el umbral, activar buzzer y registrar alerta
     if ( SEN.get_potV() >= 1500 ) {
       ACT.play_buzzer(); 
       MIRTC.get_time();
       SEN.fecha_pot = MIRTC.format_date();
       SEN.hora_pot  = MIRTC.format_time();    
       SEN.warning_pot = true;
     }
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~ 4.- tarea_lcd - Actualización periódica de la pantalla LCD ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: tarea_lcd ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_lcd ) >= TIEMPO_LCD ) {
     Serial.println ( "4.- Ejecutando tarea LCD" );
     // LCD.print("Hola");   // Ejemplo de impresión en pantalla
     tiempo_anterior_lcd = tiempo_actual;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~ 5.- tarea_rtc - Actualización periódica del reloj RTC ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: tarea_rtc ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_rtc ) >= TIEMPO_RTC ) {
     Serial.println ( "5.- Ejecutando tarea RTC" );
     MIRTC.get_time();      // Obtener hora actual
     MIRTC.show_time();     // Mostrar hora en consola
     tiempo_anterior_rtc = tiempo_actual;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~ 6.- actualizar_tareas - Actualiza el contador de millis() ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: actualizar_tareas ( void ) {
  tiempo_actual = millis();   // Actualizar tiempo actual
}

/*~~~~~~~~~~~~~~~~~~~~~~~~ 7.- tarea_msd - Guardado periódico en microSD ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: tarea_msd ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_msd ) >= TIEMPO_MSD ) {
     Serial.println ( "6.- Ejecutando tarea MSD" );
     MSD.SaveFile ( JSON_fac.make_json ( MIRTC.format_time(), MIRTC.format_date(), SEN.get_potV(), false ) );  
     tiempo_anterior_msd = tiempo_actual;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~ 8.- tarea_mqtt - Publicación periódica en servidor MQTT ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: tarea_mqtt ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_mqtt ) >= TIEMPO_MQTT ) {
    MIRTC.get_time();
    Serial.println ( "7.- Ejecutando tarea MQTT" );
     
    // Si existe una alerta de potenciómetro, publicar con advertencia
    if ( SEN.warning_pot ) {
      mqtt.publish_MQTT ( JSON_fac.make_json ( SEN.hora_pot, SEN.fecha_pot, SEN.get_potV(), true ) );
      MSD.SaveFile ( JSON_fac.make_json ( MIRTC.format_time(), MIRTC.format_date(), SEN.get_potV(), true ) );
      SEN.warning_pot = false;
      SEN.fecha_pot   = "";
      SEN.hora_pot    = "";
    }
    else {
      mqtt.publish_MQTT ( JSON_fac.make_json ( MIRTC.format_time(), MIRTC.format_date(), SEN.get_potV(), false ) );
      MSD.SaveFile ( JSON_fac.make_json ( MIRTC.format_time(), MIRTC.format_date(), SEN.get_potV(), false ) );
    }

    tiempo_anterior_mqtt = tiempo_actual;
  }
}

#endif
