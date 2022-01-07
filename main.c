#include <stdio.h>
#include "roundKeyGen.h"
#include "sDES12.h"
#include "RSA.h"
#include "sDES.h"
#include "CBC_MAC.h"
#include "CBC.h"
#include "encrypt.h"
#include <time.h>
#include <stdlib.h>

int main(void){
    srand(time(0));
    printf("\nPlease Enter the Size of the Message: ");

    int n;
    scanf("%d",&n);

    printf("\nPlease Enter the PlainText Message(in binary format seperated by whitespaces): ");
    
    int m[n];
    for(int i=0; i<n; i++){
        scanf("%d",&m[i]);
    }
    fflush(stdin);

    int c[24];
    int publicKey[2];
    int key8[10];
    int key12[9];
    int hCBC[8];

    printf("\nEncrypting... Please Wait.");
    encrypt(m,c,publicKey,key8,key12,hCBC,n);
    printf("\nYour Message has been encrypted Sucessfully.");

    printArray("\nThis is the CipherText Message Received: ", c, 24);
    printArray("This is the Message Authentication Code: ", hCBC, 8);


    char ans='0';
    while(ans!='y'||ans!='Y'||ans!='n'||ans!='N'){
        printf("\n\nWould you like to Decrypt the Message(Y/N)? ");
        scanf("%c",&ans);
        fflush(stdin);
        if(ans=='y'||ans=='Y') break;
        else if(ans=='n'||ans=='N') return 0;
        else("\nError! Please answer either (Y/N)");
    }
    

    printf("\n\nDecrypting the CipherText... Please Wait.");
    int m4[24];
    CBC_Decrypt(m4,c,24,key12);
    printf("\nCipherText Decrypted.\n");

    printf("\nRetrieving Authentication Code...");
    int m3_dash[8];
    for(int i=0;i<8;i++){
        m3_dash[i]=m4[12+i];
    }

    int m3_dash_int = convertBinaryToInt(m3_dash,8);
    int hCBC_dash_int = Dec_RSA(m3_dash_int,publicKey[0],publicKey[1]);
    int hCBC_dash[8];
    convertIntToBinary(hCBC_dash_int,hCBC_dash,8);
    printf("\nAuthentication Code Retrieved ");
    printArray("This is the Authentication Code: ", hCBC_dash, 8);
    
    printf("\n\nAuthenticating Message...");
    int hCBC_int = convertBinaryToInt(hCBC,8);
    if(hCBC_int==hCBC_dash_int){
        printf("\nAuthentication is Successful. Original Text Received");
    }
    else{
        printf("\nAuthentication Failure. Text is Corrupt.");
    }
    
    
    // printf("\n %d",hCBC_int);
    // printf("\n %d",hCBC_dash_int);


}