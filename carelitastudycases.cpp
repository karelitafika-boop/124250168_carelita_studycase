#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "masukkan panjang array: ";
    cin >> n;

    int *ptr = (int*) malloc(n * sizeof(int));
		cout << "yuk masukkin elemen array:\n";
			for(int i = 0; i < n; i++) {
				cout << "elemen ke-" << i+1 << " : ";
				cin >> *(ptr + i); 
			}
			
				cout << "isi array:\n";
			for(int i = 0; i < n; i++) {
				cout << *(ptr + i) << " ";
			}

    int max = *ptr;
    int min = *ptr;

			for(int i = 1; i < n; i++) {
				if(*(ptr + i) > max)
					max = *(ptr + i);

				if(*(ptr + i) < min)
					min = *(ptr + i);
			}

    int jumlah = 0;
			for(int i = 0; i < n; i++) {
				jumlah += *(ptr + i);
			}

			float rata = (float)jumlah / n;
			
				cout << "\n\nnilai maksimum : " << max << endl;
				cout << "nilai minimum  : " << min << endl;
				cout << "jumlah         : " << jumlah << endl;
				cout << "rata-rata      : " << rata << endl;

    return 0;
}
