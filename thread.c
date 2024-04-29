#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void *printPerfectSquares(void *arg) {
    int start = *(int*)arg;
    int end = start == 1 ? 10000 : 20000;

    for (int i = start; i <= end; i++) {
        int root = sqrt(i);
        if (root * root == i) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return NULL;
}

int main() {
    pthread_t threads[2];
    int start1 = 1, start2 = 10001;

    pthread_create(&threads[0], NULL, printPerfectSquares, &start1);
    pthread_create(&threads[1], NULL, printPerfectSquares, &start2);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}


#include <stdio.h>
#include <pthread.h>

typedef struct {
    int cat1;
    int cat2;
} Marks;

void *printCat1(void *arg) {
    Marks *marks = (Marks *)arg;
    printf("CAT 1 Marks: %d\n", marks->cat1);
    return NULL;
}

void *printCat2(void *arg) {
    Marks *marks = (Marks *)arg;
    printf("CAT 2 Marks: %d\n", marks->cat2);
    return NULL;
}

int main() {
    pthread_t threads[2];
    Marks marks = {85, 90}; // Example marks

    pthread_create(&threads[0], NULL, printCat1, &marks);
    pthread_create(&threads[1], NULL, printCat2, &marks);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}

#include <stdio.h>
#include <pthread.h>

long long factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

void *fibonacci(void *arg) {
    int n = *(int *)arg;
    long long a = 0, b = 1, c;
    if (n == 0)
        printf("%lld ", a);
    else {
        printf("%lld %lld ", a, b);
        for (int i = 2; i <= n; i++) {
            c = a + b;
            a = b;
            b = c;
            printf("%lld ", c);
        }
    }
    printf("\n");
    return NULL;
}

void *factorialThread(void *arg) {
    int n = *(int *)arg;
    printf("Factorial: %lld\n", factorial(n));
    return NULL;
}

void *evenOrOdd(void *arg) {
    int n = *(int *)arg;
    if (n % 2 == 0)
        printf("%d is Even\n", n);
    else
        printf("%d is Odd\n", n);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int number = 10; // Example number

    pthread_create(&threads[0], NULL, fibonacci, &number);
    pthread_create(&threads[1], NULL, factorialThread, &number);
    pthread_create(&threads[2], NULL, evenOrOdd, &number);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);

    return 0;
}
