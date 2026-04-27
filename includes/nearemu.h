#ifndef NEAREMU_H_INCLUDED
#define NEAREMU_H_INCLUDED

#include <stdio.h>
#include <stdint.h>


#define DEBUG_FAIL(message, ...) printf("[-] %s(): " message, __FUNCTION__, ##__VA_ARGS__)
#define DEBUG_PASS(message, ...) printf("[+] %s(): " message, __FUNCTION__, ##__VA_ARGS__)
#define DEBUG_INFO(message, ...) printf("[!] %s(): " message, __FUNCTION__, ##__VA_ARGS__)














#endif