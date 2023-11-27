//Trabalho unidade 2 tda, projetos de damas
//professor: Leonardo
//Grupo:
//Gabriel Evangelista
//Gabriel Sette
//Matheus Sette
//Sidney Braga

//bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>




//ainda não foi utilizada(talvez possa retirar)
#include <string.h>
//biblioteca para mudar a lingua
#include <locale.h>




//definindo o placar inicial
int placar_player_1 = 0;
int placar_player_2 = 0;




//definindo as características das nossas pecas (char tipo, int jogador)
typedef struct Pecas{
        
        char tipo;
        int jogador;
        
}Pecas;

typedef struct Diagonal{
        
        char tipo;
        int i;
        int j;
        
}Diagonal;


void exibir_matriz(Pecas matriz[8][8]) {
        int i = 0, j = 0;
        puts("    [00][01][02][03][04][05][06][07]");
    for (i = 0; i < 8; i++) {
            printf("[0%d]", i, i);
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
                        if (tabuleiro[i_peca_capturada][j_peca_capturada].jogador != 0 && tabuleiro[i_peca_capturada][j_peca_capturada].jogador != jogador){
                                tabuleiro[i_peca_capturada][j_peca_capturada] = vazio;
                                tabuleiro[i_destino][j_destino] = tabuleiro[i_origem][j_origem];
                                tabuleiro[i_origem][j_origem] = vazio;
                                if (jogador == 1){
                                        placar_player_1 += 1;
                                        printf("\nO player 1 capturou %d peça(s)\n\n", placar_player_1);
                                        if (i_destino == 0){
                                                tabuleiro[i_destino][j_destino].tipo = 'D';
                                        }
                                }else if (jogador == 2){
                                        placar_player_2 += 1;
                                        printf("\nO player 2 capturou %d peça(s)\n\n", placar_player_2);
                                        if (i_destino == 7){
                                                tabuleiro[i_destino][j_destino].tipo = 'D';
                                        }
                                }
                                return(1);
                        }else{
                                printf("\nMovimento inválido. Você não pode caturar uma peça.\n\n");
                        }
                        
                }
                else{ //movendo uma peca para um espaco vazio
                                tabuleiro[i_destino][j_destino] = tabuleiro[i_origem][j_origem];
                        tabuleiro[i_origem][j_origem] = vazio;
                        if (jogador == 1 && i_destino == 0){
                                tabuleiro[i_destino][j_destino].tipo = 'D';
                        }else if (jogador == 2 && i_destino == 7){
                                tabuleiro[i_destino][j_destino].tipo = 'D';
                        }
                        
                        return(1);
                }
        }
        else if(tabuleiro[i_origem][j_origem].tipo == 'D'){
                puts("verificar movimento de damas, retornar 1 caso válido, retornar 0 caso inválido. Se atentar a implementar a captura");
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
                else if(j_destino > 7 || j_destino < 0 || i_destino > 7 || i_destino < 0){
                        puts("Movimento inválido! você tentou mover a peça para uma posição que não existe. \n");
                        return(0);
                }
                else if (distancia_i == 1){ //adando uma casa	
                	tabuleiro[i_destino][j_destino] = tabuleiro[i_origem][j_origem];
                	tabuleiro[i_origem][j_origem] = vazio;
                    return(1); 
                }
                else{
                	Diagonal diagonal[10]; //diagonal que a peca deseja percorrer
                	int indice = 0;
                	int i_diag = i_origem, j_diag = j_origem;
                	char dif_i = '-', dif_j = '-';
                	
                	//determinando o sentido e posicao inicial da diagonal
                	if (i_destino > i_origem){
                		dif_i = '+';
						i_diag+=1;}
                	else { 
						i_diag -=1;}
					if (j_destino > j_origem){
						dif_j = '+';
                		j_diag+=1;}
                	else { 
						j_diag -=1;}
					
					//adicionando itens no vetor diagonal
					while(i_destino != i_diag){
						//printf("casa sendo acessada: [%d][%d]  conteudo: %c \n", i_diag, j_diag, tabuleiro[i_diag][j_diag].tipo);
						
						//caso a peca seja do mesmo jogador
						if(tabuleiro[i_diag][j_diag].jogador == jogador){
							diagonal[indice].tipo = 'A';
							diagonal[indice].i = i_diag;
							diagonal[indice].j = j_diag;
						}
						//caso a peca seja do outro jogador
						else if(tabuleiro[i_diag][j_diag].tipo == 'P' || tabuleiro[i_diag][j_diag].tipo == 'D'){
							diagonal[indice].tipo = 'P';
							diagonal[indice].i = i_diag;
							diagonal[indice].j = j_diag;
						} else{ //caso o espaco seja vazio
							diagonal[indice].tipo = 'V';
							diagonal[indice].i = i_diag;
							diagonal[indice].j = j_diag;
						}
						
					
						indice+=1;
					
						if(dif_i == '+'){
							i_diag += 1;
						} else{ i_diag -= 1;}
						if(dif_j == '+'){
							j_diag += 1;
						} else{ j_diag -= 1;}	
					}
					//criando um limite da diagonal
					diagonal[indice].tipo = 'F';
					diagonal[indice].i = i_diag;
					diagonal[indice].j = j_diag;
					
					/* for(indice = 0; indice < 10; indice++){
						printf("Conteudo : %c, i: %d, j: %d \n", diagonal[indice].tipo, diagonal[indice].i, diagonal[indice].j);
					} */
					
					indice = 0;
					while(diagonal[indice].tipo != 'F'){
						if(diagonal[indice].tipo == 'P' && diagonal[indice+1].tipo == 'P' || diagonal[indice].tipo == 'A'|| diagonal[indice+1].tipo == 'A'){
							puts("Movimento inválido!");
							return(0);
						}
						else if(diagonal[indice].tipo == 'P'){
							tabuleiro[diagonal[indice+1].i][diagonal[indice+1].j] = tabuleiro[i_origem][j_origem];
                			tabuleiro[i_origem][j_origem] = vazio;
                			tabuleiro[diagonal[indice].i][diagonal[indice].j] = vazio;
                    		return(1); 
						}
						indice+=1;
					}
					//mover a peca
					tabuleiro[i_destino][j_destino] = tabuleiro[i_origem][j_origem];
                	tabuleiro[i_origem][j_origem] = vazio;
                	
                	return(1);
                	
                	
                }
        }
}


