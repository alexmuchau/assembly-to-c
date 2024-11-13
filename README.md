# Assembly to C

## Instruções para execução correta do programa
1. Todos os métodos estão travados para apenas receber letras minúsculas,
2. Existe 32 registradores no programa sendo deles 30 disponíveis, o registrador 0 é relacionado ao número 0 ($z), o 30 é relacionado ao $sp e o 31 é relacionado ao $ra,
3. Cada registrador é acessado usando $num_reg, caso tenha qualquer caractere entre o $ e o número do registrador irá causar um problema,
4. Acesso de memória, igual no MIPS, 0($reg) 

## Instruções MIPS funcionais
### R
- add
- sub
- sll

### I
- addi
- lw
- sw
- beq

### J
- j
- jal
- jr

## Passos para executar o app (em Linux)
1. ```chmod 777 ./compile.sh```
2. ```./compile.sh && ./assembly-to-c.o```
3. seguir as instruções do menu! 

---
**Alex Muchau**