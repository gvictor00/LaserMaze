/*
   @Project: Laser maze
   @Author: George Victor
   @Description: Labirinto baseado em lasers que tem como pontos de ativação e desativaçãso
                leitura de tags RFID.
   @Version:

   0.1.0 - Inicio do desenvolvimento
*/

// OUTPUT
#define rele_laser   7
#define rele_alarme  8
#define rele_teclado 9

// INPUT
#define input_rfid_inicio 5
#define input_rfid_final  6

// Sensores analógicos
#define sensor1 A0
#define sensor2 A1
#define sensor3 A2

// Variáveis de leitura e auxiliares
int leitura_sensor1 = 0;
int leitura_sensor2 = 0;
int leitura_sensor3 = 0;

int leitura_rfid_inicio = 0;
int leitura_rfid_final = 0;

bool inicio = true;
bool bateuSensor = false;

// Limiar de luminosidade para considerar que "bateu" no laser.
int limiarSensores = 300;

// Leitura sensores - número de leituras para evitar ruido
int leiturasSensor = 50
int i = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando pinos...");

  pinMode(rele_laser,   OUTPUT);    // Liga/Desliga os lasers
  pinMode(rele_alarme,  OUTPUT);    // Liga/Desliga o alarme e a sirene
  pinMode(rele_teclado, OUTPUT);    // Liga/Desliga o teclado de saída ou fornece ou não energia para a trava elétrica.

  pinMode(input_rfid_inicio, INPUT);  // Recebe sinal do RFID de inicio
  pinMode(input_rfid_final,  INPUT);  // Recebe sinal do RFID do final

  digitalWrite(rele_laser,    LOW); // Inicia o relê desligado
  digitalWrite(rele_alarme,   LOW); // Inicia o relê desligado
  digitalWrite(rele_teclado,  LOW); // Inicia o relê desligado

  Serial.println("Setup de pinos finalizado.");
  Serial.println("======================");
  Serial.println("Calibrando sensores...");
  Serial.println("======================");

  digitalWrite(rele_laser, HIGH);   // Liga os lasers
  delay(100);
  for (i = 0; i < leiturasSensor; i++)
  {
    Serial.print(".");
    leitura_sensor1 += analogRead(sensor1);
    leitura_sensor2 += analogRead(sensor2);
    leitura_sensor3 += analogRead(sensor3);
    delay(100);
  }

  leitura_sensor1 /= leiturasSensor;
  leitura_sensor2 /= leiturasSensor;
  leitura_sensor3 /= leiturasSensor;

  Serial.println();

  Serial.print("Sensor #1: ");
  Serial.println(leitura_sensor1);
  Serial.print("Sensor #2: ");
  Serial.println(leitura_sensor2);
  Serial.print("Sensor #3: ");
  Serial.println(leitura_sensor3);

  Serial.println("======================");
  Serial.println("Sensores calibrados!!!");
  Serial.println("======================");
}

void loop() {
  if (inicio == true) // Lê o rfid do inicio
  {
    leitura_rfid_inicio = digitalRead(input_rfid_inicio);
    if (leitura_rfid_inicio == 1)
    {
      inicio = false;

      if (bateuSensor == true)
      {
        // Liga o rele dos lasers
        digitalWrite(rele_laser, HIGH);

        // Desliga a sirene/girflex
        digitalWrite(rele_sirene, LOW);
      }
    }
  }
  else // Lê os sensores dos lasers
  {
    for (i = 0; i < leiturasSensor; i++) {
      leitura_sensor1 = analogRead(sensor1);
      leitura_sensor2 = analogRead(sensor2);
      leitura_sensor3 = analogRead(sensor3);

      leitura_sensor1 /= leiturasSensor;
      leitura_sensor2 /= leiturasSensor;
      leitura_sensor3 /= leiturasSensor;
    }

    if (leitura_sensor1 <= limiarSensor || leitura_sensor2 <= limiarSensor || leitura_sensor3 <= limiarSensor)
    {
      // Aciona flag de batida no sensor
      bateuSensor = true;

      // Desliga o rele dos lasers
      digitalWrite(rele_laser, LOW);

      // Liga a sirene/girflex
      digitalWrite(rele_sirene, HIGH);
    }
  }



}
