#include <iostream>
#include <fstream>
#include <elf.h>
#include <iomanip>
#include <cstring>
#include <vector>
#include <string>

extern std::string opcodes[];

class myElf {
private:
    unsigned char *head;
    Elf32_Ehdr *ehdr;
    Elf32_Shdr *shdr;
    Elf32_Phdr *phdr;

    int textOffset;
    int textSize;

    // .shstrtab セクションの所得
    Elf32_Shdr *getShstrtab() {
        return (Elf32_Shdr *)((char *)this->shdr + this->ehdr->e_shentsize * this->ehdr->e_shstrndx);
    }

    void dumpTextSection();

    void disasm(int begin, int end);

public:
    myElf(const char *fileName);
    ~myElf();

    void textDisasm();

    bool isElf();
};
