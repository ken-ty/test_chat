#include <arpa/inet.h>  // ソケット間通信に必要なヘッダ
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>  // マルチスレッド処理に必要なヘッダ
#include <stdlib.h>
#include <string.h>

void recv_thread(void);  // 受信用スレッド
int sock;  // ソケットの番号

int main(int argc, char *argv[])
{
	pthread_t t1;
	struct sockaddr_in addr;  // ソケット間通信用のデータ構造体
	char send_buf[2048];
	sock = socket(AF_INET, SOCK_DGRAM, 0);  // ソケットの生成

	addr.sin_family = AF_INET;  // 通信プロトコルの指定
	addr.sin_port = htons(atoi(argv[1]));  // 受信ポートの指定
	addr.sin_addr.s_addr = INADDR_ANY;  // 受信ポートの指定
	bind(sock, (struct sockaddr *)&addr, sizeof(addr));  // ソケットにアドレスを割り当てる
	pthread_create(&t1, NULL, (void *)recv_thread, (void *)NULL);

	addr.sin_port = htons(atoi(argv[2]));  // 送信ポートの指定
	if (argc == 4) addr.sin_addr.s_addr = inet_addr(argv[3]);  // IPアドレス
	while(1)
	{
		scanf("%s", send_buf);
		if (!strcmp(send_buf, "quit")) break;  // quitと入力すると終了
		sendto(sock, send_buf, sizeof(send_buf), 0, (struct sockaddr *)&addr, sizeof(addr));  // データを送信
	}
	close(sock);  // ソケットを解放
	return 0;
}

void recv_thread(void)
{
	char recv_buf[2048];
	while(1)
	{
		int num = recv(sock, recv_buf, sizeof(recv_buf), 0);
		recv_buf[num] = 0;
		printf("%s\n", recv_buf);
	}
}
