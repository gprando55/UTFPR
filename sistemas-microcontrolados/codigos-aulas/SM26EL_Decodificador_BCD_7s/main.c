#include <msp430.h> 



#define     seg_a       BIT0
#define     seg_b       BIT1
#define     seg_c       BIT2
#define     seg_d       BIT3
#define     seg_e       BIT4
#define     seg_f       BIT5
#define     seg_g       BIT6
#define     seg_p       BIT7

#define     ZERO        (seg_a + seg_b + seg_c + seg_d + seg_e + seg_f)
#define     UM          (seg_b + seg_c)
#define     DOIS        (seg_a + seg_b + seg_g + seg_e + seg_d)
#define     TRES        (seg_a + seg_b + seg_c + seg_d + seg_g)
#define     QUATRO      (seg_b + seg_c + seg_f + seg_g)
#define     CINCO       (seg_a + seg_c + seg_d + seg_g + seg_f)
#define     SEIS        (seg_a + seg_g + seg_c + seg_d + seg_e + seg_f)
#define     SETE        (seg_a + seg_b + seg_c)



void ini_P1_P2(void);

/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	ini_P1_P2();

	do{
	    /* Tarefas: 1 - Verficar chaves
	     *          2 - Atribuir digito no display
	     *
	     *   1 - Verificar as chaves
	     *          - Qual registrador mostra o estado das entradas da P1?
	     *                 --> P1IN - apresenta o status dos pinos da P1
	     *
         *            bit                   7 6 5 4    3 2 1 0
         *            P1IN                  X X X X    X Y Y Y
         *            (BIT0 + BIT1 + BIT2)  0 0 0 0    0 1 1 1
         *            AND bit-a-bit       --------------------------
         *                                  0 0 0 0    0 Y Y Y
         *
         *            P1IN & (BIT0 + BIT1 + BIT2)  -> switch( * )
         *

	     *
	     *
	     *   2 -> Ex. Para mostrar 1 no display
	     *
	     *        P2OUT = BIT1 + BIT2; -> 0000 0110
	     *                 |       |
	     *                seg_b   seg_c
	     *
	     *        P2OUT = seg_b + seg_c;
	     *
	     *        P2OUT = UM;
	     *
	     *
	     *
	     *
	     */
        switch( P1IN & (BIT0 + BIT1 + BIT2) ){
            case 0b00000000:
                P2OUT = ZERO;
            break;
            case 1:
                P2OUT = UM;
            break;
            case 2:
                P2OUT = DOIS;
            break;
            case 3:
                P2OUT = TRES;
            break;
            case 4:
                P2OUT = QUATRO;
            break;
            case 5:
                P2OUT = CINCO;
            break;
            case 6:
                P2OUT = SEIS;
            break;
            case 7:
                P2OUT = SETE;
            break;
        }

	}while(1);
}
//--------------------------------------------------------------------





void ini_P1_P2(void){

    /* Inicializacao da Porta 1
     *
     *      P1.0-P1.2: S1-S3 - entradas com resistor de pull-down
     *      P1.3-P1.7: N.C. - saidas em nivel baixo.
     *
     *      P1DIR - configura direcao dos pinos como E/S
     *
     *            bit               7 6 5 4    3 2 1 0
     *            P1DIR ini.        0 0 0 0    0 0 0 0
     *            P1DIR desejado    1 1 1 1    1 0 0 0
     *                          -----------------------------
     *                HEX        0x    F          8
     *
     *            P1DIR = 0xF8;
     *            P1DIR = BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
     *
     *
     *      P1REN - Habilita resistores para entradas
     *
     *            bit               7 6 5 4    3 2 1 0
     *            P1REN ini.        0 0 0 0    0 0 0 0
     *            P1REN desejado    0 0 0 0    0 1 1 1
     *                          -----------------------------
     *                HEX        0x    0          7
     *
     *      P1REN = 0x07;
     *      P1REN = BIT0 + BIT1 + BIT2;
     *
     *      P1OUT - Configura nivel das saidas/Funcao do resistor
     *
     *                                            ______ Funcao dos resistores
     *                                           | | |
     *            bit               7 6 5 4    3 2 1 0
     *            P1OUT ini.        0 0 0 0    0 0 0 0
     *            P1OUT desejado    0 0 0 0    0 0 0 0
     *                          -----------------------------
     *
     *            P1OUT = 0;
     *
     */
    P1DIR = BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
    P1REN = BIT0 + BIT1 + BIT2;
    P1OUT = 0;

    /* Inicializacao da Porta 2
     *
     *      P2.0-P2.7: seg. a-f do display - saidas em nivel baixo (display apagado)
     *      Pinos 18 e 19: mudar a funcao de XIN/XOUT para P2.6/P2.7
     *
     *      P2DIR - configura direcao dos pinos como E/S
     *
     *            bit               7 6 5 4    3 2 1 0
     *            P2DIR ini.        0 0 0 0    0 0 0 0
     *            P2DIR desejado    1 1 1 1    1 1 1 1
     *                          -----------------------------
     *                HEX        0x    F          F
     *
     *            P2DIR = 0xFF;
     *            P2DIR = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
     *
     *
     *      P2OUT - Configura nivel das saidas
     *
     *
     *            bit               7 6 5 4    3 2 1 0
     *            P2OUT ini.        0 0 0 0    0 0 0 0
     *            P2OUT desejado    0 0 0 0    0 0 0 0
     *                          -----------------------------
     *
     *            P2OUT = 0;
     *
     *
     *      -> MUDAR a funcao dos pinos 18 e 19
     *
     *            bit               7 6 5 4    3 2 1 0
     *            P2SEL ini.        1 1 0 0    0 0 0 0
     *            P2SEL desejado    0 0 0 0    0 0 0 0
     *                          -----------------------------
     *
     *            P2SEL = 0;
     *            P2SEL &= ~(BIT6 + BIT7);
     *
     */
    P2DIR = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
    P2OUT = 0;
    P2SEL &= ~(BIT6 + BIT7);

}




