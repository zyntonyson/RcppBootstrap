#include <stdio.h>
#define MAX 50

int main ()
{ 
 //definicion de variables
 char n,                  //Cantidad de numeros a permutar
 lista[MAX+1],            //Lista con los numeros a permutar
 cont[MAX],               //Contador para calcular que permutaciones se hacen
 cont1, cont2, cont3,     //Contadores para los for
 buf;                     //Para realizar la permutacion de dos numeros
     

 //Texto explicando al usuario lo que hace el programa
 printf("\nThis program do all the permutations of n numbers (1, 2, 3, ..., n)\n");
 printf("Where n is a natural number between 1 and MAX (50)\n\n");
 printf("Este programa realiza todas las permutaciones de n numeros natuarales (1, 2, 3, ..., n)\n");
 printf("Donde n es un numeros del 1 al MAX (50)\n\n");

 //Lee la cantidad de numeros a permutar y comprueba que n esta entre 1 y MAX
 printf("Write the quantity of numbers to permutate\n");
 printf ("Introduzca la cantidad de numeros a permutar\n");
 scanf("%d", &n);
 printf("\n");
 for(;n<1 || n>MAX;)
 {
  fflush (stdin);
  printf("ERROR: Write the quantity of numbers to permutate \n\t(a natural number bettween 1 and MAX (50)\n");
  printf ("ERROR: Introduzca la cantidad de numeros a permutar\n\t(un numero natural entre 1 y MAX (50)\n");
  scanf("%d", &n);
  printf("\n");
 }
 
 n=n+1;

 //Crea la tabla para los n numeros
 for (lista[0]=0,cont1=1;cont1<n;cont1++)
 { 
  lista[(int) cont1]= lista[(int) cont1-1]+1;
 }

 //Crea la tabla del contador
 for (cont1=0;cont1<n-1;cont1++)
 { 
  cont[(int) cont1]=0;
 }

 //Escribe la permutacion de numeros inicial
 for(cont1=1;cont1<n;cont1++)
 { 
  if(lista[(int) cont1]<10 && n>10)
  {
   printf("0%d ", lista[(int) cont1]);
  }
  else
  {
   printf("%d ", lista[(int) cont1]);
  }
 }
 printf("\n");

 //Algoritmo que permuta los numeros y muestra todas las combinaciones menos la inicial
 while (cont[0]==0)
 { 
  for (cont1=n-2;cont1>=0;cont1--) 
  {  
   if (cont[(int) cont1]<n-cont1-1)  
   {   
    cont[(int) cont1]++;
    
    //permuta dos numeros y muestra los numeros permutados
    if(cont[0]==0)
    {  
     //Permuta dos numeros de la lista                 
     buf=lista[(int) cont1];    
     lista[(int) cont1]=lista[ (int)cont1+1];    
     lista[cont1+1]=buf;
     
     //Escribe la permutacion resultante
     for(cont2=1;cont2<n;cont2++) 
     {   
      if(lista[(int) cont2]<10 && n>10)
      {
       printf("0%d ", lista[(int) cont2]);
      }
      else
      {
       printf("%d ", lista[(int) cont2]);
      }
     } 
     printf("\n");    
    }

    //Limpia la tabla del contador dejando una sola cifra distinta de 0
    for (cont2=n-2;cont2>cont1;cont2--)
    { 
     cont[(int) cont2]=0;
    }    
    
    //Solucion para poner los numeros en orden siguiente
    if (cont[n-2]==1 && cont[n-3]==2)
    {
     //Calcula el numero de elementos a permutar
     for (cont2=2;cont[n-cont2-2]==cont2+1;cont2++);
     
     //Permuta los elementos
     for (cont3=1;cont3<=cont2/2;cont3++)
     {
      buf=lista[n-cont2+cont3-1];
      lista[n-cont2+cont3-1]=lista[n-cont3];
      lista[n-cont3]=buf;
     }
    }
    break;
   }
  }
 }
 fflush (stdin);
 getchar();
 return 0;
}
