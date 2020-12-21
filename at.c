#include <avr/io.h>
#include <util/delay.h>


uint16_t ad_valor = 0;
uint16_t ad = 0;
float tensao = 5;

float ten = 0;


float res=0;
int main(){
  Serial.begin(9600);

  ADMUX |= 0b01000000;
  ADCSRA |= 0b10000111;
  DDRB |= 0b11111111;
  PORTB |= 0b00000000;
  DDRD |= 0b11111111;
  PORTD |= 0b00000000;

  TCCR1A |= 0b10000011;
  TCCR1B |= 0b00001010;
  
  while(1){
    ADCSRA |= 0b10000111;

    ADMUX  &= 0b11110000;       //ZERA OS VALORES REFERENTES AO ADC
    ADMUX  |= 0b00000000;       //SETA O AD0 PARA SER UTILIZADO
    ADCSRA |= 0b01000000;       //INICIA CONVERSÃO
    while(!(ADCSRA & 0b00010000));  //ESPERA A CONVERSÃO ACABAR    
    OCR1A = ADC;
    ad = ADC;
    ten = ad*5/1023.0;
    ADMUX  &= 0b11110000;
    ADMUX  |= 0b00000001;
    ADCSRA |= 0b01000000;
    while(!(ADCSRA & 0b00010000));    
    ad_valor = ADC;
    tensao = ad_valor*ten/1023.0;
    res=tensao*220/(ten-tensao);
    
    if(res < 500){
      PORTD &= (0<<PD7);
      PORTB |= (1<<PB0);
    } else if(res>500 && res <5000){
      Serial.println("ESTOU AQUI");
      PORTD |= (1<<PD7);
      PORTB &= (0<<PB0);
      //Serial.println("AQUI");
    } else{
      
      PORTD &= (0<<PD7);
      PORTB &= (0<<PB0);
    }
    Serial.print("r");
    Serial.println(res);
    Serial.print("v");
    Serial.println(ten);
    //Serial.println(res);
    _delay_ms(300);
    //Serial.println(tensao);
  }
}
