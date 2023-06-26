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

unsigned int rpmLow;
char rpmStr[8];

void main() {

     // SET INTERRUPT
     INTCON.GIEH = 1;
     INTCON.GIEL = 1;
     RCON.IPEN = 1;
     
     C1ON_bit = 0;                       // Disable comparators
     C2ON_bit = 0;

     // SET FLAGS TIMER
     INTCON.TMR0IF = 0;  //flag de interrupção
     INTCON2.TMR0IP = 1;
     INTCON.TMR0IE = 1;

     // SET TIMER 0
     T0CON.TMR0ON = 0b10101101;
     //T0CON.TMR0ON = 1;
     // 34286
     TMR0L = 0xEE;
     TMR0H = 0x85;
     
     // SET PINS
     ANSELD = 0;
     TRISD = 0XFF;

     ANSELB = 0;
     TRISB = 0;                          // designate PORTB pins as output

     ANSELC = 0;
     TRISC = 0B00000000;

     // Habilita registrador do contador
     ANSELA = 0;
     TRISA.RA4 = 1;

     PWM1_Init(500);
     PWM1_Start();
     PWM1_Set_Duty(0);   // INICIA COM DUTY 0%

     
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);               // Clear display
     Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
     LCD_Out(1, 1, "DUTY CICLE=0%"); // INICIA COM DUTY 0%
     
     rpmLow = 0;
     
     while(1) {
              if(PORTD.RD0 == 1) {
                     TMR0L = 0x00;
                     TMR0H = 0x00;
                     T0CON.TMR0ON = 0b10101101;
                     INTCON.TMR0IF = 0;
              
                     LCD_Out(1, 1, "DUTY CICLE=    ");
                     PWM1_Set_Duty(0);
                     LCD_Out(1, 1, "DUTY CICLE=0%");
                     
                     delay_ms(250);
                     rpmLow = TMR0L;
                     sprintf(rpmStr, "RPM: %d", (rpmLow * 4));
                     LCD_Out(2, 1, rpmStr);
              } else if (PORTD.RD1 == 1) {
                     TMR0L = 0x00;
                     TMR0H = 0x00;
                     T0CON.TMR0ON = 0b10101101;
                     //T0CON.TMR0ON = 1;
                     INTCON.TMR0IF = 0;
                     
                     LCD_Out(1, 1, "DUTY CICLE=    ");
                     PWM1_Set_Duty(64);
                     LCD_Out(1, 1, "DUTY CICLE=25%");
                     
                     delay_ms(250);
                     rpmLow = TMR0L;
                     sprintf(rpmStr, "RPM: %d", (rpmLow * 4));
                     LCD_Out(2, 1, rpmStr);
              } else if (PORTD.RD2 == 1) {
                     TMR0L = 0xEE;
                     TMR0H = 0x85;
                     T0CON.TMR0ON = 0b10101101;
                     //T0CON.TMR0ON = 1;
                     INTCON.TMR0IF = 0;

                     LCD_Out(1, 1, "DUTY CICLE=    ");
                     PWM1_Set_Duty(127);
                     LCD_Out(1, 1, "DUTY CICLE=50%");

                     delay_ms(250);
                     rpmLow = TMR0L;
                     sprintf(rpmStr, "RPM: %d", (rpmLow * 4));
                     LCD_Out(2, 1, rpmStr);
              } else if (PORTD.RD3 == 1) {
                     TMR0L = 0xEE;
                     TMR0H = 0x85;
                     T0CON.TMR0ON = 0b10101101;
                     //T0CON.TMR0ON = 1;
                     INTCON.TMR0IF = 0;

                     LCD_Out(1, 1, "DUTY CICLE=    ");
                     PWM1_Set_Duty(192);
                     LCD_Out(1, 1, "DUTY CICLE=75%");

                     delay_ms(250);
                     rpmLow = TMR0L;
                     sprintf(rpmStr, "RPM: %d", (rpmLow * 4));
                     LCD_Out(2, 1, rpmStr);
              } else if (PORTD.RD4 == 1) {
                     TMR0L = 0xEE;
                     TMR0H = 0x85;
                     T0CON.TMR0ON = 0b10101101;
                     //T0CON.TMR0ON = 1;
                     INTCON.TMR0IF = 0;

                     LCD_Out(1, 1, "DUTY CICLE=    ");
                     PWM1_Set_Duty(255);
                     LCD_Out(1, 1, "DUTY CICLE=100%");

                     delay_ms(250);
                     rpmLow = TMR0L;
                     sprintf(rpmStr, "RPM: %d", (rpmLow * 4));
                     LCD_Out(2, 1, rpmStr);
              }
     }
}
