#include <Servo.h>

// ——— Variáveis de estado ———
bool boxTaken    = false;  // já pegou o box?
bool readyToFire = true;   // gatilho armado para nova detecção

// ——— Definições dos servos ———
Servo servo1; // base
Servo servo2; // ombro
Servo servo3; // cotovelo
Servo servo4; // rotação da garra
Servo servo5; // abertura da garra

// ——— Função genérica de movimento suave ———
void moverSuave(Servo &servo, int posInicial, int posFinal, int atraso) {
  if (posInicial < posFinal) {
    for (int i = posInicial; i <= posFinal; i++) {
      servo.write(i);
      delay(atraso);
    }
  } else {
    for (int i = posInicial; i >= posFinal; i--) {
      servo.write(i);
      delay(atraso);
    }
  }
}

// ——— Posicionamentos pré-definidos ———
// servo1 (base)
void servo1_para_frente()   { moverSuave(servo1, servo1.read(), 200, 15); }
void servo1_para_tras()     { moverSuave(servo1, servo1.read(),  50, 15); }
void servo1_para_vertical() { moverSuave(servo1, servo1.read(),  90, 15); }
void servo1_para_deixar()   { moverSuave(servo1, servo1.read(), 120, 15); }

// servo2 (ombro)
void servo2_para_frente()   { moverSuave(servo2, servo2.read(), 170, 15); }
void servo2_para_tras()     { moverSuave(servo2, servo2.read(),   0, 15); }
void servo2_para_vertical(){ moverSuave(servo2, servo2.read(),   75, 15); }

// servo3 (cotovelo)
void servo3_para_frentemais(){ moverSuave(servo3, servo3.read(), 160, 15); }
void servo3_para_frente()   { moverSuave(servo3, servo3.read(),  90, 15); }
void servo3_para_tras()     { moverSuave(servo3, servo3.read(),   0, 15); }

// servo4 (rotação da garra)
void servo4_para_horizontal(){ moverSuave(servo4, servo4.read(), 100, 15); }
void servo4_para_vertical() { moverSuave(servo4, servo4.read(),   0, 15); }

// servo5 (abertura da garra)
void servo5_para_abrir()    { moverSuave(servo5, servo5.read(),   0, 20); }
void servo5_para_fechar()   { moverSuave(servo5, servo5.read(),  60, 10); }

// ——— Sequências de ações ———
void dormir() {
  servo1_para_vertical();
  servo2_para_vertical();
  servo3_para_frente();
  servo4_para_vertical();
  servo5_para_abrir();
}

void pegar_box() {
  servo1_para_vertical();
  servo4_para_horizontal();
  servo5_para_abrir();
  servo2_para_frente();
  servo3_para_frente();
  servo5_para_fechar();
  delay(500);
  servo4_para_vertical();
  servo2_para_vertical();
  servo1_para_tras();
}

void deixar_box() {
  servo1_para_deixar();
  servo3_para_frentemais();
  servo5_para_abrir();
  delay(500);
 
  
  servo1_para_tras();
  
}

// ——— Definição dos pinos ultrassom ———
const int trigEsquerda   = 20, echoEsquerda   = 21;
const int trigDireita    = 14, echoDireita    = 15;
const int trigFrenteCubo = 16, echoFrenteCubo = 17;
const int trigFrenteRobo = 18, echoFrenteRobo = 19;

// ——— Função de leitura ultrassom ———
float medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracao = pulseIn(echoPin, HIGH, 25000);
  if (duracao == 0) return -1; // timeout

  return (duracao / 2.0) * 0.0343;
}

void setup() {
  // Servos
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);

  // Posição inicial
  delay(500);
  dormir();

  // Sensores ultrassom
  pinMode(trigEsquerda,   OUTPUT); pinMode(echoEsquerda,   INPUT);
  pinMode(trigDireita,    OUTPUT); pinMode(echoDireita,    INPUT);
  pinMode(trigFrenteCubo, OUTPUT); pinMode(echoFrenteCubo, INPUT);
  pinMode(trigFrenteRobo, OUTPUT); pinMode(echoFrenteRobo, INPUT);

  Serial.begin(9600);
}

void loop() {
  float dCubo = medirDistancia(trigFrenteCubo, echoFrenteCubo);

  if (dCubo > 0) {
    Serial.print("Distância Cubo: ");
    Serial.print(dCubo, 1);
    Serial.println(" cm");

    // Quando algo entra (< 5 cm) e gatilho ativo:
    if (readyToFire && dCubo < 6.0) {
      if (!boxTaken) {
        pegar_box();
        boxTaken = true;
      } else {
        deixar_box();
        boxTaken = false;
      }
      readyToFire = false;  // desarma até a saída
    }
    // Rearma só quando sai (>= 5 cm)
    else if (!readyToFire && dCubo >= 6.0) {
      readyToFire = true;
    }
  }
  else {
    Serial.println("Leitura falhou");
  }

  delay(50);
}
