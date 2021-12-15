#include<stdio.h>
#include<stdlib.h>

struct _stablo;
typedef struct _stablo* StabloP;
typedef struct _stablo {
	int Element;
	StabloP Lijevi;
	StabloP Desni;

}stablo;

StabloP StvoriNovi(int broj);
StabloP DodajNovi(StabloP trenutni, int broj);
int Inorder(StabloP trenutni);
int Preorder(StabloP trenutni);
StabloP PronadiOdredeniElement(StabloP trenutni, int broj);
StabloP PronadiMin(StabloP trenutni);
StabloP ObrisiElement(StabloP trenutni, int broj);

int main()
{
	StabloP root = NULL;
	StabloP potraga = NULL;
	int odabir = 7;
	int broj = 0;

	while (odabir != 0) {
		printf("\nOdaberite naredbu:1)Unos novog elementa 2)Inorder ispis 3)Preorder ispis 4)Postorder ispis 5)Pronalazak odredenog elementa 6)Brisanje odredenog elementa");
		printf(" 0)Izlaz\n");
		scanf("%d", &odabir);

		if (odabir == 1) {

			printf("\nUnesite novi element: ");
			scanf("%d", &broj);

			root = DodajNovi(root, broj);
		}
		
		else if (odabir == 2) {
			printf("\nInorder ispis.....\n");
			Inorder(root);
			puts(" ");
		}

		else if (odabir == 3) {
			printf("\nPreorder ispis.....\n");
			Preorder(root);
			puts(" ");
		}

		else if (odabir == 4) {
			printf("\nPostorder ispis.....\n");
			Postorder(root);
			puts(" ");
		}

		else if (odabir == 5){
			printf("\nUpisite trazeni element: ");
			scanf("%d", &broj);
			potraga = PronadiOdredeniElement(root, broj);
			if (!potraga)
				printf("\nPotraga bezuspjesna!");
			else
				printf("\nPotraga uspjesna!\nTrazeni element = %d", potraga->Element);

		}

		else if (odabir == 6) {
			printf("\nUpisite koji element zelite obrisati: ");
			scanf("%d", &broj);
			printf("\nBrisanje...");
			ObrisiElement(root, broj);
			potraga = PronadiOdredeniElement(root, broj);
			if (!potraga)
				printf("\nBrisanje uspjesno!");
			else
				printf("\nBrisanje bezuspjesna!");
		}

	}

	return EXIT_SUCCESS;
}

StabloP StvoriNovi(int broj) {

	StabloP Novi = NULL;

	Novi = (StabloP)malloc(sizeof(stablo));
	if (!Novi) {
		printf("\nGRESKA!!Neuspjela alokacija memorije!");
		return NULL;
	}

	Novi->Element = broj;
	Novi->Lijevi = NULL;
	Novi->Desni = NULL;

	return Novi;
}

StabloP DodajNovi(StabloP trenutni, int broj)
{
	if (trenutni == NULL) {
		trenutni = StvoriNovi(broj);
		return trenutni;
	}

	else if (trenutni->Element > broj)
		trenutni->Lijevi = DodajNovi(trenutni->Lijevi, broj);

	else if (trenutni->Element < broj)
		trenutni->Desni = DodajNovi(trenutni->Desni, broj);

	return trenutni;
}

int Inorder(StabloP trenutni)
{
	if (trenutni == NULL) 
		return EXIT_SUCCESS;
	
	Inorder(trenutni->Lijevi);
	printf("%d ", trenutni->Element);
	Inorder(trenutni->Desni);

	return EXIT_SUCCESS;
}

int Preorder(StabloP trenutni)
{
	if (trenutni == NULL) 
		return EXIT_SUCCESS;

	printf("%d ", trenutni->Element);
	Preorder(trenutni->Lijevi);
	Preorder(trenutni->Desni);

	return EXIT_SUCCESS;
}

int Postorder(StabloP trenutni)
{
	if (trenutni == NULL)
		return EXIT_SUCCESS;

	Postorder(trenutni->Lijevi);
	Postorder(trenutni->Desni);
	printf("%d ", trenutni->Element);

	return EXIT_SUCCESS;
}

StabloP PronadiOdredeniElement(StabloP trenutni, int broj)
{
	if (trenutni == NULL)
		return NULL;

	else if (trenutni->Element > broj)
		 trenutni = PronadiOdredeniElement(trenutni->Lijevi, broj);

	else if (trenutni->Element < broj)
		 trenutni = PronadiOdredeniElement(trenutni->Desni, broj);
	else
		return trenutni;
}

StabloP PronadiMin(StabloP trenutni)
{
	while (trenutni->Lijevi != NULL)
		trenutni = trenutni->Lijevi;
	
	return trenutni;
}

StabloP ObrisiElement(StabloP trenutni, int broj)
{
	StabloP temp;
	if (trenutni == NULL) {
		printf("\nElement %d ne postoji!", broj);
		return trenutni;
	}
	else if (trenutni->Element > broj)
		trenutni->Lijevi = ObrisiElement(trenutni->Lijevi, broj);

	else if (trenutni->Element < broj)
		trenutni->Desni = ObrisiElement(trenutni->Desni, broj);

	else{

		if (trenutni->Lijevi && trenutni->Desni){
			temp = PronadiMin(trenutni->Desni);
			trenutni->Element = temp->Element;
			trenutni->Desni = ObrisiElement(trenutni->Desni, temp->Element);
		}

		else{
			temp = trenutni;

			if (!trenutni->Lijevi)
				trenutni = trenutni->Desni;

			else if (!trenutni->Desni)
				trenutni = trenutni->Lijevi;

			free(temp);
		}
	}
	return trenutni;
}