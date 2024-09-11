class ManejadorArchivos():
    def read(self,data):
        raise NotImplementedError("Método read() debe ser implementado por la subclase")

    def mywrite(self,data):
        raise NotImplementedError("Método write() debe ser implementado por la subclase")
    def close(self):
        raise NotImplementedError("Método close() debe ser implementado por la subclase")
    def delete_file(self):
        raise NotImplementedError("Método delete_file() debe ser implementado por la subclase")