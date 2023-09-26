#Programa que envia uma mensagem pela rede usando socket UDP
import socket

#Endereco IP do receptor
SERVER = '127.0.0.1'
#Porta que o receptor esta escutando
PORT = 5002
#Criação do socket
udp = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
#Especificação do destino
dest = (SERVER, PORT)
print ('Programa que envia mensagem com Socket UDP')
print ('Digite o que quer enviar')
msg = input()
#Envia dados(data) para o socket
udp.sendto (msg.encode(), dest)
print ('Mensagem enviada')
#Encerra o Socket 
udp.close()