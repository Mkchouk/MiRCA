#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct
{	char *qid;
	char *sid;
	int posin;
	int posend;
	char *qseq;
	char *sseq;
}ligne;

bool get_ligne(FILE* f, ligne* pr)
{
     pr->posin = 0;
   pr->posend = 0;
   pr->qid = malloc(100 * sizeof(char*));
   pr->sid = malloc(100 * sizeof(char*));
   pr->qseq = malloc(60000 * sizeof(char*));
   pr->sseq = malloc(60000 * sizeof(char*));
 /*   int n = fscanf(f, "%s,contig%d,%d,%d,%[^\n]\n", &pr->seq_id,
			&pr->ch_id, &pr->pos_id, &pr->end_id, pr->data);*/
    char *chaine = NULL; // Chaîne vide de taille TAILLE_MAX
	chaine = malloc(sizeof(char*) * 200005);
	int TAILLE_MAX=200005;int n=0;
	      fgets(chaine,TAILLE_MAX,f);
   // printf("chaine= %s\n",chaine);
        n = sscanf(chaine,"%[^,],%[^,],%d,%d,%[^,],%[^\n]",pr->qid,pr->sid,&pr->posin,&pr->posend,pr->qseq,pr->sseq);
      return n == 6 ? true : false;
}
void print_ligne(ligne r, int cpt)
{if(r.posend<r.posin){
     printf("\nligne[%d]= %s  ",cpt,r.qid);
     printf("posIN= %d  ",r.posin);
     printf("posEND= %d",r.posend);
    printf("ERROR!");}
else{
     printf("\nligne[%d]= %s \t",cpt,r.qid);
     printf("posIN= %d  ",r.posin);
     printf("posEND= %d",r.posend);
     printf("   lenght qseq=       %d\t",strlen(r.qseq));
      printf("   lenght Sseq= %d",strlen(r.sseq));
  //   printf("qseq= %s\n",r.qseq);
     // printf("sseq= %s",r.sseq);
     }
}
ligne* table_trier(ligne table[], int n){
    int i,permutation = 1;ligne temp;

if(n>0){
            while (permutation == 1){
            permutation = 0;
            for (i=0; i<n-1; i++){
            if (table[i].posin > table[i+1].posin){
             /* Il y a eu permutation */
            temp = table[i];
            table[i]= table[i+1];
            table[i+1] = temp;
            permutation = 1;
            } /* if */
            if((table[i].posin == table[i+1].posin)&&(table[i].posend<table[i+1].posend)){
                temp = table[i];
            table[i]= table[i+1];
            table[i+1] = temp;
            permutation = 1;
            }
             }//FOR
            } /* while */
            }/* IF*/
          // for (j = 0; j < n; j++){print_ligne(table[j],j);}
return table;
}

char *sequence_replace(char *s, int start, int lenght, char *ct)
{
   char *new_s = NULL;
   new_s=malloc(250000*sizeof(char));
int res=0;
   if (s != NULL && start >= 0)
   {
      int size = strlen (s);
     // new_s = malloc (sizeof (*new_s) * (size - lenght + strlen (ct) + 1));
	if (new_s != NULL)
      {		 
         memcpy (new_s, s, start);
		 res=start+lenght;
		if (res>=size) {
			 memcpy (&new_s[start], ct, strlen (ct));
			 }
		else{
			memcpy (&new_s[start], ct, strlen (ct));
			memcpy (&new_s[start + strlen (ct)], &s[start + lenght], size - lenght - start + 1);
			}
      }
   }
   else
   { fprintf (stderr, "Insufficient memory\n");
      printf ("Insufficient memory\n");
      exit (EXIT_FAILURE);
   }
   return new_s;
}

ligne* inverse_table(ligne table[], int n) {
    int i = 0;
    ligne tmp;
    for(i=0 ; i < n/2 ; i++) {
        tmp = table[i];
        table[i] = table[n-i-1];
        table[n-i-1] = tmp;
    }


return table;
}
ligne* eliminer_sequence(ligne table[], int n) {
    int i = 0;int len=0;int j=0;int cpp=0; char tirer='-';
      for (i = 0; i < n; i++) {cpp=0;

    len = table[i].posend-table[i].posin;
        for (j=0;j<len;j++)
        {
          if(table[i].qseq[j]==tirer) {cpp++;}

        }
        table[i].qseq[len+cpp]='\0';
        table[i].sseq[len+cpp]='\0';

       }
return table;
}

ligne* eliminer_chevauchement(ligne table[],int n){
int i;
//if(n>1){
for (i = 1; i < n; i++) {
    if (table[i-1].posend >= table[i].posin)
       {table[i-1].posend = table[i].posin - 1;}
                        }
 table=inverse_table(table,n);
    // }
table=eliminer_sequence(table,n);
//int t=0; for (t = 0; t < n; t++){print_ligne(table[t],t);}
return table;
}

