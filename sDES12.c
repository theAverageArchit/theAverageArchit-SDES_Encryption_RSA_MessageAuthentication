#include <stdio.h>
#include "roundKeyGen.h"

int expTable[8] = {1,2,4,3,4,3,5,6};
int s1_12[2][8][3]={{{1,0,1},{0,1,0},{0,0,1},{1,1,0},{0,1,1},{1,0,0},{1,1,1},{0,0,0}},{{0,0,1},{1,0,0},{1,1,0},{0,1,0},{0,0,0},{1,1,1},{1,0,1},{0,1,1}}};
int s2[2][8][3]={{{1,0,0},{0,0,0},{1,1,0},{1,0,1},{1,1,1},{0,0,1},{0,1,1},{0,1,0}},{{1,0,1},{0,1,1},{0,0,0},{1,1,1},{1,1,0},{0,1,0},{0,0,1},{1,0,0}}};

void roundShiftRight(int arr[], int size){
    int temp=arr[size-1];
    for (int i=size-1; i>=0; i--){
        arr[i]=arr[i-1];
    }
    arr[0]=temp;
}

void expansion(int pText[], int expanded[]){
    for(int i=0; i<8; i++){
        expanded[i] = pText[expTable[i]-1];
    }
}

void substitution(int xored1[], int substituted[]){
    int row1 = xored1[0];
    int row2 = xored1[4];
    int col1=0;
    for(int i=1; i<4; i++){
        col1*=2;
        col1+=xored1[i];
    }
    int col2=0;
    for(int i=5; i<8; i++){
        col2*=2;
        col2+=xored1[i];
    }
    for(int i=0; i<6; i++){
        if(i<3){
            substituted[i]=s1_12[row1][col1][i];
        }
        else{
            substituted[i]=s2[row2][col2][i-3];
        }
    }
}

int f(int op[], int temp[], int roundKey[]){
    int expanded[8];
    expansion(temp,expanded);

    int xored1[8];
    xOR(xored1,expanded,roundKey,8);

    op[6];
    substitution(xored1,op);
}

int roundFunction(int temp[], int roundKey[], int op[]){
    int L[6];
    int R[6];
    for(int i=0; i<6; i++){
        L[i] = temp[i];
        R[i] = temp[i+6];
    }
    int fCipher[6];
    f(fCipher,R,roundKey);

    xOR(L,L,fCipher,6);

    for(int i=0; i<6; i++){
        op[i] = R[i];
        op[6+i]=L[i];
    }
}

void sDES12_Enc(int pText[], int key[], int cText[], int rounds){
    int tempKey[9];
    for(int i=0; i<9; i++){
        tempKey[i]=key[i];
    }

    
    
    for(int i=0; i<12; i++){
        cText[i]=pText[i];
    }



    for(int i=0; i<rounds; i++){
        
        int roundKey[8];
        for(int i=0; i<8; i++){
            roundKey[i] = tempKey[i];
        }
        roundShift(tempKey,9);
        roundFunction(cText,roundKey,cText);
    }

    

    for(int i=0; i<6; i++){
        int temp=cText[i];
        cText[i] = cText[i+6] ;
        cText[i+6] =temp; 
    }
    
}

void sDES12_Dec(int cText[], int key[], int pText[], int rounds){
    int tempKey[9];
    for(int i=0; i<9; i++){
        tempKey[i]=key[i];
    }
    for(int i=0; i<rounds-1; i++){
        roundShift(tempKey,9);
    }
    
    
    for(int i=0; i<12; i++){
        pText[i]=cText[i];
    }

    for(int i=0; i<rounds; i++){
        
        int roundKey[8];
        for(int i=0; i<8; i++){
            roundKey[i] = tempKey[i];
        }
        roundShiftRight(tempKey,9);
        

        roundFunction(pText,roundKey,pText);
    }

    for(int i=0; i<6; i++){
        int temp=pText[i];
        pText[i] = pText[i+6] ;
        pText[i+6] =temp; 
    }
    
}

// int main(void){
//     int pText[12] = {1,0,0,0,1,0,1,1,0,1,0,1};
//     int cText[12];
//     int correctNess[12];
//     int key[9] = {1,1,1,0,0,0,1,1,1};

//     printArray("pText",pText,12);
//     Enc(pText,key,cText,2);
//     printArray("cText",cText,12);
//     Dec(cText,key,correctNess,2);
//     printArray("Correctness",correctNess,12);

// }