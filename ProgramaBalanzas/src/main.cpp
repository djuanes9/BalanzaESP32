#include <Arduino.h>
#include "HX711.h"

// Pines de los sensores HX711
#define DOUT1 4
#define SCK1 5
#define DOUT2 16
#define SCK2 17

// Pines DAC para salida analógica
#define DAC1 25
#define DAC2 26

HX711 scale1;
HX711 scale2;

// Constantes de escala calibradas para cada sensor
const float constanteDeEscala1 = 100.0; // Sustituir con la constante obtenida para el primer sensor
const float constanteDeEscala2 = 102.5; // Sustituir con la constante obtenida para el segundo sensor

void setup() {
  Serial.begin(115200);

  // Inicializar sensores
  scale1.begin(DOUT1, SCK1);
  scale2.begin(DOUT2, SCK2);

  scale1.set_scale(constanteDeEscala1);
  scale2.set_scale(constanteDeEscala2);

  scale1.tare();
  scale2.tare();

  Serial.println("Sensores listos.");
}

void loop() {
  // Leer el peso de cada sensor
  float peso1 = scale1.get_units();
  float peso2 = scale2.get_units();

  // Mostrar los pesos en el monitor serial
  Serial.print("Peso Sensor 1: ");
  Serial.print(peso1);
  Serial.println(" g");
  Serial.print("Peso Sensor 2: ");
  Serial.print(peso2);
  Serial.println(" g");

  // Convertir el peso a valores DAC (0-255 para ESP32)
  int dacValue1 = map(peso1, 0, 1000, 0, 255); // Ajustar el rango según tu escala
  int dacValue2 = map(peso2, 0, 1000, 0, 255);

  // Asegurarse de que los valores estén dentro del rango permitido
  dacValue1 = constrain(dacValue1, 0, 255);
  dacValue2 = constrain(dacValue2, 0, 255);

  // Enviar valores a las salidas DAC
  dacWrite(DAC1, dacValue1);
  dacWrite(DAC2, dacValue2);

  delay(500); // Actualización cada 500 ms
}
