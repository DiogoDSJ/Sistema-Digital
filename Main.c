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

pthread_mutex_t mutex;
int coodx = 136, coody = 58;

int obj7 = 1;
int loop1 = 1;
int dir = 1;
int dir2 = 1;

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
            print_sprite(fd, &dataA, &dataB, 1, coodx, coody, 25, 1);
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
                }
            } 
        }

        close(mouse);
        pthread_exit(NULL);


        
    }

    void setar(void){
        coodx = 139;coody = 54;
        pthread_mutex_unlock(&mutex); 
        print_sprite(fd, &dataA, &dataB, 1, coodx, coody, 25, 1); 
        *HEX0_ptr = 0b0110000;
        pthread_mutex_unlock(&mutex); 
        diminuir_display = 3;

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
                printf("Botao KEY 0 foi clicado para reiniciar \n");

                pthread_cancel(threads[0]);
                pthread_cancel(threads[2]);
                pthread_cancel(threads[3]);
                setar();
                jogo();
                estado = 1;
            }

            if(*KEY_ptr == 13 && estado == 0) {
                printf("Botao KEY 0 foi clicado para zerar \n");
                zerar_tudo();
                estado = 1;

            }

            if (estado == 1 && *KEY_ptr != 14){
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
    struct timespec interval = {0, 2000000};
   
    //retandulo pequeno vertical
     // Posição inicial do obstáculo
    int obstaculo_x_1 = 40; // Posição inicial do obstáculo
    int obstaculo_y_1 = 140;
    int obstaculo_x_2 = 100; 
    int obstaculo_y_2 = 200;


    //retangulo pequeno horizontal
    int obstaculo_x_3 = 215; 
    int obstaculo_y_3 = 343;

    int obstaculo_x_4 = 325; 
    int obstaculo_y_4 = 385;

    int obstaculo_x_5 = 435; 
    int obstaculo_y_5 = 343;
    

    while(loop1){
        //sprite 1
        int distancia_sprite_1 = 20;
        int distancia_y = 15;
        colidiu = 0;
        for (int i = 0; i < (distancia_sprite_1 * 2); i++){
            
            pthread_mutex_lock(&mutex);
            print_sprite(fd, &dataA, &dataB, 1, obstaculo_x_1, obstaculo_y_1, 1, 3); 
            print_sprite(fd, &dataA, &dataB, 1, obstaculo_x_2, obstaculo_y_2, 1, 5); 
            print_sprite(fd, &dataA, &dataB, 1, obstaculo_x_3, obstaculo_y_3, 1, 6);
            print_sprite(fd, &dataA, &dataB, 1, obstaculo_x_4, obstaculo_y_4, 1, 7);
            print_sprite(fd, &dataA, &dataB, 1, obstaculo_x_5, obstaculo_y_5, 1, 8);
            pthread_mutex_unlock(&mutex); 

            if (i < distancia_sprite_1){
                obstaculo_x_1 += 3;
                obstaculo_x_2 -= 3;
            }
            else{
                obstaculo_x_1 -= 3;
                obstaculo_x_2 += 3;
 
            }

            if(i < distancia_y && i < 30){
                obstaculo_y_3 +=3; 
                obstaculo_y_4 -=3;
                obstaculo_y_5 +=3; 
            }
            else if(i < 30){
                obstaculo_y_3 -=3;
                obstaculo_y_4 +=3;
                obstaculo_y_5 -=3;
            }

            //COLISAO sprite 1 do retangulo vertical
            if(obstaculo_x_1 <= coodx+20 && obstaculo_x_1 + 20 > coodx && obstaculo_y_1 < coody+20 && obstaculo_y_1+20> coody){
                coodx = 139;coody = 54;
                print_sprite(fd, &dataA, &dataB, 1, coodx, coody, 25, 1);
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
                print_sprite(fd, &dataA, &dataB, 1, coodx, coody, 25, 1);
                colidiu = 1;

                diminuir_display-=1;
                alterar_display();
                printf("teste;");
            }

            //COLISAO sprite 3 do retangulo horizontal
            if(obstaculo_x_3 <= coodx+20 && obstaculo_x_3 + 20 > coodx && obstaculo_y_3 < coody+20 && obstaculo_y_3+20> coody){
                printf("TEVE COLISAO\n");
                coodx = 139;coody = 54;
                print_sprite(fd, &dataA, &dataB, 1, coodx, coody, 25, 1);
                colidiu = 1;

                diminuir_display-=1;
                alterar_display();
                printf("teste;");
            }

            //COLISAO sprite 4 do retangulo horizontal
            if(obstaculo_x_4 <= coodx+20 && obstaculo_x_4 + 20 > coodx && obstaculo_y_4 < coody+20 && obstaculo_y_4+20> coody){
                printf("TEVE COLISAO\n");
                coodx = 139;coody = 54;
                print_sprite(fd, &dataA, &dataB, 1, coodx, coody, 25, 1);
                colidiu = 1;

                diminuir_display-=1;
                alterar_display();
                printf("teste;");
            }

            //COLISAO sprite 5 do retangulo horizontal
            if(obstaculo_x_5 <= coodx+20 && obstaculo_x_5 + 20 > coodx && obstaculo_y_5 < coody+20 && obstaculo_y_5+20> coody){
                printf("TEVE COLISAO\n");
                coodx = 139;coody = 54;
                print_sprite(fd, &dataA, &dataB, 1, coodx, coody, 25, 1);
                colidiu = 1;

                diminuir_display-=1;
                alterar_display();
                printf("teste;");
            }
            
            
            
            nanosleep(&interval, NULL);
        }
        
    }
   //
    pthread_exit(NULL);
    return 0;
}




