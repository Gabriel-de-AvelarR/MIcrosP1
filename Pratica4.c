sbit LCD_D5 at RB1_bit;
sbit LCD_D4 at RB0_bit;

// Pin direction
sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D7_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB0_bit;

void Interrupt_High() iv 0x0008 ics ICS_AUTO {

}

void main() {

     INTCON.GIEH = 1;
     INTCON.GIEL = 1;
     RCON.IPEN = 1;

     INTCON.TMR0IF = 0;  //flag de interrupção

     INTCON2.TMR0IP = 1;
     INTCON.TMR0IE = 1;

     T0CON.TMR0ON = 1;

     PWM1_Init(500);

     C1ON_bit = 0;                       // Disable comparators
     C2ON_bit = 0;

     ANSELA = 0;
     TRISA = 0XFF;

     PORTB = 0;                          // set PORTB to 0
     TRISB = 0;                          // designate PORTB pins as output

     ANSELC = 0;
     TRISC = 0;

     PWM1_Start();
     
     Lcd_Init();

     Lcd_Cmd(_LCD_CLEAR);               // Clear display
     Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
     while(1) {
              if(PORTA.RA7 == 0) {
                     PWM1_Set_Duty(0);
              } else if (PORTA.RA6 == 0) {
                     PWM1_Set_Duty(64);
              } else if (PORTA.RA5 == 0) {
                     PWM1_Set_Duty(127);
              } else if (PORTA.RA4 == 0) {
                     PWM1_Set_Duty(192);
              } else if (PORTA.RA3 == 0) {
                     PWM1_Set_Duty(255);
              }

     }


}
