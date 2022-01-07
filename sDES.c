#include <stdio.h>
#include "roundKeyGen.h"


int initialPermutation[8] = {2,6,3,1,4,8,5,7};
int epTable[8] = {4,1,2,3,2,3,4,1};
int s0[4][4][2] = {{{0,1},{0,0},{1,1},{1,0}},{{1,1},{1,0},{0,1},{0,0}},{{0,0},{1,0},{0,1},{1,1}},{{1,1},{0,1},{1,1},{1,0}}};
int s1[4][4][2] = {{{0,0},{0,1},{1,0},{1,1}},{{1,0},{0,0},{0,1},{1,1}},{{1,1},{0,0},{0,1},{0,0}},{{1,0},{0,1},{0,0},{1,1}}};
int p4Table[4] = {2,4,3,1};
int ipInverseTable[8] = {4,1,3,5,7,2,8,6};



void ip8(int arr[], int temp[]){
    for(int i=0; i<8; i++){
        temp[i]=arr[initialPermutation[i]-1];
    }
}

void ep(int rightHalf[], int expanded[]){
    for(int i=0; i<8; i++){
        expanded[i] = rightHalf[epTable[i]-1];
    }
}



void sBOX(int substituted[], int leftHalf[], int rightHalf[]){
    int row1 = leftHalf[0]*2 + leftHalf[3]*1;
    int col1 = leftHalf[1]*2 + leftHalf[2]*1;
    substituted[0] = s0[row1][col1][0];
    substituted[1] = s0[row1][col1][1];

    int row2 = rightHalf[0]*2 + rightHalf[3]*1;
    int col2 = rightHalf[1]*2 + rightHalf[2]*1;
    substituted[2] = s1[row2][col2][0];
    substituted[3] = s1[row2][col2][1];
}

void p4(int permuted[], int substituted[]){
    for(int i=0; i<4; i++){
        permuted[i] = substituted[p4Table[i]-1];
    }
}

void ipInverse(int op[], int ip[]){
    for(int i=0; i<8; i++){
        op[i] = ip[ipInverseTable[i]-1];
    }
}

void round(int input[], int roundKey[], int output[]){

    //splitting into halves -1
    int leftHalf[4];
    int rightHalf[4];
    for(int i=0; i<4; i++){
        leftHalf[i]=input[i];
        rightHalf[i]=input[i+4];
    }
    // printArray("ip8 left", leftHalf, 4);
    // printArray("ip8 right", rightHalf, 4);
    
    //expansion of right half
    int expanded[8];
    ep(rightHalf,expanded);
    // printArray("expanded",expanded,8);

    //xORing expanded and k1
    int op[8];
    xOR(op,expanded,roundKey,8);
    // printArray("xORed",op,8);
    
    //splitting into halves -2
    int leftHalf2[4];
    int rightHalf2[4];
    for(int i=0; i<4; i++){
        leftHalf2[i]=op[i];
        rightHalf2[i]=op[i+4];
    }
    // printArray("lh2",leftHalf2,4);
    // printArray("rh2",rightHalf2,4);
    
    //sBOX
    int substituted[4];
    sBOX(substituted,leftHalf2,rightHalf2);
    // printArray("substituted", substituted, 4);

    //p4
    int permutated[4];
    p4(permutated,substituted);
    // printArray("p4", permutated, 4);

    //xOR2
    int xOR2[4];
    xOR(xOR2,permutated,leftHalf,4);
    // printArray("xOR2",xOR2,4);
    
    //final op (swapping left and right)
    for(int i=0; i<4; i++){
        output[i]=xOR2[i];
        output[i+4]=rightHalf[i];
    }
    // printArray("final",output,8);
}

void switchFunction(int arr[]){
    for(int i=0; i<4; i++){
        int temp=arr[i];
        arr[i] = arr[i+4];
        arr[i+4]=temp; 
    }
}

void sDES_Dec(int cText[], int key[], int pText[]){
    int k1[8];
    int k2[8];
    roundKeyGen(key,k1,k2);

    int temp[8];
    ip8(cText,temp);
    // printArray("ip8",temp,8);

    int op2[8];
    round(temp,k2,op2);
    // printArray("op2",op2,8);

    switchFunction(op2);

    // printArray("op2",op2,8);
    int op1[8];
    round(op2,k1,op1);
    // printArray("op1",op1,8);

    ipInverse(pText,op1);
}

void sDES_Enc(int pText[], int key[], int cText[]){
    //round key generation
    int k1[8];
    int k2[8];
    roundKeyGen(key,k1,k2);
    // printArray("k1",k1,8);
    // printArray("k2",k2,8);

    //initial permutation
    int temp[8];
    ip8(pText,temp);
    // printArray("ip8",temp,8);

    int op1[8];
    round(temp,k1,op1);
    // printArray("op1",op1,8);

    switchFunction(op1);

    // printArray("op1",op1,8);
    int op2[8];
    round(op1,k2,op2);
    // printArray("op2",op2,8);

    ipInverse(cText,op2);


}

// int main(void){
//     int pText[8] = {0,1,1,1,0,1,0,1};
//     int key[10] = {1,0,1,0,0,0,0,0,1,0};
//     int cText[8];
//     Enc(pText,key,cText);
//     int correctNess[8];
//     Dec(cText,key,correctNess);

//     printArray("Cipher Text",cText,8);
//     printArray("Correctness", correctNess, 8);
// }
