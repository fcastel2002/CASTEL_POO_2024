class IDataSource:
    def readData(self):
        raise NotImplementedError("Método readData() debe ser implementado por la subclase")
    def writeData(self,data):
        raise NotImplementedError("Método writeData() debe ser implementado por la subclase")


