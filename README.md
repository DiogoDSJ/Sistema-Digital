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
  Vale a pena ressaltar que, no jogo, o sprite só pode se movimentar dentro da plataforma. Portanto, tivemos que implementar a técnica de colisão para limitar a movimentação do nosso sprite principal dentro da plataforma.

Isso foi possível associando a movimentação do sprite, feita através do mouse, com as coordenadas que delimitamos como limite, ou seja, as coordenadas até onde vai a plataforma. Foi feito um cálculo para que, quando as coordenadas do sprite principal atingissem o limite (ou melhor, uma parede da plataforma), ao invés de aumentar as coordenadas e alterar a posição do sprite, subtraímos o limite ultrapassado da posição do sprite, fazendo com que ele pareça estar parado no mesmo lugar, como se algo impedisse sua movimentação.

Essa funcionalidade só foi possível porque, para implementar o movimento do mouse, precisamos somar as coordenadas que obtemos com a movimentação do mouse. Assim, ao invés de somar e alterar a posição do sprite a partir daquele limite imposto pela coordenada da parede, subtraímos esse valor, fazendo com que a colisão do sprite com toda a plataforma fosse implementada, limitando a movimentação apenas naquele espaço.

</p>

<h3>Colisão de sprites</h3>
<p>
  A colisão dos sprites foi necessária para que, quando um dos sprites secundários que impedem a passagem tocasse no sprite principal, uma vida fosse reduzida e o sprite principal voltasse ao ponto de partida.

Essa colisão foi implementada de forma simples: através da coordenada onde se encontra o sprite, somamos 20 (que é o tamanho do sprite). Com isso, criamos uma condição `if` que verifica se a coordenada do sprite principal encostou no limite do sprite secundário, calculado através da soma da coordenada x do sprite mais 20 (seu tamanho). Isso também é feito com o eixo y.

Dessa forma, formamos um quadrado do tamanho do sprite secundário e, quando as coordenadas do sprite principal "batem" nesse limite, é detectada uma colisão. Uma vida do jogador é reduzida e o sprite é lançado de volta à plataforma de saída do jogo. Vale a pena ressaltar que o jogador possui 3 vidas, que serão sinalizadas no display de 7 segmentos, explicado adiante.

Assim, quando um dos nove sprites que impedem o deslocamento colide com o sprite principal, ele retorna à base. No entanto, quando o sprite principal colide com o sprite adicionado na linha de chegada, o jogador vence o jogo.

</p>




<h3>Componentes: botões e display de 7 segmentos</h3>

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

<h4>Display de 7 segmentos</h4>
<p>
   Primeiro, o arquivo de dispositivo /dev/mem é aberto, permitindo acesso a endereços físicos de memória. Caso haja algum erro na abertura do arquivo, uma mensagem de erro é exibida e a função retorna. Em seguida, a função mmap é usada para obter um mapeamento entre os endereços físicos e os endereços virtuais, possibilitando a manipulação da memória a partir do espaço de endereçamento do processo. Se o mapeamento falhar, uma mensagem de erro é exibida, o arquivo é fechado e a função retorna.
Após obter o mapeamento, os endereços dos displays de 7 segmentos são mapeados para ponteiros virtuais, com a ajuda de um mutex para garantir que esta operação seja segura em um ambiente multi-thread. Os ponteiros virtuais são definidos para cada um dos displays (HEX5 a HEX0). Entretanto, foram apenas utilizados os HEX0 e HEX1 para exibir vidas restantes e informar quando a habilidade foi usada pelo jogador.

</p>
  
</p>
</div>
<h3>Funções</h3>
<h4>
  Main
</h4>
<p>
  A função main do programa primeiro chama a função display, que é responsável por configurar os displays de 7 segmentos, mapeando a memória física para a memória virtual e definindo os valores dos segmentos dos displays. Essa função também chama alterar_display para gerenciar a exibição dos dígitos conforme necessário.
Em seguida, a função inicio é chamada. Essa função abre o dispositivo /dev/driver_dos_amigos, limpa e reseta o cenário do jogo chamando as funções limpa_tudo e zerar_tudo, define o fundo do jogo e pinta letras de diferentes cores. Ela também mapeia o endereço virtual para acessar as chaves (KEY_ptr). Depois disso, entra em um loop infinito para monitorar o botão KEY0. Quando o botão é pressionado, o cenário é configurado e a função jogo é chamada para iniciar o jogo.
Além disso, a função `chamar_threads` inicializa todas as threads do jogo, coloca-as em execução e, posteriormente, encerra-as.

</p>

<h4>
  Componentes
