/* gaspard-opc.c -- Definitions for gaspard opcodes.
   Copyright (C) 2009-2021 Free Software Foundation, Inc.

   This file is part of the GNU opcodes library.

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this file; see the file COPYING.  If not, write to the
   Free Software Foundation, 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "sysdep.h"
#include "opcode/gaspard.h"



void or(struct opcode_chiara *s) {


}
void xor(struct opcode_chiara *s) {


}
void and(struct opcode_chiara *s) {


}
void not(struct opcode_chiara *s) {


}

void shfl(struct opcode_chiara *s) {


}

void shfr(struct opcode_chiara *s) {


}


void mult(struct opcode_chiara *s) {


}

void add(struct opcode_chiara *s) {


}

void addc(struct opcode_chiara *s) {


}

void subc(struct opcode_chiara *s) {


}

void sub(struct opcode_chiara *s) {


}

void inc(struct opcode_chiara *s) {


}

void dec(struct opcode_chiara *s) {


}
void modul(struct opcode_chiara *s) {


}


void div_(struct opcode_chiara *s) {


}

void divs(struct opcode_chiara *s) {


}

void cmp(struct opcode_chiara *s) {


}

void disp(struct opcode_chiara *s) {


}

void dispa(struct opcode_chiara *s) {


}
void disp_imm_to_pointer(struct opcode_chiara *s) {


}

void disp_pointer_to_imm(struct opcode_chiara *s) {


}

void push(struct opcode_chiara *s) {


}

void pop(struct opcode_chiara *s) {


}
void prcfg(struct opcode_chiara *s) {


}

void ret(struct opcode_chiara *s) {


}

void syscall_(struct opcode_chiara *s) {


}

void void_(struct opcode_chiara *s) {


}

void calle(struct opcode_chiara *s) {


}

void callz(struct opcode_chiara *s) {


}

void callc(struct opcode_chiara *s) {


}

void callo(struct opcode_chiara *s) {


}

void callrz(struct opcode_chiara *s) {


}
void callrc(struct opcode_chiara *s) {


}

void callro(struct opcode_chiara *s) {


}

void dispab(struct opcode_chiara *s) {


}

void dispab_read(struct opcode_chiara *s) {


}

void dispas_write(struct opcode_chiara *s) {


}

void dispas_read(struct opcode_chiara *s) {


}

void dispal_write(struct opcode_chiara *s) {


}

void dispal_read(struct opcode_chiara *s) {


}
// controler les valeurs des opcodes par rapport au livre 
struct opcode_chiara opcodes [] = {

  {"or",10,2,or},
  {"xor",8,2,xor},
  {"and",9,2,and},
  {"not",11,1,not},
  {"shfl",18,2,shfl},
  {"shfr",13,2,shfr},
  {"mult",7,2,mult},
  {"add",46,2,add},
  {"addc",26,2,addc},
  {"sub",5,2,sub},
  {"subc",27,2,subc},
  {"inc",4,1,inc},
  {"dec",153,1,dec},
  {"modul",25,2,modul},
  {"div",28,2,div_},
  {"divs",29,2,divs},
  {"cmp",16,2,cmp},
  {"disp",44,2,disp},
  {"dispa",3,2,dispa},
  {"dispa",30,2,disp_imm_to_pointer},
  {"dispa",31,2,disp_pointer_to_imm},
  {"push",35,1,push},
  {"pop",33,1,pop},
  {"prcfg",150,1,prcfg},
  {"ret",32,1,ret},
  {"syscall",36,1,syscall_},
  {"void",0,1,void_},
  {"calle",154,1,calle},
  {"callz",19,1,callz},
  {"callc",20,1,callc},
  {"callo",21,1,callo},
  {"callrz",22,1,callrz},
  {"callrc",23,1,callrc},
  {"callro",24,1,callro},
  {"dispab_write",112,1,dispab},
  {"dispab_read",111,1,dispab_read},
  {"dispas_write",40,1,dispas_write},
  {"dispas_read",41,1,dispas_read},
  {"dispal_write",45,1,dispal_write},
  {"dispal_read",47,1,dispal_read},

};















/* The gaspard processor's 16-bit instructions come in two forms:

  FORM 1 instructions start with a 0 bit...

    0oooooooaaaabbbb
    0              F

   ooooooo - form 1 opcode number
   aaaa    - operand A
   bbbb    - operand B

  FORM 2 instructions start with bits "10"...

    10ooaaaavvvvvvvv
    0              F

   oo       - form 2 opcode number
   aaaa     - operand A
   vvvvvvvv - 8-bit immediate value

  FORM 3 instructions start with a bits "11"...

    11oooovvvvvvvvvv
    0              F

   oooo         - form 3 opcode number
   vvvvvvvvvv   - 10-bit immediate value.  */

