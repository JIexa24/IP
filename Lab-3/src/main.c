#include "../include/dsignlib.h"
#include "../include/extralib.h"
#include "../include/md5.h"

int main(int argc, const char *argv[])
{
    char rsa[] = "./test.txt";
    RSA_sign(rsa);
    rsa[10] = '\0';
    if (RSA_sign_check(rsa)) {
        printf("RSA signature result:\t[FAILED]\n");
    } else {
        printf("RSA signature result:\t[SUCCESS]\n");
    }

    char elg[] = "./test.txt";
    ELG_sign(elg);
    elg[10] = '\0';
    if (ELG_sign_check(elg)) {
        printf("ELG signature result:\t[FAILED]\n");
    } else {
        printf("ELG signature result:\t[SUCCESS]\n");
    }

    char gost[] = "./test.txt";
    GOST_sign(gost);
    gost[10] = '\0';
    if (!GOST_sign_check(gost)) {
        printf("GOST signature result:\t[FAILED]\n");
    } else {
        printf("GOST signature result:\t[SUCCESS]\n");
    }

    return EXIT_SUCCESS;
}
