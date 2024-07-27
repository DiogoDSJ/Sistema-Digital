<h1>
  <p align="center">Barramento</p>
</h1>

<h2>
  <p align="center">Desenvolvimento de módulos do kernel em C para processador gráfico, utilizando o kit de desenvolvimento DE1-SoC.</p>
</h2>

<h2>Sobre o projeto</h2>
<p>
  O estudante Gabriel Sá Barreto Alves, durante suas atividades de iniciação científica e no desenvolvimento de seu trabalho de conclusão de curso, projetou e implementou um processador gráfico. Este processador possibilita mover e controlar elementos em um monitor VGA com resolução de 640×480 pixels, permitindo desenhar dois tipos de polígonos convexos (quadrados e triângulos) e uma quantidade específica de sprites. Durante o desenvolvimento, Gabriel utilizou como unidade de processamento principal o NIOS II. Ele foi embarcado na mesma FPGA que o Processador Gráfico. 
</p>
<p>
Foi solicitado aos alunos da disciplina TEC499 MI - Sistemas Digitais, do curso de Engenharia de Computação da Universidade Estadual de Feira de Santana (UEFS), que desenvolvessem um jogo para a arquitetura proposta. O usuário deve interagir exclusivamente utilizando o mouse. Para acessar e controlar o jogo (iniciar, pausar, continuar, etc.), o usuário deve usar os botões disponíveis na placa. O sistema deve utilizar a interface VGA para a visualização.
</p>

<h2>
  Requisitos do projeto
</h2>
<p>
• O código deve ser escrito na linguagem C;
</p>
<p>
• O sistema só poderá utilizar os componentes disponíveis na placa;
</p>
<p>
• Um novo sprite deve ser colocado na memória e utilizado no jogo;
</p>
<p>
• As ações do ator do jogo (pulo, tiro, etc.) devem ser comandadas pelos botões do mouse;
</p>
<p>
• A variação da velocidade no movimento do mouse deve ser refletida na ação do ator do jogo. Por exemplo, no jogo breakout a barra se move com velocidade maior se o movimento do mouse for brusco;
</p>
<p>
• Informações do jogo (placar, vidas, etc.) devem ser exibidas no display de 7-segmentos;
</p>
<p>
• O jogo deve permitir ações do usuário através dos botões da DE1-SoC, no mínimo: a pausa, o retorno, o reinício e o término do jogo.
</p>
<p>
<p>
• O usuário poderá parar e reiniciar o jogo em qualquer momento; 
</p>
<p>
• O usuário poderá sair do jogo em qualquer momento.
</p>
<p>
• Pelo menos um elemento passivo do jogo deverá se mover.
</p>

<h2>Equipe</h2>
<uL>
  <li><a href="https://github.com/Armaaaaaaaaaaaaaaaaaaaaaaaaaaando">Armando de Lima Almeida</a></li>
  <li><a href="https://github.com/DiogoDSJ">Diogo dos Santos de Jesus</a></li>
  <li><a href="https://github.com/eugabrielbr">Gabriel Silva dos Santos</a></li>
</ul>

<div id = "componentes">
<h2>Componentes, ferramentas e softwares utilizados</h2>

<h4>Placa de Desenvolvimento DE1-SoC</h4>

<p>
A DE1-SoC da Altera integra um sistema de processador rígido (HPS) baseado em ARM, composto pelo processador Dual-core ARM Cortex-A9, periféricos e interfaces de memória interligados perfeitamente com a estrutura FPGA através de uma espinha dorsal de interconexão de alta largura de banda. A placa de desenvolvimento DE1-SoC vem com memória DDR3 de alta velocidade, recursos de vídeo e áudio, conectividade Ethernet e muito mais, oferecendo inúmeras aplicações.Figura 1.
</p>
<p align="center">
  <img src = "https://github.com/Armaaaaaaaaaaaaaaaaaaaaaaaaaaando/Barramento/assets/129075181/a012967b-6624-4b1f-a59d-741b56e773cd" width = "450px"/>
  <p align="center">
    <strong>Figura 1: Kit de desenvolvimento DE1-SoC</strong> 
  </p>
</p>

<h4>Linguagem de programação C</h4>

<p>
C é uma linguagem de programação de uso geral conhecida por sua concisão, controle de fluxo moderno, estruturas de dados eficientes e ampla gama de operadores. Embora não seja uma linguagem de "altíssimo nível" nem "extensa", e não seja especializada em nenhuma área específica, sua flexibilidade e generalidade a tornam mais prática e eficaz para diversas tarefas em comparação com linguagens consideradas mais avançadas (KERNIGHAN & RITCHIE, 1983, pag. 8).
</p>

