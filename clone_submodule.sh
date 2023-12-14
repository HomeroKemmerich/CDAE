#!/bin/bash

# Verifique se um argumento foi fornecido
if [ -z "$1" ]; then
    echo "Por favor, informe o repositório"
    exit 1
fi

# Acesse o argumento da linha de comando
repo=$1

cd Contents

git submodule add https://github.com/HomeroKemmerich/$repo.git

cd ..