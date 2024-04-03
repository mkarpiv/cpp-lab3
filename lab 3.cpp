#include <iostream>
#include <cstring>
#include <windows.h>
using namespace std;

class StringArray {
private:
    int size;
    char** array;

public:
    StringArray(int n) {
        size = n;
        array = new char* [size];
        for (int i = 0; i < size; ++i) {
            array[i] = nullptr;
        }
    }

    ~StringArray() {
        for (int i = 0; i < size; ++i) {
            delete[] array[i];
        }
        delete[] array;
    }

    void setString(int index, const char* str) {
        if (index >= 0 && index < size) {
            if (array[index] != nullptr) {
                delete[] array[index];
            }
            size_t length = strlen(str);
            array[index] = new char[length + 1];
            strcpy_s(array[index], length + 1, str);
        }
        else {
            cerr << "≤ндекс поза межами" << endl;
        }
    }

    const char* getString(int index) const {
        if (index >= 0 && index < size) {
            return array[index];
        }
        else {
            cerr << "≤ндекс поза межами" << endl;
            return nullptr;
        }
    }

    int getSize() const {
        return size;
    }

    static StringArray mergeArrays(const StringArray& arr1, const StringArray& arr2) {
        int newSize = arr1.size + arr2.size;
        StringArray mergedArray(newSize);

        for (int i = 0; i < arr1.size; ++i) {
            if (arr1.array[i] != nullptr) {
                mergedArray.setString(i, arr1.array[i]);
            }
        }

        for (int i = 0; i < arr2.size; ++i) {
            if (arr2.array[i] != nullptr) {
                mergedArray.setString(arr1.size + i, arr2.array[i]);
            }
        }

        return mergedArray;
    }

    static StringArray mergeArraysUnique(const StringArray& arr1, const StringArray& arr2) {
        StringArray mergedArray(arr1.size + arr2.size);

        for (int i = 0; i < arr1.size; ++i) {
            if (arr1.array[i] != nullptr) {
                mergedArray.setString(i, arr1.array[i]);
            }
        }

        for (int i = 0; i < arr2.size; ++i) {
            bool exists = false;
            for (int j = 0; j < arr1.size; ++j) {
                if (arr2.array[i] != nullptr && strcmp(arr2.array[i], arr1.array[j]) == 0) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                mergedArray.setString(arr1.size + i, arr2.array[i]);
            }
        }

        return mergedArray;
    }
};

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int size1, size2;
    cout << "¬вед≥ть розм≥р першого масиву: ";
    cin >> size1;

    StringArray array1(size1);
    for (int i = 0; i < size1; ++i) {
        char buffer[100];
        cout << "¬вед≥ть р€док " << i << " дл€ першого масиву: ";
        cin.ignore(); // ўоб уникнути пропуску введенн€
        cin.getline(buffer, 100);
        array1.setString(i, buffer);
    }

    cout << "¬вед≥ть розм≥р другого масиву: ";
    cin >> size2;

    StringArray array2(size2);
    for (int i = 0; i < size2; ++i) {
        char buffer[100];
        cout << "¬вед≥ть р€док " << i << " дл€ другого масиву: ";
        cin.ignore(); // ўоб уникнути пропуску введенн€
        cin.getline(buffer, 100);
        array2.setString(i, buffer);
    }

    cout << "ѕерший масив:" << endl;
    for (int i = 0; i < array1.getSize(); ++i) {
        cout << array1.getString(i) << endl;
    }
    cout << endl;

    cout << "ƒругий масив:" << endl;
    for (int i = 0; i < array2.getSize(); ++i) {
        cout << array2.getString(i) << endl;
    }
    cout << endl;

    StringArray merged = StringArray::mergeArrays(array1, array2);
    cout << "ќб'Їднаний масив:" << endl;
    for (int i = 0; i < merged.getSize(); ++i) {
        cout << merged.getString(i) << endl;
    }
    cout << endl;

    StringArray mergedUnique = StringArray::mergeArraysUnique(array1, array2);
    cout << "ќб'Їднаний ун≥кальний масив:" << endl;
    for (int i = 0; i < mergedUnique.getSize(); ++i) {
        cout << mergedUnique.getString(i) << endl;
    }

    return 0;
}
