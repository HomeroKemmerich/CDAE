import json, requests

#Acesso a método GET
response = requests.get("http://127.0.0.1:8000/")
if response.status_code == 200:
    print (response.content)
else:
    print ("Erro: " + response.status_code)