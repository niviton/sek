#include <Wire.h>

#define I2C_ADDRESS 0x08
#define LED_PIN     13

volatile bool recebeu = false;
volatile uint8_t ultimoValor = 0;

void setup() {
  // Inicializa LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Inicializa Serial para debug (opcional)
  Serial.begin(9600);
  Serial.println("I2C Slave Test iniciado");

  // Inicializa I2C como escravo
  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(recebeuI2C);
}

void loop() {
  if (recebeu) {
    recebeu = false;
    // Pisca LED uma vez
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);

    // Mostra no serial o valor recebido
    Serial.print("Recebido via I2C: ");
    Serial.println(ultimoValor);
  }
}

// Handler chamado sempre que o mestre envia dados
void recebeuI2C(int bytesDisponiveis) {
  if (Wire.available()) {
    ultimoValor = Wire.read();
    recebeu = true;
  }
}
