/* Definitions for decoding the gaspard opcode table.
   Copyright (C) 2009-2021 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */

/* Form 1 instructions come in different flavors:

    Some have no arguments                          (gaspard_F1_NARG)
    Some only use the A operand                     (gaspard_F1_A)
    Some use A and B registers                      (gaspard_F1_AB)
    Some use A and consume a 4 byte immediate value (gaspard_F1_A4)
    Some use just a 4 byte immediate value          (gaspard_F1_4)
    Some use just a 4 byte memory address           (gaspard_F1_M)
    Some use B and an indirect A                    (gaspard_F1_AiB)
    Some use A and an indirect B                    (gaspard_F1_ABi)
    Some consume a 4 byte immediate value and use X (gaspard_F1_4A)
    Some use B and an indirect A plus 2 byte offset (gaspard_F1_AiB2)
    Some use A and an indirect B plus 2 byte offset (gaspard_F1_ABi2)

  Form 2 instructions also come in different flavors:

    Some have no arguments                          (gaspard_F2_NARG)
    Some use the A register and an 8-bit value      (gaspard_F2_A8V)

  Form 3 instructions also come in different flavors:

    Some have no arguments                          (gaspard_F3_NARG)
    Some have a 10-bit PC relative operand          (gaspard_F3_PCREL).  */

#define gaspard_F1_NARG 0x100
#define gaspard_F1_A    0x101
#define gaspard_F1_AB   0x102
/* #define gaspard_F1_ABC  0x103 */
#define gaspard_F1_A4   0x104
#define gaspard_F1_4    0x105
#define gaspard_F1_AiB  0x106
#define gaspard_F1_ABi  0x107
#define gaspard_F1_4A   0x108
#define gaspard_F1_AiB2 0x109
#define gaspard_F1_ABi2 0x10a
#define gaspard_F1_M    0x10b

#define gaspard_F2_NARG 0x200
#define gaspard_F2_A8V  0x201

#define gaspard_F3_NARG  0x300
#define gaspard_F3_PCREL 0x301

#define gaspard_BAD     0x400

typedef struct gaspard_opc_info_t
{
  short         opcode;
  unsigned      itype;
  const char *  name;
} gaspard_opc_info_t;

extern const gaspard_opc_info_t gaspard_form1_opc_info[128];
extern const gaspard_opc_info_t gaspard_form2_opc_info[4];
extern const gaspard_opc_info_t gaspard_form3_opc_info[16];



struct opcode_chiara{
  char *name;
  unsigned char opcode;
  unsigned char num_of_op;// le nombre d'op??randes max 3

  void (*handler)(struct opcode_chiara *s);

};

void or(struct opcode_chiara *s);
void xor(struct opcode_chiara *s);
void and(struct opcode_chiara *s);
void not(struct opcode_chiara *s);
void shfl(struct opcode_chiara *s);
void shfr(struct opcode_chiara *s);
void mult(struct opcode_chiara *s);
void add(struct opcode_chiara *s);
void addc(struct opcode_chiara *s);
void subc(struct opcode_chiara *s);
void sub(struct opcode_chiara *s);
void inc(struct opcode_chiara *s);
void dec(struct opcode_chiara *s);
void modul(struct opcode_chiara *s);
void div_(struct opcode_chiara *s);
void divs(struct opcode_chiara *s);
void cmp(struct opcode_chiara *s);
void disp(struct opcode_chiara *s);
void dispa(struct opcode_chiara *s);
void disp_imm_to_pointer(struct opcode_chiara *s);
void disp_pointer_to_imm(struct opcode_chiara *s);
void push(struct opcode_chiara *s);
void pop(struct opcode_chiara *s);
void prcfg(struct opcode_chiara *s);
void ret(struct opcode_chiara *s);
void syscall_(struct opcode_chiara *s);
void void_(struct opcode_chiara *s);
void calle(struct opcode_chiara *s);
void callz(struct opcode_chiara *s);
void callc(struct opcode_chiara *s);
void callo(struct opcode_chiara *s);
void callrz(struct opcode_chiara *s);
void callrc(struct opcode_chiara *s);
void callro(struct opcode_chiara *s);
void dispab(struct opcode_chiara *s);
void dispab_read(struct opcode_chiara *s);
void dispas_write(struct opcode_chiara *s);
void dispas_read(struct opcode_chiara *s);
void dispal_write(struct opcode_chiara *s);
void dispal_read(struct opcode_chiara *s);
