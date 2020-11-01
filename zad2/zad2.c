#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// program zrobiony jest caly w mainie poniewaz nie czuje sie jeszcze pewnie
// z wywolywaniem osobnych funkcji

int main(int argc, char *argv[])
{
    FILE * fin;
    
    int n1, m1, n2, m2;
    
    
    //wczytanie wymiarow pierwszej macierzy oraz przypisanie wartosci
    fin = fopen(argv[1], "r");
    fscanf (fin, "%d %d", &n1, &m1);
    float tab1[n1][m1];
    for(int i=0; i<n1; i++)
    {
        for(int j=0; j<m1; j++)
        fscanf (fin, "%f", &tab1[i][j]);
    }
    
    //wczytanie wymiarow drugiej macierzy oraz przypisanie wartosci
    fin = fopen(argv[2], "r");
    fscanf (fin, "%d %d", &n2, &m2);
    float tab2[n2][m2];
    for(int i=0; i<n2; i++)
    {
        for(int j=0; j<m2; j++)
        fscanf (fin, "%f", &tab2[i][j]);
    }
    //zainicjowanie wymiarow macierzy bedacej wynikiem mnozenia dwoch poprzednich
    float tab3[n1][m2];
    
    if(m1==n2)
     {
         for(int i=0; i<n1; i++) //obliczanie wynikow poszczegolnych komorek macierzy
         {
             for(int j=0; j<m2; j++)
             {
                 tab3[i][j] = 0;
                 for(int k=0; k<n2; k++)
                 {
                     tab3[i][j]=tab3[i][j]+(tab1[i][k]*tab2[k][j]);
                 }
             }
         }
         //wypisanie wyniku mnozenia
         for(int i=0; i<n1; i++)
	{
         	for(int j=0; j<m2; j++)
         		printf("%6.1f", tab3[i][j]);
         	printf("\n");
	}
    }
    else
        printf("Wymiary tablic nie pozwalaja na mnozenie");
}



