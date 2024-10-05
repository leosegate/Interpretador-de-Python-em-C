#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef struct token{
	char texto[20];
	struct token *prox;
}Token;

typedef struct linha{
	Token *inicioToken;
	struct linha *prox, *ant;
}Linha;

typedef struct {
	Linha *inicio;
}Descritor;

Token* criaToken(char texto[20]) {
	Token *novo = (Token *)malloc(sizeof(Token));
	strcpy(novo->texto, texto);
	novo->prox = NULL;
	return novo;
}

Linha* criaLinha() {
	Linha *novo = (Linha *)malloc(sizeof(Linha));
	novo->inicioToken = NULL;
	novo->ant = NULL;
	novo->prox = NULL;
}

Token *separaLinhaTokens(char linha[256]) {
    int i = 0;
    int j = 0;
    char first = '1';
    char aux[20] = {0};
    Token *token, *oldToken = NULL;
    Token *firstToken = NULL;

    while (linha[i] != '\0') {
        j = 0; 
        while (linha[i] != ' ' && linha[i] != ',' && linha[i] != '\0') {
            aux[j++] = linha[i++];
        }
        aux[j] = '\0'; 
        if (j > 0) {
            token = criaToken(aux);
            if (first != '1') {
                oldToken->prox = token;
            } else {
                firstToken = token;
                first = '0';
            }
            oldToken = token;
        }
        while (linha[i] == ' ' || linha[i] == ',') {
            i++;
        }
    }
    return firstToken;
}

Descritor* varrerArquivo(char nomeArquivo[100]) {
	FILE *arquivo = fopen(nomeArquivo, "r");
	Linha *linhas = criaLinha();
	Token *token;
	Descritor *primeiraLinha;
	
	primeiraLinha->inicio = linhas;
	
	char linhaLida[256];
	char espaco[] = " ,:";
	char *auxToken;
	
	if(arquivo == NULL) {
		printf("Erro ao abrir o arquivo.");
		return NULL; 
	} else {
		fgets(linhaLida, 256, arquivo);
		token = separaLinhaTokens(linhaLida);
		linhas->inicioToken = token;
		while(!feof(arquivo)) {
			linhas->prox = criaLinha();
			linhas->prox->ant = linhas;
			linhas = linhas->prox;
			fgets(linhaLida, 256, arquivo);
			if(!feof(arquivo)) {
				token = separaLinhaTokens(linhaLida);
				linhas->inicioToken = token;
			} else {
				token = separaLinhaTokens(linhaLida);
				linhas->inicioToken = token;
				getch();
			}		
		}
	}	
	fclose(arquivo);
	return primeiraLinha;
}

int main() {
	char arquivo[50];
	
	printf("digite o nome do arquivo: ");
	gets(arquivo);
	
	Descritor *descritor = varrerArquivo(arquivo);
	
	Linha *linhas = descritor->inicio;
	printf("\n");
	while(linhas!=NULL) {
		while(linhas->inicioToken!=NULL) {
			printf("%s ", linhas->inicioToken->texto);
			linhas->inicioToken = linhas->inicioToken->prox;
		}
		linhas = linhas->prox;
	}
	
	return 0;
}
