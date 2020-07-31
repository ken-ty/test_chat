#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void)
{
	int sock;
	struct sockaddr_in addr;
	char buf[2048];

	sock = socket(AF_INET, SOCK_DGRAM, 0);  // ソケットの生成
	addr.sin_family = AF_INET;  // 通信プロトコルの指定
	addr.sin_port = htons(8000);  // ポートの指定
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(sock, (struct sockaddr *)&addr, sizeof(addr));  // ソケットにアドレスを割り当てる

recv(sock, buf, sizeof(buf), 0);  // 受信する
printf("%s\n", buf);  // プリントする
	close(sock);  // ソケットを解放
	return 0;
}
