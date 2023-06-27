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

// Variável que será responsável por salvar o valor rpm
unsigned int rpmLow;
// String que será enviada ao LCD com valor rpm
char rpmStr[8];

void main() {

     // SET INTERRUPT
     INTCON.GIEH = 1;
     INTCON.GIEL = 1;
     RCON.IPEN = 1;

     // Disable comparators
     C1ON_bit = 0;                       
     C2ON_bit = 0;

     // SET FLAGS TIMER
     INTCON.TMR0IF = 0;  //flag de interrupção
     INTCON2.TMR0IP = 1;
     INTCON.TMR0IE = 1;

     
     
     
     // SET PINS
     ANSELD = 0;
     TRISD = 0XFF;

     // SET PORTB PARA LCD
     ANSELB = 0;
     TRISB = 0;                         

     // SET PORTC PARA PWM
     ANSELC = 0;
     TRISC = 0B00000000;

     // Habilita registrador do contador
     ANSELA = 0;
     TRISA.RA4 = 1;

     // SET PWM
     PWM1_Init(500);
     PWM1_Start();
     PWM1_Set_Duty(0);   // INICIA COM DUTY 0%

     // SET LCD
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);               // Clear display
     Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
     LCD_Out(1, 1, "DUTY CICLE=0%"); // INICIA COM DUTY 0%

     /* LOOP PRINCIPAL DO PROGRAMA
     O PROGRAMA IRÁ AGUARDAR O PRESSIONAMENTO DE ALGUM DOS BOTÕES DA PORTA D
     ENTÃO IRÁ INICIAR O TIMER, COMEÇANDO EM 0 E EM MODO CONTADOR
     DEPOIS ENVIARÁ O DUTY CICLE AO LCD
     TERÁ UM DELAY DE 250 MS
     IRÁ RECUPERAR O VALOR DO CONTADOR QUE SERÁ ENVADO AO LCD
          */
     while(1) {
              if(PORTD.RD0 == 1) {
                     // ENVIA DUTY CICLE ATUAL AO LCD
                     LCD_Out(1, 1, "DUTY CICLE=    ");
                     PWM1_Set_Duty(0);
                     LCD_Out(1, 1, "DUTY CICLE=0%");

                     // SET COUNTER 0
                     TMR0L = 0;
                     TMR0H = 0;
                     T0CON = 0b10101101;

                     // DELAY 250 MS
                     delay_ms(250);

                     // ENVIA CONTAGEM RPM AO LCD
                     rpmLow = TMR0L;
                     sprintf(rpmStr, "RPM: %d", (rpmLow * 4));
                     LCD_Out(2, 1, rpmStr);
              } else if (PORTD.RD1 == 1) {
                     // ENVIA DUTY CICLE ATUAL AO LCD
                     LCD_Out(1, 1, "DUTY CICLE=    ");
                     PWM1_Set_Duty(0);
                     LCD_Out(1, 1, "DUTY CICLE=0%");

                     // SET COUNTER 0
                     TMR0L = 0;
                     TMR0H = 0;
                     T0CON = 0b10101101;

                     // DELAY 250 MS
                     delay_ms(250);
                   
                     rpmLow = TMR0L;
                     sprintf(rpmStr, "RPM: %d", (rpmLow * 4));
                     LCD_Out(2, 1, rpmStr);
              } else if (PORTD.RD2 == 1) {
                     // ENVIA DUTY CICLE ATUAL AO LCD
                     LCD_Out(1, 1, "DUTY CICLE=    ");
                     PWM1_Set_Duty(0);
                     LCD_Out(1, 1, "DUTY CICLE=0%");
                     
                     // SET COUNTER 0
                     TMR0L = 0;
                     TMR0H = 0;
                     T0CON = 0b10101101;
                     
                     // DELAY 250 MS
                     delay_ms(250);
                   
                     // ENVIA CONTAGEM RPM AO LCD
                     rpmLow = TMR0L;
                     sprintf(rpmStr, "RPM: %d", (rpmLow * 4));
                     LCD_Out(2, 1, rpmStr);
              } else if (PORTD.RD3 == 1) {
                     // ENVIA DUTY CICLE ATUAL AO LCD
                     LCD_Out(1, 1, "DUTY CICLE=    ");
                     PWM1_Set_Duty(0);
                     LCD_Out(1, 1, "DUTY CICLE=0%");
                     
                     // SET COUNTER 0
                     TMR0L = 0;
                     TMR0H = 0;
                     T0CON = 0b10101101;
                   
                     // DELAY 250 MS
                     delay_ms(250);
                   
                     // ENVIA CONTAGEM RPM AO LCD
                     rpmLow = TMR0L;
                     sprintf(rpmStr, "RPM: %d", (rpmLow * 4));
                     LCD_Out(2, 1, rpmStr);
              } else if (PORTD.RD4 == 1) {
                     // ENVIA DUTY CICLE ATUAL AO LCD
                     LCD_Out(1, 1, "DUTY CICLE=    ");
                     PWM1_Set_Duty(0);
                     LCD_Out(1, 1, "DUTY CICLE=0%");
                     
                     // SET COUNTER 0
                     TMR0L = 0;
                     TMR0H = 0;
                     T0CON = 0b10101101;
                   
                     // DELAY 250 MS
                     delay_ms(250);
                   
                     // ENVIA CONTAGEM RPM AO LCD
                     rpmLow = TMR0L;
                     sprintf(rpmStr, "RPM: %d", (rpmLow * 4));
                     LCD_Out(2, 1, rpmStr);
              }
     }
}
