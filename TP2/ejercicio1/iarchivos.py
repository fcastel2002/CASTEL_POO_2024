


import os

class ManejadorArchivos():
    def read(self,data):
        raise NotImplementedError("Método read() debe ser implementado por la subclase")

    def write(self,data):
        raise NotImplementedError("Método write() debe ser implementado por la subclase")