void preencher_tabuleiro(Pecas tabuleiro[8][8] , Pecas P1, Pecas P2, Pecas vazio) {
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
}


void jogar_partida(){
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
        preencher_tabuleiro(tabuleiro, P1, P2, vazio);
        
        char condicao_de_parada;
        int jogador_atual = 1;
        int i_origem = 0, j_origem = 0, i_destino = 0, j_destino = 0;
        int ver_jogada = 0;
        int ver_fim = 0;
        
        while (ver_fim == 0){
                puts("Tabuleiro atual: \n");
                exibir_matriz(tabuleiro);
                puts("\nEscreva a posição da peça que deseja mover e então a posição para que deseja movê-la separados tudo por espaço.");
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
                ver_fim = verificar_fim(tabuleiro, P1, P2, vazio);
        }
        
        if (ver_fim == 1){
        	exibir_matriz(tabuleiro);
            puts("Jogador 1 Venceu!");
        }
        else if (ver_fim == 2){
        	exibir_matriz(tabuleiro);
            puts("Jogador 2 Venceu!");
        }
        else if (ver_fim == 3){
        	exibir_matriz(tabuleiro);
            puts("O jogo terminou em empate :(");
        }
}


void exibir_menu_principal(){
        puts("+++++++++++++++++++++++++++++++++++++++++++");
        puts("+++++Sejam Bem vindos ao jogo de damas+++++");
        puts("+++++++++++++++++++++++++++++++++++++++++++\n");
        puts("Selecione qual opção deseja realizar:\n");
        puts("Pressione '1' para jogar");
        puts("Pressione '2' para ver as instruções");
        puts("Pressione '3' para ver os créditos");
}


