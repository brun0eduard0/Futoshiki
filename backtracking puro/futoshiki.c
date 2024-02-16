/******************************************
UNIVERSIDADE FEDERAL DO AMAZONAS
BRUNO EDUARDO GOMES BARRETO
21050103
Implementação da versão backtracking pura para solver o futoshiki
******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int value, tam;
int cont = 0;
void print(char **mat){
	int i=0,j=0;
	for (i=0; i<tam; i++) {
		for (j=0; j<tam; j++) {
			printf("%c", mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/* parâmetros: n (tamanho da matriz de) 
 * função responsável por: abrir o arquivo e tratar as instâncias a serem testadas	*/
char **readmat(int *n){
	FILE *fp;
	char *line, nome[120];
	int i, j, k;
	char **mat;
	printf("Digite o nome do arquivo: ");
	scanf("%s",nome);
	fp = fopen(nome,"r");
	if(fp == NULL){
		printf("Erro ao tentar abrir o arquivo\n");
		exit(1);
	}
	if(fgets(nome, 100, fp) == NULL){
		printf("Formato de arquivo é inválido\n");
		fclose(fp);
		exit(1);
	}
	if(sscanf(nome,"%d",n)!=1){
		printf("Erro em parâmetros de arquivo\n");
		fclose(fp);
		exit(1);
	}
	value = (*n);
	//tratamento da instância
	(*n)=(((*n)*2)-1);	//aumento da matriz para caber as retrições (><^v) 3=>5 4=>7
	tam = (*n);
	mat=(char**)calloc((*n), (sizeof(char*)));
	for(i=0;i<=(*n);i++){
		mat[i]=(char*)calloc((*n), (sizeof(char)));
	}
	line=(char*)malloc(2*(*n)*sizeof(char));
	i=0;
	while(i <= (*n) && fgets(line, 2*(*n)+2, fp)!=NULL){
		j=0;
		k=0;
		while(j <= 2*(*n)){
			if(line[j]!=' '){
				mat[i][k]=line[j];
				k++;
			}  
			j++;
		}
		i++;
	} 
	return mat;
}

int isSolution(char **mat) {
	int i, j, k;
	for(i = 0; i < tam; i = i + 2){
		for(j = 0; j < tam; j = j + 2){
			for (k = j + 2; k < tam; k = k + 2){
				if(mat[i][j] == mat[i][k]){	// checagem para verificar se há repetições na linha
					return 0;
				}
				if(mat[j][i] == mat[k][i]){	// checagem para verificar se há repetições na coluna
					return 0;
				}
			}
			if(mat[i][j]=='0'){	// checagem para verificar se há valores nulos
				return 0;
			}
		}
	}
	// checagem em relação às regras do jogo (><^v)	
	for(i=0; i < tam; i++){
		for(j=0; j < tam; j++){
			if(mat[i][j]=='<'){
				if(mat[i][j-1] >= mat[i][j+1]){
					return 0;
				}
			}
			else if(mat[i][j]=='>'){
				if(mat[i][j-1] <= mat[i][j+1]){
					return 0;
				}
			}   
			else if(mat[i][j]=='^'){
				if(mat[i-1][j] >= mat[i+1][j]){
					return 0;
				}
			}
			else if(mat[i][j]=='v'){
				if(mat[i-1][j] <= mat[i+1][j]){
					return 0;
				}
			}
		}
	}
	return 1;	// É um resultado
}

