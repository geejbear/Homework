int fibo(int n) // 
{
    clamp(n, 30, 1);

    int *fib = malloc( n * sizeof(int) );
    fib[0] = 1;
    fib[1] = 1;

    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
        cprintf("%d\n", fib[i]);
    }

    free(fib);

    return 0;
}