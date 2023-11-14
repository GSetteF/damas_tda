//bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>

//ainda não foi utilizada(talvez possa retirar)
#include <string.h>
//biblioteca para mudar a lingua
#include <locale.h>

//definindo as características das nossas pecas (char tipo, int jogador)
typedef struct Pecas{
	
	char tipo;
	int jogador;
	
}Pecas;


//pode ignorar, ela só serve para mostrar os tipos de pecas e suas caracteristicas
void exibir_pecas(Pecas P1,Pecas P2,Pecas D1,Pecas D2){
	printf("P1 é uma peça do tipo: %c, do jogador %d \n", P1.tipo, P1.jogador);
	printf("P2 é uma peça do tipo: %c, do jogador %d \n", P2.tipo, P2.jogador);
	printf("D1 é uma peça do tipo: %c, do jogador %d \n", D1.tipo, D1.jogador);
	printf("D2 é uma peça do tipo: %c, do jogador %d \n", D2.tipo, D2.jogador);
}

void exibir_matriz(Pecas matriz[8][8]) {
	int i = 0, j = 0;
	puts("    [00][11][22][33][44][55][66][77]");
    for (i = 0; i < 8; i++) {
    	printf("[%d%d]", i, i);
        for (j = 0; j < 8; j++) {
        	if ((matriz[i][j].tipo == 'P' || matriz[i][j].tipo == 'D') && (matriz[i][j].jogador == 1 || matriz[i][j].jogador == 2)){
        	
            printf("[%c%d]", matriz[i][j].tipo, matriz[i][j].jogador);}
            else{
            	printf("    ");
            }
        }
        printf("\n");
    }
}

void menu(){
	int op = 0;
	puts("Bem-vindo(a) ao nosso jogo de damas, \n");
	puts("Para Jogar uma partida, digite 1; \n");
	puts("Para consultar o registro de partidas, digite 2; \n");
	puts("Para acessar as instruções, digite 3. \n");
	puts("Para sair, digite 4. \n");
	scanf("%d", &op);
	
	switch(op){
		case 1:
			iniciar_partida();
		case 2:
			exibir_registros();
			break;
		case 3:
			exibir_instrucoes();
			break;
		case 4:
			break;
		default:
			puts("Insira um comando válido!");
			break;
	}
}

void iniciar_partida(){
	puts("Comandos para iniciar a partida, etc");
}	

void exibir_registros(){
	puts("Comandos para exibir registros de partidas passadas");
}

void exibir_instrucoes(){
	puts("exibir as instruções do jogo");
}

int verificar_jogada (int jogador, int i_origem, int j_origem, int i_destino, int j_destino, Pecas tabuleiro[8][8], Pecas vazio){
	
	int distancia_i = abs(i_destino-i_origem);
	int distancia_j = abs(j_destino-j_origem);
	
	//verificando se a peca movida é do tipo P
	if(tabuleiro[i_origem][j_origem].tipo == 'P'){
	
		if(tabuleiro[i_origem][j_origem].jogador != jogador){
			puts("Movimento inválido! você tentou mover a peça de outro jogador. \n");
			return(0);
		}
		else if(tabuleiro[i_destino][j_destino].jogador != 0){
			puts("Movimento inválido! você tentou mover a peça para um espaço já ocupado. \n");
			return(0);
		}
		else if((i_origem == i_destino)||(j_origem == j_destino)){
			puts("Movimento inválido! você tentou mover a peça em uma direção não permitida. \n");
			return(0);
		}
		else if((jogador == 1 && i_origem <= i_destino)||(jogador == 2 && i_origem >= i_destino)){
			puts("Movimento inválido! você tentou mover a peça na direção contrária. \n");
			return(0);
		}
		else if(j_destino > 7 || j_destino < 0 || i_destino > 7 || i_destino < 0){
			puts("Movimento inválido! você tentou mover a peça para uma posição que não existe. \n");
			return(0);
			}
		else if(distancia_i > 2 || distancia_j > 2 || distancia_i == 2 && distancia_j == 1 || distancia_i == 1 && distancia_j == 2){
			puts("Movimento inválido! você tentou mover a peça para uma posição muito distante. \n");
			return(0);
		}
		else if (distancia_i == 2){ //capturando uma peca
			//posicao da peca capturada
			int i_peca_capturada = (i_origem+i_destino)/2;
			int j_peca_capturada = (j_origem+j_destino)/2;
			tabuleiro[i_peca_capturada][j_peca_capturada] = vazio;
			tabuleiro[i_destino][j_destino] = tabuleiro[i_origem][j_origem];
			tabuleiro[i_origem][j_origem] = vazio;
			return(1);
		}
		else{ //movendo uma peca para um espaco vazio
			tabuleiro[i_destino][j_destino] = tabuleiro[i_origem][j_origem];
			tabuleiro[i_origem][j_origem] = vazio;
			return(1);
		}
	}
	else if(tabuleiro[i_origem][j_origem].tipo == 'D'){
		puts("verificar movimento de damas, retornar 1 caso válido, retornar 0 caso inválido. Se atentar a implementar a captura");
	}
}

