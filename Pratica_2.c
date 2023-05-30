int TIMERL;
int TIMERH;

void Interrupt_High() iv 0x0008 ics ICS_AUTO {
     
     LATE.RE1 = ~LATE.RE1;
     
     // TODO: Enviar sinal ao buzzer
     TMR0L = TIMERL;
     TMR0H = TIMERH;
     INTCON.TMR0IF = 0;
     
}


void main() {

     //INTCON2.RBPU = 0; // PULL UP
     //WPUB = 0XFF; // PULL UP PORTA B

     // CONFIGS TIMER E INTERRUPCOES
     INTCON.GIEH = 1;
     INTCON.GIEL = 1;
     RCON.IPEN = 1;

     INTCON.TMR0IF = 0;  //flag de interrupção

     INTCON2.TMR0IP = 1;
     INTCON.TMR0IE = 1;

     T0CON.TMR0ON = 1;


     ANSELB = 0; // DEFININDO PORTA B COMO DIGITAL
     TRISB = 0B00001111; // RB7 A RB4 COMO SAIDA (0) E RB3 A RB0 COMO ENTRADA (1)

     ANSELC = 0;
     TRISC = 0B00001111;

     ANSELA = 0;
     TRISA = 0X00;


     ANSELE = 0;
     TRISE = 0X00;
     
     LATA = 0;
     
     /*
     While ira analisar o teclado matricial, checando quais teclas  foram pressionadas.
     Entao, dependendo  da tecla ira carregar os valores certos a serem colocados no timer
     nas variaveis globais TIMERL e TIMERH. Essas variaveis  globais serao usadas para
     recarregar o valor no timer apos a chamada da interrupcao.
     Esses timers sao responsaveis por  enviar ondas quadradas ao buzzer, de modo a produzir
     um som em uma certa nota.
     */
     while(1) {

                 latc = 0b11100000; // checa primeira linha

                 if(PORTC.RC0 == 0){
                        // 65295, f = 2073
                        LATA.F0 = 1;
                        TIMERL = 0X12;
                        TIMERH = 0XFF;

                        //TMR0L = 0X0D;
                        //TMR0H = 0XFF;
                        T0CON = 0b10000000;
                        
                        continue;
                 }
                 if(PORTC.RC1 == 0){
                        //65323, f = 2349
                        LATA.F1 = 1; // Acende led para teste

                        TIMERL = 0X2F;
                        TIMERH = 0XFF;

                        //TMR0L = 0X2B;
                        //TMR0H = 0XFF;
                        T0CON = 0b10000000;
                        
                        continue;
                 }
                 if(PORTC.RC2 == 0){
                        //65346, f = 2637
                        LATA.F2 = 1;  // Acende led para teste

                        TIMERL = 0X46;
                        TIMERH = 0XFF;

                        //TMR0L = 0X42;
                        //TMR0H = 0XFF;
                        T0CON = 0b10000000;
                        
                        continue;
                 }

                 latc = 0b11010000; // checa segunda linha
                 if(PORTC.RC0 == 0){
                        //65357, f= 2794
                        LATA.F3 = 1;

                        TIMERL = 0X50;
                        TIMERH = 0XFF;

                        //TMR0L = 0X4D;
                        //TMR0H = 0XFF;
                        T0CON = 0b10000000;
                        
                        continue;
                 }
                 if(PORTC.RC1 == 0){
                        //65376, f = 3136
                        LATA.F4 = 1;

                        TIMERL = 0X64;
                        TIMERH = 0XFF;

                        //TMR0L = 0X60;
                        //TMR0H = 0XFF;
                        T0CON = 0b10000000;
                        
                        continue;
                 }
                 if(PORTC.RC2 == 0){
                        //65394, f = 3520
                        LATA.F5 = 1;

                        TIMERL = 0X75;
                        TIMERH = 0XFF;

                        //TMR0L = 0X72;
                        //TMR0H = 0XFF;
                        T0CON = 0b10000000;
                        
                        continue;
                 }

                 latc = 0b10110000; // checa terceira linha
                 if(PORTC.RC0 == 0){
                        //65409, f = 3951
                        LATA.F6 = 1;



                        TIMERL = 0X85;
                        TIMERH = 0XFF;

                        //TMR0L = 0X81;
                        //TMR0H = 0XFF;
                        T0CON = 0b10000000;
                        
                        continue;
                 }
                 if(PORTC.RC1 == 0){
                        //65415, f = 4146
                        LATA.F7 = 1;

                        TIMERL = 0X8B;
                        TIMERH = 0XFF;

                        //TMR0L = 0X87;
                        //TMR0H = 0XFF;
                        T0CON = 0b10000000;

                        continue;
                 }
                 
                 T0CON = 0;
                 

                 // quarta linha, 9 e elementos alem da terceira coluna sao ignorados
     }
}
