setwd("~/tmp/code_snippets")
data <- read.csv("points.csv")

plot(data, pch = 19, asp = 1, cex = 0.3)

phi    <- seq(0, 2*pi, length.out = 10000)
circle <- data.frame(x = sin(phi), y = cos(phi))
lines(circle, col = 'red')