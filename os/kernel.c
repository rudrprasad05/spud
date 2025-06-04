// kernel.c
void print(const char *str) {
    volatile char *video = (volatile char*) 0xB8000;
    while (*str) {
        *video++ = *str++;
        *video++ = 0x07;
    }
}

void main() {
    print("Hello, World from Kernel!");
    while (1);
}
