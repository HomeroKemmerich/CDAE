from fastapi import FastAPI

app = FastAPI()

@app.get("/semtipo/{item_id}")
async def item_semtipo(item_id):
    return {"item_id": item_id}

@app.get("/comtipo/{item_id}")
async def item_comtipo(item_id: int):
    return {"item_id": item_id}