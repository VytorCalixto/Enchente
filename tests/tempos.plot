set terminal png
set output "tempos.png"
set xlabel "Tamanho"
set ylabel "Tempo (milisegundos)"
set title "Tempo médio para execução considerando tamanho do tabuleiro e tempo"
set grid
set style data lines
set key
plot "tempos.txt" using 1:2 with lines lc rgb "#602b7d" lw 2
