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
	printf("teste 1");
	FILE *arquivo = fopen(nomeArquivo, "r");
	printf("teste 1.10");
	Linha *linhas = criaLinha();
	printf("teste 1.11");
	Token *token;
	Descritor *primeiraLinha;
	printf("teste 1.12");
	
	primeiraLinha->inicio = linhas;
	
	printf("teste 1.13");
	
	char linhaLida[256];
	char espaco[] = " ,:";
	char *auxToken;
	
	printf("teste 1.1");
	
	fgets(linhaLida, 256, arquivo);
	token = separaLinhaTokens(linhaLida);
	linhas->inicioToken = token;
	printf("\n teste 1.1");
	while(!feof(arquivo)) {
		printf("entrou ");
		printf("\n");
		/*while(auxToken != NULL) {
			printf("%s ", token->texto);
			auxToken = strtok(NULL, espaco);
			if(auxToken != NULL) {
				token->prox = criaToken(auxToken);
				token = token->prox;
			}
			getch();
		}*/
		printf("teste 1.2");
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
			/*while(auxToken != NULL) {
			printf("%s ", token->texto);
			auxToken = strtok(NULL, espaco);
			if(auxToken != NULL) {
				token->prox = criaToken(auxToken);
				token = token->prox;
			}*/
			getch();
		}		
	}

	
	
	printf("teste 2");
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
		//printf("teste4");
		while(linhas->inicioToken!=NULL) {
			//printf("teste5");
			printf("%s ", linhas->inicioToken->texto);
			linhas->inicioToken = linhas->inicioToken->prox;
		}
		//printf("\n");
		linhas = linhas->prox;
	}
	
	return 0;
}
