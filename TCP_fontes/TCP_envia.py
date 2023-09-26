#programa que envia uma mensagem pela rede com socket TCP
import socket

#Endereco IP do receptor e porta
HOST = '192.168.1.6'     # IP para onde fica vai a mensagem
PORT = 8000      # Porta para ligação com o socket
#Criação do socket
tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
destino = (HOST, PORT)
#Realiza o pedido de conexão
tcp.connect(destino)
print ('Programa que envia mensagem com Socket TCP')
print ('Digite o que quer enviar')
mensagem = input("Digite uma mensagem: ")
#Envia dados(data) para o socket
tcp.send(mensagem.encode())
#Encerra o Socket 
tcp.close()