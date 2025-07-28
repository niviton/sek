#include <Servo.h>

Servo servo1; // base
Servo servo2; // ombro
Servo servo3; // cotovelo
Servo servo4; // rotação garra
Servo servo5; // abertura da garra

// Função genérica de movimento suave
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

// Funções renomeadas para servo1
void servo1_para_frente()   { moverSuave(servo1, servo1.read(), 200, 15); }
void servo1_para_tras()     { moverSuave(servo1, servo1.read(),   50, 15); }
void servo1_para_vertical() { moverSuave(servo1, servo1.read(),  90, 15); }
void servo1_para_deixar() { moverSuave(servo1, servo1.read(),  120, 15); }

// Funções renomeadas para servo2
void servo2_para_frente()   { moverSuave(servo2, servo2.read(), 170, 15); }
void servo2_para_tras()     { moverSuave(servo2, servo2.read(),   0, 15); }
void servo2_para_vertical() { moverSuave(servo2, servo2.read(),  75, 15); }

// Funções renomeadas para servo3
void servo3_para_frentemais()   { moverSuave(servo3, servo3.read(), 160, 15); }
void servo3_para_frente()     { moverSuave(servo3, servo3.read(),  90, 15); }
void servo3_para_tras()     { moverSuave(servo3, servo3.read(),   0, 15); }

// Funções renomeadas para servo4
void servo4_para_horizontal(){ moverSuave(servo4, servo4.read(), 100, 15); }
void servo4_para_vertical()  { moverSuave(servo4, servo4.read(),   0, 15); }

// Funções renomeadas para servo5
void servo5_para_abrir()    { moverSuave(servo5, servo5.read(),   0, 20); }
void servo5_para_fechar()   { moverSuave(servo5, servo5.read(),  60, 10); }

// Sequência “dormir”
void dormir() {
  servo1_para_vertical();
  servo2_para_vertical();
  servo3_para_frente();
  servo4_para_vertical();
  servo5_para_abrir();
}
void pegar_box(){
  servo1_para_vertical();
 servo4_para_horizontal();
servo5_para_abrir();
servo2_para_frente();
servo3_para_frente();
 servo5_para_fechar();
 delay(1000);
 servo4_para_vertical();
 servo2_para_vertical();
servo1_para_tras();
}
void andar(){
  servo1_para_vertical();
  servo2_para_tras();
  servo3_para_frente();
  servo4_para_vertical();
  servo5_para_fechar();
}
void deixar_box(){
  servo1_para_deixar();
  servo3_para_frentemais();
  servo5_para_abrir();
  
}

void setup() {
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);


  
  delay(500);
  //dormir();
  pegar_box();
  deixar_box();
 
}

void loop() {
 


 
   
}