#programa que recebe uma mensagem pela rede com socket TCP
import socket

#Endereco IP do receptor e porta
HOST = '192.168.1.6'     # IP para onde será enviada a mensagem
PORT = 8000      # Porta para ligação com o socket
#Criação do socket
tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# O receptor sera um par de endereço e porta
origem = (HOST, PORT)
#Realiza a ligação do socket
tcp.bind(origem)
#Coloca o socket para escutar (aguardar) conexões
tcp.listen(1)
print("Servidor escutando em", origem)
while True:
    #Aguarda uma conexão
    conexao, cliente = tcp.accept()
    print("Receptor conectado por", cliente)
    mensagem = conexao.recv(1024)
    print("Emissor:", cliente, "enviou a mensagem:", mensagem.decode())
    print("Encerrando conexao com o emissor", cliente)
    #encerra a conexão
    conexao.close()
#encerra o socket
tcp.close()