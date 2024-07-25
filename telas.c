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

        for(int j = 20; j <= 27; j++){
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

        for(int j = 34; j <= 40; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 55; i <= 58; i++){

        for(int j = 36; j <= 37; j++){
            editar_bloco_background(fd, &dataA, &dataB, i, j, r, g, b);
        }
       
    }

    for (int i = 53; i <= 60; i++){

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
            editar_bloco_background(fd, &dataA, &dataB, i, 18, r, g, b);
            editar_bloco_background(fd, &dataA, &dataB, i, 19, r, g, b);
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
