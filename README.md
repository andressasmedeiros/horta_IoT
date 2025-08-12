# Projeto Horta Inteligente - IoT com Arduino e Spring Boot

## Sobre o projeto

Este projeto foi desenvolvido como parte de uma **atividade extensionista da UNINTER**, no curso de **Análise e Desenvolvimento de Sistemas**.  
Apesar de ter surgido como um trabalho acadêmico, **foi um prazer enorme desenvolver essa solução**, unindo IoT, backend e frontend para criar um sistema funcional e prático para monitoramento de hortas.

---

## Objetivo

O objetivo principal é **automatizar o monitoramento de uma horta doméstica**, fornecendo informações em tempo real sobre:
- 🌡️ Temperatura do ar
- 💧 Umidade do ar
- 🌱 Umidade do solo
- ☀️ Intensidade de luz ambiente
- 🚿 Indicação se a planta precisa ou não ser regada
- 🌧️ Indica se está chovendo
- 💻 Interação com pesquisa no google dentro da plataforma, para pesquisar dúvidas e curiosidades sem sair da tela
- 🛜 Conexão entre o protótipo via Wifi
- 🖥️ Tela OLED no arduíno para interação local, mostrando todos os dados

A ideia é **tornar o cuidado com hortas mais fácil, eficiente e acessível**, ajudando na produção sustentável de alimentos em casa.

<img width="1917" height="941" alt="Captura de tela 2025-08-05 225454" src="https://github.com/user-attachments/assets/a3c35299-f501-4c5c-9ad2-c82f284d064f" />

<img width="567" height="412" alt="Captura de tela 2025-08-05 230859" src="https://github.com/user-attachments/assets/1cf402ce-1038-4edc-ba9f-4b30c410138f" />

---

## 🛠Tecnologias utilizadas

### 🔹 **IoT (Hardware)**
- Arduino/ESP32 (programado em **C++**) para coleta de dados dos sensores.

### 🔹 **Backend**
- **Java** com **Spring Boot** para criação da API REST que recebe os dados do Arduino e disponibiliza para o frontend.

### 🔹 **Frontend**
- **HTML**, **CSS** e **JavaScript puro**, exibindo os dados em cards dinâmicos e amigáveis ao usuário.

---

## Status do projeto

- ✅ Protótipo funcional concluído
- ✅ Testes realizados com sucesso
- ✅ Imagens ainda em versão de teste
- 🔜 Próxima etapa: finalizar protótipo e implementar em uma horta real

---

## Funcionalidades principais

- Coleta e envio de dados do Arduino para a API
- Exibição dos dados em tempo real no site
- Identificação automática da necessidade de rega
- Status visual de conexão com o dispositivo
- Exibição de curiosidades sobre hortas

---

## Agradecimentos

Esse projeto foi mais do que uma atividade acadêmica, foi **uma experiência incrível de aprendizado**, onde pude unir diferentes áreas da tecnologia em uma solução completa e funcional.

> "Unir tecnologia e natureza é um dos caminhos para um futuro mais sustentável." 🌍💚

---

## Aprendizados e Dificuldades
- Maior dificuldade: integrar corretamente todos os componentes do Arduino (sensores, tela OLED, comunicação via Wi-Fi) para funcionarem em conjunto, sem conflitos de código ou falhas na leitura dos dados.

- Aprendizados:
    - Foi meu primeiro contato com IoT, Arduino e sensores, o que me permitiu conhecer melhor esse universo da eletrônica aplicada à programação.
    - Aprendi a estruturar a comunicação entre hardware e software usando uma API REST, criando um ecossistema funcional entre o dispositivo físico e a aplicação web.
    - Desenvolvi habilidades para depurar problemas de hardware e código simultaneamente, algo muito diferente do desenvolvimento apenas de software.



### Autor

👩‍💻 **Andressa Medeiros**  
📚 Estudante de Análise e Desenvolvimento de Sistemas - UNINTER

---

