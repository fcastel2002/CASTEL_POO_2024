from iarchivos import ManejadorArchivos
import os

class ManejadorArchivo(ManejadorArchivos):
    def __init__(self, nombreArchivo):
        self.m_nombreArchivo = nombreArchivo
        self.m_currentfile = open(self.m_nombreArchivo, "w")
        print('Archivo creado exitosamente')
        self.m_currentfile.write("dispID;apertura;nivel;caudal\n")
        self.m_currentfile.close()


    def mywrite(self,data):
        try:
            self.m_currentfile = open(self.m_nombreArchivo, "a")
            self.m_currentfile.write(data)
            self.m_currentfile.flush()
        except:
            raise FileNotFoundError("No se puede escribir, archivo no existe")
        finally:
            self.m_currentfile.close()


    def close(self):
        self.m_currentfile.close()

    def delete_file(self):
        if os.path.exists(self.m_nombreArchivo):
            os.remove(self.m_nombreArchivo)
            print(f"Archivo {self.m_nombreArchivo} eliminado.")
        else:
            print(f"El archivo {self.m_nombreArchivo} no existe.")
