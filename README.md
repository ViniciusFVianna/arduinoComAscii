# ASCII Motor Bridge - Nema 17 Indexer 🎯

Projeto de comunicação mecânica utilizando Arduino e motor de passo **Nema 17**. O sistema converte comandos numéricos em posições angulares precisas em um disco de caracteres para transcrição manual.

## ⚙️ Lógica de Funcionamento
O sistema utiliza um disco físico dividido em **17 posições** (Indexador):

* **Posição 0 (Home):** Ponto de repouso e calibração inicial.
* **Posições 1 a 16:** Intervalos úteis para mapeamento de caracteres.
* **Cálculo de Ângulo:** O sistema desconsidera a posição zero para o cálculo de divisão, resultando em:
    * $360 / (17 - 1) = 22.5°$ por posição.

## 🚀 Ciclo de Operação
1. O operador insere a posição desejada (1-16) via Serial Monitor.
2. O motor **Nema 17** desloca o disco até o ângulo correspondente.
3. O sistema permanece estático por **3 segundos**, permitindo que o operador utilize o caractere para escrever no papel.
4. O motor retorna automaticamente para a posição **Home (0)**.

## 🛠️ Hardware Utilizado
* **Motor:** Nema 17 (1.8° por passo / 200 passos por volta).
* **Driver:** A4988 ou DRV8825.
* **Microcontrolador:** Arduino (Uno/Nano/Mega).
* **Fonte:** 12V externa para alimentação do motor.

## 📂 Estrutura do Repositório
```text
├── docs/                   # Esquemas elétricos e fotos do disco
├── src/
│   └── ascii_communication/
│       └── ascii_communication.ino  # Código para Arduino IDE
├── .gitignore              # Filtro de arquivos temporários
└── README.md               # Documentação principal