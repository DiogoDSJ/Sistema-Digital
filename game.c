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

// Função para inicializar as variáveis e configurar o sprite principal
void setar(void) {
    int dir = 1;
    int dir2 = 1;
    int dir_x1_x2 = 1;
    int dir_y3_y4 = 1;
    coodx = 139; // Coordenada x inicial do sprite principal
    coody = 54;  // Coordenada y inicial do sprite principal
    ativar_sprite = 1; // Flag para ativar o sprite principal
    habilidade = 0; // Flag para habilidades especiais do sprite principal

    // Desbloqueia o mutex para permitir a impressão do sprite
    pthread_mutex_unlock(&mutex);
    print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1); // Imprime o sprite principal na posição inicial
    *HEX0_ptr = 0b0110000; // Atualiza o display HEX
    pthread_mutex_unlock(&mutex); // Desbloqueia o mutex novamente
    diminuir_display = 3; // Inicializa a variável que controla a diminuição do display
}

// Função para configurar os sprites dos obstáculos
void setar_sprites(void) {
    pthread_mutex_lock(&mutex); // Bloqueia o mutex para evitar condições de corrida

    // Define as coordenadas iniciais dos obstáculos
    int obstaculo_x_1 = 40; 
    int obstaculo_y_1 = 140;
    int obstaculo_x_2 = 100; 
    int obstaculo_y_2 = 200;
    int obstaculo_x_3 = 235; 
    int obstaculo_y_3 = 343;
    int obstaculo_x_4 = 325; 
    int obstaculo_y_4 = 385;
    int obstaculo_x_5 = 420; 
    int obstaculo_y_5 = 343;
    int obstaculo_x_7 = 40;
    int obstaculo_y_7 = 233;
    int obstaculo_x_8 = 120; 
    int obstaculo_y_8 = 354;
    int obstaculo_x_9 = 480;
    int obstaculo_y_9 = 233;
    int obstaculo_x_10 = 560; 
    int obstaculo_y_10 = 354;

    // Imprime os sprites dos obstáculos nas suas posições iniciais
    print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_1, obstaculo_y_1, 1, 3);
    print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_2, obstaculo_y_2, 1, 5);
    print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_3, obstaculo_y_3, 1, 6);
    print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_4, obstaculo_y_4, 1, 7);
    print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_5, obstaculo_y_5, 1, 8);
    print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_7, obstaculo_y_7, 1, 11);
    print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_8, obstaculo_y_8, 1, 10);
    print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_9, obstaculo_y_9, 1, 12);
    print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_10, obstaculo_y_10, 1, 13);
    pthread_mutex_unlock(&mutex); // Desbloqueia o mutex
}

