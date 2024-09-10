import serial
from idatasource import IDataSource


class ConeccionSerial(IDataSource):

    def __init__(self, port, baudrate):
        self.m_port = port
        self.m_baudrate = baudrate
        self.m_conexion = None

    def connect(self):
        self.m_conexion = serial.Serial(self.m_port, self.m_baudrate,timeout=1)  # Conecta al puerto serial del Arduino

        # Descartar mensajes iniciales que no son comandos del usuario
        self._descartar_mensajes_iniciales()

    def _descartar_mensajes_iniciales(self):
        """Este metodo descarta los mensajes
         iniciales enviados por el Arduino hasta que comienza a recibir comandos."""
        if self.m_conexion:
            while True:
                data = self.m_conexion.readline().decode('utf-8').strip()
                print(f"Descartando mensaje inicial: {data}")
                # Detecta cuando terminan los mensajes iniciales y empieza a esperar comandos
                if "c:" in data:  # Este mensaje indica que los comandos comienzan a ser aceptados
                    print("Listo para recibir comandos del usuario.")
                    break

    def readData(self):
        if self.m_conexion:
            accumulated_data = ""
            newline = 0
            while True:
                # Leer una línea completa (hasta encontrar '\n')
                data = self.m_conexion.read().decode('utf-8')

                accumulated_data += data
                if data == '\n' or data == '\r':
                    newline += 1
                else: newline = 0 #este else es importante porque evalua si son seguidos
                                    #no necesariamente tiene que ser un salto de linea
                if newline == 2:
                    break
            return accumulated_data.strip()
        else:
            raise ConnectionError("Imposible leer, no hay conexión con ningún puerto serial\n")

    def writeData(self, data):  # Se utilizará para enviar los comandos 'x', 'j' y 'c' al Arduino
        if self.m_conexion:
            self.m_conexion.write(data.encode('utf-8'))

        else:
            raise ConnectionError("Imposible escribir, no hay conexión con ningún puerto serial\n")

    def disconnect(self):
        if self.m_conexion:
            self.m_conexion.close()
            self.m_conexion = None
        else:
            raise ConnectionError("Imposible desconectar, no hay conexión con ningún puerto serial\n")