const gaspard_opc_info_t gaspard_form1_opc_info[128] =
  {
    { 0x00, gaspard_BAD,     "bad" },  /* Reserved as bad.  */
    { 0x01, gaspard_F1_A4,   "ldi.l" },
    { 0x02, gaspard_F1_AB,   "mov" },
    { 0x03, gaspard_F1_M,    "jsra" },
    { 0x04, gaspard_F1_NARG, "ret" },
    { 0x05, gaspard_F1_AB,   "add" },
    { 0x06, gaspard_F1_AB,   "push" },
    { 0x07, gaspard_F1_AB,   "pop" },
    { 0x08, gaspard_F1_A4,   "lda.l" },
    { 0x09, gaspard_F1_4A,   "sta.l" },
    { 0x0a, gaspard_F1_ABi,  "ld.l" },
    { 0x0b, gaspard_F1_AiB,  "st.l" },
    { 0x0c, gaspard_F1_ABi2, "ldo.l" },
    { 0x0d, gaspard_F1_AiB2, "sto.l" },
    { 0x0e, gaspard_F1_AB,   "cmp" },
    { 0x0f, gaspard_F1_NARG, "nop" },
    { 0x10, gaspard_F1_AB,   "sex.b" },
    { 0x11, gaspard_F1_AB,   "sex.s" },
    { 0x12, gaspard_F1_AB,   "zex.b" },
    { 0x13, gaspard_F1_AB,   "zex.s" },
    { 0x14, gaspard_F1_AB,   "umul.x" },
    { 0x15, gaspard_F1_AB,   "mul.x" },
    { 0x16, gaspard_BAD,     "bad" },
    { 0x17, gaspard_BAD,     "bad" },
    { 0x18, gaspard_BAD,     "bad" },
    { 0x19, gaspard_F1_A,    "jsr" },
    { 0x1a, gaspard_F1_M,    "jmpa" },
    { 0x1b, gaspard_F1_A4,   "ldi.b" },
    { 0x1c, gaspard_F1_ABi,  "ld.b" },
    { 0x1d, gaspard_F1_A4,   "lda.b" },
    { 0x1e, gaspard_F1_AiB,  "st.b" },
    { 0x1f, gaspard_F1_4A,   "sta.b" },
    { 0x20, gaspard_F1_A4,   "ldi.s" },
    { 0x21, gaspard_F1_ABi,  "ld.s" },
    { 0x22, gaspard_F1_A4,   "lda.s" },
    { 0x23, gaspard_F1_AiB,  "st.s" },
    { 0x24, gaspard_F1_4A,   "sta.s" },
    { 0x25, gaspard_F1_A,    "jmp" },
    { 0x26, gaspard_F1_AB,   "and" },
    { 0x27, gaspard_F1_AB,   "lshr" },
    { 0x28, gaspard_F1_AB,   "ashl" },
    { 0x29, gaspard_F1_AB,   "sub" },
    { 0x2a, gaspard_F1_AB,   "neg" },
    { 0x2b, gaspard_F1_AB,   "or" },
    { 0x2c, gaspard_F1_AB,   "not" },
    { 0x2d, gaspard_F1_AB,   "ashr" },
    { 0x2e, gaspard_F1_AB,   "xor" },
    { 0x2f, gaspard_F1_AB,   "mul" },
    { 0x30, gaspard_F1_4,    "swi" },
    { 0x31, gaspard_F1_AB,   "div" },
    { 0x32, gaspard_F1_AB,   "udiv" },
    { 0x33, gaspard_F1_AB,   "mod" },
    { 0x34, gaspard_F1_AB,   "umod" },
    { 0x35, gaspard_F1_NARG, "brk" },
    { 0x36, gaspard_F1_ABi2, "ldo.b" },
    { 0x37, gaspard_F1_AiB2, "sto.b" },
    { 0x38, gaspard_F1_ABi2, "ldo.s" },
    { 0x39, gaspard_F1_AiB2, "sto.s" },
    { 0x3a, gaspard_BAD,     "bad" },
    { 0x3b, gaspard_BAD,     "bad" },
    { 0x3c, gaspard_BAD,     "bad" },
    { 0x3d, gaspard_BAD,     "bad" },
    { 0x3e, gaspard_BAD,     "bad" },
    { 0x3f, gaspard_BAD,     "bad" },
    { 0x40, gaspard_BAD,     "bad" },
    { 0x41, gaspard_BAD,     "bad" },
    { 0x42, gaspard_BAD,     "bad" },
    { 0x43, gaspard_BAD,     "bad" },
    { 0x44, gaspard_BAD,     "bad" },
    { 0x45, gaspard_BAD,     "bad" },
    { 0x46, gaspard_BAD,     "bad" },
    { 0x47, gaspard_BAD,     "bad" },
    { 0x48, gaspard_BAD,     "bad" },
    { 0x49, gaspard_BAD,     "bad" },
    { 0x4a, gaspard_BAD,     "bad" },
    { 0x4b, gaspard_BAD,     "bad" },
    { 0x4c, gaspard_BAD,     "bad" },
    { 0x4d, gaspard_BAD,     "bad" },
    { 0x4e, gaspard_BAD,     "bad" },
    { 0x4f, gaspard_BAD,     "bad" },
    { 0x50, gaspard_BAD,     "bad" },
    { 0x51, gaspard_BAD,     "bad" },
    { 0x52, gaspard_BAD,     "bad" },
    { 0x53, gaspard_BAD,     "bad" },
    { 0x54, gaspard_BAD,     "bad" },
    { 0x55, gaspard_BAD,     "bad" },
    { 0x56, gaspard_BAD,     "bad" },
    { 0x57, gaspard_BAD,     "bad" },
    { 0x58, gaspard_BAD,     "bad" },
    { 0x59, gaspard_BAD,     "bad" },
    { 0x5a, gaspard_BAD,     "bad" },
    { 0x5b, gaspard_BAD,     "bad" },
    { 0x5c, gaspard_BAD,     "bad" },
    { 0x5d, gaspard_BAD,     "bad" },
    { 0x5e, gaspard_BAD,     "bad" },
    { 0x5f, gaspard_BAD,     "bad" },
    { 0x60, gaspard_BAD,     "bad" },
    { 0x61, gaspard_BAD,     "bad" },
    { 0x62, gaspard_BAD,     "bad" },
    { 0x63, gaspard_BAD,     "bad" },
    { 0x64, gaspard_BAD,     "bad" },
    { 0x65, gaspard_BAD,     "bad" },
    { 0x66, gaspard_BAD,     "bad" },
    { 0x67, gaspard_BAD,     "bad" },
    { 0x68, gaspard_BAD,     "bad" },
    { 0x69, gaspard_BAD,     "bad" },
    { 0x6a, gaspard_BAD,     "bad" },
    { 0x6b, gaspard_BAD,     "bad" },
    { 0x6c, gaspard_BAD,     "bad" },
    { 0x6d, gaspard_BAD,     "bad" },
    { 0x6e, gaspard_BAD,     "bad" },
    { 0x6f, gaspard_BAD,     "bad" },
    { 0x70, gaspard_BAD,     "bad" },
    { 0x71, gaspard_BAD,     "bad" },
    { 0x72, gaspard_BAD,     "bad" },
    { 0x73, gaspard_BAD,     "bad" },
    { 0x74, gaspard_BAD,     "bad" },
    { 0x75, gaspard_BAD,     "bad" },
    { 0x76, gaspard_BAD,     "bad" },
    { 0x77, gaspard_BAD,     "bad" },
    { 0x78, gaspard_BAD,     "bad" },
    { 0x79, gaspard_BAD,     "bad" },
    { 0x7a, gaspard_BAD,     "bad" },
    { 0x7b, gaspard_BAD,     "bad" },
    { 0x7c, gaspard_BAD,     "bad" },
    { 0x7d, gaspard_BAD,     "bad" },
    { 0x7e, gaspard_BAD,     "bad" },
    { 0x7f, gaspard_BAD,     "bad" }
  };

