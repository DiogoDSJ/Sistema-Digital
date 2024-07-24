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


void setar(void){
        
        int dir = 1;
        int dir2 = 1;
        int dir_x1_x2 = 1;
        int dir_y3_y4 = 1;
        setar_sprites();
        coodx = 139;coody = 54;
        ativar_sprite = 1;
        pthread_mutex_unlock(&mutex);     
        print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
        *HEX0_ptr = 0b0110000;
        pthread_mutex_unlock(&mutex); 
        diminuir_display = 3;
        
}

void setar_sprites(void){
        pthread_mutex_lock(&mutex);
        int obstaculo_x_1 = 40; // Posição inicial do obstáculo
        int obstaculo_y_1 = 140;
        int obstaculo_x_2 = 100; 
        int obstaculo_y_2 = 200;
        //retangulo pequeno horizontal
        int obstaculo_x_3 = 235; 
        int obstaculo_y_3 = 343;
        int obstaculo_x_4 = 325; 
        int obstaculo_y_4 = 385;
        int obstaculo_x_5 = 420; 
        int obstaculo_y_5 = 343;
        int obstaculo_x_7 = 40; // Posição inicial do obstáculo
        int obstaculo_y_7 = 233; // Posição inicial do obstáculo
        int obstaculo_x_8 = 120; 
        int obstaculo_y_8 = 354;
        int obstaculo_x_9 = 480; // Posição inicial do obstáculo
        int obstaculo_y_9 = 233; // Posição inicial do obstáculo
        int obstaculo_x_10 = 560; 
        int obstaculo_y_10 = 354;
        
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_1, obstaculo_y_1, 1, 3); 
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_2, obstaculo_y_2, 1, 5); 
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_3, obstaculo_y_3, 1, 6);
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_4, obstaculo_y_4, 1, 7);
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_5, obstaculo_y_5, 1, 8);
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_7, obstaculo_y_7, 1, 11); //colocar para printar sprite aq
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_8, obstaculo_y_8, 1, 10);
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_9, obstaculo_y_9, 1, 12);
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_10, obstaculo_y_10, 1, 13);
        pthread_mutex_unlock(&mutex); 
}

void *obstaculo(){
    //sem_wait(&semaforo);
    struct timespec interval = {0, 8000000};
   
    //retandulo pequeno vertical
     // Posição inicial do obstáculo
    int obstaculo_x_1 = 40; // Posição inicial do obstáculo
    int obstaculo_y_1 = 140;
    int obstaculo_x_2 = 100; 
    int obstaculo_y_2 = 200;


    //retangulo pequeno horizontal
    int obstaculo_x_3 = 235; 
    int obstaculo_y_3 = 343;

    int obstaculo_x_4 = 325; 
    int obstaculo_y_4 = 385;

    int obstaculo_x_5 = 420; 
    int obstaculo_y_5 = 343;
    

    while(loop1){
        colidiu = 0;
        if(pause_jogo == 0){

            pthread_mutex_lock(&mutex);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_1, obstaculo_y_1, 1, 3); 
            print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_2, obstaculo_y_2, 1, 5); 
            print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_3, obstaculo_y_3, 1, 6);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_4, obstaculo_y_4, 1, 7);
            print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_5, obstaculo_y_5, 1, 8);
            pthread_mutex_unlock(&mutex); 
            if(habilidade != 1){
                if(dir_x1_x2 == 1) {
                    obstaculo_x_1 += 2;
                    obstaculo_x_2 -= 2;
                    if(obstaculo_x_1 > 97) dir_x1_x2 = 2;
                }
                else if(dir_x1_x2 == 2){
                    obstaculo_x_1 -= 2;
                    obstaculo_x_2 += 2;
                    if(obstaculo_x_1 < 42) dir_x1_x2 = 1;
                }
                if(dir_y3_y4 == 1){
                    obstaculo_y_3 +=1; 
                    obstaculo_y_4 -=1;
                    obstaculo_y_5 +=1;
                    if(obstaculo_y_3 > 384) dir_y3_y4 = 2;
                }
                else if(dir_y3_y4 == 2){
                    obstaculo_y_3 -=1;
                    obstaculo_y_4 +=1;
                    obstaculo_y_5 -=1;
                    if(obstaculo_y_3 < 342) dir_y3_y4 = 1;
                }
            }
        }
        //COLISAO sprite 1 do retangulo vertical
        if(obstaculo_x_1 <= coodx+20 && obstaculo_x_1 + 20 > coodx && obstaculo_y_1 < coody+20 && obstaculo_y_1+20> coody){
            coodx = 139;coody = 54;
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
            colidiu = 1;

            printf("TEVE COLISAO\n");
            diminuir_display-=1;
            printf("variavel reduzida\n");
            alterar_display();
            printf("reduzido no display\n");
        }

        //COLISAO sprite 2 do retangulo vertical
        if(obstaculo_x_2 <= coodx+20 && obstaculo_x_2 + 20 > coodx && obstaculo_y_2 < coody+20 && obstaculo_y_2+20> coody){
            printf("TEVE COLISAO\n");
            coodx = 139;coody = 54;
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
            colidiu = 1;

            diminuir_display-=1;
            alterar_display();
            printf("teste;");
        }

        //COLISAO sprite 3 do retangulo horizontal
        if(obstaculo_x_3 <= coodx+20 && obstaculo_x_3 + 20 > coodx && obstaculo_y_3 < coody+20 && obstaculo_y_3+20> coody){
            printf("TEVE COLISAO\n");
            coodx = 139;coody = 54;
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
            colidiu = 1;

            diminuir_display-=1;
            alterar_display();
            printf("teste;");
        }

        //COLISAO sprite 4 do retangulo horizontal
        if(obstaculo_x_4 <= coodx+20 && obstaculo_x_4 + 20 > coodx && obstaculo_y_4 < coody+20 && obstaculo_y_4+20> coody){
            printf("TEVE COLISAO\n");
            coodx = 139;coody = 54;
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
            colidiu = 1;

            diminuir_display-=1;
            alterar_display();
            printf("teste;");
        }

        //COLISAO sprite 5 do retangulo horizontal
        if(obstaculo_x_5 <= coodx+20 && obstaculo_x_5 + 20 > coodx && obstaculo_y_5 < coody+20 && obstaculo_y_5+20> coody){
            printf("TEVE COLISAO\n");
            coodx = 139;coody = 54;
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
            colidiu = 1;

            diminuir_display-=1;
            alterar_display();
            printf("teste;");
        }
        
        

        nanosleep(&interval, NULL);
        
        
    }
   //
    pthread_exit(NULL);
    return 0;
}

