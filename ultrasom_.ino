// Definição dos pinos de cada sensor
const int trigEsquerda = 20;
const int echoEsquerda = 21;

const int trigDireita = 14;
const int echoDireita = 15;

const int trigFrenteCubo = 16;
const int echoFrenteCubo = 17;

const int trigFrenteRobo = 18;
const int echoFrenteRobo = 19;

float distanciaEsquerda = 0;
float distanciaDireita = 0;
float distanciaFrenteCubo = 0;
float distanciaFrenteRobo = 0;

void setup() {
  // Configura os pinos como entrada/saída
  pinMode(trigEsquerda, OUTPUT);
  pinMode(echoEsquerda, INPUT);
  
  pinMode(trigDireita, OUTPUT);
  pinMode(echoDireita, INPUT);

  pinMode(trigFrenteCubo, OUTPUT);
  pinMode(echoFrenteCubo, INPUT);

  pinMode(trigFrenteRobo, OUTPUT);
  pinMode(echoFrenteRobo, INPUT);

  Serial.begin(9600);
}

// Função genérica para medir distância de um par TRIG/ECHO
float medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracao = pulseIn(echoPin, HIGH, 25000); // timeout de 25ms
  float distancia = (duracao / 2.0) * 0.0343;

  if (duracao == 0) return -1; // falha na leitura
  return distancia;
}

void loop() {
  distanciaEsquerda = medirDistancia(trigEsquerda, echoEsquerda);
  distanciaDireita = medirDistancia(trigDireita, echoDireita);
  distanciaFrenteCubo = medirDistancia(trigFrenteCubo, echoFrenteCubo);
  distanciaFrenteRobo = medirDistancia(trigFrenteRobo, echoFrenteRobo);

  Serial.print("Esquerda: ");
  Serial.print(distanciaEsquerda);
  Serial.print(" cm | Direita: ");
  Serial.print(distanciaDireita);
  Serial.print(" cm | Frente Cubo: ");
  Serial.print(distanciaFrenteCubo);
  Serial.print(" cm | Frente Robo: ");
  Serial.print(distanciaFrenteRobo);
  Serial.println(" cm");

  delay(500);
}
