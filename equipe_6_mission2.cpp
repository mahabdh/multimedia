/*
	Name: RLC reponse
	Copyright: 
	Author: Boudah Maha
	Date: 16/01/19 18:04
	Description: 
*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void RLC()
{
	FILE* fichier = NULL;
	FILE* fichier_final = NULL;
	fichier = fopen("Equipe_6_mission2_in.txt","r+");
	fichier_final = fopen("Equipe_6_mission2_out.txt","w+");
	char ch2[255] = "";
	fgets(ch2,sizeof ch2 , fichier);
	int l = strlen(ch2); int i=0;
	if (fichier!=NULL && fichier_final!=NULL)
	{
		while(i<l)
		{
			char a = (char)ch2[i];
			if(a=='#')
			{
				char k = ch2[i+1];
				//caster char vers int
				char stTemp[2];
				sprintf(stTemp,"%c",k); //on fais une copie de mon caractère dans une chaine (atoi marche que pour les chaines de caracteres)
				int p = atoi(stTemp);
				//fin de cast
				int d = i+1;
				for(int j=0;j<p;j++)
				{
					fprintf(fichier_final,"%c",ch2[d+1]);
				}
				i=i+3;
			}
			else
			{
				fprintf(fichier_final,"%c",ch2[i]);
				i=i+1;
			}
		}
	}
	if(fichier == NULL)
	{
		fichier = fopen ("Equipe_6_mission2_in.txt","w+");
		fprintf(fichier,"ERREUR : le fichier Equipe_6_mission2_in.txt n’existe pas");
	}
	fclose(fichier);
	fclose(fichier_final);
	
	/***************************************************************************
	*******************************************************************************/
	int occ = 1;
	FILE* fichier1 = NULL;
	FILE* fichier2 = NULL;
	fichier1 = fopen("Equipe_6_mission2_rep_in.txt","r+");
	fichier2 = fopen("Equipe_6_mission2_rep_out.txt","w+");
	char ch[255] = "";
	if (fichier1!=NULL && fichier2!=NULL)
	{
		fgets(ch,sizeof ch , fichier1);
		l = strlen(ch);
		i=0;
		int j;
		char a = ch[0]; 
	
		for (i=1;i<=l;i++)
		{
			
			if (a == ch[i])
			{
				occ++;
			}
			else
			{
				if(occ > 3)
				{
					fprintf(fichier2,"#%d%c",occ,a);
				}
				else
				{
					for(j=0; j<occ; j++)
					{
						fprintf(fichier2,"%c",a);
					}
				}
				occ =1;
				a = ch[i];
			}
			a = ch[i];	
		}	
	}
		if(fichier1 == NULL)
		{
			fichier1 = fopen ("Equipe_6_mission2_rep_in.txt","w+");
			fprintf(fichier1,"ERREUR : le fichier Equipe_6_mission2_rep_in.txt n’existe pas");
		}
		fclose(fichier1);
		fclose(fichier2);		
		
}

int main()
{
	RLC();
	return 0;
}