void *obstaculo_velocidade_diferente(){
  
    struct timespec interval = {0, 9000000};

    //retandulo pequeno vertical
    int obstaculo_x_7 = 40; // Posição inicial do obstáculo
    int obstaculo_y_7 = 233; // Posição inicial do obstáculo
    
    int obstaculo_x_8 = 140; 
    int obstaculo_y_8 = 354;



    int obstaculo_x_9 = 480; // Posição inicial do obstáculo
    int obstaculo_y_9 = 233; // Posição inicial do obstáculo
    
    int obstaculo_x_10 = 560; 
    int obstaculo_y_10 = 354;


    int obstaculo_x_premio = 584; 
    int obstaculo_y_premio = 179;



    while(1){
        int po;
        //sprite 1
        int distancia_sprite_1;
        if(pause_jogo == 0)  distancia_sprite_1 = 44;
        else distancia_sprite_1 = 0;
        pthread_mutex_lock(&mutex); 
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_7, obstaculo_y_7, 1, 11); //colocar para printar sprite aq
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_8, obstaculo_y_8, 1, 10);
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_9, obstaculo_y_9, 1, 12);
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_10, obstaculo_y_10, 1, 13);
        print_sprite(fd, &dataA, &dataB, ativar_sprite, obstaculo_x_premio, obstaculo_y_premio, 10, 14); //sprite premio
        pthread_mutex_unlock(&mutex);
        if(habilidade != 1){
            if(pause_jogo == 0){
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
        /*
        if(obstaculo_x_7 == 172 && obj7 == 1){
            if(obstaculo_y_7 < 385){
                obstaculo_y_7 += 3;
                printf("desceu\n");
            }
            else{
                obj7 = 2;
            }
        }
        if (i < distancia_sprite_1 && obj7 == 1){
            if(obj7 == 1) obstaculo_x_7 += 3;
            obstaculo_x_8 += 3;
            obstaculo_x_9 += 3;
            obstaculo_x_10 += 3;
        }
        else{
            if(obj7 == 2) obstaculo_x_7 -= 3;
            obstaculo_x_8 -= 3; 
            obstaculo_x_9 -= 3;
            obstaculo_x_10 -= 3;
            if(obstaculo_x_7 == 40) obj7 = 1;
        }
        if(obj7 == 2){
            if(obstaculo_y_7 > 240){
                obstaculo_y_7 -= 1;
            }
            else{
                obj7 = 1;
            }
        }
        */
        //printf("%d\n", obstaculo_x_7);
    

        //printf("obj: %d\n", obj7);
        //COLISAO 1 SPRITE DO QUADRADO DA ESQUERDA
        if(obstaculo_x_7 <= coodx+20 && obstaculo_x_7 + 20 > coodx && obstaculo_y_7 < coody+20 && obstaculo_y_7+20> coody){
            
            coodx = 139;coody = 54;
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);

            printf("TEVE COLISAO\n");
            diminuir_display-=1;
            printf("variavel reduzida\n");
            alterar_display();
            printf("reduzido no display\n");
        }

        //COLISAO 2 SPRITE DO QUADRADO DA ESQUERDA
        if(obstaculo_x_8 <= coodx+20 && obstaculo_x_8 + 20 > coodx && obstaculo_y_8 < coody+20 && obstaculo_y_8+20> coody){
            printf("TEVE COLISAO\n");
            coodx = 139;coody = 54;
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);

            diminuir_display-=1;
            alterar_display();
        }


        //COLISAO 4 SPRITE DO QUADRADO DA DIREITA
        if(obstaculo_x_9 <= coodx+20 && obstaculo_x_9 + 20 > coodx && obstaculo_y_9 < coody+20 && obstaculo_y_9+20> coody){
            printf("TEVE COLISAO\n");
            coodx = 139;coody = 54;
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);

            diminuir_display-=1;
            alterar_display();
        }


        //COLISAO 5 SPRITE DO QUADRADO DA DIREITA
        if(obstaculo_x_10 <= coodx+20 && obstaculo_x_10 + 20 > coodx && obstaculo_y_10 < coody+20 && obstaculo_y_10+20> coody){
            printf("TEVE COLISAO\n");
            coodx = 139;coody = 54;
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);

            diminuir_display-=1;
            alterar_display();
        }

        if(obstaculo_x_premio <= coodx+20 && obstaculo_x_premio + 20 > coodx && obstaculo_y_premio < coody+20 && obstaculo_y_premio+20> coody){
            printf("TEVE COLISAO\n");
            printf("PARABENS VOCE GANHOU!!!!!!\n\n\n\n");
            voce_ganhou();
        }

        nanosleep(&interval, NULL);
        
    }

    return 0;
   pthread_exit(NULL);
}

