#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int var, i = 1, n = 8, cont = 0, inicio = 0, fin = 0, romper = 0;

    char *grande = (char*)malloc(10 * sizeof(char));
    char *chico = (char*)malloc(10 * sizeof(char));
    char *inicioc = (char*)malloc(30 * sizeof(char));
    char *finc = (char*)malloc(20 * sizeof(char));

    strcpy(grande, "Grande");
    strcpy(chico, "Chico");
    strcpy(inicioc, "ContenedorInicio");
    strcpy(finc, "ContenedorFin");

    // printf("1 = %d\n", 1%3);
    // printf("2 = %d\n", 2%3);
    // printf("3 = %d\n", 3%3);
    // printf("4 = %d\n", 4%3);
    // printf("5 = %d\n", 5%3);
    // printf("6 = %d\n", 6%3);
    // printf("7 = %d\n", 7%3);
    // printf("8 = %d\n", 8%3);
    // printf("9 = %d\n", 9%3);
    // printf("10 = %d\n", 10%3);
    // printf("11 = %d\n", 11%3);

    printf(">>> ");
    scanf("%d", &var);

   	while(i <= var) {

   		if (i%3==1) {
            printf("\n%s\n", inicioc);
            printf("[%s %d] ", grande, i);
            printf("[");
        } else {
            
            if (i%3 == 0)
                printf("\n\t%s %d\n", chico, i);
            else
                printf("\n\t%s %d ", chico, i);
        }

		if(i == var)
			romper = 1;

		if(i%3==0)
   			printf("]\n%s\n", finc);
   		
   		if(i%3==1 && romper == 1)
   			printf("]\n%s\n", finc);
   		
   		if(i%3==2 && romper == 1)
   			printf("]\n%s\n", finc);

   		cont++;
   		i++;
   	}

    free(grande);
    free(chico);
    free(inicioc);
    free(finc);

    return 0;
}

