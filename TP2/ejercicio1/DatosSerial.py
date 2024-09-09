import serial
from IDataSource import IDataSource

class ConeccionSerial(IDataSource):

    def __init__(self,port,baudrate):
        self.port = port
        self.baudrate = baudrate
        self.conexion = None

    def connect(self):

        self.conexion = serial.Serial(self.port,self.baudrate) #conecta al puerto serial del Arduino

    def readData(self):
        if self.conexion:

            return self.conexion.readline().decode('utf-8').strip()

        else:
            raise ConnectionError("Imposible leer, no hay conexión con ningún puerto serial\n")

    def writeData(self,data): #se utilizaráw para enviar los comandos 'x' 'j' 'c' al Arduino
        if self.conexion:
            self.conexion.write(data.encode('utf-8'))
        else:
            raise ConnectionError("Imposible escribir, no hay conexión con ningún puerto serial\n")
    def disconnect(self):
        if self.conexion:
            self.conexion.close()
        raise ConnectionError("Imposible desconectar, no hay conexión con ningún puerto serial\n")
        self.conexion = None
