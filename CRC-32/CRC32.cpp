/**
    Автор : Аннаев Арслан
    Задание
    1) написать функцию/метод рассчета CRC32;
        начальное значение - 0xFFFFFFFF
        перед записью в поле, XOR со значением
        0xFFFFFFFF не выполнять
    2) написать функцию/метод обработки входного
       пакета и формирования выходного пакета;
        2.1) Получить пакет
        2.2) Проверить контрольную сумму
        2.3) Посчитать количество единиц в данных
        2.4) Сформировать выходной пакет
**/


#include <iostream>
#include <bitset>
#include <stddef.h>

using namespace std;

// структура пакета
struct package{
    uint8_t     receiver;       // адрес получателя
    uint8_t     sender;         // адрес отправителя
    uint8_t     dest;           // функциональное назначение пакета
    uint16_t    data_length;    // длина пакета
    uint8_t     *data;          // данные
    uint32_t    CRC32;          // контрольная сумма
};

// обьединение для корректного преобразования формата
 union Memory{
            uint16_t i16;
            uint8_t i8[2];
        };

// прототипы функций
uint32_t crc32_IEEE_802(const uint8_t *data,                        // расчет контрольной суммы
                        uint16_t len,
                        uint32_t sum);
bool     ProcessPack(package *income, package *outcome);            // обработка пакета
uint16_t BitCounting(uint8_t * data, uint16_t len);                 // подсчет количества единиц в байтах
void getDataFromUser(uint32_t * data, uint32_t array_length);       // получение данных
void ShowPackage(package *pack);                                    // отображение пакета

// =========================================================================
int main()
{
    setlocale(LC_ALL, "rus");                   // локализация для кириллицы
    uint32_t array_length = 10;               // длина массива данных
    uint32_t data[array_length];                // массив данных

    getDataFromUser(data, array_length);        // получаем данные от пользователя

    // количество байтов
    uint16_t len = sizeof(data[0])*array_length;

    package out;                // исходящий пакет
    package in;                 // формируем пакет

    in.receiver = 0xff;
    in.sender =0x0;
    in.data_length = len;
    in.dest = 0xAA;
    in.data = (uint8_t*)data;
    in.CRC32 = crc32_IEEE_802(in.data, in.data_length,0xFFFFFFFFUL);


    if (!ProcessPack(&in, &out)){
        cout << "Ошибка, не корректные данные пакета " << endl;
        return 1;
    } else{
        cout << "Количество единиц в данных = "
             << *(uint16_t *)out.data << endl;
        ShowPackage(&out);

    }
     return 0;
}

// =========================================================================
// отображение пакета
void ShowPackage(package *pack){
    cout << "Адрес отправителя : " << bitset<8>(pack->sender) << endl
         << "Адрес получателя  : " << bitset<8>(pack->receiver) << endl
         << "Код назначения    : " << bitset<8>(pack->dest) << endl
         << "Размер данных     : " << pack->data_length << endl
         << "CRC-32            : " << hex << pack->CRC32 << endl;
}

// =========================================================================
// получение данных
void getDataFromUser(uint32_t *data, uint32_t array_length){
    for(uint32_t i=0; i < array_length; i++){
         data[i] = 0xff;
      // cout << "Enter the value " << endl;
      // cin >> data[i];
    }
}


// =========================================================================
// расчет контрольной суммы
/**
           0xEDB88320
    Poly : 0x04C11DB7
*/

uint32_t crc32_IEEE_802(const uint8_t *data,uint16_t len, uint32_t sum){
    uint32_t crc_table[256];                        // создаем таблицу

    uint32_t crc32;

    // формируем таблицу
    for (uint16_t i = 0; i < 256; i++){
        crc32 = i;
        for (uint16_t j = 0; j < 8; j++){
            crc32 = crc32 & 1 ? (crc32 >> 1) ^ 0xEDB88320UL
                           :(crc32 >> 1);
        }
        crc_table[i] = crc32;
    }
    crc32 = sum;


    while (len--){
        crc32 = crc_table[(crc32 ^ *data++) & 0xFF] ^ (crc32 >> 8);
    }
    return crc32 ;
}


// =========================================================================
// обработка входного пакета и формирование нового выходного
bool ProcessPack(package*income, package *outcome){

    // определяем контрольную сумму
    uint32_t crc = crc32_IEEE_802(income->data,
                                  income->data_length,
                                  0xFFFFFFFFUL);

   // если контрольная сумма совпала и код назначения равен 0xAA
    if(!((crc == income->CRC32) && (income->dest == 0xAA))){
        return false;
    }
    else {
        Memory bitCount;                                            // выделяем память для результата
        bitCount.i16 = BitCounting(income->data,                    // количество единиц в данных
                                   income->data_length);
        outcome->receiver = 0x0;
        outcome->sender = 0xff;
        outcome->dest = 0xAB;
        outcome->data_length = 2;
        outcome->data = new uint8_t[2];
        outcome->data = (uint8_t *)bitCount.i8;
        outcome->CRC32 = crc32_IEEE_802(outcome->data,
                                        outcome->data_length,
                                        0xFFFFFFFFUL);
        return true;
    }
}


// =========================================================================
// подсчет количества единиц в байтах
uint16_t BitCounting(uint8_t * data, uint16_t len){

    uint16_t counter = 0;                           //  счетчик
    for(uint16_t i=0; i < len; i++){                //  проходим по всем данным
        while(data[i]){                             //  берем отдельный байт
        counter += data[i] & 1;                     //  считываем единицы
        data[i] >>= 1;                              //  смещаем
        }
   }
    return counter;
}
// =========================================================================
