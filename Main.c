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

    #include <sys/mman.h>
    #include "address_map_arm.h"
                

            
    pthread_t threads[10];
   // sem_t semaforo; // Declaração do semáforo


    #define MOUSE_DEV "/dev/input/event0"

    int fd;
    void *mousefik(void *arg){
        //sem_wait(&semaforo);
        uint32_t dataA = 0;
        uint32_t dataB = 0;

        int mouse;
        struct input_event ev;

        printf("Iniciando leitura de eventos do mouse...\n");

        // Abre o dispositivo de entrada (por exemplo, um mouse)
        mouse = open(MOUSE_DEV, O_RDONLY);
        if (mouse == -1) {
            perror("Erro ao abrir o dispositivo de entrada");
            exit(EXIT_FAILURE);
        }
        int coodx = 50, coody = 50;
        while (1) {
            // Lê eventos do dispositivo de entrada
            if (read(mouse, &ev, sizeof(struct input_event)) == -1) {
                perror("Erro ao ler evento");
                exit(EXIT_FAILURE);
            }
            if(ev.code == 1){
                coody += ev.value;
            }
            else if(ev.code == 0){  
                coodx += ev.value;
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
            if((coodx >= 613) && (coody > 132 && coody <= 389)){
                if(ev.code == 0) coodx -= ev.value;
                else coody -= ev.value;
            }
            if((coodx > 470 && coodx < 559) && (coody > 205 && coody < 230)){
                if(ev.code == 0) coodx -= ev.value;
                else coody -= ev.value;
            }
            if((coodx > 550 && coodx < 630) && (coody < 134 && coody > 100 )){
                if(ev.code == 0) coodx -= ev.value;
                else coody -= ev.value;
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
            if((coody <= 342 || coody >= 389) && (coodx > 181 && coodx < 480)) { // 343 e 389{
                coody -= ev.value;
            }


            //ultima parte

            printf("x: %d, y: %d\n", coodx, coody);
            print_sprite(fd, &dataA, &dataB, 1, coodx, coody, 25, 1);
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
        //sem_post(&semaforo); // Libera o semáforo
        //pthread_exit(NULL);
        
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

        int estado = 1;
            
        while(1){

            if (*KEY_ptr == 15 && estado == 0){
                printf("clicou\n");
                estado = 1;
            } 
            if (estado == 1 && *KEY_ptr != 15){
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
        //sem_post(&semaforo); // Libera o semáforo
        //pthread_exit(NULL);

    }

















    int main_mouse(){
        //sem_init(&semaforo, 0, 1);
        pthread_create(&(threads[0]),NULL,mousefik,NULL);
        pthread_create(&(threads[1]),NULL,botao,NULL);


        pthread_join(threads[0],NULL);
        pthread_join(threads[1],NULL);

        
        // Destroi o semáforo
        //sem_destroy(&semaforo);
        
        return 0;

    }
        

        int main() {
            const char *device_path = "/dev/driver_dos_amigos"; 
            fd = open_device(device_path); // Abre o dispositivo
            char informacao[512]; // Buffer para armazenar informações
            uint32_t dataA = 0;
            uint32_t dataB = 0;

            

            print_sprite(fd, &dataA, &dataB, 1, 100, 240, 2, 1);

            print_sprite(fd, &dataA, &dataB, 1, 320, 240, 25, 1);
            set_background(fd, &dataA,&dataB, 0, 5, 6);
            /*
            
            for(int i = 0; i < 80; i++){
                for(int j = 0; j < 60; j++){
                    editar_bloco_background(fd, &dataA,&dataB, i, j, 6, 7, 7);
                }
            } 
            */
            //primeiro retangulo do cenario, depois da largada verde
            for(int i = 5; i<= 14; i++){
                for(int j = 1; j <= 49; j++){
                    editar_bloco_background(fd, &dataA,&dataB, i, j, 7, 7, 7);
                }
            }
            for(int i = 5; i<= 22; i++){
                editar_bloco_background(fd, &dataA,&dataB, i, 14, 7, 7, 7);
            }
        /*
            for(int i = 5; i <= 12; i++){
                editar_bloco_background(fd, &dataA,&dataB, i, 16, 7, 7, 7);
            }

            for(int i = 16; i <= 49; i++){
                editar_bloco_background(fd, &dataA,&dataB, 13, i, 7, 7, 7);
            }

            for(int i = 5; i <= 12; i++){
                editar_bloco_background(fd, &dataA,&dataB, i, 47, 7, 7, 7);
            }
        */

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
        
    /*
        int mouse;
        struct input_event ev;

        printf("Iniciando leitura de eventos do mouse...\n");

        // Abre o dispositivo de entrada (por exemplo, um mouse)
        mouse = open(MOUSE_DEV, O_RDONLY);
        if (mouse == -1) {
            perror("Erro ao abrir o dispositivo de entrada");
            exit(EXIT_FAILURE);
        }
        int coodx = 50, coody = 50;
        while (1) {
            // Lê eventos do dispositivo de entrada
            if (read(mouse, &ev, sizeof(struct input_event)) == -1) {
                perror("Erro ao ler evento");
                exit(EXIT_FAILURE);
            }
            if(ev.code == 1){
                coody += ev.value;
            }
            else if(ev.code == 0){  
                coodx += ev.value;
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
        
            
            if((coody <= 6 || coody > 100) && coodx >= 164){
                coodx -= ev.value;
                if(ev.code == 0) coody -= ev.value;
            } 
            // colisao teto
            if(coody <= 6){
                coody -= ev.value;
            }
            // colisao chao de la de baixo
            if(coody >= 389){
                coody -= ev.value;
            }
            if((coody <= 343 || coody >= 389) && (coodx > 179 && coodx < 480)) { // 343 e 389{
                coody -= ev.value;
            }
            printf("x: %d, y: %d\n", coodx, coody);
            print_sprite(fd, &dataA, &dataB, 1, coodx, coody, 25, 1);
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
        */  
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



