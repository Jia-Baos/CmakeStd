#include <iostream>
#include <winsock2.h>
#include "./server/server.hpp"

int main(int argc, char *argv[])
{

    // 初始化DLL
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 1), &wsa_data);

    // 创建套接字
    SOCKET server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 绑定套接字
    sockaddr_in socket_addr;
    ZeroMemory(&socket_addr, sizeof(socket_addr));
    socket_addr.sin_family = PF_INET;
    socket_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    socket_addr.sin_port = htons(1234);
    bind(server_socket, (sockaddr *)&socket_addr, sizeof(socket_addr));

    // 进入监听状态
    listen(server_socket, 20);

    // 接收客户端请求
    SOCKADDR client_addr;
    int size = sizeof(client_addr);
    SOCKET client_socket = accept(server_socket, (SOCKADDR *)&client_addr, &size);

    // 向客户端发送消息
    std::cout << "Connect successfully, ready to send message..." << std::endl;
    const char *message = "hello world, socket!";
    send(client_socket, message, (int)strlen(message), 0);

    // 关闭套接字
    closesocket(client_socket);
    closesocket(server_socket);

    // 停止使用DLL
    WSACleanup();
    system("pause");

    return 0;
}
