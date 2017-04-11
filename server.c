// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
#include <math.h>

int *convert_binary(char plaintext)
{
    int i;
    //int hasil[8];
    int *hasil = (int*) malloc(8*sizeof(int));
    for (i=7; i>=0; i--)
    {
        hasil[i] = (plaintext >> i) & 1;
        //printf("%d", hasil);
    }
    //printf("\n");
    return hasil;
}

int *decimalToBinary(long n) 
{
    //int remainder[4]; 
    int *remainder = (int*) malloc(4*sizeof(int));
    long binary = 0, i = 1, j=3;
  
    while(n != 0) {
        remainder[j] = n%2;
        j--;
        n = n/2;
    }
    if(j==0) remainder[0]=0;
    return remainder;
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
    
        // Creating socket file descriptor
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }
          
        // Forcefully attaching socket to the port 8080
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                      &opt, sizeof(opt)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons( PORT );
          
        // Forcefully attaching socket to the port 8080
        if (bind(server_fd, (struct sockaddr *)&address, 
                                     sizeof(address))<0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                           (socklen_t*)&addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
    while(1)
    {  
        valread = read( new_socket , buffer, 1024);

        int ip[64] = {58, 50, 42, 34, 26, 18, 10, 2, 
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9,  1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
        };
        int PC1[56] = {57, 49, 41,  33, 25, 17, 9,
                        1,  58, 50, 42, 34, 26, 18,
                        10, 2,  59, 51, 43, 35, 27,
                        19, 11, 3,  60, 52, 44, 36,
                        63, 55, 47, 39, 31, 23, 15,
                        7,  62, 54, 45, 38, 30, 22,
                        14, 6,  61, 53, 45, 37, 29,
                        21, 13, 5,  28, 20, 12, 4
        };
        int PC2[48] = {14,  17, 11, 24, 1,  5,
                        3,  28, 15, 6,  21, 10,
                        23, 19, 12, 4,  26, 8,
                        16, 7,  27, 20, 13, 2,
                        41, 52, 31, 37, 47, 55,
                        30, 40, 51, 45, 33, 48,
                        44, 49, 39, 56, 34, 53,
                        46, 42, 50, 36, 29, 32
        };
        int geserbit[16] = {1, 1, 2, 2, 2, 2, 2, 2, 
                            1, 2, 2, 2, 2, 2, 2, 1
        };
        int E[48] = {   32, 1,  2,  3,  4,  5,
                        4,  5,  6,  7,  8,  9,
                        8,  9,  10, 11, 12, 13,
                        12, 13, 14, 15, 16, 17,
                        16, 17, 18, 19, 20, 21,
                        20, 21, 22, 23, 24, 25,
                        24, 25, 26, 27, 28, 29,
                        28, 29, 30, 31, 32, 1
        };  
        int sbox [8][64] = {
            {
                14, 4,  13, 1,  2,  15, 11, 8, 3,   10, 6,  12, 5,  9,  0,  7,
                0,  15, 7,  4,  14, 2,  13, 1, 10,  6,  12, 11, 9,  5,  3,  8,
                4,  1,  14, 8,  13, 6,  2,  11, 15, 12, 9,  7,  3,  10, 5,  0,
                15, 12, 8,  2,  4,  9,  1,  7, 5,   11, 3,  14, 10, 0,  6,  13
            },
            {
                15, 1,  8,  14, 6,  11, 3,  4,  9,  7,  2,  13, 12, 0,  5, 10,
                3,  13, 4,  7,  15, 2,  8,  14, 12, 0,  1,  10, 6,  9,  11, 5,
                0,  14, 7,  11, 10, 4,  13, 1,  5,  8,  12, 6,  9,  3,  2,  15,
                13, 8,  10, 1,  3,  15, 4,  2,  11, 6,  7,  12, 0,  5,  14, 9
            },
            {
                10, 0,  9,  14, 6,  3,  15, 5,  1,  13, 12, 7,  11, 4,  2,  8,
                13, 7,  0,  9,  3,  4,  6,  10, 2,  8,  5,  14, 12, 11, 15, 1,
                13, 6,  4,  9,  8,  15, 3,  0,  11, 1,  2,  12, 5,  10, 14, 7,
                1,  10, 13, 0,  6,  9,  8,  7,  4,  15, 14, 3,  11, 5,  2,  12
            },
            {
                7,  13, 14, 3,  0,  6,  9,  10, 1,  2,  8,  5,  11, 12, 4,  15,
                13, 8,  11, 5,  6,  15, 0,  3,  4,  7,  2,  12, 1,  10, 14, 9,
                10, 6,  9,  0,  12, 11, 7,  13, 15, 1,  3,  14, 5,  2,  8,  4,
                3,  15, 0,  6,  10, 1,  13, 18, 9,  4,  5,  11, 12, 7,  2,  14
            },
            {
                2,  12, 4,  1,  7,  10, 11, 6,  8,  5,  3,  15, 13, 0,  14, 9,
                14, 11, 2,  12, 4,  7,  13, 1,  5,  0,  15, 10, 3,  9,  8,  15,
                4,  2,  1,  11, 10, 13, 7,  8,  15, 9,  12, 5,  6,  3,  0,  14,
                11, 8,  12, 7,  1,  14, 2,  13, 6,  15, 0,  9,  10, 4,  5,  3,
            },
            {
                12, 1,  10, 15, 9,  2,  6,  8,  0,  13, 3,  4,  14, 7,  5,  11,
                10, 15, 4,  2,  7,  12, 9,  5,  6,  1,  13, 14, 0,  11, 3,  8,
                9,  14, 15, 5,  2,  8,  12, 3,  7,  0,  4,  10, 1,  13, 11, 6,
                4,  3,  2,  12, 9,  5,  15, 10, 11, 14, 1,  7,  6,  0,  8,  13
            },
            {
                4,  11, 2,  14, 15, 0,  8,  13, 3,  12, 9,  7,  5,  10, 6,  1,
                13, 0,  11, 7,  4,  9,  1,  10, 14, 3,  5,  12, 2,  15, 8,  6,
                1,  4,  11, 13, 12, 3,  7,  14, 10, 15, 6,  8,  0,  5,  9,  2,
                6,  11, 13, 8,  1,  4,  10, 7,  9,  5,  0,  15, 14, 2,  3,  12
            },
            {
                13, 2,  8,  4,  6,  15, 11, 1,  10, 9,  3,  14, 5,  0,  12, 7,
                1,  15, 13, 8,  10, 3,  7,  4,  12, 5,  6,  11, 0,  14, 9,  2,
                7,  11, 4,  1,  9,  12, 14, 2,  0,  6,  10, 13, 15, 3,  5,  8,
                2,  1,  14, 7,  4,  10, 8,  13, 15, 12, 9,  0,  3,  5,  6,  11
            }
        };
        int pbox[32]={
                16, 7,  20, 21, 29, 12, 28, 17,
                1,  15, 23, 26, 5,  18, 31, 10,
                2,  8,  24, 14, 32, 27, 3,  9,
                19, 13, 30, 6,  22, 11, 4,  25
        };
        int p_invers[64]={
                40, 8,  48, 16, 56, 24, 64, 32,
                39, 7,  47, 15, 55, 23, 63, 31,
                38, 6,  46, 14, 54, 22, 62, 30,
                37, 5,  45, 13, 53, 21, 61, 29,
                36, 4,  44, 12, 52, 20, 60, 28,
                35, 3,  43, 11, 51, 19, 59, 27,
                34, 2,  42, 10, 50, 18, 58, 26,
                33, 1,  41, 9,  49, 17, 57, 25
        };
        
        char plaintext[7];
        char key[7];
        int i, j, hasil[63], initial[63], hasil_PC1[55], *perm, *keys, a, b, count, L[31], R[31], C[27], D[27], hasilkey[63];
        //char counter[7]={0, 0, 0, 0, 0, 0, 0, 0};
        //int *cleftshift, *dleftshift;
        //for (i=1; i<=8; i++)
        printf("Masukkan : "); 
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
                hasil[j] =  *(perm+count);
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
        //  printf("%d ", Lo[i]);
        //}
        //printf("\n");
        //for(i=0; i<32; i++)
        //{
        //  printf("%d ", Ro[i]);
        //}
        
        //LANGKAH 3
        for(i=0; i<56; i++)
        {
            hasil_PC1[i] = hasilkey[PC1[i]-1];
        }
        
        //for(i=0; i<56; i++)
        //{
        //  printf("%d", hasil_PC1[i]);
        //}
        //printf("\n");
        j=28;
        for (i=0; i<28; i++)
        {
            C[i] = hasil_PC1[i];
            //printf("%d", C[i]);
            D[i] = hasil_PC1[j];
            //printf("%d", D[i]);
            j++;
        }
        /*
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
        */
        //LANGKAH 4
        int gabung[55], hasil_PC2[47], k, panjang=28, sb, S, temp1, temp2, hasil_xor[48], hasil_e[48],hasil_pbox[32], hasil_akhir[64], chipertext[64];
        for(i=0; i<16; i++)
        {
            sb = geserbit[i];
            S = panjang-sb;
            if(sb == 1){
                temp1 = C[0];
                //temp2 = C[1];
                for(i=0; i<S; i++)
                {
                    C[i] = C[i + sb];
                }
                
                for(i=S; i<panjang; i++)
                {
                    C[i] = temp1;
                }
                for(i=0; i<panjang; i++)
                {
                    printf("%d", C[i]);
                }
                printf("\n");
                temp1 = D[0];
                //temp2 = C[1];
                for(i=0; i<S; i++)
                {
                    D[i] = D[i + sb];
                }
                
                for(i=S; i<panjang; i++)
                {
                    D[i] = temp1;
                }
                for(i=0; i<panjang; i++)
                {
                    printf("%d", D[i]);
                }
                printf("\n");
            }
            else{
                temp1 = C[0];
                temp2 = C[1];
                for(i=0; i<panjang-sb; i++)
                {
                    C[i] = C[i + sb];
                }
                C[S] = temp2;
                C[panjang] = temp1;
            
                for(i=0; i<panjang; i++)
                {
                    printf("%d", C[i]);
                }
                printf("\n");
                
                temp1 = D[0];
                temp2 = D[1];
                for(i=0; i<panjang-sb; i++)
                {
                    D[i] = D[i + sb];
                }
                D[S] = temp2;
                D[panjang] = temp1;
            
                for(i=0; i<panjang; i++)
                {
                    printf("%d", D[i]);
                }
                printf("\n");
            }
            
            k=28;
            for(j=0; j<28; j++)
            {
                gabung[j] = C[j];
                gabung[k] = D[j];
                k++;
            }
            for(j=0; j<56; j++)
            {
                printf("%d", gabung[j]);
            }
            printf("\n");
            for (j=0; j<48; j++)
            {
                hasil_PC2[j] = gabung[PC2[j]-1];
            }
            for(j=0; j<48; j++)
            {
                printf("%d", hasil_PC2[j]);
            }
            printf("\n");   
            //langkah 5
            for (j=0 ; j<48; j++)
            {
                hasil_e[j]= R[E[j]-1];
            }
            for (j=0 ; j<48; j++)
            {
                printf("%d", hasil_e[j]);
            }
            printf("\n");
            for (j=0; j<48; j++)
            {
                if (hasil_PC2[j]== hasil_e[j]) hasil_xor[j]=0;
                else hasil_xor[j] = 1;
            }
            for (j=0; j<48; j++)
            {
                printf("%d", hasil_xor[j]);
            }
            printf("\n");
            int x =0, j=0;
            int y= 0, baris = 0, kolom = 0;
            int cocok =0;
            int hasil_sbox[32];
            int *biner;
            
            for (x=0;x<48;)
            {
                baris= (hasil_xor[x]*2)+(hasil_xor[x+1]*1);
                kolom= (hasil_xor[x+2]*8)+(hasil_xor[x+3]*4)+(hasil_xor[x+4]*2)+(hasil[x+5]*1);
                if(baris>1) baris = 16*(baris-1);
                else if (baris ==0) baris = 16*(baris);
                
                baris=baris+kolom;
                cocok = sbox[j][baris];
                
                biner = decimalToBinary(cocok);
                hasil_sbox[y]= *(biner);
                hasil_sbox[y+1]= *(biner+1);
                hasil_sbox[y+2]= *(biner+2);
                hasil_sbox[y+3]= *(biner+3);
                
                y=y+4;
                x=x+6;
                j++;
            }
            for(j=0; j< 32; j++){
                int c= pbox[j];
                hasil_pbox[j]= hasil_sbox[c-1];
            }
            for( j=0;j<32;j++){
                if(hasil_pbox[j]== L[j]){
                    L[j]=R[j];
                    R[j]=0;
                }
                else {
                    L[j]=R[j];
                    R[j]=1;
                }
            }
        }
        
        k=32;
        for (j=0; j<32; j++){
            hasil_akhir[j]= L[j];
            hasil_akhir[k]= R[j];
            k++;
        }
        //for(j=0;j<64;j++) printf("%d", hasil_akhir[j]);
        
        for(j=0;j<64; j++){
            int a= p_invers[j];
            chipertext[j]=hasil_akhir[a-1];
        }
        printf("Chipertext : ");
        for(j=0;j<64;j++) printf("%d", chipertext[j]);
        printf("\n");
        
        //char input[7];
        int *des, masukkan[63], hasil_CTR[63], dekrip[63];
        //printf("Masukkan Plaintext : ");
        //scanf("%s", input);
        for(i=0; i<8; i++)
        {
            des = convert_binary(buffer[i]);
            a=i*8;
            b=(i+1)*8;
            count = 7;
            for (int j = a; j<b; j++)
            {
                masukkan[j] =   *(des+count);
                //hasilkey[j] = *(keys+count);
                count--;
            }   
        }
        printf("Plaintext : ");
        for(j=0;j<64;j++) printf("%d", masukkan[j]);
        printf("\n");
        
        for (i=0; i<64; i++)
            {
                if (chipertext[i]== masukkan[i]) hasil_CTR[i]=0;
                else hasil_CTR[i] = 1;
            }
        printf("Hasil CTR : ");
        for(j=0;j<64;j++) printf("%d", hasil_CTR[j]);
        printf("\n");
        
        //decrypt
        for (i=0; i<64; i++)
            {
                if (hasil_CTR[i]== chipertext[i]) dekrip[i]=0;
                else dekrip[i] = 1;
            }
        
        printf("Dekrip : ");
        for(j=0;j<64;j++) printf("%d", dekrip[j]);
        printf("\n");

        printf("%s\n",buffer );
        send(new_socket , hello , strlen(hello) , 0 );
        printf("Hello message sent\n");
    }

    return 0;
}
