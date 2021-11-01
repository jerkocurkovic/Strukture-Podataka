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

Pozicija StvoriOsobu();
int DodajNaPocetak(Pozicija Head);
int Ispisi(Pozicija Prvi);
Pozicija PronadiZadnjeg(Pozicija Head);
int DodajNaKraj(Pozicija Head);
Pozicija PronadiOsobuPoPrezimenu(Pozicija Prvi, char* prezime);
Pozicija PronadiOdredenuOsobu(Pozicija Prvi, char* ime, char* prezime, int godinarodenja);
Pozicija PronadiPrethodnika(Pozicija Head, Pozicija Clan);
int BrisiOdredenuOsobu(Pozicija Head, char* ime, char* prezime, int godinarodenja);
int SortirajPoPrezimenu(Pozicija Head);
int UpisiUDatoteku(Pozicija Prvi);
int ProcitajIzDatoteke(Pozicija Head);


int main()
{
	osoba Head = { .ime = {0}, .prezime = {0}, .godinarodenja = 0, .next = NULL };
	Pozicija temp = NULL;
	Pozicija prethodnik = NULL;
	char ime[MAX_SIZE] = { 0 };
	char prezime[MAX_SIZE] = { 0 };
	int godinarodenja = 0;
	int brelemenata = 0;
	int i = 0;
	int odabir = 7;

	printf("\nUnesite broj elemenata vezane liste: ");
	scanf(" %d", &brelemenata);
	puts("");

	for (i = 0; i < brelemenata; i++) {

		DodajNaPocetak(&Head);
	}

	while (odabir != 0) {
		printf("\n1 - Dodaj novu osobu na pocetak liste");
		printf("\n2 - Ispisi listu");
		printf("\n3 - Dodaj novu osobu na kraj liste");
		printf("\n4 - Pronadi osobu u listi(po prezimenu)");
		printf("\n5 - Obrisi odredenu osobu iz liste");
		printf("\n6 - Dodaj novu osobu iza odredene osobe");
		printf("\n7 - Dodaj novu osobu ispred odredene osobe");
		printf("\n8 - Sortiraj listu po prezimenima");
		printf("\n9 - Upisi sve podatke iz vezane liste u datoteku");
		printf("\n10 - Procitaj sve podatke iz datoteke");
		printf("\n0 - Kraj");
		puts("");
		scanf(" %d", &odabir);

		if (odabir == 1)
			DodajNaPocetak(&Head);

		else if (odabir == 2)
			Ispisi(Head.next);

		else if (odabir == 3)
			DodajNaKraj(&Head);

		else if (odabir == 4) {
			printf("\nUnesite prezime trazene osobe: ");
			scanf(" %s", prezime);
			temp = PronadiOsobuPoPrezimenu(Head.next, prezime);
			printf("\nIme: %s\tPrezime: %s\tGodina rodenja: %d", temp->ime, temp->prezime, temp->godinarodenja);
			puts("");

			temp = NULL;
			memset(prezime, 0, MAX_SIZE);
		}

		else if (odabir == 5) {
			printf("\nUnesite ime osobe: ");
			scanf(" %s", ime);
			printf("\nUnesite prezime osobe: ");
			scanf(" %s", prezime);
			printf("\nUnesite godinu rodenja osobe: ");
			scanf(" %d", &godinarodenja);

			BrisiOdredenuOsobu(&Head, ime, prezime, godinarodenja);

			memset(ime, 0, MAX_SIZE);
			memset(prezime, 0, MAX_SIZE);
			godinarodenja = 0;
		}

		else if (odabir == 6) {
			printf("\nUnesite ime osobe iza koje zelite dodati novu osobu: ");
			scanf(" %s", ime);
			printf("\nUnesite prezime osobe iza koje zelite dodati novu osobu: ");
			scanf(" %s", prezime);
			printf("\nUnesite godinu rodenja osobe iza koje zelite dodati novu osobu: ");
			scanf(" %d", &godinarodenja);

			temp = PronadiOdredenuOsobu(&Head, ime, prezime, godinarodenja);
			DodajNaPocetak(temp);

			memset(ime, 0, MAX_SIZE);
			memset(prezime, 0, MAX_SIZE);
			godinarodenja = 0;
			temp = NULL;
		}

		else if (odabir == 7) {
			printf("\nUnesite ime osobe ispred koje zelite dodati novu osobu: ");
			scanf(" %s", ime);
			printf("\nUnesite prezime osobe ispred koje zelite dodati novu osobu: ");
			scanf(" %s", prezime);
			printf("\nUnesite godinu rodenja osobe ispred koje zelite dodati novu osobu: ");
			scanf(" %d", &godinarodenja);

			temp = PronadiOdredenuOsobu(&Head, ime, prezime, godinarodenja);
			prethodnik = PronadiPrethodnika(&Head, temp);
			DodajNaPocetak(prethodnik);

			memset(ime, 0, MAX_SIZE);
			memset(prezime, 0, MAX_SIZE);
			godinarodenja = 0;
			temp = NULL;
			prethodnik = NULL;
		}

		else if (odabir == 8) {

			SortirajPoPrezimenu(&Head);
		}

		else if (odabir == 9) {

			UpisiUDatoteku(Head.next);

		}

		else if (odabir == 10) {
			ProcitajIzDatoteke(&Head);
		}
	}





	return EXIT_SUCCESS;

}

