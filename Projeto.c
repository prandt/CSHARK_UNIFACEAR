/******************************************
* Autores: Richard Prandt && André Souza  *
* Matéria: Projeto Integrador I           *
* Turma: ANSI-2                           *
* Versão: 1.2.1                           *
* Instituição: Unifacaer                  *
*                                         *
*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

#define MAX_MATRIZ 5
#define MAX_VIDAS 4

// Variaveis   
char matriz[MAX_MATRIZ][MAX_MATRIZ];

int chaveX = 0,chaveY = 0;
int chave = 0;
int portaX = 0, portaY = 0;
int porta = 0;

struct Jogador{
	char nomeUsuario[20];
	char senha[99];
	int vidas;
	int pontos;	
};
struct Jogador jogador;
// Alinhas os quadros
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// Colorir
void colorir(int F, int B) {
	WORD wColor = ((B & 0x0F) << 4) + (F & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
int aleatorio(int max){
	return  ( rand() % max );	
}
void zeraMatriz(){
	int i , y;
	for(i=0; i < MAX_MATRIZ;i++){
		for(y=0; y < MAX_MATRIZ;y++){
			matriz[i][y]=' ';
		}
	}
}
// Arte e moldura padrão do software
void moldura(){
	int i = 0, y = 0;
	colorir(11,0);
	for( i = 0; i < 78; i ++ ){
		gotoxy(2+i,1);
		printf("*");
		for( y = 1; y <= 19; y++ ){
			gotoxy(2,y);
			printf("*");
			gotoxy(79,y);
			printf("*");
		}
		gotoxy(2+i,19);
		printf("*");
	}
	colorir(15,0);
}
void logo(){
	colorir(14,0);
	gotoxy(4,2);
	printf("*******  ************  ****   ****  ***********  ***********  ****    ****");
	gotoxy(4,3);
	printf("* *****  * **********  *  *   *  *  *   ***   *  * *     * *  *  *   *  *");
	gotoxy(4,4);
	printf("* *      * *           *  *   *  *  *  *   *  *  * *     * *  *  *  *  *");
	gotoxy(4,5);
	printf("* *      * **********  *  *****  *  * *     * *  * ******* *  *  * *  *");
	gotoxy(4,6);
	printf("* *      ********** *  *  *****  *  *  *****  *  * *********  *  * * *");
	gotoxy(4,7);
	printf("* *               * *  *  *   *  *  *  *   *  *  * *  * *     *  * *  *");
	gotoxy(4,8);
	printf("* *****  ********** *  *  *   *  *  *  *   *  *  * *   * *    *  *  *  *");
	gotoxy(4,9);
	printf("*******  ************  ****   ****  ****   ****  ***    ***   ****   ****");
}
// Mostra barra de progresso
void loading(){
	system("cls");
	moldura();
	logo();
	int i;
	colorir(14,0);
	gotoxy(20,14);
	printf("Carregando [");
	gotoxy(42,14);
	printf("]");
	colorir(11,0);
	gotoxy(32,14);
	for( i=0;i<=9;i++ ){
		printf("#");
		Sleep(150);		
	}
	colorir(15,0);
	system("cls");
}
void btn_EntrarCancelar(int pos){
	if(pos==0){
		gotoxy(15,15);
		printf("[ Entrar ]");
		printf("[ Cancelar ]");
	}
	else if(pos==1){
		gotoxy(15,15);
		colorir(14,4);
		printf("[ Entrar ]");
		colorir(14,0);
		printf("[ Cancelar ]");
	}
	else if(pos==2){
		gotoxy(15,15);
		colorir(14,0);
		printf("[ Entrar ]");
		colorir(14,4);
		printf("[ Cancelar ]");
	}
}
// Função para "desbugar" o buffer da tela 
void limpaTela(){
	gotoxy(21,10);
	printf(" 	                 ");
	gotoxy(25,11);
	printf("              ");
	gotoxy(24,12);
	printf("               ");
}
// Função para deixar o software pausado || X e Y representam a posição na tela através do GOTOXY
void pause(int x, int y){
	char key;
	int keyValue;
	do{
		colorir(14,0);
		gotoxy(x,y);
		printf("Pressione enter para continuar...");
		key = getch();
		keyValue = key;
	}while(keyValue!=13);
}
// Função para gravar e ler o txt
FILE* abrirArquivo(char modo, char caminho[30]){
	FILE *arquivo;
	switch( modo ){
		case 'g':{
			arquivo = fopen(caminho,"wt");		
			break;
		}
		case 'l':{
			arquivo = fopen(caminho,"rt");
			break;
		}
		case 'a':{
			arquivo = fopen(caminho,"a");
			break;
		}
	}
	if(arquivo==NULL){
		exit(0);
	}
	return arquivo;
}
void fechaArquivo(FILE *arquivo){
	fclose(arquivo);
}
void salvaSecsao(){
	//jogador.nomeUsuario;
	//jogador.pontos;
}
void pg_Vidas(){
	int i;
	colorir(11,0);
	for(i=0;i<jogador.vidas;i++){
		printf("%c ",3);
	}
	colorir(14,0);
}
//Função para mostrar ranking
void telaRanking(){
	system("cls");	
	moldura();
	
	FILE *arquivo;
	struct Jogador lista_jogadores[50];
	arquivo = abrirArquivo('l',"dados.txt");

	char senha[15];
	char vPontos[10];

	int cont = 0;

	while(!feof(arquivo)){
			fscanf(arquivo,"%s %s %s ",lista_jogadores[cont].nomeUsuario,senha,vPontos);
			lista_jogadores[cont].pontos = atoi(vPontos);
			cont++;
		
	}
	//cont -= 1;

	colorir(14,0);
	gotoxy(6,2);
	printf("###########################################");
	gotoxy(6,3);
	printf("##           Classificação  C-SHark      ##");
	gotoxy(6,4);
	printf("###########################################");
	gotoxy(6,5);
	printf("##  Posicao |   Jogador  |   Pontuacao   ##");
	gotoxy(6,6);
	printf("#####################################");
	
	int aux = 0,i, j;
	char auxNome[15];
   	for (j=cont; j>0; j--){
        for (i=0; i<j; i++){
            if (lista_jogadores[i].pontos < lista_jogadores[i+1].pontos){                            
                aux = lista_jogadores[i].pontos;
                lista_jogadores[i].pontos = lista_jogadores[i+1].pontos;
                lista_jogadores[i+1].pontos = aux;
                
				strcpy(auxNome,lista_jogadores[i].nomeUsuario);  
				strcpy(lista_jogadores[i].nomeUsuario,lista_jogadores[i+1].nomeUsuario);
				strcpy(lista_jogadores[i+1].nomeUsuario,auxNome); 
            }
        }
    }
    int y = 0;
    for(i = 0;i <= cont && i < 10; i++){
    	gotoxy(6,i+7);
    	printf("##    %d    |   %s    |      %d     ##\n",(i+1),lista_jogadores[i].nomeUsuario,lista_jogadores[i].pontos);
	}
	gotoxy(6,i+7);
	printf("#####################################");

	pause(25,30);	

	system("cls");
	logo();
	moldura();	
}
int mascaraNumerica(int x, int y, int maxNumbers){
	int key = 0;
	char keyPressed, strNumero[3];
	int i = 0, n;
	float numero = 0;
	gotoxy(x,y);
	printf(": ");
	while(key!=13){
		keyPressed = getch();
		key = keyPressed;
		if( i < maxNumbers ){
			if(key > 47 && key < 58 || key == 46){
				strNumero[i] = keyPressed;
				i++;
				gotoxy(x+i,y);
				printf("%c",keyPressed);
			}
		}
		if( key == 8){
			for(n = 0; n < maxNumbers; n++){
				strNumero[n] = 'a';
			}
			gotoxy(x+1,y);
			printf("   ");
			i=0;
		}
	}
	numero = atoi(strNumero); 
	return numero;
}
// Função para mostrar nome e pontuação na parte superior do jogo
void topBar(){
	int i,y;
	colorir(11,0);
	for( i=0; i < 35; i++ ){
		gotoxy(50+i,2);
		printf("*");
		for( y=1; y <= 10; y++ ){
			gotoxy(50,2+y);
			printf("*");
			gotoxy(84,2+y);
			printf("*");
		}
		gotoxy(50+i,13);
		printf("*");
	}
	colorir(14,0);
	gotoxy(52,3);
	printf("Nome: ");colorir(11,0);printf("%s",jogador.nomeUsuario);colorir(14,0);
	gotoxy(52,5);
	printf("Pontos:");colorir(11,0);printf(" %d",jogador.pontos);colorir(14,0);
	// Gambiarra para desbugar
	gotoxy(52,7);
	puts("                         ");
	gotoxy(52,7);
	printf("Vidas: ");pg_Vidas();
	gotoxy(52,9);
	printf("Chave:");colorir(11,0);printf(" %d | 1",chave);colorir(14,0);
	gotoxy(52,11);
	printf("Porta:");colorir(11,0);printf(" %d | 1",porta);colorir(14,0);
}
// Função para mostrar as perguntas
void v_perguntas(char operacao){
	float soma = 0;
	float resultado = 0;
	int i = 0;
	int valor1 = 0, valor2 = 0;
	do{
		soma = 0;
		valor1 = aleatorio(10);
		valor2 = aleatorio(10);
	
		gotoxy(60,15
		);
		printf("%d %c %d",valor1,operacao,valor2);
		
		if(operacao == '+'){
			soma = valor1 + valor2;	
		}
		else if(operacao == '*'){
			soma = valor1 * valor2;
		}
		else if(operacao == '/'){
			soma = valor1 / valor2;
		}
		colorir(11,0);
		gotoxy(60,16);
		printf("Resultado: ");
		colorir(14,0);
		//scanf("%f",&resultado);
		
		resultado = mascaraNumerica(69,16,4);
		
		gotoxy(60,16);
		printf("               ");
		gotoxy(60,15);
		printf("               ");
		
		// Pontos
		if(resultado == soma){
			jogador.pontos += 2;
			topBar();
		}
		else {
			jogador.pontos -= 1;
			jogador.vidas -= 1;
			topBar();
		}
	}while(resultado != soma);	
}
void tabuleiro(char matriz [5][5]){
	gotoxy(4,25);
	colorir(14,4);
	printf("AVISO:");
	colorir(14,0);
	printf(" Pressione ESC para voltar ao menu");

	colorir(11,0);
	gotoxy(4,3);
	printf ("\t###############################\n");
	gotoxy(4,4);
	printf ("\t#     |     |     |     |     #\n");
	gotoxy(4,5);
	printf ("\t# %c   | %c   | %c   | %c   | %c   # \n",matriz[0][0],matriz[0][1],matriz[0][2],matriz[0][3],matriz[0][4]);
	gotoxy(4,6);
	printf ("\t#     |     |     |     |     #\n");
	gotoxy(4,7);
	printf ("\t###############################\n");
	gotoxy(4,8);
	printf ("\t#     |     |     |     |     #\n");
	gotoxy(4,9);
	printf ("\t# %c   | %c   | %c   | %c   | %c   # \n",matriz[1][0],matriz[1][1],matriz[1][2],matriz[1][3],matriz[1][4]);
	gotoxy(4,10);
	printf ("\t#     |     |     |     |     #\n");
	gotoxy(4,11);
	printf ("\t###############################\n");
	gotoxy(4,12);
	printf ("\t#     |     |     |     |     #\n");
	gotoxy(4,13);
	printf ("\t# %c   | %c   | %c   | %c   | %c   # \n",matriz[2][0],matriz[2][1],matriz[2][2],matriz[2][3],matriz[2][4]);
	gotoxy(4,14);
	printf ("\t#     |     |     |     |     #\n");
	gotoxy(4,15);
	printf ("\t###############################\n");
	gotoxy(4,16);
	printf ("\t#     |     |     |     |     #\n");
	gotoxy(4,17);
	printf ("\t# %c   | %c   | %c   | %c   | %c   # \n",matriz[3][0],matriz[3][1],matriz[3][2],matriz[3][3],matriz[3][4]);
	gotoxy(4,18);
	printf ("\t#     |     |     |     |     #\n");
	gotoxy(4,19);
	printf ("\t###############################\n");
	gotoxy(4,20);
	printf ("\t#     |     |     |     |     #\n");
	gotoxy(4,21);
	printf ("\t# %c   | %c   | %c   | %c   | %c   # \n",matriz[4][0],matriz[4][1],matriz[4][2],matriz[4][3],matriz[4][4]);
	gotoxy(4,22);
	printf ("\t#     |     |     |     |     #\n");
	gotoxy(4,23);
	printf ("\t###############################\n");
} 
void movimenta(int x, int y){
	matriz[x][y] = 'C';
	tabuleiro(matriz);
	
}
void chaveEPorta(int x, int y){	
	if(x==chaveX && y==chaveY){
		if(chave==0){
			chave+=1;
			topBar();
			}
	}
	if(x==portaX && y==portaY){
		if(porta==0){
			porta+=1;
			topBar();
			}
		if(chave==1){
			//gotoxy(0,0);printf("Entrou");
		}
	}
}
void perguntas(int nivel){
	if(nivel==1){
		v_perguntas('+');
	}
	else if(nivel==2){
		v_perguntas('*');
	}
	else if(nivel==3){
		v_perguntas('/');
	}
}
void jogar(int nivel){
	// Barra de progresso
	loading();
	
	// Gera a chave e porta aleatoria
	chaveX = aleatorio(MAX_MATRIZ);	
	chaveY = aleatorio(MAX_MATRIZ);
	portaX = aleatorio(MAX_MATRIZ);
	portaY = aleatorio(MAX_MATRIZ);
	// Nao deixa a chave e porta nascerem no mesmo local
	if(chaveX == portaX && chaveY == portaY ){
		portaX = aleatorio(MAX_MATRIZ);
		portaY = aleatorio(MAX_MATRIZ);
	}
	// Nao deixa a chave nascer na primeira posicao
	if( chaveX == 4 && chaveY == 4  ){
		chaveX = aleatorio(MAX_MATRIZ);	
		chaveY = aleatorio(MAX_MATRIZ);
	}
	// Nao deixa a porta nascer na primeria posicao
	if(  portaY == 4 && portaX == 4){
		portaX = aleatorio(MAX_MATRIZ);
		portaY = aleatorio(MAX_MATRIZ);
	}
	/*
	gotoxy(0,0);
	printf("Chave: [%d][%d] Porta: [%d][%d]",chaveX,chaveY,portaX,portaY); // teste para saber onde estão nascendo chave e porta
	*/
	jogador.vidas = MAX_VIDAS;
	chave = 0;
	porta = 0;
	topBar();
	int x = 4;
	int y = 4;
	char casas [5][5];
	int i , n;
	for(i = 0; i < MAX_MATRIZ; i++){
		for(n = 0; n < MAX_MATRIZ; n++){
			casas[i][n]=' ';
		}
	}
	casas[x][y]='C';
	tabuleiro(casas);
	
	char tecla;
	int TCPressionada, sair = 0;
	while(1 && sair!=3){
		tecla = getch();
		TCPressionada = tecla;
		switch(TCPressionada){
			//Seta para esquerda
			case 75:
					if(x==portaX && y==portaY ){
						matriz[x][y] = 'P';
					}
					else {
						matriz[x][y] = 'X';	
					}
					y -= 1;
					if ((y < 0) || (y > 4)){
						y += 1;
					}
					if(matriz[x][y]=='X' || matriz[x][y]=='P'){
						movimenta(x,y);	
					}
					else {
						perguntas(nivel);
						movimenta(x,y);
					}
					chaveEPorta(x,y);
					break;
				case 72:
					if( x==portaX && y==portaY ){
						matriz[x][y] = 'P';
					}
					else {
						matriz[x][y] = 'X';	
					}
					x -= 1;
					if ((x < 0 ) || (x > 4)){
						x += 1;
						
					}
					if(matriz[x][y]=='X' || matriz[x][y]=='P'){
						movimenta(x,y);	
					}
					else {
						perguntas(nivel);
						movimenta(x,y);
					}
					chaveEPorta(x,y);
					break;
				case 77:
					if(x==portaX && y==portaY){
						matriz[x][y] = 'P';
					}
					else {
						matriz[x][y] = 'X';	
					}
					y += 1;
					if ((y < 0) || (y > 4)){
						y -= 1;
						
					}
					if(matriz[x][y]=='X' || matriz[x][y]=='P'){
						movimenta(x,y);	
					}
					else {
						perguntas(nivel);
						movimenta(x,y);
					}
					chaveEPorta(x,y);
					break;
				case 80:
					if( x==portaX && y==portaY ){
						matriz[x][y] = 'P';
					}
					else {
						matriz[x][y] = 'X';	
					}
					x += 1;
					if ((x < 0 ) || (x > 4)){
						x -= 1;
					}
					if(matriz[x][y]=='X' || matriz[x][y]=='P'){
						movimenta(x,y);	
					}
					else {
						perguntas(nivel);
						movimenta(x,y);
					}
					chaveEPorta(x,y);
					break;
				case 27:{
					zeraMatriz();
					sair=3;
					system("cls");
					logo();
					moldura();
					break;
				}
		}	
	}
}
void menu_nivel(){
	system("cls");
	logo();
	moldura();
	char key;
	int keyValue;
	// Pos representa a posição do item selecionado
	int pos=1, sair=0;
	gotoxy(35,13);
	colorir(11,0);
	printf(">> Facil   ");
	colorir(14,0);
	gotoxy(35,14);
	printf("Medio      ");
	gotoxy(35,15);
	printf("Dificil   ");
	gotoxy(35,16);
	printf("Voltar    ");
	
	do{
		key = getch();
		keyValue = key;
		switch(keyValue){
			// Pressionou para cima
			case 72:{
				if(pos > 1 && pos <= 4){
					pos--;
				}		
				break;
			}
			// Pressionou para baixo
			case 80:{
				if(pos >= 1 && pos < 4){
					pos++;	
				}
				break;
			}
			case 13:{
				system("cls");
				if(pos==4){
					sair=3;
				}
				else {
					jogar(pos);	
				}
				break;
			}
			default:{
				break;
			}	
		}
		if(pos==1)
		{
			gotoxy(35,13);
			colorir(11,0);
			printf(">> Facil  ");
			colorir(14,0);
			gotoxy(35,14);
			printf("Medio     ");
			gotoxy(35,15);
			printf("Dificil   ");
			gotoxy(35,16);
			printf("Voltar    ");
		}
		else if(pos==2)
		{
			colorir(14,0);
			gotoxy(35,13);
			printf("Facil     ");
			gotoxy(35,14);
			colorir(11,0);
			printf(">> Medio   ");
			colorir(14,0);
			gotoxy(35,15);
			printf("Dificil    ");
			gotoxy(35,16);
			printf("Voltar    ");
		}
		else if(pos==3){
			colorir(14,0);
			gotoxy(35,13);
			printf("Facil     ");
			gotoxy(35,14);
			printf("Medio     ");
			gotoxy(35,15);
			colorir(11,0);
			printf(">> Dificil  ");
			colorir(14,0);
			gotoxy(35,16);
			printf("Voltar    ");
		}
		else if(pos==4){
			colorir(14,0);
			gotoxy(35,13);
			printf("Facil     ");
			gotoxy(35,14);
			printf("Medio     ");
			gotoxy(35,15);
			printf("Dificil    ");
			gotoxy(35,16);
			colorir(11,0);
			printf(">> Voltar    ");
		}
	}while(1 && sair!=3);
	system("cls");
	// Logo e moldura do jogo
	logo();
	moldura();
}
// Salvar dados do usuário
void salvarUsuario(char nome[15], char senha[99]){
	FILE *arquivo;
	arquivo = abrirArquivo('a',"dados.txt");
	fprintf(arquivo,"%s %s 0\n", nome, senha);
	fechaArquivo(arquivo);
	system("cls");
	printf("\n\n\tSalvando");
	int i;
	for(i=0;i<3;i++){
		printf(".");
		Sleep(300);
	}
	system("cls");
}
int listarUsuario(char user[15], char password[99]){
	FILE *arquivo;
	char nome[15];
	char senha[99];
	char vPontos[10];
	int valor = 0; // valor a ser retornado para o software indicando 1 para usuario existente e 0 para nao exitente
	arquivo = abrirArquivo('l',"dados.txt");
	while(!feof(arquivo)){
		fscanf(arquivo,"%s %s %s ",nome,senha,vPontos);
		if(strcmp(user,nome) == 0 && strcmp(senha,password) == 0) {
			strcpy(jogador.nomeUsuario,nome);
			strcpy(jogador.senha,senha);
			valor =  1;
			jogador.pontos = atoi(vPontos);
		//	pontos = vPontos;
			break;
		}
		else {
			valor = 0;
		}
	}
	fechaArquivo(arquivo);	
	return valor;
}
void menuSecundario(){
	system("cls");
	logo();
	moldura();
	char key;
	int keyValue;
	// Pos representa a posição do item selecionado
	int pos=1, sair=0;
	gotoxy(35,13);
	colorir(11,0);
	printf(">> Jogar");
	colorir(14,0);
	gotoxy(35,14);
	printf("Classificação");
	gotoxy(35,15);
	printf("Voltar");
	do{
		key = getch();
		keyValue = key;
		switch(keyValue){
			// Pressionou para cima
			case 72:{
				if(pos > 1 && pos <= 3){
					pos--;
				}		
				break;
			}
			// Pressionou para baixo
			case 80:{
				if(pos >= 1 && pos < 3){
					pos++;	
				}
				break;
			}
			case 13:{
				if(pos==1){
					system("cls");
					menu_nivel();
				}
				if(pos==2){
					system("cls");
					telaRanking();	
				}
				if(pos==3){
					sair=3;
				}
				break;
			}
			default:{
				break;
			}	
		}
		if(pos==1)
		{
			limpaTela();
			gotoxy(35,13);
			colorir(11,0);
			printf(">> Jogar");
			colorir(14,0);
			gotoxy(35,14);
			printf("Classificação      ");
			gotoxy(35,15);
			printf("Voltar   ");
		}
		else if(pos==2)
		{
			limpaTela();
			gotoxy(35,13);
			colorir(14,0);
			printf("Jogar   ");
			gotoxy(35,14);
			colorir(11,0);
			printf(">> Classificação");
			colorir(14,0);
			gotoxy(35,15);
			printf("Voltar   ");
		}
		else if(pos==3)
		{
			limpaTela();
			gotoxy(35,13);
			printf("Jogar  ");
			gotoxy(35,14);
			printf("Classificação      ");
			gotoxy(35,15);
			colorir(11,0);
			printf(">> Voltar");
			colorir(14,0);
		}
	}while(1 && sair!=3);
}
// Tela de login
void telaLogin(){
	system("cls");
	char user[15];
	char senha[99];
	int pos = 0;
	moldura();
	logo();
	// Colocando os campos de usuario e senha
	colorir(14,0);
	gotoxy(6,12);
	printf("Usuario: ");	
	gotoxy(6,13);
	printf("Senha: ");
	btn_EntrarCancelar(pos);
	// Colocando o gets() ao lado dos campos de usuario e senha
	colorir(11,0);
	gotoxy(14,12);
	gets(user);
	setbuf(stdin,NULL);
	gotoxy(12,13);
	gets(senha);
	setbuf(stdin,NULL);
	colorir(11,0);
	// Gambiarra
	pos = 1;
	btn_EntrarCancelar(pos);
	// Não mecher
	char key;
	int keyPressed;
	int sair = 0;
	do{
		key = getch();
		keyPressed = key;
		switch(keyPressed){
			case 75:{
				pos = 1;
				btn_EntrarCancelar(pos);
				break;
			}
			case 77:{
				pos = 2;
				btn_EntrarCancelar(pos);
				break;
			}
			case 13:{
				if(pos==1){
					// Logar
					int valor = listarUsuario(user,senha);
					if(valor==1){
						system("cls");
						// abrir o jogo
						menuSecundario();
					}
					else {
						gotoxy(4,20);
						colorir(14,0);
						printf("OPS paraece que os dados informados nao existem em nosso banco de dados!!");
						pause(4,22);
					}
				}
				sair=1;
				break;
			}
		}
		if(sair==1) break;
	}while(1);
	colorir(14,0);
	system("cls");
	// Logo para C-Shark - Moldura
	logo();
	moldura();
}
// Tela de caadastro
void menuCadasto(){
	system("cls");
	moldura();
	logo();
	int i, y;
	char user[15];
	char senha[3];
	char confirmarSenha[3];
	char key;
	int keyValue, pos = 1;
	gotoxy(23,17);
	colorir(14,0);
	printf("[ Salvar ]");
	printf("[ Cancelar ]");
	// Colocando os campos na tela
	colorir(14,0);
	gotoxy(5,12);
	printf("Digite seu nome de usuario: ");
	gotoxy(5,13);
	printf("Digite sua senha: ");
	gotoxy(5,14);
	printf("Confirme sua senha:");
	//pegando dados
	colorir(11,0);
	gotoxy(32,12);
	scanf("%s",user);
	setbuf(stdin,NULL);
	gotoxy(22,13);
	scanf("%s",senha);
	setbuf(stdin,NULL);
	gotoxy(24,14);
	scanf("%s",confirmarSenha);
	setbuf(stdin,NULL);
	// comparando a senha se é igual
	if(!strcmp(senha,confirmarSenha)==0){
		gotoxy(4,20);
		colorir(9,4);
		printf("AVISO:");
		colorir(15,0);
		printf(" A senhas digitadas nao sao iguais!!");
		pause(3,22);
		pos=3;
	}
	// verificando se o usurio ja existe
	FILE *arquivo;
	char nome[15];
	char password[15];
	int valor = 0;
	arquivo = abrirArquivo('l',"dados.txt");
	while(!feof(arquivo)){
		fscanf(arquivo,"%s %s 0 ",nome,password);
		if(strcmp(user,nome) == 0) {
			valor =  1;
			break;
		}
		else {
			valor = 0;
		}
	}
	fechaArquivo(arquivo);
	if(valor==1){
		gotoxy(4,20);
		colorir(14,4);
		printf("AVISO:");
		colorir(14,0);
		printf(" Ja existe um usuario com esse nome cadastrado!!");
		gotoxy(23,17);
		printf("[ Salvar ]");
		printf("[ Cancelar ]");
		pause(3,22);
		pos=3;
	}
	// GAMBIARRA --------------
	colorir(14,4);
	gotoxy(23,17);
	printf("[ Salvar ]");
	colorir(14,0);
	printf("[ Cancelar ]");
	// -----------------------
	while(pos!=3){
		key = getch();
		keyValue = key;
		switch( keyValue ){
			case 9:
			case 77:
			case 75:
			{
				if(pos==1){
					pos=2;
				}
				else if(pos==2){
					pos=1;
				}	
				break;
			}
			case 13:{
				if(pos==1){
					salvarUsuario(user,senha);
					pos=3;	
				}
				else {
					pos=3;
				}
				break;
			}	
			default:{
				break;
			}
		}
		if(pos==1){
			colorir(14,4);
			gotoxy(23,17);
			printf("[ Salvar ]");
			colorir(14,0);
			printf("[ Cancelar ]");
		}
		else if(pos==2){
			colorir(14,0);
			gotoxy(23,17);
			printf("[ Salvar ]");
			colorir(14,4);
			printf("[ Cancelar ]");
			colorir(0,0);
		}
	}
	system("cls");
	logo();
	moldura();
}
// Tela com o menu principal
void menuPrincipal(){
	system("cls");
	logo();
	moldura();
	char key;
	int keyValue;
	// Pos representa a posição do item selecionado
	int pos=1;
	gotoxy(35,13);
	colorir(11,0);
	printf(">> Cadastrar");
	colorir(14,0);
	gotoxy(35,14);
	printf("Entrar   ");
	gotoxy(35,15);
	printf("Sair   ");
	do{
		key = getch();
		keyValue = key;
		switch(keyValue){
			// Pressionou para cima
			case 72:{
				if(pos > 1 && pos <= 3){
					pos--;
				}		
				break;
			}
			// Pressionou para baixo
			case 80:{
				if(pos >= 1 && pos < 3){
					pos++;	
				}
				break;
			}
			case 13:{
				if(pos==1){
					menuCadasto();
				}
				if(pos==2){
					telaLogin();
				}
				if(pos==3){
					colorir(14,0);
					system("cls");
					gotoxy(3,3);
					printf("Saindo ");
					int i;
					gotoxy(9,3);
					for( i = 0; i < 3; i++ ){
						printf(".");
						Sleep(340);
					}
					exit(0);
				}
				break;
			}
			default:{
				break;
			}	
		}
		colorir(14,0);
		if(pos==1)
		{
			limpaTela();
			gotoxy(35,13);
			colorir(11,0);
			printf(">> Cadastrar");
			colorir(14,0);
			gotoxy(35,14);
			printf("Entrar   ");
			gotoxy(35,15);
			printf("Sair   ");
		}
		else if(pos==2)
		{
			limpaTela();
			gotoxy(35,13);
			printf("Cadastrar   ");
			gotoxy(35,14);
			colorir(11,0);
			printf(">> Entrar");
			colorir(14,0);
			gotoxy(35,15);
			printf("Sair   ");
		}
		else if(pos==3)
		{
			limpaTela();
			gotoxy(35,13);
			printf("Cadastrar   ");
			gotoxy(35,14);
			printf("Entrar   ");
			gotoxy(35,15);
			colorir(11,0);
			printf(">> Sair");
			colorir(14,0);
		}
	}while(1);
			
}
int main()
{	
	system("MODE CON: COLS=100 LINES=100");
	setlocale(LC_ALL, "Portuguese");
	menuPrincipal();
	return 0;
}
