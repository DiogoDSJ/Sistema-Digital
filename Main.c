#include "biblioteca.h" 
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>
#include <linux/input.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <sys/mman.h>
#include "address_map_arm.h"

// Variáveis globais para dados e controle de threads e estado do jogo
uint32_t dataA= 0;
uint32_t dataB= 0;
int fd;
pthread_mutex_t mutex;
pthread_t threads[10];

int colidiu = 0;
int habilidade = 0;
int diminuir_display = 3;
int ativar_sprite = 1;

int coodx = 136, coody = 58;
int jogo_comecou = 0;
int cheat = 0;
int obj7 = 1;
int loop1 = 1;
int dir = 1;
int dir2 = 1;
int pause_jogo = 0;
int dir_x1_x2 = 1;
int dir_y3_y4 = 1;

#define MOUSE_DEV "/dev/input/event0"

// Definições das bases dos displays de 7 segmentos
#define HEX5_BASE 0x10
#define HEX4_BASE 0x20
#define HEX3_BASE 0x30
#define HEX2_BASE 0x40
#define HEX1_BASE 0x50
#define HEX0_BASE 0x60

// Ponteiros de endereço virtual para os dígitos do display de 7 segmentos
volatile int *HEX5_ptr;
volatile int *HEX4_ptr;
volatile int *HEX3_ptr;
volatile int *HEX2_ptr;
volatile int *HEX1_ptr;
volatile int *HEX0_ptr;

// Função para pausar o jogo
void pausar() {
    if (pause_jogo == 0) pause_jogo = 1;
    else pause_jogo = 0;
}

// Função para alterar os valores exibidos nos displays de 7 segmentos
void alterar_display() {
    if (diminuir_display == 3) {
        *HEX0_ptr = 0b0110000; 
    } else if (diminuir_display == 2) {
        *HEX0_ptr = 0b0100100;
    } else if (diminuir_display == 1) {
        *HEX0_ptr = 0b1111001;
    } else {
        *HEX0_ptr = 0b0111111;
        zerar_tudo();
        sleep(1);
        voce_perdeu();
        exit(0);
    }
}

// Função para resetar o cenário do jogo
void zerar_tudo() {
    int dir = 1;
    int dir2 = 1;
    int dir_x1_x2 = 1;
    int dir_y3_y4 = 1;
    int habilidade = 0;
    set_background(fd, &dataA, &dataB, 0, 0, 0);

    // Configuração inicial do cenário
    for (int i = 5; i <= 14; i++) {
        for (int j = 1; j <= 49; j++) {
            pthread_mutex_lock(&mutex); 
            editar_bloco_background(fd, &dataA, &dataB, i, j, 0, 0, 0);
            pthread_mutex_unlock(&mutex); 
        }
    }

    // Configurações adicionais de cenário
    for (int i = 5; i <= 22; i++) {
        pthread_mutex_lock(&mutex); 
        editar_bloco_background(fd, &dataA, &dataB, i, 14, 0, 0, 0);
        pthread_mutex_unlock(&mutex); 
    }

    for (int j = 1; j <= 13; j++) {
        pthread_mutex_lock(&mutex); 
        editar_bloco_background(fd, &dataA, &dataB, 14, j, 0, 0, 0);
        pthread_mutex_unlock(&mutex); 
        for (int i = 15; i <= 21; i++) {
            pthread_mutex_lock(&mutex); 
            editar_bloco_background(fd, &dataA, &dataB, i, 1, 0, 0, 0);
            pthread_mutex_unlock(&mutex); 
        } 
        for (int i = 15; i <= 21; i++) {
            pthread_mutex_lock(&mutex); 
            editar_bloco_background(fd, &dataA, &dataB, i, j, 0, 0, 0);
            pthread_mutex_unlock(&mutex); 
        }
        pthread_mutex_lock(&mutex); 
        editar_bloco_background(fd, &dataA, &dataB, 22, j, 0, 0, 0);
        pthread_mutex_unlock(&mutex); 
    }

    // Configuração da saída do cenário
    for (int i = 17; i <= 28; i++) {
        pthread_mutex_lock(&mutex); 
        editar_bloco_background(fd, &dataA, &dataB, 70, i, 0, 0, 0);
        pthread_mutex_unlock(&mutex); 
        for (int j = 70; j <= 78; j++) {
            pthread_mutex_lock(&mutex); 
            editar_bloco_background(fd, &dataA, &dataB, j, 17, 0, 0, 0);
            pthread_mutex_unlock(&mutex); 
        }
        for (int j = 71; j <= 77; j++) {
            pthread_mutex_lock(&mutex); 
            editar_bloco_background(fd, &dataA, &dataB, j, i, 0, 0, 0);
            pthread_mutex_unlock(&mutex); 
        }
        pthread_mutex_lock(&mutex); 
        editar_bloco_background(fd, &dataA, &dataB, 78, i, 0, 0, 0);
        pthread_mutex_unlock(&mutex); 
    }

    // Configuração do primeiro retângulo do cenário (parte branca)
    for (int i = 5; i <= 24; i++) {
        for (int j = 29; j <= 50; j++) {
            pthread_mutex_lock(&mutex); 
            editar_bloco_background(fd, &dataA, &dataB, i, j, 0, 0, 0);
            pthread_mutex_unlock(&mutex); 
        }
    }

    for (int i = 60; i <= 78; i++) {
        for (int j = 29; j <= 50; j++) {
            pthread_mutex_lock(&mutex); 
            editar_bloco_background(fd, &dataA, &dataB, i, j, 0, 0, 0);
            pthread_mutex_unlock(&mutex); 
        }
    }

    // Configuração do retângulo deitado branco
    for (int i = 25; i <= 59; i++) {
        for (int j = 43; j <= 50; j++) {
            pthread_mutex_lock(&mutex); 
            editar_bloco_background(fd, &dataA, &dataB, i, j, 0, 0, 0);
            pthread_mutex_unlock(&mutex); 
        }
    } 

    for (int i = 13; i <= 75; i++) {
        pthread_mutex_lock(&mutex); 
        editar_bloco_background(fd, &dataA, &dataB, i, 49, 0, 0, 0);
        pthread_mutex_unlock(&mutex); 
    }

    // Configuração do sprite emoji
    pthread_mutex_lock(&mutex); 
    print_sprite(fd, &dataA, &dataB, ativar_sprite, 138, 58, 25, 1);
    pthread_mutex_unlock(&mutex); 

    // Configuração dos sprites da primeira thread
    pthread_mutex_lock(&mutex); 
    ativar_sprite = 0;
    pthread_mutex_unlock(&mutex);

    for (int i = 0; i < 16; i++) {
        print_sprite(fd, &dataA, &dataB, ativar_sprite, 138, 58, 25, i);
    }
}

