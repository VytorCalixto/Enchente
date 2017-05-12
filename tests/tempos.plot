set terminal png
set output "tempos.png"
set xlabel "Cores"
set ylabel "Tempo (milisegundos)"
set title "Tempo médio para execução considerando número de cores e tamanho do tabuleiro"

filename="tempos.txt"
from=system('tail -n +2 '.filename. '| cut -f 1 | sort | uniq')
select_source(w) = sprintf('< awk ''{if ($1 == "%s") print }'' %s', w, filename)

set grid
set key
set style data linespoints
set pointintervalbox 3

plot for [f in from] select_source(f) using 2:3 title f


#plot "tempos.txt" using 1:3 with points lc rgb "#602b7d" lw 2 title "Tamanho do tabuleiro",\
#    "tempos.txt" using 2:3 with points lc rgb "#19e287" lw 2 title "Número de cores"
