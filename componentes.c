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


#define MOUSE_DEV "/dev/input/event0"

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
            
            if(colidiu != 1 && (pause_jogo == 0 || cheat == 1 || (habilidade == 1 && pause_jogo == 0))){
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
                    if(ev.code == BTN_MIDDLE){
                        if(cheat == 0) cheat = 1;
                        else{
                            cheat = 0;
                        }
                    } 
                    if(ev.code == BTN_LEFT){
                        if (habilidade == 0) habilidade = 1;
                    }
                }
            } 
        }

        close(mouse);
        pthread_exit(NULL);


        
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
