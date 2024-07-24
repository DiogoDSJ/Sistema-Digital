#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>

int open_device(const char *device_path);
int write_device(int fd, const char *data);
int read_device(int fd, char *buffer, size_t size);
void close_device(int fd);

int verificar_cor(int vermelho, int verde, int azul);
int verificar_cordenadas(int x, int y);
int verificar_cordenadas_poligono(int x, int y);
int verificar_tamanho(int tamanho);
int verificar_sprite(int sprite);
int verificar_registrador(int registrador);
int verificar_bloco(int bloco);
int verificar_endereco(int endereco);

int editar_sprite(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int endereco, int vermelho, int verde, int azul);
int editar_bloco_background(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int x, int y, int vermelho, int verde, int azul);
int print_quadrado(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int endereco, int x, int y, int tamanho, int vermelho, int verde, int azul);
int print_triangulo(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int endereco, int x, int y, int tamanho, int vermelho, int verde, int azul);
int print_sprite(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, uint32_t ativar_sprite, int x, int y, int sprite, int registrador);
int set_background(int fd, uint32_t* DATA_A_ptr, uint32_t* DATA_B_ptr, int vermelho, int verde, int azul);

void palavra_you(int r, int g, int b);
void palavra_won(int r, int g, int b);
void palavra_game(int r, int g, int b);
void palavra_over(int r, int g, int b);
void letra_verde(int r,int g,int b);
void letra_branca(int r, int g,int b);
void letra_vermelha(int r,int g,int b);

void setar();
void setar_sprites();
void setar_sprites(void);
void *obstaculo();
void *obstaculo_velocidade_diferente();
void *habilidade_parar();
void voce_ganhou();
void voce_perdeu();
int jogo();

void *mousefik(void *arg);
 void *botao(void *arg);



extern uint32_t dataA;
extern uint32_t dataB;
extern int fd;
extern pthread_mutex_t mutex;

extern int colidiu;
extern int habilidade;
extern int diminuir_display;
extern int ativar_sprite;


extern int coodx, coody;
extern int jogo_comecou;
extern int cheat;
extern int obj7;
extern int loop1;
extern int dir;
extern int dir2;
extern int pause_jogo;
extern int dir_x1_x2;
extern int dir_y3_y4;

extern volatile int *HEX5_ptr;
extern volatile int *HEX4_ptr;
extern volatile int *HEX3_ptr;
extern volatile int *HEX2_ptr;
extern volatile int *HEX1_ptr;
extern volatile int *HEX0_ptr;

#endif /* BIBLIOTECA_H */
