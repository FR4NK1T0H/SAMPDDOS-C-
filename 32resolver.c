/* Creditos: Frankito FSAMP (Wachichorro) */
#include <stdlib.h>
#include <stdio.h>

#define VECTOR 22 // 0x16

int vect = VECTOR;
char conv[2];
int secuencia = 0;
int keymaster;

int main(int argc, char *argv[]){
    if(argc < 1)
    {
        printf("- Uso: %s <NUM>\n", argv[0]);
        exit(1);
    }
    keymaster = atoi(argv[1]);
   while(256 <= keymaster)
    {
        keymaster = keymaster - 256;
    }
        printf("[SECUENCIA 0](+1) %d -> %02x \n", vect, (char)(vect & 0xFFFF));
        secuencia++;
        for(int i = 0; i != 128; i++)
        {
        vect = vect + 1;
        secuencia++;
        sprintf(conv, "%d", vect);
                if (keymaster == secuencia - 1)
        {
            printf(" \n \n --------> %02x <-------- \n \n", vect);
            break;
        }
        printf("%d -> %02x  %s\n",  secuencia - 1, (char)(vect & 0xFFFF), conv);
        vect = vect - 3;
                if(secuencia == 8)
        {
            printf("[SECUENCIA 8](+16)");
            vect = vect + 16;
        }
        else if(secuencia == 16)
        {
            vect = vect - 16;
        printf("[SECUENCIA 16](-16)");
        }
        else if(secuencia == 24)
        {
            vect = vect + 16;
            printf("[SECUENCIA 24](+16)");
        }
        else if(secuencia == 32)
        {
            vect = vect + 48;
            printf("[SECUENCIA 32](+48)");
        }
        else if(secuencia ==  40)
        {   
            vect = vect + 16;
            printf("[SECUENCIA 40](+16)");
        }
        else if(secuencia == 48)
        {   
            vect = vect - 16;
            printf("[SECUENCIA 48](-16)");
        }
        else if(secuencia == 56)
        {   
            vect = vect + 16;
            printf("[SECUENCIA 56](+16)");
        }
        else if(secuencia == 64)
        {
            vect = vect + 48;
            printf("SECUENCIA [64](+48)");
        }
        else if(secuencia == 72)
        {
            vect = vect + 16;
            printf("SECUENCIA [72](+16)");
        }
        else if(secuencia == 80)
        {
            vect = vect - 16;
            printf("SECUENCIA [80](-16)");
        }
        else if(secuencia == 88)
        {
            vect = vect + 16;
            printf("SECUENCIA [88](+16)");
        }
        else if(secuencia == 96)
        {
            vect = vect + 48;
            printf("SECUENCIA [96](+48)");
        }
        else if(secuencia == 104)
        {
            vect = vect + 16;
            printf("SECUENCIA [104](+16)");
        }
        else if(secuencia == 112)
        {
            vect = vect - 16;
            printf("SECUENCIA [112](-16)");
        }
        else if(secuencia == 120)
        {
            vect = vect + 16;
            printf("SECUENCIA [120](+16)");
        }
        else if(secuencia == 128)
        {
            vect = vect + 48;
            printf("SECUENCIA [128](+48)");
        }
        else if(secuencia == 136)
        {
            vect = vect + 16;
            printf("SECUENCIA [136](+16)");
        }
        else if(secuencia == 144)
        {
            vect = vect - 16;
            printf("SECUENCIA [144](-16)");
        }
        else if(secuencia == 152)
        {
            vect = vect + 16;
            printf("SECUENCIA [152](+16)");
        }
        else if(secuencia == 160)
        {
            printf("SECUENCIA [160](+48)");
            vect = vect + 48;
        }
        else if(secuencia == 168)
        {
            printf("SECUENCIA [168](+16)");
            vect = vect + 16;
        }
        else if(secuencia == 176)
        {
            printf("SECUENCIA [176](-16)");
            vect = vect - 16;
        }
        else if(secuencia == 184)
        {
            printf("SECUENCIA [184](+16)");
            vect = vect + 16;
        }
        else if(secuencia == 192)
        {
            printf("SECUENCIA [192](+48)");
            vect = vect + 48;
        }
        else if(secuencia == 200)
        {
            printf("SECUENCIA [200](+16)");
            vect = vect + 16;
        }
        else if(secuencia == 208)
        {
            printf("SECUENCIA [208](-16)");
            vect = vect - 16;
        }
        else if(secuencia == 216)
        {
            printf("SECUENCIA [216](+16)");
            vect = vect + 16;
        }
        else if(secuencia == 224)
        {
            printf("SECUENCIA [224](+48)");
            vect = vect + 48;
        }
        else if(secuencia == 232)
        {
            printf("SECUENCIA [232](+16)");
            vect = vect + 16;
        }
        else if(secuencia == 240)
        {
            printf("SECUENCIA [240](-16)");
            vect = vect - 16;
        }
        else if(secuencia == 248)
        {
            printf("SECUENCIA [248](+16)");
            vect = vect + 16;
        }
        else if(secuencia == 256)
        {
            vect = 22;
            secuencia = 1;
        }
        sprintf(conv, "%d", vect);
        secuencia++;
        printf("%d -> %02x %s \n",  secuencia - 1, (char)(vect & 0xFFFF), conv);       
           if (keymaster == secuencia - 1)
        {
            printf(" \n \n --------> %02x <-------- \n \n", vect);
            break;
        }
    }
    return 0;
}
