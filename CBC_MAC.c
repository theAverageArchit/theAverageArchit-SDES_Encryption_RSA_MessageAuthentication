#include <stdio.h>
#include "sDES.h"
#include "roundKeyGen.h"
#include "sDES12.h"

int IV8[8]={0,0,0,0,0,0,0,0};
int IV12[12]={0,0,0,0,0,0,0,0,0,0,0,0};

void HCBCround(int c_current[], int c_last[],int p_current[], int key[], int Enc_Size){
    if(Enc_Size==8){ 
        int op[8];
        xOR(op,c_last,p_current,8);
        sDES_Enc(op, key, c_current);
    }
    if(Enc_Size==12){ 
        int op[12];
        xOR(op,c_last,p_current,12);
        sDES12_Enc(op, key, c_current,10);
    }
}

void hCBC(int arr[],int key[],int size, int cbcmac[], int Enc_Size){
    //printf("size - %d\n",size);
    int padding = size%Enc_Size;
    int rounds = size/Enc_Size;
    int* c_last;
    if(Enc_Size==8){
        c_last = IV8;
    }
    else if(Enc_Size==12){
        c_last = IV12;
    }
    //printArray("IV",c_last,Enc_Size);
    int c_current[Enc_Size];

    for(int i=0; i<rounds; i++){
        
        int start = i*Enc_Size;
        int p_current[Enc_Size];
        
        //loading p_current
        for(int j=0; j<Enc_Size; j++){
            p_current[j] = arr[start];
            start++;
        }

        //HCBC round
         
        HCBCround(c_current, c_last,p_current,key,Enc_Size);

        c_last = c_current;
    }

    //EDGE CASE
    if(padding!=0){
        int start = rounds*Enc_Size;
        int p_current[Enc_Size];
        int i=0;
        while(i<Enc_Size-padding){
            p_current[i]=arr[start];
            start++;
            i++;
        }
        while(padding!=1){
            p_current[i]=0;
            i++;
            padding--;
        }

        p_current[i] = 1;

        int c_current[Enc_Size]; 
        HCBCround(c_current, c_last,p_current,key,Enc_Size);
        c_last=c_current;
    }
    
    for(int i=0; i<Enc_Size; i++){
        cbcmac[i]=c_last[i];
    }

}

// int main(void){
//     int arr[24] = {0,1,1,0,1,0,1,1,0,0,0,1,0,0,1,1,0,1,1,1,0,0,0,0};
//     int key[9] = {0,1,0,1,1,1,1,0,1};
//     int cbcmac[12];
//     hCBC(arr,key,24,cbcmac,12);
//     printArray("DES CBC-MAC",cbcmac,12);
// }