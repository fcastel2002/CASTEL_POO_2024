import random


class Registro:
    def __init__(self):
        self.altura = random.randint(0, 1000)
        self.velocidad = random.randint(0, 100)
        self.tiempo = random.randint(0, 100)
        self.direccion = random.choice(["N", "S", "E", "O"])


class Dron:
    def __init__(self, id):
        self.id = id
        self.registros = []

    def getRegistro(self, i):
        if i in range(len(self.registros)):
            return self.registros[i]
        else:
            raise IndexError("Índice de registro inválido")

    def addRegistro(self, registro):
        self.registros.append(registro)


class Reporte:
    def __init__(self):
        self.encabezado = f"{'altura':<10} | {'velocidad':<10} | {'tiempo':<10} | {'direccion':<10}"

    def listar(self, registros):
        print(self.encabezado)
        for registro in registros:
            print(f"{registro.altura:<10} | {registro.velocidad:<10} | {registro.tiempo:<10} | {registro.direccion:<10}")



d1 = Dron(1)
for i in range(10):
    d1.addRegistro(Registro())
r1 = Reporte()
r1.listar(d1.registros)