// Função para chamar threads
int chamar_threads() {
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&(threads[0]), NULL, mousefik, NULL);
    pthread_create(&(threads[1]), NULL, botao, NULL);
    pthread_create(&(threads[2]), NULL, obstaculo, NULL);
    pthread_create(&(threads[3]), NULL, obstaculo_velocidade_diferente, NULL);
    pthread_create(&(threads[4]), NULL, habilidade_parar, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);
    pthread_join(threads[4], NULL);

    pthread_cancel(threads[0]);
    pthread_cancel(threads[1]);
    pthread_cancel(threads[2]);
    pthread_cancel(threads[3]);
    pthread_cancel(threads[4]);

    pthread_mutex_destroy(&mutex);

    return 0;
}

// Função para limpar todo o cenário
void limpa_tudo() {
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < 60; j++) {
            editar_bloco_background(fd, &dataA, &dataB, i, j, 0, 0, 0);
        }
    }
}

// Função para configurar e inicializar os displays de 7 segmentos
void display() {
    // Usado para abrir /dev/mem
    int fd = -1;

    // Endereços físicos para a ponte (light-weight bridge)
    void *LW_virtual;
    // Abrir /dev/mem para dar acesso a endereços físicos
    if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        return;
    }

    // Obter um mapeamento de endereços físicos para endereços virtuais
    LW_virtual = mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
    if (LW_virtual == MAP_FAILED) {
        printf("ERROR: mmap() failed...\n");
        close(fd);
        return;
    }

    // Mapear os endereços dos displays de 7 segmentos para ponteiros virtuais
    pthread_mutex_lock(&mutex); 
    HEX5_ptr = (int *)(LW_virtual + HEX5_BASE);
    HEX4_ptr = (int *)(LW_virtual + HEX4_BASE);
    HEX3_ptr = (int *)(LW_virtual + HEX3_BASE);
    HEX2_ptr = (int *)(LW_virtual + HEX2_BASE);
    HEX1_ptr = (int *)(LW_virtual + HEX1_BASE);
    HEX0_ptr = (int *)(LW_virtual + HEX0_BASE);
    pthread_mutex_unlock(&mutex);

    // Configurar os valores iniciais dos displays
    *HEX1_ptr = 0b01000000;
    *HEX2_ptr = 0b1111111;
    *HEX3_ptr = 0b1111111;
    *HEX4_ptr = 0b1111111;
    *HEX5_ptr = 0b1111111;

    // Chamar a função para alterar os valores dos displays conforme necessário
    alterar_display();

    // Fechar o mapeamento de endereço virtual
    if (munmap(LW_virtual, LW_BRIDGE_SPAN) != 0) {
        printf("ERROR: munmap() failed...\n");
        return;
    }

    // Fechar /dev/mem
    close(fd);
}

// Função para inicializar o jogo
void inicio() {
    const char *device_path = "/dev/driver_dos_amigos"; 
    fd = open_device(device_path); // Abre o dispositivo
    limpa_tudo();
    zerar_tudo();
    pthread_mutex_lock(&mutex); 
    set_background(fd, &dataA, &dataB, 0, 0, 0);
    pthread_mutex_unlock(&mutex);

    // Configurar tela iniciail do jogo
    letra_verde(0, 5, 0);
    letra_branca(7, 7, 7);
    letra_vermelha(7, 0, 0);

    // Mapear o endereço virtual para acessar as chaves
    volatile int *KEY_ptr;
    int fd = -1;
    void *LW_virtual;

    // Abrir /dev/mem para dar acesso a endereços físicos
    if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        return;
    }

    // Obter um mapeamento de endereços físicos para endereços virtuais
    LW_virtual = mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
    if (LW_virtual == MAP_FAILED) {
        printf("ERROR: mmap() failed...\n");
        close(fd);
        return;
    }

    // Mapear o endereço das chaves
    KEY_ptr = (int *)(LW_virtual + 0x0);

    int estado = 0;

    // Loop principal para monitorar o botão KEY0 e iniciar o jogo
    while (1) {
        if (*KEY_ptr == 14 && estado == 0) {
            printf("Botao KEY 0 foi clicado para setar \n");
            letra_verde(0, 0, 0);
            letra_branca(0, 0, 0);
            letra_vermelha(0, 0, 0);

            setar();
            jogo();
            estado = 1;
        }
        if (estado == 1 && *KEY_ptr != 14) {
            estado = 0;
        }
    }
}

// Função principal
int main() {
    display(); // Inicializa os displays de 7 segmentos
    inicio();  // Inicializa o jogo
}
