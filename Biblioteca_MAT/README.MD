# Biblioteca Matemática de Vetores em C

Programa em C (`biblioteca_mat.c`) que armazena vetores de números
reais em arrays alocados dinamicamente e implementa operações
matemáticas sobre eles, incluindo similaridade de cosseno — sem uso
de bibliotecas externas para as operações da estrutura de dados.

## Requisitos

- GCC (ou outro compilador C compatível com C99)
- Biblioteca matemática padrão (`libm`), já presente em qualquer
  instalação padrão de Linux/macOS

## Compilação

```bash
gcc -Wall -Wextra -o biblioteca_mat biblioteca_mat.c -lm
```

> A flag `-lm` é necessária porque o programa usa `sqrtf` (de
> `math.h`) no cálculo da norma de um vetor. Sem ela, o linker pode
> falhar com `undefined reference to 'sqrtf'` em alguns sistemas.

## Execução

```bash
./biblioteca_mat
```

O programa exibe um menu numerado e aguarda a opção do usuário via
teclado, repetindo até que `0` seja escolhido.

```
===== MENU =====
1  - Criar novo vetor
2  - Exibir vetores armazenados
3  - Multiplicar vetor por escalar
4  - Somar dois vetores
5 - Produto escalar entre dois vetores
6 - Calcular norma de um vetor
7 - Similaridade de cosseno entre dois vetores
8 - Determinar o vetor mais similar a um vetor de consulta
0 - Sair
Escolha uma opcao:
```

### Observação sobre `buscar` e `remover`

As operações `inicializar_array`, `inserir`, `imprimir`, `buscar` e
`remover` fazem parte das **operações da estrutura de dados**
exigidas pelo enunciado e estão implementadas e testadas (veja a
seção de testes abaixo). `buscar` e `remover` não aparecem no menu
porque a lista de **funcionalidades do sistema** do enunciado não as
inclui — a estrutura oferece essas operações, mas o sistema não
precisa expô-las ao usuário final.

---

## Exemplos de execução

Os exemplos abaixo usam os seguintes vetores de entrada:

- **Vetor 0:** `[0.80, 0.20, 0.50, 0.90, 0.30]`
- **Vetor 1:** `[0.10, 0.90, 0.40, 0.20, 0.70]`
- **Vetor 2:** `[0.75, 0.25, 0.55, 0.85, 0.35]`

### 1. Criar um vetor (opção 1)

```
Escolha uma opcao: 1
Informe o tamanho do novo vetor: 5
Informe os 5 valores reais do vetor 0:
  posicao 0: 0.80
  posicao 1: 0.20
  posicao 2: 0.50
  posicao 3: 0.90
  posicao 4: 0.30
Vetor criado com sucesso!
```

### 2. Exibir vetores armazenados (opção 2)

```
Escolha uma opcao: 2
Vetor 0: [0.80, 0.20, 0.50, 0.90, 0.30]
Vetor 1: [0.10, 0.90, 0.40, 0.20, 0.70]
Vetor 2: [0.75, 0.25, 0.55, 0.85, 0.35]
```

### 3. Multiplicar vetor por escalar (opção 3)

```
Escolha uma opcao: 3
[...lista os vetores...]
Escolha o vetor a multiplicar: 1
Informe o escalar: 2.0
Resultado: [0.20, 1.80, 0.80, 0.40, 1.40]
Resultado armazenado como vetor 3.
```

### 4. Somar dois vetores (opção 4)

```
Escolha uma opcao: 4
[...lista os vetores...]
Escolha o primeiro vetor: 0
[...lista os vetores...]
Escolha o segundo vetor: 1
Resultado: [0.90, 1.10, 0.90, 1.10, 1.00]
Resultado armazenado como vetor 4.
```

### 5. Produto escalar entre dois vetores (opção 5)

```
Escolha uma opcao: 5
Escolha o primeiro vetor: 0
Escolha o segundo vetor: 1
Produto escalar: 0.8500
```

### 6. Norma de um vetor (opção 6)

```
Escolha uma opcao: 6
Escolha o vetor: 0
Norma: 1.3528
```

### 7. Similaridade de cosseno entre dois vetores (opção 7)

