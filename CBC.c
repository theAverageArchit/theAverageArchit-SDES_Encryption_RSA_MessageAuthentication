#include <stdio.h>
#include "sDES.h"
#include "roundkeyGen.h"
#include "sDES12.h"

int IV[12] = {0,1,0,0,1,0,1,1,0,1,0,1};

void CBC_Encrypt(int p[], int c[], int size, int key12[]){
    int rounds = size/12;
    int* c_last=IV;

    int c_current[12];

    for(int i=0; i<rounds; i++){
        
        int start = i*12;
        int p_current[12];
        
        for(int j=0; j<12; j++){
            p_current[j] = p[start];
            start++;
        }

        int op[12];
        xOR(op,c_last,p_current,12);
        sDES12_Enc(op, key12, c_current,10);

        // xOR(c_current,c_last,p_current,12);
        for(int j=0; j<+12; j++){
            c[i*12+j]=c_current[j];
        }

        c_last = c_current;
    }

}

void CBC_Decrypt(int p[], int c[], int size, int key12[]){
    int rounds = size/12;
    int c_temp[12];
    for(int i=0; i<12; i++){
        c_temp[i]=IV[i];
    }

    int c_current[12];

    for(int i=0; i<rounds; i++){
        int p_current[12];
        int op[12];

        for(int j=0; j<12; j++){
            c_current[j]=c[i*12+j];
        }

        sDES12_Dec(c_current,key12,op,10);

        xOR(p_current,c_temp,op,12);

        // xOR(p_current,c_temp,c_current,12);

        for(int j=0; j<12;j++){
            p[i*12+j]=p_current[j];
        }

        for(int j=0; j<12; j++){
            c_temp[j]=c_current[j];
        }
    }
}

// int main(void){
//     int key12[]={0,1,1,0,1,0,1,0,1};
//     int p[]={1,0,1,1,0,1,0,1,1,0,1,1,0,0,0,1,1,1,0,0,0,1,1,1};

//     int c[24];
//     CBC_Encrypt(p,c,24,key12);
//     printArray("c",c,24);

//     int correctNess[24];
//     CBC_Decrypt(correctNess,c,24,key12);
//     printArray("Correctness",correctNess,24);

// }