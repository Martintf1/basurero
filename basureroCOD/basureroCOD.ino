#include <Servo.h>
#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>

// Objetos
TMRpcm tmrpcm;
Servo servo1;
Servo servo2;

// Pines sensores
const int trigPin1 = 9;
const int echoPin1 = A0;

const int trigPin2 = 7;
const int echoPin2 = 8;

// Pin CS lector SD
const int SD_CS = 4;

// Estado de la tarjeta SD
bool sdDisponible = false;

void setup() {
  Serial.begin(9600);

  // Configurar servos
  servo1.attach(6);
  servo2.attach(5);
  servo1.write(0);
  servo2.write(0);

  // Configurar sensores
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Inicializar tarjeta SD
  if (!SD.begin(SD_CS)) {
    Serial.println(" No se pudo inicializar la tarjeta SD.");
    sdDisponible = false;
  } else {
    Serial.println("Tarjeta SD lista.");
    sdDisponible = true;
    tmrpcm.speakerPin = 10;  // Salida de audio
    tmrpcm.setVolume(6);     // Volumen entre 0 y 7
  }
}

// Función para medir distancia con sensor ultrasónico
int medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH, 30000);  // timeout de 30ms
  int distancia = duracion * 0.034 / 2;
  return distancia;
}

void loop() {
  // Sensor 1 y Servo 1

  int distancia1 = medirDistancia(trigPin1, echoPin1);
  Serial.print("Distancia Sensor 1: ");
  Serial.print(distancia1);
  Serial.print(" cm\t");

  if (distancia1 > 0 && distancia1 < 10 && !tmrpcm.isPlaying()) {
    servo1.write(90);
    //  if (sdDisponible) {
    // tmrpcm.play("SONIDO1.WAV");
    // }
    delay(3000);  // Espera a que termine el sonido
    servo1.write(0);
  }

  // Sensor 2 y Servo 2
  int distancia2 = medirDistancia(trigPin2, echoPin2);
  Serial.print("Distancia Sensor 2: ");
  Serial.print(distancia2);
  Serial.println(" cm");

  if (distancia2 > 0 && distancia2 < 10 && !tmrpcm.isPlaying()) {
    servo2.write(90);
    //if (sdDisponible) {
    //  tmrpcm.play("SONIDO2.WAV");
    //}
    delay(3000);
    servo2.write(0);
  }

  delay(200);  // Pequeña pausa
}
