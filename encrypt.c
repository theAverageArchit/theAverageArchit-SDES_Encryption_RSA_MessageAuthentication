#include <stdio.h>
#include "roundKeyGen.h"
#include "sDES12.h"
#include "RSA.h"
#include "sDES.h"
#include "CBC_MAC.h"
#include <time.h>
#include <stdlib.h>
#include "CBC.h"

void encrypt(int m[], int c[], int publicKey[], int key8[], int key12[], int m2[], int size){

    srand(time(0));
    int k8 = rand()%1024;

    convertIntToBinary(k8,key8,10);

    m2[8];
    hCBC(m,key8,size,m2,8); //padding handled in HCBC
    
    int privateKey[3];
    publicKey[2];

    int m2_Int = convertBinaryToInt(m2,8);
    generateKeys(privateKey,publicKey,m2_Int);
    
    int c_Int = Enc_RSA(m2_Int,privateKey[0],privateKey[1],privateKey[2]);
    int m3[8];
    convertIntToBinary(c_Int,m3,8);
    
    int m4[24];
    for(int i=0; i<12; i++) m4[i]=m[i];
    for(int i=12; i<20; i++) m4[i]=m3[i-12];
    for(int i=20; i<23; i++) m4[i]=0;
    m4[23]=1;
    
    int k12 = rand()%512;
    convertIntToBinary(k12,key12,9);

    CBC_Encrypt(m4,c,24,key12);    
}

// int main(void){
//     int m[] = {0,1,0,1,1,1,0,0,0,0,0,1};
//     int c[24];
//     int key8[10];
//     int key12[9];
//     int publicKey[2];

//     encrypt(m,c,publicKey,key8,key12);

//     printArray("c",c,24);

// }