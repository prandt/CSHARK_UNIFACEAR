#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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
		Sleep(1000);
	}
	system("cls");
}
void telaLogin()
{
	char user[15];
	char senha[99];
	//Desenhando as linhas
	int i = 0;
	gotoxy(3,1);
	for(i=0;i<10;i++)
	{
		printf("***");
	}
	gotoxy(3,6);
	for(i=0;i<10;i++)
	{
		printf("***");
	}
	for(i=1;i<=5;i++){
		gotoxy(3,i);
		printf("*");
	}
	for(i=1;i<=5;i++){
		gotoxy(32,i);
		printf("*");
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

}
int main()
{	
	waiting();
	telaLogin();
	printf("\n\n");
	system("pause");
	return 0;
}
