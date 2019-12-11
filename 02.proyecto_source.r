library(Rcpp)
library(microbenchmark)
sourceCpp("/home/roman/Escritorio/MCE/01.Programacion y análisis de algoritmos/Tareas/Proyecto/inversa.cpp")

a<-sample(c(-10:10),100,replace = TRUE)
A<-matrix(a,9,9)

InverS(A)
solve(A)
det(A)
detC(A)


Minc(A,1,1)
A
detC(A)
det(A)



microbenchmark(
  detC(A),
  det(A)
  )

