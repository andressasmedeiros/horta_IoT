#include <Wire.h>
#include <DHT.h>
#include "SSD1306Wire.h"
#include <WiFi.h>
#include <HTTPClient.h>

// ---- SENSOR LDR ----
#define LIGHT_SENSOR_PIN 36 // ESP32 pin GIOP36 (ADC0)

// ---- SENSOR DHT22 ----
#define DHTTYPE   DHT22
#define DHTPIN    4        // Pino do DHT22
DHT dht(DHTPIN, DHTTYPE, 22);

// ---- SENSOR DE CHUVA ----
#define POWER_PIN 14       // Alimentação do sensor de chuva
#define AO_PIN 39          // Saída analógica do sensor de chuva

// ---- SENSOR UMIDADE SOLO ----
#define SOIL_SENSOR_PIN 34  // Pino analógico do sensor de umidade do solo



// Pinos do NodeMCU
// SDA => D1
// SCL => D2

SSD1306Wire display(0x3c, 21, 22);

// Simulação dos estados
float temperatura = 0;
int umidade = 0;
int clima = 0;
int umidadeSolo = 0;
int statusLuz = 0;

const char *ssid = "nome-da-sua-rede";
const char *password = "senha-da-sua-rede";
const char *addr = "http://seu-ip-aqui";  // Endereço do servidor
const uint16_t port = 8080;
String token = "";

void setup() {
  Serial.begin(115200);
  display.init();
  display.flipScreenVertically();

  dht.begin();
  pinMode(POWER_PIN, OUTPUT);
  analogSetAttenuation(ADC_11db);

  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);

  unsigned long inicio = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - inicio < 10000) { // tenta por 10 segundos
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConectado ao WiFi!");
  } else {
    Serial.println("\nNão foi possível conectar ao WiFi!");
  }
}


void desenhaLampadaAcesa(int x, int y) {
  desenhaLampada(x, y);  // Desenha a lâmpada base

  int cx = x + round(13 * 0.65);  // Centro horizontal da lâmpada
  int topo = y - 4;               // Posiciona os raios acima da cúpula
  int comprimento = 4;
  int raio = 6;

  // Raio vertical (↑) - centralizado
  display.drawLine(cx, topo, cx, topo - raio);

  // ↖ esquerda
  display.drawLine(
    cx - 4, topo + 1,
    cx - 4 - comprimento, topo + 1 - comprimento);

  // ↗ direita
  display.drawLine(
    cx + 4, topo + 1,
    cx + 4 + comprimento, topo + 1 - comprimento);

  display.drawLine(
    cx - 10, topo + 5,  // início: mais afastado e mais pra baixo
    cx - 14, topo + 1   // fim: mais aberto e mais baixo
  );

  // Raio intermediário direita (↗ menos inclinado)
  display.drawLine(
    cx + 10, topo + 5,
    cx + 14, topo + 1);

  // Raio horizontal esquerda (←)
  display.drawLine(cx - 14, y + 6, cx - 14 - raio + 2, y + 6);

  // Raio horizontal direita (→)
  display.drawLine(cx + 14, y + 6, cx + 14 + raio - 2, y + 6);
}

void desenhaLampadaApagada(int x, int y) {
  desenhaLampada(x, y);  // base da lâmpada

  // "X" grande por cima da lâmpada toda
  int largura = round(27 * 0.65);     // ≈ 18
  int altura = round(19 * 0.65 * 2);  // ≈ 25

  int centroX = x + largura / 2;
  int centroY = y + altura / 2;

  display.drawLine(x, y, x + largura, y + altura);  // diagonal ↘
  display.drawLine(x, y + altura, x + largura, y);  // diagonal ↙
}


