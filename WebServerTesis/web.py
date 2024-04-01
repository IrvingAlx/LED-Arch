import socket
import time

# Dirección IP del ESP32-C3 mini
ip_esp = "192.168.1.93"

# Puerto del ESP32-C3 mini
puerto_esp = 8080

# Crear un socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Conectar al ESP32-C3 mini
sock.connect((ip_esp, puerto_esp))

while True:
    # Obtener el mensaje del usuario
    mensaje = input("Introduzca un mensaje (1, 2 o 3): ")

    # Enviar el mensaje al ESP32-C3 mini
    sock.sendall(mensaje.encode())

    # Recibir la respuesta del ESP32-C3 mini (opcional)
    #respuesta = sock.recv(1024).decode()

    # Imprimir la respuesta del ESP32-C3 mini (opcional)
    #print(f"Respuesta del ESP32-C3 mini: {respuesta}")

    # Esperar un segundo
    time.sleep(1)

# Cerrar el socket
sock.close()
