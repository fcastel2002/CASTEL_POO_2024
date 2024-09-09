class DataParser:
    """ interfaz para las clases que se encargaran de parsear los datos """
    def parse(self,data):
        raise NotImplementedError("Método parse() debe ser implementado por la subclase")

    def toString(self,data):
        raise NotImplementedError("Método toString() debe ser implementado por la subclase")