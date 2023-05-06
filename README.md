# TP1 - Algoritmos-2
Trabalho Prático 1 - Manipulação de sequências - Abordagem de aspectos práticos de manipulação de sequências. Especificamente, aspectos de implementação de árvores de prefixo aplicada ao problema de compressão de arquivos.

## Execução
Rode `make` na pasta principal do arquivo para obtenção do executável `main`
É possível realizar tanto a compressão, quanto a descompressão, dos arquivos de teste com base no Makefile. 
A compressão será realizada em todos os arquivos `*.txt` presentes na pasta `test`.
Da mesma forma, a descompressão é realizada em todos os arquivos `*.z78` presentes na pasta `test`.

A seguir o código para executar a compressão.
```sh
make compress
``` 
A seguir o código para executar a descompressão.
```sh
make decompress
```
A descompressão não presume uma pré-compressão, ou seja, a chamada de compressão é sempre feita ao se chamar `make decompress`. 
## Arquivos de Exemplo
Existem dez arquivos de texto, no formato `*.txt` presentes na pasta `test`, todos são textos de diferentes linguas obtidos no site [https://www.gutenberg.org/](URL). Todos os testes realizados nos experimentos baseiam-se neles. Além disso, todos possuem um armazenamento inicial entre 1KB e 2MB.
## Relatório
Em `TP1.pdf` pode ser encontrado a documentação do trabalho, incluindo modelagens e análise do algoritmo implementado.
