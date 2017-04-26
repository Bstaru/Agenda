#include <Windows.h>
#include "resource.h"
#include "variables.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include<string>
#include <MMSystem.h>

;using namespace std;
#pragma comment(lib,"winmm.lib")

//Cosas para color de ventanas-----------------------------------------------------------------------------------

HBRUSH g_hbrBackground = CreateSolidBrush(RGB(153, 217,234));
HBRUSH g_hbrBackground1 = CreateSolidBrush(RGB(153, 217,234));

//---Declaracion de Funciones--------------------------------------------------------------------------------------
void registrar(char cats[50], int nominas, char nombres[50], char apellidosp[50], char apellidosm[50], 
	char direc1[100], char telefono2[20], char celular2[20], char archivo2 [256]);
void modificar(char cats[50], int keys, char nombres[50], char apellidosp[50], char apellidosm[50], 
	char direc1[100], char telefono2[20], char celular2[20], char archivo2[256]);
void guardar();
void cargar();
void eliminar();
void ACate(char catt[]);
void saveCat();
void delcat();
void AgMu(char NM[]);
void saveMus();
void search(HWND wind, HWND Nwind);
void deldate();
void adddate(char dnom[], char dnote[], char dday[], char dmon[], char dyea[], char dhou[], 
	char dmin[], char dmu[], char dc[]);
void savedate();
int ListBoxSelec(HWND hpar, int idListBox);
void showlist(HWND windo);
void addfake();
char* DeleteChar(char _cadena[100]);

BOOL loadcat(HWND wCat);
BOOL loadmusic(HWND wMus);
BOOL loaddate(HWND wDate);
BOOL load(HWND win);

//-------------botones de la ventana principal---------------------------------------------------------------------
HWND browse =0;
HWND ghDlg = 0;

#define boton1 1
#define boton2 2
#define boton3 3
#define boton4 4
#define boton5 5
#define boton6 6
#define boton7 7
#define boton8 8
#define boton9 9
HWND bot1, bot2, bot3, bot4, bot5, bot6, bot7, bot8, bot9;

