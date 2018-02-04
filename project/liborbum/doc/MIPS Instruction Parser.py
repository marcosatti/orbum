import sys
import os

INSTRUCTION_VALUES = [0xA8C30003]

class Instruction:
    PRINT_IN_HEX = True

    def __init__(self, value):
        self.value = value

    def __str__(self):
        if self.PRINT_IN_HEX:
            return f'{hex(self.value)}:' + os.linesep + \
                f'    opcode : {hex(self.opcode())}' + os.linesep + \
                f'    rs     : {hex(self.rs())}' + os.linesep + \
                f'    rt     : {hex(self.rt())}' + os.linesep + \
                f'    rd     : {hex(self.rd())}' + os.linesep + \
                f'    shamt  : {hex(self.shamt())}' + os.linesep + \
                f'    funct  : {hex(self.funct())}' + os.linesep + \
                f'    imm    : {hex(self.imm())}' + os.linesep + \
                f'    addr   : {hex(self.addr())}' + os.linesep
        else:
            return f'{hex(self.value)}:' + os.linesep + \
                f'    opcode : {self.opcode()}' + os.linesep + \
                f'    rs     : {self.rs()}' + os.linesep + \
                f'    rt     : {self.rt()}' + os.linesep + \
                f'    rd     : {self.rd()}' + os.linesep + \
                f'    shamt  : {self.shamt()}' + os.linesep + \
                f'    funct  : {self.funct()}' + os.linesep + \
                f'    imm    : {self.imm()}' + os.linesep + \
                f'    addr   : {self.addr()}' + os.linesep

    def opcode(self):
        return (self.value >> 26) & ((1 << 6) - 1)

    def rs(self):
        return (self.value >> 21) & ((1 << 5) - 1)

    def rt(self):
        return (self.value >> 16) & ((1 << 5) - 1)

    def rd(self):
        return (self.value >> 11) & ((1 << 5) - 1)

    def shamt(self):
        return (self.value >> 6) & ((1 << 5) - 1)

    def funct(self):
        return (self.value >> 0) & ((1 << 6) - 1)

    def imm(self):
        return (self.value >> 0) & ((1 << 16) - 1)

    def addr(self):
        return (self.value >> 0) & ((1 << 26) - 1)

if __name__ == '__main__':
    if len(sys.argv) >= 2:
        INSTRUCTION_VALUES = []
        for i in sys.argv[2:]:
            INSTRUCTION_VALUES += [int(i, 16)]
    
    for i in INSTRUCTION_VALUES:
        print(Instruction(i))
