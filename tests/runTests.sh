#!/bin/bash

# tempo máximo para executar, em milisegundos
tempo_max=500

# tamanhos do tabuleiro
tams=(4 8 16 32 64 128)

# lista de cores
cores=(2 4 8 16)

#-- Cores do terminal
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # Sem cor

echo -ne "" > tabuleiros.txt
echo -ne "" > tempos.txt

echo "Iniciado testes"
for i in ${tams[*]}
do
    echo "Tamanho do tabuleiro: ${i}"
    T_soma_total=0
    for cor in ${cores[*]}
    do
        echo "Número de cores: ${cor}"
        T_soma_cor=0
        for j in $(seq 1 $i)
        do
            echo -ne "Tabuleiro com ${i} linhas e ${cor} cores ${i}x${j}"\\r
            semente=$RANDOM
            # echo "Usando semente: ${semente}"
            ./test $i $j $cor $semente
            T_inicial=$(date +%s%N)
            ../main < "/tmp/${semente}.in"
            T_gasto=$(($(date +%s%N) - $T_inicial))
            T_soma_cor=$(($T_gasto + $T_soma_cor))
            T_soma_total=$(($T_gasto + $T_soma_total))
            # tempo em segundos
            S=$(($T_gasto/1000000000))
            # tempo em milisegundos
            M=$(($T_gasto/1000000))
            if (($M>$tempo_max)); then
                echo -e "\n${RED}Tabuleiro ${i} ${j} ${cor} ${semente} levou mais de ${tempo_max} milisegundos: ${S}.${M}s${NC}"
                echo "${i} ${j} ${cor} ${semente}" >> tabuleiros.txt
            fi
            rm "/tmp/${semente}.in"
        done
        T_medio_cor=$(($T_soma_cor/$i))
        S_medio_cor=$(($T_medio_cor/1000000000))
        M_medio_cor=$(($T_medio_cor/1000000))
        echo -ne "\n${CYAN}Tempo médio com ${cor} cores: ${S_medio_cor}."
        printf "%03d" ${M_medio_cor}
        echo -e "s (${T_medio_cor})${NC}\n"
    done
    T_medio_total=$(( $T_soma_total/($i * ${#cores[*]}) ))
    S_medio_total=$(($T_medio_total/1000000000))
    M_medio_total=$(($T_medio_total/1000000))
    echo -ne "${BLUE}Tempo médio com tamanho ${i}: ${S_medio_total}."
    printf "%03d" ${M_medio_total}
    echo -e "s (${T_medio_cor})${NC}\n"
    echo -e "${i} \t ${M_medio_total}" >> tempos.txt
done

fs=$(cat tabuleiros.txt | wc -l)
if [ ${fs} -gt "1" ]; then
    echo -e "${RED}${fs} tabuleiro(s) passou do tempo limite de ${tempo_max} milisegundos:${NC}"
    cat tabuleiros.txt
    exit 1
else
    echo -e "${GREEN}Nenhum tabuleiro passou do tempo limite de ${tempo_max} milisegundos${NC}"
    exit 0
fi