//Declaración de los Callbacks------------------------------------------------------------------------------------
BOOL CALLBACK Home(HWND hWnd, UINT msg, WPARAM wParam,LPARAM lParam);
BOOL CALLBACK Registro(HWND hdWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Categoria(HWND hdWnd2, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Contactos(HWND hdWnd3, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Citas(HWND hdWnd4, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK MostrarC (HWND hWndMc, UINT msg, WPARAM wParam,LPARAM lParam);
BOOL CALLBACK Musica(HWND hdWndAm, UINT msg, WPARAM wParam,LPARAM lParam);
BOOL CALLBACK Citas(HWND hWndad, UINT msg, WPARAM wParam,LPARAM lParam);
BOOL CALLBACK MCit(HWND hWndmda, UINT msg, WPARAM wParam,LPARAM lParam);
///Instancias-----------------------------------------------------------------------------------------------------

HINSTANCE hIns, hIns2, hIns3, hIns4, hIns5, hIns6;
HINSTANCE hinstance;
int CmdShow= 0;

//---Ventana principal -------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int showCmd)
{
	CmdShow= showCmd;
	ghDlg= CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG7), 0, Home);	

	ShowWindow(ghDlg, showCmd);
	
	MSG msg;

	ZeroMemory(&msg, sizeof(MSG));

	while(TRUE == GetMessage(&msg, NULL, 0, 0)) 
	{
		if( ghDlg ==0 || !IsDialogMessage(ghDlg, &msg))
		{
			TranslateMessage(&msg);
			
			mciSendString("play alarma notify repeat", NULL, 0, 0);  
			
			DispatchMessage(&msg);

		}
	}
	return (int)msg.wParam;
}

//----Diálogos----------------------------------------------------------------------------------------------------
BOOL CALLBACK Home(HWND hWnd, UINT msg, WPARAM wParam,LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
			SetTimer(hWnd, 1, 1000, (TIMERPROC)NULL);
			load(hWnd);
			loadcat(hWnd);
			loadmusic(hWnd);
			loaddate(hWnd);
			Bip6 = (HBITMAP)SendDlgItemMessage(hWnd, caguai, STM_GETIMAGE, IMAGE_BITMAP,0);
			Bip7 = (HBITMAP)LoadImage(NULL, "c:\lel.bmp", IMAGE_BITMAP, 475, 320, LR_LOADFROMFILE);
			SendDlgItemMessage(hWnd, caguai, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Bip7);
			if(mini!=NULL)
				addfake();
	}
	case WM_TIMER:
		{
			int daday, dames, daaño, dahora, damin;
			SYSTEMTIME systemTime;
			GetLocalTime(&systemTime);
			if(seLeyo!=true)
			{
			if((mini!=NULL)&&(dini!=NULL))
			{
				daux=dini;
				while(daux!=NULL)
				{
					daday= atoi(daux->dias);
					dames= atoi(daux->mess);
					daaño= atoi(daux->año);
					dahora= atoi(daux->horas);
					damin= atoi(daux->minus);
					if((daday<=systemTime.wDay)&&(dames<=systemTime.wMonth)&&(daaño<=systemTime.wYear)&&(((dahora<=systemTime.wHour)&&(damin<= systemTime.wMinute))||(dahora<systemTime.wHour)))
					{
						DialogBox(hinstance, MAKEINTRESOURCE(IDD_DIALOG8), hWnd, (DLGPROC)MCit);
						savedate();
						break;
					}
					daux=daux->sig;
				}
			}
		}
			break;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case Registrars:
			{
			DialogBox(hinstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)Registro);
			break;
			}
			case Contacs:
			{
			DialogBox(hinstance, MAKEINTRESOURCE(IDD_DIALOG4), hWnd, (DLGPROC)Contactos);
			break;
			}
			case CrearCategorias:
			{
			DialogBox(hinstance, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, (DLGPROC)Categoria);
			break;
			}
			case CrearCitas:
			{
			DialogBox(hinstance, MAKEINTRESOURCE(IDD_DIALOG6), hWnd, (DLGPROC)Citas);
			break;
			}
			case TonoCitas:
			{
			DialogBox(hinstance, MAKEINTRESOURCE(IDD_DIALOG5), hWnd, (DLGPROC)Musica);
			break;
			}
			case Salir:
			{
			EndDialog(hWnd, 0);
			break;
			}
			}
		break;
		}
		case WM_CLOSE:
			DestroyWindow(hWnd);	//hWnd es un puntero a la ventana, yle decimos que destruya la ventana a la que apunta
			return true;
	case WM_DESTROY:
		PostQuitMessage(0);
		return true;
	}
	return false;
}
BOOL CALLBACK Registro(HWND hdWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP hBmp;
	static HWND hPic=0;

	switch(msg)
	{
		case WM_CTLCOLORDLG:
		 return (LONG)g_hbrBackground;

		 case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 0, 0));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (LONG)g_hbrBackground;
    }

		case WM_INITDIALOG:
			{

					HWND combobo= GetDlgItem(hdWnd, IDC_COMBO1);
					ctaux= cini;
					for( int i=0; ctaux!=NULL; i++) {
					SendMessage(combobo, CB_ADDSTRING, i, (LPARAM)ctaux->Ncat);
					ctaux=ctaux->sig;
		}
					
				hPic = GetDlgItem(hdWnd, IDC_PICTURE);
				
			}

	case WM_COMMAND:
		switch(wParam)
		{
			case IDC_BUSCAR:
					{
						   ofn.lStructSize = sizeof(OPENFILENAME);
							ofn.hwndOwner = hdWnd;
							ofn.lpstrDefExt = "txt";
							ofn.lpstrFile = archivo;
							//ofn.lpstrFile[0] = '\0';
							ofn.nMaxFile = MAX_PATH;
							ofn.lpstrFilter = filtro;
							ofn.nFilterIndex = 0;
							ofn.lpstrInitialDir = dirinicial;
							ofn.lpstrTitle = titulo;
							ofn.Flags = OFN_SHOWHELP;

						if (GetOpenFileName(&ofn) == TRUE)
						   {
							
							strcpy(jongkey, ofn.lpstrFile);
							
							hBmp = (HBITMAP)LoadImage(NULL, archivo, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
							SendMessage(hPic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);
							
						   }
						   else
							   MessageBox(0, "No eligio ninguna imagen", "¡HEY! ¡LISTEN!", MB_OK | MB_ICONINFORMATION);
						   return true;
					}
			
		case IDOK:
			{
			char cat1[50], nombres1[50],apellidosp1[50], apellidosm1[50], direc1[100],telefono1[20], celular1[20];

				int cate = SendDlgItemMessage(hdWnd, IDC_COMBO1 , CB_GETCURSEL,0,0);

				SendDlgItemMessage(hdWnd, IDC_COMBO1 , CB_GETLBTEXT, cate, (LPARAM)cat1); 
				GetWindowText(GetDlgItem(hdWnd, IDC_Nom1), (LPSTR)nombres1, 50);
				GetWindowText(GetDlgItem(hdWnd, IDC_AP1), (LPSTR)apellidosp1, 50);
				GetWindowText(GetDlgItem(hdWnd, IDC_AM1), (LPSTR)apellidosm1, 50);
				GetWindowText(GetDlgItem(hdWnd, IDC_Dir1), (LPSTR)direc1, 50);
				GetWindowText(GetDlgItem(hdWnd, IDC_Tel1), (LPSTR)telefono1, 20);
				GetWindowText(GetDlgItem(hdWnd, IDC_Cel1), (LPSTR)celular1, 20);
				
				if((strcmp(cat1,"")==0)&&
					(strcmp(nombres1, "")==0)&&
					(strcmp(apellidosp1, "")==0)&&
					(strcmp(apellidosm1, "")==0)&&
					(strcmp(direc1,"")==0)&&
					(strcmp(telefono1,"")==0)&&
					(strcmp(celular1,"")==0)&&
					(strcmp(archivo, "")==0))
				{
					MessageBox(hdWnd, "Llene todos los campos", "Falta Información",MB_ICONWARNING);
					break;
				}
				registrar(cat1, count, nombres1, apellidosp1, apellidosm1, direc1, telefono1, celular1, archivo);
				count++;
				guardar();
				
				SetDlgItemText(hdWnd, IDC_Nom1, "");
				SetDlgItemText(hdWnd, IDC_AP1, "");
				SetDlgItemText(hdWnd, IDC_AM1, "");
				SetDlgItemText(hdWnd, IDC_Dir1, "");
				SetDlgItemText(hdWnd, IDC_Tel1, "");
				SetDlgItemText(hdWnd, IDC_Cel1, "");
				SetDlgItemText(hdWnd, IDC_PICTURE, "");

				EndDialog(hdWnd, 0);
				break;
		
				break;
			}
		case IDCANCEL:
			EndDialog(hdWnd, 0);
			break;
		}
			break;
			
	case WM_CLOSE:
		EndDialog(hdWnd, 0);
		break;
		}
	return false;
	}