<h4>Monitores</h4>
<p>
Dois monitores foram utilizados para os testes e desenvolvimento: um monitor do tipo "Cathode Ray Tube" (CRT) e outro do tipo "Liquid Crystal Display" (LCD). Ambos apresentam conexão VGA e foram conectados, de acordo com a disponibilidade do equipamento no laboratório, ao kit de desenvolvimento DE1-SoC para verificar se a interação do hardware com o driver desenvolvido estaria ocorrendo de maneira satisfatória. Figura 2.
</p>

<p align="center">
  <img src = "https://github.com/Armaaaaaaaaaaaaaaaaaaaaaaaaaaando/Barramento/assets/129075181/a93c589a-7af7-450c-bebc-3afdfcb17657" width = "450px"/>
  <p align="center">
    <strong>Figura 2: Monitor CRT Dell</strong> 
  </p>
</p>

<p align="center">
  <img src = "https://github.com/Armaaaaaaaaaaaaaaaaaaaaaaaaaaando/Barramento/assets/129075181/53bacef8-4206-4f67-9757-bb5f96c66239" width = "450px"/>
  <p align="center">
    <strong>Figura 3: Monitor LCD Philips</strong> 
  </p>
</p>

<h4>Vscode</h4>
<p>
  O Visual Studio Code é um editor de código-fonte desenvolvido pela Microsoft para Windows, Linux e macOS. Foi utilizado no projeto como ambiente de desenvolvimento para codificar o driver e biblioteca.
</p>

<h4>Compilador</h4>
<p>
O Compilador GNU, também conhecido como GCC, é uma ferramenta de código aberto desenvolvida pelo Projeto GNU. Ele suporta várias linguagens de programação e é altamente portátil, funcionando em uma ampla variedade de sistemas operacionais. O GCC oferece opções avançadas de otimização e é amplamente utilizado tanto no desenvolvimento de software de código aberto quanto comercial. Sua capacidade de gerar código otimizado para diferentes arquiteturas o torna uma escolha popular entre os desenvolvedores. 
</p>


<h4>Processador gráfico</h4>
<p>O Processador Gráfico, desenvolvido pelo estudante Gabriel Sá Barreto Alves, é responsável por gerenciar o processo de renderização da imagem e executar um conjunto de instruções que permitem inicialmente inserir sprites, além de modificar o layout do background da tela e renderizar polígonos do tipo quadrado e triângulo. A GPU atua em conjunto com um processador de propósito geral, que para este projeto é o Dual-core ARM Cortex-A9 presente no kit, duas FIFOs (First In, First Out) e uma PLL (Phase Locked Loop), em resumo.(Figura 4)</p>

<p align="center">
  <img src = "https://github.com/Armaaaaaaaaaaaaaaaaaaaaaaaaaaando/Barramento/assets/129075181/591de9f8-4a37-4d81-8051-57e107099bac" width = "450px"/>
  <p align="center">
    <strong>Figura 4: Diagrama da estrutura interna do processador gráfico</strong> 
  </p>
</p>

<h4>GPU </h4>
<p>
 As GPUs são componentes essenciais em computadores, encarregadas do processamento de imagens. Com hardware especializado, elas lidam tanto com imagens 2D quanto 3D, realizando operações como cálculo de geometria, mapeamento de texturas e transformação de pixels.

No contexto dos jogos e aplicativos, as imagens 3D são geradas através de gráficos vetoriais. A GPU utiliza coordenadas (vértices) para formar polígonos que compõem a cena, aplicando texturas, iluminação e outros detalhes.

Após calcular a cena no espaço virtual, a GPU realiza a rasterização, convertendo-a em dados de pixels. Essas informações são então enviadas aos monitores, exibindo a imagem final. Esse ciclo se repete várias vezes por segundo, permitindo uma visualização fluida e dinâmica.
</p>
</div>


<div id= "jogo">

<h2>Desenvolvimento do jogo</h2>
<p>
  Após a conclusão de todos os processos de mapeamento de memória, criação do driver e desenvolvimento das funções da biblioteca, realizados no problema 2, foi iniciado o desenvolvimento do jogo solicitado no problema 3. 
</p>

<h3>
  Construção do cenário e sprite personalizado
