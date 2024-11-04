/*
  Projeto: Prática 03
  Descrição: Este código implementa um jogo de velocidade utilizando um ESP32, três LEDs e três sensores touch usando touchReaders.
  O jogo é iniciado ao tocar o primeiro sensor, fazendo o LED1 piscar três vezes e iniciar a contagem do tempo. 
  Dois jogadores competem tocando em seus respectivos sensores. O primeiro a tocar acende o LED correspondente e vence a rodada.
  O placar é exibido no monitor serial, juntamente com o tempo de reação do vencedor.

  Autores: Daniel Luan Lourenço de Lima e Emanoel Batista Pereira Filho
*/

#define LED_START_PIN 27
#define LED_P1_PIN 14
#define LED_P2_PIN 12

#define TOUCH1_PIN 15
#define TOUCH2_PIN 13
#define TOUCH3_PIN 4

int scoreP1 = 0;
int scoreP2 = 0;

void setup() {
  pinMode(LED_START_PIN, OUTPUT);
  pinMode(LED_P1_PIN, OUTPUT);
  pinMode(LED_P2_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (touchRead(TOUCH1_PIN) < 30) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_START_PIN, HIGH);
      delay(500);
      digitalWrite(LED_START_PIN, LOW);
      delay(500);
    }
    digitalWrite(LED_START_PIN, HIGH);

    unsigned long startTime = millis();
    bool gameEnded = false;
    int vencedor = 0;
    unsigned long roundStartTime = 0;

    while (!gameEnded) {
      if (touchRead(TOUCH2_PIN) < 30) {
        digitalWrite(LED_P1_PIN, HIGH);
        roundStartTime = millis() - startTime;
        vencedor = 1;
        scoreP1++;
        gameEnded = true;
      } else if (touchRead(TOUCH3_PIN) < 30) {
        digitalWrite(LED_P2_PIN, HIGH);
        roundStartTime = millis() - startTime;
        vencedor = 2;
        scoreP2++;
        gameEnded = true;
      }
    }

    Serial.println("=== Resultado do Jogo ===");
    Serial.print("Vencedor: Jogador ");
    Serial.println(vencedor);
    Serial.print("Tempo de reacao: ");
    Serial.print(roundStartTime);
    Serial.println(" ms");
    Serial.println("Placar:");
    Serial.print("Jogador 1: ");
    Serial.println(scoreP1);
    Serial.print("Jogador 2: ");
    Serial.println(scoreP2);
    Serial.println("=========================");

    while (touchRead(TOUCH1_PIN) >= 30) {
      delay(100);
    }

    digitalWrite(LED_START_PIN, LOW);
    digitalWrite(LED_P1_PIN, LOW);
    digitalWrite(LED_P2_PIN, LOW);
  }
  delay(100);
}