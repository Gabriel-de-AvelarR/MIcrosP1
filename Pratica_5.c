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

int contAceita; // Contador de material aceito
int contRejeita; // Contador de material rejeitado
bit escolha; // Flag que define qual material será aceito e qual será rejeitado (se 0 madeira será aceita e se 1 metal será aceito)
bit leuoptico; // FLag que define se o sensor óptico foi lido
bit metalOuMadeira; // Flag que define se o material na esteira no momento eh metal ou madeira (se 1 metal se 0 madeira)
char strMadeira[16]; // String de envio ao LCD com o número de blocos de madeira aceitos
char strMetal[16]; // String de envio ao LCD com o número de blocos de metal aceitos

void main() {
       ANSELD = 0; // Porta D digital
       TRISD = 0b00000111; // Bits 0, 1, 2 como entrada (leitura dos sensores), resto saída
       
       ANSELB = 0; // Porta B como digital
       TRISB = 0; // Porta B como saída
       
       ANSELC = 0; // Porta C como digital
       TRISC = 0xFF; // Porta C como saída
       
       contAceita = 0; // Inicializa o contador de materiais aceitos
       contRejeita = 0; // Inicializa o contador de materiais rejeitados

       leuoptico = 0; // Inicializa flag do leitor optico
       metalOuMadeira = 0; // Inicializa flag que diz se o material é metal ou madeira
       
       LCD_Init();
       Lcd_Cmd(_LCD_CLEAR);               // Clear display
       Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
       
       LCD_Out(1, 1, "Madeira: RC7");
       LCD_Out(2, 1, "Metal: RC6");

       while(1) {
                if(PORTC.RC7 == 0) { // Madeira será aceita, metal será rejeitado
                             escolha = 0;
                             break;
                }
                if(PORTC.RC6 == 0) { // Metal será aceito, madeira será rejeitada
                             escolha = 1;
                             break;
                }
       }

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
       
