# 💧 Sistema de Monitoramento de Qualidade da Água com IoT (MQTT)

Este projeto tem como objetivo monitorar a qualidade da água simulando a turbidez por meio de um potenciômetro. O sistema utiliza um microcontrolador **ESP32**, simulado na plataforma **Wokwi**, e publica os dados em tempo real para um **broker MQTT** público.

## 📡 Tecnologias e Protocolos
- ESP32 (simulado)
- Sensor de turbidez (simulado por potenciômetro)
- Protocolo MQTT
- Broker público: [test.mosquitto.org](https://test.mosquitto.org)
- Plataforma de simulação: [Wokwi](https://wokwi.com)

---

## 📁 Acessando o Projeto na Wokwi

Você pode simular o projeto diretamente no navegador:

🔗 **Link para o projeto no Wokwi**:  
[https://wokwi.com/projects/429580006199272449](https://wokwi.com/projects/429580006199272449)


### Componentes usados na simulação:
- ESP32 DevKit-C V4
- Potenciômetro (representando o sensor de turbidez)

O potenciômetro está conectado da seguinte forma:
- VCC → 3.3V
- GND → GND
- Sinal → GPIO34 (entrada analógica)

---

## 🧪 Funcionamento

O sistema lê periodicamente (a cada 5 segundos) o valor analógico do sensor e publica esse valor no **tópico MQTT** abaixo:

- sensor/turbidity

O envio é feito usando a biblioteca **PubSubClient** com o seguinte broker:

- Broker: test.mosquitto.org
- Porta: 1883

---

## 🛠 Como visualizar as mensagens MQTT (com Mosquitto)

Você pode usar o **Mosquitto client** para visualizar as mensagens publicadas.

### 1. Instale o Mosquitto client
**Linux (Ubuntu/Debian):**
```bash
sudo apt install mosquitto-clients
```

**Windows:**
Baixe em: [https://mosquitto.org/download/](https://mosquitto.org/download/)

### 2. Assine o tópico no terminal:
```bash
mosquitto_sub -h test.mosquitto.org -t sensor/turbidity -v
```
Isso irá exibir, em tempo real, os valores de turbidez enviados pelo ESP32 da simulação no Wokwi.

## 🧾 Licença
Este projeto é de uso acadêmico, desenvolvido para a disciplina de Internet das Coisas na Universidade Presbiteriana Mackenzie.

## 👨‍💻 Autor
Wesley Alves


