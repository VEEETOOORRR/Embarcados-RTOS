# Atividade 5 — Compartilhamento da UART

## 1. Objetivo

Comparar o compartilhamento da UART sem proteção e com proteção por mutex.

## 2. Implementação e experimentos

### Sem uso de mutex

```c
void TaskSensor_fun(void *argument)
{
 /* USER CODE BEGIN 5 */
 /* Infinite loop */
 for(;;)
 {
   for(int i = 0; i < 50; i++){
   	printf("TASKSENSOR\r\n");
   }
 }
 /* USER CODE END 5 */
}
```

```c
void TaskControle_fun(void *argument)
{
 /* USER CODE BEGIN TaskControle_fun */
 /* Infinite loop */
 for(;;)
 {
	for(int i = 0; i < 50; i++){
		printf("TASKCONTROLE\r\n");
	}
 }
 /* USER CODE END TaskControle_fun */
}
```

**Saída registrada:**

```text
TASKSENSOR
TASKCONTROLE
TASKSETAOR
NTROLE
TASKCONTROLE
TASKSENSOR
TASKCONTROLE
TASKSETASKCONTROLE
TASKCENSOR
TASKSENSOR
TASKSENSOR
TASKCONTROLE
```

Sem o uso do mutex, o terminal apresenta mensagens fragmentadas e sobrepostas.

### Com uso de mutex

```text
TASKCONTROLE
TASKCONTROLE
TASKCONTROLE
TASKCONTROLE
TASKCONTROLE
TASKCONTROLE
TASKCONTROLE
TASKCONTROLE
TASKCONTROLE
TASKCONTROLE
…
TASKCONTROLE
TASKSENSOR
TASKSENSOR
TASKSENSOR
TASKSENSOR
TASKSENSOR
TASKSENSOR
TASKSENSOR
TASKSENSOR
TASKSENSOR
TASKSENSOR
TASKSENSOR
TASKSENSOR
TASKSENSOR
TASKSENSOR
TASKSENSOR
TASKSENSOR
TASKSENSOR
…
TASKSENSOR
```

Fazendo uso do mutex, a cada task imprime sua mensagem via UART 50 vezes sem "atropelo".

## 3. Análise dos resultados

**Questão:** Por que um mutex é conceitualmente mais adequado para proteger a UART do que um semáforo?

Fazendo uso de um mutex, a tarefa que o adquire é responsável por liberá-lo. Na UART, a proteção deve abranger toda a região de transmissão que precisa permanecer íntegra, e todos os acessos concorrentes devem respeitar o mesmo mecanismo.