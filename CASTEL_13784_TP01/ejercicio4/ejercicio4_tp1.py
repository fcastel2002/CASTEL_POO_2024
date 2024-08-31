import random

class Medicion: #esta clase se encargaria de la medicion propiamente dicha
    def __init__(self, temperatura: float, presion: float, humedad: float):
        self.temperatura = temperatura
        self.presion = presion
        self.humedad = humedad
    def __str__(self):
        return f"{self.temperatura:11.2f} |  {self.presion:8.2f} | {self.humedad:7.2f}"

class SistemaMedicion:
    def __init__(self,cantidadSimulaciones: int):

        #manejo de errores
        if cantidadSimulaciones <= 0:
            raise ValueError("La cantidad de simulaciones debe ser mayor a 0")

        self.cantidadSimulaciones = cantidadSimulaciones
        self.mediciones = []
    def medir(self):
        for i in range(self.cantidadSimulaciones):
            temperatura = random.uniform(-10,40)
            presion = random.uniform(900,1100)
            humedad = random.uniform(0,100)
            medicion = Medicion(temperatura,presion,humedad)
            self.mediciones.append(medicion)
    def mostrarMediciones(self):
        if not self.mediciones:
            raise ValueError("No hay mediciones para mostrar")
        print("N° | Temperatura |  Presion  |\tHumedad |")
        print("-"*40)
        for i, medicion in enumerate(self.mediciones,1):
            print(f'{i:2} - {medicion}')
            print("_" * 40)
        print("_" * 40)

    def mayorTemperatura(self):
        if not self.mediciones:
            raise ValueError("No hay mediciones para calcular la temperatura máxima, pruebe realizando mediciones")
        mayor = self.mediciones[0].temperatura
        for medicion in self.mediciones:
            if medicion.temperatura > mayor:
                mayor = medicion.temperatura
        return mayor
    def presionProm(self):
        if not self.mediciones:
            raise ValueError("No hay mediciones para calcular la presion promedio, pruebe realizando mediciones")
        suma = 0
        for medicion in self.mediciones:
            suma += medicion.presion
        return suma / len(self.mediciones)




def main():
    print("\n/////Sistema de medicion/////")
    print(" Simule las mediciones de un sistema, y realice operaciones sobre las mediciones")
    print(" Cualquier operacion, sera realizada sobre las ultimas mediciones simuladas")
    print(" Cada vez que quiera volver a realizar mediciones, se perderan las anteriores")
    sistema = None
    try:
        while True:
            for _ in range(20):
                print("_",end="")
            print("\n Opciones:")
            print("1 - Realizar mediciones")
            print("2 - Mostrar mediciones")
            print("3 - Mostrar la mayor temperatura")
            print("4 - Mostrar la presion promedio")
            print("5 - Salir")
            opcion = int(input("Ingrese una opcion: "))

            if opcion == 1:
                N = int(input("Ingrese la cantidad de simulaciones: "))
                sistema = SistemaMedicion(N)
                aux = 1
                sistema.medir()
            elif opcion == 2:
                if sistema is None:
                    raise ValueError("No hay mediciones para mostrar")
                sistema.mostrarMediciones()
            elif opcion == 3:
                if sistema is None:
                    raise ValueError("No hay mediciones para mostrar")
                print(f"La mayor temperatura es: {sistema.mayorTemperatura():.2f}")
            elif opcion == 4:
                if sistema is None:
                    raise ValueError("No hay mediciones para mostrar")
                print(f"La presion promedio es: {sistema.presionProm(): .2f}")
            elif opcion == 5:
                a = input("Desea salir? (s/n): ")
                if a == "s":
                    exit("Fin del programa")
                elif a == "n":
                    continue
            else:
                print("Opcion invalida")
    except ValueError as e:
        print(f'Error: {e}')
        main()

if __name__ == "__main__":
    main()