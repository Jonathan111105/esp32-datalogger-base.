/*☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄
☄                                                                            ☄
☄      ☘ DATOS GENERALES:                                                    ☄
☄      NOMBRE:      Sistema Datalogger IoT modular con ESP32.                ☄
☄      FECHA:       21 de marzo de 2026.                                     ☄
☄      VERSIÓN:     1.0.                                                     ☄
☄                                                                            ☄
☄      AUTOR:       M. en C. Esli Castellanos Berján.                        ☄
☄      E-MAIL:      esli_castellanos@ucol.mx                                 ☄
☄      COMPAÑÍA:    Universidad de Colima - Facultad de Telemática.          ☄
☄                                                                            ☄
☄      uC:          ESP32-D0WD Dual Core.                                    ☄
☄      Nombre:      ESP32-S.                                                 ☄
☄                                                                            ☄
☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄
☄                                                                            ☄
☄      ☘ DESCRIPCIÓN DEL PROGRAMA:                                           ☄
☄      El sistema es un datalogger IoT modular que:                          ☄
☄        - Lee valores de un potenciómetro mediante ADC.                     ☄
☄        - Registra datos en una tarjeta MicroSD en formato JSON.            ☄
☄        - Obtiene fecha y hora desde un RTC DS1307.                         ☄
☄        - Publica información en un broker MQTT para telemetría remota.     ☄
☄        - Muestra mensajes en una pantalla LCD.                             ☄
☄        - Activa un buzzer cuando se detectan valores críticos.             ☄
☄        - Gestiona todas las tareas con millis() evitando bloqueos.         ☄
☄                                                                            ☄
☄      Es útil en proyectos de monitoreo ambiental, control industrial,      ☄
☄      sistemas educativos y aplicaciones IoT donde se requiere registro,    ☄
☄      transmisión y alerta de datos en tiempo real.                         ☄
☄                                                                            ☄
☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄
☄                                                                            ☄
☄      ☘ NOTAS:                                                             ☄
☄      - El sistema está diseñado de forma modular, cada componente          ☄
☄        (Sensores, Actuadores, RTC, MicroSD, MQTT, JSON, Tasks) se          ☄
☄        encuentra en un archivo independiente para facilitar mantenimiento. ☄
☄      - El uso de millis() permite ejecución paralela sin bloquear el loop. ☄
☄      - La arquitectura facilita la escalabilidad y reutilización en otros  ☄
☄        proyectos.                                                          ☄
☄                                                                            ☄
☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄☄*/
