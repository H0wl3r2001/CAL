# CAL PROJECT - Padeiro em Época de Covid


## Compilação

Simplesmente é necessário compilar o código utilizando o *CMAKE* num IDE recente (Visual Studio Code, CLion, ...).
Podem existir erros de dependências que estão explicados abaixo.


## Dependências

O nosso código utiliza uma versão alterado da API de visualização de grafos fornecida (*graphviewer*). Portanto, é necessario utilizar a versão enviada para que as animações e a visualização funcionem.
Este graphviewer depende evidentemente da libraria SFML - sendo necessário existirem as 3 dll *sfm-graphics-d-2.dll*, *sfm-system-d-2.dll*,
*sfm-window-d-2.dll* na pasta do executável.

## Como usar

Sendo que não foi implementada leitura de ficheiros, pela complexidade dos dados, tudo pode ser modificado na *main function* presento no ficheiro *main.cpp*. O código foi cuidadosamente **documentado** e **comentado** o que facilitará a compreensão e a criação de *datasets* personalizados.


## Final

Trabalho realizado por:
Afonso Duarte de Carvalho Monteiro (up201907284@edu.fe.up.pt)
João Ferreira Baltazar (up201905616@edu.fe.up.pt)
Joel Alexandre Vieira Fernandes (up201904977@edu.fe.up.pt)
