# Sistema de Gerenciamento de Voos - Voo Seguro

Este é um sistema de gerenciamento de voos para a companhia fictícia **Voo Seguro**, desenvolvido como parte de um projeto interdisciplinar na **Pontifícia Universidade Católica de Minas Gerais (PUC-Minas)**. O sistema foi implementado em linguagem **C** e utiliza conceitos de estruturas de dados e engenharia de software.

---

## 📋 Funcionalidades

1. **Cadastro**:
   - Passageiros.
   - Tripulação (pilotos, copilotos, comissários).
   - Voos (data, hora, origem, destino, tripulação).
   - Assentos para cada voo.

2. **Reservas**:
   - Realizar reservas de assentos.
   - Cancelar reservas.

3. **Pesquisa**:
   - Buscar passageiros e tripulantes por código ou nome.
   - Listar voos associados a um passageiro.

4. **Programa de Fidelidade**:
   - Acumular pontos de fidelidade por voo.
   - Consultar pontos acumulados.

5. **Menu Interativo**:
   - Interface simples com opções para navegar pelas funcionalidades.

---

## 🔧 Estrutura do Projeto

```plaintext
VooSeguro/
├── src/                # Código-fonte
│   ├── main.c          # Arquivo principal do programa
│   ├── passageiro.c    # Lógica para cadastro e gestão de passageiros
│   ├── tripulacao.c    # Lógica para cadastro e gestão da tripulação
│   ├── voo.c           # Lógica para cadastro e gestão de voos
│   └── reserva.c       # Lógica para reservas e cancelamentos
├── tests/              # Testes automatizados com MUnit
│   ├── test_passageiro.c
│   ├── test_voo.c
│   └── test_reserva.c
├── docs/               # Documentação do projeto
│   ├── especificacao.pdf
│   └── relatorio_testes.pdf
└── README.md           # Documentação principal
```

---

## 🚀 Como Executar o Projeto

### **Requisitos**
- Compilador GCC ou similar.
- Sistema operacional compatível com C (Windows, macOS, Linux).

### **Passos para Compilar e Executar**

1. Clone o repositório:
   ```bash
   git clone https://github.com/theuzao/VooSeguro.git
   cd VooSeguro
   ```

2. Compile o código:
   ```bash
   gcc src/*.c -o voo_seguro
   ```

3. Execute o programa:
   ```bash
   ./voo_seguro
   ```

---

## 🧮 Testes Automatizados

Este projeto utiliza a biblioteca **MUnit** para testes automatizados. Para executar os testes:

1. Instale a biblioteca MUnit (veja a [documentação oficial](https://nemequ.github.io/munit/)).

2. Compile os testes:
   ```bash
   gcc -I tests/ src/*.c tests/*.c -o tests.out
   ```

3. Execute:
   ```bash
   ./tests.out
   ```

---

## 📚 Documentação

Toda a documentação está localizada na pasta `docs/`:
- **Especificação do Projeto**: Detalhes sobre os requisitos e funcionalidades.
- **Relatório de Testes**: Planejamento e resultados dos testes automatizados.

---

## 📚 Contribuidores

- **Matheus** - Desenvolvedor e gestor do repositório.
- **Arthur** - Desenvolvedor e colaborador no projeto.

---

## 🗓 Status do Projeto

- ✅ Estruturas de dados criadas.
- ✅ Cadastro de passageiros e tripulação.
- 🟨 Cadastro de voos e reservas em andamento.
- 🟨 Implementação dos testes unitários em progresso.

---

## 🔗 Links Importantes

- Repositório no GitHub: [Voo Seguro](https://github.com/theuzao/VooSeguro)
- Documentação MUnit: [MUnit](https://nemequ.github.io/munit/)

---

## 📝 Licença

Este projeto é exclusivamente acadêmico e não possui licença de uso comercial.
