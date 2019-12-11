/* Headers necesarios para el funcionamiento*/
#include <Rcpp.h>
using namespace Rcpp;


/*Ordenamiento Quicksort: usado para el ordenamiento de datos*/
// [[Rcpp::export]]
NumericVector QuickSort(NumericVector datos, int l, int r)
{
  int i,j;
  double pivot,temp;
  
  if (r > l){
    pivot = datos[r];
    i= l-1;
    j = r;
    for(;;){
      while(datos[++i] < pivot);
      while(datos[--j] > pivot);
      
      if(i >= j)
        break;
      temp=datos[i];
      datos[i]=datos[j];
      datos[j]=temp;
    }
    
    temp=datos[i];
    datos[i]=datos[r];
    datos[r] = temp;
    
    QuickSort(datos,l,i-1);
    QuickSort(datos,i+1,r);
    
  } return datos;
} 

/*Extrae muestras Jack eliminando sistemáticamente una observacion a la vez*/
  // [[Rcpp::export]]
NumericVector SampleJack( NumericVector datos, int posicion )
  {
  int longitud= datos.length();
  NumericVector Jacksample(longitud-1);
  
  int i,j;
  j=0;
  
  for(i=0;i<longitud;i++)
    {
      if(i!=posicion){
        Jacksample[j]=datos[i];
        j++;
      }    
    }
  
  return Jacksample;
}



/*Calcula la mediana*/
// [[Rcpp::export]]
double Median(NumericVector x)
  {
    int longitud = x.length();
    
    x=QuickSort(x,0,(longitud-1));
    
    if(longitud%2==0)
      {return((x[(longitud/2)-1]+x[(longitud/2)])/2);}
    else
      {return x[((longitud+1)/2)-1];}
  }


/*Corrección Jacknife Mediana: realiza el cálculo del sesgo y corrige la estimación*/
// [[Rcpp::export]]
double JackCorreccion(NumericVector x)
  {
    double biasJack=0;
    int longitud= x.length();
    int i;
    for(i=0;i<longitud;i++)
      {
      biasJack+=Median(SampleJack(x,i));
        
      }
    
    biasJack = (biasJack/longitud);
    
    
    return (longitud)*Median(x)-(longitud-1)*biasJack;
  }


/*media Sn: implementación para el cálculo de la media*/
// [[Rcpp::export]]
double MediaCpp(NumericVector x)
  {
    int longitud = x.length();
    double xbarra =0;
    for(int i=0;i<longitud;i++)
      {
        xbarra += x[i];  
      }
      
    return (xbarra/longitud);
  }
 
 
 /*varianza Sn implemetación para el cálculo de la varianza n*/
 // [[Rcpp::export]]
 
 double VarSn(NumericVector x)
  {
  
  int longitud = x.length();
  double VarsnC =0;
  double mu= MediaCpp(x);
  for(int i=0;i<longitud;i++)
  {
    VarsnC += pow((x[i]-mu),2);  
  }
  
  return (VarsnC/longitud);
 
 }



/*Corrección Jacknife: elimina el sesgo de la estimación Sn*/
// [[Rcpp::export]]
double JackCorreccionSn(NumericVector x)
{
  double biasJack=0;
  int longitud= x.length();
  int i;
  for(i=0;i<longitud;i++)
  {
    biasJack+=VarSn(SampleJack(x,i));
    
  }
  
  biasJack = (biasJack/longitud);
  
  
  return (longitud)*VarSn(x)-(longitud-1)*biasJack;
}
