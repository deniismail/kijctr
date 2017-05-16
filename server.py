from socket import socket, AF_INET, SOCK_STREAM, SOL_SOCKET, SO_REUSEADDR
from select import select
import sys
import random

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def dekrip (priv_key, n, chipertext):
    plaintext = [chr((char ** priv_key) % n) for char in chipertext]
    return ''.join(plaintext)

server_address = ('', 5078)
server_socket = socket(AF_INET, SOCK_STREAM)
server_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
server_socket.bind(server_address)
server_socket.listen(3)

CONNECTION = [server_socket]
BUFFER_SIZE = 1024
try:
    while True:
        reads, writes, errors = select(CONNECTION, [], [])
        for sock in reads:
            if sock == server_socket:
                client_socket, client_address = server_socket.accept()
                CONNECTION.append(client_socket)

            else:
    # 1
                p = 17
                q = 23

     # 2
                n = p * q

    # 3
                phi = (p - 1) * (q - 1)
                print n
                print phi

     # 4
                e = random.randrange(1, phi)
                cek = gcd(e, phi)
                while cek != 1:
                    e = random.randrange(1, phi)
                    cek = gcd(e, phi)
                print e

      # 5
                cek2 = e % phi
                d = 1
                while cek2 != 1:
                    d += 1
                    cek2 = (d * e) % phi
                print d

     # 6
                print "private key : ", d
                print "public key : ", e

                terima = sock.recv(BUFFER_SIZE)
                message = terima
                sock.send('pub_key {} n {}\n'.format(e,n))
                panjang = sock.recv(BUFFER_SIZE)
                panjang = int (panjang)
                hasil_enkrip = []
                i = 0
                while 1 :
                    if i == panjang :
                        break
                    hasil_enkrip.append(int(sock.recv(BUFFER_SIZE)))
                    i+=1

                message_dekrip = dekrip(d, n , hasil_enkrip)
                print message_dekrip

                if message:
                    sock.send('data sent\n')
                else:
                    print sock.getpeername(), '((disconnect))'
                    sock.close()
                    CONNECTION.remove(sock)

except KeyboardInterrupt:
    server_socket.close()
    sys.exit(0)