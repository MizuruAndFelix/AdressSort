﻿#include <fstream>
#include <iostream>
#include <locale.h>
#include <windows.h>
#include <string>
using namespace std;


class Adresa
{
private:
    string city;
    string street;
    int home;
    int room;
    string full; //шоб полный адресс хранить
public:
    Adresa(string city_, string street_, int home_, int room_)
    {
        city = city_;
        street = street_;
        home = home_;
        room = room_;
    }
    void SetCity(string valueCity)
    {
        city = valueCity;
    }
    string GetCity()
    {
        return city;
    }
    void SetStreet(string valueStreet)
    {
        street = valueStreet;
    }
    string GetStreet()
    {
        return street;
    }
    void SetHome(int valueHome)
    {
        home = valueHome;
    }
    int GetHome()
    {
        return home;
    }
    void SetRoom(int valueRoom)
    {
        room = valueRoom;
    }
    int GetRoom()
    {
        return room;
    }
    string SetSum(int valueFull)
    {
        full = valueFull;
    }
    string GetFull()
    {
        return full;
    }
    bool comprasion(Adresa* arrAdress, int i)
    {
        return (arrAdress[i - 1].city > arrAdress[i].city);
    }
    
    string fullAddress();
    Adresa() {}
};

string fullAddress();


string Adresa::fullAddress() //полный адресс в строку
{
    return city + " " + street + " " + to_string(home) + " " + to_string(room);
}


int fullAddressPrint(Adresa* arrAdress,int numbersAdress) //ФУНКЦИЯ (НЕ МЕТОД) печать в файл
{
    ofstream fileOut("out.txt");
    if (fileOut.is_open())
    {
        std::cout << "File out.txt is open." << std::endl;
    }
    else
    {
        std::cout << "Eror file out.txt is not open!" << std::endl;
        return 0;
    }

    fileOut << "Число адресов: " << numbersAdress << endl;
    fileOut << "Формат вывода адреса: <название города>, <название улицы>, <номер дома>, <номер квартиры>.\n";

    for (int i = numbersAdress - 1; i >= 0; i--) //надо проверить корректность номеров 5
    {//если чо переделать на (int i = numbersAdress ; i >= 1; i--)
        fileOut << "Адресс #" << numbersAdress - i << " " << arrAdress[i].fullAddress() << endl;
    }
    fileOut.close();
}

Adresa* createDinamicStringArr(int numbersAdress)// функклия для динамического массива
{
    Adresa* stringArr = new Adresa[numbersAdress]
    {
    };
    return stringArr;
}
void deleteTextArr(Adresa* stringArr, int numbersAdress) //удалить массив чтоб не забивать память
{
    delete[] stringArr;
}


//void bubleAdress(Adresa* arrAdress, int numbersAdress) //пузырек сортировка
//{
//    string t = {};
//    bool swap = false;
//    while (swap)
//    {
//        for (int i = numbersAdress; i < 0; --i)
//        {
//            if (arrAdress[i - 1] > arrAdress[i])
//            {
//                t = arrAdress[i];
//                arrAdress[i] = arrAdress[i - 1];
//                arrAdress[i - 1] = t;
//                swap = true;
//            }
//        }
//    }
//}

int main()
{
    setlocale(LC_ALL, ".UTF8");
    setlocale(LC_ALL, "Russian"); //Корректное отображение Кириллицы
    system("chcp 1251");
    SetConsoleCP(1251); //перевод на русский
    SetConsoleOutputCP(1251);

    cout << "start\n";

    string city_m = {};
    string street_m = {};
    int home_m = 0;
    int room_m = 0;
    int numbersAdress = 0;

    std::ifstream fileIn("in.txt"); // Открываю и проверяю
    if (fileIn.is_open())
    {

        std::cout << "File in.txt is open." << std::endl;
        fileIn >> numbersAdress;
        Adresa* arrAdress = createDinamicStringArr(numbersAdress);

        for (int i = numbersAdress - 1; i >= 0; i--)
        {
            fileIn >> city_m >> street_m >> home_m >> room_m;
            
            arrAdress[i].SetCity(city_m);
            arrAdress[i].SetStreet(street_m);
            arrAdress[i].SetHome(home_m);
            arrAdress[i].SetRoom(room_m);
        }
        fileIn.close(); //закрыт адресса в массивах

        bool swaped = false;
        Adresa t;
        do
        {
            for (int i = numbersAdress - 1; i < 0; --i) //5
            {
                if (t.comprasion(arrAdress, i))
                {
                    t = arrAdress[i];
                    arrAdress[i] = arrAdress[i - 1];
                    arrAdress[i - 1] = t;
                    swaped = true;
                }
            }
        } while (swaped);
       //bublesort

        fullAddressPrint(arrAdress, numbersAdress); //печать в out.txt

        deleteTextArr(arrAdress, numbersAdress);//память очищена

    }
    else
    {
        std::cout << "Eror! File in.txt is not open!" << std::endl;
        return 0;
    }
}