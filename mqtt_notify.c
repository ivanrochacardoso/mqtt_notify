#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MQTTClient.h>
#include <unistd.h>
#include <libgen.h>
#define ENV_FILE ".env"
#define BUFFER_SIZE 256
// Função para ler valores do .env
void load_env(const char *filename, char *broker, int *port, char *topic, char *user, char *password) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo .env");
        exit(EXIT_FAILURE);
    }
    char line[BUFFER_SIZE];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "MQTT_BROKER=%s", broker) == 1) continue;
        if (sscanf(line, "MQTT_PORT=%d", port) == 1) continue;
        if (sscanf(line, "MQTT_TOPIC=%s", topic) == 1) continue;
        if (sscanf(line, "MQTT_USER=%s", user) == 1) continue;
        if (sscanf(line, "MQTT_PASSWORD=%s", password) == 1) continue;
    }
    fclose(file);
}

// Callback para mensagens recebidas
int message_callback(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "notify-send 'Nova Mensagem MQTT' '%s'", (char *)message->payload);
    system(command);  // Chama o notify-send para exibir a notificação
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

// Função principal MQTT
void mqtt_notify(const char *broker, int port, const char *topic, const char *user, const char *password) {
    MQTTClient client;
    char address[BUFFER_SIZE];
    snprintf(address, sizeof(address), "tcp://%s:%d", broker, port);

    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.username = user;
    conn_opts.password = password;

    MQTTClient_create(&client, address, "mqtt_notify_client", MQTTCLIENT_PERSISTENCE_NONE, NULL);
    MQTTClient_setCallbacks(client, NULL, NULL, message_callback, NULL);

    if (MQTTClient_connect(client, &conn_opts) != MQTTCLIENT_SUCCESS) {
        fprintf(stderr, "Erro ao conectar ao broker MQTT\n");
        exit(EXIT_FAILURE);
    }

    MQTTClient_subscribe(client, topic, 0);

    while (1) {
        sleep(1);  // Mantém o loop ativo
    }

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
}

int main() {
    // char broker[BUFFER_SIZE] = {0};
    // int port = 1883;
    // char topic[BUFFER_SIZE] = {0};
    // char user[BUFFER_SIZE] = {0};
    // char password[BUFFER_SIZE] = {0};

    // load_env(ENV_FILE, broker, &port, topic, user, password);
    // mqtt_notify(broker, port, topic, user, password);

    // return 0;
        char broker[BUFFER_SIZE] = {0};
    int port = 1883;
    char topic[BUFFER_SIZE] = {0};
    char user[BUFFER_SIZE] = {0};
    char password[BUFFER_SIZE] = {0};
    
    // Obtém o caminho do executável
    char exec_path[BUFFER_SIZE];
    char env_path[BUFFER_SIZE];
    readlink("/proc/self/exe", exec_path, BUFFER_SIZE);
    char *exec_dir = dirname(exec_path);
    snprintf(env_path, BUFFER_SIZE, "%s/.env", exec_dir);
    
    load_env(env_path, broker, &port, topic, user, password);
    mqtt_notify(broker, port, topic, user, password);

    return 0;
}