void desenhaLampada(int x, int y) {
  float escala = 0.65;  // fator de escala, diminui a lâmpada pela metade

  auto px2 = [&](int dx, int dy) {
    int dxs = round(dx * escala);
    int dys = round(dy * escala);
    display.fillRect(x + dxs, y + 2 * dys, 1, 2);
  };

  int i;

  for (i = 9; i <= 18; i++) px2(i, 0);
  for (i = 5; i <= 22; i++) px2(i, 1);
  for (i = 2; i <= 24; i++) px2(i, 2);
  for (i = 0; i <= 26; i++) px2(i, 3);
  for (i = 0; i <= 26; i++) px2(i, 4);
  for (i = 0; i <= 26; i++) px2(i, 5);
  for (i = 0; i <= 8; i++) px2(i, 6);
  for (i = 17; i <= 26; i++) px2(i, 6);
  for (i = 0; i <= 7; i++) px2(i, 7);
  for (i = 12; i <= 14; i++) px2(i, 7);
  for (i = 19; i <= 26; i++) px2(i, 7);
  for (i = 0; i <= 6; i++) px2(i, 8);
  for (i = 11; i <= 15; i++) px2(i, 8);
  for (i = 20; i <= 26; i++) px2(i, 8);
  for (i = 0; i <= 7; i++) px2(i, 9);
  for (i = 12; i <= 14; i++) px2(i, 9);
  for (i = 19; i <= 26; i++) px2(i, 9);
  for (i = 0; i <= 9; i++) px2(i, 10);
  for (i = 17; i <= 26; i++) px2(i, 10);
  for (i = 3; i <= 10; i++) px2(i, 11);
  for (i = 16; i <= 23; i++) px2(i, 11);
  for (i = 5; i <= 10; i++) px2(i, 12);
  for (i = 16; i <= 21; i++) px2(i, 12);
  for (i = 5; i <= 10; i++) px2(i, 13);
  for (i = 16; i <= 21; i++) px2(i, 13);
  for (i = 8; i <= 19; i++) px2(i, 15);
  for (i = 10; i <= 17; i++) px2(i, 16);
  for (i = 8; i <= 19; i++) px2(i, 17);
  for (i = 11; i <= 16; i++) px2(i, 19);
}

void desenhaStatusBar() {
  // Wi-Fi (bitmap)
  desenhaWifiIcon(98, 2);

  // Bateria
  int batX = 112;
  int batY = 0;
  display.drawRect(batX, batY + 1, 14, 7);
  display.drawRect(batX + 14, batY + 3, 2, 3);
  display.fillRect(batX + 2, batY + 3, 10, 3);  // Nível da bateria
}

void desenhaWifiIcon(int x, int y) {
  // Ícone base do Wi-Fi
  display.fillRect(x + 4, y + 6, 2, 1); // Arco de baixo
  display.fillRect(x + 3, y + 3, 4, 1);
  display.fillRect(x + 2, y + 4, 1, 1);
  display.fillRect(x + 7, y + 4, 1, 1);
  display.fillRect(x + 2, y, 6, 1);     // Arco de cima
  display.fillRect(x + 1, y + 1, 1, 1);
  display.fillRect(x + 8, y + 1, 1, 1);

  // Se estiver desconectado, desenha um "X" por cima
  if (WiFi.status() != WL_CONNECTED) {
    display.drawLine(x, y, x + 10, y + 10);  // Diagonal ↘
    display.drawLine(x, y + 10, x + 10, y);  // Diagonal ↙
  }
}


// Desenha o Sol (com raios maiores e um pouco para a direita)
void desenhaSolMini(int x, int y) {
  // Aumenta o raio do Sol de 6 para 10
  display.drawCircle(x + 6, y + 6, 8);  // Move um pouco para a direita e para baixo

  // Raios maiores
  for (int i = 0; i < 8; i++) {
    float angle = i * PI / 4;
    int x1 = x + 6 + cos(angle) * 12;  // Aumentando o comprimento dos raios
    int y1 = y + 6 + sin(angle) * 12;
    int x2 = x + 6 + cos(angle) * 14;  // Aumentando os raios
    int y2 = y + 6 + sin(angle) * 14;
    display.drawLine(x1, y1, x2, y2);
  }
}

