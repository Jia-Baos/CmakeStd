#include <iostream>
#include <winsock2.h>
#include "./client/client.hpp"

int main(int argc, char *argv[])
{

    // 初始化DLL
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 1), &wsa_data);

    // 创建套接字
    SOCKET client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 绑定套接字
    sockaddr_in socket_addr;
    ZeroMemory(&socket_addr, sizeof(socket_addr));
    socket_addr.sin_family = PF_INET;
    socket_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    socket_addr.sin_port = htons(1234);

    connect(client_socket, (SOCKADDR *)&socket_addr, sizeof(sockaddr));

    // 接收服务器发送的信息
    char message[512] = {0};
    recv(client_socket, message, 512, 0);
    std::cout << "Message from Server is: " << message << std::endl;

    // 关闭套接字
    closesocket(client_socket);

    // 停止使用DLL
    WSACleanup();

    system("pause");

    return 0;
}
