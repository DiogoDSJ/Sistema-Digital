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



        
pthread_t threads[10];
uint32_t dataA = 0;
uint32_t dataB = 0;
int colidiu = 0;

int diminuir_display = 3;
int ativar_sprite = 1;

pthread_mutex_t mutex;
int coodx = 136, coody = 58;
int jogo_comecou = 0;

int obj7 = 1;
int loop1 = 1;
int dir = 1;
int dir2 = 1;
int pause_jogo = 0;
int dir_x1_x2 = 1;
int dir_y3_y4 = 1;

#define MOUSE_DEV "/dev/input/event0"

#define HEX5_BASE 0x10
#define HEX4_BASE 0x20
#define HEX3_BASE 0x30
#define HEX2_BASE 0x40
#define HEX1_BASE 0x50
#define HEX0_BASE 0x60





//Ponteiro de endereço virtual para os digitos do display de 7seg
volatile int *HEX5_ptr;
volatile int *HEX4_ptr;
volatile int *HEX3_ptr;
volatile int *HEX2_ptr;
volatile int *HEX1_ptr;
volatile int *HEX0_ptr;



    int fd;
    void *mousefik(void *arg){
        //sem_wait(&semaforo);
        int mouse;
        struct input_event ev;

        printf("Iniciando leitura de eventos do mouse...\n");

        // Abre o dispositivo de entrada (por exemplo, um mouse)
        mouse = open(MOUSE_DEV, O_RDONLY);
        if (mouse == -1) {
            perror("Erro ao abrir o dispositivo de entrada");
            exit(EXIT_FAILURE);
        }
        while (1) {
            // Lê eventos do dispositivo de entrada
            if (read(mouse, &ev, sizeof(struct input_event)) == -1) {
                /*perror("Erro ao ler evento");
                printf("teste");
                //exit(EXIT_FAILURE);*/
                if (errno == EWOULDBLOCK) {
                    //printf("No data available for non-blocking read.\n");
                    // Handle scenario where no data is immediately available
                } else {
                    perror("read");
                    return 1;
                }
            }
            
            if(colidiu != 1){
                if(ev.code == 1){
                    coody += ev.value;
                }
                else if(ev.code == 0){  
                    coodx += ev.value;
                }
            }

            //colisao do monitor
            if(coodx < 0) coodx = 0;
            if(coodx > 619) coodx= 619;
            if(coody > 459) coody = 459;
            if(coody < 0) coody = 0;

            //colisao muro esquerdo
            if(coodx <= 37){
                coodx -= ev.value;
            }
            //colisao muro direito
        
            if((coody >= 210 && coody <= 230) && (coodx>= 102 && coodx<= 200)){
                if(ev.code == 0 ) coodx -= ev.value;
                else coody -= ev.value;
            }
            if((coody >= 231 && coody <= 342) && (coodx >= 181 && coodx <= 463)){
                if(ev.code == 0 ) coodx -= ev.value;
                else coody -= ev.value;
            }
            else if(((coody < 101) && coodx >= 165) || ((coody >= 101 && coody <= 230) && (coodx >= 101 && coodx <= 180))){
                if(ev.code == 0 ) coodx -= ev.value;
                else coody -= ev.value;
            }   // 544 e y 230
                // 478 e y 388
            if((coodx > 470 && coodx < 559) && (coody > 205 && coody < 230)){
                if(ev.code == 0) coodx -= ev.value;
                else coody -= ev.value;
            }
            if((coodx > 500 && coodx < 550) && (coody < 134)){
                if(ev.code == 0) coodx -= ev.value;
                else coody -= ev.value;
            }
            if((coodx > 549 && coodx < 613) && (coody < 134)){
                if(ev.code == 0) coodx = 614;
                else coody = 134;
            }
            if((coodx > 470 && coodx <= 477) && (coody > 230 && coody < 340)){
                if(ev.code == 0) coodx -= ev.value;
                else coody -= ev.value;
            }
            // colisao teto
            if(coody <= 6){
                coody -= ev.value;
            }
            // colisao chao de la de baixo
            if(coody >= 389){
                coody -= ev.value;
            }
            if((coody <= 342 || coody >= 389) && (coodx > 181 && coodx < 478)) { // 343 e 389{
                if(ev.code == 0) coodx -= ev.value;
                else coody -= ev.value;
            }
            if((coody < 213 && coody > 120) && (coodx < 556 & coodx > 350)){
                if(ev.code == 0) coodx -= ev.value;
                else coody -= ev.value;
            }
            if(coodx > 613){
                coodx = 612;
            }
            //ultima parte

            printf("x: %d, y: %d\n", coodx, coody);
            pthread_mutex_lock(&mutex); 
            print_sprite(fd, &dataA, &dataB, ativar_sprite, coodx, coody, 25, 1);
            pthread_mutex_unlock(&mutex); 
            
            // Processa o evento recebido
            if (ev.type == EV_REL) {
                // Eventos de movimento relativo do mouse
                if (ev.code == REL_X || ev.code == REL_Y) {
                    printf("Movimento relativo: eixo %d, valor %d\n", ev.code, ev.value);
                } else if (ev.code == REL_WHEEL) {
                    printf("Roda do mouse: valor %d\n", ev.value); //irrelevante
                }
            } else if (ev.type == EV_KEY) {
                // Eventos de botão do mouse
                if (ev.code == BTN_LEFT || ev.code == BTN_RIGHT || ev.code == BTN_MIDDLE) {
                    if (ev.value == 1)
                        printf("Botão %d pressionado\n", ev.code);
                        if(pause_jogo == 0) pause_jogo = 1;
                        else pause_jogo = 0;
                }
            } 
        }

        close(mouse);
        pthread_exit(NULL);


        
    }

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

    void pausar(){
        
        if(pause_jogo == 0) pause_jogo = 1;
        else pause_jogo = 0;
    }


    void *botao(void *arg){
         //sem_wait(&semaforo);

        volatile int *KEY_ptr; // virtual address pointer to red LEDs
        int fd = -1; // used to open /dev/mem
        void *LW_virtual; // physical addresses for light-weight bridge

        // Open /dev/mem to give access to physical addresses
        if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
            printf("ERROR: could not open \"/dev/mem\"...\n");
            return (-1);
        }

        // Get a mapping from physical addresses to virtual addresses
        LW_virtual = mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
        if (LW_virtual == MAP_FAILED) {
            printf("ERROR: mmap() failed...\n");
            close(fd);
            return (-1);
        }

        // Set virtual address pointer to I/O port
        KEY_ptr = (int *)(LW_virtual + 0x0);

        int estado = 0;
        
            
        while(1){

            if (*KEY_ptr == 14 && estado == 0){
                printf("Botao KEY 0 foi clicado para iniciar \n");
                printf("valor de %d\n\n\n",jogo_comecou);
                jogo_comecou =1;
                if(jogo_comecou == 0){
                    jogo(); 

                }
                
                estado = 1;
                    
                
                

            }

            if(*KEY_ptr == 13 && estado == 0) {
                printf("Botao KEY 1 foi clicado para zerar \n");
                
                zerar_tudo();
                exit(0);
                estado = 1;

            }

            if(*KEY_ptr == 11 && estado == 0) {
                printf("Botao KEY 2 foi clicado para reiniciar \n");
                
                setar();
                estado = 1;

            }

            if(*KEY_ptr == 7 && estado == 0) {
                printf("Botao KEY 3 pause \n");

                pausar();
             
                
                
                estado = 1;

            }
            

            if ((estado == 1 && *KEY_ptr != 14) && (estado == 1 && *KEY_ptr != 13) && (estado == 1 && *KEY_ptr != 11) && (estado == 1 && *KEY_ptr != 7)){
                estado = 0;
            }

        }
        
        

        // Close the previously-opened virtual address mapping
        if (munmap(LW_virtual, LW_BRIDGE_SPAN) != 0) {
            printf("ERROR: munmap() failed...\n");
            return (-1);
        }

        // Close /dev/mem to give access to physical addresses
        close(fd);


    
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
            if(dir_x1_x2 == 1) {
                obstaculo_x_1 += 2;
                obstaculo_x_2 -= 2;
                if(obstaculo_x_1 > 99) dir_x1_x2 = 2;
            }
            else if(dir_x1_x2 == 2){
                obstaculo_x_1 -= 2;
                obstaculo_x_2 += 2;
                if(obstaculo_x_1 < 40) dir_x1_x2 = 1;
            }
            if(dir_y3_y4 == 1){
                obstaculo_y_3 +=2; 
                obstaculo_y_4 -=2;
                obstaculo_y_5 +=2;
                if(obstaculo_y_3 > 385) dir_y3_y4 = 2;
            }
            else if(dir_y3_y4 == 2){
                obstaculo_y_3 -=2;
                obstaculo_y_4 +=2;
                obstaculo_y_5 -=2;
                if(obstaculo_y_3 < 340) dir_y3_y4 = 1;
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
        if(pause_jogo == 0){
            if(dir == 1) {
                obstaculo_x_7 += 4;
                obstaculo_x_9 += 4;
                if(obstaculo_x_7 > 165) dir = 2;
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
                if(obstaculo_y_7 < 233) dir = 1;
            }
            
            

            if(dir2 == 1) {
                obstaculo_x_8 -= 2;
                obstaculo_x_10 -= 2;
                if(obstaculo_x_8 < 90) dir2 = 2;
            }
            else if(dir2 == 2){
                obstaculo_y_8 -= 2;
                obstaculo_y_10 -= 2;
                if(obstaculo_y_8 < 272) dir2 = 3;
            }
            else if(dir2 == 3){ 
                obstaculo_x_8 += 2;
                obstaculo_x_10 += 2;
                if(obstaculo_x_8 > 140) dir2 = 4;
            }
            
            else if(dir2 == 4){
                obstaculo_y_8 += 2;
                obstaculo_y_10 += 2;
                if(obstaculo_y_8 > 354) dir2 = 1;
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




    

    void alterar_display(){
        
        if(diminuir_display == 3){
            *HEX0_ptr = 0b0110000; 
        }
        else if(diminuir_display == 2){
             
            *HEX0_ptr = 0b0100100;
             
        }
        else if(diminuir_display == 1){
            
            *HEX0_ptr = 0b1111001;
             
        }
        else{
            
            *HEX0_ptr = 0b0111111;
            //reinicia todo o cenario
            zerar_tudo();
            sleep(1);
            voce_perdeu();
            exit(0);
            

        }
        

    }


    void zerar_tudo(){
        int dir = 1;
        int dir2 = 1;
        int dir_x1_x2 = 1;
        int dir_y3_y4 = 1;
        setar_sprites();
        set_background(fd, &dataA,&dataB, 0, 0, 0);

        
        //primeiro retangulo do cenario, depois da largada verde
            for(int i = 5; i<= 14; i++){
                for(int j = 1; j <= 49; j++){
                    pthread_mutex_lock(&mutex); 
                    editar_bloco_background(fd, &dataA,&dataB, i, j, 0,0,0);
                    pthread_mutex_unlock(&mutex); 
                }
            }
            for(int i = 5; i<= 22; i++){
                pthread_mutex_lock(&mutex); 
                editar_bloco_background(fd, &dataA,&dataB, i, 14, 0,0,0);
                pthread_mutex_unlock(&mutex); 
            }
 

            //parte da entrada
            for(int j = 1; j <= 13; j++){
                pthread_mutex_lock(&mutex); 
                editar_bloco_background(fd, &dataA,&dataB, 14, j, 0,0,0);
                pthread_mutex_unlock(&mutex); 
                for(int i = 15; i<= 21; i++){
                    pthread_mutex_lock(&mutex); 
                    editar_bloco_background(fd, &dataA,&dataB, i, 1, 0,0,0);
                    pthread_mutex_unlock(&mutex); 
                } 
                for(int i = 15; i<= 21; i++){
                    pthread_mutex_lock(&mutex); 
                    editar_bloco_background(fd, &dataA,&dataB, i, j, 0, 0, 0);
                    pthread_mutex_unlock(&mutex); 
                }
                pthread_mutex_lock(&mutex); 
                editar_bloco_background(fd, &dataA,&dataB, 22, j, 0,0,0);
                pthread_mutex_unlock(&mutex); 
            }
            //parte da saída
            for(int i = 17; i <= 28; i++){
                pthread_mutex_lock(&mutex); 
                editar_bloco_background(fd, &dataA,&dataB, 70, i, 0,0,0);
                pthread_mutex_unlock(&mutex); 
                for(int j = 70; j<= 78; j++){
                    pthread_mutex_lock(&mutex); 
                    editar_bloco_background(fd, &dataA,&dataB, j, 17, 0,0,0);
                    pthread_mutex_unlock(&mutex); 
                }
                for(int j = 71; j<= 77; j++){
                    pthread_mutex_lock(&mutex); 
                    editar_bloco_background(fd, &dataA,&dataB, j, i, 0, 0, 0);
                    pthread_mutex_unlock(&mutex); 
                }
                pthread_mutex_lock(&mutex); 
                editar_bloco_background(fd, &dataA,&dataB, 78, i, 0,0,0);
                pthread_mutex_unlock(&mutex); 
            }


            //preenchimento primeiro retangulo do cenario (parte branca)
            for(int i = 5; i <= 24; i++){
                for(int j = 29; j <= 50; j++){
                    pthread_mutex_lock(&mutex); 
                    editar_bloco_background(fd, &dataA,&dataB, i, j, 0,0,0);
                    pthread_mutex_unlock(&mutex); 
                }
            }
            for(int i = 60; i <= 78; i++){
                for(int j = 29; j <= 50; j++){
                    pthread_mutex_lock(&mutex); 
                    editar_bloco_background(fd, &dataA,&dataB, i, j, 0,0,0);
                    pthread_mutex_unlock(&mutex); 
                }
            }
            //retangulo deitado branco

            for(int i = 25; i <= 59; i++){
                for(int j = 43; j <= 50; j++){
                    pthread_mutex_lock(&mutex); 
                    editar_bloco_background(fd, &dataA,&dataB, i, j, 0,0,0);
                    pthread_mutex_unlock(&mutex); 
                }
            } 
            for(int i = 13; i <= 75; i++){
                pthread_mutex_lock(&mutex); 
                editar_bloco_background(fd, &dataA,&dataB, i, 49, 0,0,0);
                pthread_mutex_unlock(&mutex); 
            }
        pthread_mutex_lock(&mutex); 
        //sprite emoji
        print_sprite(fd, &dataA, &dataB, ativar_sprite, 138, 58, 25, 1);
        pthread_mutex_unlock(&mutex); 

        pthread_mutex_lock(&mutex); 
        //sprites da primeira thread
        ativar_sprite = 0;
        pthread_mutex_unlock(&mutex);

        for(int i = 0; i < 16; i++){
            print_sprite(fd, &dataA, &dataB, ativar_sprite, 138, 58, 25, i);
        }

        printf("vou finalizar as threads\n");
       // pthread_cancel(threads[0]);
        //pthread_cancel(threads[2]);
        //pthread_cancel(threads[3]);
        printf("finalizei\n");
        
        
    }



    int main_mouse(){
        //sem_init(&semaforo, 0, 1);        
        pthread_mutex_init(&mutex, NULL);

        
        pthread_create(&(threads[0]),NULL,mousefik,NULL);
        pthread_create(&(threads[1]),NULL,botao,NULL);
        pthread_create(&(threads[2]),NULL,obstaculo,NULL);
        pthread_create(&(threads[3]),NULL,obstaculo_velocidade_diferente,NULL);


        pthread_join(threads[0],NULL);
        pthread_join(threads[1],NULL);
        pthread_join(threads[2],NULL);
        pthread_join(threads[3],NULL);


        pthread_cancel(threads[0]);
        pthread_cancel(threads[1]);
        pthread_cancel(threads[2]);
        pthread_cancel(threads[3]);
        


        pthread_mutex_destroy(&mutex);  



        return 0;

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
            main_mouse();

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


           void display(){
                //Usado para abrir /dev/mem
            int fd = -1;

            //Endereços físicos para a ponte (light-weight bridge)
            void *LW_virtual;
            // Abrir /dev/mem para dar acesso a endereços físicos
            if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
                printf("ERROR: could not open \"/dev/mem\"...\n");
                return (-1);
            }

            // Obter um mapeamento de endereços físicos para endereços virtuais
            LW_virtual = mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
            if (LW_virtual == MAP_FAILED) {
                printf("ERROR: mmap() failed...\n");
                close(fd);
                return (-1);
            }

            pthread_mutex_lock(&mutex); 
            HEX5_ptr = (int *)(LW_virtual + HEX5_BASE);
            HEX4_ptr = (int *)(LW_virtual + HEX4_BASE);
            HEX3_ptr = (int *)(LW_virtual + HEX3_BASE);
            HEX2_ptr = (int *)(LW_virtual + HEX2_BASE);
            HEX1_ptr = (int *)(LW_virtual + HEX1_BASE);
            HEX0_ptr = (int *)(LW_virtual + HEX0_BASE);
            pthread_mutex_unlock(&mutex); 


            //seta os bits nos leds
            //LED 2
            *HEX1_ptr = 0b01000000;
            //LED 3
            *HEX2_ptr = 0b1111111;
            //LED 4
            *HEX3_ptr = 0b1111111;
            //LED 5
            *HEX4_ptr = 0b1111111;
            //LED 6
            *HEX5_ptr = 0b1111111;
            //Função para decrementar valores no display conforme colide
            alterar_display();

            

        // Fechar o mapeamento de endereço virtual previamente aberto
            if (munmap(LW_virtual, LW_BRIDGE_SPAN) != 0) {
                printf("ERROR: munmap() failed...\n");
                return (-1);
            }

            // Fechar /dev/mem para dar acesso a endereços físicos
            close(fd); 
    }

   
    void palavra_you(int r, int g, int b){
        pthread_mutex_lock(&mutex); 

    
    //letra y 

    for (int i = 11; i <= 12; i++){

        for(int j = 19; j <= 22; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 19; i <= 20; i++){

        for(int j = 19; j <= 22; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 13; i <= 18; i++){

        for(int j = 23; j <= 24; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 15; i <= 16; i++){

        for(int j = 25; j <= 28; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    //letra O

    for (int i = 25; i <= 28; i++){

        for(int j = 19; j <= 20; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 23; i <= 24; i++){

        for(int j = 21; j <= 26; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 29; i <= 30; i++){

        for(int j = 21; j <= 26; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 25; i <= 28; i++){

        for(int j = 27; j <= 28; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    //letra U 

    for (int i = 33; i <= 34; i++){

        for(int j = 19; j <= 26; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 39; i <= 40; i++){

        for(int j = 19; j <= 26; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 35; i <= 38; i++){

        for(int j = 27; j <= 28; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }
    pthread_mutex_unlock(&mutex); 

}

void palavra_won(int r, int g, int b){

    //letra w 
    pthread_mutex_lock(&mutex); 
    for (int i = 36; i <= 37; i++){

        for(int j = 34; j <= 43; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 38; i <= 39; i++){

        for(int j = 40; j <= 41; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 40; i <= 41; i++){

        for(int j = 38; j <= 39; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 42; i <= 43; i++){

        for(int j = 40; j <= 41; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 44; i <= 45; i++){

        for(int j = 34; j <= 43; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    //letra O

    for (int i = 50; i <= 53; i++){

        for(int j = 34; j <= 35; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 48; i <= 49; i++){

        for(int j = 36; j <= 41; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 54; i <= 55; i++){

        for(int j = 36; j <= 41; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 50; i <= 53; i++){

        for(int j = 42; j <= 43; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    //letra N 

    for (int i = 58; i <= 59; i++){

        for(int j = 34; j <= 43; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 60; i <= 61; i++){

        for(int j = 36; j <= 37; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 62; i <= 63; i++){

        for(int j = 38; j <= 39; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 64; i <= 65; i++){

        for(int j = 34; j <= 43; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    //!

    for (int i = 70; i <= 71; i++){

        for(int j = 34; j <= 39; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 70; i <= 71; i++){

        for(int j = 42; j <= 43; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }
    pthread_mutex_unlock(&mutex); 

}
/*******************************************************************************************************************************************************************************/
void palavra_game(int r, int g, int b){

    pthread_mutex_lock(&mutex); 

    //letra g

    for (int i = 8; i <= 15; i++){

        for(int j = 18; j <= 19; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 8; i <= 9; i++){

        for(int j = 20; j <= 27; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 10; i <= 15; i++){

        for(int j = 26; j <= 27; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 14; i <= 15; i++){

        for(int j = 22; j <= 25; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 12; i <= 13; i++){

        for(int j = 22; j <= 23; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    //letra a


    for (int i = 19; i <= 20; i++){

        for(int j = 18; j <= 27; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 20; i <= 25; i++){

        for(int j = 18; j <= 19; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }
    
    for (int i = 24; i <= 25; i++){

        for(int j = 20; j <= 27; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 20; i <= 23; i++){

        for(int j = 22; j <= 23; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    //letra m 

    for (int i = 28; i <= 29; i++){

        for(int j = 18; j <= 27; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    
    for (int i = 30; i <= 31; i++){

        for(int j = 20; j <= 21; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }
    
    for (int i = 32; i <= 33; i++){

        for(int j = 22; j <= 23; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 34; i <= 35; i++){

        for(int j = 20; j <= 21; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 36; i <= 37; i++){

        for(int j = 18; j <= 27; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    // letra E

    for (int i = 40; i <= 47; i++){

        for(int j = 18; j <= 19; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 40; i <= 41; i++){

        for(int j = 20; j <= 28; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 42; i <= 45; i++){

        for(int j = 22; j <= 23; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 42; i <= 47; i++){

        for(int j = 26; j <= 27; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    pthread_mutex_unlock(&mutex); 




}

void palavra_over(int r, int g, int b){

    pthread_mutex_lock(&mutex); 
    //letra O

    for (int i = 31; i <= 38; i++){

        for(int j = 32; j <= 33; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }


    for (int i = 31; i <= 32; i++){

        for(int j = 34; j <= 41; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 37; i <= 38; i++){

        for(int j = 34; j <= 41; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 33; i <= 36; i++){

        for(int j = 40; j <= 41; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    // letra v

    for (int i = 41; i <= 42; i++){

        for(int j = 32; j <= 35; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 43; i <= 44; i++){

        for(int j = 36; j <= 39; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 45; i <= 46; i++){

        for(int j = 40; j <= 41; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 47; i <= 48; i++){

        for(int j = 36; j <= 39; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 49; i <= 50; i++){

        for(int j = 32; j <= 35; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    //letra e 

    for (int i = 53; i <= 60; i++){

        for(int j = 32; j <= 33; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 53; i <= 54; i++){

        for(int j = 34; j <= 41; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 55; i <= 58; i++){

        for(int j = 36; j <= 37; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 55; i <= 60; i++){

        for(int j = 40; j <= 41; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    //letra R

    for (int i = 63; i <= 70; i++){

        for(int j = 32; j <= 33; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 63; i <= 64; i++){

        for(int j = 34; j <= 41; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 65; i <= 68; i++){

        for(int j = 36; j <= 37; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 67; i <= 68; i++){

        for(int j = 38; j <= 39; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 69; i <= 70; i++){

        for(int j = 34; j <= 35; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 69; i <= 70; i++){

        for(int j = 39; j <= 41; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    pthread_mutex_unlock(&mutex); 


}


    void letra_verde(int r,int g,int b){

        pthread_mutex_lock(&mutex); 

        //LETRA G
        for(int i = 15; i <= 22; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 19, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 20, r, g, b);
        }

        for(int i = 20; i <= 27; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 15, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 16, i, r, g, b);
        }

        for(int i = 17; i <= 22; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 26, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 27, r, g, b);
        }

        for(int i = 22; i <= 26; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 22, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 21, i, r, g, b);
        }

        for(int i = 19; i <= 22; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 22, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 23, r, g, b);
        }

        //letra R
        for(int i = 25; i <= 32; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 18, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 19, r, g, b);
        }

        for(int i = 20; i <= 27; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 25, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 26, i, r, g, b);
        }

        for(int i = 27; i <= 30; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 22, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 23, r, g, b);
        }

        for(int i = 20; i <= 21; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 31, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 32, i, r, g, b);
        }

        for(int i = 24; i <= 25; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 29, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 30, i, r, g, b);
        }

        for(int i = 26; i <= 27; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 31, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 32, i, r, g, b);
        }

        //primeira letra E 
        for(int i = 35; i <= 42; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 18, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 19, r, g, b);
        }

        for(int i = 35; i <= 42; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 26, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 27, r, g, b);
        }

        for(int i = 35; i <= 42; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 22, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 23, r, g, b);
        }

        for(int i = 18; i <= 27; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 35, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 36, i, r, g, b);
        }

        //segunda letra E
        for(int i = 45; i <= 52; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 18, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 19, r, g, b);
        }

        for(int i = 45; i <= 52; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 26, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 27, r, g, b);
        }

        for(int i = 45; i <= 50; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 22, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 23, r, g, b);
        }

        for(int i = 18; i <= 27; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 45, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 46, i, r, g, b);
        }

        //letra N
        for(int i = 18; i <= 27; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 55, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 56, i, r, g, b);
        }

        for(int i = 18; i <= 27; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 61, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 62, i, r, g, b);
        }

        for(int i = 18; i <= 27; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 45, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 46, i, r, g, b);
        }

        for(int i = 20; i <= 21; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 57, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 58, i, r, g, b);
        }

        for(int i = 22; i <= 23; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 59, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 60, i, r, g, b);
        }

        pthread_mutex_unlock(&mutex); 

    }

    void letra_branca(int r, int g,int b){

        pthread_mutex_lock(&mutex); 
        //letra T
        for(int i = 21; i <= 25; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 33, r, g, b);
        }

        for(int i = 33; i <= 37; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 23, i, r, g, b);
        }


        //letra O
        for(int i = 27; i <= 30; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 33, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 37, r, g, b);
        }

        for(int i = 33; i <= 37; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 27, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 30, i, r, g, b);
        }
        
        pthread_mutex_unlock(&mutex); 
    }

    void letra_vermelha(int r,int g,int b){

        pthread_mutex_lock(&mutex); 
        //letra R
        for(int i = 35; i <= 42; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 31, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 32, r, g, b);
        }

        for(int i = 31; i <= 40; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 35, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 36, i, r, g, b);
        }



        for(int i = 36; i <= 40; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 35, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 36, i, r, g, b);
        }
        

        for(int i = 37; i <= 40; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 35, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 36, r, g, b);
        }

        for(int i = 33; i <= 34; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 41, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 42, i, r, g, b);
        }

        for(int i = 37; i <= 38; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 39, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 40, i, r, g, b);
        }

        for(int i = 39; i <= 40; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 41, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 42, i, r, g, b);
        }



        // letra E 
        for(int i = 45; i <= 52; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 31, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 32, r, g, b);
        }

        for(int i = 45; i <= 52; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 39, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 40, r, g, b);
        }

        for(int i = 47; i <= 52; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 35, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 36, r, g, b);
        }

        for(int i = 31; i <= 40; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 45, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 46, i, r, g, b);
        }


        //letra D
        for(int i = 31; i <= 40; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 55, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 56, i, r, g, b);
        }

        for(int i = 57; i <= 60; i++) {
            editar_bloco_background(fd, &dataA, &dataB, i, 31, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 32, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 39, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 40, r, g, b);
        }

        for(int i = 33; i <= 38; i++) {
            editar_bloco_background(fd, &dataA, &dataB, 61, i, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, 62, i, r, g, b);
        }

        pthread_mutex_unlock(&mutex); 



        

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


    

     void inicio(){
        const char *device_path = "/dev/driver_dos_amigos"; 
        fd = open_device(device_path); // Abre o dispositivo
        char informacao[512]; // Buffer para armazenar informações
        uint32_t dataA = 0;
        uint32_t dataB = 0;
        pthread_mutex_lock(&mutex); 
        set_background(fd, &dataA,&dataB, 0, 0, 0);
        pthread_mutex_unlock(&mutex); 

        //para pintar as letras de verde
        letra_verde(0,5,0);
        letra_branca(7,7,7);
        letra_vermelha(7,0,0);

        


        


        volatile int *KEY_ptr; // virtual address pointer to red LEDs
        int fd = -1; // used to open /dev/mem
        void *LW_virtual; // physical addresses for light-weight bridge

        // Open /dev/mem to give access to physical addresses
        if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
            printf("ERROR: could not open \"/dev/mem\"...\n");
            return (-1);
        }

        // Get a mapping from physical addresses to virtual addresses
        LW_virtual = mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
        if (LW_virtual == MAP_FAILED) {
            printf("ERROR: mmap() failed...\n");
            close(fd);
            return (-1);
        }

        // Set virtual address pointer to I/O port
        KEY_ptr = (int *)(LW_virtual + 0x0);

        int estado = 0;

        while (1)
        {
            if(*KEY_ptr == 14 && estado == 0){
                printf("Botao KEY 0 foi clicado para setar \n");
                letra_verde(0,0,0);
                letra_branca(0,0,0);
                letra_vermelha(0,0,0);
              

             

                setar();
                jogo();   
                estado = 1;

            }
            if (estado == 1 && *KEY_ptr != 14){
                estado = 0;
            }
        }
     }



        int main() {
            display();
            inicio();

            
        }
