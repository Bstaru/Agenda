#include <Windows.h>
#include "resource.h"
#include <string>
#include <fstream>

using namespace std;

BOOL seLeyo=false;
int count;
int countcat;
int countmu;
int countd;
char Name[MAX_PATH];
char radiobtn[10];

//--------Lista de contactos------------------------------------------------------------------------------
struct persona
{
	int key2;
	char categoria[50];
	char nombre[50];
	char apellidop[50];
	char apellidom[50];
	char direccion[100];
	char tel[20];
	char cel[20];
	char foto[256];

	persona*sig;
	persona*ant;

} Per[50];

struct persona *inicio, *tempo, *final;
persona *buscado, *encontrado;

//declaraciones necesarias y punteros---------------------------------------------------------------------

persona *p,*q,*list = NULL;
int id=0, c=0, j=0, i=0;

//------------Lista de categoria-------------------------------------------------------------------------
struct categos
{
char Ncat[50];
int posiD;
categos *sig, *ant;
};
categos *cini, *ctaux, *clast;
//------------Lista de musicas----------------------------------------------------------------------------
struct musict
{
	int id;
	char NoMusic[MAX_PATH];
	musict *ant, *sig;
};
struct fakem
{
	char FaMus[MAX_PATH];
	fakem *sig, *ant;
};
musict *mini, *maux, *mlast;
fakem *fini, *faux, *flast;

char k[256] = { "\0" };

//------------Lista de dias/alarmas/etc------------------------------------------------------------------
struct diaa
{
	char Nota[256];
	char dias[3];
	char mess[3];
	char año[5];
	char minus[3], horas[3];
	char Namdate[25];
	char MuAl[25];
	char per[25];
	diaa *sig, *ant;
};
diaa *dini, *daux, *dlast;


//cosas de la foto--------------------------------------------------------------------------------------- 
OPENFILENAME ofn;
char extensiondef[5] = "bmp\0";
char archivo[MAX_PATH] = "\0";
char length = sizeof(archivo);
char filtro[50] = "Bitmap\0*.bmp\0\0";
char dirinicial[MAX_PATH] = "C:\\Imagenes";
char titulo[50] = "Foto de Contacto";
char directorio[150];

char jongkey[256];


static HBITMAP hBmp,Bip2,Bip3,Bip4,Bip5,Bip6,Bip7,Bip8;
static HWND hPic=0;