// Função da thread que movimenta os obstáculos
void *obstaculo() {
    struct timespec interval = {0, 8000000}; // Intervalo de tempo para a movimentação dos obstáculos

    // Define as coordenadas iniciais dos obstáculos
    int obstaculo_x_1 = 40;
    int obstaculo_y_1 = 140;
    int obstaculo_x_2 = 100;
    int obstaculo_y_2 = 200;
    int obstaculo_x_3 = 235;
    int obstaculo_y_3 = 343;
    int obstaculo_x_4 = 325;
    int obstaculo_y_4 = 385;
    int obstaculo_x_5 = 420;
    int obstaculo_y_5 = 343;

    while(loop1) { // Loop contínuo enquanto o jogo está ativo
        colidiu = 0; // Reseta a variável de colisão
        if(pause_jogo == 0) { // Verifica se o jogo não está pausado
            pthread_mutex_lock(&mutex); // Bloqueia o mutex para evitar condições de corrida
            // Imprime os sprites dos obstáculos
            print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_1, obstaculo_y_1, 1, 3);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_2, obstaculo_y_2, 1, 5);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_3, obstaculo_y_3, 1, 6);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_4, obstaculo_y_4, 1, 7);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_5, obstaculo_y_5, 1, 8);
            pthread_mutex_unlock(&mutex); // Desbloqueia o mutex

            if(habilidade != 1) { // Verifica se uma habilidade especial não está ativa
                // Movimentação dos obstáculos
                if(dir_x1_x2 == 1) {
                    obstaculo_x_1 += 1;
                    obstaculo_x_2 -= 1;
                    if(obstaculo_x_1 > 97) dir_x1_x2 = 2;
                } else if(dir_x1_x2 == 2) {
                    obstaculo_x_1 -= 1;
                    obstaculo_x_2 += 1;
                    if(obstaculo_x_1 < 42) dir_x1_x2 = 1;
                }
                if(dir_y3_y4 == 1) {
                    obstaculo_y_3 += 1;
                    obstaculo_y_4 -= 1;
                    obstaculo_y_5 += 1;
                    if(obstaculo_y_3 > 384) dir_y3_y4 = 2;
                } else if(dir_y3_y4 == 2) {
                    obstaculo_y_3 -= 1;
                    obstaculo_y_4 += 1;
                    obstaculo_y_5 -= 1;
                    if(obstaculo_y_3 < 342) dir_y3_y4 = 1;
                }
            }
        }

        // Verificação de colisão para cada obstáculo
        // COLISÃO sprite 1 do retângulo vertical
        if(obstaculo_x_1 <= coodx + 20 && obstaculo_x_1 + 20 > coodx && obstaculo_y_1 < coody + 20 && obstaculo_y_1 + 20 > coody) {
            coodx = 139;
            coody = 54;
            pthread_mutex_lock(&mutex);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
            pthread_mutex_unlock(&mutex);
            colidiu = 1;
            habilidade = 0;
            printf("TEVE COLISAO\n");
            diminuir_display -= 1;
            printf("variavel reduzida\n");
            alterar_display();
            printf("reduzido no display\n");
        }

        // COLISÃO sprite 2 do retângulo vertical
        if(obstaculo_x_2 <= coodx + 20 && obstaculo_x_2 + 20 > coodx && obstaculo_y_2 < coody + 20 && obstaculo_y_2 + 20 > coody) {
            printf("TEVE COLISAO\n");
            coodx = 139;
            coody = 54;
            pthread_mutex_lock(&mutex);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
            pthread_mutex_unlock(&mutex);
            colidiu = 1;
            habilidade = 0;
            diminuir_display -= 1;
            alterar_display();
            printf("teste;");
        }

        // COLISÃO sprite 3 do retângulo horizontal
        if(obstaculo_x_3 <= coodx + 20 && obstaculo_x_3 + 20 > coodx && obstaculo_y_3 < coody + 20 && obstaculo_y_3 + 20 > coody) {
            printf("TEVE COLISAO\n");
            coodx = 139;
            coody = 54;
            pthread_mutex_lock(&mutex);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
            pthread_mutex_unlock(&mutex);
            colidiu = 1;
            habilidade = 0;
            diminuir_display -= 1;
            alterar_display();
            printf("teste;");
        }

        // COLISÃO sprite 4 do retângulo horizontal
        if(obstaculo_x_4 <= coodx + 20 && obstaculo_x_4 + 20 > coodx && obstaculo_y_4 < coody + 20 && obstaculo_y_4 + 20 > coody) {
            printf("TEVE COLISAO\n");
            coodx = 139;
            coody = 54;
            pthread_mutex_lock(&mutex);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
            pthread_mutex_unlock(&mutex);
            colidiu = 1;
            habilidade = 0;
            diminuir_display -= 1;
            alterar_display();
            printf("teste;");
        }

        // COLISÃO sprite 5 do retângulo horizontal
        if(obstaculo_x_5 <= coodx + 20 && obstaculo_x_5 + 20 > coodx && obstaculo_y_5 < coody + 20 && obstaculo_y_5 + 20 > coody) {
            printf("TEVE COLISAO\n");
            coodx = 139;
            coody = 54;
            pthread_mutex_lock(&mutex);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
            pthread_mutex_unlock(&mutex);
            colidiu = 1;
            habilidade = 0;
            diminuir_display -= 1;
            alterar_display();
            printf("teste;");
        }

        nanosleep(&interval, NULL); // Espera pelo intervalo definido antes de continuar o loop
    }
    pthread_exit(NULL); // Finaliza a thread
}

