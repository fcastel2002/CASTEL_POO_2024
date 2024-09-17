class IDataSource:
    """interfaz para las clases que se encargan de la conexión con el puerto serial y su comunicacion"""
    def connect(self):
        raise NotImplementedError("Metodo connect() debe ser implementado por la subclase")

    def _descartar_mensajes_iniciales(self):
        raise NotImplementedError("Metodo _descartar_mensajes_iniciales() debe ser implementado por la subclase")


    def readData(self):
        raise NotImplementedError("Metodo readData() debe ser implementado por la subclase")

    def writeData(self, data):
        raise NotImplementedError("Metodo writeData() debe ser implementado por la subclase")

    def disconnect(self):
        raise NotImplementedError("Metodo disconnect() debe ser implementado por la subclase")
