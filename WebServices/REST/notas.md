---
title: 2023-10-10 Class Notes 
date: 2023-10-10
---
# Serviços Web 

## Python e FastAPI

## Arquivos
- [FontesPythonServiços](../../FontesPythonServiços/)
- [Especificações](./assets/openapi.json)

### Instalando o FastAPI

```bash
pip install "fastapi[all]"
```

### Rodando o código

- Arquivo [main.py](../../FontesPythonServiços/main.py)

```bash
cd FontesPythonServiços
```
```bash
uvicorn [nome_do_arquivo]:app --reload
```

![Hello world](pictures/image.png)

![Teste](pictures/image-1.png)

- Adicionar extensão "REST Client" by Huachao Mao

- Acessar o arquivo [primeiro.http](../../FontesPythonServiços/testando/primeiro.http)

## Conexão utilizando ESP-32

- Deixe o serviço python rodando em paralelo

- Abra o projeto [AulasREST](../../AulasRest/) utilizando o PlatformIO

- Rode o serviço em python novamente, dessa vez substituindo o [localhost] pelo IP da máquina
```bash
uvicorn main:app --host [ip.address] --reload
```

[localhost]: 127.0.0.1

## Fast API

### Rotas

- [Rotas.py](../../FontesPythonServiços/rotas.py)

- [Documentation](./assets/openapi(2).json)

### Métodos

- [Metodos.py](../../FontesPythonServiços/metodos.py)
- [Documentation](./assets/openapi%20(3).json)

### Argumentos

#### Path

- [Argumentos.py](../../FontesPythonServiços/argrotas.py)
- [Documentation](./assets/openapi%20(4).json)

#### Query

- [Query.py](../../FontesPythonServiços/queryparam.py)
- [Documentation](./assets/openapi%20(5).json)

### Por que A biblioteca HTTPClient não possui o método `DELETE`?

Por ser uma biblioteca voltada para IoT, não faz sentido que um dispositivo com essa finalidade apague dados.

