/*
 * NULL pointer dereference in proxy_getaddrinfo()
 * if node == NULL && hints == NULL.
 */
#define _POSIX_C_SOURCE 200112L
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void on_crash(int sig) {
    fprintf(stderr, "POC_HIT: signal %d from getaddrinfo(NULL, \"80\", NULL, &res)\n", sig);
    fflush(stderr);
    _exit(0);
}

int main(void) {
    struct addrinfo *res = 0;
    int rc;
    signal(SIGSEGV, on_crash);
    signal(SIGBUS, on_crash);
    rc = getaddrinfo(NULL, "80", NULL, &res);
    fprintf(stderr, "POC_MISS: getaddrinfo returned %d\n", rc);
    return 1;
}
