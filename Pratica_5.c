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

int contAceita;
int contRejeita;
bit escolha;
bit leuoptico;
bit metalOuMadeira;
char strMadeira[16];
char strMetal[16];

void main() {
       ANSELD = 0;
       TRISD = 0b00000111;
       
       ANSELB = 0;
       TRISB = 0;
       
       ANSELC = 0;
       TRISC = 0xFF;
       
       contAceita = 0;
       contRejeita = 0;
       
       LCD_Init();
       Lcd_Cmd(_LCD_CLEAR);               // Clear display
       Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
       
       LCD_Out(1, 1, "Madeira: RC7");
       LCD_Out(2, 1, "Metal: RC6");
       
       while(1) {
                if(PORTC.RC7 == 0) {
                             escolha = 0;
                             break;
                }
                if(PORTC.RC6 == 0) {
                             escolha = 1;
                             break;
                }
       }
       
       //while(PORTD.RD0 == 1 || PORTD.RD1 == 1); // tempo de soltura do botao

       //TRISD = 0b00000111;

       Lcd_Cmd(_LCD_CLEAR);               // Clear display

       /*
       ATIVACAO SENSOR OPTICO: MOVE ESTERIRA PARA DIREITA
       ATIVACAO SENSOR INDUTIVO: E METAL, ESPERAR 5,5 S
       ATIVACAO SENSOR CAPACITIVO: SE NAO METAL, ESPERAR 3,45S E EMPURRAR COM CILINDRO
       //Ausência de objeto no sensor -> 1
       //Presença de objeto no sensor -> 0
       */
       
       // MOVE ESTEIRA PARA ESQUERDA
        LATD.RD7 = 0;
        LATD.RD6 = 1;
        
         leuoptico = 0;
         metalOuMadeira = 0;
         
         LCD_OUT(1, 1, "Madeira: 0");
         LCD_OUT(2, 1, "Metal: 0");
       while(1) {
       // SE ATIVA SENSOR OPTICO
            if(PORTD.RD0 == 0) {
                         leuoptico = 1;
                         // MOVE ESTEIRA PARA DIREITA
                         LATD.RD7 = 1;
                         LATD.RD6 = 0;
                         
            }
                         
            if(leuoptico){
                          if(PORTD.RD2 == 0) { //le indutivo
                                       metalOuMadeira = 1;
                          }
                          if(PORTD.RD1 == 0) {  //le capacitivo
                                       if(metalOuMadeira) {
                                                          if(!escolha) { // EH METAL E ESCOLHEMOS MADEIRA
                                                                              contRejeita++;
                                                                              delay_ms(3450);
                                                                              // ACIONA CILINDRO
                                                                              LATD.RD5 = 1;
                                                                              LATD.RD4 = 0;
                                                                              delay_ms(500);

                                                                  } else { // EH METAL E ESCOLHEMOS METAL
                                                                              contAceita++;
                                                                              delay_ms(5500);

                                                                  }
                                               } else {
                                                                  if(!escolha) { // EH MADEIRA E ESCOLHEMOS MADEIRA
                                                                              contAceita++;
                                                                              delay_ms(5500);

                                                                  } else { // EH MADEIRA E ESCOLHEMOS METAL
                                                                              contRejeita++;
                                                                              delay_ms(3450);
                                                                              // ACIONA CILINDRO
                                                                              LATD.RD5 = 1;
                                                                              LATD.RD4 = 0;
                                                                              delay_ms(500);

                                                                  }
                                               }
                                  
                                  //recua cilindro
                                   LATD.RD5 = 0;
                                   LATD.RD4 = 1;
                                   delay_ms(500);
                                   
                                   //move pra esquerda
                                   LATD.RD7 = 0;
                                   LATD.RD6 = 1;
                                   leuoptico = 0;
                                   metalOuMadeira = 0;

                                   if(!escolha) {
                                              sprintf(strMadeira, "Madeira: %d", contAceita);
                                              LCD_OUT(1, 1, strMadeira);
                                              sprintf(strMetal, "Metal: %d",  contRejeita);
                                              LCD_OUT(2, 1, strMetal);
                                   } else {
                                                sprintf(strMadeira, "Madeira: %d", contRejeita);
                                                LCD_OUT(1, 1, strMadeira);
                                                sprintf(strMetal, "Metal: %d",  contAceita);
                                                LCD_OUT(2, 1, strMetal);
                                   }
                                  }
                         
                         }
                         
                         
            
            }
       }
       
