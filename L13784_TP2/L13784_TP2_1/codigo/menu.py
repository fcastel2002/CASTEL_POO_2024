from archivoshandler import *
from parserall import CSVParser, XMLMessageParser, JSONMessageParser
from datosserial import ConeccionSerial

class Usuario:
    def __init__(self,port):
        """
        Inicializa una instancia de la clase Usuario.
        Establece una conexión serial en el puerto COM5 con una velocidad de 19200 baudios.
        """
        # Conexion serial
        self.m_conexion = ConeccionSerial(port, 19200)
        self.m_conexion.connect()

    def recibir_comando(self):
        """
        Solicita al usuario que ingrese un comando.

        Returns:
            str: El comando ingresado por el usuario.
        """
        return input("Ingrese el comando (x, j, c): ")

    def recibir_datos(self):
        """
        Lee datos desde la conexión serial hasta recibir datos válidos.

        Returns:
            str: Los datos recibidos desde la conexión serial.
        """
        rawData = ""
        while not rawData.strip():
            rawData = self.m_conexion.readData()
            #print("Esperando datos válidos del puerto serial...")
        return rawData

    def procesar_datos(self, command, rawData):
        """
        Procesa los datos recibidos según el comando especificado.

        Args:
            command (str): El comando que indica el tipo de datos ('c' para CSV, 'j' para JSON, 'x' para XML).
            rawData (str): Los datos en formato de cadena a procesar.

        Returns:
            list: Los datos procesados en forma de lista.
        """
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

    def enviar_comando(self, data):
        """
        Envía datos a través de la conexión serial.

        Args:
            data (str): Los datos a enviar.
        """
        self.m_conexion.writeData(data)

    def command_menu(self):
        """
        Muestra un menú de comandos y ejecuta las acciones correspondientes según la opción seleccionada por el usuario.
        """
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
                archivo = ManejadorArchivo(input() + ".csv")
                archivo.close()
            elif opcion == '2':
                print("Ingrese el nombre del archivo a escribir (sin extensión): ")
                lista_archivos = listar_archivos_csv()
                print("Elija un archivo a escribir:")
                for index, archivo in enumerate(lista_archivos):
                    print(f"{index} - " + archivo)
                if not lista_archivos:
                    print("Error: No se ha creado ningún archivo.")
                    continue
                cual= int(input())
                if cual >= len(lista_archivos):
                    print("Error: Índice fuera de rango.")
                    continue
                filename = lista_archivos[cual]
                archivo = ManejadorArchivo(filename)
                if not filename:
                    print("Error: No se ha creado ningún archivo.")
                    continue

                comandos = ['c', 'j', 'x', 'exit']
                while True:
                    command = self.recibir_comando()
                    if command not in comandos:
                        print("Comando inválido.")
                        continue
                    if command == 'exit':
                        break
                    self.enviar_comando(command)
                    rawData = self.recibir_datos()
                    data = self.procesar_datos(command, rawData)
                    if data not in ([], None):
                        print(f"Datos recibidos: {data}")
                        csvdata = CSVParser().deparser(data)
                        archivo.mywrite(csvdata)
                    else:
                        print("Error: El formato de los datos CSV no es válido.")

                archivo.close()
            elif opcion == '3':
                lista_archivos = listar_archivos_csv()
                print("Elija un archivo a eliminar:")
                for index, archivo in enumerate(lista_archivos):
                    print(f"{index} - " + archivo)
                cual= int(input())
                if cual >= len(lista_archivos):
                    print("Error: Índice fuera de rango.")
                    continue
                filename = lista_archivos[cual]
                archivo = ManejadorArchivo(filename)
                archivo.delete_file()
            elif opcion == '4':
                exit(1)