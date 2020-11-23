# Problema da Mochila com Conflitos

Projeto que visa resolver o problema da mochila com conflitos utilizando o Branch and Bound e heurísticas.

## How to compile

Run

-   `g++ -o main ./src/main.cpp ./src/implementations/node.cpp ./src/implementations/branchandbound.cpp ./src/implementations/instance.cpp ./src/implementations/knapsack.cpp -I ./src/declarations -Wall`

## How to compile with Debug

Run

-   `g++ -g -o main ./src/main.cpp ./src/implementations/node.cpp ./src/implementations/branchandbound.cpp ./src/implementations/instance.cpp ./src/implementations/knapsack.cpp -I ./src/declarations -Wall`

## How to compile with AddressSanitizer:

Run

-   `g++ -o main ./src/main.cpp ./src/implementations/node.cpp ./src/implementations/branchandbound.cpp ./src/implementations/instance.cpp ./src/implementations/knapsack.cpp -I ./src/declarations -Wall -fsanitize=address`

## Fast Compile + Test

Run

-    `g++ -o main ./src/main.cpp ./src/implementations/node.cpp ./src/implementations/branchandbound.cpp ./src/implementations/instance.cpp ./src/implementations/knapsack.cpp -I ./src/declarations -Wall && main example.knpc example.knpc`

## How to compile and run ALL instances

Run

-   `g++ -o main ./src/main.cpp ./src/implementations/node.cpp ./src/implementations/branchandbound.cpp ./src/implementations/instance.cpp ./src/implementations/knapsack.cpp -I ./src/declarations -Wall && main n50c36dc0.64.knpc n50c36dc0.64.knpc && main n100c29dc0.60.knpc n100c29dc0.60.knpc && main n150c50dc0.36.knpc n150c50dc0.36.knpc && main n200c27dc0.42.knpc n200c27dc0.42.knpc && main n250c49dc0.63.knpc n250c49dc0.63.knpc && main n300c37dc0.30.knpc n300c37dc0.30.knpc && main n350c33dc0.39.knpc n350c33dc0.39.knpc && main n400c31dc0.68.knpc n400c31dc0.68.knpc && main n450c20dc0.69.knpc n450c20dc0.69.knpc && main n500c22dc0.46.knpc n500c22dc0.46.knpc && main n550c14dc0.39.knpc n550c14dc0.39.knpc && main n600c19dc0.58.knpc n600c19dc0.58.knpc && main n650c18dc0.56.knpc n650c18dc0.56.knpc && main n700c49dc0.63.knpc n700c49dc0.63.knpc && main n750c46dc0.38.knpc n750c46dc0.38.knpc && main n800c27dc0.56.knpc n800c27dc0.56.knpc && main n850c42dc0.32.knpc n850c42dc0.32.knpc && main n900c25dc0.40.knpc n900c25dc0.40.knpc && main n950c50dc0.51.knpc n950c50dc0.51.knpc && main n1000c11dc0.62.knpc n1000c11dc0.62.knpc`