int main(int argc, char *argv[]) {
	//Comando para mudar a lingua
	setlocale(LC_ALL, "Portuguese");
	
	//Definindo nossas pecas
	Pecas P1, P2, D1, D2, vazio;
	
	P1.tipo = 'P';
	P1.jogador = 1;
	D1.tipo = 'D';
	D1.jogador = 1;
	P2.tipo = 'P';
	P2.jogador = 2;
	D2.tipo = 'D';
	D2.jogador = 2;
	vazio.tipo = ' ';
	vazio.jogador = 0; 
	
	//criando o tabuleiro
	Pecas tabuleiro[8][8];
	
	//populando o tabuleiro
	
	//variáveis para percorrer linhas e colunas (linha percorre horizontalmente e coluna verticalmente)
	int linha = 0;
	int coluna = 0;
	
	//populando o tabuleiro com as pecas pretas (jogador 2) e limpando os outros espacos
	
	for (coluna = 1; coluna < 8;coluna++){
		if (coluna%2 != 0){
		
		tabuleiro[0][coluna] = P2;
		tabuleiro[2][coluna] = P2;
		}
		else{
			tabuleiro[0][coluna] = vazio;
			tabuleiro[2][coluna] = vazio;
		}
	}
	
	for (coluna = 0; coluna < 8;coluna+=2){
		if (coluna%2 == 0){
		
		tabuleiro[1][coluna] = P2;
		}
		else{
			tabuleiro[1][coluna] = vazio;
		}
	}
	
	//preenchendo o meio do tabuleiro com o elemento vazio
	for (coluna = 0; coluna < 8; coluna++){
		tabuleiro[3][coluna] = vazio;
		tabuleiro[4][coluna] = vazio;
	}
	
	//preenchendo o tabuleiro com as pecas brancas (jogador 1) e limpando os outros espacos
	for (coluna = 0; coluna < 8;coluna++){
		if (coluna%2 == 0){
		
		tabuleiro[5][coluna] = P1;
		tabuleiro[7][coluna] = P1;
		}
		else{
			tabuleiro[5][coluna] = vazio;
			tabuleiro[7][coluna] = vazio;
		}
	}
	
	for (coluna = 1; coluna < 8;coluna+=2){
		if (coluna%2 != 0){
		
		tabuleiro[6][coluna] = P1;
		}
		else{
			tabuleiro[6][coluna] = vazio;
		}
	}
	
	
	char condicao_de_parada;
	int jogador_atual = 1;
	int i_origem = 0, j_origem = 0, i_destino = 0, j_destino = 0;
	int ver_jogada = 0;
	
	//Depois, melhor mudar essa verificacao por uma funcao que verifica
	while (condicao_de_parada != 'V' || condicao_de_parada != 'E'){
		puts("Tabuleiro atual: \n");
		exibir_matriz(tabuleiro);
		puts("Escreva a posição da peça que deseja mover e então a posição para que deseja movê-la separados tudo por espaço.");
		scanf("%d %d %d %d", &i_origem, &j_origem, &i_destino, &j_destino);
		ver_jogada = verificar_jogada(jogador_atual, i_origem, j_origem, i_destino, j_destino, tabuleiro, vazio);
		if (ver_jogada == 1){
			if (jogador_atual == 1){
				jogador_atual = 2;
			}
			else{
				jogador_atual = 1;
			}
		}
	}
	
	
	
	
	
	return 0;
}
