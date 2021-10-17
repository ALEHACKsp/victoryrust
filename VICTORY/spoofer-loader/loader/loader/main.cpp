#include "main.h"
#include "conn.h"
#include "aes.hpp"
#include "xor.hpp"
#include "hwid.h"
#include "utils.hpp"
#ifndef _COLORS_
#define _COLORS_

/* FOREGROUND */
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

#endif  /* _COLORS_ */


std::string user_key;


#pragma warning(disable : 4996)

bool createClient() {
    m_Client = std::make_unique<Client>();
    if (m_Client->isSetup()) return true;
    else return false;
}

// Create file from a vector
std::vector<unsigned char> data{};
void CreateFileFromBytes(std::string path, std::vector<unsigned char>vector) {
    std::ofstream outfile(path, std::ios::out | std::ios::binary);
    outfile.write((const char*)&vector[0], vector.size());
}

std::string UserExpire = _xor_("");

void Scenes::Cheat() {
    system("cls");
    std::cout << mixer(
        _xor_(BOLD(FBLU("Expiration date: "))),
        UserExpire
    );

    Sleep(2000);

    std::cout << BOLD(FMAG("\n\nWe getting uniqe build for you, it will get 1min")) << std::endl;

    // Get buffer size
    size_t bufferSize = std::stoi(std::string(
        aes_enc->decrypt(m_Client->cipher_key, m_Client->iv_key,
            m_Client->sendrecieve(aes_enc->encrypt(m_Client->cipher_key, m_Client->iv_key, _xor_("GET_SIZE")))
        )
    ));

    // Get splitting speed
    size_t splitSpeed = std::stoi(std::string(
        aes_enc->decrypt(m_Client->cipher_key, m_Client->iv_key,
            m_Client->sendrecieve(aes_enc->encrypt(m_Client->cipher_key, m_Client->iv_key, _xor_("GET_SPEED")))
        )
    ));

    // Total process
    int forCount = bufferSize / splitSpeed;

    // Remain process
    int remainingFor = bufferSize % splitSpeed;

    // One percent
    int onePercent = bufferSize / 100;

    int receivedBytes = 0;

    for (int i = 0; i < (forCount + remainingFor); i++) {

        // Get bytes { 0x4d;0x5a;0x90 }
        std::string recordBytes = aes_enc->decrypt(m_Client->cipher_key, m_Client->iv_key,
            m_Client->sendrecieve(
                aes_enc->encrypt(m_Client->cipher_key, m_Client->iv_key, _xor_("GET_FILE")
                )
            ));

        if (bufferSize / splitSpeed != receivedBytes / splitSpeed) {

            // Splitting group bytes
            const char* delp = strtok((char*)recordBytes.c_str(), ";");

            while (delp != NULL) {
                // Insert bytes
                data.push_back(std::stoi(delp, 0, 16));
                delp = strtok(NULL, ";");
            }

            receivedBytes += splitSpeed;
        }
        else data.push_back(std::stoi(recordBytes, 0, 16));
    }

    std::cout << BOLD(FGRN("Locating Memory...")) << std::endl;

    // Create file


    char* pe = reinterpret_cast<char*>(data.data());;

    IMAGE_DOS_HEADER* DOSHeader;
    IMAGE_NT_HEADERS64* NtHeader;
    IMAGE_SECTION_HEADER* SectionHeader;

    PROCESS_INFORMATION PI;
    STARTUPINFOA SI;
    ZeroMemory(&PI, sizeof(PI));
    ZeroMemory(&SI, sizeof(SI));


    void* pImageBase;

    char currentFilePath[1024];

    DOSHeader = PIMAGE_DOS_HEADER(pe);
    NtHeader = PIMAGE_NT_HEADERS64(DWORD64(pe) + DOSHeader->e_lfanew);

    if (NtHeader->Signature == IMAGE_NT_SIGNATURE) {

        GetModuleFileNameA(NULL, currentFilePath, MAX_PATH);
        //create process
        if (CreateProcessA(currentFilePath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &SI, &PI)) {

            CONTEXT* CTX;
            CTX = LPCONTEXT(VirtualAlloc(NULL, sizeof(CTX), MEM_COMMIT, PAGE_READWRITE));
            CTX->ContextFlags = CONTEXT_FULL;


            UINT64 imageBase = 0;
            if (GetThreadContext(PI.hThread, LPCONTEXT(CTX))) {
                pImageBase = VirtualAllocEx(
                    PI.hProcess,
                    LPVOID(NtHeader->OptionalHeader.ImageBase),
                    NtHeader->OptionalHeader.SizeOfImage,
                    MEM_COMMIT | MEM_RESERVE,
                    PAGE_EXECUTE_READWRITE
                );


                WriteProcessMemory(PI.hProcess, pImageBase, pe, NtHeader->OptionalHeader.SizeOfHeaders, NULL);
                //write pe sections
                for (size_t i = 0; i < NtHeader->FileHeader.NumberOfSections; i++)
                {
                    SectionHeader = PIMAGE_SECTION_HEADER(DWORD64(pe) + DOSHeader->e_lfanew + 264 + (i * 40));

                    WriteProcessMemory(
                        PI.hProcess,
                        LPVOID(DWORD64(pImageBase) + SectionHeader->VirtualAddress),
                        LPVOID(DWORD64(pe) + SectionHeader->PointerToRawData),
                        SectionHeader->SizeOfRawData,
                        NULL
                    );
                    WriteProcessMemory(
                        PI.hProcess,
                        LPVOID(CTX->Rdx + 0x10),
                        LPVOID(&NtHeader->OptionalHeader.ImageBase),
                        8,
                        NULL
                    );

                }

                CTX->Rcx = DWORD64(pImageBase) + NtHeader->OptionalHeader.AddressOfEntryPoint;
                SetThreadContext(PI.hThread, LPCONTEXT(CTX));
                ResumeThread(PI.hThread);

                WaitForSingleObject(PI.hProcess, NULL);




            }
        }
    }

    HWND consoleWindow = GetConsoleWindow();
  //  CreateFileFromBytes(filePath, data);
    SetWindowPos(consoleWindow, 0, 5000, 5000, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void Scenes::Login() {
    std::cout << _xor_(" Thanks for choosing us! , We are ready do you?\n") << std::endl;
    std::cout << _xor_("|-> License Key: ");
    std::cin >> user_key;
    user_key = mixer(user_key, _xor_(";"), getHWinfo64());
    
    if (!user_key.empty()) {
        std::string successLogin = _xor_("SUCCESS_LOGIN");

        std::string loginQuery = aes_enc->decrypt(
        m_Client->cipher_key, m_Client->iv_key, m_Client->sendrecieve(
            aes_enc->encrypt(m_Client->cipher_key, m_Client->iv_key, user_key)
        ));

        if (loginQuery.size() == successLogin.size()) {
            
            std::string successExpire = _xor_("SUCCESS_EXPIRE");

            std::string expireQuery = aes_enc->decrypt(
            m_Client->cipher_key, m_Client->iv_key, m_Client->sendrecieve(
                aes_enc->encrypt(m_Client->cipher_key, m_Client->iv_key, _xor_("EXPIRE_STATUS"))
            ));

            std::string resultQuery = expireQuery.substr(0, expireQuery.find(_xor_(";")));
            UserExpire = expireQuery.substr(expireQuery.find(_xor_(";")) + 1, expireQuery.size());
            
            if (resultQuery.size() == successExpire.size()) {
                Cheat();
            }
            else {
                std::cout << BOLD(FRED("Bro go buy, your time expired.")) << std::endl;
                Sleep(2000);
                exit(0);
            }
        }
        else {
            std::cout << BOLD(FRED("Login failed, check your key!")) << std::endl;
            Sleep(2000);
            exit(0);
        }
    }
}

int main()
{
    std::string str("#VICTORY SPOOFER");
    SetConsoleTitle(str.c_str());
    // Create client
    if (!createClient()) return 0;
    // Login scene
    m_Scenes->Login();
    return 0;
}