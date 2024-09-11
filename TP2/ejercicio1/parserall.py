import csv
import json
import xml.etree.ElementTree as ET
from idataparser import IDataParser
from io import StringIO

class CSVParser(IDataParser):
    """
    Un analizador para datos CSV que implementa la interfaz IDataParser.
    """

    def parse(self, data):
        """
        Analiza los datos CSV en una lista de filas.

        Args:
            data (str): Los datos CSV como una cadena.

        Returns:
            list: Una lista de filas, donde cada fila es una lista de valores.
                  Devuelve una lista vacía si los datos están vacíos o son inválidos.
        """
        # Verificar si los datos están vacíos
        if not data.strip():
            print("Error: Los datos CSV están vacíos o no contienen un formato válido.")
            return []

        reader = csv.reader(StringIO(data), delimiter=',')

        try:
            header = next(reader)  # Leer la primera línea como encabezado
            for row in reader:
                if not any(row):  # Si es una fila vacía, la saltamos
                    continue
                print(f"hi from parsearll: {row}")
            return header
        except StopIteration:
            # Esto ocurre si el CSV está vacío o mal formado
            print("Error: No se encontraron datos válidos en el CSV.")
            return []

    def deparser(self, listed_data):
        """
        Convierte una lista de datos de nuevo en una cadena con formato CSV.

        Args:
            listed_data (list): La lista de datos a convertir.

        Returns:
            str: La cadena con formato CSV.
        """
        csv_data = ""
        for index, valor in enumerate(listed_data):
            if index + 1 == len(listed_data):
                csv_data += valor
                continue
            csv_data += valor + ";"
        return csv_data + "\n"


class XMLMessageParser(IDataParser):
    """
    Un analizador para datos XML que implementa la interfaz IDataParser.
    """

    def parse(self, data):
        """
        Analiza los datos XML en una lista de valores de texto.

        Args:
            data (str): Los datos XML como una cadena.

        Returns:
            list: Una lista de valores de texto de los elementos XML.
                  Devuelve una lista vacía si los datos están vacíos o son inválidos.
        """
        # Verificar si los datos están vacíos
        if not data.strip():
            print("Error: Los datos XML están vacíos o no contienen un formato válido.")
            return []

        try:
            root = ET.fromstring(data)
            values = [elem.text.strip() for elem in root.iter() if elem.text is not None]
            if values and values[0] == '':
                values = values[1:]
            return values
        except ET.ParseError as e:
            print(f"Error parsing XML: {e}")
            return []


class JSONMessageParser(IDataParser):
    """
    Un analizador para datos JSON que implementa la interfaz IDataParser.
    """

    def parse(self, data):
        """
        Analiza los datos JSON en una lista de valores de texto.

        Args:
            data (str): Los datos JSON como una cadena.

        Returns:
            list: Una lista de valores de texto del objeto JSON.
                  Devuelve una lista vacía si los datos están vacíos o son inválidos.
        """
        # Verificar si los datos están vacíos
        if not data.strip():
            print("Error: Los datos JSON están vacíos o no contienen un formato válido.")
            return []

        try:
            json_data = json.loads(data)
            values = [str(value).strip() for value in json_data.values() if value is not None]
            return values
        except json.JSONDecodeError as e:
            print(f"Error parsing JSON: {e}")
            return []