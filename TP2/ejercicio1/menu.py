from archivoshandler import *
from parserall import CSVParser, XMLMessageParser, JSONMessageParser
from datosserial import ConeccionSerial

class Usuario:
    def __init__(self):
        #Conexion serial
        self.m_conexion = ConeccionSerial("COM5", 19200)
        self.m_conexion.connect()

    def recibir_comando(self):
        return input("Ingrese el comando (x, j, c): ")

    def recibir_datos(self):
        rawData = ""
        while not rawData.strip():
            rawData = self.m_conexion.readData()
            if not rawData.strip():
                print("Esperando datos válidos del puerto serial...")
        return rawData

    def procesar_datos(self,command,rawData):
        if command == 'c':
            parser = CSVParser()
            data = parser.parse(rawData)
        if command == 'j':
            parser = JSONMessageParser()
            data = parser.parse(rawData)
        if command == 'x':
            parser = XMLMessageParser()
            data = parser.parse(rawData)
        return data
    def enviar_comando(self,data):
        self.m_conexion.writeData(data)

    def command_menu(self):
        opciones = ['1', '2', '3', '4']
        while True:
            print("1. Crear archivo nuevo")
            print("2. Escribir en archivo existente (enviar comandos)")
            print("3. Eliminar archivo")
            print("4. Salir")

            opcion = input("Ingrese una opción: ")
            if opcion not in opciones:
                print("Opción inválida.")
                continue
            if opcion == '1':
                print("Ingrese el nombre del archivo a crear (sin extensión): ")
                archivo = ManejadorArchivo(input()+".csv")
                archivo.close()
            elif opcion == '2':
                print("Ingrese el nombre del archivo a escribir (sin extensión): ")
                lista_archivos = listar_archivos_csv()
                print("Elija un archivo a escribir:")
                for index,archivo in enumerate(lista_archivos):
                    print(f"{index} - " + archivo)
                cual = input()
                archivo = lista_archivos(cual)
                if not archivo:
                    print("Error: No se ha creado ningún archivo.")
                    continue

                comandos = ['c', 'j', 'x']
                while True:
                    command = self.recibir_comando()
                    if command not in comandos:
                        print("Comando inválido.")
                        continue
                    if command == 'exit':
                        break
                    self.enviar_comando(command)
                    rawData = self.recibir_datos()
                    data = self.procesar_datos(command,rawData)
                    if data not in ([], None):
                        print(f"Datos recibidos: {data}")
                        csvdata = CSVParser().deparser(data)
                        archivo.mywrite(csvdata)
                    else:
                        print("Error: El formato de los datos CSV no es válido.")

                archivo.close()
            elif opcion == '3':
                print("Ingrese el nombre del archivo a eliminar (sin extensión): ")
                archivo = ManejadorArchivo(input()+".csv")
                archivo.delete_file()
            elif opcion == '4':
                print("Ingrese el nombre del archivo donde desea guardar los datos: ")
                archivo = ManejadorArchivo(input()+".csv")

