# Projeto - Jogo de Exploração de Dungeons

Projeto desenvolvido para a disciplina de Estruturas de Dados I.

## Objetivo

O trabalho consiste em implementar um jogo de exploração de masmorras, onde o jogador precisa encontrar a saída de um labirinto, coletar itens, evitar armadilhas e enfrentar inimigos. O projeto utiliza e implementa manualmente as seguintes estruturas de dados:

- **Listas Encadeadas:** Para gerenciar o inventário do jogador, permitindo coletar, usar e descartar itens.
- **Pilhas:** Para o sistema de retrocesso de movimentos, permitindo que o jogador desfaça sua última ação.
- **Árvores Binárias:** Para a inteligência artificial dos inimigos, que utilizam uma árvore de decisão para escolher suas ações durante o combate.

## Como funciona

O programa é um jogo de terminal. O jogador utiliza as teclas `W`, `A`, `S`, `D` para se mover por um mapa gerado aleatoriamente. O mapa contém paredes, itens, armadilhas e inimigos ocultos.

Ao longo da exploração, o jogador pode:

- **Encontrar Itens:** Itens como poções de cura, repelentes e moedas são adicionados ao inventário.
- **Enfrentar Inimigos:** Ao encontrar um inimigo, uma tela de combate em turnos é iniciada. O jogador pode atacar, defender, usar um item ou tentar fugir.
- **Cair em Armadilhas:** Resulta em perda de pontos de vida.
- **Gerenciar o Inventário:** O jogador pode, a qualquer momento, abrir o inventário para usar ou descartar um item.
- **Desfazer Movimentos:** Utilizando a tecla 'Z', o jogador pode retornar à sua posição anterior.

O jogo termina com vitória se o jogador encontrar a saída (`S`) ou com derrota se a vida do jogador chegar a zero.

## Tecnologias utilizadas

* **Linguagem C**
* **GCC** como compilador e **Make** para automação da compilação.
* Desenvolvido no Visual Studio Code com a extensão C/C++.

## Observações

* Todas as estruturas de dados (Lista, Pilha e Árvore) foram implementadas manualmente seguindo o modelo de Tipo Abstrato de Dado (TAD), com arquivos `.h` para as interfaces e `.c` para as implementações, sem o uso de bibliotecas externas para as estruturas.
* A posição dos itens, armadilhas e inimigos é gerada de forma aleatória a cada novo jogo, garantindo maior rejogabilidade.