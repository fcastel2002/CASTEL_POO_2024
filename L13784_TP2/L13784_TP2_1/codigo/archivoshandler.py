from iarchivos import ManejadorArchivos
import os

class ManejadorArchivo(ManejadorArchivos):
    def __init__(self, nombreArchivo):
        """
        Inicializa una instancia de ManejadorArchivo.

        Args:
            nombreArchivo (str): El nombre del archivo a manejar.
        """
        self.m_nombreArchivo = os.path.join('..', 'anexo', nombreArchivo)
        if not os.path.exists(os.path.join('..', 'anexo')):
            os.makedirs(os.path.join('..', 'anexo'))
        if not os.path.exists(self.m_nombreArchivo):
            self.m_currentfile = open(self.m_nombreArchivo, "w")
            self.m_currentfile.write("dispID;apertura;nivel;caudal\n")
            print('Archivo creado exitosamente')
            self.m_currentfile.close()

    def mywrite(self, data):
        """
        Escribe datos en el archivo.

        Args:
            data (str): Los datos a escribir en el archivo.

        Raises:
            FileNotFoundError: Si el archivo no existe.
        """
        try:
            self.m_currentfile = open(self.m_nombreArchivo, "a")
            self.m_currentfile.write(data)
            self.m_currentfile.flush()
        except:
            raise FileNotFoundError("No se puede escribir, archivo no existe")
        finally:
            self.m_currentfile.close()

    def close(self):
        """
        Cierra el archivo.
        """
        self.m_currentfile.close()

    def delete_file(self):
        """
        Elimina el archivo si existe.

        Prints:
            Mensaje indicando si el archivo fue eliminado o no existe.
        """
        if os.path.exists(self.m_nombreArchivo):
            os.remove(self.m_nombreArchivo)
            print(f"Archivo {self.m_nombreArchivo} eliminado.")
        else:
            print(f"El archivo {self.m_nombreArchivo} no existe.")

def listar_archivos_csv():
    """
    Lista todos los archivos CSV en el directorio 'anexo'.

    Returns:
        list: Una lista de nombres de archivos CSV en el directorio 'anexo'.
    """
    archivos_csv = [f for f in os.listdir(os.path.join('..', 'anexo')) if f.endswith('.csv')]
    return archivos_csv