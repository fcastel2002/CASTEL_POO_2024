
# @author
#   Francisco Castel - 13784 - 2024
# @version
#   1.0
#   1.1 (last revision)

import random

class Matriz:
    def __init__(self,cantFilas,cantColumnas):
        self.__cantFilas = cantFilas
        self.__cantColumnas = cantColumnas
        self.__matrix = [[0 for j in range(0,self.__cantColumnas)] for i in range(0,self.__cantFilas)]
    @property
    def llenar(self):
        for i in range(0,self.__cantFilas):
            for j in range(0,self.__cantColumnas):
                self.__matrix[i][j] = chr(random.randint(32, 96))
    
    @property
    def mostrar(self):
        for i in range(0,self.__cantFilas):
            for j in range(0,self.__cantColumnas):
                print(self.__matrix[i][j],end=" ")
            print()
    @llenar.deleter
    def matriz(self):
        del self.__matrix
            
filas = int(input("Ingrese la cantidad de filas: "))
while filas<=0:
    print("Error. La cantidad de filas debe ser mayor a 0.")
    filas = int(input("Ingrese la cantidad de filas: "))
columnas = int(input("Ingrese la cantidad de columnas: "))
while columnas<=0:
    print("Error. La cantidad de columnas debe ser mayor a 0.")
    columnas = int(input("Ingrese la cantidad de columnas: "))
matriz1 = Matriz(filas,columnas)
matriz1.llenar
matriz1.mostrar
del matriz1.matriz
      
                 