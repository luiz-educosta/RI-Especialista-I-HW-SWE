# RI-Especialista-I-HW-SWE
***


## Estudo de caso
***

Você foi selecionado para fazer testes em um projeto no ICC. Este projeto tem o intuito de avisar quando a porta de um cofre é aberta e possui as seguintes características:

1. Possui Comunicação LoRa -  Cliente P2P;
1. Uma entrada para o sensor magnético;
1. Dois leds (verde e vermelho);
1. Um buzzer.

Foi projetado um firmware que controla todos os periféricos descritos acima. Dentre as funções desse firmware você terá que testar as seguintes ações relacionada a violação da porta.

**Cenário**: Violação da porta.

### Ações que o firmware deve tomar durante o cenário de violação:
***

1. Estabelecer comunicação com o gateway LoRa e ficar conectado a todo momento
1. Quando houver violação da porta, o sensor magnético é ativado e gera uma notificação que é enviado pela comunicação LoRa.
1. Ao detectar a violação o led vermelho acende e buzzer fica tocando a todo momento.
1. Violação resolvida led verde acende.

#### Sua função é testar se essas 4 funções estão funcionando de acordo. Para isso será necessário:
***

1. Criar um repositório no git e colocar todas as respostas dessa atividade e enviar o link por e-mail.

1. Descrever de forma sucinta, passo a passo, de como você fará os testes de cada ação - (formato word, seja organizado!).

1. Escolher uma das ações que será testada e fazer uma solução para teste automatizado.
Fique a vontade para usar qualquer tipo de ferramenta como Raspberry, BeagleBone, Arduino, KL25Z, MSP32 , etc.. (Seja criativo!) 