</h4>
<p>
  O arquivo componentes define duas funções, mousefik e botao, que serão usadas como threads em um jogo. A função mousefik é responsável por gerenciar a interação com o mouse. Primeiro, ela abre o dispositivo de entrada do mouse e começa a ler continuamente os eventos do dispositivo. Com base nos movimentos do mouse, a função ajusta a posição de um sprite na tela. Além disso, a função verifica colisões entre o sprite e as bordas da tela, bem como com obstáculos específicos definidos no código. Quando uma colisão é detectada, a posição do sprite é ajustada para evitar que ele saia dos limites permitidos. A função também atualiza a posição do sprite na tela, garantindo que as colisões sejam respeitadas. Além dos movimentos, a função reage a cliques do mouse, ativando ou desativando um "cheat" ou uma "habilidade" dependendo de qual botão é pressionado.
A função botao é responsável por gerenciar a interação com botões físicos. Ela mapeia a memória de um ponteiro virtual para acessar esses botões e lê continuamente o estado deles. Dependendo do botão pressionado, a função realiza ações específicas. Quando o botão de início é pressionado, o jogo começa. Se o botão de reset for pressionado, o jogo é reiniciado. Outro botão permite reiniciar a configuração, enquanto um quarto botão pode pausar ou despausar o jogo. Após realizar a ação correspondente, a função retorna ao estado de leitura contínua, aguardando a próxima interação do usuário.
Essas funções são utilizadas em um contexto de jogo para permitir que o usuário controle o jogo através de um mouse e botões físicos. Isso proporciona uma interação dinâmica e responsiva, onde o usuário pode mover um sprite pela tela usando o mouse e controlar o estado do jogo utilizando os botões físicos.

</p>

<h4>
  Game
</h4>
<p>
  A função setar inicializa variáveis de direção, define a posição inicial do sprite principal, ativa o sprite, inicializa a variável de habilidade e desbloqueia o mutex para permitir a impressão do sprite. Em seguida, imprime o sprite principal na posição inicial, atualiza o display hexadecimal e define a variável diminuir_display como 3.

A função setar_sprites define as posições iniciais dos obstáculos e bloqueia o mutex para operações seguras. Em seguida, imprime cada um dos obstáculos nas posições especificadas e desbloqueia o mutex.

A função obstaculo utiliza nanosleep para criar um intervalo de tempo entre as iterações do loop. Define as posições iniciais de vários obstáculos e entra em um loop que verifica colisões e movimenta os obstáculos. Se não houver pausa no jogo (pause_jogo == 0), bloqueia o mutex, imprime os obstáculos, desbloqueia o mutex e ajusta a posição dos obstáculos de acordo com as variáveis de direção. Verifica colisões entre o sprite principal e os obstáculos e, em caso de colisão, redefine a posição do sprite principal, imprime novamente o sprite, desbloqueia o mutex, reseta a habilidade, decrementa diminuir_display e chama a função alterar_display.

A função jogo configura e inicia um jogo. Primeiro, abre um dispositivo específico usando um caminho predefinido, que provavelmente se refere a algum hardware ou driver relacionado ao jogo. Em seguida, configura várias partes do cenário do jogo através de loops que preenchem blocos de fundo com diferentes cores. Depois, uma imagem é definida por uma matriz de valores que representam diferentes cores. O código percorre essa matriz e desenha os sprites correspondentes no cenário, configurando suas cores adequadamente. Para garantir a segurança durante as operações de desenho, mutexes são usados para sincronização. Após configurar o cenário e desenhar a imagem, o código inicia as threads necessárias para a execução do jogo. Em seguida, lê dados do dispositivo para verificar se tudo está funcionando corretamente. Finalmente, o dispositivo é fechado para liberar os recursos.

A função obstaculo_velocidade_diferente movimenta os obstáculos e verifica colisões com o jogador. Ela inicia um intervalo de 9 milissegundos e define as posições iniciais dos obstáculos e do prêmio. Dentro de um loop infinito, a função trava o mutex para garantir que a impressão dos sprites (imagens dos obstáculos) seja atômica e depois destrava o mutex. Os obstáculos se movem em diferentes direções com base nas variáveis de direção dir e dir2. As colisões entre o jogador e os obstáculos são verificadas. Se houver uma colisão, o jogador é reposicionado, a habilidade especial é desativada, e o display é atualizado. A colisão com o prêmio termina o jogo, declarando o jogador vencedor.

A função habilidade_parar verifica se a habilidade especial do jogador está ativa (habilidade == 1). Se estiver, aciona o display de 7 segmentos, aguardando 1 segundo, depois desativa a habilidade.

A função voce_ganhou é chamada quando o jogador coleta o prêmio. Ela reseta o jogo, exibe a mensagem "YOU WON" por 2 segundos e encerra o programa.

