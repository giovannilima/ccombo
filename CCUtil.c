#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include "CCUtil.h"



extern void doIt() {
	printf("%s\n", "Giovanni Lima Rocks!!!");
}

//COLLECTIONS FRAMEWORK
/////////// MACROS
#define CC_FREE_MEMORY(x) do{ if(objectMemoryType == DYNAMIC_OBJECTS) free(x); }while(0)
CCListObjectMemoryType objectMemoryType = STATIC_OBJECTS;


/*
 *@Description: permite adicionar  um elemente no final lista, se a lista estiver vazia esse sera criado e definido como primeiro elemento
 *@Params: -list => ponteiro do primeiro elemento da lista ; -data => o elemento a ser adicionado
 *@Return: retorna 1 se a operacao foi concluida com sucesso, 0 se nao for concluida, normalmente porque nao foi possivel alocar memoria para o elemento  
 */
extern int CCListAdd(CCList **list, void *data) {
	CCNode *current;
	CCNode *prev;
	CCNode *newNode  = NULL;
	
	newNode  = malloc(sizeof(CCNode));

	if(newNode != NULL) {
		newNode->data = data;
		newNode->nextNode = NULL;
		newNode->previous = NULL;
		current = *list;
		prev = NULL;
		
		while(current != NULL) {		
			prev = current;
			current = current->nextNode;
		}
					
		if(prev == NULL) {
			*list = newNode;
		} else {
			prev->nextNode = newNode;
			newNode->previous = prev;
		}
	} else {
		
		char errorMessage[200];
		sprintf(errorMessage, "CCCombo BUG-REPORT:\n CCList Exception allocating new node\nFILE: %s {%d}", __FILE__, __LINE__);
		perror(errorMessage);
	 	return 0;
	}
	
	return 1;
}


/*
 *@Description: cria uma lista inicializada com varios elementos; OBS: NULL deve ser colocado no final como sinalizador de que o ultimo elemento foi inserido
 *@Params: -list => ponteiro para a lista, inicialmente vazia(NULL); - ... => lista de elementos separados por virgula, para inicializar a lista
 *@Return: retorna 1 se a operacao foi concluida com sucesso, 0 se nao for concluida, normalmente porque nao foi possivel alocar memoria para o elemento  
 */
extern int CCListInitWith(CCList **list, ...) {
	va_list listArgs;
	CCNode *newNode;
	CCNode *prev;
	CCNode *current;
	void *content;
	va_start(listArgs, list);
	while((content = (va_arg(listArgs, void *))) != NULL) {
		newNode = malloc(sizeof(CCNode));
		newNode->data  = content;
		newNode->nextNode = NULL;
		newNode->previous = NULL;
		if(newNode != NULL) {
			current = *list;
			prev = NULL;
			
			while(current != NULL) {
				prev = current;
				current = current->nextNode;
			}
			
			if(prev == NULL) {
				*list = newNode;
			} else {
				prev->nextNode = newNode;
				newNode->previous = prev;
			}
		} else {
			char errorMessage[200];
			sprintf(errorMessage, "CCCombo BUG-REPORT:\n CCList Exception allocating new node\nFILE: %s {%d}", __FILE__, __LINE__);
			perror(errorMessage);
			return 0;
		}
	}
	va_end(listArgs);
	return 1;
}


/*
 *@Description: remove um elemento da lista baseando-se no index informado
 *@Params: -list => ponteiro do primeiro elemento da lista ; -index => a posicao do elemento a ser eliminado (comecando de ZERO)
 *@Return: retorna 1 se a operacao foi concluida com sucesso, 0 se nao for concluida, que pode ocorrer no caso da lista estar vazia ou o elemento nao ser encontrado
 */

extern int CCListRemoveAtIndex(CCList **list, int index) {
	int posCounter = 0;
	if(!CCListIsEmpty(*list)) {
		
		if(index == 0) {
			CCNode *temp = *list;
			*list = (*list)->nextNode;
			CC_FREE_MEMORY(temp);
			return 1;
		}
		CCNode *current = *list;
		CCNode *prev = NULL;
		while(current != NULL && posCounter != index) {
			prev = current;
			posCounter++;
			current = current->nextNode;
		}	
		
		
		if(current != NULL) {
			prev->nextNode = current->nextNode;
			CC_FREE_MEMORY(current);
			return 1;
		}
	}
	return 0;
}

extern int CCListRemove(CCList **list, void *element, int (*comparator)(void *, void *)) {
	if(CCListIsEmpty(*list))
		return 0;
		
	int pos = 0;
	CCNode *current = *list;
	CCNode *prev = NULL;
	while(current != NULL && (comparator(current->data, element)) != 0) {
		pos++;
		prev = current;
		current = current->nextNode;
	}
	
	if(pos == 0) {
		CCNode *temp = *list;
		*list = (*list)->nextNode;
		CC_FREE_MEMORY(temp);
		return 1;
	}
	if(current == NULL) return 0;
	else { 
		prev->nextNode = current->nextNode;
		CC_FREE_MEMORY(current);
	}
	
	return 1;
	
}

/*
 *@Description: verifica se lista esta vazia
 *@Params: -list => ponteiro para o primeiro elemento da lista
 *@Return: 1 se a lista estiver vazia, 0 caso contrario
 */

extern int CCListIsEmpty(CCList *list) {
	return list == NULL;
}


/*
 *@Description: permite listar todos os elementos de uma lista informando a ordem em que devem ser impressos(asc ou desc) e o ponteiro pra uma funcao que faz o trabalho final de mostrar
 *@Params: -list => ponteiro para o primeiro elemento da lista ; -listOrder => constante pre-definida que informa a ordem (LIST_DEFAULT_ORDER, LIST_REVERSE_ORDER) ; -showData => funcao para qual serao passados os elementos da lista a cada iteracao, deve imprmir devimdamento dos dados na tela
 */

extern void CCListShow(CCList *list, ListOrderType listOrder, void (*showData)(void *)) {
	if(listOrder == LIST_DEFAULT_ORDER) {
		while(list != NULL) {
			showData(list->data);
			list = list->nextNode;
		}
	} else {
		if(list == NULL)
			return;
		CCListShow(list->nextNode, LIST_REVERSE_ORDER, showData);
		showData(list->data);
	}
}
/*
 *@Description: calcula e retorna o quantidade de elementos presente na lista
 *@Params: -list => ponteiro para o primeiro elemento da lista
 *@Return: a quantidade de elementos da lista
 */

extern int CCListLength(CCList *list) {
	int size = 0;
	if(list == NULL)
		return 0;
	while(list != NULL) {
		list = list->nextNode;
		size++;
	}
	
	return size;
}

/*
 *@Description: permite esvaziar uma lista, liberando a memoria ocupada por todos elementos da lista OBS:  a varial global deve estar como DYNAMIC_OBJECTS, caso constrario a funcao nao altera nada na lista
 *@Params: -list => ponteiro para o primeiro elemento da lista
 *@Return: 1 se a opercao for bem sucedida, 0 caso contrario
 */

extern int CCListFreeMemory(CCList **list) {
	if(objectMemoryType == STATIC_OBJECTS) return 0;
	CCNode *current = *list;
	CCNode *temp;
	while(current != NULL) {
		temp = current;
		current = current->nextNode;
		free(temp);
	}
	
	*list = NULL;
	
	return 1;
}

// collections private methods;
// criar formatadores de saida usando todos recursos do printf, usar *.* para calcular automaticamento cumprimeto do campo e quant de char a mostrar
// exmplo printf("%*.*s", strlenth("HellWorld") + 2, 4 "Hello World")