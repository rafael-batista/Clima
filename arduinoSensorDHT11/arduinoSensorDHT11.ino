// ===============================================================================
// --- Biblioteca Auxiliar ---
#include <dht.h>   //biblioteca do sensor de umidade e temperatura


// ===============================================================================
// --- Mapeamento de Hardware ---
#define    dht_pin    5   //pino de sinal do dht11 ligado no digital 5


// ===============================================================================
// --- Declaração de Objetos ---
dht   my_dht;   //objeto para o sensor


// ===============================================================================
// --- Variáveis Globais ---
int    temperatura = 0x00,   //armazena a temperatura em inteiro
       umidade     = 0x00;   //armazena a umidade em inteiro


// ===============================================================================
// --- Configurações Iniciais ---
void setup() 
{
   Serial.begin(9600);   //serial em 9600 baud rate


} //end setup


// ===============================================================================
// --- Loop Infinito ---
void loop() 
{
   my_dht.read11(dht_pin);

   temperatura = my_dht.temperature;
   umidade     = my_dht.humidity;

   //Serial.print("Temperatura: ");
   Serial.print(temperatura);
   //Serial.println();
   //Serial.print("Umidade: ");
   Serial.println(umidade);
   


   delay(1000);
 


} //end loop
