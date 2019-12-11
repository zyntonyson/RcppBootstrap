
###LIBRERIAS NECESARIAS
library(Rcpp)
library(microbenchmark)
library(bootstrap)
#### CARGADO DE ARCHIVO *.cpp (No encontré cómo cargarlo dinámicamente :( )
sourceCpp("/home/roman/Escritorio/MCE/01.Programacion y análisis de algoritmos/Tareas/Proyecto/01.cpp")


##Cálculo de la varianza Sn
varsnR<-function(a){
  
return ((sum((a-mean(a))^2))/2)

}


##Corrector de sesgo Jackknife para varianza
BiasSnR<-function(a)
  {
  RplJac<-rep(0,length(a))
    for(i in 1:length(a))
      {
      RplJac[i]<-varsnR(a[-i])
      }
  BiaJack<-(length(a)-1)*(-varsnR(a)+mean(RplJac))  
  varsnR(a)-BiaJack  
  }


##Corrector de sesgo Jackknife para mediana
BiasMedianR<-function(a)
  {
  RplJac<-rep(0,length(a))
  for(i in 1:length(a))
    {
    RplJac[i]<-median(a[-i])
    }
  BiaJack<-(length(a)-1)*(-median(a)+mean(RplJac))  
  median(a)-BiaJack  
}


#Muestra para pruebas
a<-sample(1:500,00,replace = FALSE)

#Benchmark para mediana
microbenchmark(
  jackknife(a,median),
  BiasMedianR(a),
  JackCorreccion(a))

#Benchmark para varianza
muestra<-sample(1:500,50, replace = FALSE)
microbenchmark(
  jackknife(muestra,var),
  BiasSnR(muestra),
  JackCorreccionSn(muestra))
