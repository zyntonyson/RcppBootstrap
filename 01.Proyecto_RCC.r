



library(microbenchmark)


a<-sample(-10:10,9,replace = TRUE)
A<-matrix(a,3,3)
A
det(A)


##Determina el determinante de la matrix de forma recursiva
cppFunction('double detC( NumericMatrix x)
            {
            int dimension = x.nrow();
            double det=0;

            if(dimension ==2)
              {
              det =x[0][0]*x[1][1]- x[0][1]*x[1][0];
              }
            else
              {
              for(int i=0;i<dimension;i++)
                {
                det+= (pow(-1,i))*(x[0][i])*detC(Minc(x,0,i));
                }
              }
            return det; 
            
            }')




float  determinante( float**matriz ,int dimension){
  
  int i;
  // Contenedor del determinante
  float det;
  
  // Condición de salida
  if(dimension==2)
  {
    
    det =matriz[0][0]*matriz[1][1]- matriz[0][1]*matriz[1][0];
  }
  else
  {
    // cálculo por cofactores usando el  renglón 1 de la matriz
    for(i=0;i<dimension;i++)
    {
      det+= (pow(-1,i))*(matriz[0][i])*determinante(Min(matriz,0,i,dimension),(dimension-1));
    }
    
  }
  return det; 
}








##Determina la matrix Min(i,j) para obtener la matriz de cofactores
cppFunction('NumericMatrix Minc(NumericMatrix x, int r, int c)
            {
              int dimension = x.nrow(); 
              NumericMatrix MinijC (nrow,ncol);
              NumericVector aux((nrow-1)*(nrow-1))
            int k =0;

            for( int i=0; i<dimension; i++)
            {     
              for(int j=0; j<dimension; j++)
              {
                if((i!=r )&& (j!=c))
                  {
                  temp[k]=x[i][j];
                  k++;
                  }
              }
            
            }
            
            k=0;

            for( i=0; i<dimension; i++)
            {     
              for( j=0; j<dimension; j++)
              {
                MinijC[i][j]=temp[k];
                k++;
              }
            }
            
            return MiniJC            

            }            
            '
            )


#Determina la inversa de la matriz por el método de  cofactores
cppFunction ('NumericMatrix InverS(NumericMatrix x) 
            {
                int nrow = x.nrow(), ncol = x.ncol(); 
                NumericMatrix invC (nrow,ncol);
                double detx = detC(x);
            
                for (int i = 0; i <nrow; i ++) 
                  {
                  for (int j = 0; j <ncol; j ++) 
                      {
                        
                        out[i][j]= detC(Minc(x,i,j))/(detx);
                      } 
                
                  } 
                  
                  return invC;
            }')
  
  
  
cppFunction(
  'double sumC(NumericVector x) {
  int n = x.size();
  double total = 0;
  for(int i = 0; i < n; ++i) {
  total += x[i];
  }
  return total;
  }'
)





x <- runif(1e3)
microbenchmark(
  sum(x),
  sumC(x),
  sumR(x)
)