#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

struct Produk{
    char name[60];
    char category[30];
    double price;
    int stock;
    float rating;
};

Produk arr[100];
int n = 0;

void loadFile(){

    FILE *pointer = fopen("shopease_db.txt","r");

    if(pointer == NULL){
        return;
    }

    while(fscanf(pointer," %[^|]|%[^|]|%lf|%d|%f\n",
    arr[n].name,
    arr[n].category,
    &arr[n].price,
    &arr[n].stock,
    &arr[n].rating)!=EOF){

        n++;
    }

    fclose(pointer);
}

void saveFile(){

    FILE *pointer = fopen("shopease_db.txt","w");

    for(int i=0;i<n;i++){

        fprintf(pointer,"%s|%s|%.0lf|%d|%.1f\n",
        arr[i].name,
        arr[i].category,
        arr[i].price,
        arr[i].stock,
        arr[i].rating);

    }

    fclose(pointer);
}

void tambahProduk(){

    char lagi;

    do{

        cin.ignore();

        cout<<"\n=== TAMBAH PRODUK ===\n";

        cout<<"nama produk?: ";
        cin.getline(arr[n].name,60);

        cout<<"um kategorinya? : ";
        cin.getline(arr[n].category,30);

        cout<<"harganya brp nih? : ";
        cin>>arr[n].price;

        cout<<"stok : ";
        cin>>arr[n].stock;

        cout<<"ratingnya brp nih? : ";
        cin>>arr[n].rating;

        n++;

        saveFile();

        cout<<"\nyeyyyy produk berhasil ditambahinn!\n";

        cout<<"\nmau tambah lagi gakkkkk? (y/t) : ";
        cin>>lagi;

    }while(lagi=='y' || lagi=='Y');

}

void bubbleSort(){

    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){

            if(strcmp(arr[j].name,arr[j+1].name) > 0){

                Produk temp;

                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;

            }

        }
    }
}

void quickSort(int low,int high){

    int i = low;
    int j = high;

    float pivot = arr[(low+high)/2].rating;

    while(i <= j){

        while(arr[i].rating > pivot){
            i++;
        }

        while(arr[j].rating < pivot){
            j--;
        }

        if(i <= j){

            Produk temp;

            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            i++;
            j--;
        }

    }

    if(low < j){
        quickSort(low,j);
    }

    if(i < high){
        quickSort(i,high);
    }

}

void tampilProduk(){

    int pilih;

    cout<<"\n=== TAMPILKAN PRODUK ===\n";
    cout<<"1. bubble sort asc (nama)\n";
    cout<<"2. quick sort desc (rating)\n";

    cout<<"pilih cpt : ";
    cin>>pilih;

    if(pilih==1){
        bubbleSort();
    }
    else if(pilih==2){
        quickSort(0,n-1);
    }

    cout<<"\n===============================================================\n";
    printf("%-20s %-15s %-10s %-6s %-6s\n",
    "Nama","Kategori","Harga","Stok","Rate");
    cout<<"===============================================================\n";

    for(int i=0;i<n;i++){

        printf("%-20s %-15s %-10.0lf %-6d %-6.1f\n",
        arr[i].name,
        arr[i].category,
        arr[i].price,
        arr[i].stock,
        arr[i].rating);

    }

}

void cariProduk(){

    char cari[60];
    int found = 0;

    cin.ignore();

    cout<<"\nhayo tadi nama produknya apa? : ";
    cin.getline(cari,60);

    for(int i=0;i<n;i++){

        if(strcmp(arr[i].name,cari)==0){

            cout<<"\nyeyyy yeyyy ketemuuu produknya!\n";

            cout<<"Nama     : "<<arr[i].name<<endl;
            cout<<"Kategori : "<<arr[i].category<<endl;
            cout<<"Harga    : "<<arr[i].price<<endl;
            cout<<"Stok     : "<<arr[i].stock<<endl;
            cout<<"Rating   : "<<arr[i].rating<<endl;

            found = 1;
            break;
        }

    }

    if(found==0){
        cout<<"\nyahh:( produknya gak ketemu\n";
    }

}

void clearData(){

    FILE *pf = fopen("shopease_db.txt","w");

    fclose(pf);

    n = 0;

    cout<<"\nokayyyy! data udah aku clear ya!\n";

}

int main(){

    int menu;

    loadFile();

    do{

        cout<<"\n===== SHOPEASE PRODUCT MANAGER =====\n";

        cout<<"1. Tambah Produk\n";
        cout<<"2. Tampilkan Produk\n";
        cout<<"3. Cari Produk\n";
        cout<<"4. Hapus Semua Data\n";
        cout<<"5. Keluar\n";

        cout<<"mau pilih menu yang mana nih? : ";
        cin>>menu;

        if(menu==1){
            tambahProduk();
        }
        else if(menu==2){
            tampilProduk();
        }
        else if(menu==3){
            cariProduk();
        }
        else if(menu==4){
            clearData();
        }

    }while(menu!=5);

    saveFile();

    cout<<"\nyahhh, kok udah:( okeyy dehh terimakasih yaaaa udah pakee progrmku! semoga harimu minggu terus!\n";

}
