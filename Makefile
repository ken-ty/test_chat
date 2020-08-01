CC := gcc

ALL: sock_chat

sock_chat: sock_chat.c
	$(CC) -o sock_chat sock_chat.c

clean:
	$(RM) sock_chat
