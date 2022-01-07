extern int mod_power(int x, int n, int mod);
extern int gcd(int a, int b);
extern int multiplicativeInverse(int x, int n);
extern void generateKeys(int privateKey[], int publicKey[], int m);
extern int convertBinaryToInt(int bin[], int size);
extern void convertIntToBinary(int x, int bin[], int size);
extern int Enc_RSA(int m, int p, int q, int b);
extern int Dec_RSA(int c, int n, int a);

