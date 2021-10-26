#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (50)

struct _osoba;
typedef struct _osoba* Pozicija;

typedef struct _osoba {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int godinarodenja;
	Pozicija next;
}osoba;

Pozicija StvoriOsobu(char* ime, char* prezime, int godinarodenja);
int DodajNaPocetak(Pozicija Head, char* ime, char* prezime, int godinarodenja);
int Ispisi(Pozicija Prvi);
Pozicija PronadiZadnjeg(Pozicija Head);
Pozicija PronadiOsobuPoPrezimenu(Pozicija Prvi, char* prezime);
int DodajNaKraj(Pozicija Head, char* ime, char* prezime, int godinarodenja);
Pozicija PronadiOdredenuOsobu(Pozicija Prvi, char* ime, char* prezime, int godinarodenja);
Pozicija PronadiPrethodnika(Pozicija Head, Pozicija Clan);
int BrisiOdredenuOsobu(Pozicija Head, char* ime, char* prezime, int godinarodenja);


int main(int argc, char** argv)
{
	osoba Head = { .ime = {0}, .prezime = {0}, .godinarodenja = 0, .next = NULL };
	Pozicija p = &Head;
	

	return EXIT_SUCCESS;
}

Pozicija StvoriOsobu(char* ime, char* prezime, int godinarodenja)
{

	Pozicija NovaOsoba = NULL;

	NovaOsoba = (Pozicija)malloc(sizeof(osoba));
	if (!NovaOsoba) {
		printf("\nGRESKA!!!NEMOGUCA ALOKACIJA MEMORIJE\n");
		return NULL;
	}

	strcpy(NovaOsoba->ime, ime);
	strcpy(NovaOsoba->prezime, prezime);
	NovaOsoba->godinarodenja = godinarodenja;
	NovaOsoba->next = NULL;

	return NovaOsoba;
}

int DodajNaPocetak(Pozicija Head, char* ime, char* prezime, int godinarodenja)
{
	Pozicija NovaOsoba = NULL;

	NovaOsoba = StvoriOsobu(ime, prezime, godinarodenja);

	NovaOsoba->next = Head->next;
	Head->next = NovaOsoba;

	return EXIT_SUCCESS;
}

int Ispisi(Pozicija Prvi)
{
	Pozicija temp = Prvi;

	while (temp) {
		printf("\nIme: %s/tPrezime: %s/tGodina rodenja: %d", temp->ime, temp->prezime, temp->godinarodenja);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

Pozicija PronadiZadnjeg(Pozicija Head)
{
	Pozicija temp = Head;
	while (temp->next) {
		temp = temp->next;
	}

	return temp;
}

Pozicija PronadiOsobuPoPrezimenu(Pozicija Prvi, char* prezime)
{
	Pozicija temp = Prvi;
	while (temp) {

		if (strcmp(temp->prezime, prezime) == 0) {
			return temp;
		}
		temp = temp->next;

	}

	return NULL;
}

int DodajNaKraj(Pozicija Head, char* ime, char* prezime, int godinarodenja)
{
	Pozicija NovaOsoba = NULL;
	Pozicija temp = NULL;

	temp = PronadiZadnjeg(Head);
	NovaOsoba = StvoriOsobu(ime, prezime, godinarodenja);

	NovaOsoba->next = temp->next;
	temp->next = NovaOsoba;


	return EXIT_SUCCESS;
}

Pozicija PronadiOdredenuOsobu(Pozicija Prvi, char* ime, char* prezime, int godinarodenja)
{
	Pozicija temp = Prvi;
	while (temp) {

		if ((strcmp(temp->prezime, prezime) == 0) && (strcmp(temp->ime, ime) == 0) && (temp->godinarodenja == godinarodenja))
		{
			return temp;
		}
		temp = temp->next;

	}

	return NULL;
}

Pozicija PronadiPrethodnika(Pozicija Head, Pozicija Clan)
{
	Pozicija prethodnik = NULL;
	prethodnik = Head;
	Head = Head->next;

	while (Head != NULL && Head != Clan)
	{
		prethodnik = Head;
		Head = Head->next;
	}

	if (Head == NULL)
		return NULL;
	else
		return prethodnik;


}


int BrisiOdredenuOsobu(Pozicija Head, char* ime, char* prezime, int godinarodenja) {

	Pozicija prethodnik = NULL;
	Pozicija temp = NULL;

	temp = PronadiOdredenuOsobu(Head->next, ime, prezime, godinarodenja);
	prethodnik = PronadiPrethodnika(Head, temp);

	if (prethodnik == NULL)
		printf("\nGRESKA!!\n");
	else {
		temp = prethodnik->next;
		prethodnik->next = temp->next;
		free(temp);
	}

	return EXIT_SUCCESS;
}