#ifndef JSONS_H
#define JSONS_H

// ============================================================================
//  Clase JSON_Factory
//  Esta clase se encarga de generar un objeto JSON con información de fecha,
//  hora, valor del potenciómetro y, opcionalmente, una advertencia.
//  Utiliza la librería ArduinoJson para crear y serializar el documento.
// ============================================================================

class JSON_Factory {
  public:
    // Método que construye un JSON con los parámetros recibidos
    String make_json ( String hora, String fecha, int pot, bool warning );
};

// ============================================================================
//  Método: make_json()
//  Parámetros:
//    - hora: cadena con la hora actual
//    - fecha: cadena con la fecha actual
//    - pot: valor leído del potenciómetro
//    - warning: bandera booleana que indica si se debe incluir advertencia
//
//  Funcionamiento:
//    1. Crea un documento JSON dinámico con capacidad de 1024 bytes.
//    2. Inserta la fecha, hora y valor del potenciómetro.
//    3. Si la bandera warning es verdadera, añade un objeto "advertencia"
//       con la fecha y hora del evento crítico almacenadas en SEN.
//    4. Serializa el documento en una cadena y la imprime por Serial.
//    5. Devuelve la cadena JSON generada.
// ============================================================================
String JSON_Factory :: make_json ( String hora, String fecha, int pot, bool warning ) {
  DynamicJsonDocument doc ( 1024 );   // Documento JSON dinámico con buffer de 1024 bytes
  String temp = "";                   // Cadena temporal para almacenar el JSON serializado

  // Asignar valores principales
  doc["fecha"] = fecha;
  doc["hora"] = hora;
  doc["potenciometro"] = pot;

  // Si existe advertencia, crear objeto anidado
  if ( warning ) {
    JsonObject advertencia = doc.createNestedObject ( "advertencia" );
    advertencia["fecha"] = SEN.fecha_pot;   // Fecha del evento crítico
    advertencia["hora"]  = SEN.hora_pot;    // Hora del evento crítico
  }

  // Serializar el documento JSON en la cadena temp
  serializeJson ( doc, temp );
  Serial.println ( temp );   // Mostrar el JSON generado en consola serial

  return temp;   // Retornar el JSON como String
};

#endif