void exibir_instrucoes(){
        puts("\n\n");
        puts("+++++++++++++++++++++++++++++++++++++++++++");
        puts("+++++++++++++++Instruções++++++++++++++++++");
        puts("+++++++++++++++++++++++++++++++++++++++++++\n");
        puts("> Objetivo: capturar todas as peças do jogador adversário\n");
        puts("> Inicio de partida: o jogador 1 sempre será o primeiro a começar seguindo pelo jogador 2,\n se manterá esse mesmo esquema até o final da partida\n");
        puts("> Como jogar: para fazer a movimentação de uma peça, você deverá inserir qual é a casa de origem da sua peça \n(linha de origem e coluna de origem) depois a casa de destino (linha de destino e coluna de destino)\n\n");
                                
}


void exibir_creditos(){
        puts("\n\n");
        puts("+++++++++++++++++++++++++++++++++++++++++++");        
        puts("++++++++++++++++++Créditos+++++++++++++++++");
        puts("+++++++++++++++++++++++++++++++++++++++++++");
        puts("Todos que participaram na criação do jogo: \n");
        puts("Matheus Sette");
        puts("Gabriel Sette");
        puts("Sidney Braga");
        puts("Gabriel Evangelista\n\n");
                                
        puts("                ___");
        puts("            ,-'"   "`-.");
        puts("          ,'_          `.  ");
        puts("         / / \  ,-       \ ");
        puts("    __   | \_0 ---        |");
        puts("   /  |  |                |");
        puts("   \  \  `--.______,-/    |");
        puts(" ___)  \  ,--""    ,/     |");
        puts("/    _  \ \-_____,-      / ");
        puts("\__-/ \  | `.          ,'  ");
        puts("  \___/ <    ?--------'    ");
        puts("   \__/\ |             ");
        puts("    \__//\n\n");        
}

int verificar_fim(Pecas tabuleiro[8][8] , Pecas P1, Pecas P2, Pecas vazio){
	int tipo_fim = 0;
	int i = 0, j = 0;
	int cont_1 = 0, cont_2 = 0;
	
	
	//contar as pecas restantes
	for(i = 0; i < 8;i++){
		for(j = 0; j < 8;j++){
			if (tabuleiro[i][j].jogador == 1){
				cont_1+=1;
			}
			else if (tabuleiro[i][j].jogador == 2){
				cont_2+=1;
			}
		}
	}
	//jogador 2 ganhou
	if (cont_1 == 0){
		return(2);
	}
	//jogador 1 ganhou
	else if (cont_2 == 0){
		return(1);
	}
	//empate(1 peca de cada um restante)
	else if (cont_1 == 1 && cont_2 == 1){
		return(3);
	}
	return(0);
}

int main(int argc, char *argv[]) {
    //Comando para mudar a lingua
    setlocale(LC_ALL, "Portuguese");
        
    	int op_menu = 0; //variavel responsavel pela escolha das opcoes no menu principal
        char op_loop; //variavel principal pela repeticao do codigo
        
        do{
                //menu principal
                exibir_menu_principal();
                scanf("%d", &op_menu);
                
                switch(op_menu){
                        case 1:{
                                //inicializar jogo aqui
                                jogar_partida();
                                break;
                        }
                        case 2:{
                                //intrucoes de como jogar
                                exibir_instrucoes();
                                break;
                        }
                        case 3:{
                                //creditos do grupo
                                exibir_creditos();
                                break;
                        }
                        default:{
                                //caso o usuario nao insera uma opcao valida
                                
                                puts("\nOpção Inválida. Tente novamente!! ;-;");
                                printf("\n\n\n");
                                
                                break;
                        }
                }
                
                /*acao depois que passar do switch case
                pergunta ao usuario se ele quer voltar ao menu*/
                
                printf("Deseja voltar ao menu principal?\n");
                printf("Pressione 's' para sim  ||  Pressione 'n' para não\n");
                scanf("%s", &op_loop);
                
                /*if/else para quebrar o loop caso o usuario nao queira continuar
                Obs: talvez isso possa ficar um pouco redundante ja
                que essa condicao esta dentro do while*/
                if(op_loop == 's' || op_loop == 'S'){
                        puts("\n\n\n\n\n");
                        continue;
                
                } else{
                        puts("\n\nObrigado por jogar!!");
                        puts("Volte sempre!! :)");
                        
                        break;
                }
                        
        //se o usuario digitar 's' ou 'S' o loop se repetira
        } while(op_loop == 's' || op_loop == 'S');
        
        return 0;
}