void *habilidade_parar(){
       
        while(1){
            if(habilidade == 1){ 
                *HEX5_ptr = 0b0001001;
                sleep(1);
                *HEX5_ptr = 0b1111111;
                habilidade = 2;
            }
        }
        pthread_exit(NULL);
        //return 0;
}


void voce_ganhou(){
        zerar_tudo();
        palavra_won(0,5,0);
        palavra_you(0,5,0);
        sleep(2);
        palavra_won(0,0,0);
        palavra_you(0,0,0);
        exit(0);

}

void voce_perdeu(){
        zerar_tudo();
        palavra_game(7,0,0);
        palavra_over(7,0,0);
        sleep(2);
        palavra_game(0,0,0);
        palavra_over(0,0,0);
        exit(0);
}

int jogo(){
            
            const char *device_path = "/dev/driver_dos_amigos"; 
            fd = open_device(device_path); // Abre o dispositivo
            char informacao[512]; // Buffer para armazenar informações
            uint32_t dataA = 0;
            uint32_t dataB = 0;

            
            print_sprite(fd, &dataA, &dataB, ativar_sprite, 138, 58, 25, 1);
            set_background(fd, &dataA,&dataB, 0, 0, 0);
  
  
            //primeiro retangulo do cenario, depois da largada verde
            pthread_mutex_lock(&mutex);
            for(int i = 5; i<= 14; i++){
                for(int j = 1; j <= 49; j++){
                    editar_bloco_background(fd, &dataA,&dataB, i, j, 7, 7, 7);
                }
            }
            for(int i = 5; i<= 22; i++){
                editar_bloco_background(fd, &dataA,&dataB, i, 14, 7, 7, 7);
            }
 

            //parte da entrada
            for(int j = 1; j <= 13; j++){
                editar_bloco_background(fd, &dataA,&dataB, 14, j, 7, 7, 7);
                for(int i = 15; i<= 21; i++){
                    editar_bloco_background(fd, &dataA,&dataB, i, 1, 7, 7, 7);
                } 
                for(int i = 15; i<= 21; i++){
                    editar_bloco_background(fd, &dataA,&dataB, i, j, 0, 5, 0);
                }
                editar_bloco_background(fd, &dataA,&dataB, 22, j, 7, 7, 7);
            }
            //parte da saída
            for(int i = 17; i <= 28; i++){
                editar_bloco_background(fd, &dataA,&dataB, 70, i, 7, 7, 7);
                for(int j = 70; j<= 78; j++){
                    editar_bloco_background(fd, &dataA,&dataB, j, 17, 7, 7, 7);
                }
                for(int j = 71; j<= 77; j++){
                    editar_bloco_background(fd, &dataA,&dataB, j, i, 7, 0, 0);
                    //a partir daqui a colisao
                }
                editar_bloco_background(fd, &dataA,&dataB, 78, i, 7, 7, 7);
            }


            //preenchimento primeiro retangulo do cenario (parte branca)
            for(int i = 5; i <= 24; i++){
                for(int j = 29; j <= 50; j++){
                    editar_bloco_background(fd, &dataA,&dataB, i, j, 7, 7, 7);
                }
            }
            for(int i = 60; i <= 78; i++){
                for(int j = 29; j <= 50; j++){
                    editar_bloco_background(fd, &dataA,&dataB, i, j, 7, 7, 7);
                }
            }
            //retangulo deitado branco

            for(int i = 25; i <= 59; i++){
                for(int j = 43; j <= 50; j++){
                    editar_bloco_background(fd, &dataA,&dataB, i, j, 7, 7, 7);
                }
            } 
            for(int i = 13; i <= 75; i++){
                editar_bloco_background(fd, &dataA,&dataB, i, 49, 7, 7, 7);
            }




            //linha invisivel
            for(int i = 10000;i<10020;i++){
                editar_sprite(fd, &dataA,&dataB,i,6,7,7);
            }
            for(int i = 10020;i<10040;i++){
                editar_sprite(fd, &dataA,&dataB,i,6,7,7);
            }

            for(int i = 10027;i<10033;i++){
                editar_sprite(fd, &dataA,&dataB,i,5,5,0);
            }
            
            for(int i = 10047;i<10053;i++){
                editar_sprite(fd, &dataA,&dataB,i,5,5,0);
            }
            
            for(int i = 10065;i<10075;i++){
                editar_sprite(fd, &dataA,&dataB,i,5,5,0);
            }

            for(int i = 10084;i<10096;i++){
                editar_sprite(fd, &dataA,&dataB,i,5,5,0);
            }

            
            //retangulo
            for(int i = 10100;i<10300;i++){
                editar_sprite(fd, &dataA,&dataB,i,5,5,0);
            }

            for(int i = 10182;i<10198;i++){
                editar_sprite(fd, &dataA,&dataB,i,5,5,0);
            }
            int invisivel = 1; // RGB(6, 7, 7)
            int amarelo = 2;     // RGB(7, 6, 1)
            int preto = 3;     // RGB(0, 0, 0)
            int branco = 4;      // RGB(7, 7, 7)
            int rosa = 5;        // RGB(7, 6, 6)
            int imagem[21][20] = {

            //curvatura do inicio
            {invisivel,invisivel,invisivel,invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel},
            {invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, preto, preto, preto, preto, preto, preto, preto, preto, invisivel, invisivel, invisivel, invisivel, invisivel},
            {invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, invisivel, invisivel, invisivel, invisivel},
            {invisivel, invisivel, invisivel, invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, invisivel, invisivel, invisivel},
            {invisivel, invisivel, invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, invisivel, invisivel},
            {invisivel, invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, invisivel},
            
            //meio
            {invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto},
            {invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto},
            {invisivel, invisivel, preto, amarelo, amarelo, amarelo, preto, branco, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, branco, amarelo, amarelo, amarelo, preto},
            {invisivel, invisivel, preto, amarelo, amarelo, amarelo, preto, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, preto, amarelo, amarelo, amarelo, preto},
            {invisivel, invisivel, preto, amarelo, amarelo, amarelo, preto, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, preto, amarelo, amarelo, amarelo, preto},
            {invisivel, invisivel, preto, amarelo, amarelo, amarelo, preto, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, preto, amarelo, amarelo, amarelo, preto},
            {invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto},
            {invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, preto, preto, preto, preto, amarelo, amarelo, amarelo, amarelo, amarelo, preto},
            {invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto},
            

            //curvatura do final
            {invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto},
            {invisivel, invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, invisivel},
            {invisivel, invisivel, invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, invisivel, invisivel},
            {invisivel, invisivel, invisivel, invisivel, invisivel, preto, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, amarelo, preto, invisivel, invisivel, invisivel},       
            {invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, preto, preto, preto, preto, preto, preto, preto, preto, preto, preto, invisivel, invisivel, invisivel, invisivel},
            {invisivel,invisivel,invisivel,invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel, invisivel}

        };

        

            pthread_mutex_unlock(&mutex); 
            int endereco = 10000;
            for (int i = 0; i < 21; i++) {
                for (int j = 0; j < 20; j++) {
                    int r,g,b;
                    int cor = imagem[i][j];
                    if(cor == 1){
                        r = 6;
                        g = 7;
                        b = 7;
                    }
                    if(cor == 2){
                        r = 7;
                        g = 6;
                        b = 1;
                    }
                    if(cor == 3){
                        r = 0;
                        g = 0;
                        b = 0;  
                    }
                    if(cor == 4){
                        r = 7;
                        g = 7;
                        b = 7;
                    }
                    if(cor == 5){
                        r = 7;
                        g = 6;
                        b = 6;
                    }       
                    editar_sprite(fd, &dataA, &dataB, endereco, r, g, b);
                    endereco++;
                }   
            }
        
            printf("vou iniciar as threads\n\n\n");
            chamar_threads();

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

