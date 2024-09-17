class DataLogger:
    """Clase que se encarga de mostrar mensajes en consola"""
    @staticmethod
    def log_message(message: str):
        """En este caso, imprime un mensaje en consola"""
        print(message)

    @staticmethod
    def log_input(prompt: str):
        """Solicita datos al usuario y los devuelve"""
        return input(prompt)

    @staticmethod
    def log_table(headers,rows):
        """Muestra los datos en formato tabular"""
        headers_str = " ".join([f"{header:<15}" for header in headers])
        print(headers_str)
        print("-" * len(headers_str))
        for row in rows:
            row_str = "".join([f"{cell:<18.2f}" for cell in row])
            print(row_str)
    @staticmethod
    def log_avg_speed(speed):
        """Muestra la velocidad promedio"""
        print(f"La velocidad promedio es: {speed:.2f} m/s")

    @staticmethod
    def log_altitud_max(medicion):
        """Muestra las mediciones correspondientes a la altitud máxima"""
        if medicion:

            print("\nMedicion con la mayor altitud:")
            print(f"{'Velocidad (m/s) ':<15}{'Distancia (m)':<15}{'Altitud (m)':<15}")
            print("-" * 45)
            print(f"{medicion.m_velocidad:<15.2f}{medicion.m_distancia:<17.2f}{medicion.m_altitud:<15}")
        else:
            print("No hay mediciones")