void *obstaculo_velocidade_diferente(){
    struct timespec interval = {0, 9000000};  // Define um intervalo de 9 milissegundos para o uso na função nanosleep

    // Inicializa as posições iniciais dos obstáculos
    int obstaculo_x_7 = 40; // Posição inicial do obstáculo 7 (x)
    int obstaculo_y_7 = 233; // Posição inicial do obstáculo 7 (y)
    
    int obstaculo_x_8 = 140; // Posição inicial do obstáculo 8 (x)
    int obstaculo_y_8 = 354; // Posição inicial do obstáculo 8 (y)

    int obstaculo_x_9 = 480; // Posição inicial do obstáculo 9 (x)
    int obstaculo_y_9 = 233; // Posição inicial do obstáculo 9 (y)
    
    int obstaculo_x_10 = 560; // Posição inicial do obstáculo 10 (x)
    int obstaculo_y_10 = 354; // Posição inicial do obstáculo 10 (y)

    int obstaculo_x_premio = 584; // Posição inicial do prêmio (x)
    int obstaculo_y_premio = 179; // Posição inicial do prêmio (y)

    // Loop principal da função
    while(1){
        int po;
        // Trava o mutex para garantir que a impressão dos sprites seja atômica
        pthread_mutex_lock(&mutex); 
        // Imprime os sprites dos obstáculos e do prêmio
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_7, obstaculo_y_7, 1, 11);
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_8, obstaculo_y_8, 1, 10);
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_9, obstaculo_y_9, 1, 12);
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_10, obstaculo_y_10, 1, 13);
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_premio, obstaculo_y_premio, 10, 14); // Sprite prêmio
        pthread_mutex_unlock(&mutex);

        // Verifica se a habilidade especial não está ativa
        if(habilidade != 1){
            // Verifica se o jogo não está em pausa
            if(pause_jogo == 0){
                // Movimentação do obstáculo 7 e 9
                if(dir == 1) {
                    obstaculo_x_7 += 4;
                    obstaculo_x_9 += 4;
                    if(obstaculo_x_7 > 168) dir = 2;
                }
                else if(dir == 2){
                    obstaculo_y_7 += 4;
                    obstaculo_y_9 += 4;
                    if(obstaculo_y_7 > 385) dir = 3;
                }
                else if(dir == 3){
                    obstaculo_x_7 -= 4;
                    obstaculo_x_9 -= 4;
                    if(obstaculo_x_7 < 44) dir = 4;
                }
                else if(dir == 4){ 
                    obstaculo_y_7 -= 4;
                    obstaculo_y_9 -= 4;
                    if(obstaculo_y_7 < 239) dir = 1;
                }
                
                // Movimentação do obstáculo 8 e 10
                if(dir2 == 1) {
                    obstaculo_x_8 -= 4;
                    obstaculo_x_10 -= 4;
                    if(obstaculo_x_8 < 90) dir2 = 2;
                }
                else if(dir2 == 2){
                    obstaculo_y_8 -= 4;
                    obstaculo_y_10 -= 4;
                    if(obstaculo_y_8 < 272) dir2 = 3;
                }
                else if(dir2 == 3){ 
                    obstaculo_x_8 += 4;
                    obstaculo_x_10 += 4;
                    if(obstaculo_x_8 > 140) dir2 = 4;
                }
                else if(dir2 == 4){
                    obstaculo_y_8 += 4;
                    obstaculo_y_10 += 4;
                    if(obstaculo_y_8 > 354) dir2 = 1;
                }
            }
        }

        // Verifica colisões com o sprite do jogador para cada obstáculo
        if(obstaculo_x_7 <= coodx+20 && obstaculo_x_7 + 20 > coodx && obstaculo_y_7 < coody+20 && obstaculo_y_7+20 > coody){
            coodx = 139; coody = 54;
            pthread_mutex_lock(&mutex);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
            pthread_mutex_unlock(&mutex);
            habilidade = 0;
            printf("TEVE COLISAO\n");
            diminuir_display -= 1;
            printf("variavel reduzida\n");
            alterar_display();
            printf("reduzido no display\n");
        }

        if(obstaculo_x_8 <= coodx+20 && obstaculo_x_8 + 20 > coodx && obstaculo_y_8 < coody+20 && obstaculo_y_8+20 > coody){
            printf("TEVE COLISAO\n");
            coodx = 139; coody = 54;
            pthread_mutex_lock(&mutex);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
            pthread_mutex_unlock(&mutex);
            habilidade = 0;
            diminuir_display -= 1;
            alterar_display();
        }

        if(obstaculo_x_9 <= coodx+20 && obstaculo_x_9 + 20 > coodx && obstaculo_y_9 < coody+20 && obstaculo_y_9+20 > coody){
            printf("TEVE COLISAO\n");
            coodx = 139; coody = 54;
            pthread_mutex_lock(&mutex);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
            pthread_mutex_unlock(&mutex);
            habilidade = 0;
            diminuir_display -= 1;
            alterar_display();
        }

        if(obstaculo_x_10 <= coodx+20 && obstaculo_x_10 + 20 > coodx && obstaculo_y_10 < coody+20 && obstaculo_y_10+20 > coody){
            printf("TEVE COLISAO\n");
            coodx = 139; coody = 54;
            pthread_mutex_lock(&mutex);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
            pthread_mutex_unlock(&mutex);
            habilidade = 0;
            diminuir_display -= 1;
            alterar_display();
        }

        // Verifica colisão com o prêmio
        if(obstaculo_x_premio <= coodx+20 && obstaculo_x_premio + 20 > coodx && obstaculo_y_premio < coody+20 && obstaculo_y_premio+20 > coody){
            printf("TEVE COLISAO\n");
            printf("PARABENS VOCE GANHOU!!!!!!\n\n\n\n");
            voce_ganhou();
        }

        // Dorme por 9 milissegundos
        nanosleep(&interval, NULL);
    }

    return 0;
    pthread_exit(NULL); // Termina a thread
}

