import serial

# Configura la conexión serie (ajusta el puerto según tu sistema)
ser = serial.Serial('COM5', 19200   , timeout=1)

while True:
    command = ser.write(input().encode())
    while True :
        line = ser.readline().decode('utf-8').strip()  # Lee una línea y decodifica a texto
        print(line)
        if not line:
            break

