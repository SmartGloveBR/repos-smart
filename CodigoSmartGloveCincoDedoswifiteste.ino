#include "Wire.h"


/////////wifi/////////////
/// exemplo -> https://blogmasterwalkershop.com.br/embarcados/nodemcu/nodemcu-como-criar-um-web-server-e-conectar-a-uma-rede-wifi/
#include <ESP8266WiFi.h> //INCLUSÃO DA BIBINCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO
 const char* ssid = "IF_CATARINENSE"; //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO EM QUE VAI CONECTAR
const char* password = "ifcatarinense"; //VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO EM QUE VAI CONECTAR
 
 
WiFiServer server(80); //CASO OCORRA PROBLEMAS COM A PORTA 80, UTILIZE OUTRA (EX:8082,8089) E A CHAMADA DA URL FICARÁ IP:PORTA(EX: 192.168.0.15:8082)
 

//////////////////////////

const int MPU_addr = 0x69; 

int16_t AcX, AcY, AcZ;
//protototpos das funcoes
byte check_I2c(byte); 
void reiniciaCom();
void setup() {

  /////wifi
  Serial.begin(115200); //INICIALIZA A SERIAL
delay(10); //INTERVALO DE 10 MILISEGUNDOS
 
Serial.println(""); //PULA UMA LINHA NA JANELA SERIAL
Serial.println(""); //PULA UMA LINHA NA JANELA SERIAL
Serial.print("Conectando a "); //ESCREVE O TEXTO NA SERIAL
Serial.print(ssid); //ESCREVE O NOME DA REDE NA SERIAL
 
WiFi.begin(ssid, password); //PASSA OS PARÂMETROS PARA A FUNÇÃO QUE VAI FAZER A CONEXÃO COM A REDE SEM FIO
 
while (WiFi.status() != WL_CONNECTED) { //ENQUANTO STATUS FOR DIFERENTE DE CONECTADO
delay(500); //INTERVALO DE 500 MILISEGUNDOS
Serial.print("."); //ESCREVE O CARACTER NA SERIAL
}
Serial.println(""); //PULA UMA LINHA NA JANELA SERIAL
Serial.print("Conectado a rede sem fio "); //ESCREVE O TEXTO NA SERIAL
Serial.println(ssid); //ESCREVE O NOME DA REDE NA SERIAL
server.begin(); //INICIA O SERVIDOR PARA RECEBER DADOS NA PORTA DEFINIDA EM "WiFiServer server(porta);"
Serial.println("Servidor iniciado"); //ESCREVE O TEXTO NA SERIAL
 
Serial.print("IP para se conectar ao NodeMCU: "); //ESCREVE O TEXTO NA SERIAL
Serial.print("http://"); //ESCREVE O TEXTO NA SERIAL
Serial.println(WiFi.localIP()); //ESCREVE NA SERIAL O IP RECEBIDO DENTRO DA REDE SEM FIO (O IP NESSA PRÁTICA É RECEBIDO DE FORMA AUTOMÁTICA)
delay(1000);
  // start the web server on port 80
  server.begin();
//// wifi fim

  pinMode(D0, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  Wire.begin();
  Serial.begin(115200);
  check_I2c(MPU_addr); 

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true);
  reiniciaCom();

  

}



////



void reiniciaCom() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true);
}

void trocaParaDedo1() {
  digitalWrite(D0, LOW);
  digitalWrite(D5, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);

}

void trocaParaDedo2() {
  digitalWrite(D0, HIGH);
  digitalWrite(D5, LOW);
  digitalWrite(D4, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
}


void trocaParaDedo3() {
  digitalWrite(D0, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D4, LOW);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
}

void trocaParaDedo4() {
  digitalWrite(D0, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D6, LOW);
  digitalWrite(D7, HIGH);
}

void trocaParaDedo5() {
  digitalWrite(D0, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, LOW);
}


void lerUmDedo() {

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); 
  Wire.endTransmission(false);

  Wire.requestFrom(MPU_addr, 14, true); 
  AcX = Wire.read() << 8 | Wire.read(); 
  AcY = Wire.read() << 8 | Wire.read(); 
  AcZ = Wire.read() << 8 | Wire.read(); 
  Serial.print(AcX);
  Serial.print("  "); Serial.print(AcY);
  Serial.print("  "); Serial.print(AcZ);
  Serial.print("  ");
  Wire.endTransmission(true);
  delay(100);


}
void loop() {

WiFiClient client = server.available(); //VERIFICA SE ALGUM CLIENTE ESTÁ CONECTADO NO SERVIDOR
if(!client) { //SE NÃO EXISTIR CLIENTE CONECTADO, FAZ
return; //REEXECUTA O PROCESSO ATÉ QUE ALGUM CLIENTE SE CONECTE AO SERVIDOR
}
Serial.println("Novo cliente se conectou!"); //ESCREVE O TEXTO NA SERIAL
while(!client.available()){ //ENQUANTO CLIENTE ESTIVER CONECTADO
delay(1); //INTERVALO DE 1 MILISEGUNDO
}
String request = client.readStringUntil('\r'); //FAZ A LEITURA DA PRIMEIRA LINHA DA REQUISIÇÃO
Serial.println(request); //ESCREVE A REQUISIÇÃO NA SERIAL
client.flush(); //AGUARDA ATÉ QUE TODOS OS DADOS DE SAÍDA SEJAM ENVIADOS AO CLIENTE
 
client.println("HTTP/1.1 200 OK"); //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
client.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
client.println("");
client.println("<!DOCTYPE HTML>"); //INFORMA AO NAVEGADOR A ESPECIFICAÇÃO DO HTML
client.println("<html>"); //ABRE A TAG "html"
client.println("<h1><center>Ola cliente!</center></h1>"); //ESCREVE "Ola cliente!" NA PÁGINA
client.println("<center><font size='5'>Seja bem vindo!</center>"); //ESCREVE "Seja bem vindo!" NA PÁGINA
client.println("</html>"); //FECHA A TAG "html"
delay(1); //INTERVALO DE 1 MILISEGUNDO
Serial.println("Cliente desconectado"); //ESCREVE O TEXTO NA SERIAL
Serial.println(""); //PULA UMA LINHA NA JANELA SERIAL


  //// wifi fim

  trocaParaDedo1();
  delay(50);
  lerUmDedo();
  trocaParaDedo2();
  delay(50);
  lerUmDedo();
  trocaParaDedo3();
  delay(50);
  lerUmDedo();
  trocaParaDedo4();
  delay(50);
  lerUmDedo();
  trocaParaDedo5();
  delay(50);
  lerUmDedo();
  Serial.println("");

  delay(1000);
  reiniciaCom();
}

byte check_I2c(byte addr) {
  byte error;
  Wire.beginTransmission(addr);
  error = Wire.endTransmission();

  if (error == 0)
  {
    //    Serial.print(" Device Found at 0x");
    //    Serial.println(addr, HEX);
  }
  else
  {
    Serial.print(" No Device Found at 0x");
    Serial.print(addr, HEX);
  }
  return error;
}