</h3>

<p>
Antes de partir para a explicação de como o cenário foi feito e alguns conceitos importantes, é interessante mencionar o objetivo do jogo implementado e em qual jogo ja existente ele foi inspirado.
</p>
<p>
O jogo foi influenciado pelo "Jogo Mais Difícil do Mundo" (Figura 5), que consiste em um ponto principal, controlado pelo jogador, que deve se movimentar de um lado da plataforma ao outro. Até aqui parece fácil, mas a dificuldade surge quando são implementados outros objetos que impedem a passagem até o destino. Sempre que colide com um desses objetos, o personagem retorna à base inicial.
</p>

<p align="center">
  <img src = "https://github.com/user-attachments/assets/51454119-a83e-407e-ab54-a0bc25987261" width = "450px"/>
  <p align="center">
    <strong>Figura 5: "Jogo Mais Difícil do Mundo"</strong> 
  </p>
</p>

<p>
  O jogo original possui fases, o que justifica seu título de "Jogo Mais Difícil do Mundo". A cada fase completada, a próxima se torna progressivamente mais difícil, pois os cenários mudam, a velocidade dos pontos varia, ou a maneira de deslocamento dos pontos é alterada (Figura 6). Com essa influência em mente, partimos para o nosso desenvolvimento. Vale a pena ressaltar que nossa versão possui uma única fase, com um nível de dificuldade mediano, não sendo tão semelhante com o original.
</p>

<p align="center">
  <img src = "https://github.com/user-attachments/assets/56fdc963-fa8a-44f7-89fc-a378ed721dbe" width = "450px"/>
  <p align="center">
    <strong>Figura 6: Nível mais avançado do "Jogo Mais Difícil do Mundo"</strong> 
  </p>
</p>

<p>
Antes de se construir o cenário, fez-se o design do objeto principal, que seria controlado pelo jogador. A ideia para o personagem principal do jogo veio de um emoji do Facebook, mas com uma versão mais séria e sem óculos (Figura 7). Ele foi criado, primeiramente, através de uma ferramenta online chamada PixelArt. Com essa ferramenta, fez-se o desenho que foi implementado no jogo. O objetivo de se utilizar essa ferramenta foi facilitar a construção, visto que os blocos dos sprites têm 20x20 pixels. Portanto, seria necessário preencher 400 blocos de pixels para construir a imagem desejada, o que poderia não ficar satisfatório se feito de maneira desorganizada. Assim, a ferramenta mencionada ajudou na localização dos pixels, para que o emoji fosse desenhado de forma exata pela GPU.
</p>

<p align="center">
  <img src = "https://github.com/user-attachments/assets/d8fd9646-bd74-44e3-92a3-6fe89b942f83" width = "450px"/>
  <p align="center">
    <strong>Figura 7: Emoji base</strong> 
  </p>
</p>

<p>
  Utilizou-se a função editar_bloco_sprite para criar o sprite do objeto principal, combinada com laços de repetição "for", para imprimir linha a linha do desenho desejado. Vale a pena ressaltar que, como já se tinham 24 sprites na memória da GPU, associou-se o sprite ao registrador 25. Com isso, obteve-se o resultado descrito na figura 8.
</p>

<p align="center">
  <img src = "https://github.com/user-attachments/assets/c9545d0d-f481-4d5e-881c-c3e11fdc310b" width = "450px"/>
  <p align="center">
    <strong>Figura 8: Sprite personalizado do objeto principal</strong> 
  </p>
</p>

<p>
  Finalizado a parte de criação do sprite, partiu-se para a criação do cenário. Nosso objetivo foi criar algo simples, para que o jogador saia de uma plataforma e chegue a outra de forma intuitiva. Assim, nosso cenário não possui muitas curvas, sendo um caminho consideravelmente simples. A dificuldade estará na movimentação dos sprites secundários, que serão explicados mais adiante.
</p>

<p>
A construção do cenário foi possível graças à função editar_bloco_background, disponível na biblioteca já implementada e utilizada no problema anterior. De forma semelhante à construção do sprite, utilizaram-se laços de repetição "for" para fornecer os parâmetros necessários (coordenadas, cor, etc.) para a função que edita o background, desenhando, assim, pixel a pixel a imagem. O cenário base foi feito por meio da ferramenta PixelArt, que ajudou a determinar as coordenadas dos pixels que seriam modificados.
Com isso, obteve-se um fundo preto, com uma plataforma e os pontos de início pintados de verde e os de chegada pintados de vermelho (Figura 9).
</p>