void table_optimiser(ligne table[], int n,FILE* f1,FILE* f2){
int i=0;int j=0;int k=0;
    for(i=0;i<n;i++)
    {
     for(j=i+1;j<n;j++)
     {
        if(table[i].posin<=table[j].posin && table[i].posend>=table[j].posend)
        {
            for (k=j;k<n;k++)
            {
               table[k]=table[k+1];
            }
            n--;
            j=j-1;
                }
     }
     }

 table= eliminer_chevauchement(table,n);

char *chaine1 = NULL;
char *chaine2=NULL;
char *chaine3=NULL;
void rewind(FILE* f1);
int t=0;int c=0;
chaine1 = malloc(sizeof(char) * 200000);int TAILLE_MAX=200005;
chaine2 = malloc(sizeof(char) * 250000);
chaine3 = malloc(sizeof(char)* 250000);
char *delim=NULL;
        delim = malloc(sizeof(char) * 250);
  while(fgets(chaine1,TAILLE_MAX, f1)!= NULL){
        int p=0;
    if(strlen(chaine1)<150 && chaine1[0]=='>')  {
   		delim=chaine1;
    delim[strlen(chaine1) - 1] = '\0';
      		p=1;}

    /*if(strlen(chaine1)>70 && strlen(chaine1)<300 && chaine1[0]=='>'){delim=strtok(chaine1," ");p=1;}*/
       if(p==1){
        for(c=0;c<strlen(delim);c++)
		{
		delim[c]=delim[c+1];
		}
		delim[strlen(delim)]='\0';
		}
        if(strcmp(table[0].qid,delim)==0)
        {
           //fprintf(f2,">%s_Corrected\n",delim);
           fgets(chaine3,TAILLE_MAX, f1);
            printf("len chaine: %d\n",strlen(chaine3));
            int lencouv=0;int percent=0;
            for (t = 0; t < n; t++){
            lencouv=(table[t].posend-table[t].posin)+lencouv;
            }
            printf("len table: %d\n",lencouv);
            percent=(lencouv*100)/strlen(chaine3);
            printf("Pourcentage: %d \n\n",percent);
                chaine2=chaine3;

            for (t = 0; t < n; t++)
            {
                chaine2=sequence_replace(chaine2,table[t].posin,table[t].posend-table[t].posin,table[t].sseq);
                }

               for (t = 0; t < n; t++){//print_ligne(table[t],t);
                                        }
            int deb=0,fin=0;
            deb= table[t-1].posin;
            fin= table[0].posend;
//            printf("\ndeb= %d   fin= %d\n",deb,fin);
//            printf("\nt= %d\n",t);

		j=0;
		for(i=deb;i<fin;i++){
			if(chaine2[i]!='-'){
			chaine2[j]=chaine2[i];
			j++;
			}
		}
		chaine2[j]='\0';
        if (percent>98){
        fprintf(f2,">%s_Corrected\n",delim);
           fprintf(f2,"%s\n",chaine2);}

            break;

        }
       }//WHILE fgets()

}

int main()
{
ligne* Tligne;
	FILE* fichier = NULL;
	int i = 0;
Tligne=malloc(25000*sizeof(ligne));
		char *precedent;
		precedent = NULL;
   ligne l;
    fichier = fopen("Alignresults","r");
//	fichier = fopen("resultatblastne102D","r"); //(File to alignment result of Blast)
	FILE* fichier1 = NULL;
	fichier1 = fopen("655H4pacbio.fasta","r"); //(File of Raw long Reads)
	FILE* fichier2 = NULL;
	fichier2 = fopen("ReadsCorrected_trimmode.fasta","w");// (file of Corrected reads)
	int j = 0;

	if (fichier == NULL)
	{
		// On affiche un message d'erreur si on veut
		printf("File not found"); //      perror(msg);
	}
	if (fichier1 == NULL)
	{		// On affiche un message d'erreur si on veut
		printf("File not found"); //      perror(msg);
	}
	i = 0;int cpp=0;int nbligneResultat8=0;
	while (get_ligne(fichier, &l))
	{
		nbligneResultat8++;
		if (precedent != NULL && strcmp(l.qid, precedent)!= 0)
		{       cpp++;
		        Tligne=	table_trier(Tligne,i);
		//	printf("OK!!");
                   table_optimiser(Tligne,i,fichier1,fichier2);

			  i = 0;
				}
		Tligne[i] = l;
	precedent = l.qid;
		i++;
			}
	        Tligne=	table_trier(Tligne,i);
            table_optimiser(Tligne,i,fichier1,fichier2);

printf("CPP derniere= %d\n",cpp+1);
printf("nb ligne Resultat8= %d\n",nbligneResultat8);

	fclose(fichier);
	fclose(fichier1);
	fclose(fichier2);
	return 0;}
