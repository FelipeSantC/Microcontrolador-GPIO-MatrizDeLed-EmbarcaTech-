# Projeto: Matriz de LEDs Interativa

## Introdução

Este projeto visa controlar uma matriz de LEDs 5x5 utilizando um microcontrolador Raspberry Pi Pico e um teclado matricial. Ao pressionar diferentes teclas, o usuário pode acionar diversas animações e efeitos visuais na matriz.

## Funcionamento

* **Teclado:** Um teclado matricial é utilizado para controlar as animações.
    * **Teclas numéricas (1-4):** Cada tecla aciona uma animação única, com diferentes padrões, cores e velocidades.
    * **Tecla A:** Desliga todos os LEDs.
    * **Tecla B:** Acende todos os LEDs na cor azul com máxima intensidade.
    * **Tecla C:** Acende todos os LEDs na cor vermelha com 80% de intensidade.
    * **Tecla D:** Acende todos os LEDs na cor verde com 50% de intensidade.
    * **Tecla #:** Acende todos os LEDs na cor branca com 20% de intensidade.

* **Matriz de LEDs:** A matriz de LEDs exibe as animações selecionadas pelo usuário, oferecendo uma experiência visual dinâmica.

## Requisitos Atendidos

* **Diversidade de animações:** Foram desenvolvidas 4 animações únicas, uma para cada tecla numérica, atendendo aos requisitos de variedade e criatividade.
* **Qualidade das animações:** Todas as animações possuem pelo menos 5 frames e uma taxa de quadros por segundo adequada, garantindo uma experiência visual fluida.
* **Controle de cores e luminosidade:** As teclas de controle de cor e brilho funcionam conforme especificado, permitindo ao usuário personalizar a visualização.
* **Flexibilidade:** A equipe adaptou a quantidade de animações à quantidade de membros, garantindo a participação de todos.

## Desenvolvedores

* **Felipe Santana (Nick git: FelipeSantC):** Líder do projeto e responsável pela animação 4.
* **Alisson Lívio(Nick git: Alivinho):** Criador da animação 1.
* **Caique César (Nick git: Caique217):** Desenvolvedor da animação 2.
* **Felipe Silva Pires (Nick git: lipesilvapr):** Autor da animação 3.

## Tecnologias Utilizadas

* **Raspberry Pi Pico:** Microcontrolador principal.
* **PIO:** Programable Input/Output para controle dos LEDs.
* **C:** Linguagem de programação utilizada.

## Instruções de Uso

1. **Conecte os componentes:** Conecte a matriz de LEDs, o teclado e o Raspberry Pi Pico de acordo com o diagrama de ligação.
2. **Carregue o código:** Carregue o código para o Raspberry Pi Pico utilizando a ferramenta de programação escolhida.
3. **Acionamento:** Utilize o teclado para selecionar as diferentes animações e efeitos.

## Link do video
https://drive.google.com/drive/folders/1ghMSkHuqnHLxKWr5oM_1rFw_N5_xUil3?usp=sharing
