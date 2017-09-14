#include <SoftwareSerial.h>

struct Led{ // Estrutura para saber qual a porta do Arduino estamos trabalhando e o estado da porta ligado ou desligado
  const int port;
  bool statusPort;
  int positionPort;
};

//Declaração de todas as porta que estou utilizando no Arduino com a estrutura
Led led1 = {2,false,1}, led2 = {3,false,2}, led3 = {4,false,3}, led4 = {5,false,4}, led5 = {6,false,5}, led6 = {7,false,6}, led7 = {8,false,7}, led8 = {9,false,8}, led9 = {10,false,9}, led10 = {11,false,10};
//Portas Analogicas
const int temp = 0, lux = 1;
//Variaveis Diversas para Calculo e representação dos dados
float temperatura = 0;
int luminosidade = 0;
bool enviaDados = false;
unsigned long tempo = 0;
const int timeSendData = 10000;

void setup() {
  //Inicia a comunicação Serial
  Serial.begin(9600);
  //Declaração das portas de saida e entrada
  pinMode(led1.port,OUTPUT);
  pinMode(led2.port,OUTPUT);
  pinMode(led3.port,OUTPUT);
  pinMode(led4.port,OUTPUT);
  pinMode(led5.port,OUTPUT);
  pinMode(led6.port,OUTPUT);
  pinMode(led7.port,OUTPUT);
  pinMode(led8.port,OUTPUT);
  pinMode(led9.port,OUTPUT);
  pinMode(led10.port,OUTPUT);
}

void loop() {
  //Verifica se tem algo na porta Serial
  if(Serial.available()){
    //Ler a letra que esta na porta
    int byteSerial = Serial.read();

    //De acordo com a letra ele executa uma ação
    switch (byteSerial){
      //Liga ou desliga a porta que esta a led1
      case 'A':
        led1.statusPort = led1.statusPort ? false : true;
        alternaLed(led1);
        break;
      //Liga ou desliga a porta que esta a led2
      case 'B':
        led2.statusPort = led2.statusPort ? false : true;
        alternaLed(led2);
        break;
      //Liga ou desliga a porta que esta a led3
      case 'C':
        led3.statusPort = led3.statusPort ? false : true;
        alternaLed(led3);
        break;
      //Liga ou desliga a porta que esta a led4
      case 'D':
        led4.statusPort = led4.statusPort ? false : true;
        alternaLed(led4);
        break;
      //Liga ou desliga a porta que esta a led5
      case 'E':
        led5.statusPort = led5.statusPort ? false : true;
        alternaLed(led5);
        break;
      //Liga ou desliga a porta que esta a led6
      case 'F':
        led6.statusPort = led6.statusPort ? false : true;
        alternaLed(led6);
        break;
      //Liga ou desliga a porta que esta a led7
      case 'G':
        led7.statusPort = led7.statusPort ? false : true;
        alternaLed(led7);
        break;
      //Liga ou desliga a porta que esta a led8
      case 'H':
        led8.statusPort = led8.statusPort ? false : true;
        alternaLed(led8);
        break;
      //Liga ou desliga a porta que esta a led9
      case 'I':
        led9.statusPort = led9.statusPort ? false : true;
        alternaLed(led9);
        break;
      //Liga ou desliga a porta que esta a led10
      case 'J':
        led10.statusPort = led10.statusPort ? false : true;
        alternaLed(led10);
        break;
      //Liga todos os leds
      case 'K':
        led1.statusPort = led2.statusPort = led3.statusPort = led4.statusPort = led5.statusPort = led6.statusPort = led7.statusPort = led8.statusPort = led9.statusPort = led10.statusPort = true;
        alternaLed(led1);
        alternaLed(led2);
        alternaLed(led3);
        alternaLed(led4);
        alternaLed(led5);
        alternaLed(led6);
        alternaLed(led7);
        alternaLed(led8);
        alternaLed(led9);
        alternaLed(led10);
        break;
      //Desliga todos os leds
      case 'L':
        led1.statusPort = led2.statusPort = led3.statusPort = led4.statusPort = led5.statusPort = led6.statusPort = led7.statusPort = led8.statusPort = led9.statusPort = led10.statusPort = false;
        alternaLed(led1);
        alternaLed(led2);
        alternaLed(led3);
        alternaLed(led4);
        alternaLed(led5);
        alternaLed(led6);
        alternaLed(led7);
        alternaLed(led8);
        alternaLed(led9);
        alternaLed(led10);
        break;
      //Pega os dados vindo do sensor de temperatura
      case 'M':
        temperatura = analogRead(temp) * 0.4887585532;
        Serial.print("{\"temperature\":");
        Serial.print(temperatura);
        Serial.println("}");
        break;
      //Pega os dados vindo do sensor de luz
      case 'N':
        luminosidade = analogRead(lux);
        Serial.print("{\"luminosity\":");
        Serial.print(map(luminosidade,0,1023,0,100));
        Serial.println("}");
        break;
      case 'O':
        enviaDados = enviaDados ? false : true;
        //getStatusAllChip();
        break;
      case 'P':
        getStatusAllChip();
        break;
    }    
  }
  if(enviaDados){
    if(tempo == 0){
      tempo = millis();
      getStatusAllChip();
    }

    if(tempo + timeSendData <= millis()){
      tempo = 0;
    }
  }
  //digitalWrite(13,LOW);
  delay(100);
}

void alternaLed(Led alterLed){
  digitalWrite(alterLed.port,alterLed.statusPort);
  Serial.print("{\"relays\":{\"relay");
  Serial.print(alterLed.positionPort);
  Serial.print("\":");
  Serial.print(alterLed.statusPort);
  Serial.println("}}");
}

void getStatusAllChip(){
  temperatura = analogRead(temp) * 0.4887585532;
  delay(10);
  luminosidade = map(analogRead(lux),0,1023,0,100);
  delay(10);
  Serial.print("{");
  Serial.print("\"temperature\":");
  Serial.print(temperatura);
  Serial.print(",\"luminosity\":");
  Serial.print(luminosidade);
  Serial.print(",\"relays\":{");
  Serial.print("\"relay1\":");
  Serial.print(led1.statusPort);
  Serial.print(",\"relay2\":");
  Serial.print(led2.statusPort);
  Serial.print(",\"relay3\":");
  Serial.print(led3.statusPort);
  Serial.print(",\"relay4\":");
  Serial.print(led4.statusPort);
  Serial.print(",\"relay5\":");
  Serial.print(led5.statusPort);
  Serial.print(",\"relay6\":");
  Serial.print(led6.statusPort);
  Serial.print(",\"relay7\":");
  Serial.print(led7.statusPort);
  Serial.print(",\"relay8\":");
  Serial.print(led8.statusPort);
  Serial.print(",\"relay9\":");
  Serial.print(led9.statusPort);
  Serial.print(",\"relay10\":");
  Serial.print(led10.statusPort);
  Serial.println("}}");
}

