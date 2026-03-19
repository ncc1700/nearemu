#ifndef NEAREMU_H_INCLUDED
#define NEAREMU_H_INCLUDED

#include <stdio.h>
#include <stdint.h>


#define NFAIL(message, ...) printf("[-] %s(): " message, __FUNCTION__, ##__VA_ARGS__)
#define NPASS(message, ...) printf("[+] %s(): " message, __FUNCTION__, ##__VA_ARGS__)
#define NINFO(message, ...) printf("[!] %s(): " message, __FUNCTION__, ##__VA_ARGS__)














#endif