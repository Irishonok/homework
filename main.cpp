#include <QCoreApplication>
#include <QFile>
#include <ctime>
#include <windows.h>

void RandFillAr(int *ar, int size){
    srand(time(NULL));
    for(int i = 0; i < size; i++){
        ar[i]=rand() % 100;
    }
}


void WriteToFile(int something, const char* fileName){
    QFile mur(fileName);
    mur.open(QIODevice::Append);
    mur.write(QString::number(something).toUtf8());
    mur.putChar('\t');
    mur.close();
}

void Swap(int *a, int *b) {
    int c;
    c = *b;
    *b = *a;
    *a = c;
}
int Min(int *m, int size){
    int ind = 0;
    for(int i = 1; i < size; i++){
        if(m[ind] > m[i]){
            ind = i;
        }
    }
    return ind;
}

void InsertionSort(int* mas, int size) {
    for(int i = 0; i < size; i++){
        int ind = Min(&mas[i], size - i) + i;
        Swap(&mas[i], &mas[ind] ) ;
    }
}

void BubbleSort(int *ar, int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size - 1; j++){
            if(ar[j] > ar[j+1]){
                Swap(&ar[j+1], &ar[j]);
            }
        }
    }
}

int TimeBubble(int *ar, int size){
    RandFillAr(ar,size);
    int time = GetTickCount();
    BubbleSort(ar, size);
    return GetTickCount() - time;
}

int TimeInsert(int *ar, int size){
    RandFillAr(ar,size);
    int time = GetTickCount();
    InsertionSort(ar, size);
    return GetTickCount() - time;
}

int test(void (*sort)(int*, int), int* data, int size)
{
    RandFillAr(data,size);
    int time = GetTickCount();
    sort(data, size);
    return GetTickCount() - time;

}

int main()
{
    void (*sort_p[2])(int*, int) = {BubbleSort, InsertionSort};

    int *ar;
    for (int i = 100; i < 100000; i+= 100) {
        ar = new int [i];
        WriteToFile(i, "test.txt");
        for (int j = 0; j < 2; j++) {
            WriteToFile(test(sort_p[j], ar, i), "test.txt");
        }
        delete [] ar;
        QFile mur("test.txt");
        mur.open(QIODevice::Append);
        mur.putChar('\n');
        mur.close();
    }

    return 0;

    const int STEP_SIZE = 100;
    int size;
    for(int i = 0; i < 5000; i++){
        size = STEP_SIZE * i;
        int *ar = new int[size];
        WriteToFile(size, "time_from_size");

        WriteToFile(TimeBubble(ar, size), "time_from_size");

        WriteToFile(TimeInsert(ar, size), "time_from_size");

        delete [] ar;

        QFile mur("time_from_size");
        mur.open(QIODevice::Append);
        mur.putChar('\n');
        mur.close();
    }
}
