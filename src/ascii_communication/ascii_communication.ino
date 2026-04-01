#include <AccelStepper.h>

// Configuração dos pinos do Driver A4988 / DRV8825
const int stepPin = 3;
const int dirPin = 4;

// Interface 1 significa que usamos um Driver (Step/Dir)
AccelStepper stepper(1, stepPin, dirPin);

// --- PARÂMETROS DO PROJETO ---
const int passosPorVolta = 200;      // Padrão Nema 17 (1.8° por passo)
const int totalPosicoes = 17;        // 0 (Home) + 16 Caracteres
const float grausPorPosicao = 360.0 / (totalPosicoes - 1); // 22.5° por salto

void setup() {
  Serial.begin(9600);
  
  // Configurações de performance do Nema 17
  stepper.setMaxSpeed(800);      // Velocidade máxima (passos/seg)
  stepper.setAcceleration(400);  // Aceleração para evitar perda de passos
  
  Serial.println("========================================");
  Serial.println("   SISTEMA DE COMUNICACAO ASCII - NEMA 17");
  Serial.println("========================================");
  Serial.println("Posicao 0: HOME");
  Serial.println("Posicoes 1-16: Caracteres no Disco");
  Serial.println("Digite um numero de 1 a 16 para iniciar:");
}

void loop() {
  if (Serial.available() > 0) {
    // Lê a posição desejada enviada pelo operador
    int posicaoAlvo = Serial.parseInt();

    // Valida se a posição está no range permitido (1 a 16)
    if (posicaoAlvo >= 1 && posicaoAlvo < totalPosicoes) {
      
      // CÁLCULO: (Posição * 22.5 graus) convertido para passos do motor
      float anguloFinal = posicaoAlvo * grausPorPosicao;
      long passosFinal = (anguloFinal * passosPorVolta) / 360;

      Serial.print("\n-> Movendo para Posicao: ");
      Serial.print(posicaoAlvo);
      Serial.print(" (Angulo: ");
      Serial.print(anguloFinal);
      Serial.println(")");

      // 1. Executa o movimento de IDA
      stepper.runToNewPosition(passosFinal);
      
      // 2. Aguarda 3 segundos para a escrita manual no papel
      Serial.println(">> Aguardando 3 segundos para escrita...");
      delay(3000);

      // 3. Executa o movimento de VOLTA para o ponto zero
      Serial.println("<< Retornando para HOME (Posicao 0)...");
      stepper.runToNewPosition(0);
      
      Serial.println("Pronto. Aguardando proximo comando.");
    }
  }
}