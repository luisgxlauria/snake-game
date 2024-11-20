# 🐍 Snake Game  

## 📋 Instalação

### Pré-requisitos
Antes de compilar o jogo, certifique-se de ter o **GCC** instalado no sistema:
- **Linux**: Use o comando:  
  `sudo apt install gcc`
- **Windows**: Instale o [MinGW](http://mingw.org/).
- **WSL (Windows Subsystem for Linux)**: Instale o WSL e GCC:  
  `sudo apt install gcc`
- **macOS**: Siga as instruções abaixo para instalar o GCC:

  1. **Instalando o GCC no macOS**:
     O GCC faz parte das ferramentas de desenvolvimento Xcode. Para instalá-las, abra o terminal e execute:

     ```bash
     xcode-select --install
     ```

     Siga as instruções na tela para completar a instalação.

  2. **Verifique se o GCC está instalado**:
     Após a instalação, execute no terminal:

     ```bash
     gcc --version
     ```

     Isso deve mostrar a versão do GCC instalada. Se o comando não funcionar, verifique se as ferramentas Xcode foram instaladas corretamente.

## 📚 Bibliotecas Utilizadas

### Padrão do C:
- `<stdlib.h>`: Para alocação de memória dinâmica e funções utilitárias.
- `<stdio.h>`: Para entrada e saída padrão.
- `<string.h>`: Para manipulação de strings.
- `<time.h>`: Para inicializar o gerador de números aleatórios.

### Customizadas:
- `keyboard.h`: Gerencia entradas do teclado.
- `screen.h`: Manipula o terminal para criar a interface gráfica.
- `timer.h`: Lida com temporizações no jogo.
- `score.h`: Gerencia pontuações e rankings.

## 🛠️ Como Compilar

1. Navegue até o diretório do projeto:
   `cd /caminho/do/projeto`

2. Compile o programa utilizando o GCC:
   `gcc -o snake-game main.c screen.c keyboard.c timer.c score.c`

## ▶️ Como Executar
Após a compilação, execute o programa com o comando:  
`./snake-game`

## 🎮 Como Jogar

### Movimentos:
Use as seguintes teclas para controlar a cobra:
- **W**: Mover para cima  
- **A**: Mover para a esquerda  
- **S**: Mover para baixo  
- **D**: Mover para a direita  

### Pausar e Sair:
- **P**: Pausar o jogo  
- **Q**: Sair do jogo  

## 🍎 Tipos de Comida

1. **Comida Normal (❤)**:  
   - **Cor**: Vermelho  
   - **Efeito**: Aumenta o tamanho da cobra em 1 unidade.  

2. **Comida Especial (★)**:  
   - **Cor**: Amarelo  
   - **Efeito**: Aumenta o tamanho da cobra em 2 unidades.  

3. **Comida Venenosa (☠)**:  
   - **Cor**: Magenta  
   - **Efeito**: Reduz o tamanho da cobra em 1 unidade. Se o tamanho atingir 0, o jogo termina.  

## ⚙️ Regras do Jogo

1. **Colisão com Obstáculos**: O jogo termina se a cobra colidir com um obstáculo.  
2. **Colisão com as Paredes Laterais**: O jogo termina ao bater nas paredes laterais.  
3. **Teletransporte Vertical**: A cobra pode atravessar a borda superior e reaparecer na borda inferior, e vice-versa.  

## ⏱️ Incremento de Dificuldade

A dificuldade do jogo aumenta gradualmente:  
- A velocidade do jogo aumenta à medida que a cobra cresce.  
- A cada 5 comidas consumidas, o intervalo do temporizador é reduzido, acelerando o movimento da cobra.  

💻 **Divirta-se jogando Snake Game!**
