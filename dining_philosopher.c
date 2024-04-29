#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void* philosopher(void* num);
void take_forks(int pnum);
void put_forks(int pnum);
void think(int pnum);
void eat(int pnum);

int main() {
    pthread_t phils[NUM_PHILOSOPHERS];
    int philosopher_numbers[NUM_PHILOSOPHERS];

    // Initialize mutexes for each fork
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create a thread for each philosopher
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_numbers[i] = i;
        pthread_create(&phils[i], NULL, philosopher, &philosopher_numbers[i]);
    }

    // Join all threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(phils[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

void* philosopher(void* num) {
    int pnum = *(int*)num;

    while (1) {
        think(pnum);
        take_forks(pnum);
        eat(pnum);
        put_forks(pnum);
    }
}

void take_forks(int pnum) {
    int left_fork = pnum;
    int right_fork = (pnum + 1) % NUM_PHILOSOPHERS;

    if (pnum == NUM_PHILOSOPHERS - 1) { // Last philosopher picks right fork first
        pthread_mutex_lock(&forks[right_fork]);
        printf("Philosopher %d took right fork %d\n", pnum, right_fork);
        pthread_mutex_lock(&forks[left_fork]);
        printf("Philosopher %d took left fork %d\n", pnum, left_fork);
    } else { // All other philosophers pick left fork first
        pthread_mutex_lock(&forks[left_fork]);
        printf("Philosopher %d took left fork %d\n", pnum, left_fork);
        pthread_mutex_lock(&forks[right_fork]);
        printf("Philosopher %d took right fork %d\n", pnum, right_fork);
    }
}

void put_forks(int pnum) {
    int left_fork = pnum;
    int right_fork = (pnum + 1) % NUM_PHILOSOPHERS;

    pthread_mutex_unlock(&forks[left_fork]);
    pthread_mutex_unlock(&forks[right_fork]);

    printf("Philosopher %d put down forks %d and %d\n", pnum, left_fork, right_fork);
}

void think(int pnum) {
    printf("Philosopher %d is thinking\n", pnum);
    sleep(1);
}

void eat(int pnum) {
    printf("Philosopher %d is eating\n", pnum);
    sleep(2);
}
