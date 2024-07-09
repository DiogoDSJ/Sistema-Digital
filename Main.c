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
                
    pthread_t threads[10];


    #define MOUSE_DEV "/dev/input/event0"

    int fd;
    void *mousefik(void *arg){

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

            

        close(mouse);
        
    }

    int main_mouse(){
        pthread_create(&(threads[0]),NULL,mousefik,NULL);


        pthread_join(threads[0],NULL);
        
        return 0;

    }
        

        int main() {
            const char *device_path = "/dev/driver_dos_amigos"; 
            fd = open_device(device_path); // Abre o dispositivo
            char informacao[512]; // Buffer para armazenar informações
            uint32_t dataA = 0;
            uint32_t dataB = 0;

            
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



