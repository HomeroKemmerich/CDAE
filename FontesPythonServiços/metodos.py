from fastapi import FastAPI
app = FastAPI()

urlbase = "/"

@app.get(urlbase)
async def listagem():
    return {"message": "Mensagem de listagem (recupera todos) por GET"}

@app.get(urlbase+"contato/")
async def consulta():
    return {"message": "Mensagem de consulta por GET"}

@app.put(urlbase+"contato/")
async def altera():
    return {"message": "Mensagem de alteração por PUT"}

@app.post(urlbase+"contato/")
async def insere():
    return {"message": "Mensagem de inserção por POST"}

@app.delete(urlbase+"contato/")
async def apaga():
    return {"message": "Mensagem de remoção por DELETE"}