Pozicija StvoriOsobu()
{

	Pozicija NovaOsoba = NULL;
	char ime[MAX_SIZE] = { 0 };
	char prezime[MAX_SIZE] = { 0 };
	int godinarodenja = 0;

	NovaOsoba = (Pozicija)malloc(sizeof(osoba));
	if (!NovaOsoba) {
		printf("\nGRESKA!!!NEMOGUCA ALOKACIJA MEMORIJE\n");
		return NULL;
	}

	printf("\nUnesite ime osobe: ");
	scanf(" %s", ime);
	printf("\nUnesite prezime osobe: ");
	scanf(" %s", prezime);
	printf("\nUnesite godinu rodenja osobe: ");
	scanf(" %d", &godinarodenja);

	strcpy(NovaOsoba->ime, ime);
	strcpy(NovaOsoba->prezime, prezime);
	NovaOsoba->godinarodenja = godinarodenja;

	NovaOsoba->next = NULL;

	return NovaOsoba;
}

int DodajNaPocetak(Pozicija Head)
{
	Pozicija NovaOsoba = StvoriOsobu();
	NovaOsoba->next = Head->next;
	Head->next = NovaOsoba;

	return EXIT_SUCCESS;
}

int Ispisi(Pozicija Prvi)
{
	Pozicija temp = Prvi;
	int brojac = 0;

	while (temp) {
		printf("\n%d. osoba: ", brojac + 1);
		printf("\nIme: %s\tPrezime: %s\tGodina rodenja: %d", temp->ime, temp->prezime, temp->godinarodenja);

		temp = temp->next;
		brojac++;
	}
	puts("");

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

int DodajNaKraj(Pozicija Head)
{
	Pozicija NovaOsoba = NULL;
	Pozicija temp = NULL;

	temp = PronadiZadnjeg(Head);
	NovaOsoba = StvoriOsobu();

	NovaOsoba->next = temp->next;
	temp->next = NovaOsoba;


	return EXIT_SUCCESS;
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

int BrisiOdredenuOsobu(Pozicija Head, char* ime, char* prezime, int godinarodenja)
{

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

int SortirajPoPrezimenu(Pozicija Head)
{
	Pozicija i=Head;
	Pozicija j = NULL;
	Pozicija k = NULL;
	Pozicija temp = NULL;


	while (i->next != k)
	{
		i = Head;
		j = i->next;
		while (j->next != k)
		{
			if (strcmp( j->prezime, j->next->prezime) > 0)
			{
				temp = j->next;
				i->next = temp;
				j->next = temp->next;
				temp->next = j;
				j = temp;
			}
			i = j;
			j = j->next;
		}

		k = j;
	}





	return EXIT_SUCCESS;
}

int UpisiUDatoteku(Pozicija Prvi)
{
	char imedatoteke[MAX_SIZE] = { 0 };
	FILE* pDat = NULL;



	printf("\nUnesite ime datoteke u koju zelite upisati(NAPOMENA: na kraju stavite .txt): ");
	scanf(" %s", imedatoteke);

	pDat = fopen(imedatoteke, "w");

	if (!pDat) {
		printf("GRESKA!!");
		return -1;
	}
	while (Prvi != NULL) {
		fprintf(pDat, "%s\t%s\t%d\n", Prvi->ime, Prvi->prezime, Prvi->godinarodenja);
		Prvi = Prvi->next;
	}

	fclose(pDat);

	return EXIT_SUCCESS;

}

int ProcitajIzDatoteke(Pozicija Head)
{
	char imedatoteke[MAX_SIZE] = { 0 };
	FILE* pDat = NULL;
	Pozicija temp = NULL;
	

	printf("\nUnesite ime datoteke iz koju zelite procitati(NAPOMENA: na kraju stavite .txt): ");
	scanf(" %s", imedatoteke);

	pDat = fopen(imedatoteke, "r");

	if (!pDat) {
		printf("GRESKA!!");
		return -1;
	}

	while (!feof(pDat)) {
		temp = (Pozicija)malloc(sizeof(osoba));
		temp->next = NULL;

		if (!temp) {
			printf("\nGRESKA!!!NEMOGUCA ALOKACIJA MEMORIJE\n");
			return -2;
		}

		

		fscanf(pDat, " %s %s %d", temp->ime, temp->prezime, &temp->godinarodenja);
		temp->next = Head->next;
		Head->next = temp;
		Head = temp;

	}


	fclose(pDat);

	return EXIT_SUCCESS;
}