int isValid(char **mat,int row,int col, int weight){
	int i,j;
	char peso = weight + '0';
	for(i=0; i<tam ;i+=2){
		//  checam se o valor existe na linha
		if(mat[row][i]==peso){
			return 0;
		}
		//  checam se o valor existe na coluna
		if(mat[i][col]==peso){
			return 0;
		}
	}
	// checagem em relação às regras do jogo (><^v)	
	if(row == 0){
		if(col == 0){
			if(mat[row][col+1]=='<'){
				if(mat[row][col+2]=='0'){
					return 1;
				}
				if(peso >= mat[row][col+2]){
					return 0;
				}
			}
			if(mat[row][col+1]=='>'){
				if(peso <= mat[row][col+2]){
					return 0;
				}
			}
			if(mat[row+1][col]=='^'){
				if(mat[row+2][col]=='0'){
					return 1;
				}
				if(mat[row+2][col] <= peso){
					return 0;
				}
			}
			if(mat[row+1][col]=='v'){
				if(mat[row+2][row] >= peso){
					return 0;
				}
			}
		}
		else if((0 < col) && (col < (tam-1))){
			if(mat[row][col+1]=='<'){
				if(mat[row][col+2]=='0'){
					return 1;
				}
				if(peso >= mat[row][col+2]){
					return 0;
				}
			}
			if(mat[row][col+1]=='>'){
				if(peso <= mat[row][col+2]){
							return 0;
				}
			}
			if(mat[row+1][col]=='^'){
				if(mat[row+2][col]=='0'){
					return 1;
				}
				if(mat[row+2][col] <= peso){
					return 0;
				}
			}
			if(mat[row+1][col]=='v'){
				if(mat[row+2][col] >= peso){
					return 0;
				}
			}			
			if(mat[row][col-1]=='<'){
				if(mat[row][col-2] >= peso){
					return 0;
				}
			}
			if(mat[row][col-1]=='>'){
				if(mat[row][col-2] <= peso){
					return 0;
				}
			}
		}
		else{	// col == (tam-1) ultima coluna
			if(mat[row+1][col]=='^'){
				if(mat[row+2][col]=='0'){
					return 1;
				}
				if(mat[row+2][col] <= peso){
					return 0;
				}
			}
			if(mat[row+1][col]=='v'){
				if(mat[row+2][col] >= peso){
					return 0;
				}
			}			
			if(mat[row][col-1]=='<'){
				if(mat[row][col-2] >= peso){
					return 0;
				}
			}
			if(mat[row][col-1]=='>'){
				if(mat[row][col-2] <= peso){
					return 0;
				}
			}
		}	
	}
	else if((0 < row) && (row < (tam-1))){
		if(col ==0){
			if(mat[row][col+1]=='<'){
				if(mat[row][col+2]=='0'){
					return 1;
				}
				if(peso >= mat[row][col+2]){
					return 0;
				}
			}
			if(mat[row][col+1]=='>'){
				if(peso <= mat[row][col+2]){
					return 0;
				}
			}
			if(mat[row+1][col]=='^'){
				if(mat[row][col+2]=='0'){
					return 1;
				}
				if(mat[row+2][col] <= peso){
					return 0;
				}
			}
			if(mat[row-1][col]=='^'){
				if(peso <= mat[row-2][col]){
					return 0;
				}
			}
			if(mat[row+1][col]=='v'){
				if(mat[row+2][col] >= peso){
					return 0;
				}
			}
			if(mat[row-1][col]=='v'){
				if(peso >= mat[row-2][col]){
					return 0;
				}
			}		
		}
		else if((0 < col) && (col < (tam-1))){
			if(mat[row][col-1]=='<'){
				if(mat[row][col-2] >= peso){
					return 0;
				}
			}			
			if(mat[row][col-1]=='>'){
				if(mat[row][col-2] <= peso){
					return 0;
				}
			}
			if(mat[row][col+1]=='<'){
				if(mat[row][col+2]=='0'){
					return 1;
				}
				if(peso >= mat[row][col+2]){
					return 0;
				}
			}
			if(mat[row][col+1]=='>'){
				if(peso <= mat[row][col+2]){
					return 0;
				}
			}
			if(mat[row+1][col]=='^'){			//trocar
				if(mat[row+2][col]=='0'){
					return 1;
				}
				if(mat[row+2][col] <= peso){
					return 0;
				}
			}
			if(mat[row-1][col]=='^'){			//trocar
				if(peso <= mat[row-2][col]){
					return 0;
				}
			}	
			if(mat[row+1][col]=='v'){
				if(mat[row+2][col] >= peso){
					return 0;
				}
			}
			if(mat[row-1][col]=='v'){
				if(peso >= mat[row-2][col]){
					return 0;
				}
			}			
		}
		else{	// col == (tam-1) ultima coluna
			if(mat[row][col-1]=='<'){
				if(mat[row][col-2] >= peso){
					return 0;
				}
			}			
			if(mat[row][col-1]=='>'){
				if(mat[row][col-2] <= peso){
					return 0;
				}
			}
			if(mat[row+1][col]=='^'){
				if(mat[row+2][col]=='0'){
					return 1;
				}
				if(mat[row+2][col] <= peso){
					return 0;
				}
			}
			if(mat[row-1][col]=='^'){
				if(peso <= mat[row-2][col]){
					return 0;
				}
			}	
			if(mat[row+1][col]=='v'){
				if(mat[row+2][col] >= peso){
					return 0;
				}
			}
			if(mat[row-1][col]=='v'){
				if(peso >= mat[row-2][col]){
					return 0;
				}
			}
		}
	}
	else{	// row == (tam - 1) ultima linha
		if(col ==0){
			if(mat[row][col+1]=='<'){
				if(mat[row][col+2]=='0'){
					return 1;
				}
				if(peso >= mat[row][col+2]){
					return 0;
				}
			}
			if(mat[row][col+1]=='>'){
				if(peso <= mat[row][col+2]){
					return 0;
				}
			}
			if(mat[row-1][col]=='^'){
				if(peso <= mat[row-2][col]){
					return 0;
				}
			}	
			if(mat[row-1][col]=='v'){
				if(peso >= mat[row-2][col]){
					return 0;
				}
			}		
		}
		else if((0 < col) && (col < (tam-1))){
			if(mat[row][col-1]=='<'){
				if(mat[row][col-2] >= peso){
					return 0;
				}
			}			
			if(mat[row][col-1]=='>'){
				if(mat[row][col-2] <= peso){
					return 0;
				}
			}
			if(mat[row][col+1]=='<'){
				if(mat[row][col+2]=='0'){
					return 1;
				}
				if(peso >= mat[row][col+2]){
					return 0;
				}
			}
			if(mat[row][col+1]=='>'){
				if(peso <= mat[row][col+2]){
					return 0;
				}
			}
			if(mat[row-1][col]=='^'){
				if(peso <= mat[row-2][col]){
					return 0;
				}
			}	
			if(mat[row-1][col]=='v'){
				if(peso >= mat[row-2][col]){
					return 0;
				}
			}			
		}
		else{	// col == (tam-1) ultima coluna
			if(mat[row][col-1]=='<'){
				if(mat[row][col-2] >= peso){
					return 0;
				}
			}			
			if(mat[row][col-1]=='>'){
				if(mat[row][col-2] <= peso){
					return 0;
				}
			}
			if(mat[row-1][col]=='^'){
				if(peso <= mat[row-2][col]){
					return 0;
				}
			}	
			if(mat[row-1][col]=='v'){
				if(peso >= mat[row-2][col]){
					return 0;
				}
			}
		}		
	}	                
	return 1;
}

