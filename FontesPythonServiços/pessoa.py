from pydantic import BaseModel
from pydantic import Field

class Pessoa(BaseModel):
    id: int = Field(description= "Código da Pessoa")
    nome: str 
    altura: float = None 
