#include <iostream>
extern "C" int PrimeCount (int A, int B);
extern "C" int GCF (int A, int B);

int main () {
    int command;
    while (printf("Please enter your command: ") && (scanf("%d", &command)) != EOF) {
        switch (command) {
            case 1: {
                int A, B;
                std::cout << "enter A and B\n";
                std::cin >> A >> B;
                int prime_count = PrimeCount (A, B);
                printf("PrimeCount = %d\n", prime_count);
                break;
            }
            case 2: {
                int A, B;
                std::cout << "enter A and B\n";
                std::cin >> A >> B;
                int gcf = GCF (A, B);
                printf("GCF = %d\n", gcf);
                break;
            }
            default:
                std:: cout << "You must enter 1 or 2!\n" << std:: endl;
                break;
        }
    }
    return 0;
}