from pydantic import BaseModel
from pydantic import Field

class Pessoa2(BaseModel):
    id: int = Field(description= "Código da Pessoa")
    nome: str 
    altura: float
    peso: float
    IMC: float = None


class PessoaAlt(BaseModel):
    id: int = Field(description= "Código da Pessoa")
    nome: str = None
    altura: float = None
    peso: float = None
    IMC: float = None
