#include <stdio.h>

int permutation10[10] = {3,5,2,7,4,10,1,9,8,6};
int permutation8[8] = {6,3,7,4,8,5,10,9};
void p10(int k[], int temp[]){
    
    for(int i=0; i<10; i++){
        temp[i]=k[permutation10[i]-1];
    }
    
}

void printArray(char* name, int arr[], int  size){
    printf("\n %s ",name);
    for(int i=0; i<size; i++){
        printf("%d ",arr[i]);
    }
}

void xOR(int op[], int a[], int b[], int size){
    for(int i=0; i<size; i++){
        op[i]=(a[i]&&!b[i])||(!a[i]&&b[i]);
    }
}

void p8(int k[], int k1[]){
    
    for(int i=0; i<8; i++){
        k1[i]=k[permutation8[i]-1];
    }
}

void roundShift(int arr[],int size){
    int temp = arr[0];
    for(int i=1; i<size; i++){
        arr[i-1]=arr[i];
    }
    arr[size-1]=temp;
}

void roundShiftTimes(int temp[], int times, int size){
    int temp1[size/2];
    int temp2[size/2 + size%2];
    for(int i=0; i<size/2; i++){
        temp1[i]=temp[i];
        temp2[i]=temp[i+5];
    }
    //for corner case
    if(size%2==1){
        temp2[size/2]=temp[size-1];
    }

    //main functionality
    for(int i=0; i<times; i++){
        roundShift(temp1,size/2);
        roundShift(temp2,size/2 + size%2);
    }
    
    for(int i=0; i<size/2;i++){
        temp[i]=temp1[i];
        temp[i+5]=temp2[i];
    }
    //for corner case
    if(size%2==1){
        temp[size-1]=temp2[size/2];
    }
}

void roundKeyGen(int k[], int k1[], int k2[]){
    int temp[10];
    p10(k,temp);
    roundShiftTimes(temp,1,10);
    p8(temp,k1);
    roundShiftTimes(temp,2,10);
    p8(temp,k2);
}

// int main(void){
//     int k[10] = {1,0,1,0,0,0,0,0,1,0};
//     int k1[8];
//     int k2[8];
//     roundKeyGen(k,k1,k2);
//     for(int i=0; i<8; i++){
//         printf("%d",k1[i]);
//     }
//     printf("\n");
//     for(int i=0; i<8; i++){
//         printf("%d",k2[i]);
//     }
// }