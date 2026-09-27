# Atividade 6 — O contador que apresenta o valor errado

## 1. Objetivo

Investigar o resultado de incrementos concorrentes em uma variável compartilhada e a proteção com mutex.

## 4. Implementação e experimentos

### Sem usar mutex

```c
void Task01_fun(void *argument)
{
 /* USER CODE BEGIN 5 */
 for(int i = 0; i < 100000; i++){
	contadorGlobal++;
 }
 /* Infinite loop */
 for(;;)
 {
   osDelay(1);
 }
 /* USER CODE END 5 */
}
```

```c
void Task02_fun(void *argument)
{
 /* USER CODE BEGIN Task02_fun */
	for(int i = 0; i < 100000; i++){
		contadorGlobal++;
	}
 /* Infinite loop */
 for(;;)
 {
   osDelay(1);
 }
 /* USER CODE END Task02_fun */
}
```

```c
void TaskUART_fun(void *argument)
{
 /* USER CODE BEGIN TaskUART_fun */
	osDelay(1000);
	printf("%lu\r\n", contadorGlobal);
 /* Infinite loop */
 for(;;)
 {
   osDelay(1);
 }
 /* USER CODE END TaskUART_fun */
}
```

**Saída registrada:**

```text
163725
```

### Proteção com mutex

```c
void Task01_fun(void *argument)
{
 /* USER CODE BEGIN 5 */
 for(int i = 0; i < 100000; i++){
	osMutexAcquire(contadorMutexHandle, osWaitForever);
	contadorGlobal++;
	osMutexRelease(contadorMutexHandle);
 }
 /* Infinite loop */
 for(;;)
 {
   osDelay(1);
 }
 /* USER CODE END 5 */
}
```

```c
void Task02_fun(void *argument)
{
 /* USER CODE BEGIN Task02_fun */
	for(int i = 0; i < 100000; i++){
		osMutexAcquire(contadorMutexHandle, osWaitForever);
		contadorGlobal++;
		osMutexRelease(contadorMutexHandle);
	}
 /* Infinite loop */
 for(;;)
 {
   osDelay(1);
 }
 /* USER CODE END Task02_fun */
}
```

**Saída registrada:**

```text
200000
```

[Registro completo disponível no rascunho](logs/atividade-06-registro-02.txt).

## 5. Análise dos resultados

**Questão:** Explique por que contadorGlobal++ não deve ser considerado necessariamente atômico. Utilize a sequência LER → MODIFICAR → ESCREVER.

O incremento pode envolver três etapas: **ler** o valor da memória para um registrador, **modificar** esse valor e **escrever** o resultado na memória. Se outra tarefa acessar a variável entre essas etapas, um incremento pode sobrescrever o resultado de outro.