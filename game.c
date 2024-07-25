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

   

    
void pausar(){
    
    if(pause_jogo == 0) pause_jogo = 1;
    else pause_jogo = 0;
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
    int habilidade = 0;
    //setar_sprites();
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



    
    
}

int chamar_threads(){
    //sem_init(&semaforo, 0, 1);        
    pthread_mutex_init(&mutex, NULL);

    
    pthread_create(&(threads[0]),NULL,mousefik,NULL);
    pthread_create(&(threads[1]),NULL,botao,NULL);
    pthread_create(&(threads[2]),NULL,obstaculo,NULL);
    pthread_create(&(threads[3]),NULL,obstaculo_velocidade_diferente,NULL);
    pthread_create(&(threads[4]),NULL,habilidade_parar,NULL);


    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);
    pthread_join(threads[2],NULL);
    pthread_join(threads[3],NULL);
    pthread_join(threads[4],NULL);

    pthread_cancel(threads[0]);
    pthread_cancel(threads[1]);
    pthread_cancel(threads[2]);
    pthread_cancel(threads[3]);
    pthread_cancel(threads[4]);
    


    pthread_mutex_destroy(&mutex);  


    return 0;

}

void limpa_tudo(){
    
    for(int i = 0; i< 80; i++){
        for(int j = 0; j<60; j++){
            editar_bloco_background(fd, &dataA,&dataB, i, j, 0,0,0);
        }
    }
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
    limpa_tudo();
    zerar_tudo();
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
