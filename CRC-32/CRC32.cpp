/**
    ����� : ������ ������
    �������
    1) �������� �������/����� �������� CRC32;
        ��������� �������� - 0xFFFFFFFF
        ����� ������� � ����, XOR �� ���������
        0xFFFFFFFF �� ���������
    2) �������� �������/����� ��������� ��������
       ������ � ������������ ��������� ������;
        2.1) �������� �����
        2.2) ��������� ����������� �����
        2.3) ��������� ���������� ������ � ������
        2.4) ������������ �������� �����
**/


#include <iostream>
#include <bitset>
#include <stddef.h>

using namespace std;

// ��������� ������
struct package{
    uint8_t     receiver;       // ����� ����������
    uint8_t     sender;         // ����� �����������
    uint8_t     dest;           // �������������� ���������� ������
    uint16_t    data_length;    // ����� ������
    uint8_t     *data;          // ������
    uint32_t    CRC32;          // ����������� �����
};

// ����������� ��� ����������� �������������� �������
 union Memory{
            uint16_t i16;
            uint8_t i8[2];
        };

// ��������� �������
uint32_t crc32_IEEE_802(const uint8_t *data,                        // ������ ����������� �����
                        uint16_t len,
                        uint32_t sum);
bool     ProcessPack(package *income, package *outcome);            // ��������� ������
uint16_t BitCounting(uint8_t * data, uint16_t len);                 // ������� ���������� ������ � ������
void getDataFromUser(uint32_t * data, uint32_t array_length);       // ��������� ������
void ShowPackage(package *pack);                                    // ����������� ������

// =========================================================================
int main()
{
    setlocale(LC_ALL, "rus");                   // ����������� ��� ���������
    uint32_t array_length = 10;               // ����� ������� ������
    uint32_t data[array_length];                // ������ ������

    getDataFromUser(data, array_length);        // �������� ������ �� ������������

    // ���������� ������
    uint16_t len = sizeof(data[0])*array_length;

    package out;                // ��������� �����
    package in;                 // ��������� �����

    in.receiver = 0xff;
    in.sender =0x0;
    in.data_length = len;
    in.dest = 0xAA;
    in.data = (uint8_t*)data;
    in.CRC32 = crc32_IEEE_802(in.data, in.data_length,0xFFFFFFFFUL);


    if (!ProcessPack(&in, &out)){
        cout << "������, �� ���������� ������ ������ " << endl;
        return 1;
    } else{
        cout << "���������� ������ � ������ = "
             << *(uint16_t *)out.data << endl;
        ShowPackage(&out);

    }
     return 0;
}

// =========================================================================
// ����������� ������
void ShowPackage(package *pack){
    cout << "����� ����������� : " << bitset<8>(pack->sender) << endl
         << "����� ����������  : " << bitset<8>(pack->receiver) << endl
         << "��� ����������    : " << bitset<8>(pack->dest) << endl
         << "������ ������     : " << pack->data_length << endl
         << "CRC-32            : " << hex << pack->CRC32 << endl;
}

// =========================================================================
// ��������� ������
void getDataFromUser(uint32_t *data, uint32_t array_length){
    for(uint32_t i=0; i < array_length; i++){
         data[i] = 0xff;
      // cout << "Enter the value " << endl;
      // cin >> data[i];
    }
}


// =========================================================================
// ������ ����������� �����
/**
           0xEDB88320
    Poly : 0x04C11DB7
*/

uint32_t crc32_IEEE_802(const uint8_t *data,uint16_t len, uint32_t sum){
    uint32_t crc_table[256];                        // ������� �������

    uint32_t crc32;

    // ��������� �������
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
// ��������� �������� ������ � ������������ ������ ���������
bool ProcessPack(package*income, package *outcome){

    // ���������� ����������� �����
    uint32_t crc = crc32_IEEE_802(income->data,
                                  income->data_length,
                                  0xFFFFFFFFUL);

   // ���� ����������� ����� ������� � ��� ���������� ����� 0xAA
    if(!((crc == income->CRC32) && (income->dest == 0xAA))){
        return false;
    }
    else {
        Memory bitCount;                                            // �������� ������ ��� ����������
        bitCount.i16 = BitCounting(income->data,                    // ���������� ������ � ������
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
// ������� ���������� ������ � ������
uint16_t BitCounting(uint8_t * data, uint16_t len){

    uint16_t counter = 0;                           //  �������
    for(uint16_t i=0; i < len; i++){                //  �������� �� ���� ������
        while(data[i]){                             //  ����� ��������� ����
        counter += data[i] & 1;                     //  ��������� �������
        data[i] >>= 1;                              //  �������
        }
   }
    return counter;
}
// =========================================================================
