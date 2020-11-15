#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _student
{
    char imie[25];
    char nazwisko[50];
    char nr_albumu[10];
    char kod_przed[10];
    char nazwa_przed[255];
    float ocena;
    int ects;
} student, *pstudent;

int wczytaj(student dane[100], char *fnazwa)
{
    FILE * fin = fopen(fnazwa, "r");
    int cnt;
    char bufor[1024];
    char *w;

    fgets(bufor, 1023, fin);
    sscanf(bufor, "%d", &cnt);
 
    for (int i=0; i<cnt; i++)
    {
        fgets(bufor, 1023, fin);
        
        w = strtok(bufor, "|");
        strncpy(dane[i].imie, w, 24);

        w = strtok(NULL, "|");
        strncpy(dane[i].nazwisko, w, 49);
        
        w = strtok(NULL, "|");
        strncpy(dane[i].nr_albumu, w, 9);

        w = strtok(NULL, "|");
        strncpy(dane[i].kod_przed, w, 9);

        w = strtok(NULL, "|");
        strncpy(dane[i].nazwa_przed, w, 254);

        w = strtok(NULL, "|");
        dane[i].ocena = atof(w);

        w = strtok(NULL, "|");
        dane[i].ects = atoi(w);
    }

    fclose(fin);
    return cnt;
}

int znajdz(char *szukany_nr, char kod_przed[100][10], int n)
{
    for (int i=0; i<n; i++)
    {
        if (strcmp(szukany_nr, kod_przed[i]) == 0)
            return i;
    }
    return -1;
}

int znajdz_przed(char kod_przed[100][10], student dane[100], int n)
{
    int ile_znal = 0;

    for (int i=0; i <n; i++)
    {
        if (znajdz(dane[i].kod_przed, kod_przed, ile_znal) == -1)
        {
            strncpy(kod_przed[ile_znal], dane[i].kod_przed, 9);
            ile_znal++;
        }
    }
    return ile_znal;
}


void najt_przed(student dane[100], int ile_rekord)
{
    char kod_przed[100][10];
    char nazwa_przed[100][255];
    int ile_przed;

    float sred[100];
    memset(sred, 0, 100 * sizeof (int));

    int ile_dod[100];
    memset(ile_dod, 0, 100 * sizeof (int));
    
    int poz;
    int najl_poz;
    float najlepsza = 6.0f;

    ile_przed = znajdz_przed(kod_przed, dane, ile_rekord);

    for (int i=0; i < ile_rekord; i++)
    {
        poz = znajdz( dane[i].kod_przed, kod_przed, ile_przed );
        strcpy(nazwa_przed[poz],dane[i].nazwa_przed);
        ile_dod[poz]++;
        sred[poz] += dane[i].ocena;
    }   

    for (int i=0; i < ile_przed; i++)
    {
        sred[i] = sred[i]/ile_dod[i];
    }   

    for (int i=0; i < ile_przed; i++)
    {
        if (najlepsza > sred[i])
        {
            najlepsza = sred[i];
            najl_poz = i;
        }
    }

    printf("Najgorsza średnia: %s - %s: %.2f \n", kod_przed[najl_poz], nazwa_przed[najl_poz], sred[najl_poz]);
}

void najl_przed(student dane[100], int ile_rekord)
{
    char kod_przed[100][10];
    char nazwa_przed[100][255];
    int ile_przed;
    
    float sred[100];
    memset(sred, 0, 100 * sizeof (int));
    
    int ile_dod[100];
    memset(ile_dod, 0, 100 * sizeof (int));
    
    int poz;
    int najl_poz;
    float najlepsza = 0.0f;

    ile_przed = znajdz_przed(kod_przed, dane, ile_rekord);
    
    for (int i=0; i < ile_rekord; i++)
    {
        poz = znajdz( dane[i].kod_przed, kod_przed, ile_przed );
        strcpy(nazwa_przed[poz],dane[i].nazwa_przed);
        ile_dod[poz]++;
        sred[poz] += dane[i].ocena;
    }   
   
    for (int i=0; i < ile_przed; i++)
    {
        sred[i] = sred[i]/ile_dod[i];
    }   
  
    for (int i=0; i < ile_przed; i++)
    {
        if (najlepsza < sred[i])
        {
            najlepsza = sred[i];
            najl_poz = i;
        }
    }
  
    printf("Najlepsza średnia: %s - %s: %.2f \n", kod_przed[najl_poz], nazwa_przed[najl_poz], sred[najl_poz]);
}


int main(int argc, char ** argv)
{
    student dane[100];
    
    int ile;
    ile = wczytaj(dane, argv[1]);

    najt_przed(dane, ile);
    najl_przed(dane, ile);
}
