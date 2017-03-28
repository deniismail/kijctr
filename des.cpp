#include<stdio.h>
#include<stdlib.h>

int *convert_binary(char plaintext)
{
	int i, hasil[8];
	for (i=7; i>=0; i--)
	{
		hasil[i] = (plaintext >> i) & 1;
		//printf("%d", hasil);
	}
	//printf("\n");
	return hasil;
}

void geserkiri (int *C, int panjang, int sb)
{
	int i, temp, temp1, temp2, S;
	if (sb == 1)
	{
		temp = C[0];
		printf("%d\n", temp);
		S = panjang-sb;
		for(i=0; i<S; i++)
		{
			C[i] = C[i + sb];
			if(i==S) C[i] = temp;
		}
		for(i=0; i<panjang; i++)
		{
			printf("%d", C[i]);
		}
		printf("\n");
	}
	if(sb == 2) 
	{
		temp1 = C[0];
		temp2 = C[1];
		printf("%d\n %d\n", temp1, temp2);
		S = panjang-sb; 
		for(i=0; i<S; i++)
		{
			
			C[i] = C[i + sb];
		}
		C[S] = temp1;
		C[S+1] = temp2;
		for(i=0; i<panjang; i++)
		{
			printf("%d", C[i]);
		}
		printf("\n");
	}
	
}



int main()
{
	int ip[64] = {58, 50, 42, 34, 26, 18, 10, 2, 
		60,	52,	44,	36,	28,	20,	12,	4,
		62,	54,	46,	38,	30,	22,	14,	6,
	 	64,	56,	48,	40,	32,	24,	16,	8,
		57,	49,	41,	33,	25,	17,	9,	1,
		59,	51,	43,	35,	27,	19,	11,	3,
		61,	53,	45,	37,	29,	21,	13,	5,
		63,	55,	47,	39,	31,	23,	15,	7
	};
	int PC1[56] = {57, 49, 41,	33, 25, 17, 9,
					1,	58,	50,	42,	34,	26,	18,
					10,	2,	59,	51,	43,	35,	27,
					19,	11,	3,	60,	52,	44,	36,
					63,	55,	47,	39,	31,	23,	15,
					7,	62,	54,	45,	38,	30,	22,
					14,	6,	61,	53,	45,	37,	29,
					21,	13,	5,	28,	20,	12,	4};
	int geserbit[16] = {1, 1, 2, 2, 2, 2, 2, 2, 
						1, 2, 2, 2, 2, 2, 2, 1};
						
	char plaintext[7];
	char key[7];
	int i, j, hasil[63], initial[63], hasil_PC1[55], *perm, *keys, a, b, count, L[31], R[31], C[27], D[27], hasilkey[63];
	//int *cleftshift, *dleftshift;
	//for (i=1; i<=8; i++)
	printf("Masukkan PlainText : "); 
	scanf ("%s", plaintext);
	printf("Masukkan Key : ");
	scanf ("%s", key);
	
	//LANGKAH 1
	for(i=0; i<8; i++)
	{
	  	perm = convert_binary(plaintext[i]);
	  	keys = convert_binary(key[i]);
	  	a=i*8;
	  	b=(i+1)*8;
	  	count = 7;
	  	for (int j = a; j<b; j++)
	  	{
	  		hasil[j] = 	*(perm+count);
	  		hasilkey[j] = *(keys+count);
	  		count--;
		}  	
	}
	//LANGKAH 2
	for(i=0; i<64; i++)
	{
		initial[i] = hasil[ip[i]-1];
	}
	j=32;
	for(i=0; i<32; i++)
	{
		L[i] = initial[i];
		R[i] = initial[j];
		j++;
	}
	
	//for(i=0; i<32; i++)
	//{
	//	printf("%d ", Lo[i]);
	//}
	//printf("\n");
	//for(i=0; i<32; i++)
	//{
	//	printf("%d ", Ro[i]);
	//}
	
	//LANGKAH 3
	for(i=0; i<56; i++)
	{
		hasil_PC1[i] = hasilkey[PC1[i]-1];
	}
	
	//for(i=0; i<56; i++)
	//{
	//	printf("%d", hasil_PC1[i]);
	//}
	printf("\n");
	j=28;
	for (i=0; i<28; i++)
	{
		C[i] = hasil_PC1[i];
		//printf("%d", C[i]);
		D[i] = hasil_PC1[j];
		//printf("%d", D[i]);
		j++;
	}
	for(i=0; i<28; i++)
		{
			printf("%d", C[i]);
		}
	printf("\n");
	for(i=0; i<28; i++)
		{
			printf("%d", D[i]);
		}
	printf("\n \n");
	//LANGKAH 4
	for(i=0; i<3; i++)
	{
		geserkiri(C, 28, geserbit[i]);
		geserkiri(D, 28, geserbit[i]);
		printf("\n");
	}
	
	return 0;
}
