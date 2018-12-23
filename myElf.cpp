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

        this->ehdr = (Elf64_Ehdr *)this->head;
        this->shdr = (Elf64_Shdr *)(this->head + this->ehdr->e_shoff);
        this->phdr = (Elf64_Phdr *)(this->head + this->ehdr->e_phoff);

        ifs.close();

        if(!isElf()) {
            std::cerr << "The file is no ELF" << std::endl;
            exit(1);
        }
        // for(int i=0; i<s.size(); i++) std::cout << std::hex << std::setfill('0') << std::setw(2) << +this->head[i] << " ";
    }
}

myElf::~myElf() {
    delete[] this->head;
}

bool myElf::isElf() {
    if(this->ehdr->e_ident[EI_MAG0] == ELFMAG0 && this->ehdr->e_ident[EI_MAG1] == ELFMAG1 &&
        this->ehdr->e_ident[EI_MAG2] == ELFMAG2 && this->ehdr->e_ident[EI_MAG3] == ELFMAG3)
        return true;
    return false;
}
