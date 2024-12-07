#include <Arduino.h>
#include "HX711.h"

#define DOUT 4
#define SCK 5
HX711 scale;

void setup() {
  Serial.begin(115200);
  scale.begin(DOUT, SCK);

  Serial.println("Calibración del sensor de peso:");
  
  // Ajustar el sensor a cero (sin peso)
  Serial.println("Retira cualquier peso del sensor y presiona cualquier tecla...");
  while (!Serial.available());
  scale.tare(); // Configurar el punto cero
  Serial.println("Tara completada.");

  // Determinar la constante de escala
  Serial.println("Coloca un peso conocido en el sensor y escribe su valor en gramos:");
  while (!Serial.available());
  float pesoConocido = Serial.parseFloat(); // Leer el peso ingresado
  Serial.println("Midiendo...");
  delay(2000); // Esperar para estabilizar la lectura
  long valorEnBruto = scale.get_units(10); // Promediar 10 lecturas
  float constanteDeEscala = valorEnBruto / pesoConocido;
  
  Serial.print("Constante de escala calculada: ");
  Serial.println(constanteDeEscala);

  // Guardar la constante en el código o memoria para uso futuro
  scale.set_scale(constanteDeEscala);
  Serial.println("Calibración completada.");
}

void loop() {
  // Lectura continua del peso
  float peso = scale.get_units();
  Serial.print("Peso: ");
  Serial.print(peso);
  Serial.println(" g");
  delay(500);
}
