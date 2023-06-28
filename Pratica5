

// Lcd pinout settings
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D7 at RB3_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D4 at RB0_bit;

// Pin direction
sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D7_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB0_bit;

int contMetal;
int contMadeira;

void main() {
       ANSELB = 0;
       TRISB = 0b00000111;
       contMetal = 0;
       contMadeira = 0;
       
       /*
       ATIVACAO SENSOR OPTICO: MOVE ESTERIRA PARA DIREITA
       ATIVACAO SENSOR INDUTIVO: E METAL, ESPERAR 5,5 S
       ATIVACAO SENSOR CAPACITIVO: SE NAO METAL, ESPERAR 3,45S E EMPURRAR COM CILINDRO
       //Ausência de objeto no sensor -> 1
       //Presença de objeto no sensor -> 0
       */
       
       while(1) {
                // SE ATIVA SENSOR OPTICO
            if(PORTB.RB0 == 0) {
                         // MOVE ESTEIRA PARA DIREITA
                         LATB.RB7 = 1;
                         LATB.RB6 = 0;
                         
                         while(1) {
                                  if(PORTB.RB2 == 1) {
                                               contMetal++;
                                               delay_ms(5500);
                                               break;
                                  }
                                  if(PORTB.RB1 == 1) {

                                  }
                         }
            }
       }
       
}
