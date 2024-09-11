from archivoshandler import ManejadorArchivo
from parserall import CSVParser, XMLMessageParser, JSONMessageParser
from datosserial import ConeccionSerial


if __name__ == '__main__':
    serialConnect = ConeccionSerial("COM5", 19200)
    serialConnect.connect()
    archivo = ManejadorArchivo("datos.csv")
    try:
        while True:
            command = input("Ingrese el comando (x, j, c): ")
            serialConnect.writeData(command)  # Enviar comando al Arduino

            # Bucle para esperar hasta que se reciban datos válidos
            rawData = ""
            data = ""
            while not rawData.strip():
                rawData = serialConnect.readData()  # Leer los datos enviados por el Arduino

                if not rawData.strip():
                    print("Esperando datos válidos del puerto serial...")

            # Procesar los datos CSV
            if command == 'c':
                parser = CSVParser()
                data = parser.parse(rawData)  # Intentar parsear los datos CSV
            if command == 'j':
                parser = JSONMessageParser()
                data = parser.parse(rawData)
            if command == 'x':
                parser = XMLMessageParser()
                data = parser.parse(rawData)



            if data not in ([], None):
                print(f"Datos recibidos: {data} & {type(data)}")  # Mostrar los datos CSV si son válidos
                csvdata = CSVParser().deparser(data)
                # Escribir los datos en un archivo CSV
                archivo.mywrite(csvdata)
                archivo.close()


            else:
                print("Error: El formato de los datos CSV no es válido.")

    except KeyboardInterrupt:
        archivo.delete_file()
        serialConnect.disconnect()
