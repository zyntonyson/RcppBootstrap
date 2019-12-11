/* Headers necesarios para el funcionamiento*/
#include <Rcpp.h>
using namespace Rcpp;


/*Determina el minimo (i,j)*/
// [[Rcpp::export]]
NumericMatrix Minc(NumericMatrix x, int r, int c)
            {
            int dimension = x.nrow(); 
            NumericMatrix MinijC((dimension-1),(dimension-1));
            NumericVector temp((dimension-1)*(dimension-1));
            int k =0;
            
            for( int i=0; i<dimension; i++)
            {     
            for( int j=0; j<dimension; j++)
            {
            if((i!=r )&& (j!=c))
            {
            temp[k]=x(i,j);
            k++;
            }
            }
            
            }
            
            k=0;
            
            for( int i=0; i<dimension-1; i++)
            {     
            for( int j=0; j<dimension-1; j++)
            {
            MinijC (i,j) = temp[k];
            k++;
            }
            }
            
            return MinijC;           
            
            }            
            



/*Determina el determinante de la matrix de forma recursiva*/
// [[Rcpp::export]]
double detC( NumericMatrix x)
            {
            int dimension = x.nrow();
            double det=0;
            
            if(dimension == 2)
            {
            det =x(0,0)*x(1,1)- x(0,1)*x(1,0);
            }
            else
            {
            for(int i=0;i<dimension;i++)
            {
            det += (pow((-1),i))*x(0,i)*detC(Minc(x,0,i));
            }
            }
            return det; 
            
            }



/*Determina la inversa de la matriz por el método de  cofactores*/
// [[Rcpp::export]]
NumericMatrix InverS(NumericMatrix x) 
             {
             int nrow = x.nrow(), ncol = x.ncol(); 
             NumericMatrix invC(nrow,ncol);
             double detx = detC(x);
             
             for (int i = 0; i <nrow; i ++) 
             {
             for (int j = 0; j <ncol; j ++) 
             {
             
             invC(i,j)= detC(Minc(x ,i, j))/(detx);
             } 
             
             } 
             
             return invC;
             }
  
  