// Desenha a Nuvem (movida um pouco para a esquerda e aumentada)
void desenhaNuvemMini(int x, int y) {
  // Aumenta o tamanho dos círculos da nuvem e move a nuvem levemente para a esquerda
  display.fillCircle(x - 2, y + 4, 6);    // Move um pouco para a esquerda e aumenta o tamanho
  display.fillCircle(x + 6, y + 2, 7);    // Move um pouco para a esquerda e aumenta o tamanho
  display.fillCircle(x + 14, y + 4, 6);   // Move um pouco para a esquerda e aumenta o tamanho
  display.fillRect(x - 2, y + 4, 20, 6);  // Ajusta o retângulo para cobrir os círculos
}

// Desenha a Chuva (com alinhamento e aumento do comprimento)
void desenhaChuvaMini(int x, int y) {
  desenhaNuvemMini(x, y);  // Move a nuvem um pouco para a esquerda

  // Ajusta a posição da chuva para ser mais centralizada e maior
  display.drawLine(x - 2, y + 10, x - 2, y + 20);    // Chuva um pouco maior e alinhada
  display.drawLine(x + 2, y + 10, x + 2, y + 20);    // Chuva um pouco maior e alinhada
  display.drawLine(x + 6, y + 10, x + 6, y + 20);    // Chuva um pouco maior e alinhada
  display.drawLine(x + 10, y + 10, x + 10, y + 20);  // Chuva um pouco maior e alinhada
}

void desenhaGota(int x, int y) {
  int largura = 8;  // Largura da gota
  int altura = 16;  // Altura total da gota

  // Desenha a parte superior da gota (triângulo invertido)
  display.drawLine(x, y + altura / 2, x + largura / 2, y);            // Linha esquerda
  display.drawLine(x + largura, y + altura / 2, x + largura / 2, y);  // Linha direita

  // Desenha a parte inferior da gota (círculo) conectando ao triângulo
  display.fillCircle(x + largura / 2, y + altura / 2, largura / 2);  // Base arredondada
}

void desenhaCarinha(int x, int y, int estado) {
  int raio = 12;
  display.drawCircle(x, y, raio);
  display.fillCircle(x - 5, y - 3, 2);
  display.fillCircle(x + 5, y - 3, 2);

  if (estado == 0) {
    display.drawLine(x - 6, y + 7, x, y + 3);
    display.drawLine(x, y + 3, x + 6, y + 7);
  } else if (estado == 1) {
    display.drawLine(x - 6, y + 7, x + 6, y + 7);
  } else {
    display.drawLine(x - 6, y + 3, x, y + 7);
    display.drawLine(x, y + 7, x + 6, y + 3);
  }
}

void lerDHT() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!isnan(h)) umidade = (int)h;
  if (!isnan(t)) temperatura = t;
}

void lerChuva() {
  digitalWrite(POWER_PIN, HIGH); // Liga o sensor
  delay(10);

  int rain_value = analogRead(AO_PIN);

  digitalWrite(POWER_PIN, LOW);  // Desliga o sensor

  // Interpretação simples
  if (rain_value >= 3800) {
    clima = 0; // Sol
  } else {
    clima = 2; // Chuva
  }
}

void atualizarClima() {
  // ---- Leitura do sensor de chuva ----
  digitalWrite(POWER_PIN, HIGH);
  delay(10);
  int rain_value = analogRead(AO_PIN);
  digitalWrite(POWER_PIN, LOW);

  // ---- Leitura do sensor de luz ----
  int luz_value = analogRead(LIGHT_SENSOR_PIN);

  // ---- Regra de prioridade ----
  if (rain_value < 3800) {
    clima = 2;  // 2 = Chuva 🌧️
  } 
  else {
    // Ajuste dos limites para nublado
    if (luz_value < 1500) {         // Ajuste maior sensibilidade
      clima = 1;  // 1 = Nublado ☁️
    } else {
      clima = 0;  // 0 = Sol ☀️
    }
  }
}

