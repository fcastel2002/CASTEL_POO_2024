import serial
from datosserial import ConeccionSerial
from parserall import CSVParser
arduino = ConeccionSerial("COM5", 19200)
arduino.connect()
print(arduino.readData())
while True:
    command = input("Enter command: ")
    if command == 'exit':
        break
    arduino.writeData(command)
    ndata = ''
    print(arduino.readData())