<p align="center">
  <img src = "https://github.com/user-attachments/assets/0ca465df-3683-44e5-ab4b-8aff0dcf1048" width = "450px"/>
  <p align="center">
    <strong>Figura 9: Cenário do jogo</strong> 
  </p>
</p>



<h3>
  Movimentação com o mouse
</h3>

<p>
O objeto principal tem o objetivo de se movimentar pelo mapa para seguir a funcionalidade do jogo. Para realizar esse movimento e permitir a interação do jogador, utilizou-se o mouse. Com o auxílio da biblioteca input.h, foi possível abrir o arquivo do dispositivo e capturar os eventos ao movimentá-lo. Dessa forma, associou-se o movimento do mouse às coordenadas do sprite e, ao imprimi-lo na tela, foi possível incrementar suas coordenadas de impressão com as coordenadas do mouse, permitindo que o sprite do objeto principal se movesse com uma animação semelhante à do ponteiro do Windows.
</p>


<h3>
  Movimentação dos sprites secundários
</h3>

<p>
  Foi utilizado um total de 10 sprites já contidos no banco de registradores da GPU. A funcionalidade de 9 deles era impedir que o sprite principal chegasse até a plataforma de chegada, enquanto um deles deveria ser coletado na chegada para indicar que o jogo foi vencido (figura 10).
</p>
<p>
Com isso em mente, a utilização dos sprites foi possível graças à função print_sprite da biblioteca, na qual se imprimiram na tela 9 sprites "inimigos". Após posicionar todos na tela, foi necessário implementar uma lógica para que eles se movimentassem, de maneira semelhante ao sprite principal, modificando as coordenadas x e y do sprite. Entretanto, essa movimentação não foi feita pelo mouse, mas de forma automática pelo jogo. Os dois primeiros sprites se movimentavam da direita para a esquerda, o que foi possível ao armazenar a posição inicial deles em variáveis e fazer o deslocamento somando um. Quando o sprite chegava ao limite da plataforma, todo aquele valor que foi somado era subtraído da coordenada para que ele voltasse à posição inicial.
Isso foi feito através de duas variáveis: a posição inicial do x e do y, e uma variável de distância, que indicava ao sprite quanto ele iria percorrer antes de voltar. O limite percorrido era até ele tocar na parede da plataforma, o que fazia com que todo o valor acrescentado fosse subtraído, retornando ao estado inicial. É importante destacar que: quanto maior o valor incrementado, maior o velocidade dos sprites passivos.
</p>
<p>
Essa lógica foi implementada para todos os sprites que se movimentavam da direita para a esquerda, de cima para baixo e outros tipos de movimento.
</p>

<p align="center">
  <img src = "https://github.com/user-attachments/assets/b4806bae-4c5e-4cf8-b909-91191e51c4ef" width = "450px"/>
  <p align="center">
    <strong>Figura 10: Sprites secundários</strong> 
  </p>
</p>

<h3>
  Colisão dos sprites e cenário
</h3>
<p>
  completa ai armando, cm teu texto ou diogo sla
</p>




<h3>Componentes: mouse, botões e display de 7 segmentos</h3>

<h4> Botões</h4>
<p>
  Os botões da placa foram essenciais para o desenvolvimento do jogo. Com eles, foi possível atribuir algumas funcionalidades como: pausar, reiniciar, iniciar e encerrar o jogo. 
</p>

<p>
 Para ter acesso aos botões da placa, foi preciso criar uma função para gerenciar a interação e captura de eventos. Ela mapeia a memória de um ponteiro virtual para acessar esses botões e lê continuamente o estado deles por meio de um “while true”. Dependendo do botão pressionado, a função realiza ações específicas já citadas anteriormente
</p>

<p>
  Durante o desenvolvimento do jogo, surgiram problemas na leitura dos eventos dos botões devido ao fenômeno conhecido como "debounce". O debounce é um conceito que se refere ao atraso na leitura de um botão quando ele é pressionado ou solto, evitando que múltiplos sinais elétricos indesejados sejam interpretados como várias pressões. Embora o debounce ajude a estabilizar a leitura em muitos casos, ele acabou conflitando com o loop while true, que estava lendo os eventos muito rapidamente. Isso resultava em leituras imprecisas e em um comportamento indesejado dos botões.
</p>

