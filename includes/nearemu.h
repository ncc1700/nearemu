#ifndef NEAREMU_H_INCLUDED
#define NEAREMU_H_INCLUDED

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define DEBUG_FAIL(message, ...) printf("[-] %s(): " message, __FUNCTION__, ##__VA_ARGS__)
#define DEBUG_PASS(message, ...) printf("[+] %s(): " message, __FUNCTION__, ##__VA_ARGS__)
#define DEBUG_INFO(message, ...) printf("[!] %s(): " message, __FUNCTION__, ##__VA_ARGS__)














#endif