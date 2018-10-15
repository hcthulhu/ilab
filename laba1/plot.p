set terminal png
set output "graph.png"
f(x) = a*x^2
fit f(x) "graph" using 1:2 via a
plot f(x) with points
