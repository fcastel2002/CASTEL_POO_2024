from iarchivos import ManejadorArchivos
import os

class ManejadorArchivo(ManejadorArchivos):
    def __init__(self, nombreArchivo):
        self.m_nombreArchivo = nombreArchivo
        self.m_currentfile = open(self.m_nombreArchivo, "w+t")
        self.m_currentfile.write("dispID | apertura | nivel | caudal\n")
        self.m_currentfile.close()


    def write(self,data):
        try:
            self.m_currentfile = open(self.m_nombreArchivo, "w+t")
            self.m_currentfile.write(data)
        except:
            raise FileNotFoundError("No se puede escribir, archivo no existe")


        self.m_currentfile.write(data)
    def close(self):
        self.m_currentfile.close()

    def delete_file(self, nombreArchivo):
        if os.path.exists(nombreArchivo):
            os.remove(nombreArchivo)
            print(f"Archivo {nombreArchivo} eliminado.")
        else:
            print(f"El archivo {nombreArchivo} no existe.")