void *obstaculo_velocidade_diferente(){
  
    struct timespec interval = {0, 2000000};

    //retandulo pequeno vertical
    int obstaculo_x_7 = 40; // Posição inicial do obstáculo
    int obstaculo_y_7 = 240; // Posição inicial do obstáculo
    
    int obstaculo_x_8 = 140; 
    int obstaculo_y_8 = 354;



    int obstaculo_x_9 = 477; // Posição inicial do obstáculo
    int obstaculo_y_9 = 240; // Posição inicial do obstáculo
    
    int obstaculo_x_10 = 585; 
    int obstaculo_y_10 = 354;



    while(1){
        int po;
        //sprite 1
        int distancia_sprite_1 = 44;
 
        for (int i = 0; i < (distancia_sprite_1 * 2); i++){
            pthread_mutex_lock(&mutex); 
            print_sprite(fd, &dataA, &dataB, 1, obstaculo_x_7, obstaculo_y_7, 1, 11); //colocar para printar sprite aq
            print_sprite(fd, &dataA, &dataB, 1, obstaculo_x_8, obstaculo_y_8, 1, 10);
            print_sprite(fd, &dataA, &dataB, 1, obstaculo_x_9, obstaculo_y_9, 1, 12);
            print_sprite(fd, &dataA, &dataB, 1, obstaculo_x_10, obstaculo_y_10, 1, 13);
            pthread_mutex_unlock(&mutex);

            if(dir == 1) {
                obstaculo_x_7 += 3;
                obstaculo_x_9 += 3;
            }
            if(obstaculo_x_7 > 172) dir = 2;
            if(dir == 2){
                obstaculo_y_7 += 3;
                obstaculo_y_9 += 3;
            }
            if(obstaculo_y_7 > 380) dir = 3;
            if(dir == 3){
                obstaculo_x_7 -= 3;
                obstaculo_x_9 -= 3;
            }
            if(obstaculo_x_7 < 45) dir = 4;
            if(dir == 4){ 
                obstaculo_y_7 -= 3;
                obstaculo_y_9 -= 3;
            }
            if(obstaculo_y_7 < 240) dir = 1;
            

            if(dir2 == 1) {
                obstaculo_x_8 -= 3;
                obstaculo_x_10 -= 3;
            }
            if(obstaculo_x_8 < 65) dir2 = 2;
            if(dir2 == 2){
                obstaculo_y_8 -= 3;
                obstaculo_y_10 -= 3;
            }
            if(obstaculo_y_8 < 340) dir2 = 3;

            if(dir2 == 3){ 
                obstaculo_x_8 += 3;
                obstaculo_x_10 += 3;
            }
            if(obstaculo_x_8 > 142) dir2 = 4;

            if(dir2 == 4){
                 obstaculo_y_8 += 3;
                 obstaculo_y_10 += 3;
            }
            if(obstaculo_y_8 > 280) dir2 = 1;

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
                print_sprite(fd, &dataA, &dataB, 1, coodx, coody, 25, 1);

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
                print_sprite(fd, &dataA, &dataB, 1, coodx, coody, 25, 1);

                diminuir_display-=1;
                alterar_display();
            }


            //COLISAO 4 SPRITE DO QUADRADO DA DIREITA
            if(obstaculo_x_9 <= coodx+20 && obstaculo_x_9 + 20 > coodx && obstaculo_y_9 < coody+20 && obstaculo_y_9+20> coody){
                printf("TEVE COLISAO\n");
                coodx = 139;coody = 54;
                print_sprite(fd, &dataA, &dataB, 1, coodx, coody, 25, 1);

                diminuir_display-=1;
                alterar_display();
            }


            //COLISAO 5 SPRITE DO QUADRADO DA DIREITA
            if(obstaculo_x_10 <= coodx+20 && obstaculo_x_10 + 20 > coodx && obstaculo_y_10 < coody+20 && obstaculo_y_10+20> coody){
                printf("TEVE COLISAO\n");
                coodx = 139;coody = 54;
                print_sprite(fd, &dataA, &dataB, 1, coodx, coody, 25, 1);

                diminuir_display-=1;
                alterar_display();
            }


            nanosleep(&interval, NULL);
        }
        
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

        }
        

    }


    void zerar_tudo(){
        
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
        print_sprite(fd, &dataA, &dataB, 0, 138, 58, 25, 1);
        pthread_mutex_unlock(&mutex); 

        pthread_mutex_lock(&mutex); 
        //sprites da primeira thread
        print_sprite(fd, &dataA, &dataB, 0, 0, 0, 1, 3); 
        print_sprite(fd, &dataA, &dataB, 0, 0, 0, 1, 5); 
        print_sprite(fd, &dataA, &dataB, 0, 0, 0, 1, 6);
        print_sprite(fd, &dataA, &dataB, 0, 0, 0, 1, 7);
        print_sprite(fd, &dataA, &dataB, 0, 0, 0, 1, 8);
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        //sprites da segunda thread
        print_sprite(fd, &dataA, &dataB, 0, 0, 0, 1, 11); 
        print_sprite(fd, &dataA, &dataB, 0, 0, 0, 1, 10);
        print_sprite(fd, &dataA, &dataB, 0, 0, 0, 1, 12);
        print_sprite(fd, &dataA, &dataB, 0, 0, 0, 1, 13);
        pthread_mutex_unlock(&mutex);


        pthread_cancel(threads[0]);
        pthread_cancel(threads[2]);
        pthread_cancel(threads[3]);
        
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

        pthread_mutex_destroy(&mutex);  
        return 0;

    }



        int jogo(){
            const char *device_path = "/dev/driver_dos_amigos"; 
            fd = open_device(device_path); // Abre o dispositivo
            char informacao[512]; // Buffer para armazenar informações
            uint32_t dataA = 0;
            uint32_t dataB = 0;

            
            print_sprite(fd, &dataA, &dataB, 1, 138, 58, 25, 1);
            set_background(fd, &dataA,&dataB, 0, 5, 6);
  
  
            //primeiro retangulo do cenario, depois da largada verde
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


     void inicio(){
        const char *device_path = "/dev/driver_dos_amigos"; 
        fd = open_device(device_path); // Abre o dispositivo
        char informacao[512]; // Buffer para armazenar informações
        uint32_t dataA = 0;
        uint32_t dataB = 0;
        pthread_mutex_lock(&mutex); 
        set_background(fd, &dataA,&dataB, 0, 5, 6);
        pthread_mutex_unlock(&mutex); 








        //primeiro retangulo do cenario, depois da largada verde
        for(int i = 5; i<= 14; i++){
           editar_bloco_background(fd, &dataA,&dataB, 20, i, 7, 7, 7);
        }

        for(int i = 20; i<= 25; i++){
            editar_bloco_background(fd, &dataA,&dataB, i, 5, 7, 7, 7);
        }
        
        for(int i = 20; i<= 25; i++){
            editar_bloco_background(fd, &dataA,&dataB, i, 5, 7, 7, 7);
        }






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

