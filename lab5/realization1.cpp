extern "C" int PrimeCount(int A, int B);
extern "C" int GCF(int A, int B);

int PrimeCount(int A, int B) {
    int count = 0;
    for (int i = A; i <= B; i++){
        int j;
        for(j = 2; j <= i; j++)
            if(i % j == 0) break;
        if(j == i) count++;
    }
    return count;
}

int GCF(int A, int B) {
    while (A!=0 && B!=0)
        if (A > B)
            A = A % B;
        else
            B = B % A;
    return A+B;
}
