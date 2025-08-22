#include <Wire.h>

#define I2C_ADDRESS 0x08
#define LED_PIN     13

volatile uint8_t valor_para_resposta = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);
  Wire.begin(I2C_ADDRESS);

  Wire.onReceive(recebeuI2C);
  Wire.onRequest(onRequestFromMaster);
  Serial.println("I2C Slave simplificado pronto");
}

void loop() {
  delay(10);
}

void recebeuI2C(int bytesDisponiveis) {
  if (Wire.available()) {
    uint8_t cmd = Wire.read();
    Serial.print("Recebido: ");
    Serial.println(cmd);

    switch(cmd) {
      case 0: digitalWrite(LED_PIN, LOW); valor_para_resposta = 0; break;
      case 1: digitalWrite(LED_PIN, HIGH); valor_para_resposta = 1; break;
      case 2: valor_para_resposta = 42; break; // valor fictício do sensor
    }
  }
}

void onRequestFromMaster() {
  Wire.write(valor_para_resposta); // envia último valor ou sensor
  Serial.print("Enviado: ");
  Serial.println(valor_para_resposta);
}
