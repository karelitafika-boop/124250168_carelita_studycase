#include <iostream>
using namespace std;

void bubblesort(string data[], int n)
{
    int i, j;
    string temp;

    for(i = 0; i < n-1; i++)
    {
        for(j = 0; j < n-1-i; j++)
        {
            if(data[j] > data[j+1])
            {
                temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }
}

void quicksort (string data[], int kiri, int kanan)
{
    int low = kiri;
    int high = kanan;
    string temp;
    string pivot = data[(kiri + kanan) / 2];

    while(low <= high)
    {
        while(data[low] > pivot)
            low++;

        while(data[high] < pivot)
            high--;

        if(low <= high)
        {
            temp = data[low];
            data[low] = data[high];
            data[high] = temp;
            low++;
            high--;
        }
    }

    if(kiri < high)
        quicksort(data, kiri, high);
    if(low < kanan)
        quicksort(data, low, kanan);
}

int main()
{
    int n, i;

    cout << "mau berapa mahasiswa nih? : ";
    cin >> n;
    cin.ignore();

    string nama[n];

    for(i = 0; i < n; i++)
    {
        cout << "nama ke-" << i+1 << " : ";
        getline(cin, nama[i]);
    }

    bubblesort(nama, n);

    cout << "\nini yaa hasil bubble sort asc!:\n";
    for(i = 0; i < n; i++)
        cout << nama[i] << endl;

    quicksort(nama, 0, n-1);

    cout << "\nkaloo ini quick sort desc yahh! :\n";
    for(i = 0; i < n; i++)
        cout << nama[i] << endl;

    return 0;
}
