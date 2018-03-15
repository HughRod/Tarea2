/*
Programa que hace que LED parpadee al detectar
que la puerta se abre. Logrado con la detección
de un campo magnético generado a un reed switch.

Autor: Hugo Rodrigo Murillo Martínez
*/

/*IMPORTAR BIBLIOTECA QUE AYUDA A REDUCIR CONSUMO DE ENERGÍA*/
#include "LowPower.h"

/*DECLARAR VARIABLES*/
int CONTACTO = 2;                   // PIN ASIGNADO AL REED SWITCH
int LED = 13;                       // PIN ASIGNADO AL LED
boolean ALARMA_ENCENDIDA = false;   // BANDERA QUE CAMBIA CADA QUE SE ENCIENDE O NO LA ALARMA

void setup() {
  pinMode(CONTACTO, INPUT);         // CONFIGURAR EL REED SWITCH COMO ENTRADA
  pinMode(LED, OUTPUT);             // CONFIGURAR EL LED COMO SALIDA
  Serial.begin(9600);               // INICIAR COMUNICACIÓN SERIAL
}

void loop() {
  if (digitalRead(CONTACTO) == LOW) {     // SI SE DETECTA EL IMÁN CERCA
    ALARMA_ENCENDIDA = true;              // CAMBIA A TRUE LA BANDERA
    
    // CICLO FOR QUE VA DE 0 A 50, EL CONTADOR ES LA VARIABLE I
    // QUE SE REPITE MIENTRAS SEA MENOR A 50
    for (int i = 0; i < 50; i++) {
      digitalWrite(LED, HIGH);            // ENCIENDE EL LED
      delay(50);                          // TIEMPO DE RETARDO
      digitalWrite(LED, LOW);             // APAGA EL LED
      delay(50);                          // TIEMPO DE RETARDO
    }
  } else {                                // SI NO SE DETECTA EL IMÁN CERCA
    ALARMA_ENCENDIDA = false;             // CAMBIAR LA BANDERA A FALSE
    digitalWrite(LED, LOW);               // APAGAR EL LED

    /* DORMIR EL ARDUINO POR 4 SEGUNDOS.
     *  ADC_OFF APAGA LOS CONVERTIDORES ANALÓGICO A DIGITAL
     *  BOD_OFF APAGA EL CIRCUITO DE BROWN OUT DETECTION, QUE ES UN CIRCUITO 
     *  PARA DETECTAR NIVELES PELIGROSAMENTE BAJOS DE TENSIÓN.
    */
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
  }

  if(ALARMA_ENCENDIDA)                    // SI LA VARIABLE ES TRUE
    Serial.println("Intruso en casa.");   // IMPRIMIR 'INTRUSO EN CASA'
}

