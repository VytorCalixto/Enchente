set terminal png
set output "medias.png"
set xlabel "Tamanho"
set ylabel "Tempo (milisegundos)"
set title "Tempo médio para execução considerando tamanho do tabuleiro"
set grid
set key
set pointintervalbox 3
plot "medias.txt" using 1:2 with linespoints lc rgb "#602b7d" lw 2 pt 7 lt 1 pi -1 ps 1.5
