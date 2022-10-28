#include "source.h"

void pow_()
{
    HANDLE value_a = CreateMailslot(L"\\\\.\\mailslot\\a", 0, MAILSLOT_WAIT_FOREVER, NULL);
    HANDLE value_b = CreateMailslot(L"\\\\.\\mailslot\\b", 0, MAILSLOT_WAIT_FOREVER, NULL);

    HANDLE first_semafor = OpenSemaphore(EVENT_ALL_ACCESS, TRUE, L"first_semafor");
    HANDLE second_semafor = OpenSemaphore(EVENT_ALL_ACCESS, TRUE, L"second_semafor");


    while (true)
    {
        WaitForSingleObject(first_semafor, INFINITE);

        print_mes("DEBUG OUT: FIRST PROGRAM");
        print_mes("DEBUG OUT: Program is calculating pow of a and b now!");

        int_convert received_a;
        int_convert received_b;
        int_convert res_a;
        int_convert res_b;
        DWORD real_reading_a = 0;//unsigned long
        DWORD real_reading_b = 0;

        auto tmp1 = ReadFile(value_a, &received_a.bytes, sizeof(int), &real_reading_a, NULL);
        auto tmp2 = ReadFile(value_b, &received_b.bytes, sizeof(int), &real_reading_b, NULL);

        HANDLE a_pow = CreateFile(L"\\\\.\\mailslot\\a^2", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        HANDLE b_pow = CreateFile(L"\\\\.\\mailslot\\b^2", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

        real_reading_a = 0;
        real_reading_b = 0;

        res_a.value = received_a.value * received_a.value;
        res_b.value = received_b.value * received_b.value;

        WriteFile(a_pow, res_a.bytes, sizeof(int), &real_reading_a, NULL);
        WriteFile(b_pow, res_b.bytes, sizeof(int), &real_reading_b, NULL);

        print_value("Function result - a: ", res_a.value);
        print_value("Function result - b: ", res_b.value);

        print_mes("DEBUG OUT: Program is terminating now!");

        CloseHandle(value_a);
        CloseHandle(value_b);

        ReleaseSemaphore(second_semafor, 1, NULL);
    }
}
