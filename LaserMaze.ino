/*
 * @Project: Laser maze
 * @Author: George Victor
 * @Description: Labirinto baseado em lasers que tem como pontos de ativação e desativaçãso
 *              leitura de tags RFID. 
 * @Version:
 * 
 * 0.1.0 - Inicio do desenvolvimento
 */

// OUTPUT
#define rele_laser   7
#define rele_alarme  8
#define rele_teclado 9

// INPUT
#define input_rfid_inicio 5
#define input_rfid_final  6

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

  Serial.println("Setup de pinos finalizado...");
  
  delay(2000);
  Serial.println("Inicializando programa!");
}

void loop() {
  // put your main code here, to run repeatedly:

}
