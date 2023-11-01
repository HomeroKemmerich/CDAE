from fastapi import FastAPI
from pessoa2 import Pessoa2

app = FastAPI()

@app.post("/pessoa2/")
async def insere(pes: Pessoa2):
    if pes.altura != 0:
        pes.IMC = pes.peso / (pes.altura * pes.altura)
    return  {"Message" : pes}