void *habilidade_parar(){
    while(1){
        if(habilidade == 1){ 
            *HEX5_ptr = 0b0001001; // Define um valor no display de 7 segmentos
            sleep(1);
            *HEX5_ptr = 0b1111111; // Apaga o display de 7 segmentos
            habilidade = 2;
        }
    }
    pthread_exit(NULL); // Termina a thread
}

void voce_ganhou(){
    zerar_tudo(); // Reseta todos os componentes do jogo
    palavra_won(0, 5, 0); // Mostra a palavra "WON"
    palavra_you(0, 5, 0); // Mostra a palavra "YOU"
    sleep(2); // Espera por 2 segundos
    palavra_won(0, 0, 0); // Apaga a palavra "WON"
    palavra_you(0, 0, 0); // Apaga a palavra "YOU"
    exit(0); // Encerra o programa
}

void voce_perdeu(){
    zerar_tudo(); // Reseta todos os componentes do jogo
    palavra_game(7, 0, 0); // Mostra a palavra "GAME"
    palavra_over(7, 0, 0); // Mostra a palavra "OVER"
    sleep(2); // Espera por 2 segundos
    palavra_game(0, 0, 0); // Apaga a palavra "GAME"
    palavra_over(0, 0, 0); // Apaga a palavra "OVER"
    exit(0); // Encerra o programa
}