<p>
 Os botões do jogo estão em um registrador mapeado na memória, onde cada um dos 4 bits representa um botão diferente. Quando um botão é pressionado, o bit correspondente a esse botão é definido como 0, indicando que o botão está pressionado. Quando o botão é solto, o bit é definido como 1, indicando que o botão não está mais pressionado. Essa configuração permite que o sistema identifique quais botões estão sendo pressionados em um determinado momento. 
</p>

<p>
  Para solucionar o problema de leitura rápida dos eventos, foi implementada uma variável chamada "estado" que aguarda o debounce acontecer, ou seja, espera que o registrador dos botões mapeados na memória mude os bits de estado indicando estar pressionado (0) para não pressionado (1) antes de permitir a leitura do evento novamente. Essa abordagem garantiu que, após um pressionamento, o sistema não registrasse novas entradas até que o botão estivesse completamente liberado. A variável "estado" atuava como um "filtro", evitando que múltiplos eventos fossem acionados em sequência rápida e assegurando que a interação do jogador fosse precisa e confiável.
</p>
<p>
  
</p>
</div>

<h2>
  Execução do projeto
</h2>
<p>
  Para utilizar o driver e a biblioteca, é imperativo seguir uma série de etapas específicas:

1. **Obtenção do Código-Fonte:** Primeiro, é necessário obter o código-fonte.
2. **Compilação do Código em C:** Em seguida, compile o código-fonte em C.
3. **Inserção do Driver no Kernel Linux:** Insira o driver compilado no kernel Linux.
4. **Criação do Nó de Acesso ao Dispositivo de Caractere:** Crie um nó de acesso ao dispositivo de caractere, garantindo que o número principal (major number) alocado dinamicamente ao driver pelo kernel seja ajustado adequadamente.
5. **Execução no Dispositivo FPGA:** Execute o driver em um dispositivo FPGA DE1-SoC, equipado com a GPU desenvolvida por Gabriel Sá Barreto Alves.

Adicionalmente, é essencial ajustar o caminho onde os arquivos gerados durante a compilação do módulo do kernel serão armazenados. Esses passos são cruciais para garantir a correta integração e funcionamento do driver e da biblioteca no ambiente especificado.
<p>

**Passo 1: Clonar o Repositório**

Abra o terminal e execute o seguinte comando para obter o código do repositório:

    git clone https://github.com/Armaaaaaaaaaaaaaaaaaaaaaaaaaaando/Barramento.git

**Passo 1.1: Ajustando major number do nó para dispositivo de caractere**

Caso necessário, na regra "all" do arquivo Makefile, ajuste o major number correspondente ao alocado pelo kernel no momento do carregamento do driver no sistema. O major number corresponde ao "X" mostrado no comando abaixo:

    mknod /dev/driver_dos_amgios c X 0
  
**Passo 1.2: Verificar major number**

Para verificar o major number voce precisa após inserir o driver utilizar o comando


    cat /proc/devices

**Passo 2: Carregando e configurando driver**

Para compilar, inserir o módulo kernel (driver) e criar um nó para o dispositivo de caractere (arquivo especial), use o comando:

    make

**Passo 3: Compilar o Código em C**

Para obter código teste da biblioteca, compile e execute o código usando o comando:

    make run

**Passo 4: Descarregando driver**

Para apagar os arquivos gerados de compilação do módulo, remover o módulo do kernel e seu nó (arquivo especial), use o comando:

    make clean

</div>




<h2>Referências</h2>

<p>
  KERNIGHAN, Brian; RITCHIE, Dennis. The C programming language. 2nd ed. Prentice Hall, 1983.
</p>
<p>
  MEU POSITIVO. O que é placa de vídeo (GPU)? Disponível em: https://www.meupositivo.com.br/doseujeito/tecnologia/o-que-e-placa-de-video-gpu/. Acesso em: 01 jun. 2024.
</p>
<p>
  ALVES, Gabriel Sá B.; DIAS, Anfranserai M.; SARINHO, Victor T.. Development of a Sprite-Based Architecture for Creating 2D Games in Reconfigurable Environments Using FPGA Devices. In: TRILHA DE COMPUTAÇÃO – ARTIGOS CURTOS - SIMPÓSIO BRASILEIRO DE JOGOS E ENTRETENIMENTO DIGITAL (SBGAMES), 21. , 2022, Natal/RN. Anais [...]. Porto Alegre: Sociedade Brasileira de Computação, 2022 . p. 283-288.
</p>





