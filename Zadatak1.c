#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE (128)
#define MAX_LINE (1024)

typedef struct _student {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
}student;

int ProcitajBrojRedakaIzDatoteke(char* nazivDatoteke);
student* AlocirajMemorijuIProcitajStudente(int brStudenata, char* nazivDatoteke);


int main()
{
	int i=0, brojStudenata = 0;
	double relativnibodovi = 0, maxbodovi=0;
	student* studenti = NULL;
	char ImeDatoteke[MAX_SIZE] = {0};


	printf("Unesite naziv datoteke: ");
	scanf("%s",ImeDatoteke);
	puts("");
	
	studenti=AlocirajMemorijuIProcitajStudente(brojStudenata = ProcitajBrojRedakaIzDatoteke(ImeDatoteke) , ImeDatoteke);
	for (i = 0; i < brojStudenata; i++) {
		maxbodovi = maxbodovi + studenti[i].bodovi;
	}

	for (i = 0; i < brojStudenata; i++) {
		relativnibodovi = 0;
		relativnibodovi = (studenti[i].bodovi / maxbodovi) * 100;
		
		printf("%s %s %lf %lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativnibodovi);
	}

	return 0;
}

int ProcitajBrojRedakaIzDatoteke(char* nazivDatoteke) {
	int brojac = 0;
	FILE* datoteka = NULL;
	char buffer[MAX_LINE] = { 0 };

	datoteka = fopen(nazivDatoteke, "r");
	if (!datoteka) {
		printf("GRESKA!!");
		return -1;
	}

	while (!feof(datoteka)) {
		fgets(buffer, MAX_LINE, datoteka);
		brojac++;
	}

	fclose(datoteka);
	return brojac;
}

student* AlocirajMemorijuIProcitajStudente(int brStudenata, char* nazivDatoteke) {
	int brojac = 0;
	FILE* datoteka = NULL;
	student* studenti = NULL;

	studenti = (student*)malloc(brStudenata * sizeof(student));

	datoteka = fopen(nazivDatoteke, "r");
	if (!datoteka) {
		printf("GRESKA!!");
		return NULL;
	}

	while (!feof(datoteka)) {
		fscanf(datoteka," %s %s %lf", studenti[brojac].ime, studenti[brojac].prezime,&studenti[brojac].bodovi);
		brojac++;
	}

	fclose(datoteka);
	return studenti;
}