A função voce_perdeu é chamada quando o jogador colide com um obstáculo em certas condições, reseta o jogo, exibe a mensagem "GAME OVER" por 2 segundos e encerra o programa.
</p>


<h2>Telas</h2>
<p>
  O arquivo `telas` é responsável pela edição das telas do jogo. Nele, é utilizado um loop `for` que percorre todo o background, pintando onde necessário para exibir as mensagens apropriadas. As mensagens incluem "Green to Red" na tela de início, "You Won" na tela final em caso de vitória, e "Game Over" na tela final em caso de derrota.
</p>

<h2>
  Resultados
</h2>
<p>
  Sendo assim, como resultados, tivemos a funcionalidade do jogo mais difícil do mundo. Com isso, o fluxo de execução se dá quando a função main é chamada. Com ela, é chamada a função display, que faz o mapeamento de memória do display e desliga os displays de 7 segmentos que não serão usados. O 0 e o 3 são acesos nos displays HEX1 e HEX0, indicando a vida. Após a conclusão, a função inicio é chamada. Nela, temos o mapeamento de memória dos botões, e são enviadas à GPU as informações para desenhar na tela a imagem com o título do jogo. Após isso, entra-se em um loop, esperando que o botão KEY0 seja pressionado. Com isso, temos o resultado:
</p>
<p align="center">
  <img src = "https://github.com/user-attachments/assets/0e6caeb7-dcda-45c0-9653-10ccf065827c" width = "450px"/>
  <p align="center">
    <strong>Figura 11: Tela incial</strong> 
  </p>
</p>

<p>
  Logo após, o jogo é iniciado, e todas as threads são chamadas. Isso faz com que a execução da movimentação dos sprites, a captação do mouse, a captação dos botões e habilidades aconteçam ao mesmo tempo. Sendo assim, temos o resultado:
</p>

<p align="center">
  <img src = "https://github.com/user-attachments/assets/52270309-b153-4d55-a7d1-26e5675d36bc" width = "450px"/>
  <p align="center">
    <strong>Figura 12: Tela de jogo</strong> 
  </p>
</p>

<p>
  Com o jogo pronto para jogar, o objetivo é chegar no ponto vermelho do mapa. Caso você não consiga e colida 3 vezes com outros sprites secundários, a tela seguinte aparecerá para você, e o jogo será encerrado após 3 segundos.
</p>

<p align="center">
  <img src = "https://github.com/user-attachments/assets/c8ea5c44-1887-494f-9aa9-4a31ae5c9724" width = "450px"/>
  <p align="center">
    <strong>Figura 13: Tela de game over</strong> 
  </p>
</p>

<p>
  Com o jogo pronto para jogar, o objetivo é chegar no ponto vermelho do mapa. Caso você não consiga e colida 3 vezes com outros sprites secundários, a tela seguinte aparecerá para você, e o jogo será encerrado após 3 segundos. Entretanto, caso você consiga cumprir o objetivo e capturar o diamante no outro lado do mapa, você terá vencido o jogo, e a tela seguinte aparecerá para você, seguida do fechamento do jogo.
</p>

<p align="center">
  <img src = "https://github.com/user-attachments/assets/e51fd5f8-d821-40b2-8305-a961ca293d14" width = "450px"/>
  <p align="center">
    <strong>Figura 14: Tela de you won</strong> 
  </p>
</p>

<p>
  Vale a pena ressaltar que você pode utilizar habilidades durante o jogo. A habilidade consiste em paralisar a movimentação dos sprites secundários por 1 segundo, permitindo que você passe de uma posição difícil. No entanto, ela só está disponível uma vez por jogo; caso você perca uma vida, poderá utilizá-la novamente. A habilidade é ativada pelo clique direito do mouse.
Além disso, você pode utilizar o modo debug, como um hack. Dessa forma, você pode parar todos os sprites secundários e seguir até o caminho da vitória. Para isso, basta pausar o jogo e segurar o botão do meio do mouse.
E por fim, caso você queira pausar o jogo, apenas pressione o botão KEY 3 da placa. Para encerrar o jogo, pressione o botão KEY 1, e para reiniciar a posição do sprite juntamente com a vida, pressione o botão KEY 2. Todas essas atividades podem ser realizadas durante a execução do jogo.

</p>

<h2> Fluxograma </h2>
<p align="center">
  <img src = "https://github.com/user-attachments/assets/5541657c-ca0d-44f9-8e5f-9c3488905950" width = "800px"/>
  <p align="center">
    <strong>Figura 15: Fluxograma</strong> 
  </p>
</p>



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





