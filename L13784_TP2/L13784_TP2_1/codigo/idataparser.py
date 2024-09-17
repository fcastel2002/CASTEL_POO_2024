class IDataParser:
    """ interfaz para las clases que se encargaran de parsear los datos """
    def parse(self,data):
        raise NotImplementedError("Método parse() debe ser implementado por la subclase")

    def deparser(self,listed_data):
        raise NotImplementedError("Método deparser debe ser implementado por la subclase")