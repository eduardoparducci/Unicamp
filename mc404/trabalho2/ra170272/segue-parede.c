#include "api_robot2.h"

#define WALL_APROX_THRESHOLD 1200
#define WALL_LOSS_THRESHOLD 1500
#define WALL_THRESHOLD 1000
#define VELOCIDADE_RETA 50
#define VELOCIDADE_LENTA 10

motor_cfg_t m1, m2;
unsigned short achou_parede=0;
void parede_esq();
void parede_dir();
void vira_dir();
void vira_esq();
void emparelha();
void acompanha_parede();
void evita_colisao_frontal();
void evita_colisao_lateral();

int main(void) {
    unsigned short sonar;

    m1.id = 0;
    m2.id = 1;

    register_proximity_callback(3, WALL_APROX_THRESHOLD, parede_esq); 
    register_proximity_callback(4, WALL_APROX_THRESHOLD, parede_dir); 
    // anda em linha reta
    m1.speed = VELOCIDADE_RETA;
    m2.speed = VELOCIDADE_RETA;
    set_motors_speed(&m1, &m2);

    while (1) {
    }

    return 0;
}

void parede_esq(){
    unsigned short s3, s4;
    // reduz a velocidade do robo
    m1.speed = VELOCIDADE_LENTA;
    m2.speed = VELOCIDADE_LENTA;
    set_motors_speed(&m1, &m2);
    do{
	s3=read_sonar(3);
	s4=read_sonar(4);
    }while(s3>WALL_THRESHOLD && s4>WALL_THRESHOLD);
    // para o robo
    m1.speed = 0;
    m2.speed = 0;
    set_motors_speed(&m1, &m2);
    if(!achou_parede){
	register_proximity_callback(1, WALL_THRESHOLD, evita_colisao_lateral);
	register_proximity_callback(3, WALL_THRESHOLD, evita_colisao_frontal);
    }
    achou_parede = 1;
    emparelha();
}

void parede_dir(){
    unsigned short s3, s4;
    // reduz a velocidade do robo
    m1.speed = VELOCIDADE_LENTA;
    m2.speed = VELOCIDADE_LENTA;
    set_motors_speed(&m1, &m2);
    do{
	s3=read_sonar(3);
	s4=read_sonar(4);
    }while(s3>WALL_THRESHOLD && s4>WALL_THRESHOLD);
    // para o robo
    m1.speed = 0;
    m2.speed = 0;
    set_motors_speed(&m1, &m2);
    if(!achou_parede){
	register_proximity_callback(1, WALL_THRESHOLD, evita_colisao_lateral);
	register_proximity_callback(3, WALL_THRESHOLD, evita_colisao_frontal);
    }
    achou_parede = 1;
    emparelha();
}

void emparelha() {
    unsigned short s0, s0_;

    // vira o robo para a direita
    m1.speed = 0;
    m2.speed = VELOCIDADE_LENTA;
    set_motors_speed(&m1, &m2);
    s0=read_sonar(0);
    s0_=s0+100;
    while(s0_>s0 || s0>WALL_THRESHOLD){
	s0_=s0;
	s0=read_sonar(0);
    }
    // para o robo
    m1.speed = 0;
    m2.speed = 0;
    set_motors_speed(&m1, &m2);
    acompanha_parede();

}
void vira_dir() {
    unsigned short s2;

    // vira o robo para a direita
    m1.speed = 0;
    m2.speed = VELOCIDADE_LENTA;
    set_motors_speed(&m1, &m2);
    s2=read_sonar(3);
    while(s2>WALL_THRESHOLD && s2<WALL_LOSS_THRESHOLD){
	s2=read_sonar(3);
    }
    // anda reto
    //m1.speed = VELOCIDADE_LENTA;
    //m2.speed = VELOCIDADE_LENTA;
    //set_motors_speed(&m1, &m2);
}

void vira_esq() {
    unsigned short s2;

    // vira o robo para a esquerda
    m1.speed = VELOCIDADE_LENTA;
    m2.speed = 0;    
    set_motors_speed(&m1, &m2);
    s2=read_sonar(3);
    while(s2>WALL_THRESHOLD){
	s2=read_sonar(3);
    }
    // anda reto
    //m1.speed = VELOCIDADE_LENTA;
    //m2.speed = VELOCIDADE_LENTA;
    //set_motors_speed(&m1, &m2);
}
void acompanha_parede(){
    unsigned short s2, s0;
    
    // anda para frente
    m1.speed = VELOCIDADE_LENTA;
    m2.speed = VELOCIDADE_LENTA;
    set_motors_speed(&m1, &m2);

    s2=read_sonar(2);
    while(s2<WALL_LOSS_THRESHOLD && s2>WALL_THRESHOLD){
	s2=read_sonar(2);
    }
    if(s2>=WALL_LOSS_THRESHOLD) vira_esq();
    else vira_dir();
    m1.speed = VELOCIDADE_LENTA;
    m2.speed = VELOCIDADE_LENTA;
    set_motors_speed(&m1, &m2);
}

void evita_colisao_frontal(){
    unsigned short s3;
    // vira o robo ate uma distancia segura
    m1.speed = 0;
    m2.speed = VELOCIDADE_LENTA;
    set_motors_speed(&m1, &m2);
    do{
	s3=read_sonar(3);
    }while(s3<WALL_THRESHOLD);
    register_proximity_callback(3, WALL_THRESHOLD, evita_colisao_frontal);
    acompanha_parede();
}

void evita_colisao_lateral(){
    unsigned short s1;
    // vira o robo ate uma distancia segura
    m1.speed = 0;
    m2.speed = VELOCIDADE_LENTA;
    set_motors_speed(&m1, &m2);
    do{
	s1=read_sonar(1);
    }while(s1<WALL_THRESHOLD);
    register_proximity_callback(1, WALL_THRESHOLD, evita_colisao_lateral);
    acompanha_parede();
}
