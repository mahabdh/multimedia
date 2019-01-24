/*
	Name: topologique inverse
	Copyright: 
	Author: Boudah Maha
	Date: 17/01/19 19:45
	Description: 
*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct tableau{
	char a;
	int n;
}tableau;

typedef struct chaine{
	char c;
}chaine;

mission3()
{
	FILE* fichier1 = NULL;
	FILE* fichier2 = NULL;
	fichier1 = fopen ("Equipe_6_mission3_in.txt","r+");
	fichier2 = fopen ("Equipe_6_mission3_out.txt","w+");
	char ch[255]="";
	char c;
	char ch_final[255]="";
	char ch2[255]="";
	int i; int taille; int j;
	if (fichier1!=NULL && fichier2!=NULL)
	{
	fgets(ch,255,fichier1);
	c = ch[0];
	fgets(ch,255,fichier1);
	i=0;
	j=0;
	while (i<strlen(ch))
	{
		if (ch[i]=='+')
		{
			for (j = 0;j<i;j++)
			{
				ch2[j]=ch[j];
			}
		}
		i++;
	}
	i=0;
	int z=0;
	while (i<strlen(ch))
	{
		if (ch[i]=='+')
		{
			for (j=i+1;j<strlen(ch);j++)
			{
				ch_final[z]=ch[j];
				z++;
			}
		}
		i++;
	}
	j=0;
	for (i=0;i<strlen(ch2);i++)
	{
		if (ch2[i]=='1')
		{
			fprintf (fichier2, "%c", c);
		}
		else if (ch2[i]=='0')
		{
			fprintf (fichier2, "%c", ch_final[j]);
			j++;
		}
	}
	}
	if(fichier1 == NULL)
	{
		fichier1 = fopen ("Equipe_6_mission3_in.txt","w+");
		fprintf(fichier1,"ERREUR : le fichier Equipe_6_mission3_in.txt n’existe pas");
	}
	fclose(fichier1);
	fclose(fichier2);
	
	/*****************************************************************************
	*****************************************************************************/
	
	i=0;  j=0; 
	bool trouve = false; //booleen qui va nous indiquer si le caractere existe dans le tableau ou non
	FILE* in = NULL;
	FILE* fichier_final = NULL;
	in = fopen("Equipe_x_mission3_rep_in.txt","r+");
	fichier_final = fopen("Equipe_x_mission3_rep_out.txt","w+");
	//char ch2[255] = "";
	char str[255];
	int fileReadingVerdict; int n;
	if (in!=NULL && fichier_final!=NULL)
	{
		fileReadingVerdict = fgets(str, 255, in) != NULL;
	tableau tab;
	tab.a = str[0];
	tab.n = 1;
	tableau t[26]; int z=2;
	t[1] = tab;
    printf("\nContenu de fich2ier %s\n", str);
    //remplir le tableau avec chaque caractere et son occurence
	for(i=1;i<strlen(str);i++)
	{
		for(j=0;j<26;j++)
		{
			if(t[j].a == str[i])
			{
				t[j].n++;
				trouve = true;
			}
		}
		if(trouve == false)
		{
			t[z].a = str[i]; //si le caractere ne figure pas dans le tableau on le place en fin de tableau
			t[z].n = 1;
			z++;
		}
		trouve = false;
	}
	//ch2ercher le caractere le plus dominant dans la ch
	i =1; int max = 1; char d;
	for(i=0;i<z;i++)
	{
		if (t[i].n > max)
		{
			max = t[i].n;
			d = t[i].a;
		}
	}
	printf("\nla valeur max est %c",d);
	
	//faire le codage topologique
	chaine s[strlen(str)]; j=0; int cpt=0;
	char b = d;
	fprintf(fichier_final,"%c \n",b); //ecrire la valeur dominante
	printf("\nla valeur ecrite dans le fich2ier est %c",b);

	for(i=0;i<strlen(str);i++)
	{
		if(str[i] == d)
		{
			fprintf(fichier_final,"1"); //s'il s'agit de la lettre dominante on ecrit 1
		}
		else
		{
			fprintf(fichier_final,"0");//s'il ne s'agit pas de la lettre dominante on ecrit 0
			s[j].c = str[i];
			j++; cpt++;
		}
	}
	fprintf(fichier_final,"+");
	for(j=0;j<cpt;j++)
	{
		fprintf(fichier_final,"%c",s[j].c); // sinon ecrire les lettres qui ont la valeur 0
	}
	}
	if(in == NULL)
	{
		in = fopen ("Equipe_x_mission3_rep_in.txt","w+");
		fprintf(in,"ERREUR : le fichier Equipe_x_mission3_rep_in.txt n’existe pas");
	}
	fclose(in);
	fclose(fichier_final);

}
int main()
{
	mission3();
	return 0;
}
