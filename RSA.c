#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int prime[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127};

int mod_power(int x, int n, int mod){
    // printf("\n %d x=%d, n=%d",n%2,x,n);
    if(n==1) return x;
    if(n==0) return 1;
    if(n%2==1) return (x*mod_power((x*x)%mod,(n-1)/2,mod))%mod;
    else return mod_power((x*x)%mod,n/2,mod)%mod;
} //Efficient Exponentiation by Squaring

int gcd(int a, int b){
    if(b>a){
        int temp =a;
        a=b;
        b=temp;
    }
    int c=a%b;
    if(c==0) return b;
    else return gcd(b,c);
}

int multiplicativeInverse(int x, int n){
    int a=n;
    int b=x;
    int r1=0;
    int r0=1;
    int inv;
    while(b>1){
        inv = r1 - (a/b)*r0;

        //printf("\n n-%d, b-%d, q-%d, r-%d, t1-%d, t2-%d, t3-%d",a,b,a/b,a%b,r1,r0,inv);

        int temp = b;
        b=a%b;
        a=temp;

        r1=r0;
        r0=inv;
        
    }

    if(b<1) return -1;
    if(inv>0) return inv%n;
    else return n+inv%n;
}

void generateKeys(int privateKey[], int publicKey[], int m){
    int n=257;
    int p=0;
    int q=0;
    srand(time(0));
    while(n>=256||p==q||n<=m){
        p = prime[(rand())%31];
        q = prime[(rand())%31];
        n=p*q;
    }
    int phi = (p-1)*(q-1);

    int a=-1;
    int b=-1;
    while(a<2||b<2){
        b = rand()%phi;
        a = multiplicativeInverse(b,phi);
    }
    
    publicKey[0]=n;
    publicKey[1]=a;

    privateKey[0]=p;
    privateKey[1]=q;
    privateKey[2]=b;
}

int convertBinaryToInt(int bin[], int size){
    int x=0;
    for(int i=0; i<size; i++){
        x*=2;
        x+=bin[i];
    }
    return x;

}

void convertIntToBinary(int x, int bin[], int size){
    int temp=2;
    for(int i=size-1; i>=0; i--){
        if(x%temp==0){
            bin[i]=0;
        }
        else{
            bin[i]=1;
            x-=x%temp;
        }
        temp*=2;
    }
}

int Enc_RSA(int m, int p, int q, int b){
    return mod_power(m,b,(p*q));
}

int Dec_RSA(int c, int n, int a){
    return mod_power(c,a,n);
}

// int main(void){
//     int publicKey[2];
//     int privateKey[3];
//     int m=253;
//     generateKeys(privateKey,publicKey,m);
//     printf("\n p:%d q:%d b:%d n:%d a:%d",privateKey[0],privateKey[1],privateKey[2],publicKey[0],publicKey[1]);
    
//     printf("\n\nPlainText = %d\n",m);
//     int c = Enc_RSA(m,privateKey[0],privateKey[1],privateKey[2]);
//     printf("\n\nCipher Text = %d\n",c);
//     int correctness = Dec_RSA(c,publicKey[0],publicKey[1]);
//     printf("\n\nCorrectness = %d\n\n",correctness);
// }