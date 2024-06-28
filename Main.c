#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>


    int main() {
        const char *device_path = "/dev/driver_dos_amigos"; // Substitua pelo caminho do seu dispositivo
        int fd = open_device(device_path); // Abre o dispositivo
        char informacao[512]; // Buffer para armazenar informações
        uint32_t dataA = 0;
        uint32_t dataB = 0;

        int x = 70;
        int y = 50;
        set_background(fd, &dataA,&dataB, 0, 5, 6);
        //editar_bloco_background(fd, &dataA,&dataB, 0, 400, 3, 5, 6);
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


    
        print_sprite(fd, &dataA, &dataB, 1, 320, 240, 25, 1);

        
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



