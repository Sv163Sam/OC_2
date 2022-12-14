#include "source.h"

void sum_()
{
    HANDLE value_a = CreateMailslot(L"\\\\.\\mailslot\\a2", 0, MAILSLOT_WAIT_FOREVER, NULL);
    HANDLE value_b = CreateMailslot(L"\\\\.\\mailslot\\b2", 0, MAILSLOT_WAIT_FOREVER, NULL);

    HANDLE second_semafor = OpenSemaphore(EVENT_ALL_ACCESS, TRUE, L"second_semafor");
    HANDLE third_semafor = OpenSemaphore(EVENT_ALL_ACCESS, TRUE, L"third_semafor");

    while (true) {
        WaitForSingleObject(second_semafor, INFINITE);

        print_mes("DEBUG OUT: SECOND PROGRAM");
        print_mes("DEBUG OUT: Program is calculating sum of a and b now!");

        int_convert received_a;
        int_convert received_b;
        int_convert res;

        DWORD real_reading_a = 0;
        DWORD real_reading_b = 0;
        DWORD real_reading_sum = 0;

        ReadFile(value_a, &received_a.bytes, sizeof(int), &real_reading_a, NULL);
        ReadFile(value_b, &received_a.bytes, sizeof(int), &real_reading_b, NULL);

        HANDLE sum = CreateFile(L"\\\\.\\mailslot\\sum", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

        res.value = (received_a.value + received_b.value);

        WriteFile(sum, res.bytes, sizeof(int), &real_reading_sum, NULL);

        CloseHandle(value_a);
        CloseHandle(value_b);

        print_value("Function result - sum a*a and b*b: ", res.value);
        print_mes("DEBUG OUT: Program is terminating now!");

        ReleaseSemaphore(third_semafor, 1, NULL);
    }
}
