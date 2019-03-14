#include <stdio.h>
#include <windows.h>
#include <conio.h>

// Alinhas os quadros
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// Função para deixar o software pausado
void pause(int x, int y){
	char key;
	int keyValue;
	do{
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
void arte_CSHARK()
{
	//Desenhando as linhas
	int i = 0, y = 0;
	for( i = 0; i < 20; i ++ ){
		gotoxy(3+i,1);
		colorir(1,0);
		printf("####################");
		for( y = 1; y <= 15; y++ ){
			gotoxy(3,y);
			printf("#");
			gotoxy(41,y);
			printf("#");
		}
		gotoxy(3+i,15);
		printf("####################");
		colorir(15,0);
	}
	Sleep(20);
}
// Colorir
void colorir(int F, int B) {
	WORD wColor = ((B & 0x0F) << 4) + (F & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
// Mostra barra de progresso
void loading(){
	system("cls");
	int i;
	gotoxy(5,2);
	printf("Carregando [");
	gotoxy(27,2);
	printf("]");
	colorir(2,0);
	gotoxy(17,2);
	for( i=0;i<=9;i++ ){
		printf("#");
		Sleep(350);		
	}
	colorir(15,0);
}
// Tela de login
void telaLogin()
{
	system("cls");
	char user[15];
	char senha[99];
	//Desenhando as linhas
	int i = 0, y = 0;
	for( i = 0; i <= 20; i ++ ){
		gotoxy(3+i,1);
		colorir(9,0);
		printf("*********");
		for( y = 1; y <= 5; y++ ){
			gotoxy(3,y);
			printf("*");
			gotoxy(31,y);
			printf("*");
		}
		gotoxy(3+i,6);
		printf("*********");
		colorir(15,0);
	}
	// Colocando os campos de usuario e senha
	gotoxy(5,3);
	printf("Usuario: ");	
	gotoxy(5,4);
	printf("Senha: ");
	// Colocando o gets() ao lado dos campos de usuario e senha
	colorir(6,0);
	gotoxy(13,3);
	gets(user);
	setbuf(stdin,NULL);
	gotoxy(11,4);
	gets(senha);
	setbuf(stdin,NULL);
	colorir(15,0);
	int valor = listarUsuario(user,senha);
	if(valor==1){
		printf("\n\n\n\n\n existe kkk");
		loading();
		// abrir o jogo
	}
	else {
		gotoxy(5,8);
		colorir(4,0);
		printf("OPS paraece que os dados informados nao existem em nosso banco de dados!!");
		colorir(15,0);
		pause(5,10);
	}
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
	// desenhando os * na tela
	for( i=0; i < 55; i++ ){
		colorir(9,0);
		gotoxy(3+i,2);
		printf("***");
		for( y=2; y<=15; y++ ){
			gotoxy(3,y);
			printf("*");
			gotoxy(59,y);
			printf("*");
		}
		gotoxy(3+i,15);
		printf("***");
		colorir(15,0);
	}
	gotoxy(15,13);
	printf("[ Salvar ]");
	printf("[ Cancelar ]");
	// Colocando os campos na tela
	gotoxy(5,4);
	printf("Digite seu nome de usuario: ");
	gotoxy(5,6);
	printf("Digite sua senha: ");
	gotoxy(5,8);
	printf("Confirme sua senha:");
	//pegando dados
	colorir(6,0);
	gotoxy(32,4);
	scanf("%s",user);
	setbuf(stdin,NULL);
	gotoxy(22,6);
	scanf("%s",senha);
	setbuf(stdin,NULL);
	gotoxy(24,8);
	scanf("%s",confirmarSenha);
	setbuf(stdin,NULL);
	colorir(15,0);
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
		gotoxy(15,13);
		printf("[ Salvar ]");
		printf("[ Cancelar ]");
		pause(3,22);
		pos=3;
	}
	// GAMBIARRA KKKKKKKKK
	colorir(9,4);
	gotoxy(15,13);
	printf("[ Salvar ]");
	colorir(15,0);
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
			colorir(9,4);
			gotoxy(15,13);
			printf("[ Salvar ]");
			colorir(15,0);
			printf("[ Cancelar ]");
		}
		else if(pos==2){
			colorir(15,0);
			gotoxy(15,13);
			printf("[ Salvar ]");
			colorir(9,4);
			printf("[ Calcelar ]");
			colorir(15,0);
		}
	}
	system("cls");
	arte_CSHARK();
}
void limpaTela(){
	gotoxy(4,9);
	printf("		              ");
	gotoxy(4,10);
	printf("       		       ");
	gotoxy(4,11);
	printf("            		  ");
}
// Tela com o menu principal
void menuPrincipal(){
	system("cls");
	arte_CSHARK();
	char key;
	int keyValue;
	// Pos representa a posição do item selecionado
	int pos=1;
	gotoxy(5,9);
	colorir(4,0);
	printf("		>> Cadastrar");
	colorir(15,0);
	gotoxy(4,10);
	printf("		Entrar");
	gotoxy(4,11);
	printf("		Sair");
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
		if(pos==1)
		{
			limpaTela();
			gotoxy(4,9);
			colorir(4,0);
			printf("		>> Cadastrar");
			colorir(15,0);
			gotoxy(5,10);
			printf("		Entrar");
			gotoxy(5,11);
			printf("		Sair");
		}
		else if(pos==2)
		{
			limpaTela();
			gotoxy(5,9);
			printf("		Cadastrar");
			gotoxy(4,10);
			colorir(4,0);
			printf("		>> Entrar");
			colorir(15,0);
			gotoxy(5,11);
			printf("		Sair");
		}
		else if(pos==3)
		{
			limpaTela();
			gotoxy(5,9);
			printf("		Cadastrar");
			gotoxy(5,10);
			printf("		Entrar");
			gotoxy(4,11);
			colorir(4,0);
			printf("		>> Sair");
			colorir(15,0);
		}
	}while(1);		
}
int main()
{	
	menuPrincipal();
	return 0;
}
