import socket
import time

esp32_ip = 'your ip' # Change to your ip, example '111.11.11.11'
esp32_port = 80 # Change to your port

def led(fingerUp):
    finger_data = ' '.join(map(str, fingerUp)) + '\n'
    print(f"data to be sent: {finger_data}")

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.settimeout(5)

    try:
        # Connect to the esp32 server
        client_socket.connect((esp32_ip, esp32_port))
        print("connected to esp32")

        # Send the data
        client_socket.sendall(finger_data.encode())
        print(f"sent data: {finger_data}")
        time.sleep(0.1)  

        # Close the connection
        client_socket.close()
        print("connection closed")
    except Exception as e:
        print(f"error: {e}")
