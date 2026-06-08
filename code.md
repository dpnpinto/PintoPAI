# Retropropagação, Derivadas e o Gradiente em Redes Neuronais

O conceito de **retropropagação** (*backpropagation*), associado às **derivadas** e ao **gradiente**, é o coração do treino de redes neuronais. Em termos simples, é o mecanismo matemático que permite à rede "aprender com os erros".

Para entender como tudo se liga, podemos desconstruir o processo do fim para o início.

---

## 1. O Objetivo: Minimizar a Função de Custo ($L$)

Uma rede neuronal recebe uma entrada, processa-a através de várias camadas de neurónios (multiplicações por pesos $w$ e adições de bias $b$) e gera uma saída. 

A diferença entre a saída calculada pela rede e a saída real desejada é medida por uma **Função de Custo** ou de perda ($L$, de *Loss*). O objetivo supremo do treino é fazer com que $L$ seja o mais próximo de zero possível. Para isso, precisamos de ajustar os pesos ($w$). Mas como saber se devemos aumentar ou diminuir um peso? É aqui que entram as derivadas.

---

## 2. A Derivada: A Direção do Ajuste

A **derivada** mede a taxa de variação de uma função em relação a uma variável. No contexto de redes neuronais, a derivada parcial da função de custo em relação a um peso específico é representada por:

$$rac{\partial L}{\partial w}$$

Esta derivada diz-nos exatamente **como o erro ($L$) muda se alterarmos ligeiramente o peso ($w$)**:
* Se a derivada for **positiva**, significa que aumentar o peso vai aumentar o erro. Logo, devemos diminuir o peso.
* Se a derivada for **negativa**, significa que aumentar o peso vai diminuir o erro. Logo, devemos aumentar o peso.

---

## 3. O Gradiente: O Vetor de Direção Geral

Uma rede neuronal real não tem apenas um peso; tem milhares ou milhões deles. O **gradiente** (representado pelo símbolo $
abla$) é simplesmente um **vetor (uma lista) de todas as derivadas parciais** da função de custo em relação a cada um dos pesos e bias da rede:

$$
abla L =  begin{bmatrix} rac{\partial L}{\partial w_1} \ rac{\partial L}{\partial w_2} \  dots \ rac{\partial L}{\partial w_n} \end{bmatrix}$$

O gradiente aponta matematicamente para a direção de *maior crescimento* da função de custo. Como o objetivo é minimizar o erro, caminha-se na direção contrária ao gradiente. Este algoritmo chama-se **Gradiente Descendente** (*Gradient Descent*).

---

## 4. A Retropropagação (*Backpropagation*): A Regra da Cadeia em Ação

O desafio é que uma rede neuronal possui muitas camadas sobrepostas. Um peso na primeira camada afeta a saída da primeira camada, que afeta a entrada da segunda, e assim sucessivamente, até impactar o erro final. Para calcular a derivada de um peso localizado nas camadas iniciais da rede, utiliza-se a **Regra da Cadeia** do cálculo diferencial.

A retropropagação é a aplicação sistemática da regra da cadeia, calculando as derivadas de trás para a frente (da saída em direção à entrada).

### Exemplo Prático de Fluxo

Considere um neurónio simples onde a soma ponderada é dada por $z = w \cdot x$, a aplicação da função de ativação gera $a = \sigma(z)$, e o erro final calculado é $L$.

Para descobrir o impacto do peso $w$ no erro final $L$, a retropropagação faz o caminho inverso:

1. Calcula quanto o erro muda em relação à ativação: $rac{\partial L}{\partial a}$
2. Calcula quanto a ativação muda em relação à soma ponderada: $rac{\partial a}{\partial z}$
3. Calcula quanto a soma ponderada muda em relação ao peso: $rac{\partial z}{\partial w}$ (que equivale ao próprio valor de entrada $x$)

Multiplicando estas taxas de variação intermédias através da Regra da Cadeia, obtém-se a derivada final:

$$rac{\partial L}{\partial w} = rac{\partial L}{\partial a} \cdot rac{\partial a}{\partial z} \cdot rac{\partial z}{\partial w}$$

Este valor (que integra o **gradiente** da rede) é posteriormente multiplicado por uma taxa de aprendizagem ($ lpha$, ou *learning rate*) para atualizar o peso:

$$w_{	ext{novo}} = w_{	ext{antigo}} -  lpha \cdot rac{\partial L}{\partial w}$$

---

## Resumo Visual do Ciclo

1. **Propagação para a frente (Forward Pass):** Os dados de entrada cruzam a rede, os pesos são aplicados e a perda ($L$) é medida na saída.
2. **Retropropagação (Backward Pass):** O erro é transmitido em sentido inverso. A **regra da cadeia** calcula as **derivadas** correspondentes a cada camada.
3. **Atualização (Weight Update):** O **gradiente** total é utilizado para ajustar todos os pesos em simultâneo através do gradiente descendente, repetindo-se o ciclo até à convergência do modelo.
