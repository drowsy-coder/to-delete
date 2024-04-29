#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t reader_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t writer_cond = PTHREAD_COND_INITIALIZER;
int read_count = 0;
int write_count = 0;
int active_writer = 0;

void *reader(void *arg) {
    int reader_id = *(int *)arg;

    pthread_mutex_lock(&lock);
    while (active_writer > 0) { // Wait if there is an active writer
        pthread_cond_wait(&reader_cond, &lock);
    }
    read_count++;
    pthread_mutex_unlock(&lock);

    // Reading section
    printf("Reader %d is reading\n", reader_id);
    sleep(1);

    pthread_mutex_lock(&lock);
    read_count--;
    if (read_count == 0 && write_count > 0) { // Signal writers if no more readers
        pthread_cond_signal(&writer_cond);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;

    pthread_mutex_lock(&lock);
    write_count++;
    while (read_count > 0 || active_writer > 0) { // Wait if there are active readers or another writer
        pthread_cond_wait(&writer_cond, &lock);
    }
    active_writer++;

    pthread_mutex_unlock(&lock);

    // Writing section
    printf("Writer %d is writing\n", writer_id);
    sleep(1);

    pthread_mutex_lock(&lock);
    active_writer--;
    write_count--;
    if (write_count > 0) { // If there are waiting writers, let another writer go
        pthread_cond_signal(&writer_cond);
    } else { // Otherwise, allow readers
        pthread_cond_broadcast(&reader_cond);
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t readers[3], writers[2];
    int reader_ids[3] = {1, 2, 3};
    int writer_ids[2] = {1, 2};

    for (int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&reader_cond);
    pthread_cond_destroy(&writer_cond);

    return 0;
}
