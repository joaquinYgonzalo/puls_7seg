#include "MKL25Z4.h"
int puls= 13;
int led_r=18;
int led_v=19;
int contador [7]={0,1,2,3,4,5,6};
int display[10][7]={
//   a  b  c  d  e  f  g
    {1, 1, 1, 1, 1, 1, 0},//0
    {0, 1, 1, 0, 0, 0, 0},//1
    {1, 1, 0, 1, 1, 0, 1},//2
    {1, 1, 1, 1, 0, 0, 1},//3
    {0, 1, 1, 0, 0, 1, 1},//4
    {1, 0, 1, 1, 0, 1, 1},//5
    {1, 0, 1, 1, 1, 1, 1},//6
    {1, 1, 1, 0, 0, 0, 0},//7
    {1, 1, 1, 1, 1, 1, 1},//8
    {1, 1, 1, 0, 0, 1, 1}//9
};
int i, t, j;
volatile a=0;
int main(void){
    SIM->SCGC5|=SIM_SCGC5_PORTB_MASK;
    SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;
    SIM->SCGC5|=SIM_SCGC5_PORTD_MASK;
    PORTA->PCR[13]|=PORT_PCR_MUX(1)|PORT_PCR_IRQC(0b1101);
    PTA->PDDR&=~(1<<13);
    NVIC_EnableIRQ(PORTA_IRQn);
    NVIC_SetPriority(PORTA_IRQn, 0b1101);
    PORTA->PCR[13]|=(1<<8)|PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
    PORTB->PCR[18]|=(1<<8);
    PORTB->PCR[19]|=(1<<8);
    PTB->PDDR|=(1<<18);
    PTB->PDDR|=(1<<19);
    for(j=0; j<7; j++){
        PORTB->PCR[contador[j]]|=(1<<8);
        PTB->PDDR|=(1<<contador[j]);
    }
    PTB->PSOR|=(1<<18);
    PTB->PSOR|=(1<<19);
    while(1){
        if(a==0){
            if((PTA->PDIR&(1<<13))==0){
             for (i = 0; i <10; i++){
                for(j=0;j<7;j++){

                    if(display[i][j]==0){
                        PTD->PCOR|=(1<<contador[j]);
                    }else{
                        PTD->PSOR|=(1<<contador[j]);
                    }
                }
                for (int t = 7000000; t>0; t--);
                }
                PTB->PTOR|=(1<<19);
             }
  }else if(a==1){
              if((PTA->PDIR&(1<<13))==0){
                for (i = 0; i <10; i--){
            	    if((PTA->PDIR&(1<<13))==0){
                       for(j=0;j<7;j++){

                    if(display[i][j]==0){
                        PTD->PCOR|=(1<<contador[j]);
                    }else{
                        PTD->PSOR|=(1<<contador[j]);
                    }
                }
                for (int t = 7000000; t>0; t--);
            }
        }
        }
                        PTB->PTOR|=(1<<19);
                PTB->PTOR|=(1<<18);

    }

    }
    return 0;
  }
void PORTA_IRQhander(void){
    if(PORTA -> ISFR & (1<<13)){
        PORTA -> ISFR |= (1<<13);
        for (t = 7000000; t>0; t--);
        if(a==1){
                a=0;

            }else{
            a=1;
            }
        }
  }
