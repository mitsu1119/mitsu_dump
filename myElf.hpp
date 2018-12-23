#include <iostream>
#include <fstream>
#include <elf.h>
#include <iomanip>

class myElf {
private:
    unsigned char *head;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
    Elf64_Phdr *phdr;

public:
    myElf(const char *fileName);
    ~myElf();

    bool isElf();
};
