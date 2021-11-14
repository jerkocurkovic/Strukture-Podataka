#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 25

struct _stog;
typedef struct _stog* Pozicija;

typedef struct _stog{
	double Element;
	Pozicija Next;
}Stog;

Pozicija StvoriElement( double El);
int DodajIza(Pozicija P, Pozicija NoviElement);
int Push(Pozicija P, double El);
int IzbrisiIza(Pozicija P);
int Pop(double* Odrediste, Pozicija P);
int IzvediOperaciju(Pozicija P, char Operacija);
int IzracunajPostfix(double* Odrediste, char* imedatoteke);

int main()
{
	char imedatoteke[MAX_SIZE] = { 0 };
	double Odrediste = 0;


	printf("\nUnesite naziv datoteke(NAPOMENA: na kraj dodajte .txt): ");
	scanf(" %s", imedatoteke);

	IzracunajPostfix(&Odrediste, imedatoteke);

	printf("\nPostfix iznosi: %lf", Odrediste);
	puts("");

	return EXIT_SUCCESS;
}

Pozicija StvoriElement( double El)
{
	Pozicija NoviElement = NULL;

	NoviElement = (Pozicija)malloc(sizeof(Stog));
	if (!NoviElement)
	{
		printf("\nGreska!Nemoguca alokacija memorije");
		return NULL;
	}

	NoviElement->Element = El;
	NoviElement->Next = NULL;

	return NoviElement;
}

int DodajIza(Pozicija P, Pozicija NoviElement)
{
	NoviElement->Next=P->Next;
	P->Next = NoviElement;

	return EXIT_SUCCESS;
}

int Push(Pozicija P, double El)
{
	Pozicija NoviElement = NULL;

	NoviElement = StvoriElement(El);
	if (!NoviElement)
	{
		return -1;
	}

	DodajIza(P, NoviElement);


	return EXIT_SUCCESS;
}

int IzbrisiIza(Pozicija P)
{
	Pozicija temp = NULL;
	
	temp = P->Next;
	if (!temp)
	{
		return EXIT_SUCCESS;
	}

	P->Next = temp->Next;

	free(temp);

	return EXIT_SUCCESS;

}

int Pop(double* Odrediste, Pozicija P)
{
	Pozicija Prvi = P->Next;

	if (!Prvi)
	{
		printf("\nGreska!Neispravan postfix, provjerite datoteku");
		return -1;
	}

	*Odrediste = Prvi->Element;

	IzbrisiIza(P);

	return EXIT_SUCCESS;

}

int IzvediOperaciju(Pozicija P, char Operacija)
{
	double operand1 = 0;
	double operand2 = 0;
	double rezultat = 0;
	int status1 = EXIT_SUCCESS;
	int status2 = EXIT_SUCCESS;

	status2 = Pop(&operand2, P);
	if (status2 != EXIT_SUCCESS)
	{
		return -2;
	}

	status1 = Pop(&operand1, P);
	if (status1 != EXIT_SUCCESS)
	{
		return -1;
	}

	if (Operacija == '+')
		rezultat = operand1 + operand2;

	else if (Operacija == '-')
		rezultat = operand1 - operand2;

	else if (Operacija == '*')
		rezultat = operand1 * operand2;

	else if (Operacija == '/')
	{
		if (operand2 == 0) {
			printf("\nGreska!Ne smije se dijeliti s 0!");
			return -3;
		}

		rezultat = operand1 / operand2;

	}
	
	else
	{
		printf("\nOva operacija je trenutno nedostupna:(");
		return -4;
	}

	Push(P, rezultat);

	return EXIT_SUCCESS;

}

int IzracunajPostfix(double* Odrediste, char* imedatoteke) 
{
	FILE* pDat = NULL;
	int duljinadatoteke = 0;
	int status = EXIT_SUCCESS;
	double broj = 0;
	char* buffer = NULL;
	char* trenutnibuffer = NULL;
	int brojbajtova = 0;
	char operacija = 0;
	Stog Head = { .Element = 0, .Next = NULL };


	pDat = fopen(imedatoteke, "rb");
	if (!pDat)
	{
		printf("\nGreska pri otvaranju datoteke!");
		return -1;
	}

	fseek(pDat, 0, SEEK_END);
	duljinadatoteke = ftell(pDat);

	buffer = (char*)calloc(duljinadatoteke + 1, sizeof(char));
	if (!buffer)
	{
		printf("\nGreska!Nemoguca alokacija memorije");
		return -2;
	}

	rewind(pDat);
	fread(buffer, sizeof(char), duljinadatoteke, pDat);
	printf("\nProcitano iz datoteke: %s", buffer);
	puts("");
	fclose(pDat);

	trenutnibuffer = buffer;

	while (strlen(trenutnibuffer) > 0) 
	{
		status = sscanf(trenutnibuffer, " %lf %n", &broj, &brojbajtova);

		if (status == 1) 
		{
			Push(&Head, broj);
			trenutnibuffer = trenutnibuffer + brojbajtova;

		}
		else
		{
			sscanf(trenutnibuffer, " %c %n", &operacija, &brojbajtova);
			status = IzvediOperaciju(&Head, operacija);

			if (status != EXIT_SUCCESS)
			{
				free(buffer);

				while (Head.Next != NULL) 
					IzbrisiIza(&Head);

				return -3;
			}
			trenutnibuffer = trenutnibuffer + brojbajtova;
		}
	}

	*Odrediste = Head.Next->Element;

	free(buffer);


	return EXIT_SUCCESS;

}