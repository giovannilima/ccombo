/*
 *@Author: Giovanni Lima
 *@Created-At: 10 - Jundo de 2011
 *@Last-Modif: 10 - Junho de 2011
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



/*
 *@Description: funcao que permite separar uma string em tokens delimitados pelo caracter passado para o parametro delimiter
 *@Params: -content => a string que será fatiada em tokens ; -point => o token encontrado ; -delimiter => delimitador dos tokens
 *@Return: retorna 1 enquanto exitir tokens disponiveis e 0 quando atingir o final  
 */
char tokenBuffer[1000];
extern int CCNextToken(char *content, char **point, char delimiter) {
	static int lastIndex;
	int tokenSize  = 0;
	tokenBuffer[tokenSize++] = *(content + lastIndex); 
	while(*(content + (++lastIndex)) != '\0') {
		if(*(content + (lastIndex)) == delimiter) {
			tokenBuffer[tokenSize] = '\0';
			*point = tokenBuffer;
			++lastIndex; // aponta para o proximo caracter depois do espaco em branco
			return 1;
		}
		
		tokenBuffer[tokenSize++] = *(content + lastIndex); 
	}
	return 0;
}

/*
 *@Description: imprime a string na ordem inversa 
 *@Params: -content => a string a ser impressa  
 */

extern void CCStringReverse(char *str) {
	// OBS, reimplementar essa funcao de modos a retornar uma string na ordem inversa ou recebe 1 ponteiro ** q vai apontar p inversa
	if(*str == '\0')
		return;
	CCStringReverse(str + 1);
	putchar(*str);
}

/*
 *@Description: permite a letura de uma string apartir do teclado. Essa funcao le ateh encontrar um caracter de nova linha
 *@Params: -str => a variavel que vai armazenar o endereco para a string inserida ; -elements => a quantidade caracteres a ser lida
 *@Return: o ponteiro para o string lido
 */

extern char * CCReadString(char *str, int elements) {
	int size = 0;
	char n;
	
	// limpa o buffer
	while(getchar()!= '\n');
	
	while(((n = getchar()) != '\n') && (size < elements)) {
		str[size++] = n;
	}
	
	return str;
}


/*
 *@Description: converte a primeira ocorrencia de um double na string para double usando como delimitador de casas decimais o informado
 *@Params: -str => o string a ser convertido ; -end => apontará para o primeiro caracter após a parte convertida ; -decimalDelimiter => se informado será o delimitador de casas decimais, se for 0 entao '.' sera usado
 *@Return: o valor double convertido
 */
extern double CCStringToDouble(const char *str, char **end, char decimalDelimiter) {
	char temp[16];
	int pos = 0;
	int delimFound = 0;
	if(decimalDelimiter == 0) {
		decimalDelimiter = '.';
	}
	
	while(*str++ != '\0') {
		if(pos == 0 && decimalDelimiter == *str)
			continue;
		if(isdigit(*str)) {
			temp[pos++] = *str;
		} else if(*str == decimalDelimiter) {
			if(delimFound > 0)
				break;
			delimFound++;
			temp[pos++]  = *str;
		}
	}
	*end = ++str;
	temp[pos] = '\0';
	
	return strtod(temp, NULL);
}
