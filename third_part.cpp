#include "source.h"

void sqrt_()
{
    HANDLE result = CreateMailslot(L"\\\\.\\mailslot\\sum", 0, MAILSLOT_WAIT_FOREVER, NULL);

    HANDLE third_semafor = OpenSemaphore(EVENT_ALL_ACCESS, TRUE, L"third_semafor");
    HANDLE fourth_semafor = OpenSemaphore(EVENT_ALL_ACCESS, TRUE, L"fourth_semafor");

    while (true) {
        WaitForSingleObject(third_semafor, INFINITE);

        print_mes("DEBUG OUT: THIRD PROGRAM");
        print_mes("DEBUG OUT: Program is calculating sum of a and b now!");

        int_convert received_sum;
        double_convert mresult;

        DWORD real_reading_sum = 0;
        DWORD real_writing_res = 0;

        ReadFile(result, &received_sum.bytes, sizeof(int), &real_reading_sum, NULL);

        HANDLE res = CreateFile(L"\\\\.\\mailslot\\res", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

        mresult.value = sqrt(received_sum.value);

        WriteFile(res, mresult.bytes, sizeof(double), &real_writing_res, NULL);

        CloseHandle(result);

        print_value("Function result - sqrt of (a*a + b*b): ", res.value);
        print_mes("DEBUG OUT: Program is terminating now!");

        ReleaseSemaphore(fourth_semafor, 1, NULL);
    }
}
