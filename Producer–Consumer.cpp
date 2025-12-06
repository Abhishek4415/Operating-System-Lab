#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty;             // Counts empty slots
sem_t full;              // Counts filled slots
pthread_mutex_t mutex;   // Ensures mutual exclusion

void* producer(void* arg) {
    int item = 1;

    while (1) {
        sem_wait(&empty);           // Wait if buffer is full
        pthread_mutex_lock(&mutex); // Enter critical section

        printf("Producer produced item %d\n", item);
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        item++;

        pthread_mutex_unlock(&mutex); 
        sem_post(&full);            // Signal that buffer has one more item

        sleep(1);                   // Slow down production
    }
}

void* consumer(void* arg) {
    while (1) {
        sem_wait(&full);            // Wait if buffer is empty
        pthread_mutex_lock(&mutex); // Enter critical section

        int item = buffer[out];
        printf("Consumer consumed item %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);           // Signal that buffer has empty space

        sleep(2);                   // Slow down consumption
    }
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores & mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer & consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Cleanup (won't actually reach here due to infinite loops)
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
