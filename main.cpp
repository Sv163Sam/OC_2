#include "source.h"

// B E I L; PIPE FORM ONE PROCESS, SEMAFOR, MAILSLOT, C = SQRT(A^2+B^2)// VARIANT 14

int main()
{
    print_mes("DEBUG OUT: MAIN");

    DWORD info_1;
    DWORD info_2;
    DWORD info_3;
    CreateSemaphore(NULL, 0, 1, L"first_semafor");
    CreateSemaphore(NULL, 0, 1, L"second_semafor");
    CreateSemaphore(NULL, 0, 1, L"third_semafor");
    CreateSemaphore(NULL, 0, 1, L"fourth_semafor");

    CreateThread(NULL, 0, pow_, NULL, 0, &info_1);
    CreateThread(NULL, 0, pow_, NULL, CREATE_SUSPENDED, &info_2);
    CreateThread(NULL, 0, pow_, NULL, CREATE_SUSPENDED, &info_3);

    HANDLE res = CreateMailslot(L"\\\\.\\mailslot\\res", 0, MAILSLOT_WAIT_FOREVER, NULL);

    int a = 0;
    int b = 0;

    print_mes("Please enter a: ");
    cin_value(a);
    print_mes("Please enter b: ");
    cin_value(b);


    /// ------- ЗАПИСЬ а и b --------- ///
    HANDLE value_a = CreateFile(L"\\\\.\\mailslot\\a", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    HANDLE value_b = CreateFile(L"\\\\.\\mailslot\\b", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    int_convert received_a;
    int_convert received_b;
    received_a.value = a;
    received_b.value = b;

    DWORD real_read_a = 0;
    DWORD real_read_b = 0;

    WriteFile(value_a, received_a.bytes, sizeof(int), &real_read_a, NULL);
    WriteFile(value_b, received_b.bytes, sizeof(int), &real_read_b, NULL);

    CloseHandle(value_a);
    CloseHandle(value_a);

    HANDLE first_semafor = OpenSemaphore(EVENT_ALL_ACCESS, TRUE, L"first_semafor");//transport
    HANDLE fourth_semafor = OpenSemaphore(EVENT_ALL_ACCESS, TRUE, L"fourth_semafor");

    ReleaseSemaphore(first_semafor, 1, NULL);
    WaitForSingleObject(fourth_semafor, INFINITE);
    sleep(10);

    double_convert result;
    result.value = 0;

    DWORD real_write_result = 0;
    ReadFile(res, &result.bytes, sizeof(double), &real_write_result, NULL);
    CloseHandle(res);

    print_value("ALL RESULT CALCULATIONS - sqrt(a^2 + b^2)", result.value);
    print_mes("DEBUG OUT: Program is terminating now!");

    return 0;
}
