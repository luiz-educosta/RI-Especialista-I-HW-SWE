# RI-Especialista-I-HW-SWE

**Este repositório foi criado com o intuito de postar a resolução do teste de seleção para vaga interna de Especialista I (HW/SW) no ICC - Inatel.**

**Abaixo, encontra-se o cenário proposto e os respectivos links das resoluções.**
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

1. Estabelecer comunicação com o gateway LoRa e ficar conectado a todo momento. [Resposta](https://github.com/luiz-educosta/RI-Especialista-I-HW-SWE/blob/main/RI-Especialista-I-HW-SWE/RespostasTestes/1-Estabelecer-comunica%C3%A7%C3%A3o-com-o-gateway.txt)
1. Quando houver violação da porta, o sensor magnético é ativado e gera uma notificação que é enviado pela comunicação LoRa. [Resposta](https://github.com/luiz-educosta/RI-Especialista-I-HW-SWE/blob/main/RI-Especialista-I-HW-SWE/RespostasTestes/2-Notificacao.txt)
1. Ao detectar a violação o led vermelho acende e buzzer fica tocando a todo momento. [Resposta](https://github.com/luiz-educosta/RI-Especialista-I-HW-SWE/blob/main/RI-Especialista-I-HW-SWE/RespostasTestes/3-Verificando-LEDvermelho-Buzzer.txt)
1. Violação resolvida led verde acende. [Resposta](https://github.com/luiz-educosta/RI-Especialista-I-HW-SWE/blob/main/RI-Especialista-I-HW-SWE/RespostasTestes/4-Violacao-resolvida.txt)

### Sua função é testar se essas 4 funções estão funcionando de acordo. Para isso será necessário:
***

1. Criar um repositório no git e colocar todas as respostas dessa atividade e enviar o link por e-mail. [Clique aqui](https://github.com/luiz-educosta/RI-Especialista-I-HW-SWE)

1. Descrever de forma sucinta, passo a passo, de como você fará os testes de cada ação - (formato word, seja organizado!). [Ver documento](https://github.com/luiz-educosta/RI-Especialista-I-HW-SWE/tree/main/RI-Especialista-I-HW-SWE/Documentacao)

1. Escolher uma das ações que será testada e fazer uma solução para teste automatizado.
Fique a vontade para usar qualquer tipo de ferramenta como Raspberry, BeagleBone, Arduino, KL25Z, MSP32 , etc.. (Seja criativo!) [Confira o teste automatizado](https://github.com/luiz-educosta/RI-Especialista-I-HW-SWE/blob/main/RI-Especialista-I-HW-SWE/SolucaoAutomatizada/CodigoFonte/CodigoFonte.ino) 

