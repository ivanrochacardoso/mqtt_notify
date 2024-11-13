## mqtt_notify

mqtt_notify é uma aplicação simples em C que se conecta a um broker MQTT, escuta mensagens em um tópico específico e exibe notificações de desktop para cada mensagem recebida. Ele é útil para quem deseja receber alertas em tempo real, como compromissos ou eventos críticos, diretamente na área de trabalho.

Essa ferramenta pode ser integrada com tarefas programadas (como o cron no Linux), monitoramento de dispositivos IoT, e outros sistemas que utilizam MQTT para comunicar eventos e notificações.

Funcionalidades
Conexão com um broker MQTT.
Assinatura em um tópico específico para escutar mensagens.
Exibição de notificações na área de trabalho (usando notify-send no Linux).
Autenticação opcional no broker MQTT com nome de usuário e senha.
Requisitos
Sistemas Operacionais Suportados
Linux (Desenvolvido e testado no Debian 12).


A biblioteca Paho MQTT C não vem instalada por padrão, então você precisará baixá-la e instalá-la. Aqui estão as etapas para fazer isso no Debian:

Passo 1: Instalar Dependências
Primeiro, instale as dependências necessárias para compilar a biblioteca:

```shell
sudo apt update
sudo apt install build-essential cmake libssl-dev
```
Passo 2: Baixar e Compilar a Biblioteca Paho MQTT C
Clone o repositório da Paho MQTT C do GitHub:

```shell
git clone https://github.com/eclipse/paho.mqtt.c.git
```
Compile e instale a biblioteca:

```shell
cd paho.mqtt.c
cmake -Bbuild -H. -DPAHO_WITH_SSL=ON
sudo cmake --build build/ --target install
sudo ldconfig
```
O comando cmake -Bbuild -H. cria a configuração de compilação.
O sudo cmake --build build/ --target install compila e instala a biblioteca.
sudo ldconfig atualiza o cache das bibliotecas para que o sistema encontre a biblioteca instalada.


### passo 3 compilar com gcc
gcc mqtt_notify.c -o mqtt_notify -lpaho-mqtt3c

