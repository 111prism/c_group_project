#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval start, end;

    gettimeofday(&start, NULL);  // Get the start time

    // Code block to measure
    for (volatile int i = 0; i < 100000000; i++); // Example workload

    gettimeofday(&end, NULL);    // Get the end time
    double elapsed = (end.tv_sec - start.tv_sec) + 
                     (end.tv_usec - start.tv_usec) / 1000000.0;  // Calculate elapsed time in seconds

    printf("Elapsed time: %.6f seconds\n", elapsed);
    return 0;
}
