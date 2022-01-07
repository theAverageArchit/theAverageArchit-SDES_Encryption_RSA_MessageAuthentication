#include "sDES.h"

void HCBCround(int c_current[], int c_last[],int p_current[], int key[], int Enc_Size);
void hCBC(int arr[],int key[],int size, int cbcmac[], int Enc_Size);