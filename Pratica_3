unsigned int temp_res;
//PINOS A SEREM SETADOS
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


void main() {

  ANSELA  = 0xFF;
  TRISA = 0XFF;
  
  ANSELB = 0;
  TRISB = 0;

  ANSELC = 0;
  TRISC = 0;
  
  Lcd_Init();
  Lcd_Out(1, 3, "Hello!");

  do {
    temp_res = ADC_Read(1);   // Get 10-bit results of AD conversion
    PORTB = temp_res;         // Send lower 8 bits to PORTB
    PORTC = temp_res >> 8;    // Send 2 most significant bits to RC1, RC0
  } while(1);
}
