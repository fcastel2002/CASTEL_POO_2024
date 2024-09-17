import random
from ej3_logger import DataLogger

class Medicion:
    def __init__(self, velocidad: float, distancia: float, altitud: int):
        #dasd
        #dasd
        self.m_velocidad = velocidad
        self.m_distancia = distancia
        self.m_altitud = altitud

    def __repr__ (self):
            return f"Velocidad: {self.m_velocidad}, Distancia: {self.m_distancia}, Altitud: {self.m_altitud}"

class ControladorMediciones:
    def __init__(self):
        #
        self.mediciones = []

    def generarMedicion(self, N: int):

        for _ in range(N):
            velocidad = round(random.uniform(0, 100),2)
            distancia = round(random.uniform(0, 1000),2)
            altitud = round(random.randint(0, 10000),2)
            medicion = Medicion(velocidad, distancia, altitud)
            self.mediciones.append(medicion)

    def obtenerVelocidadPromedio(self):

        if not self.mediciones:
            return 0

        velocidad_total = sum([medicion.m_velocidad for medicion in self.mediciones])

        return velocidad_total / len(self.mediciones)

    def obtenerAltitudMaxima(self):
        if not self.mediciones:
            return 0
        return max(self.mediciones, key=lambda medicion: medicion.m_altitud)

    def retenerDatos(self, nombreArchivo: str):
        repo = RepositorioMediciones()
        if not os.path.exists(nombreArchivo):
            exists = False
        else:
            exists = True
        repo.guardarEnArchivo(self.mediciones, nombreArchivo,exists)

    def cargarDatos(self, nombreArchivo: str):
        repo = RepositorioMediciones()
        self.mediciones = repo.cagarDesdeArchivo(nombreArchivo)
        if self.mediciones == "ERROR":
            return "ERROR"

import csv
import os
class RepositorioMediciones:

    def guardarEnArchivo(self, mediciones, nombreArchivo: str, exists):

        with open(nombreArchivo, mode = 'a', newline = '') as file:
            writer = csv.writer(file)

            if not exists: #si no existe escribe cabecera
                writer.writerow(['Velocidad', 'Distancia', 'Altitud'])

            for medicion in mediciones:
                writer.writerow([medicion.m_velocidad, medicion.m_distancia, medicion.m_altitud])

    def cagarDesdeArchivo(self,nombreArchivo: str):
        logger = DataLogger()
        mediciones = []

        if not os.path.exists(nombreArchivo):
            logger.log_message("No existe el archivo")
            return "ERROR"
        with open(nombreArchivo, mode = 'r') as file:
            reader = csv.reader(file)
            next(reader)
            for row in reader:
                medicion = Medicion(float(row[0]), float(row[1]), int(row[2]))
                mediciones.append(medicion)

        return mediciones



def main():
    controlador = ControladorMediciones()
    logger = DataLogger()

    while True:
        logger.log_message("-" * 30)
        logger.log_message("1. Generar mediciones")
        logger.log_message("2. Obtener velocidad promedio")
        logger.log_message("3. Obtener altitud máxima")
        logger.log_message("4. Persistir datos en archivo")
        logger.log_message("5. Cargar datos desde archivo")
        logger.log_message("6. Mostrar datos en tabla")
        logger.log_message("7. Salir")
        opcion = logger.log_input("Ingrese una opción: ")
        logger.log_message("-" * 30)

        if opcion == "1":
            if controlador.mediciones != []:
                logger.log_message("Hay mediciones cargadas, si continua se agregarán a las existentes")
                while True:
                    continuar = logger.log_input("Ingrese 's' para continuar,'b' para borrar las existentes o 'n' para cancelar: ")
                    if continuar == "n":
                        continue
                    elif continuar == "b":
                        controlador.mediciones = []
                    elif continuar != "s":
                        logger.log_message("Opción inválida")
                        continue
                    break

            N = int(logger.log_input("Ingrese la cantidad de mediciones a generar: "))
            controlador.generarMedicion(N)
            logger.log_message(f"{N} Mediciones generadas")


        elif opcion == "5":
            nombreArchivo = logger.log_input("Ingrese el nombre del archivo: ")
            if not controlador.cargarDatos(nombreArchivo) == "ERROR":
                logger.log_message(f"Datos cargados desde {nombreArchivo}")

        elif opcion == "7":
            logger.log_message("Saliendo...")
            break

        elif controlador.mediciones == []:
            logger.log_message("ERROR: No hay mediciones")
            continue

        elif opcion == "2":
            velocidad_promedio = controlador.obtenerVelocidadPromedio()
            logger.log_avg_speed(velocidad_promedio)

        elif opcion == "3":
            altitud_maxima = controlador.obtenerAltitudMaxima()
            logger.log_altitud_max(altitud_maxima)

        elif opcion == "4":
            nombreArchivo = logger.log_input("Ingrese el nombre del archivo: ")
            controlador.retenerDatos(nombreArchivo)
            logger.log_message(f"Datos guardados en {nombreArchivo}")

        elif opcion == "6":
            filas = [[medicion.m_velocidad, medicion.m_distancia, medicion.m_altitud] for medicion in controlador.mediciones]
            logger.log_table(["Velocidad (m/s) ", " Distancia (m) ", "   Altitud (m)"], filas)


        else :
            logger.log_message("Opción inválida")






if __name__ == "__main__":
    main()
