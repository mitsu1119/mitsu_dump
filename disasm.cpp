#include <iostream>
#include <string>

std::string opcodes[] {
    "add",    "add",   "add",   "add",   "add",    "add",    "push",   "pop",    "or",    "or",    "or",    "or",    "or",    "or",   "push",   "?",
    "adc",    "adc",   "adc",   "adc",   "adc",    "adc",    "push",   "pop",    "sbb",   "sbb",   "sbb",   "sbb",   "sbb",   "sbb",  "push",   "pop",
    "and",    "and",   "and",   "and",   "and",    "and",    "seg.ES", "daa",    "sub",   "sub",   "sub",   "sub",   "sub",   "sub",  "seg.CS", "das",
    "xor",    "xor",   "xor",   "xor",   "xor",    "xor",    "seg.SS", "aaa",    "cmp",   "cmp",   "cmp",   "cmp",   "cmp",   "cmp",  "seg.DS", "aas",
    "inc",    "inc",   "inc",   "inc",   "inc",    "inc",    "inc",    "inc",    "dec",   "dec",   "dec",   "dec",   "dec",   "dec",  "dec",    "dec",
    "push",   "push",  "push",  "push",  "push",   "push",   "push",   "push",   "pop",   "pop",   "pop",   "pop",   "pop",   "pop",  "pop",    "pop",
    "pusha",  "popa",  "bound", "arpl",  "seg.FS", "seg.GS", "o.size", "o.addr", "push",  "imul",  "push",  "imul",  "insb",  "ins",  "outsb",  "outs",
    "jcc",    "jcc",   "jcc",   "jcc",   "jcc",    "jcc",    "jcc",    "jcc",    "jcc",   "jcc",   "jcc",   "jcc",   "jcc",   "jcc",  "jcc",    "jcc",
    "?",      "?",     "?",     "?",     "test",   "test",   "xchg",   "xchg",   "mov",   "mov",   "mov",   "mov",   "mov",   "lea",  "mov",    "?",
    "xchg",   "xchg",  "xchg",  "xchg",  "xchg",   "xchg",   "xchg",   "xchg",   "cbw",   "cwd",   "call",  "fwait", "pushf", "popf", "sahf",   "lahf",
    "mov",    "mov",   "mov",   "mov",   "movsb",  "movs",   "cmpsb",  "cmps",   "test",  "test",  "stosb", "stos",  "lodsb", "lods", "scasb",  "scas",
    "mov",    "mov",   "mov",   "mov",   "mov",    "mov",    "mov",    "mov",    "mov",   "mov",   "mov",   "mov",   "mov",   "mov",  "mov",    "mov",
    "?",      "?",     "ret",   "les",   "lds",    "lds",    "?",      "?",      "enter", "leave", "ret",   "ret",   "int",   "int",  "into",   "iret",
    "?",      "?",     "?",     "?",     "aam",    "aad",    "salc",   "xlat",   "?",     "?",     "?",     "?",     "?",     "?",    "?",      "?",
    "loopne", "loope", "loop",  "jexcz", "in",     "in",     "out",    "out",    "call",  "jmp",   "jmp",   "jmp",   "in",    "in",   "out",    "out",
    "lock",   "icebp", "repne", "repe",  "hlt",    "cmc",    "?",      "?",      "clc",   "stc",   "cli",   "sti",   "cld",   "std",  "?",      "?"
};
