
/*
 * Created on: 19 de mai de 2020
     Author: lucas.rodrigues
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Caixinha {
	struct Caixinha *ant;
	char valor;
	struct Caixinha *prox;

} Caixinha;

typedef struct Lista {

	Caixinha *inicio;

} Lista;

void create(Lista *lista);
void inserir(Lista *lista, char valor);
int retirar(Lista *lista, char valor);
Lista* procurar(Lista *lista, char valor);
void imprimir(Lista *lista);

int main() {
	char dado, dado_remove, dado_busca;
	int resp = 1;
	int retorno_retira;
	Lista lista_vogal;
	Lista lista_cons;
	Lista *retorno_busca;

	create(&lista_vogal);
	create(&lista_cons);

	while (resp != 0) {

		printf("Digite o caractere:");
		scanf("%c", &dado);
		if (dado == '\n')
			scanf("%c", &dado);

		if (dado == 'a' || dado == 'e' || dado == 'i' || dado == 'o'
				|| dado == 'u') {
			inserir(&lista_vogal, dado);
		} else if (dado != ' ' && dado != '@' && dado != '#' && dado != '%'
				&& dado != '&' && dado != '*' && dado != '(' && dado != ')'
				&& dado != '!' && dado != '?') {
			inserir(&lista_cons, dado);
		}

		printf("Deseja continuar? (1-SIM e 0-NAO):");
		scanf("%d", &resp);

		fflush(stdin);

	}

	printf("*Lista das vogais*\n");
	imprimir(&lista_vogal);
	printf("\n*Lista das consoantes*\n");
	imprimir(&lista_cons);
	printf("\n");


	fflush(stdin);
	printf("Digite o caractere a ser procurado: ");
	scanf("%c", &dado_busca);
	if(dado_busca == '\n')
		scanf("%c",&dado_busca);

	if (dado_busca == 'a' || dado_busca == 'e' || dado_busca == 'i'
			|| dado_busca == 'o' || dado_busca == 'u') {

		retorno_busca = procurar(&lista_vogal, dado_busca);
	} else if (dado_busca != ' ' && dado_busca != '@' && dado_busca != '#'
			&& dado_busca != '%' && dado_busca != '&' && dado_busca != '*'
			&& dado_busca != '(' && dado_busca != ')') {

		retorno_busca = procurar(&lista_cons, dado_busca);
	}

	if (retorno_busca == NULL) {
		printf("Elemento não encontrado! \n");
	} else
		printf("Elemento encontrado! \n");

	fflush(stdin);
	printf("Digite o caractere a ser removido:");
	scanf("%c", &dado_remove);
	if(dado_remove == '\n')
		scanf("%c", &dado_remove);
	if (dado_remove == 'a' || dado_remove == 'e' || dado_remove == 'i'
			|| dado_remove == 'o' || dado_remove == 'u') {
		retorno_retira = retirar(&lista_vogal, dado_remove);

	} else if (dado_remove != ' ' && dado_remove != '@' && dado_remove != '#'
			&& dado_remove != '%' && dado_remove != '&' && dado_remove != '*'
			&& dado_remove != '(' && dado_remove != ')') {
		retorno_retira = retirar(&lista_cons, dado_remove);

	}

	if (retorno_retira == 0) {
		printf("Elemento nao retirado!\n");
	} else
		printf("Elemento retirado!\n");

	printf("\n*Lista das vogais*\n");
	imprimir(&lista_vogal);
	printf("\n*Lista das consoantes*\n");
	imprimir(&lista_cons);

	printf("\n\n **Fim do programa");
	return 0;
}
void create(Lista *lista) {
	lista->inicio = NULL;
}
void inserir(Lista *lista, char valor) {
	Caixinha *nova = (Caixinha*) malloc(sizeof(Caixinha));
	nova->valor = valor;
	if (lista->inicio == NULL) {
		nova->ant = nova;
		nova->prox = nova;
		lista->inicio = nova;
	} else {
		Caixinha *aux = lista->inicio;
		while (aux->prox != lista->inicio)
			aux = aux->prox;

		aux->prox = nova; //prox elemento do ultimo sera nova
		nova->ant = aux; //o elemento anterior de nova sera ant
		nova->prox = lista->inicio; //proximo elemento de nova sera o inicio
		lista->inicio->ant = nova; //o anterior de incio acessa o ultimo elmento

	}
}
int retirar(Lista *lista, char valor) {

	Caixinha *aux = lista->inicio;
	Caixinha *nova;
	create(&nova);
	if (lista->inicio == NULL)
		return 0;
	else {
		if (aux->valor == valor) {
			nova = aux->prox;
			nova->ant = aux->ant;
			nova->ant->prox = nova;
			lista->inicio = nova;
		} else {
			while (aux->prox != lista->inicio) {
				if (aux->valor == valor) {
					nova = aux->prox; //peguei o proximo elemento do retirado
					nova->ant = aux->ant; //anterior de nova sera o anterior do elemento retirado
					nova->ant->prox = nova; //o proximo do anterior do elemento retirado sera nova

					break;
				}
				aux = aux->prox;

			}
			if (aux->prox == lista->inicio) { //caso tenha ido ate o fim
				if (aux->valor == valor) {
					nova = aux->ant; //anterior do elemento removido
					nova->prox = lista->inicio; //proximo de nova sera o inicio
					lista->inicio->ant = nova; //ant de inicio aponta para nova
				} else {
					return 0;
				}
			}
		}

	}
	free(aux);
	return 1;

}
Lista* procurar(Lista *lista, char valor) {
	Caixinha *aux = lista->inicio;
	if (lista->inicio != NULL) {
		do {
			if (aux->valor == valor)
				return aux;

			aux = aux->prox;
		} while (aux->prox != lista->inicio);
	}
	return NULL;
}
void imprimir(Lista *lista) {
	if (lista->inicio != NULL) {
		Caixinha *aux = lista->inicio;

		do {
			printf(" %c ", aux->valor);
			aux = aux->prox;
		} while (aux != lista->inicio);
	}
}