void solveFutoshiki(char **mat,int row, int col){
	int i;
	if(row==(tam-1)){	// verificação se é uma instância valida
		if(col==(tam-1)){
			if(isSolution(mat)==1){
				cont++;
				printf("Resultado - %d\n", cont);
				print(mat);
				return;
			}
		}
	}
	else if(row == (tam+1)){
		if(isSolution(mat) == 1){
			cont++;
			printf("Resultado - %d\n", cont);
			print(mat);
		}
		return;
	}
	if(mat[row][col]!='0'){			// avança para o próximo quadrante caso hava alguma valor na posição.
		if(col==(tam-1)){
			solveFutoshiki(mat,(row+2),0);
		}
		else{
			solveFutoshiki(mat,row,col+2);	
		}
	}
	else{
		for(i=1;i<=value;i++){
			//if( isValid(mat,row,col,i) ){	// verifica se é uma entrada válida
			mat[row][col]=i+'0';
			if(col < tam-1){
				solveFutoshiki(mat,row,col+2);
			}
			if(col==tam-1){
				solveFutoshiki(mat,row+2,0);
			}
			mat[row][col]='0';
		}
	}
}


int main(int argc, char *argv[]){
	char **mat;
	int n;
	mat = readmat(&n);
	printf("entrada\n\n");
	print(mat);
	solveFutoshiki(mat,0,0);
	return 0;
}
