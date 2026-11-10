# Projetos de Arduino

Repositório com meus projetos de Arduino e eletrônica.

## Projetos

| Projeto | Descrição | Conceitos |
|---|---|---|
| [Semáforo com botão de pedestre](./semaforo-arduino) | Semáforo de 3 LEDs que fecha para os carros quando o pedestre aperta o botão, com buzzer durante a travessia. | `millis()`, máquina de estados, `INPUT_PULLUP`, `tone()` |

_Novos projetos serão adicionados aqui._

## Como usar os projetos

1. Instale a [Arduino IDE](https://www.arduino.cc/en/software).
2. Baixe o repositório (**Code → Download ZIP**) e extraia.
3. Abra a pasta do projeto desejado e dê dois cliques no arquivo `.ino`.
4. Monte o circuito conforme o README do projeto.
5. Selecione a placa e a porta em *Ferramentas* e clique em **Carregar**.

Sem Arduino físico? Os projetos que têm `diagram.json` podem ser simulados no [Wokwi](https://wokwi.com): crie um projeto **Arduino Uno**, cole o `diagram.json` na aba de diagrama e o código `.ino` na aba do sketch.

## Estrutura do repositório

```
arduino/
├── README.md
└── semaforo-arduino/
    ├── README.md
    ├── semaforo-arduino.ino
    └── diagram.json
```

Cada projeto fica na sua própria pasta, com código, README e, quando possível, o diagrama para simulação.

## Ferramentas

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Wokwi](https://img.shields.io/badge/Wokwi-simulador-blue?style=for-the-badge)

## Autor

Feito por **Gabriel Alasca**.
- GitHub: [@gabrielalasca](https://github.com/gabrielalasca)
- Instagram: [@wx_gabe](https://instagram.com/wx_gabe)