const gaspard_opc_info_t gaspard_form2_opc_info[4] =
  {
    { 0x00, gaspard_F2_A8V,  "inc" },
    { 0x01, gaspard_F2_A8V,  "dec" },
    { 0x02, gaspard_F2_A8V,  "gsr" },
    { 0x03, gaspard_F2_A8V,  "ssr" }
  };

const gaspard_opc_info_t gaspard_form3_opc_info[16] =
  {
    { 0x00, gaspard_F3_PCREL,"beq" },
    { 0x01, gaspard_F3_PCREL,"bne" },
    { 0x02, gaspard_F3_PCREL,"blt" },
    { 0x03, gaspard_F3_PCREL,"bgt" },
    { 0x04, gaspard_F3_PCREL,"bltu" },
    { 0x05, gaspard_F3_PCREL,"bgtu" },
    { 0x06, gaspard_F3_PCREL,"bge" },
    { 0x07, gaspard_F3_PCREL,"ble" },
    { 0x08, gaspard_F3_PCREL,"bgeu" },
    { 0x09, gaspard_F3_PCREL,"bleu" },
    { 0x0a, gaspard_BAD,     "bad" },
    { 0x0b, gaspard_BAD,     "bad" },
    { 0x0c, gaspard_BAD,     "bad" },
    { 0x0d, gaspard_BAD,     "bad" },
    { 0x0e, gaspard_BAD,     "bad" },
    { 0x0f, gaspard_BAD,     "bad" }  /* Reserved as bad.  */
  };




