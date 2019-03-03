#include "api_robot2.h"

#define TRIGGER 1000
#define TEMPO_LOOP 10200
#define V_CURVA 20
#define V_RETA 50

motor_cfg_t m1, m2;
unsigned int contagem_tempo = 0;
unsigned int tempo_atual=0;

void vira();
void reta();
void colisao_esquerda();
void colisao_direita();
    
int main(void) {
    unsigned short sonar;
    
    m1.id = 0;
    m2.id = 1;
    register_proximity_callback(3,TRIGGER,colisao_esquerda);
    register_proximity_callback(4,TRIGGER,colisao_direita);
    reta();
    while(1){};
    return 0;
}

void reta() {
    // anda com o robo
    m1.speed = V_RETA;
    m2.speed = V_RETA;
    set_motors_speed(&m1, &m2);
    set_time(0);
    add_alarm(vira,1+contagem_tempo);    
}

void vira() {
    int i,j;
    contagem_tempo++;
    m1.speed = 0;
    m2.speed = V_CURVA;
    set_motors_speed(&m1, &m2);
    set_time(0);
    for(j=0;j<TEMPO_LOOP;j++)
	for(i=0;i<TEMPO_LOOP;i++);
    reta();
}

void colisao_esquerda(){
    unsigned short s3;
    // vira com o robo
    m1.speed = 0;
    m2.speed = V_CURVA;
    set_motors_speed(&m1, &m2);
    do{
	s3 = read_sonar(3);
    }while(s3<=TRIGGER);
    register_proximity_callback(3,TRIGGER,colisao_esquerda);
    // anda com o robo
    m1.speed = V_RETA;
    m2.speed = V_RETA;
    set_motors_speed(&m1, &m2);
}
void colisao_direita(){
    unsigned short s4;
    // para com o robo
    m1.speed = 0;
    m2.speed = V_CURVA;
    set_motors_speed(&m1, &m2);
    do{
	s4 = read_sonar(4);
    }while(s4<=TRIGGER);
    register_proximity_callback(4,TRIGGER,colisao_direita);
    // anda com o robo
    m1.speed = V_RETA;
    m2.speed = V_RETA;
    set_motors_speed(&m1, &m2);
}
