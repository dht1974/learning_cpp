#!/usr/bin/Rscript

require ('tidyverse')

nd <- read_csv ('nd.csv')
sigma <- read_csv ('sigma.csv')

if (nrow (nd) > 20000 && nrow (nd) <= 200000) {
    nd %>% filter (seq %% 5 == 1) %>% ggplot (aes (seq, val)) + geom_point (color = 'red')
} else if (nrow (nd) > 200000 && nrow (nd) <= 2000000) {
    nd %>% filter (seq %% 50 == 1) %>% ggplot (aes (seq, val)) + geom_point (color = 'red')
} else if (nrow (nd) > 2000000) {
    nd %>% filter (seq %% 500 == 1) %>% ggplot (aes (seq, val)) + geom_point (color = 'red')
} else {
    nd %>% ggplot (aes (seq, val)) + geom_point (color = 'red')
}
