from fastapi import FastAPI
app = FastAPI()

urlbase = "/"
urlsec = "teste/"

@app.get(urlbase)
async def root():
    return {"message": "New Hello World"}

@app.get(urlbase+"teste/")
async def teste():
    return {"message": "Hello World de teste"}

@app.get(urlbase+urlsec+"bla/")
async def bla():
    return {"message": "Hello World de teste bla"}