BOOL CALLBACK Categoria(HWND hdWnd2, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CTLCOLORDLG:
		 return (LONG)g_hbrBackground1;

		 case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 0, 0));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (LONG)g_hbrBackground1;
    }

		case WM_INITDIALOG:
			{

				Bip2 = (HBITMAP)LoadImage(NULL, "c:\yo1.bmp", IMAGE_BITMAP, 150, 200, LR_LOADFROMFILE);
				SendDlgItemMessage(hdWnd2, PicYo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Bip2);
				if(cini==NULL)
			{
		HWND hwndList = GetDlgItem(hdWnd2, CatLista);
		char auxlis[30]={"No hay ninguna categoria"};
		int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM) auxlis); 
		SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM) 1);
		}
		else
		{
		ctaux=cini;
		HWND hwndList = GetDlgItem(hdWnd2, CatLista);
		for (int i=0; i<countcat; i++)
		{
			if(ctaux==NULL)
				break;
			int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM) ctaux->Ncat);
		SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM) i);
		ctaux= ctaux->sig;
		}
			}
		return true;
			}

		case WM_COMMAND:
			{
				switch(LOWORD(wParam))
		{
		case CatAgregar:
			{
				char carr[50];
			GetWindowText(GetDlgItem(hdWnd2, CatNueva), (LPSTR)carr, 50);
			ACate(carr);
			countcat++;
			SetDlgItemText(hdWnd2, CatNueva, "");
			saveCat();
			
			//
			if(cini==NULL)
		{
		HWND hwndList = GetDlgItem(hdWnd2, CatLista);
		SendMessage(hwndList, LB_RESETCONTENT,0,0);
		char auxlis[30]={"No hay ninguna categoria"};
		int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM) auxlis); 
		SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM) 1);
		}
		else
		{
		ctaux=cini;
		HWND hwndList = GetDlgItem(hdWnd2, CatLista);
		SendMessage(hwndList, LB_RESETCONTENT,0,0);
		for (int i=0; i<countcat; i++)
		{
			if(ctaux==NULL)
				break;
			int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM) ctaux->Ncat);
		SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM) i);
		ctaux= ctaux->sig;
		}
		}
			//
			break;
			}

		case CatLista:
			{
				switch(HIWORD(wParam))
					{
						case LBN_SELCHANGE:
						{
							int iSelectedId = ListBoxSelec(hdWnd2, CatLista);
							ctaux = cini;
							if(ctaux==NULL)
								break;
							while (ctaux->posiD!= iSelectedId)
							{
								if(ctaux->sig==NULL)
									break;
								ctaux = ctaux->sig;
							}
							
						} break;
					break;
				}
			break;
			}
		case CatEliminar:
			{
			if((cini==NULL)||(ctaux==NULL))
			{
				MessageBox(hdWnd2, "No hay o no ha seleccionado una categoria aún", "Atención", MB_ICONINFORMATION);
				break;
			}
			else
			{
			delcat();
			countcat--;
			HWND hwndList = GetDlgItem(hdWnd2, CatLista);
			SendMessage(hwndList, LB_RESETCONTENT, 0, 0 );
			if(cini==NULL)
		{
		HWND hwndList = GetDlgItem(hdWnd2, CatLista);
		char auxlis[30]={"No hay ninguna categoria"};
		int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM) auxlis); 
		SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM) 1);
		}
		else
		{
		ctaux=cini;
		HWND hwndList = GetDlgItem(hdWnd2, CatLista);
		for (int i=0; i<countcat; i++)
		{
			if(ctaux==NULL)
				break;
			int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM) ctaux->Ncat);
			SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM) i);
			ctaux= ctaux->sig;
		}
		}
			break;
			}
			}
			break;
		}
		break;

			case WM_CLOSE:
			EndDialog(hdWnd2, 0);
			break;
		  }
		
	}

		return false;
}
BOOL CALLBACK Contactos(HWND hdWnd3, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CTLCOLORDLG:
		 return (LONG)g_hbrBackground1;

		 case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 0, 0));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (LONG)g_hbrBackground1;
    }

	case WM_INITDIALOG:
		{
			Bip3 = (HBITMAP)LoadImage(NULL, "c:\hosky.bmp", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
			SendDlgItemMessage(hdWnd3, fotocaguai , STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Bip3);

			if(inicio==NULL)
		{
		HWND hwndList = GetDlgItem(hdWnd3, IDC_LCONT);
		char auxlis[30]={"No hay contactos"};
		int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM) auxlis); 
		SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM) 1);
		}
		else
		{
		tempo=inicio;
		HWND hwndList = GetDlgItem(hdWnd3, IDC_LCONT);
		for (int i=0; i<count; i++)
		{
			if(tempo==NULL)
				break;
		int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM) tempo->nombre);
		SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM) i);
		tempo = tempo->sig;
		}
		}
		}
		return true;
	
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_LCONT:
				{
					switch(HIWORD(wParam))
					{
				case LBN_SELCHANGE:
						{
							int iSelectedId = ListBoxSelec(hdWnd3, IDC_LCONT);
							tempo = inicio;
							if(tempo==NULL)
								break;
							while (tempo->key2 != iSelectedId)
							{
								if(tempo->sig==NULL)
									break;
								tempo = tempo->sig;
							}
							SetDlgItemText(hdWnd3, IDC_EDIT1, tempo->nombre);
							
						} 
						break;
					}
					break;
				}
			case ContM:
				{
					if(tempo ==NULL)
					{
						MessageBox(hdWnd3, "No hay contacto", "Archivo no encontrado", MB_ICONINFORMATION);
						HWND hwndList = GetDlgItem(hdWnd3, IDC_LCONT);
						SendMessage(hwndList, LB_RESETCONTENT, 0, 0 );
						if(inicio==NULL)
		{
		HWND hwndList = GetDlgItem(hdWnd3, IDC_LCONT);
		char auxlis[30]={"No hay nada"};
		int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM) auxlis); 
		SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM) 1);
		}
		else
		{
		tempo=inicio;
		HWND hwndList = GetDlgItem(hdWnd3, IDC_LCONT);
		for (int i=0; i<count; i++)
		{
			if(tempo==NULL)
				break;
		int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM) tempo->nombre);
		SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM) i);
		tempo = tempo ->sig;
		}
		}
						break;
					}
					else
					{
				DialogBox(hinstance, MAKEINTRESOURCE(IDD_DIALOG2), hdWnd3, (DLGPROC) MostrarC);
				guardar();
				break;
					}
				}
			case ContEl:
				{
					HWND hwndList = GetDlgItem(hdWnd3, IDC_LCONT);
					eliminar();
					count--;
					SendMessage(hwndList, LB_RESETCONTENT, 0, 0 );
					if(inicio==NULL)
		{
		HWND hwndList = GetDlgItem(hdWnd3, IDC_LCONT);
		char auxlis[30]={"No hay nada"};
		int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM) auxlis); 
		SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM) 1);
		}
		else
		{
		tempo=inicio;
		HWND hwndList = GetDlgItem(hdWnd3, IDC_LCONT);
		for (int i=0; i<count; i++)
		{
			if(tempo==NULL)
				break;
		int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM) tempo->nombre);
		SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM) i);
		tempo= tempo->sig;
		}
		}
				guardar();
				break;
				}
	case ContV:
		EndDialog(hdWnd3, 0);
		break;
			}
	break;
	
	}
	
	case WM_CLOSE:
			EndDialog(hdWnd3, 0);
			break;
	}
	
	return false;

}
BOOL CALLBACK MostrarC(HWND hWndMc, UINT msg, WPARAM wParam,LPARAM lParam)
{
	switch (msg)
	{
		case WM_CTLCOLORDLG:
		 return (LONG)g_hbrBackground;

		 case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 0, 0));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (LONG)g_hbrBackground;
    }
		case WM_INITDIALOG:
			{
				
				ctaux=cini;

				for(int i=0; ctaux!=NULL; i++)
				{
					SendDlgItemMessage(hWndMc, IDC_COMBO2, CB_ADDSTRING, i, (LPARAM)ctaux->Ncat );
					ctaux= ctaux->sig;
				}

				static HBITMAP picker;
				strcpy(Name, tempo->foto);
				picker= (HBITMAP)LoadImage(NULL, Name, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
				SendDlgItemMessage(hWndMc, fotokguai, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)picker);

				SetDlgItemText(hWndMc, IDC_categoria, tempo->categoria);
				SetDlgItemText(hWndMc, IDC_Nom2, tempo->nombre);
				SetDlgItemText(hWndMc, IDC_AP2,  tempo->apellidop);
				SetDlgItemText(hWndMc, IDC_AM2,  tempo->apellidom);
				SetDlgItemText(hWndMc, IDC_Dir2, tempo->direccion);
				SetDlgItemText(hWndMc, IDC_Tel2, tempo->tel);
				SetDlgItemText(hWndMc, IDC_Cel2, tempo->cel);
			}
