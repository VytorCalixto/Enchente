set terminal png size 800,800
set output "piores.png"

filename="piores.txt"

from=system('tail -n +2 '.filename. '| cut -f 1 | sort -n | uniq')
select_source(w) = sprintf('< awk ''{if ($1 == "%s") print }'' %s', w, filename)

from2=system('tail -n +2 '.filename. '| cut -f 2 | sort -n | uniq')
select_source2(w) = sprintf('< awk ''{if ($2 == "%s") print }'' %s', w, filename)

set grid
set key
set style data linespoints
set pointintervalbox 3

set multiplot layout 2,1
set title "Piores tempo de execução\n considerando número de cores"
set xlabel "Cores"
set ylabel "Tempo médio (milisegundos)"
plot for [f in from] select_source(f) using 2:3 title f

set title "Piores tempo execução\n considerando tamanho do tabuleiro"
set xlabel "Tamanho do Tabuleiro"
plot for [f in from2] select_source2(f) using 1:3 title f

unset multiplot
