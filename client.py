from socket import socket, AF_INET, SOCK_STREAM
import sys

def enkrip(pub_key, n, plain):
    chipertext = [(ord(char) ** pub_key) % n for char in plain]
    return chipertext

#server_address = ('10.151.43.24', 5078)
server_address = ('localhost', 5078)
client_socket = socket(AF_INET, SOCK_STREAM)
client_socket.connect(server_address)

BUFFER_SIZE = 1024

try:
    while True:
        sys.stdout.write('message : ')
        message = sys.stdin.readline()
        client_socket.send(message)
        terima = client_socket.recv(BUFFER_SIZE)
        sys.stdout.write(terima)
        terima = terima.split(" ")
        print terima[1]
        print terima[3]

        e = int(terima[1])
        n = int(terima[3])

        message_encrypt = enkrip(e, n, message)
        #print message_encrypt

        panjang = str(len(message_encrypt))
        client_socket.send(panjang)

        i = 0
        while 1:
            if i == len(message_encrypt):
                break
            print message_encrypt [i]
            client_socket.send(str(message_encrypt[i]))
            i += 1
        sys.stdout.write(client_socket.recv(BUFFER_SIZE))

except KeyboardInterrupt:
    client_socket.close()
    sys.exit(0)
