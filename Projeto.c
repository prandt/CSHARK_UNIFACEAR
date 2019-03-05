#include <stdio.h>
#include <windows.h>
#include <conio.h>

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void arte_CSHARK()
{

}
// Tela de aguardando
void waiting(){
	system("cls");
	int i = 0;
	gotoxy(3,3);
	printf("Aguarde ");
	gotoxy(10,3);
	for(i=0;i<3;i++){
		printf(".");
		Sleep(500);
	}
	system("cls");
}
void telaLogin()
{
	system("cls");
	char user[15];
	char senha[99];
	//Desenhando as linhas
	int i = 0, y = 0;
	for( i = 0; i <= 20; i ++ ){
		gotoxy(3+i,1);
		printf("*********");
		for( y = 1; y <= 5; y++ ){
			gotoxy(3,y);
			printf("*");
			gotoxy(31,y);
			printf("*");
		}
		gotoxy(3+i,6);
		printf("*********");
	}
	// Colocando os campos de usuario e senha
	gotoxy(5,3);
	printf("Usuario: ");	
	gotoxy(5,4);
	printf("Senha: ");
	// Colocando o gets() ao lado dos campos de usuario e senha
	gotoxy(13,3);
	gets(user);
	setbuf(stdin,NULL);
	gotoxy(11,4);
	gets(senha);
	setbuf(stdin,NULL);
	waiting();
}
void menuPrincipal(){
	char key;
	int keyValue;
	int valor=1;
	gotoxy(5,3);
	printf(">> Cadastrar");
	gotoxy(4,4);
	printf("Entrar");
	gotoxy(4,5);
	printf("Sair");
	do{
		key = getch();
		keyValue = key;
		switch(keyValue){
			// Pressionou para cima
			case 72:{
				if(valor > 1 && valor <= 3){
					valor--;
				}		
				break;
			}
			// Pressionou para baixo
			case 80:{
				if(valor >= 1 && valor < 3){
					valor++;	
				}
				break;
			}
			case 13:{
				if(valor==1){
					
				}
				if(valor==2){
					telaLogin();
				}
				if(valor==3){
					exit(0);
				}
				break;
			}
			default:{
				break;
			}	
		}
		if(valor==1)
		{
			system("cls");
			gotoxy(5,3);
			printf(">> Cadastrar");
			gotoxy(4,4);
			printf("Entrar");
			gotoxy(4,5);
			printf("Sair");
		}
		else if(valor==2)
		{
			system("cls");
			gotoxy(4,3);
			printf("Cadastrar");
			gotoxy(5,4);
			printf(">> Entrar");
			gotoxy(4,5);
			printf("Sair");
		}
		else if(valor==3)
		{
			system("cls");
			gotoxy(4,3);
			printf("Cadastrar");
			gotoxy(4,4);
			printf("Entrar");
			gotoxy(5,5);
			printf(">> Sair");
		}
	}while(1);		
}
int main()
{	
	menuPrincipal();
	printf("\n\n");
	system("pause");
	return 0;
}
