/* Disassemble gaspard instructions.
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
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "sysdep.h"
#include <stdio.h>

#define STATIC_TABLE
#define DEFINE_TABLE

#include "opcode/gaspard.h"
#include "disassemble.h"

static fprintf_ftype fpr;
static void *stream;

/* Macros to extract operands from the instruction word.  */
#define OP_A(i) ((i >> 4) & 0xf)
#define OP_B(i) (i & 0xf)
#define INST2OFFSET(o) (((((o) & 0x3ff) ^ 0x200) - 0x200) * 2)

static const char * reg_names[16] =
  { "$fp", "$sp", "$r0", "$r1", "$r2", "$r3", "$r4", "$r5",
    "$r6", "$r7", "$r8", "$r9", "$r10", "$r11", "$r12", "$r13" };


extern const struct opcode_chiara opcodes [];

void print_gpr_fpr(struct disassemble_info *info,bfd_byte  gpr_gpr) {

    if(gpr_gpr > 31) {
        fpr(stream,"FPR%d",gpr_gpr+31);
        
    } else {
        fpr(stream,"GPR%d",gpr_gpr);

    }
    
    
}
int
print_insn_gaspard (bfd_vma addr, struct disassemble_info * info)
{

int length = 2;
    int status;
    stream = info->stream;
    bfd_byte buffer[4];
  fpr = info->fprintf_func;

    if ((status = info->read_memory_func (addr, buffer, 3, info))) {
        info->memory_error_func (status, addr, info);
        return 1;
    }
      switch(buffer[0]) {
          case 36: {
              // syscall
              
              
              return 2;
          }
          case 11: {
              
              // not
              
              return 2;
          }
          case 4: {
              // inc
              
              return 2;
          }
          case 34: {
              // dec
              
              return 2;
          }
          case 35: {
              // push
              
              return 2;
          }
          case 33: {
              // pop
              
              return 2;
          }
          case 150: {
              // prcfg
              bfd_byte buff_tmp[10];
              if ((status = info->read_memory_func (addr, buff_tmp, 10, info))) {
                  info->memory_error_func (status, addr, info);
                  return -1;
              }
              
              fpr(stream,"prcfg %d,",buff_tmp[1]);
              unsigned long long data_tmp = (unsigned long long)buff_tmp[2] |  (unsigned long long) buff_tmp[3] << 8 | (unsigned long long)  buff_tmp[4] << 16 |  (unsigned long long) buff_tmp[5] << 24 | (unsigned long long) buff_tmp[6] << 32 | (unsigned long long) buff_tmp[7] << 40 | (unsigned long long) buff_tmp[8] << 48 | (unsigned long long) buff_tmp[9] << 56;
              fpr(stream,"0x%lx",data_tmp);

              
              return 10;
          }
          case 32: {
              // ret
              return 1;
          }
          case 0:{
              fpr(stream,"void","");

              
              return 1;
          }
          case 18: {
              
              // calle
              
              return 9;
          }
          case 19: {
              
              // callz
              
              return 9;
          }
          case 20: {
              
              // callc
              
              return 9;
          }
          case 21: {
              
              // callo
              
              return 9;
          }
          case 22: {
              
              // callrz
              
              return 9;
          }
          case 23: {
              
              // callrc
              
              return 9;
          }
          case 24: {
              
              // callro
              
              return 9;
          }
        default: {
            for(int x=  0;x<39;x++) {
                
                if(*buffer == opcodes[x].opcode) {
                    
                  
                    
                    
                    fpr(stream,"%s ",opcodes[x].name);
                    print_gpr_fpr(info,buffer[1]);
                    fpr(stream,"%s",",");

                    print_gpr_fpr(info,buffer[2]);
                    fpr(stream,"%s","\n");

                    return 3;
                }
            }
          
            return 3;
    }
    
    
    
    return 3;

}
}
int
pr2int_insn_gaspard (bfd_vma addr, struct disassemble_info * info)
{
  int length = 2;
  int status;
  stream = info->stream;
  const gaspard_opc_info_t * opcode;
  bfd_byte buffer[4];
  unsigned short iword;
  fpr = info->fprintf_func;

  if ((status = info->read_memory_func (addr, buffer, 2, info)))
    goto fail;


    
  return length;

 fail:
  info->memory_error_func (status, addr, info);
  return -1;
}
