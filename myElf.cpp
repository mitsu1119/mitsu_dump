#include "myElf.hpp"

myElf::myElf(const char *fileName) {
    std::ifstream ifs(fileName);
    if(ifs.fail()) {
        std::cerr << "Error: Failed to open this file." << std::endl;
        exit(1);
    } else {
        std::string s((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        this->head = new unsigned char[s.size()];
        s.copy((char *)this->head, s.size());

        this->ehdr = (Elf32_Ehdr *)this->head;
        this->shdr = (Elf32_Shdr *)(this->head + this->ehdr->e_shoff);
        this->phdr = (Elf32_Phdr *)(this->head + this->ehdr->e_phoff);

        ifs.close();

        if(!isElf()) {
            std::cerr << "The file is no ELF" << std::endl;
            exit(1);
        }

        // textセクションの位置把握
        Elf32_Shdr *shdrL = this->shdr;
        Elf32_Shdr *shstr = getShstrtab();
        char *sectionName;

        for(int i=0; i < this->ehdr->e_shnum; i++) {
            sectionName = (char *)(this->head + shstr->sh_offset + shdrL->sh_name);
            if(strcmp(sectionName, ".text")) {
                shdrL = (Elf32_Shdr *)((char *)shdrL + this->ehdr->e_shentsize);
                continue;
            }
            this->textOffset = shdrL->sh_addr;
            this->textSize = shdrL->sh_size;
            break;
        }

        // std::cout << ".text_offset:" << this->textOffset << ", .text_size:" << this->textSize << std::endl;
        // for(int i=0; i<s.size(); i++) std::cout << std::hex << std::setfill('0') << std::setw(2) << +this->head[i] << " ";
        textDisasm();
    }
}

myElf::~myElf() {
    delete[] this->head;
}

void myElf::dumpTextSection() {
    std::cout << ".text_offset:" << this->textOffset << ", .text_size:" << this->textSize << std::endl;
    for(int i = this->textOffset; i < this->textOffset + this->textSize; i++) std::cout << std::hex << std::setfill('0') << std::setw(2) << +this->head[i] << " ";
}

bool myElf::isElf() {
    if(this->ehdr->e_ident[EI_MAG0] == ELFMAG0 && this->ehdr->e_ident[EI_MAG1] == ELFMAG1 &&
        this->ehdr->e_ident[EI_MAG2] == ELFMAG2 && this->ehdr->e_ident[EI_MAG3] == ELFMAG3)
        return true;
    return false;
}

void myElf::textDisasm() {
    disasm(this->textOffset, this->textOffset + this->textSize - 1);
}

void myElf::disasm(int begin, int end) {
    for(int i = begin; i <= end; i++) {
        std::cout << opcodes[(int)this->head[i]] << std::endl;
    }
}
