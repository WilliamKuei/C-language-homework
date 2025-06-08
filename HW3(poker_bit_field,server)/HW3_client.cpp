#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>  // for inet_pton
#include <cstring>



using namespace std;

#define BUFFERSIZE 100
char buf[BUFFERSIZE + 1];
int rVal;

int connectServer(const char* ServerIP, unsigned short ServerPort);

int main() {
    WSADATA WsaData;
    
    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &WsaData) != 0) { 
        cerr << "WSAStartup failed!" << endl;
        return 1;
    }

    connectServer("127.0.0.1", 5114);

    // 清理 Winsock
    cout << "Press Enter to exit..." << endl;
    cin.get();
    WSACleanup();
    return 0;
}

int connectServer(const char* ServerIP, unsigned short ServerPort) {
    SOCKET ServerSocket = INVALID_SOCKET;
    SOCKADDR_IN serveraddr;

    // 建立 Server 的 SOCKET
    ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ServerSocket == INVALID_SOCKET) {
        cerr << "Socket creation failed! Error: " << WSAGetLastError() << endl;
        return 0;
    }

    // 設定伺服器地址
    serveraddr.sin_family = AF_INET;
    if (inet_pton(AF_INET, ServerIP, &serveraddr.sin_addr) != 1) {
        cerr << "Invalid IP Address!" << endl;
        closesocket(ServerSocket);
        return 0;
    }
    serveraddr.sin_port = htons(ServerPort);

    // 連線到 Server
    if (connect(ServerSocket, (LPSOCKADDR)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR) {
        cerr << "Connected Server Error! Code: " << WSAGetLastError() << endl;
        closesocket(ServerSocket);
        return 0;
    }

    cout << "Connect successfully!" << endl;

    // 傳送訊息給 Server
    strcpy_s(buf, BUFFERSIZE, "Hello!\n");
    rVal = send(ServerSocket, buf, strlen(buf), 0);

    while (rVal > 0) {
        rVal = recv(ServerSocket, buf, BUFFERSIZE, 0);
        
        // 檢查連線是否關閉或發生錯誤
        if (rVal == SOCKET_ERROR) {
            cerr << "Receive failed! Error: " << WSAGetLastError() << endl;
            break;
        } else if (rVal == 0) {
            cout << "Server closed connection." << endl;
            break;
        }

        buf[rVal] = '\0';  // 確保字串結束
        printf("[Server] %s", buf);

        cout << "Enter message: ";
        cin.getline(buf, BUFFERSIZE);

        rVal = send(ServerSocket, buf, strlen(buf), 0);
    }

    // 關閉 Socket
    closesocket(ServerSocket);
    return 1;
}