void lerUmidadeSolo() {
  int leitura = analogRead(SOIL_SENSOR_PIN);  
  umidadeSolo = map(leitura, 2900, 4095, 0, 100);  
  umidadeSolo = constrain(umidadeSolo, 0, 100);  
}


void enviarDadosParaAPI(float temperatura, int umidade, int umidadeSolo, int statusLuz) {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(addr) + ":" + String(port) + "/api/status";

    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + token);

    String payload = "{";
    payload += "\"statusLuz\":" + String(statusLuz) + ",";
    payload += "\"chuva\":" + String(clima == 2) + ",";
    payload += "\"temperatura\":" + String(temperatura, 1) + ",";
    payload += "\"umidade\":" + String(umidade) + ",";
    payload += "\"umidadeSolo\":" + String(umidadeSolo);
    payload += "}";

    Serial.println("Enviando para API:");
    Serial.println(payload);
    int httpResponseCode = http.POST(payload);

    if(httpResponseCode > 0) {
      Serial.println("Dados enviados com sucesso!");
      Serial.println(http.getString());
    } else {
      Serial.print("Erro ao enviar: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi desconectado");
  }
}



// TELA 1 – Água com carinha no texto
void telaAgua() {
  display.clear();
  desenhaStatusBar();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);

  // Exibir texto de acordo com o valor real
  if (umidadeSolo < 30) {
    display.drawString(64, 18, "Precisa regar");
    desenhaCarinha(64, 50, 0);  // carinha triste
  } else if (umidadeSolo < 70) {
    display.drawString(64, 18, "Água média");
    desenhaCarinha(64, 50, 1);  // carinha neutra
  } else {
    display.drawString(64, 18, "Não precisa regar");
    desenhaCarinha(64, 50, 2);  // carinha feliz
  }
  display.display();
}

// TELA 2 – Luz sem carinha
void telaLuz() {
  display.clear();
  desenhaStatusBar();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);

  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  if (analogValue < 40) {
    statusLuz = 0;
    display.drawString(64, 12, "Escuro");
    desenhaLampadaApagada(55, 40);
  } else if (analogValue < 800) {
    statusLuz = 1;
    display.drawString(64, 12, "Pouca luz");
    desenhaLampada(55, 40);
  } else if (analogValue < 2000) {
    statusLuz = 2;
    display.drawString(64, 12, "Luz média");
    desenhaLampadaAcesa(55, 40);
  } else if (analogValue < 3200) {
    statusLuz = 2;
    display.drawString(64, 12, "Muita Luz");
    desenhaLampadaAcesa(55, 40);
  } else {
    statusLuz = 2;
    display.drawString(64, 12, "Luz Intensa");
    desenhaLampadaAcesa(55, 40);
  }

  display.display();
}



void telaClimaFormatada() {
  display.clear();
  desenhaStatusBar();

  // Ícone do clima
  if (clima == 0) {
    desenhaSolMini(20, 20);
  } else if (clima == 1) {
    desenhaNuvemMini(20, 20);
  } else {
    desenhaChuvaMini(20, 20);
  }

  // Temperatura (lado direito)
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(50, 10, "Temp.");
  display.setFont(ArialMT_Plain_24);
  display.drawString(48, 24, String(temperatura, 0) + "°C");

  // Umidade
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(20, 54, "Umidade");

  desenhaGota(74, 50);

  display.setFont(ArialMT_Plain_16);
  display.drawString(86, 48, String(umidade) + "%");

  display.display();
}


void loop() {
  lerUmidadeSolo();
  telaAgua();
  delay(4000);

  telaLuz();
  delay(4000);

  lerDHT();         // Lê temperatura e umidade
  atualizarClima(); // Define o ícone de clima real
  telaClimaFormatada();

  enviarDadosParaAPI(temperatura, umidade, umidadeSolo, statusLuz);
  delay(5000);
}
