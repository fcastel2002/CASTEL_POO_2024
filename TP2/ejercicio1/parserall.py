from datosserial import ConeccionSerial
from dataparser import DataParser


class CSVParser:
    def parse(self, data):
        return data.split(',')

    def toString(self, data):
        return ','.join(data)