#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>

unsigned current_number, number;
pthread_t* threads;

typedef struct
{
    unsigned left, right;
    int *array;
} thread_data;

void* quicksort (void* arguments)
{
    //sleep(3);
    thread_data* data = (thread_data*) arguments;
    unsigned left = data->left, right = data->right;
    int x = data->array[(left + right) / 2];
    while (left <= right)
    {
        while (data->array[left] < x)
            left++;
        while (data->array[right] > x)
            right--;
        if (left <= right)
        {
            if (data->array[left] > data->array[right])
            {
                data->array[left] += data->array[right];
                data->array[right] = data->array[left] - data->array[right];
                data->array[left] -= data->array[right];
            }
            if (left == INT_MAX)
                break;
            left++;
            if (!right)
                break;
            right--;
        }
    }
    if ((left < data->right) && (data->left < right))
    {
        thread_data a = {left, data->right, data->array}, b = {data->left, right, data->array};
        if (current_number)
        {
	    	int index;
            current_number--;
        	int local_number = current_number;
        	if ((data->right - left) >= (right - data->left))
            {
                if (index = (pthread_create(&threads[number - current_number - 1], NULL, quicksort, &b)) != 0)
                {
                    printf("Ошибка при создании процесса\n");
                    printf("Код ошибки %d\n", index);
                    exit(1);
                }
                quicksort(&a);
            }
            else
            {
                if (index = (pthread_create(&threads[number - current_number - 1], NULL, quicksort, &a)) != 0)
                {
                    printf("Ошибка при создании процесса\n");
                    printf("Код ошибки %d\n", index);
                    exit(1);
                }
                quicksort(&b);
            }
            if ((index = pthread_join(threads[number - local_number - 1], NULL)) != 0)
            {
                printf("Ошибка при создании процесса\n");
                printf("Код ошибки %d\n", index);
                exit(1);
            }
        }
        else
        {
            quicksort(&a);
            quicksort(&b);
        }
    }
    else
    {
        if (left < data->right)
        {
            thread_data a = {left, data->right, data->array};
            quicksort(&a);
        }
        else if (data->left < right)
        {
            thread_data a = {data->left, right, data->array};
            quicksort(&a);
        }
    }
    return NULL;
}

int main(int argc, char* argv[])
{
  if ((argc != 3) || (atoi(argv[1]) < 0) || (atoi(argv[2]) < 1))
    {
        printf("Аргументы вызова программы: (не отрицательное) числопотоков (позитивное) размер массива\n");
        exit(1);
    }
    number = strtol(argv[1], NULL, 10);
    unsigned size = strtol(argv[2], NULL, 10);
    if (number > size)
    {
        printf("Количество потоков больше размера массива. Количество потоков приравнено к размеру массива\n");
        number = size;
    }
    current_number = number;
    pid_t pid = getpid();
    printf("PID: %d\n", pid);
    printf("Введите элементы массива размером %d \n", size);
    int *array = (int*) malloc(size * sizeof(int));
    int sorted = 1;
    for (int i = 0; i < size; i++)
    {
        array[i] = rand();
        if ((i) && (sorted) && (array[i] < array[i - 1]))
        {
            sorted = 0;
        }
    }
    if (sorted)
    {
      printf("Массив отсортирован\n");
        // for (int i = 0; i < size; i++)
        // {
        //     printf("%i ", array[i]);
        // }
        printf("\n");
	    free(array);
        return 0;
    }
    /*int index;
    if (index = (pthread_mutex_init(&mutex, NULL)) != 0)
    {
        printf("There is some problems with initializing mutex\n");
	    printf("%i\n", index);
	    free(array);
	    exit(1);
    }*/
    threads = (pthread_t*)malloc(number * sizeof(pthread_t));
    thread_data a = {0, size - 1, array};
    struct timespec mt1, mt2;
    clock_gettime (CLOCK_REALTIME, &mt1);
    quicksort(&a);
    clock_gettime (CLOCK_REALTIME, &mt2);

    printf("Массив отсортирован:\n");
    // for (int i = 0; i < size; i++)
    // {
    //     printf("%i ", array[i]);
    // }
    printf("\n");
    long int tt=1000000000*(mt2.tv_sec - mt1.tv_sec)+(mt2.tv_nsec - mt1.tv_nsec);
	printf ("Затрачено время: %ld нс\n",tt);
    free(array);
    free(threads);
    /*if (index = (pthread_mutex_destroy(&mutex)) != 0)
    {       
        printf("There is some problems with destroying mutex\n");
        printf("%i\n", index);
        exit(1);
    }*/
    return 0;
}