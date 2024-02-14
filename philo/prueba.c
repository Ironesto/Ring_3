#include <stdio.h>
#include <pthread.h>
/* Para trabajar con hilos, al compilar usar: -pthread */

//                                                THREAD
// >>> para crear un hilo:
// int pthread_create(	pthread_t *thread,            		>>> puntero al hilo
// 						const pthread_attr_t *attr,       	>>> atributos del hilo, NULL por defecto 
// 						void *(*start_routine) (void *),  	>>> función que ejecutara el hilo
// 						void *arg);                       	>>> argumento adicional, NULL si no pasamos nada
// >>> esperar que termine el hilo:
// int pthread_join(	pthread_t thread, 					>>> el hilo
// 						void **retval);						>>> copia el 'exit status' del hilo, NULL por defecto


//                                                MUTEX
// >>> iniciar un mutex:
// int pthread_mutex_init(pthread_mutex_t *mutex,           >>> puntero al mutex
//                        const pthread_mutexattr_t *attr); >>> atributos del mutex, NULL por defecto
// >>> destruir un mutex:
// int pthread_mutex_destroy(pthread_mutex_t *mutex);       >>> puntero al mutex
// >>> para cerrar un mutex:
// int pthread_mutex_lock(pthread_mutex_t *mutex);          >>> puntero al mutex
// >>> para abrir un mutex:
// int pthread_mutex_unlock(pthread_mutex_t *mutex);        >>> puntero al mutex

typedef struct s_mutex_counter
{
    int             count;
    pthread_mutex_t	mutex_count;
}   t_mutex_counter;

void	*routine(void *data)
{
	t_mutex_counter *counter;
    int             i;

    i = 0;
	counter = (t_mutex_counter *)data;
	while (i < 10000)
	{
        // el primero que llega a este punto cierra el mutex y no puede acceder los otros hilos
        pthread_mutex_lock(&counter->mutex_count); 
		counter->count++;
        // desbloquea el mutex para que pueda accder otro hilo
        pthread_mutex_unlock(&counter->mutex_count);
        i++;
	}
	return (NULL); 
}

int main(void)
{
    t_mutex_counter counter; // struct creada para el ejerccio, tiene un entero que sera el contador y un mutex para acceder 
	pthread_t	    thread1;
	pthread_t	    thread2;

	counter.count = 0;
    pthread_mutex_init(&counter.mutex_count, NULL); // para inicializar el mutex
	pthread_create(&thread1, NULL, routine, &counter);
	pthread_create(&thread2, NULL, routine, &counter);
	printf("antes del join: %d\n", counter.count);
	pthread_join(thread1, NULL); 
	pthread_join(thread2, NULL); 
    pthread_mutex_destroy(&counter.mutex_count); // destruir el mutex
	printf("final: %d\n", counter.count); 
	return (0); 
}