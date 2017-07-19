int setupLocalSocket(unsigned short port, int queueSize) {
   int socketfd, on;
   struct sockaddr_in local;
   on = 1;

   if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == ERROR) return ERROR;

}
