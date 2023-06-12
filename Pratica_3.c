#define TAM 8
unsigned int temp_res;
float conversao;
char stringConvert [TAM];
unsigned int Vref =  5;

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

  ADC_Init();
  Lcd_Init();
  
 // Lcd_Out(1, 3, "Hello");
  
  Lcd_Cmd(_LCD_CLEAR);               // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off


  do {
    char str[TAM];
    int conversaoPrim;
    
    temp_res = ADC_Get_Sample(0);   // Get 10-bit results of AD conversion
    conversao = temp_res *  (5.0 / 1023.0);
    sprintf(str, "%.2fV", conversao);
    
    Lcd_Out(1, 3, str);
    
    //delay_ms(1000);
  } while(1);
  
  
  
}
