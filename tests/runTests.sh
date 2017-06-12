#!/bin/bash

OPTIND=1
MAIN="../main"
HEUR="./floodit_h6"

while getopts ":m:h:" opt; do
    case "$opt" in
        m)  MAIN=$OPTARG
            ;;
        h)  HEUR=$OPTARG
            ;;
    esac
done

shift $((OPTIND-1))
[ "$1" = "--" ] && shift

echo $MAIN
echo $HEUR

# tempo máximo para executar, em milisegundos
tempo_max=120000 #120s

# tamanhos do tabuleiro
tams=(8 16 32)

# lista de cores
cores=(2 3 4 6 8 10)

#-- Cores do terminal
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # Sem cor

TABULEIROS="tabuleiros_$(basename ${HEUR}).txt"

echo -ne "" > $TABULEIROS
echo -ne "#Tam tabuleiro\t#N cores\t#Tempo médio\n" > tempos.txt
echo -ne "#Tam tabuleiro\t#Tempo médio\n" > medias.txt
echo -ne "#Tam tabuleiro\t#N cores\t#Tempo médio\n" > piores.txt

echo "Iniciado testes"
for i in ${tams[*]}
do
    echo "Tamanho do tabuleiro: ${i}"
    T_soma_total=0
    for cor in ${cores[*]}
    do
        echo "Número de cores: ${cor}"
        T_soma_cor=0
        T_max_cor=0
        N_TESTES=500
        for j in $(seq 1 ${N_TESTES})
        do
            echo -ne "Tabuleiro ${i}x${i} com ${cor} cores: (${j}/${N_TESTES}) (T max: $(($T_max_cor/1000000000))."
            printf "%03d" $(($T_max_cor/1000000%1000))
            echo -ne ")"\\r
            semente=$RANDOM
            ./test $i $i $cor $semente

            T_inicial=$(date +%s%N)

            eval $MAIN < "/tmp/${semente}.in" > "/tmp/resp${semente}.out"

            T_gasto=$(($(date +%s%N) - $T_inicial))
            T_soma_cor=$(($T_gasto + $T_soma_cor))
            T_soma_total=$(($T_gasto + $T_soma_total))

            eval $HEUR < "/tmp/${semente}.in" > "/tmp/heur${semente}.out"

            RESP=$(cat "/tmp/resp${semente}.out" | tail -n2 | head -n1)
            HRESP=$(cat "/tmp/heur${semente}.out" | tail -n2 | head -n1)

            if [ $RESP -gt $HRESP ]; then
                echo -ne "${RED}Heurística $(basename ${HEUR}) fez tabuleiro ${i} ${i} ${cor} ${semente} em ${HRESP} e nós em ${RESP}${NC}\n"
                echo "${i} ${i} ${cor} ${semente} (${HRESP})" >> ${TABULEIROS}
            fi

            # tempo em segundos
            S=$(($T_gasto/1000000000))
            # tempo em milisegundos
            M=$(($T_gasto/1000000))
            # tempo máximo por cor
            if [ $T_max_cor -lt $T_gasto ]; then
                T_max_cor=$T_gasto
            fi

            rm "/tmp/${semente}.in"
            rm "/tmp/resp${semente}.out"
            rm "/tmp/heur${semente}.out"
        done
        T_medio_cor=$(($T_soma_cor/${N_TESTES}))
        S_medio_cor=$(($T_medio_cor/1000000000))
        M_medio_cor=$(($T_medio_cor/1000000))
        echo -ne "\n${CYAN}Tempo médio com ${cor} cores: ${S_medio_cor}."
        printf "%03d" $((${M_medio_cor}%1000))
        echo -e "s (${T_medio_cor})${NC}\n"
        echo -e "${i}\t${cor}\t${M_medio_cor}" >> tempos.txt
        echo -e "${i}\t${cor}\t$(($T_max_cor/1000000))" >> piores.txt
    done
    T_medio_total=$(( $T_soma_total/(${N_TESTES} * ${#cores[*]}) ))
    S_medio_total=$(($T_medio_total/1000000000))
    M_medio_total=$(($T_medio_total/1000000))
    echo -ne "${BLUE}Tempo médio com tamanho ${i}: ${S_medio_total}."
    printf "%03d" $((${M_medio_total}%1000))
    echo -e "s (${T_medio_total})${NC}\n"
    echo -e "${i}\t${M_medio_total}" >> medias.txt
done

fs=$(cat "${TABULEIROS}" | wc -l)
if [ ${fs} -gt "1" ]; then
    echo -e "${RED}${fs} tabuleiro(s) perdeu(perderam) para outras heurísticas${NC}"
    cat ${TABULEIROS}
else
    echo -e "${GREEN}Nenhum tabuleiro perdeu para as outras heurísticas${NC}"
fi
