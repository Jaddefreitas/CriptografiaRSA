#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chaves.h"
#include "descriptografar.h"
#include "interface.h"

l_int descriptografaLetra(l_int caractereCriptografado, l_int n, l_int d) {
	l_int r = 1;
	for(; d > 0; d--) r = (r * caractereCriptografado) % n;
	return r;
}

void geraArquivoDescriptografado(char nomeDoArquivoCriptografado[], l_int n, l_int d) {
	unsigned char caractereCriptografado;
	l_int numero;
	int i = 0, j;
	char num[100];
	FILE *arqCriptografado = fopen(nomeDoArquivoCriptografado, "r");
	FILE *arqDescriptografado = NULL;
	char nomeDoArquivoDescriptografado[FILENAME_MAX];
	strcpy(nomeDoArquivoDescriptografado, nomeDoArquivoCriptografado);
	strcat(nomeDoArquivoDescriptografado, ".txt");
	arqDescriptografado = fopen(nomeDoArquivoDescriptografado, "w+");
	while(fread(&caractereCriptografado, sizeof(unsigned char), 1, arqCriptografado) == 1) {
		if(caractereCriptografado == 32) {
			i = 0;
			numero = atoi(num);
			numero = descriptografaLetra(numero, n, d);
			for(j = 0; j < strlen(num); j++) num[j] = ' ';
			if(numero == 26) {
				numero = 32;
			} else {
				numero = numero + 65;
			}
			fprintf(arqDescriptografado, "%c", numero);
		} else {
			num[i] = caractereCriptografado;
			i++;
		}
	}
	fclose(arqCriptografado);
	fclose(arqDescriptografado);
}

void descriptografar() {
	l_int p, q, e;
	char arquivo[FILENAME_MAX];
	i_descriptografar(1);
	scanf("%[^\n]s", arquivo);
	i_descriptografar(2);
	scanf("%lu", &p);
	i_descriptografar(3);
	scanf("%lu", &q);
	i_descriptografar(4);
	scanf("%lu", &e);
	i_descriptografar(5);
	geraArquivoDescriptografado(arquivo, geraN(p, q), geraD(geraFiN(p, q), e));
	i_descriptografar(6);
}
