#Programa que recebe uma mensagem pela rede usando socket UDP
import socket

#Endereco IP do receptor
HOST = ''
# Porta que o receptor vai escutar
PORT =  8888          #informar aqui a porta que vai aguardar a mensagem
# O receptor sera um par de endereço e porta
orig = (HOST, PORT)
#Cria o socket
udp = socket.socket(socket.AF_INET,socket.SOCK_DGRAM) 
#Conectando
udp.bind(orig)
print('Programa que recebe e mostra uma mensagem ...')
print('Aguarda receber uma mensagem ...')
#Recebe dados do socket, informações e endereço
msg, cliente = udp.recvfrom(1024)
print ('Recebeu !!!\n')
print (cliente, msg)
#Fechamento do socekt
udp.close()