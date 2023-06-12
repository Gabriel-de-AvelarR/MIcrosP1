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

  TRISA = 0;

  ANSELE  = 0xFF;
  TRISE = 0XFF;

  ANSELB = 0;
  TRISB = 0;
  
  ADC_Init_Advanced(_ADC_INTERNAL_FVRH1);
  Lcd_Init();

  Lcd_Cmd(_LCD_CLEAR);               // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off


  do {
    char str[TAM];
    int conversaoPrim;

    temp_res = ADC_Get_Sample(7);   // Get 10-bit results of AD conversion
    conversao = (temp_res *  0.001) * 100.0;
    sprintf(str, "%.1fC", conversao);

    Lcd_Out(1, 3, str);
    
    delay_ms(200);
  } while(1);


}