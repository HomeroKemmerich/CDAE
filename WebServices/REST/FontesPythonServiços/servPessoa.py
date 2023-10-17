from fastapi import FastAPI
from fastapi import FastAPI
from pessoa import Pessoa

app = FastAPI()

@app.post("/pessoa/")
async def insere(pes: Pessoa):
    return  {"Message" : pes}

