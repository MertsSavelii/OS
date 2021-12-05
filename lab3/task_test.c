#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define SUCCESS               0

unsigned current_number, number;
pthread_t* threads;

typedef struct
{
    unsigned left, right;
    int *array;
} thread_data;

void* native_quick_sort(void* arguments)
{
	//sleep(1);
	thread_data* data = (thread_data*) arguments;
  	int pivot; // разрешающий элемент
  	unsigned left = data->left; 
  	unsigned right = data->right; 
  	pivot = data->array[left];
  	while (left < right)
	{
    	while ((data->array[right] >= pivot) && (left < right))
			right--;
    	if (left != right)
    	{
      		data->array[left] = data->array[right];
      		left++;
    	}
    	while ((data->array[left] <= pivot) && (left < right)) 
			left++;
    	if (left != right)
    	{
      		data->array[right] = data->array[left];
      		right--;
    	}
	}
  	data->array[left] = pivot; // ставим разрешающий элемент на место
  	pivot = left;
  	left = data->left;
  	right = data->right;

	thread_data a = {left, pivot - 1, data->array}, b = {pivot + 1, right, data->array};
	if ((left < pivot) && (right > pivot))
    {
        if (current_number)
        {
			current_number--;
			int id_thread = number - current_number - 1;
			if ((pivot - left) >= (right - pivot))
			{
				int status = pthread_create(&threads[id_thread], NULL, native_quick_sort, &a);
				if (status != SUCCESS)
				{
					printf("Ошибка при создании процесса\n");
                    printf("Код ошибки %d\n", status);
                    exit(ERROR_CREATE_THREAD);
				}
				native_quick_sort(&b);
			}
			else
			{
				int status = pthread_create(&threads[id_thread], NULL, native_quick_sort, &b);
				if (status != SUCCESS)
				{
					printf("Ошибка при создании процесса\n");
                    printf("Код ошибки %d\n", status);
                    exit(ERROR_CREATE_THREAD);
				}
				native_quick_sort(&a);
			}
			int status_arrt = pthread_join(threads[id_thread], NULL);
			if (status_arrt != SUCCESS)
			{
				printf("Ошибка при присоединении процесса\n");
                printf("Код ошибки %d\n", status_arrt);
                exit(ERROR_JOIN_THREAD);
			}
        }
        else
        {
            native_quick_sort(&a);
            native_quick_sort(&b);
        }
    }
    else
    {
        if (left < pivot)
    		native_quick_sort(&a);
  		if (right > pivot)
    		native_quick_sort(&b);
    }
	return SUCCESS;
}

int main(int argc, char* argv[])
{
  	if ((argc != 3) || (atoi(argv[1]) < 0) || (atoi(argv[2]) < 1))
    {
        printf("Аргументы вызова программы: (не отрицательное) число потоков (позитивное) размер массива\n");
        exit(1);
    }
    number = strtol(argv[1], NULL, 10);
    unsigned size = strtol(argv[2], NULL, 10);
    if (number > size)
    {
        printf("Количество потоков больше размера массива. Количество потоков приравнено к размеру массива\n");
        number = size;
    }

	pid_t pid = getpid();
    printf("PID: %d\n", pid);

    current_number = number;
    int *array = (int*) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        array[i] = rand();

	struct timespec mt1, mt2;

    threads = (pthread_t*)malloc(number * sizeof(pthread_t));
    thread_data a = {0, size - 1, array};
	clock_gettime (CLOCK_REALTIME, &mt1);
    native_quick_sort(&a);
	clock_gettime (CLOCK_REALTIME, &mt2);

    printf("Массив отсортирован:\n");

	long int tt=1000000000*(mt2.tv_sec - mt1.tv_sec)+(mt2.tv_nsec - mt1.tv_nsec);
	printf ("Затрачено время: %ld нс\n",tt);

    free(array);
    free(threads);
    return 0;
}