#include <libmath.h>

#include <iostream>

using namespace std;


int main() {
    int num;
    cout << "Informe um numero: " << std::flush;
    cin >> num;

    int fat = libmath::fatorial( num );

    cout << endl;
    cout << "O fatorial de " << num << " eh: " << fat << endl;

    return 0;
}