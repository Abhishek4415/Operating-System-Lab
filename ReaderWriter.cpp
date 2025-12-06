#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;        // Protects readcount
sem_t writeblock;   // Controls access for writers
int readcount = 0;  // Number of active readers

void* reader(void* arg) {
    int id = *(int*)arg;

    sem_wait(&mutex);          // Enter critical section
    readcount++;

    if (readcount == 1) {
        // First reader blocks writers
        sem_wait(&writeblock);
    }

    sem_post(&mutex);          // Exit critical section

    // Reading Section
    printf("Reader %d is reading...\n", id);
    sleep(1);

    sem_wait(&mutex);          // Enter critical section
    readcount--;

    if (readcount == 0) {
        // Last reader allows writers
        sem_post(&writeblock);
    }

    sem_post(&mutex);          // Exit critical section

    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;

    sem_wait(&writeblock);     // Writer gets exclusive access

    // Writing Section
    printf("Writer %d is writing...\n", id);
    sleep(2);

    sem_post(&writeblock);     // Writer releases access

    return NULL;
}

int main() {
    pthread_t r[5], w[5];
    int id[5];

    sem_init(&mutex, 0, 1);
    sem_init(&writeblock, 0, 1);

    // Creating reader and writer threads
    for (int i = 0; i < 5; i++) {
        id[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &id[i]);
        pthread_create(&w[i], NULL, writer, &id[i]);
    }

    // Wait for all threads
    for (int i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
        pthread_join(w[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&writeblock);

    return 0;
}