case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
		case IDOKMC:
			{
				char categors[50], irumu[50], appa[50], omma[50],home[100], celu[20], phone[20];

				int cate = SendDlgItemMessage(hWndMc, IDC_COMBO2, CB_GETCURSEL,0,0);

				GetWindowText(GetDlgItem(hWndMc, IDC_Nom2), (LPSTR)irumu, 50);
				GetWindowText(GetDlgItem(hWndMc, IDC_AP2), (LPSTR)appa, 50);
				GetWindowText(GetDlgItem(hWndMc, IDC_AM2), (LPSTR)omma, 50);
				GetWindowText(GetDlgItem(hWndMc, IDC_Dir2), (LPSTR)home, 100);
				GetWindowText(GetDlgItem(hWndMc, IDC_Tel2), (LPSTR)celu, 20);
				GetWindowText(GetDlgItem(hWndMc, IDC_Cel2), (LPSTR)phone, 20);
				
				if(cate>=0)
					SendDlgItemMessage(hWndMc, IDC_COMBO2, CB_GETLBTEXT, cate, (LPARAM)categors);
				else
					GetWindowText(GetDlgItem(hWndMc, IDC_categoria), (LPSTR)categors, 50);
				
				if((strcmp(irumu,"")==0)&&
					(strcmp(appa, "")==0)&&
					(strcmp(omma, "")==0)&&
					(strcmp(home, "")==0)&&
					(strcmp(celu,"")==0)&&
					(strcmp(phone, "")==0)) {
					MessageBox(hWndMc, "Llene todos los campos", "Falta Información",MB_ICONWARNING);
					break;
				}
				strcpy(tempo->categoria, categors);
				strcpy(tempo->nombre, irumu);
				strcpy(tempo->apellidop,appa );
				strcpy(tempo->apellidom,omma);
				strcpy(tempo->direccion,home);
				strcpy(tempo->cel, celu);
				strcpy(tempo->tel, phone);
				strcpy(tempo->foto, Name);
				MessageBox(hWndMc, "Se a agregado correctamente", "Información",MB_OK);
				EndDialog(hWndMc, 0);
				break;
			}
			break;

		}
			break;
	}
