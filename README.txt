Alunos: Silvana Trindade e Maurício André Cinelli
E-mails: syletri@gmail.com e mauricio.andre.cinelli@gmail.com

**************************************************************
TRABALHO 2

O programa foi desenvolvido em ambiente Linux (testados em Debian e Ubuntu 14.04), utilizando a versão 3 do freeGlut. Assumindo que o OpenGl e o freeglut estejam devidamente configurados.

*Compilação:
  Utilizar makefile no terminal, digitando o comando:
    make
*Execução:
  Para execução, no terminal digite:
    ./main
O código do programa encontra-se dividido em algumas classes,
além do arquivo main.cpp.

No trabalho, foram feitas duas bandeiras: Wallis e Fortuna, e a bandeira de Israel (padrão).
Para alterar a bandeira a ser desenhada, é necessário comentar e descomentar algumas linhas:

arquivo main.cpp:
  para habilitar a bandeira de Wallis e Fortuna, comente a linha 13 e descomente a linha 14
  para habilitar a bandeira de Israel, descomente a linha 13 e comente a linha 14

arquivo Tecido.cpp:
  para habilitar a bandeira de Wallis e Fortuna, comente a matriz nas linhas 75-136, e descomente a matriz nas linhas 9-70
  para habilitar a bandeira de Israel, descomente a matriz nas linhas 75-136, e comente a matriz nas linhas 9-70

Note que a bandeira de Israel é mais lenta, já que possui consideravelmente mais triângulos.

Uma documentação mais elaborada e detalhada sobre os processos
e teoria por trás do código pode ser vista no arquivo
"documentacao.pdf". Além de todas as funções não-triviais
estarem todas documentadas

**************************************************************