```
Escolha uma opcao: 7
Escolha o primeiro vetor: 0
Escolha o segundo vetor: 1
Similaridade de cosseno: 0.5113
```

### 8. Vetor mais similar a um vetor de consulta (opção 8)

```
Escolha uma opcao: 8
Escolha o vetor de consulta: 0
Comparando vetor 0 com os demais:
  -> Similaridade com vetor 1: 0.5113
  -> Similaridade com vetor 2: 0.9967
  -> Similaridade com vetor 3: 0.5113
  -> Similaridade com vetor 4: 0.8825
O vetor mais similar ao vetor 0 e o vetor 2.
```

### Opção inválida

```
Escolha uma opcao: 99
Opcao invalida.
```

---

## Conjunto de testes realizados

Todos os testes abaixo foram executados de fato (via automação de
entrada padrão) e os resultados numéricos foram conferidos
manualmente pela fórmula matemática correspondente.

| # | Cenário testado | Entrada / ação | Resultado obtido | Resultado esperado (cálculo manual) | Status |
|---|---|---|---|---|---|
| 1 | Criar vetor | Vetor 0 = `[0.80, 0.20, 0.50, 0.90, 0.30]`, tamanho 5 | Vetor armazenado corretamente | — | ✅ |
| 2 | Exibir vetores armazenados | Opção 2 com 3 vetores cadastrados | Lista os 3 vetores na ordem de criação | — | ✅ |
| 3 | Norma de um vetor | Norma do vetor 0 | `1.3528` | `sqrt(0.8²+0.2²+0.5²+0.9²+0.3²) = sqrt(1.83) = 1.3528` | ✅ |
| 4 | Produto escalar | Vetor 0 · Vetor 1 | `0.8500` | `0.8·0.1 + 0.2·0.9 + 0.5·0.4 + 0.9·0.2 + 0.3·0.7 = 0.85` | ✅ |
| 5 | Similaridade de cosseno | Vetor 0 vs Vetor 1 | `0.5113` | `0.85 / (1.3528 × 1.2288) = 0.5113` | ✅ |
| 6 | Multiplicação por escalar | Vetor 1 × 2.0 | `[0.20, 1.80, 0.80, 0.40, 1.40]` | Cada elemento × 2 | ✅ |
| 7 | Soma de vetores | Vetor 0 + Vetor 1 | `[0.90, 1.10, 0.90, 1.10, 1.00]` | Soma elemento a elemento | ✅ |
| 8 | Vetor mais similar | Consulta = Vetor 0, contra vetores 1 a 4 | Vetor 2 apontado como mais similar (`0.9967`) | Vetor 2 é quase idêntico ao vetor 0 → maior similaridade esperada | ✅ |
| 9 | Opção de menu inválida | Digitar `99` | `"Opcao invalida."`, sem travar o programa | Mensagem de erro e retorno ao menu | ✅ |
| 10 | Soma com tamanhos diferentes | Vetores de tamanhos distintos (5 e 4) | `"Erro: os vetores precisam ter o mesmo tamanho..."` | Rejeição da operação, sem crash | ✅ |
| 11 | `buscar` (teste unitário isolado) | Buscar `0.50` no vetor `[0.80, 0.20, 0.50, 0.90, 0.30]` | índice `2` | Elemento está na posição 2 | ✅ |
| 12 | `buscar` valor ausente (teste unitário isolado) | Buscar `9.99` no mesmo vetor | `-1` | Elemento não existe no vetor | ✅ |
| 13 | `remover` (teste unitário isolado) | Remover índice 2 do vetor acima | `[0.80, 0.20, 0.90, 0.30]` | Elemento na posição 2 removido, restante deslocado | ✅ |

### Como os testes foram executados

- **Testes 1–10:** automatizados via redirecionamento de entrada
  padrão (`./biblioteca_mat < entrada_teste.txt`), simulando exatamente a
  sequência de opções e valores que um usuário digitaria no menu.
- **Testes 11–13:** como `buscar` e `remover` não têm entrada no
  menu (ver observação acima), foram testados isoladamente em um
  `main()` de verificação separado, chamando as funções diretamente
  e comparando o resultado com o valor esperado.

### Compilação sem warnings

O programa foi compilado com `-Wall -Wextra` em todas as versões
testadas, sem nenhum warning gerado.