case WM_CLOSE:
		EndDialog(hWndMc, 0);
		break;
	}
	return false;
}
BOOL CALLBACK Musica(HWND hdWndAm, UINT msg, WPARAM wParam,LPARAM lParam)
{
	switch (msg)
	{
		case WM_CTLCOLORDLG:
		 return (LONG)g_hbrBackground;

		 case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 0, 0));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (LONG)g_hbrBackground;
    }
	case WM_INITDIALOG:
		{
			Bip5 = (HBITMAP)LoadImage(NULL, "c:\grr.bmp", IMAGE_BITMAP, 220, 200, LR_LOADFROMFILE);
			SendDlgItemMessage(hdWndAm, picji , STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Bip5);

			addfake();
		//	EnableWindow( GetDlgItem( hdWndAm, MusAgregar), FALSE);
			HWND hwndList = GetDlgItem(hdWndAm, MusLista);
			showlist(hwndList);
		}
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
	case MusBuscar:
		{
			SetDlgItemText(hdWndAm, MusNueva, "");
			HWND Musicc= GetDlgItem(hdWndAm, MusLista);
			search(hdWndAm, Musicc);
			if(Name==NULL)
				break;
			else
			{
			SetDlgItemText(hdWndAm, MusNueva , Name);
			EnableWindow( GetDlgItem( hdWndAm, MusNueva), TRUE);
			}
			break;
		}
	case MusAgregar:
		{
			AgMu(Name);
			addfake();
			countmu++;
			saveMus();
			HWND hwndList = GetDlgItem(hdWndAm, MusLista);
			SetDlgItemText(hdWndAm, MusNueva, "");
			//EnableWindow( GetDlgItem( hdWndAm, MusBuscar), FALSE);
			SendMessage(hwndList, LB_RESETCONTENT, 0, 0 );
			showlist(hwndList);
			break;
		}
	case MusLista:
		{
			switch(HIWORD(wParam))
					{
			case LBN_SELCHANGE:
						{
							int iSelectedId = ListBoxSelec(hdWndAm, MusLista);
							maux = mini;
							if(maux==NULL)
								break;
							while (maux->id != iSelectedId)
							{
								if(maux->sig==NULL)
									break;
								maux = maux->sig;
							}
						} 
						break;
				}
			break;
		}
	case Play:
		{
			strcpy(Name, "");
			strcpy(Name, "open c:\0");
			strcat(Name, DeleteChar(maux->NoMusic));
			strcat(Name, ".mp3 alias ke");
			mciSendString(Name, NULL, 0, 0);
			strcpy(Name, "play ke");
			mciSendString("stop alarma", NULL, 0, 0);
			mciSendString("play ke", NULL, 0, 0);
			break;
		}
	case Stop:
		{
			mciSendString("close ke", NULL, 0, 0);
			mciSendString("play alarma", NULL, 0, 0);
			break;
		}
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hdWndAm, 0);
		break;
	}
	return false;
}
BOOL CALLBACK Citas(HWND hWndad, UINT msg, WPARAM wParam,LPARAM lParam)
{
	switch (msg)
	{
		case WM_CTLCOLORDLG:
		 return (LONG)g_hbrBackground;

		 case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 0, 0));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (LONG)g_hbrBackground;
    }
	case WM_INITDIALOG:
		{
		Bip4 = (HBITMAP)LoadImage(NULL, "c:\doge.bmp", IMAGE_BITMAP, 200, 300, LR_LOADFROMFILE);
			SendDlgItemMessage(hWndad, picturek , STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Bip4);
			addfake();
		HWND combobo= GetDlgItem(hWndad, Tono);
		faux= fini;
		for( int i=0; faux!=NULL; i++)
		{
		SendMessage(combobo, CB_ADDSTRING, i, (LPARAM)faux->FaMus);
		faux=faux->sig;
		}
		HWND conbobo= GetDlgItem(hWndad, CitaCon);
		tempo = inicio;
		for( int i=0; tempo!=NULL; i++)
		{
			SendMessage(conbobo, CB_ADDSTRING, i, (LPARAM)tempo->nombre);
		tempo=tempo->sig;
		}
		break;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
		{	
	case IDC_BUTTON1:
		{
			int Nomu = SendDlgItemMessage(hWndad, Tono, CB_GETCURSEL,0,0);
			int Nocon = SendDlgItemMessage(hWndad, CitaCon , CB_GETCURSEL,0,0);

			char NomCi[25], Notes[256], day[3], month[3], anio[5], hour[3], min[3], muid[25], conid[25];

			GetWindowText(GetDlgItem(hWndad, NomCita), (LPSTR)NomCi, 25);
			GetWindowText(GetDlgItem(hWndad, notas), (LPSTR)Notes, 256);
			GetWindowText(GetDlgItem(hWndad, dia), (LPSTR)day, 3);
			GetWindowText(GetDlgItem(hWndad, mes), (LPSTR)month, 3);
			GetWindowText(GetDlgItem(hWndad, year), (LPSTR)anio, 5);
			GetWindowText(GetDlgItem(hWndad, hora), (LPSTR)hour, 3);
			GetWindowText(GetDlgItem(hWndad, minuto), (LPSTR)min, 3);
			SendDlgItemMessage(hWndad, Tono, CB_GETLBTEXT, Nomu, (LPARAM)muid);
			SendDlgItemMessage(hWndad, CitaCon, CB_GETLBTEXT, Nocon, (LPARAM)conid);

			if((strcmp(NomCi, "")==0)&&
				(strcmp(Notes,"")==0)&&
				(strcmp(day,"")==0)&&
				(strcmp(month, "")==0)&&
				(strcmp(anio, "")==0)&&
				(strcmp(hour,"")==0)&&
				(strcmp(min,"")==0)&&
				(strcmp(muid,"")==0)&&
				(strcmp(conid,"")==0))
			{
				MessageBox(hWndad, "Llene todos los campos", "Falta Información",MB_ICONSTOP);
				break;
			}
			else
			{
				adddate(NomCi, Notes, day, month, anio, hour, min, muid, conid);
				countd++;
				savedate();
				MessageBox(hWndad, "Los datos se han llenado correctamente", "Éxito",MB_OK);
			}
			EndDialog(hWndad, 0);
			break;
		}
			break;
	case ID_Volver:
		EndDialog(hWndad,0);
		break;
		}
			break;
	}
	case WM_CLOSE:
		EndDialog(hWndad, 0);
		break;
	}
	return false;
}
BOOL CALLBACK MCit(HWND hWndmda, UINT msg, WPARAM wParam,LPARAM lParam)
{
	switch (msg)
	{
		
	case WM_CTLCOLORDLG:
		 return (LONG)g_hbrBackground;

		 case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 0, 0));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (LONG)g_hbrBackground;
    }
	case WM_INITDIALOG:
	{

		Bip8 = (HBITMAP)LoadImage(NULL, "c:\me1.bmp", IMAGE_BITMAP, 200, 150, LR_LOADFROMFILE);
		SendDlgItemMessage(hWndmda, jiji , STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Bip8);

		char botellacruji[15];
		SetDlgItemText(hWndmda, AlarmCit, daux->Namdate);
		SetDlgItemText(hWndmda, AlarmCon, daux->per);
		SetDlgItemText(hWndmda, AlarmNotas, daux->Nota);
		strcpy(botellacruji, daux->dias);
		strcat(botellacruji, "/");
		strcat(botellacruji, daux->mess);
		strcat(botellacruji,"/");
		strcat(botellacruji, daux->año);
		SetDlgItemText(hWndmda, AlarmFecha, botellacruji);
		strcpy(botellacruji, daux->horas);
		strcat(botellacruji, ":");
		strcat(botellacruji, daux->minus);
		SetDlgItemText(hWndmda, AlarmHora, botellacruji);

		faux=fini;
		int coin;
		for(int i=0; i<countmu; i++)
		{
			coin=i;
			if(strcmp(faux->FaMus,daux->MuAl)==0)
				break;
			faux= faux->sig;
		}
		maux=mini;
		for(int j=0; j<coin; j++)
			maux=maux->sig;
		KillTimer(hWndmda,1);
		strcpy(Name, "");
		strcpy(Name, "open c:\0");
		strcat(Name, DeleteChar(maux->NoMusic));
		strcat(Name, ".mp3 alias ke");
		mciSendString(Name, NULL, 0, 0);
		strcpy(Name, "play ke");
		mciSendString("stop alarma", NULL, 0, 0);
		mciSendString("play ke", NULL, 0, 0);
		seLeyo=true;
		
	}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDOKK:
				{
					mciSendString("close ke", NULL, 0, 0);
					mciSendString("play alarma", NULL, 0, 0);
					deldate();
					EndDialog(hWndmda, 0);
				}
			}
			break;
		}
	case WM_CLOSE:
		EndDialog(hWndmda, 0);
		break;
	}
	return false;
}
//---------Funciones de contactos---------------------------------------------------------------------------------
void registrar(char cats[50], int keys, char nom[50], char ap[50], char am[50], 
	char di[100], char te[20], char ce[20], char arc[256])
{
	if(inicio==NULL)
	{
	inicio= new persona;
	strcpy(inicio->categoria, cats);
	inicio->key2= keys;
	strcpy(inicio->nombre, nom);
	strcpy(inicio->apellidop, ap);
	strcpy(inicio->apellidom, am);
	strcpy(inicio->direccion, di);
	strcpy(inicio->tel, te);
	strcpy(inicio->cel, ce);
	strcpy(inicio->foto, arc);
	inicio->ant=NULL;
	inicio->sig=NULL;
	final=inicio;
	}
	else
	{
		final->sig= new persona;
		final->sig->ant= final;
		final= final->sig;
		strcpy(final->categoria, cats);
		final->key2= keys;
		strcpy(final->nombre, nom);
		strcpy(final->apellidop, ap);
		strcpy(final->apellidom, am);
		strcpy(final->direccion, di);
		strcpy(final->tel, te);
		strcpy(final->cel, ce);
		strcpy(final->foto, arc);
		final->sig=NULL;
	}
}
void guardar()
{
ofstream Data("ReporteAgenda.txt");
Data<<count<<endl;
tempo= inicio;
while(tempo!=NULL)
{
	Data<<tempo->categoria<<endl;
	Data<<tempo->key2<<endl;
	Data<<tempo->nombre<<endl;
	Data<<tempo->apellidop<<endl;
	Data<<tempo->apellidom<<endl;
	Data<<tempo->direccion<<endl;
	Data<<tempo->tel<<endl;
	Data<<tempo->cel<<endl;
	Data<<tempo->foto<<endl;
	tempo=tempo->sig;
}
Data.close();
}
void eliminar()
{
	persona *hope;
	if((tempo->ant==NULL)&&(tempo->sig!=NULL))// es el primero
	{
		inicio=tempo->sig;
		inicio->ant=NULL;
		delete tempo;
		tempo=inicio;
		while(tempo!=NULL)
		{
			tempo->key2--;
			tempo=tempo->sig;
		}
	}
	else
	{
	if((tempo->ant==NULL)&&(tempo->sig==NULL))
	{
	delete tempo;
	inicio=NULL;
	final=NULL;
	tempo=NULL;
	}
	else
	{
	if((tempo->ant!=NULL)&&(tempo->sig!=NULL))
	{
		hope=tempo->sig;
		tempo->ant->sig=tempo->sig;
		tempo->sig->ant=tempo->ant;
		delete tempo;
		
		while (hope!=NULL)
		{
			hope->key2--;
			hope= hope->sig;
		}

	}
	else
	{
	if(tempo->sig==NULL)
	{
		tempo->ant->sig=NULL;
		final=tempo->ant;
		delete tempo;
	}
	
	}
	}
}
}
BOOL load(HWND win)
{
char war[25];
int lopiti=0;
fstream Data("ReporteAgenda.txt");

if(!Data)
{
	MessageBox(win, "Archivo no encontrado", "Falta Info", MB_ICONWARNING);
	return true;
}
Data.getline(war, sizeof(Data));
count= atoi(war);

while(lopiti!=count)
		{
			if(inicio==NULL)
			{
				inicio= new persona;
				inicio->ant=NULL;
				
				Data.getline(war, sizeof(Data));
				Data.getline(inicio-> categoria, sizeof(Data));
				inicio->key2= atoi(war);
				Data.getline(inicio->nombre, sizeof(Data));
				Data.getline(inicio->apellidop, sizeof(Data));
				Data.getline(inicio->apellidom, sizeof(Data));
				Data.getline(inicio->direccion, sizeof(Data));
				Data.getline(inicio->tel, sizeof(Data));
				Data.getline(inicio->cel, sizeof(Data));
				Data.getline(inicio->foto, sizeof(Data));

				inicio->sig= NULL;
				tempo = final = inicio;
				lopiti++;
			}
			else
			{
				tempo = final;
				final = new persona;
				final -> ant = tempo;
				tempo->sig=final;
				final->sig=NULL;
				
				Data.getline(war, sizeof(Data));
				Data.getline(final->categoria, sizeof(Data));
				final->key2 = atoi(war);
				Data.getline(final->nombre, sizeof(Data));
				Data.getline(final->apellidop, sizeof(Data));
				Data.getline(final->apellidom, sizeof(Data));
				Data.getline(final->direccion, sizeof(Data));
				Data.getline(final->tel, sizeof(Data));
				Data.getline(final->cel, sizeof(Data));
				Data.getline(final->foto, sizeof(Data));

				tempo = final;
				lopiti++;
			
			}
		}
		Data.close();
		return true;
}
//Funciones para categorias---------------------------------------------------------------------------------------
void ACate(char catt[])
{
	if(cini==NULL)
	{
		cini= new categos;
		cini->ant= NULL;
		strcpy(cini->Ncat, catt);
		cini->posiD=0;
		cini->sig=NULL;
		clast= cini;
	}
	else
	{
	ctaux=clast;
	clast= new categos;
	ctaux->sig=clast;
	clast->sig=NULL;
	strcpy(clast->Ncat, catt);
	clast->posiD=ctaux->posiD+1;
	clast->ant=ctaux;
	}
}
void saveCat()
{
	ofstream Cat("Categorias.txt");
Cat<<countcat<<endl;
ctaux= cini;
while(ctaux!=NULL)
{
	Cat<<ctaux->Ncat<<endl;
	Cat<<ctaux->posiD<<endl;
	ctaux= ctaux->sig;
}
Cat.close();
}
void delcat()
{
	categos *hope;
	if((ctaux->ant==NULL)&&(ctaux->sig==NULL))
	{
		cini=NULL;
		clast=NULL;
		delete ctaux;
		ctaux=NULL;
	}
	else
	{
		if((ctaux->ant==NULL)&&(ctaux->sig!=NULL))
		{
			cini=ctaux->sig;
			delete ctaux;
			cini->ant=NULL;
			ctaux=cini;
			while(ctaux!=NULL)
			{
				ctaux->posiD--;
				ctaux=ctaux->sig;
			}
		}
		else
		{
			if((ctaux->sig!=NULL)&&(ctaux->ant!=NULL))
			{
				ctaux->sig->ant=ctaux->ant;
				ctaux->ant->sig=ctaux->sig;
				hope=ctaux->sig;
				delete ctaux;
				while(hope!=NULL)
				{
					hope->posiD--;
					hope=hope->sig;
				}
			}
			else
			{
				if(ctaux->sig==NULL)
				{
					clast=ctaux->ant;
					clast->sig=NULL;
					delete ctaux;
				}
			}
		}
	}
}
BOOL loadcat(HWND wCat)
{
char war[25];
int lopiti=0;
fstream Cat("Categorias.txt");

if(!Cat)
{
	MessageBox(wCat, "No hay Categorias", "Falta Info", MB_ICONWARNING);
	return true;
}
Cat.getline(war, sizeof(Cat));
countcat= atoi(war);

while(lopiti!=countcat)
		{
			if(cini==NULL)
			{
				cini= new categos;
				cini->ant=NULL;
				
				Cat.getline(cini->Ncat, sizeof(Cat));
				Cat.getline(war, sizeof(Cat));
				cini->posiD= atoi(war);

				cini->sig= NULL;
				ctaux=clast= cini;
				lopiti++;
			}
			else
			{
				ctaux= clast;
				clast= new categos;
				clast->ant=ctaux;
				ctaux->sig=clast;
				clast->sig=NULL;
				
				Cat.getline(clast->Ncat, sizeof(Cat));
				Cat.getline(war, sizeof(Cat));
				clast->posiD= atoi(war);

				ctaux=clast;
				lopiti++;
				
			
			}
		}
		Cat.close();
		return true;
}
//Funciones para la musica-----------------------------------------------------------------------------------------
void AgMu(char NM[])
{
	if(mini==NULL)
	{
		mini = new musict;
		mini->ant=NULL;
		strcpy(mini->NoMusic, NM);
		mini->id=0;
		mini->sig=NULL;
		mlast=mini;
	}
	else
	{
		maux=mlast;
		mlast= new musict;
		mlast->ant=maux;
		maux->sig=mlast;
		strcpy(mlast->NoMusic, NM);
		mlast->id=maux->id+1;
		mlast->sig=NULL;
	}
}
void saveMus()
{
	ofstream TrackList("Music.txt");
	TrackList<<countmu<<endl;
	maux=mini;
	while(maux!=NULL)
	{
		TrackList<<maux->NoMusic<<endl;
		TrackList<<maux->id<<endl;
		maux= maux->sig;
	}
	TrackList.close();
}
void addfake()
{
	if(fini!=NULL)
	{
	faux=fini;
	while(faux!=NULL)
	{
		if(fini!=NULL)
		{
			fini=fini->sig;
			delete faux;
			faux=fini;
		}
		else
		{
			delete fini;
			flast=NULL;
			fini=NULL;
			faux=NULL;
		}
	}
	}
	maux=mini;
	while(maux!=NULL)
	{
		if(fini==NULL)
		{
			fini= new fakem;
			strcpy(fini->FaMus, DeleteChar(maux->NoMusic));
			fini->sig=NULL;
			fini->ant=NULL;
			flast=fini;
		}
		else
		{
			faux=flast;
			flast= new fakem;
			faux->sig= flast;
			strcpy(flast->FaMus, DeleteChar(maux->NoMusic));
			flast->sig=NULL;
			flast->ant=faux;
		}
		maux=maux->sig;
	}
}
BOOL loadmusic(HWND wMus)
{
	char hope[MAX_PATH];
	int loops=0;
	fstream TrackList("Music.txt");

	if(!TrackList)
	{
		MessageBox(wMus, "No hay Lista de Musica", "Falta Info", MB_ICONWARNING);
		return true;
	}

	TrackList.getline(hope, sizeof(TrackList));
	countmu= atoi(hope);

	while(loops!=countmu)
	{
		if(mini==NULL)
		{
			mini= new musict;
			TrackList.getline(mini->NoMusic, sizeof(TrackList));
			TrackList.getline(hope, sizeof(TrackList));
			mini->id= atoi(hope);
			mini->ant=NULL;
			mini->sig=NULL;
			mlast=mini;
			loops++;
		}
		else
		{
			maux=mlast;
			mlast = new musict;
			maux->sig=mlast;
			mlast->ant= maux;
			TrackList.getline(mlast->NoMusic, sizeof(TrackList));
			TrackList.getline(hope, sizeof(TrackList));
			mlast->id=atoi(hope);
			mlast->sig=NULL;
			loops++;
		}
	}
}
//Funciones para las citas-----------------------------------------------------------------------------------------
void deldate()
{
	if((daux->ant==NULL)&&(daux->sig==NULL))
	{
		delete daux;
		dini=NULL;
		dlast=NULL;
		countd--;
	}
	else
	{
		if(daux->ant==NULL)
		{
			dini=dini->sig;
			dini->ant=NULL;
			delete daux;
			countd--;
		}
		else
		{
			if(daux->sig==NULL)
			{
				dlast=dlast->ant;
				dlast->sig=NULL;
				delete daux;
				countd--;
			}
			else
			{
				if((daux->ant!=NULL)&&(daux->sig!=NULL))
				{
					daux->ant->sig= daux->sig;
					daux->sig->ant= daux->ant;
					delete daux;
					countd--;
				}
			}
		}
	}
	seLeyo=false;
}
void adddate(char dnom[], char dnote[], char dday[], char dmon[], 
	char dyea[], char dhou[], char dmin[], char dmu[], char dc[])
{
	if(dini==NULL)
	{
		dini = new diaa;
		strcpy(dini->Namdate, dnom);
		strcpy(dini->Nota, dnote);
		strcpy(dini->dias, dday);
		strcpy(dini->mess, dmon);
		strcpy(dini->año, dyea);
		strcpy(dini->horas, dhou);
		strcpy(dini->minus, dmin);
		strcpy(dini->MuAl, dmu);
		strcpy(dini->per, dc);
		dini->ant=NULL;
		dini->sig=NULL;
		dlast=dini;
	}
	else
	{
	daux= dlast;
	dlast= new diaa;
	daux->sig= dlast;
	strcpy(dlast->Namdate, dnom);
	strcpy(dlast->Nota, dnote);
	strcpy(dlast->dias, dday);
	strcpy(dlast->mess, dmon);
	strcpy(dlast->año, dyea);
	strcpy(dlast->horas, dhou);
	strcpy(dlast->minus, dmin);
	strcpy(dlast->MuAl, dmu);
	strcpy(dlast->per, dc);
	dlast->sig=NULL;
	dlast->ant= daux;
	}
}
void savedate()
{
	ofstream Cita("Citas.txt");
	Cita<<countd<<endl;
	daux=dini;
	while(daux!=NULL)
	{
		Cita<<daux->Namdate<<endl;
		Cita<<daux->Nota<<endl;
		Cita<<daux->dias<<endl;
		Cita<<daux->mess<<endl;
		Cita<<daux->año<<endl;
		Cita<<daux->horas<<endl;
		Cita<<daux->minus<<endl;
		Cita<<daux->MuAl<<endl;
		Cita<<daux->per<<endl;
		daux= daux->sig;
	}
	Cita.close();
}
BOOL loaddate(HWND wDate)
{
	char morehope[25];
	int looped=0;
	fstream Cita("Citas.txt");
	if(!Cita)
	{
		MessageBox(wDate, "No hay Lista de Citas", "Falta Info", MB_ICONWARNING);
		return true;
	}
	Cita.getline(morehope, sizeof(Cita));
	countd= atoi(morehope);
	while(looped<countd)
	{
		if(dini==NULL)
		{
			dini= new diaa;
			Cita.getline(dini->Namdate, sizeof(Cita));
			Cita.getline(dini->Nota, sizeof(Cita));
			Cita.getline(dini->dias, sizeof(Cita));
			Cita.getline(dini->mess, sizeof(Cita));
			Cita.getline(dini->año, sizeof(Cita));
			Cita.getline(dini->horas, sizeof(Cita));
			Cita.getline(dini->minus, sizeof(Cita));
			Cita.getline(dini->MuAl, sizeof(Cita));
			Cita.getline(dini->per, sizeof(Cita));
			dini->ant=NULL;
			dini->sig=NULL;
			dlast=dini;
			looped=1;
		}
		else
		{
			daux=dlast;
			dlast= new diaa;
			daux->sig=dlast;
			Cita.getline(dlast->Namdate, sizeof(Cita));
			Cita.getline(dlast->Nota, sizeof(Cita));
			Cita.getline(dlast->dias, sizeof(Cita));
			Cita.getline(dlast->mess, sizeof(Cita));
			Cita.getline(dlast->año, sizeof(Cita));
			Cita.getline(dlast->horas, sizeof(Cita));
			Cita.getline(dlast->minus, sizeof(Cita));
			Cita.getline(dlast->MuAl, sizeof(Cita));
			Cita.getline(dlast->per, sizeof(Cita));
			dlast->ant=daux;
			dlast->sig=NULL;
			looped++;
		}
	}

}
//---Otras Funciones-----------------------------------------------------------------------------------------------
int ListBoxSelec(HWND hpar, int idListBox)
{
	HWND hListBox = GetDlgItem(hpar, idListBox);
	int Selec = (int) SendMessage(hListBox, LB_GETCURSEL, NULL, NULL);
	return (int) SendMessage(hListBox, LB_GETITEMDATA, Selec, NULL);
}
void showlist(HWND windo)
{
	faux=fini;
			for(int i=0; i<countmu; i++)
			{
			if(faux==NULL)
					break;
			else
			{
				int pos = (int)SendMessage(windo, LB_ADDSTRING, 0, (LPARAM) faux->FaMus); 

				SendMessage(windo, LB_SETITEMDATA, pos, (LPARAM) i);
				faux=faux->sig;
			}
			}
}
void search(HWND wind, HWND Nwind)
{
				OPENFILENAME ofn;
				char szfile[MAX_PATH];
				HANDLE hf;
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = ghDlg;
				ofn.lpstrFile= szfile;
				ofn.lpstrFile[0] =  '\0';
				ofn.nMaxFile= sizeof(szfile);
				ofn.lpstrFilter = "Todos\0*.*\0MP3\0*.mp3\0WAV\0*.wav\*"; 
				ofn.nFilterIndex=0;
				ofn.lpstrFileTitle= NULL;
				ofn.nMaxFileTitle=0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

				if(GetOpenFileName(&ofn)==TRUE)
				{
					strcpy(Name, ofn.lpstrFile);
					
				}
				else
				MessageBox(0,"No eligió archivo", "OYE!", MB_OK | MB_ICONINFORMATION);
}
char* DeleteChar(char _cadena[100])
{
int slashCount=0;
char Name[100];
int j=0;
for(int i=0; i<strlen(_cadena); i++)
	{
		if(_cadena[i]=='\\')
		{
			slashCount= i+1;
		}
	}
	for(int i=slashCount; _cadena[i]!='\0'; i++)
	{
		Name[j]= _cadena[i];
		j++;
		slashCount=j;
	}
	Name[slashCount--]= '\0';
	Name[slashCount--]= '\0';
	Name[slashCount--]= '\0';
	Name[slashCount--]= '\0';
	Name[slashCount--]= '\0';
	return Name;
}