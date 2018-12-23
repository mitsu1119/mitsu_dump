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
        dumpTextSection();
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

const char *sectionType2str(int sectionType) {
    switch(sectionType) {
    case SHT_NULL:      return "NULL";
    case SHT_PROGBITS:  return "PROGBITS";
    case SHT_SYMTAB:    return "SYMTAB";
    case SHT_STRTAB:    return "STRTAB";
    case SHT_RELA:      return "RELA";
    case SHT_HASH:      return "HASH";
    case SHT_DYNAMIC:   return "DYNAMIC";
    case SHT_NOTE:      return "NOTE";
    case SHT_NOBITS:    return "NOBITS";
    case SHT_REL:       return "REL";
    case SHT_SHLIB:     return "SHLIB";
    case SHT_DYNSYM:    return "DYNSYM";
    case SHT_INIT_ARRAY:return "INIT_ARRAY";
    case SHT_FINI_ARRAY:return "FINI_ARRAY";
    case SHT_GNU_HASH:  return "GNU_HASH";
    case SHT_GNU_verdef:return "GNU_VERDEF";
    case SHT_GNU_verneed:return "GNU_VERNEED";
    case SHT_GNU_versym:return "GNU_VERSYM";
    default:            return "Unknown...";
    }
}