int jogo() {
    const char *device_path = "/dev/driver_dos_amigos"; // Caminho para o dispositivo
    fd = open_device(device_path); // Abre o dispositivo
    char informacao[512]; // Buffer para armazenar informações
    uint32_t dataA = 0; // Variável de dados A
    uint32_t dataB = 0; // Variável de dados B

    pthread_mutex_lock(&mutex); // Trava o mutex para operações seguras de threads
    print_sprite(fd, &dataA, &dataB, ativar_sprite, 138, 58, 25, 1); // Imprime um sprite na posição especificada
    set_background(fd, &dataA, &dataB, 0, 0, 0); // Define o fundo como preto

    // Primeiro retângulo do cenário, depois da largada verde
    for (int i = 5; i <= 14; i++) {
        for (int j = 1; j <= 49; j++) {
            editar_bloco_background(fd, &dataA, &dataB, i, j, 7, 7, 7); // Pinta blocos de fundo
        }
    }
    for (int i = 5; i <= 22; i++) {
        editar_bloco_background(fd, &dataA, &dataB, i, 14, 7, 7, 7); // Pinta blocos de fundo
    }

    // Parte da entrada
    for (int j = 1; j <= 13; j++) {
        editar_bloco_background(fd, &dataA, &dataB, 14, j, 7, 7, 7); // Pinta blocos de fundo
        for (int i = 15; i <= 21; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 1, 7, 7, 7); // Pinta blocos de fundo
        }
        for (int i = 15; i <= 21; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, j, 0, 5, 0); // Pinta blocos de fundo
        }
        editar_bloco_background(fd, &dataA, &dataB, 22, j, 7, 7, 7); // Pinta blocos de fundo
    }

    // Parte da saída
    for (int i = 17; i <= 28; i++) {
        editar_bloco_background(fd, &dataA, &dataB, 70, i, 7, 7, 7); // Pinta blocos de fundo
        for (int j = 70; j <= 78; j++) {
            editar_bloco_background(fd, &dataA, &dataB, j, 17, 7, 7, 7); // Pinta blocos de fundo
        }
        for (int j = 71; j <= 77; j++) {
            editar_bloco_background(fd, &dataA, &dataB, j, i, 7, 0, 0); // Pinta blocos de fundo (colisão)
        }
        editar_bloco_background(fd, &dataA, &dataB, 78, i, 7, 7, 7); // Pinta blocos de fundo
    }

    // Preenchimento do primeiro retângulo do cenário (parte branca)
    for (int i = 5; i <= 24; i++) {
        for (int j = 29; j <= 50; j++) {
            editar_bloco_background(fd, &dataA, &dataB, i, j, 7, 7, 7); // Pinta blocos de fundo
        }
    }
    for (int i = 60; i <= 78; i++) {
        for (int j = 29; j <= 50; j++) {
            editar_bloco_background(fd, &dataA, &dataB, i, j, 7, 7, 7); // Pinta blocos de fundo
        }
    }

    // Retângulo deitado branco
    for (int i = 25; i <= 59; i++) {
        for (int j = 43; j <= 50; j++) {
            editar_bloco_background(fd, &dataA, &dataB, i, j, 7, 7, 7); // Pinta blocos de fundo
        }
    }
    for (int i = 13; i <= 75; i++) {
        editar_bloco_background(fd, &dataA, &dataB, i, 49, 7, 7, 7); // Pinta blocos de fundo
    }

    // Linha invisível
    for (int i = 10000; i < 10020; i++) {
        editar_sprite(fd, &dataA, &dataB, i, 6, 7, 7); // Pinta sprites invisíveis
    }
    for (int i = 10020; i < 10040; i++) {
        editar_sprite(fd, &dataA, &dataB, i, 6, 7, 7); // Pinta sprites invisíveis
    }

    for (int i = 10027; i < 10033; i++) {
        editar_sprite(fd, &dataA, &dataB, i, 5, 5, 0); // Pinta sprites amarelos
    }

    for (int i = 10047; i < 10053; i++) {
        editar_sprite(fd, &dataA, &dataB, i, 5, 5, 0); // Pinta sprites amarelos
    }

    for (int i = 10065; i < 10075; i++) {
        editar_sprite(fd, &dataA, &dataB, i, 5, 5, 0); // Pinta sprites amarelos
    }

    for (int i = 10084; i < 10096; i++) {
        editar_sprite(fd, &dataA, &dataB, i, 5, 5, 0); // Pinta sprites amarelos
    }

    // Retângulo
    for (int i = 10100; i < 10300; i++) {
        editar_sprite(fd, &dataA, &dataB, i, 5, 5, 0); // Pinta sprites amarelos
    }

    for (int i = 10182; i < 10198; i++) {
        editar_sprite(fd, &dataA, &dataB, i, 5, 5, 0); // Pinta sprites amarelos
    }

    int invisivel = 1; // RGB(6, 7, 7)
    int amarelo = 2; // RGB(7, 6, 1)
    int preto = 3; // RGB(0, 0, 0)
    int branco = 4; // RGB(7, 7, 7)
    int rosa = 5; // RGB(7, 6, 6)
    int imagem[21][20] = {
        // Matriz para representar a imagem com diferentes cores

        // Curvatura do início
        {invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel},
        {invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, preto, preto, preto, preto, preto, preto, preto, preto, invisivel, invisivel, invisivel, invisivel, invisivel},
        {invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, invisivel, invisivel, invisivel, invisivel},
        {invisivel, invisivel, invisivel, invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, invisivel, invisivel, invisivel},
        {invisivel, invisivel, invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, invisivel, invisivel},
        {invisivel, invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, invisivel},
        
        // Meio
        {invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto},
        {invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto},
        {invisivel, invisivel, preto, amarelo, amarelo, amarelo, preto, branco, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, branco, amarelo, amarelo, amarelo, preto},
        {invisivel, invisivel, preto, amarelo, amarelo, amarelo, preto, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, preto, amarelo, amarelo, amarelo, preto},
        {invisivel, invisivel, preto, amarelo, amarelo, amarelo, preto, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, preto, amarelo, amarelo, amarelo, preto},
        {invisivel, invisivel, preto, amarelo, amarelo, amarelo, preto, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, preto, amarelo, amarelo, amarelo, preto},
        {invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto},
        {invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, preto, preto, preto, preto, amarelo, amarelo, amarelo, amarelo, amarelo, preto},
        {invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto},

        // Curvatura do final
        {invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto},
        {invisivel, invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, invisivel},
        {invisivel, invisivel, invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, invisivel, invisivel},
        {invisivel, invisivel, invisivel, invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, invisivel, invisivel, invisivel},
        {invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, preto, preto, preto, preto, preto, preto, preto, preto, preto, preto, invisivel, invisivel, invisivel, invisivel},
        {invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel}
    };

    pthread_mutex_unlock(&mutex); // Destrava o mutex
    int endereco = 10000; // Endereço inicial dos sprites
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 20; j++) {
            int r, g, b; // Variáveis para armazenar as cores
            int cor = imagem[i][j]; // Cor da posição atual da matriz
            if (cor == 1) {
                r = 6;
                g = 7;
                b = 7;
            }
            if (cor == 2) {
                r = 7;
                g = 6;
                b = 1;
            }
            if (cor == 3) {
                r = 0;
                g = 0;
                b = 0;
            }
            if (cor == 4) {
                r = 7;
                g = 7;
                b = 7;
            }
            if (cor == 5) {
                r = 7;
                g = 6;
                b = 6;
            }
            editar_sprite(fd, &dataA, &dataB, endereco, r, g, b); // Edita o sprite com as cores definidas
            endereco++;
        }
    }

    printf("vou iniciar as threads\n\n\n"); // Mensagem de debug
    chamar_threads(); // Chama a função para iniciar as threads

    // Buffer para armazenar a leitura do dispositivo
    char buffer[100];
    if (read_device(fd, buffer, sizeof(buffer)) < 0) {
        close_device(fd); // Fecha o dispositivo se falhar
        return EXIT_FAILURE;
    }

    // Fecha o dispositivo
    close_device(fd);
    return EXIT_SUCCESS;
}
