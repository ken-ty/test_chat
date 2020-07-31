CC := gcc

ALL: sock_recv sock_send

sock_recv: sock_recv.c
	$(CC) -o sock_recv sock_recv.c

sock_send: sock_send.c
	$(CC) -o sock_send sock_send.c

clean:
	$(RM) sock_recv sock_send
