struct reg_lista {
	struct listagen *cabeca;
	struct listagen *cauda;
};

union info_lista {
	char info[8];
	struct reg_lista lista;
};

typedef struct listagen {
	char terminal;
	union info_lista no;
}ListaGen;

ListaGen *CriaTerminal(char *info) {
	ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
	L->terminal = 1;
	strcpy(L->no.info, info);
	return L;
}

char Nula(ListaGen *L) {
	return L==NULL;
}

char Atomo(ListaGen *L) {
	return !Nula(L) && L->terminal;
}

ListaGen *Construir(ListaGen *H, ListaGen *T) {
	if (Atomo(T)) {
		printf("Cons: Segundo arqumento nao pode ser Atomo!");
		return NULL;
	} else {
		ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
		L->terminal = 0;
		L->no.lista.cabeca = H;
		L->no.lista.cauda = T;
		return L;
	}	
}

ListaGen *Tail(ListaGen *L) {
	if (Nula(L) || Atomo(L)) {
		printf("Tail: argumento deve ser lista não vazia!");
		return NULL;
	}
	else
		return L->no.lista.cauda;
}

