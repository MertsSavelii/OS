extern "C" int PrimeCount(int A, int B);
extern "C" int GCF(int A, int B);

int PrimeCount(int A, int B) {
    int count = 0;
    int n = B + 1;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
        arr[i] = i;
    for (int i = 2; i < n; i++)
        if (arr[i] != 0 ) {
            if (arr[i] >= A && arr[i] <= B) count++;
            for (int j = i*i; j < n; j += i)
                arr[j] = 0;
        }
    return count;
}

int GCF(int A, int B) {
    A = A < B ? A : B;
    B = A > B ? A : B;
    int c = A;
    while (c) {
        if(A % c == 0 && B % c == 0)
            break;
        c--;
    }
    return c;
}
