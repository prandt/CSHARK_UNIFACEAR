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

#define MAX_MATRIZ 5

// Variaveis 
char matriz[MAX_MATRIZ][MAX_MATRIZ];
char nomeUsuario[20];
int chaveX = 0,chaveY = 0;
int chave = 0;
int portaX = 0, portaY = 0;
int porta = 0;

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
void btn_EntrarCancelar(int pos){
	if(pos==0){
		gotoxy(15,13);
		printf("[ Entrar ]");
		printf("[ Cancelar ]");
	}
	else if(pos==1){
		gotoxy(15,13);
		colorir(14,4);
		printf("[ Entrar ]");
		colorir(14,0);
		printf("[ Cancelar ]");
	}
	else if(pos==2){
		gotoxy(15,13);
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
// Arte e moldura padrão do software
void arte_CSHARK(){
	int i = 0, y = 0;
	colorir(11,0);
	for( i = 0; i < 60; i ++ ){
		gotoxy(3+i,1);
		printf("*");
		for( y = 1; y <= 19; y++ ){
			gotoxy(3,y);
			printf("*");
			gotoxy(62,y);
			printf("*");
		}
		gotoxy(3+i,19);
		printf("*");
	}
	colorir(15,0);
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
	printf("Nome: ");colorir(11,0);printf("%s",nomeUsuario);colorir(14,0);
	gotoxy(52,5);
	printf("Pontos:");
	gotoxy(52,7);
	printf("Vidas: ");colorir(11,0);printf("%c %c %c %c",3,3,3,3);colorir(14,0);
	gotoxy(52,9);
	printf("Chave:");colorir(11,0);printf(" %d | 1",chave);colorir(14,0);
	gotoxy(52,11);
	printf("Porta:");colorir(11,0);printf(" %d | 1",porta);colorir(14,0);
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
void jogar(){
	chaveX = aleatorio(MAX_MATRIZ);	
	chaveY = aleatorio(MAX_MATRIZ);
	portaX = aleatorio(MAX_MATRIZ);
	portaY = aleatorio(MAX_MATRIZ);
	if(chaveX == portaX && chaveY == portaY){
		portaX = aleatorio(MAX_MATRIZ);
		portaY = aleatorio(MAX_MATRIZ);
	}
	/*
	gotoxy(0,0);
	printf("Chave: [%d][%d] Porta: [%d][%d]",chaveX,chaveY,portaX,portaY); // teste para saber onde estão nascendo chave e porta
	*/
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
			case 75:
					matriz[x][y] = ' ';
					y -= 1;
					if ((y < 0) || (y > 4)){
						y += 1;
					}
					movimenta(x,y); //Seta para esquerda
					chaveEPorta(x,y);
					break;
				case 72:
					matriz[x][y] = ' ';
					x -= 1;
					if ((x < 0 ) || (x > 4)){
						x += 1;
						
					}
					movimenta(x,y); //Seta para cima
					chaveEPorta(x,y);
					break;
				case 77:
					matriz[x][y] = ' ';
					y += 1;
					if ((y < 0) || (y > 4)){
						y -= 1;
						
					}
					movimenta(x,y); //Seta para direita
					chaveEPorta(x,y);
					break;
				case 80:
					matriz[x][y] = ' ';
					x += 1;
					if ((x < 0 ) || (x > 4)){
						x -= 1;
					}
					movimenta(x,y); //Seta para baixo
					chaveEPorta(x,y);
					break;
				case 27:{
					zeraMatriz();
					sair=3;
					system("cls");
					arte_CSHARK();
					break;
				}
		}	
	}
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
	int valor = 0; // valor a ser retornado para o software indicando 1 para usuario existente e 0 para nao exitente
	arquivo = abrirArquivo('l',"dados.txt");
	while(!feof(arquivo)){
		fscanf(arquivo,"%s %s 0 ",nome,senha);
		if(strcmp(user,nome) == 0 && strcmp(senha,password) == 0) {
			strcpy(nomeUsuario,nome);
			valor =  1;
			break;
		}
		else {
			valor = 0;
		}
	}
	fechaArquivo(arquivo);	
	return valor;
}
// Mostra barra de progresso
void loading(){
	system("cls");
	int i;
	colorir(11,0);
	gotoxy(5,2);
	printf("Carregando [");
	gotoxy(27,2);
	printf("]");
	colorir(14,0);
	gotoxy(17,2);
	for( i=0;i<=9;i++ ){
		printf("#");
		Sleep(150);		
	}
	colorir(15,0);
	system("cls");
}
void menuSecundario(){
	system("cls");
	arte_CSHARK(3);
	char key;
	int keyValue;
	// Pos representa a posição do item selecionado
	int pos=1, sair=0;
	gotoxy(25,10);
	colorir(11,0);
	printf(">> Jogar");
	colorir(14,0);
	gotoxy(25,11);
	printf("Ranking");
	gotoxy(25,12);
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
					loading();
					jogar();
				}
				if(pos==2){
					
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
			gotoxy(25,10);
			colorir(11,0);
			printf(">> Jogar");
			colorir(14,0);
			gotoxy(25,11);
			printf("Ranking");
			gotoxy(25,12);
			printf("Voltar");
		}
		else if(pos==2)
		{
			limpaTela();
			gotoxy(25,10);
			printf("Jogar");
			gotoxy(25,11);
			colorir(11,0);
			printf(">> Ranking");
			colorir(14,0);
			gotoxy(25,12);
			printf("Voltar");
		}
		else if(pos==3)
		{
			limpaTela();
			gotoxy(25,10);
			printf("Jogar");
			gotoxy(25,11);
			printf("Ranking");
			gotoxy(25,12);
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
	arte_CSHARK();
	// Colocando os campos de usuario e senha
	colorir(14,0);
	gotoxy(6,10);
	printf("Usuario: ");	
	gotoxy(6,11);
	printf("Senha: ");
	btn_EntrarCancelar(pos);
	// Colocando o gets() ao lado dos campos de usuario e senha
	colorir(11,0);
	gotoxy(14,10);
	gets(user);
	setbuf(stdin,NULL);
	gotoxy(12,11);
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
	colorir(15,0);
	system("cls");
	arte_CSHARK();
}
// Tela de caadastro
void menuCadasto(){
	system("cls");
	int i, y;
	char user[15];
	char senha[3];
	char confirmarSenha[3];
	char key;
	int keyValue, pos = 1;
	arte_CSHARK();
	gotoxy(20,15);
	colorir(14,0);
	printf("[ Salvar ]");
	printf("[ Cancelar ]");
	// Colocando os campos na tela
	colorir(14,0);
	gotoxy(5,8);
	printf("Digite seu nome de usuario: ");
	gotoxy(5,10);
	printf("Digite sua senha: ");
	gotoxy(5,12);
	printf("Confirme sua senha:");
	//pegando dados
	colorir(11,0);
	gotoxy(32,8);
	scanf("%s",user);
	setbuf(stdin,NULL);
	gotoxy(22,10);
	scanf("%s",senha);
	setbuf(stdin,NULL);
	gotoxy(24,12);
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
		colorir(9,4);
		printf("AVISO:");
		colorir(15,0);
		printf(" Ja existe um usuario com esse nome cadastrado!!");
		gotoxy(20,15);
		colorir(14,0);
		printf("[ Salvar ]");
		printf("[ Cancelar ]");
		pause(3,22);
		pos=3;
	}
	// GAMBIARRA KKKKKKKKK
	colorir(14,4);
	gotoxy(20,15);
	printf("[ Salvar ]");
	colorir(14,0);
	printf("[ Cancelar ]");
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
			gotoxy(20,15);
			printf("[ Salvar ]");
			colorir(14,0);
			printf("[ Cancelar ]");
		}
		else if(pos==2){
			colorir(14,0);
			gotoxy(20,15);
			printf("[ Salvar ]");
			colorir(14,4);
			printf("[ Cancelar ]");
			colorir(0,0);
		}
	}
	system("cls");
	arte_CSHARK();
}
// Tela com o menu principal
void menuPrincipal(){
	system("cls");
	arte_CSHARK();
	char key;
	int keyValue;
	// Pos representa a posição do item selecionado
	int pos=1;
	gotoxy(25,10);
	colorir(11,0);
	printf(">> Cadastrar");
	colorir(14,0);
	gotoxy(25,11);
	printf("Entrar");
	gotoxy(25,12);
	printf("Sair");
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
			gotoxy(25,10);
			colorir(11,0);
			printf(">> Cadastrar");
			colorir(14,0);
			gotoxy(25,11);
			printf("Entrar");
			gotoxy(25,12);
			printf("Sair");
		}
		else if(pos==2)
		{
			limpaTela();
			gotoxy(25,10);
			printf("Cadastrar");
			gotoxy(25,11);
			colorir(11,0);
			printf(">> Entrar");
			colorir(14,0);
			gotoxy(25,12);
			printf("Sair");
		}
		else if(pos==3)
		{
			limpaTela();
			gotoxy(25,10);
			printf("Cadastrar");
			gotoxy(25,11);
			printf("Entrar");
			gotoxy(25,12);
			colorir(11,0);
			printf(">> Sair");
			colorir(14,0);
		}
	}while(1);
			
}
int main()
{	
	system("MODE CON: COLS=100 LINES=100");
	menuPrincipal();
	return 0;
}
