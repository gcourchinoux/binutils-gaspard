/* tc-gaspard.c -- Assemble code for gaspard
   Copyright (C) 2009-2021 Free Software Foundation, Inc.

   This file is part of GAS, the GNU Assembler.

   GAS is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GAS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GAS; see the file COPYING.  If not, write to
   the Free Software Foundation, 51 Franklin Street - Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* Contributed by Anthony Green <green@gaspardlogic.com>.  */

#include "as.h"
#include "safe-ctype.h"
#include "opcode/gaspard.h"
#include "elf/gaspard.h"

extern const gaspard_opc_info_t gaspard_opc_info[128];
extern const struct opcode_chiara opcodes[];  // 39 opcodes 


const char comment_chars[]        = "#";
const char line_separator_chars[] = ";";
const char line_comment_chars[]   = "#";

static int pending_reloc;
static htab_t opcode_hash_control;

const pseudo_typeS md_pseudo_table[] =
{
  {0, 0, 0}
};

const char FLT_CHARS[] = "rRsSfFdDxXpP";
const char EXP_CHARS[] = "eE";

static valueT md_chars_to_number (char * buf, int n);

/* Byte order.  */
extern int target_big_endian;

void
md_operand (expressionS *op __attribute__((unused)))
{
  /* Empty for now. */
}

/* This function is called once, at assembler startup time.  It sets
   up the hash table with all the opcodes in it, and also initializes
   some aliases for compatibility with other assemblers.  */

void
md_begin (void)
{
  int count;
  const gaspard_opc_info_t *opcode;
  opcode_hash_control = str_htab_create ();

  /* Insert names into hash table.  */
  for (count = 0, opcode = gaspard_form1_opc_info; count++ < 64; opcode++)
    str_hash_insert (opcode_hash_control, opcode->name, opcode, 0);

  for (count = 0, opcode = gaspard_form2_opc_info; count++ < 4; opcode++)
    str_hash_insert (opcode_hash_control, opcode->name, opcode, 0);

  for (count = 0, opcode = gaspard_form3_opc_info; count++ < 10; opcode++)
    str_hash_insert (opcode_hash_control, opcode->name, opcode, 0);

  bfd_set_arch_mach (stdoutput, TARGET_ARCH, 0);
}

/* Parse an expression and then restore the input line pointer.  */

static char *
parse_exp_save_ilp (char *s, expressionS *op)
{
  char *save = input_line_pointer;

  input_line_pointer = s;
  expression (op);
  s = input_line_pointer;
  input_line_pointer = save;
  return s;
}

static int
parse_register_operand (char **ptr)
{
  int reg;
  char *s = *ptr;

  if (*s != '$')
    {
      as_bad (_("expecting register"));
      ignore_rest_of_line ();
      return -1;
    }
  if (s[1] == 'f' && s[2] == 'p')
    {
      *ptr += 3;
      return 0;
    }
  if (s[1] == 's' && s[2] == 'p')
    {
      *ptr += 3;
      return 1;
    }
  if (s[1] == 'r')
    {
      reg = s[2] - '0';
      if ((reg < 0) || (reg > 9))
	{
	  as_bad (_("illegal register number"));
	  ignore_rest_of_line ();
	  return -1;
	}
      if (reg == 1)
	{
	  int r2 = s[3] - '0';
	  if ((r2 >= 0) && (r2 <= 3))
	    {
	      reg = 10 + r2;
	      *ptr += 1;
	    }
	}
    }
  else
    {
      as_bad (_("illegal register number"));
      ignore_rest_of_line ();
      return -1;
    }

  *ptr += 3;

  return reg + 2;
}
//todo : faire les hexas et les binaires
unsigned long long gaspard_atol(char* str){
    return atol(str);
}
unsigned char gaspard_atol_8bits(char *str) {
    
    
    return atol(str);
    
}
void rm_spaces(char* s) {
    char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}

unsigned char gpr_fpr(char *argument) {
    rm_spaces(argument);
	if(strcmp(argument,"GPR0") == 0) {
		//~ return 34;
		return 0;
		} else if(strcmp(argument,"GPR1") == 0) {
			return 1;
			}
		 else if(strcmp(argument,"GPR2") == 0) {
			return 2;
			}
		 else if(strcmp(argument,"GPR3") == 0) {
			return 3;
			}
		 else if(strcmp(argument,"GPR4") == 0) {
			return 4;
			}
		 else if(strcmp(argument,"GPR5") == 0) {
			return 5;
			}
		 else if(strcmp(argument,"GPR6") == 0) {
			return 6;
			}
		 else if(strcmp(argument,"GPR7") == 0) {
			return 7;
			}
		 else if(strcmp(argument,"GPR8") == 0) {
			return 8;
			}
		 else if(strcmp(argument,"GPR9") == 0) {
			return 9;
			}
		 else if(strcmp(argument,"GPR10") == 0) {
			return 10;
			}
		 else if(strcmp(argument,"GPR11") == 0) {
			return 11;
			}
		 else if(strcmp(argument,"GPR12") == 0) {
			return 12;
			}
		 else if(strcmp(argument,"GPR13") == 0) {
			return 13;
			}
		 else if(strcmp(argument,"GPR14") == 0) {
			return 14;
			}
		 else if(strcmp(argument,"GPR15") == 0) {
			return 15;
			}
		 else if(strcmp(argument,"GPR16") == 0) {
			return 16;
			}
		 else if(strcmp(argument,"GPR17") == 0) {
			return 17;
			}
		 else if(strcmp(argument,"GPR18") == 0) {
			return 18;
			}
		 else if(strcmp(argument,"GPR19") == 0) {
			return 19;
			}
		 else if(strcmp(argument,"GPR20") == 0) {
			return 20;
			}
		 else if(strcmp(argument,"GPR21") == 0) {
			return 21;
			}
		 else if(strcmp(argument,"GPR22") == 0) {
			return 22;
			}
		 else if(strcmp(argument,"GPR23") == 0) {
			return 23;
			}
		 else if(strcmp(argument,"GPR24") == 0) {
			return 24;
			}
		 else if(strcmp(argument,"GPR25") == 0) {
			return 25;
			}
		 else if(strcmp(argument,"GPR26") == 0) {
			return 26;
			}
		 else if(strcmp(argument,"GPR27") == 0) {
			return 27;
			}
		 else if(strcmp(argument,"GPR28") == 0) {
			return 28;
			}
		 else if(strcmp(argument,"GPR29") == 0) {
			return 29;
			}
		 else if(strcmp(argument,"GPR30") == 0) {
			return 30;
			}
		 else if(strcmp(argument,"GPR31") == 0) {
			return 31;
			}   else if(strcmp(argument,"FPR0") == 0)   { 
 return 32; 
 } 
  else if(strcmp(argument,"FPR1") == 0)   { 
 return 33; 
 } 
  else if(strcmp(argument,"FPR2") == 0)   { 
 return 34; 
 } 
  else if(strcmp(argument,"FPR3") == 0)   { 
 return 35; 
 } 
  else if(strcmp(argument,"FPR4") == 0)   { 
 return 36; 
 } 
  else if(strcmp(argument,"FPR5") == 0)   { 
 return 37; 
 } 
  else if(strcmp(argument,"FPR6") == 0)   { 
 return 38; 
 } 
  else if(strcmp(argument,"FPR7") == 0)   { 
 return 39; 
 } 
  else if(strcmp(argument,"FPR8") == 0)   { 
 return 40; 
 } 
  else if(strcmp(argument,"FPR9") == 0)   { 
 return 41; 
 } 
  else if(strcmp(argument,"FPR10") == 0)   { 
 return 42; 
 } 
  else if(strcmp(argument,"FPR11") == 0)   { 
 return 43; 
 } 
  else if(strcmp(argument,"FPR12") == 0)   { 
 return 44; 
 } 
  else if(strcmp(argument,"FPR13") == 0)   { 
 return 45; 
 } 
  else if(strcmp(argument,"FPR14") == 0)   { 
 return 46; 
 } 
  else if(strcmp(argument,"FPR15") == 0)   { 
 return 47; 
 } 
  else if(strcmp(argument,"FPR16") == 0)   { 
 return 48; 
 } 
  else if(strcmp(argument,"FPR17") == 0)   { 
 return 49; 
 } 
  else if(strcmp(argument,"FPR18") == 0)   { 
 return 50; 
 } 
  else if(strcmp(argument,"FPR19") == 0)   { 
 return 51; 
 } 
  else if(strcmp(argument,"FPR20") == 0)   { 
 return 52; 
 } 
  else if(strcmp(argument,"FPR21") == 0)   { 
 return 53; 
 } 
  else if(strcmp(argument,"FPR22") == 0)   { 
 return 54; 
 } 
  else if(strcmp(argument,"FPR23") == 0)   { 
 return 55; 
 } 
  else if(strcmp(argument,"FPR24") == 0)   { 
 return 56; 
 } 
  else if(strcmp(argument,"FPR25") == 0)   { 
 return 57; 
 } 
  else if(strcmp(argument,"FPR26") == 0)   { 
 return 58; 
 } 
  else if(strcmp(argument,"FPR27") == 0)   { 
 return 59; 
 } 
  else if(strcmp(argument,"FPR28") == 0)   { 
 return 60; 
 } 
  else if(strcmp(argument,"FPR29") == 0)   { 
 return 61; 
 } 
  else if(strcmp(argument,"FPR30") == 0)   { 
 return 62; 
 } 
  else if(strcmp(argument,"FPR31") == 0)   { 
 return 63; 
 } 
		 else if(strcmp(argument,"RETGPR") == 0) {
			return 32;
			} else {
			
				return 254;
				}
	
	
	}
char * build_argv(char *str ) {

int status;
  char *final = malloc(5);
  
  while(1) {
    if(str[status] == ',' || str[status] == '\n' || str[status] == '\0') {
      final[status] == '\0';
      break;
    } 

      final[status] = str[status];


    status++;
  }

return final;


}
char *build_instruction(char *str) {

int status;
  char *final = malloc(5);
  
  while(str[status] != ' ') {


      final[status] = str[status];


    status++;
  }

return final;
}
void
md_assemble (char *str)


{
    unsigned char *output;
    unsigned char iword;
    

while(*str != '\0') {

    char * instr = build_instruction(str);
    printf("instr %s \n",instr);
    str+= strlen(instr);

    printf("str %s \n",str);

            bool ok =false;
struct opcode_chiara tmp ;
      for(int x =0;x<39;x++) {

// parcourir les instructions 


      tmp = opcodes[x]; 


        if(strcmp(tmp.name,instr) == 0) {
            ok = true;
            break;


        }        
      }
        if(ok == true) {
            // nosu avons trouvé l'opcode incrementer ! 

                unsigned char op  = tmp.opcode;


            if(op == 36) {
                // syscall

                output = frag_more(2);
                output[0] = tmp.opcode;
                unsigned char *gpr1 = build_argv(str);
                str+= strlen(gpr1);
                output[1] = gaspard_atol_8bits(gpr1) ;
           //bfd_getl16     md_number_to_chars (output, 0, 2);

            } else if(op == 11) {
                // not
                output = frag_more(2);
                output[0] = tmp.opcode;
                unsigned char *gpr1 = build_argv(str);
                str+= strlen(gpr1);
                unsigned char gpr1_final = gpr_fpr(gpr1);
                output[1] = gpr1_final ;
             //   md_number_to_chars (output, 0, 2);

            } else if(op == 4) {
                // inc
                output = frag_more(2);
                output[0] = tmp.opcode;
                unsigned char *gpr1 = build_argv(str);
                str+= strlen(gpr1);
           unsigned      char gpr1_final = gpr_fpr(gpr1);
                output[1] = gpr1_final ;
               // md_number_to_chars (output, 0, 2);

            } else if(op == 34) {
                // dec
                output = frag_more(2);
                output[0] = tmp.opcode;
                unsigned char *gpr1 = build_argv(str);
                str+= strlen(gpr1);
               unsigned char gpr1_final = gpr_fpr(gpr1);
                output[1] = gpr1_final ;
               // md_number_to_chars (output, 0, 2);

            } else if(op == 35) {
                // push
                output = frag_more(2);
                output[0] = tmp.opcode;
                unsigned char *gpr1 = build_argv(str);
                str+= strlen(gpr1);
               unsigned char gpr1_final = gpr_fpr(gpr1);
                output[1] = gpr1_final ;
               // md_number_to_chars (output, 0, 2);

            } else if(op == 33) {
                // pop
                output = frag_more(2);
                output[0] = tmp.opcode;
                unsigned char *gpr1 = build_argv(str);
                str+= strlen(gpr1);
                unsigned char gpr1_final = gpr_fpr(gpr1);
                output[1] = gpr1_final ;
             //   md_number_to_chars (output, 0, 2);

            } else if(op == 150) {
                // prcfg
                
                output = frag_more(10);
                output[0] = tmp.opcode; // 150
                
                unsigned char *mode = build_argv(str);
                  printf("mode  %s \n",mode);

                str+= strlen(mode);
                if(*str == ',') {
                  str++;
                }
               
                unsigned char *adress = build_argv(str);
               
                str+= strlen(adress);
                if(gaspard_atol_8bits(mode) > 3) {
                    
                    as_bad(_("prcfg must have operand between 1 and 3"));
                }
                output[1] = gaspard_atol_8bits(mode);
                unsigned long long number = gaspard_atol(adress);

                output[2] = number ;
                output[3] = number << 8;
                output[4] = number << 16;
                output[5] = number << 24;
                output[6] = number << 32;
                output[7] = number << 40;
                output[8] = number << 48;
                output[9] = number << 56;
                
            } else if(op == 32) {
                // ret
                output = frag_more(1);
                output[0] = tmp.opcode;
             //   md_number_to_chars (output, 0, 1);
            } else if(op == 0) {
                // void
                output = frag_more(1);
                output[0] = tmp.opcode;
              //  md_number_to_chars (output, 0, 1);

            } else if(op == 18) {
                // calle
                output = frag_more(9);
                output[0] = tmp.opcode;
                unsigned char *nombre = build_argv(str);
                str+= strlen(nombre);
                unsigned long long number = gaspard_atol(nombre);
                output[1] = number;
                output[2] = number << 8;
                output[3] = number << 16;
                output[4] = number << 24;
                output[5] = number << 32;
                output[6] = number << 40;
                output[7] = number << 48;
                output[8] = number << 56;
                output[9] = number << 64;
               // md_number_to_chars (output, 0, 9);

                
            }  else if(op == 19) {
                // callz
                output = frag_more(9);
                output[0] = tmp.opcode;
                unsigned char *nombre = build_argv(str);
                str+= strlen(nombre);
                unsigned long long number = gaspard_atol(nombre);
                output[1] = number;
                output[2] = number << 8;
                output[3] = number << 16;
                output[4] = number << 24;
                output[5] = number << 32;
                output[6] = number << 40;
                output[7] = number << 48;
                output[8] = number << 56;
                output[9] = number << 64;
             //   md_number_to_chars (output, 0, 9);

            }  else if(op == 20) {
                // callc
                output = frag_more(9);
                output[0] = tmp.opcode;
                unsigned char *nombre = build_argv(str);
                str+= strlen(nombre);
                unsigned long long number = gaspard_atol(nombre);
                output[1] = number;
                output[2] = number << 8;
                output[3] = number << 16;
                output[4] = number << 24;
                output[5] = number << 32;
                output[6] = number << 40;
                output[7] = number << 48;
                output[8] = number << 56;
                output[9] = number << 64;
              //  md_number_to_chars (output, 0, 9);

            }  else if(op == 21) {
                // callo
                output = frag_more(9);
                output[0] = tmp.opcode;
                unsigned char *nombre = build_argv(str);
                str+= strlen(nombre);
                unsigned long long number = gaspard_atol(nombre);
                output[1] = number;
                output[2] = number << 8;
                output[3] = number << 16;
                output[4] = number << 24;
                output[5] = number << 32;
                output[6] = number << 40;
                output[7] = number << 48;
                output[8] = number << 56;
                output[9] = number << 64;
              //  md_number_to_chars (output, 0, 9);

            }  else if(op == 22) {
                // callrz
                output = frag_more(9);
                output[0] = tmp.opcode;
                unsigned char *nombre = build_argv(str);
                str+= strlen(nombre);
                unsigned long long number = gaspard_atol(nombre);
                output[1] = number;
                output[2] = number << 8;
                output[3] = number << 16;
                output[4] = number << 24;
                output[5] = number << 32;
                output[6] = number << 40;
                output[7] = number << 48;
                output[8] = number << 56;
                output[9] = number << 64;
                //md_number_to_chars (output, 0, 9);

            }  else if(op == 23) {
                // callrc
                output = frag_more(9);
                output[0] = tmp.opcode;
                unsigned char *nombre = build_argv(str);
                str+= strlen(nombre);
                unsigned long long number = gaspard_atol(nombre);
                output[1] = number;
                output[2] = number << 8;
                output[3] = number << 16;
                output[4] = number << 24;
                output[5] = number << 32;
                output[6] = number << 40;
                output[7] = number << 48;
                output[8] = number << 56;
                output[9] = number << 64;
               // md_number_to_chars (output, 0, 9);

            }  else if(op == 24) {
                // callro
                output = frag_more(9);
                output[0] = tmp.opcode;
                unsigned char *nombre = build_argv(str);
                str+= strlen(nombre);
                unsigned long long number = gaspard_atol(nombre);
                output[1] = number;
                output[2] = number << 8;
                output[3] = number << 16;
                output[4] = number << 24;
                output[5] = number << 32;
                output[6] = number << 40;
                output[7] = number << 48;
                output[8] = number << 56;
                output[9] = number << 64;
               // md_number_to_chars (output, 0, 9);

            }  else if(op == 112) {
                // dispab
                output = frag_more(10);
                output[0] = tmp.opcode;
                unsigned char *argv1 = build_argv(str);

                str+= strlen(argv1);
                if(*str == ',') {
                  str++;
                }
               
                unsigned char *argv2 = build_argv(str);
               
                str+= strlen(argv2);
                unsigned long long adresse = gaspard_atol(argv1);
                output[1] = adresse;
                output[2] = adresse << 8;
                output[3] = adresse << 16;
                output[4] = adresse << 24;
                output[5] = adresse << 32;
                output[6] = adresse << 40;
                output[7] = adresse << 48;
                output[8] = adresse << 56;
                output[9] = adresse << 64;
                output[10] = gaspard_atol_8bits(argv2) ;
             //   md_number_to_chars (output, 0, 10);

   
            }  else if(op == 111) {
                // dispab_read
                output = frag_more(10);
                output[0] = tmp.opcode;
                unsigned char *argv1 = build_argv(str);

                str+= strlen(argv1);
                if(*str == ',') {
                  str++;
                }
               
                unsigned char *argv2 = build_argv(str);
               
                str+= strlen(argv2);
                unsigned long long adresse = gaspard_atol(argv1);
                output[1] = adresse;
                output[2] = adresse << 8;
                output[3] = adresse << 16;
                output[4] = adresse << 24;
                output[5] = adresse << 32;
                output[6] = adresse << 40;
                output[7] = adresse << 48;
                output[8] = adresse << 56;
                output[9] = adresse << 64;
                output[10] = (unsigned char)gpr_fpr(argv2) ;
                printf("argv dispab %s %d",argv2,gpr_fpr(argv2) );

            //    md_number_to_chars (output, 0, 10);

   
            }  else if(op == 40) {
                // dispas_write
                output = frag_more(11);
                output[0] = tmp.opcode;
                unsigned char *argv1 = build_argv(str);

                str+= strlen(argv1);
                if(*str == ',') {
                  str++;
                }
               
                unsigned char *argv2 = build_argv(str);
               
                str+= strlen(argv2);
                unsigned long long adresse = gaspard_atol(argv1);
                unsigned long long data = gaspard_atol(argv2);

                output[1] = adresse;
                output[2] = adresse << 8;
                output[3] = adresse << 16;
                output[4] = adresse << 24;
                output[5] = adresse << 32;
                output[6] = adresse << 40;
                output[7] = adresse << 48;
                output[8] = adresse << 56;
                output[9] = adresse << 64;
                output[10] = data ;
                output[11] = data << 8 ;

              //  md_number_to_chars (output, 0, 11);

            }  else if(op == 41) {
                // dispas_read
                output = frag_more(10);
                output[0] = tmp.opcode;
                unsigned char *argv1 = build_argv(str);

                str+= strlen(argv1);
                if(*str == ',') {
                  str++;
                }
               
                unsigned char *argv2 = build_argv(str);
               
                str+= strlen(argv2);
                unsigned long long adresse = gaspard_atol(argv1);
                output[1] = adresse;
                output[2] = adresse << 8;
                output[3] = adresse << 16;
                output[4] = adresse << 24;
                output[5] = adresse << 32;
                output[6] = adresse << 40;
                output[7] = adresse << 48;
                output[8] = adresse << 56;
                output[9] = adresse << 64;
                output[10] = gpr_fpr(argv2) ;
                //md_number_to_chars (output, 0, 10);

            }  else if(op == 45) {
                // dispal_write
                output = frag_more(13);
                output[0] = tmp.opcode;
                unsigned char *argv1 = build_argv(str);

                str+= strlen(argv1);
                if(*str == ',') {
                  str++;
                }
               
                unsigned char *argv2 = build_argv(str);
               
                str+= strlen(argv2);
                unsigned long long adresse = gaspard_atol(argv1);
                unsigned long long data = gaspard_atol(argv2);

                output[1] = adresse;
                output[2] = adresse << 8;
                output[3] = adresse << 16;
                output[4] = adresse << 24;
                output[5] = adresse << 32;
                output[6] = adresse << 40;
                output[7] = adresse << 48;
                output[8] = adresse << 56;
                output[9] = adresse << 64;
                output[10] = data ;
                output[11] = data << 8 ;
                output[12] = data << 16 ;
                output[13] = data << 24 ;

                md_number_to_chars (output, 0, 13);
            }  else if(op == 47) {
                // dispal_read
                output = frag_more(10);
                output[0] = tmp.opcode;
                unsigned char *argv1 = build_argv(str);

                str+= strlen(argv1);
                if(*str == ',') {
                  str++;
                }
               
                unsigned char *argv2 = build_argv(str);
                unsigned long long data = gaspard_atol(argv2);

                str+= strlen(argv2);
                unsigned long long adresse = gaspard_atol(argv1);
                output[1] = adresse;
                output[2] = adresse << 8;
                output[3] = adresse << 16;
                output[4] = adresse << 24;
                output[5] = adresse << 32;
                output[6] = adresse << 40;
                output[7] = adresse << 48;
                output[8] = adresse << 56;
                output[9] = adresse << 64;
                output[10] = gpr_fpr(argv2) ;

                
                //   md_number_to_chars (output, 0, 10);
            }
            
            
            else {

              // generer l'instruction 
               
                unsigned char *gpr1 = build_argv(str);
                  printf("gpr  1%s \n",gpr1);

                str+= strlen(gpr1);
                if(*str == ',') {
                  str++;
                }
               
                unsigned char *gpr2 = build_argv(str);
               
                str+= strlen(gpr2);

                printf("gpr  2%s \n",gpr2);
             unsigned   char gpr1_final = gpr_fpr(gpr1);
               unsigned char gpr2_final = gpr_fpr(gpr2);
                if(gpr2_final == 254 && *gpr2 == '0') {
                    output = frag_more(3);
                    output[0] = tmp.opcode;
                    output[1]  = gpr1_final;
                    output[2] = gpr2_final;
                   // md_number_to_chars (output, 0, 3);
                    
                } else if(gpr2_final == 254) {
                    printf("gpr disp avec immediat \n");
                    output = frag_more(3+8);
                    output[0] = tmp.opcode;
                    output[1]  = gpr1_final;
                    output[2] = 66;
                    unsigned long long data = gaspard_atol(gpr2);
                    output[3] = data;
                    output[4] = data << 8;
                    output[5] = data << 16;
                    output[6] = data << 24;
                    output[7] = data << 32;
                    output[8] = data << 40;
                    output[9] = data << 48;
                    output[10] = data << 56;
                    output[11] = data << 64;
                 //   md_number_to_chars (output, 0, 3+8);
 
                }
                else {
                output = frag_more(3);
                output[0] = tmp.opcode;
                // controler si cela n'est pas un immediat
                output[1]  = gpr1_final;
                output[2] = gpr2_final;
                    printf("GPR num %d %d  ",gpr1_final,gpr2_final);
                }
            }
          break; 
          

        } else {
            // imprimer que nous troubons pas l'instruction 
     as_fatal (_("Cannot find instruction ")); 




        }



  }


}







/* This is the guts of the machine-dependent assembler.  STR points to
   a machine dependent instruction.  This function is supposed to emit
   the frags/bytes it assembles to.  */

void
m2d_assemble (char *str)
{
  char *op_start;
  char *op_end;

  gaspard_opc_info_t *opcode;
  char *p;
  char pend;

  unsigned short iword = 0;

  int nlen = 0;

  /* Drop leading whitespace.  */
  while (*str == ' ')
    str++;

  /* Find the op code end.  */
  op_start = str;
  for (op_end = str;
       *op_end && !is_end_of_line[*op_end & 0xff] && *op_end != ' ';
       op_end++)
    nlen++;

  pend = *op_end;
  *op_end = 0;

  if (nlen == 0)
    as_bad (_("can't find opcode "));
  opcode = (gaspard_opc_info_t *) str_hash_find (opcode_hash_control, op_start);
  *op_end = pend;

  if (opcode == NULL)
    {
      as_bad (_("unknown opcode %s"), op_start);
      return;
    }

  p = frag_more (2);

  switch (opcode->itype)
    {
    case gaspard_F2_A8V:
      iword = (1<<15) | (opcode->opcode << 12);
      while (ISSPACE (*op_end))
	op_end++;
      {
	expressionS arg;
	int reg;
	reg = parse_register_operand (&op_end);
	iword += (reg << 8);
	if (*op_end != ',')
	  as_warn (_("expecting comma delimited register operands"));
	op_end++;
	op_end = parse_exp_save_ilp (op_end, &arg);
	fix_new_exp (frag_now,
		     ((p + (target_big_endian ? 1 : 0)) - frag_now->fr_literal),
		     1,
		     &arg,
		     0,
		     BFD_RELOC_8);
      }
      break;
    case gaspard_F1_AB:
      iword = opcode->opcode << 8;
      while (ISSPACE (*op_end))
	op_end++;
      {
	int dest, src;
	dest = parse_register_operand (&op_end);
	if (*op_end != ',')
	  as_warn (_("expecting comma delimited register operands"));
	op_end++;
	src  = parse_register_operand (&op_end);
	iword += (dest << 4) + src;
	while (ISSPACE (*op_end))
	  op_end++;
	if (*op_end != 0)
	  as_warn (_("extra stuff on line ignored"));
      }
      break;
    case gaspard_F1_A4:
      iword = opcode->opcode << 8;
      while (ISSPACE (*op_end))
	op_end++;
      {
	expressionS arg;
	char *where;
	int regnum;

 	regnum = parse_register_operand (&op_end);
	while (ISSPACE (*op_end))
	  op_end++;

	iword += (regnum << 4);

	if (*op_end != ',')
	  {
	    as_bad (_("expecting comma delimited operands"));
	    ignore_rest_of_line ();
	    return;
	  }
	op_end++;

	op_end = parse_exp_save_ilp (op_end, &arg);
	where = frag_more (4);
	fix_new_exp (frag_now,
		     (where - frag_now->fr_literal),
		     4,
		     &arg,
		     0,
		     BFD_RELOC_32);
      }
      break;
    case gaspard_F1_M:
    case gaspard_F1_4:
      iword = opcode->opcode << 8;
      while (ISSPACE (*op_end))
	op_end++;
      {
	expressionS arg;
	char *where;

	op_end = parse_exp_save_ilp (op_end, &arg);
	where = frag_more (4);
	fix_new_exp (frag_now,
		     (where - frag_now->fr_literal),
		     4,
		     &arg,
		     0,
		     BFD_RELOC_32);
      }
      break;
    case gaspard_F1_NARG:
      iword = opcode->opcode << 8;
      while (ISSPACE (*op_end))
	op_end++;
      if (*op_end != 0)
	as_warn (_("extra stuff on line ignored"));
      break;
    case gaspard_F1_A:
      iword = opcode->opcode << 8;
      while (ISSPACE (*op_end))
	op_end++;
      {
	int reg;
	reg = parse_register_operand (&op_end);
	while (ISSPACE (*op_end))
	  op_end++;
	if (*op_end != 0)
	  as_warn (_("extra stuff on line ignored"));
	iword += (reg << 4);
      }
      break;
    case gaspard_F1_ABi:
      iword = opcode->opcode << 8;
      while (ISSPACE (*op_end))
	op_end++;
      {
	int a, b;
	a = parse_register_operand (&op_end);
	if (*op_end != ',')
	  as_warn (_("expecting comma delimited register operands"));
	op_end++;
	if (*op_end != '(')
	  {
	    as_bad (_("expecting indirect register `($rA)'"));
	    ignore_rest_of_line ();
	    return;
	  }
	op_end++;
	b = parse_register_operand (&op_end);
	if (*op_end != ')')
	  {
	    as_bad (_("missing closing parenthesis"));
	    ignore_rest_of_line ();
	    return;
	  }
	op_end++;
	iword += (a << 4) + b;
	while (ISSPACE (*op_end))
	  op_end++;
	if (*op_end != 0)
	  as_warn (_("extra stuff on line ignored"));
      }
      break;
    case gaspard_F1_AiB:
      iword = opcode->opcode << 8;
      while (ISSPACE (*op_end))
	op_end++;
      {
	int a, b;
	if (*op_end != '(')
	  {
	    as_bad (_("expecting indirect register `($rA)'"));
	    ignore_rest_of_line ();
	    return;
	  }
	op_end++;
	a = parse_register_operand (&op_end);
	if (*op_end != ')')
	  {
	    as_bad (_("missing closing parenthesis"));
	    ignore_rest_of_line ();
	    return;
	  }
	op_end++;
	if (*op_end != ',')
	  as_warn (_("expecting comma delimited register operands"));
	op_end++;
	b = parse_register_operand (&op_end);
	iword += (a << 4) + b;
	while (ISSPACE (*op_end))
	  op_end++;
	if (*op_end != 0)
	  as_warn (_("extra stuff on line ignored"));
      }
      break;
    case gaspard_F1_4A:
      iword = opcode->opcode << 8;
      while (ISSPACE (*op_end))
	op_end++;
      {
	expressionS arg;
	char *where;
	int a;

	op_end = parse_exp_save_ilp (op_end, &arg);
	where = frag_more (4);
	fix_new_exp (frag_now,
		     (where - frag_now->fr_literal),
		     4,
		     &arg,
		     0,
		     BFD_RELOC_32);

	if (*op_end != ',')
	  {
	    as_bad (_("expecting comma delimited operands"));
	    ignore_rest_of_line ();
	    return;
	  }
	op_end++;

 	a = parse_register_operand (&op_end);
	while (ISSPACE (*op_end))
	  op_end++;
	if (*op_end != 0)
	  as_warn (_("extra stuff on line ignored"));

	iword += (a << 4);
      }
      break;
    case gaspard_F1_ABi2:
      iword = opcode->opcode << 8;
      while (ISSPACE (*op_end))
	op_end++;
      {
	expressionS arg;
	char *offset;
	int a, b;

 	a = parse_register_operand (&op_end);
	while (ISSPACE (*op_end))
	  op_end++;

	if (*op_end != ',')
	  {
	    as_bad (_("expecting comma delimited operands"));
	    ignore_rest_of_line ();
	    return;
	  }
	op_end++;

	op_end = parse_exp_save_ilp (op_end, &arg);
	offset = frag_more (2);
	fix_new_exp (frag_now,
		     (offset - frag_now->fr_literal),
		     2,
		     &arg,
		     0,
		     BFD_RELOC_16);

	if (*op_end != '(')
	  {
	    as_bad (_("expecting indirect register `($rX)'"));
	    ignore_rest_of_line ();
	    return;
	  }
	op_end++;
	b = parse_register_operand (&op_end);
	if (*op_end != ')')
	  {
	    as_bad (_("missing closing parenthesis"));
	    ignore_rest_of_line ();
	    return;
	  }
	op_end++;

	while (ISSPACE (*op_end))
	  op_end++;
	if (*op_end != 0)
	  as_warn (_("extra stuff on line ignored"));

	iword += (a << 4) + b;
      }
      break;
    case gaspard_F1_AiB2:
      iword = opcode->opcode << 8;
      while (ISSPACE (*op_end))
	op_end++;
      {
	expressionS arg;
	char *offset;
	int a, b;

	op_end = parse_exp_save_ilp (op_end, &arg);
	offset = frag_more (2);
	fix_new_exp (frag_now,
		     (offset - frag_now->fr_literal),
		     2,
		     &arg,
		     0,
		     BFD_RELOC_16);

	if (*op_end != '(')
	  {
	    as_bad (_("expecting indirect register `($rX)'"));
	    ignore_rest_of_line ();
	    return;
	  }
	op_end++;
	a = parse_register_operand (&op_end);
	if (*op_end != ')')
	  {
	    as_bad (_("missing closing parenthesis"));
	    ignore_rest_of_line ();
	    return;
	  }
	op_end++;

	if (*op_end != ',')
	  {
	    as_bad (_("expecting comma delimited operands"));
	    ignore_rest_of_line ();
	    return;
	  }
	op_end++;

 	b = parse_register_operand (&op_end);
	while (ISSPACE (*op_end))
	  op_end++;

	while (ISSPACE (*op_end))
	  op_end++;
	if (*op_end != 0)
	  as_warn (_("extra stuff on line ignored"));

	iword += (a << 4) + b;
      }
      break;
    case gaspard_F2_NARG:
      iword = opcode->opcode << 12;
      while (ISSPACE (*op_end))
	op_end++;
      if (*op_end != 0)
	as_warn (_("extra stuff on line ignored"));
      break;
    case gaspard_F3_PCREL:
      iword = (3<<14) | (opcode->opcode << 10);
      while (ISSPACE (*op_end))
	op_end++;
      {
	expressionS arg;

	op_end = parse_exp_save_ilp (op_end, &arg);
	fix_new_exp (frag_now,
		     (p - frag_now->fr_literal),
		     2,
		     &arg,
		     true,
		     BFD_RELOC_gaspard_10_PCREL);
      }
      break;
    case gaspard_BAD:
      iword = 0;
      while (ISSPACE (*op_end))
	op_end++;
      if (*op_end != 0)
	as_warn (_("extra stuff on line ignored"));
      break;
    default:
      abort ();
    }

  md_number_to_chars (p, iword, 2);
  dwarf2_emit_insn (2);

  while (ISSPACE (*op_end))
    op_end++;

  if (*op_end != 0)
    as_warn (_("extra stuff on line ignored"));

  if (pending_reloc)
    as_bad (_("Something forgot to clean up\n"));
}

/* Turn a string in input_line_pointer into a floating point constant
   of type type, and store the appropriate bytes in *LITP.  The number
   of LITTLENUMS emitted is stored in *SIZEP .  An error message is
   returned, or NULL on OK.  */

const char *
md_atof (int type, char *litP, int *sizeP)
{
  int prec;
  LITTLENUM_TYPE words[4];
  char *t;
  int i;

  switch (type)
    {
    case 'f':
      prec = 2;
      break;

    case 'd':
      prec = 4;
      break;

    default:
      *sizeP = 0;
      return _("bad call to md_atof");
    }

  t = atof_ieee (input_line_pointer, type, words);
  if (t)
    input_line_pointer = t;

  *sizeP = prec * 2;

  for (i = prec - 1; i >= 0; i--)
    {
      md_number_to_chars (litP, (valueT) words[i], 2);
      litP += 2;
    }

  return NULL;
}

enum options
{
  OPTION_EB = OPTION_MD_BASE,
  OPTION_EL,
};

struct option md_longopts[] =
{
  { "EB",          no_argument, NULL, OPTION_EB},
  { "EL",          no_argument, NULL, OPTION_EL},
  { NULL,          no_argument, NULL, 0}
};

size_t md_longopts_size = sizeof (md_longopts);

const char *md_shortopts = "";

int
md_parse_option (int c ATTRIBUTE_UNUSED, const char *arg ATTRIBUTE_UNUSED)
{
  switch (c)
    {
    case OPTION_EB:
      target_big_endian = 1;
      break;
    case OPTION_EL:
      target_big_endian = 0;
      break;
    default:
      return 0;
    }

  return 1;
}

void
md_show_usage (FILE *stream ATTRIBUTE_UNUSED)
{
  fprintf (stream, _("\
  -EB                     assemble for a big endian system (default)\n\
  -EL                     assemble for a little endian system\n"));
}

/* Apply a fixup to the object file.  */

void
md_apply_fix (fixS *fixP ATTRIBUTE_UNUSED,
	      valueT * valP ATTRIBUTE_UNUSED, segT seg ATTRIBUTE_UNUSED)
{
  char *buf = fixP->fx_where + fixP->fx_frag->fr_literal;
  long val = *valP;
  long newval;
  long max, min;

  max = min = 0;
  switch (fixP->fx_r_type)
    {
    case BFD_RELOC_32:
      if (target_big_endian)
	{
	  buf[0] = val >> 24;
	  buf[1] = val >> 16;
	  buf[2] = val >> 8;
	  buf[3] = val >> 0;
	}
      else
	{
	  buf[3] = val >> 24;
	  buf[2] = val >> 16;
	  buf[1] = val >> 8;
	  buf[0] = val >> 0;
	}
      buf += 4;
      break;

    case BFD_RELOC_16:
      if (target_big_endian)
	{
	  buf[0] = val >> 8;
	  buf[1] = val >> 0;
	}
      else
	{
	  buf[1] = val >> 8;
	  buf[0] = val >> 0;
	}
      buf += 2;
      break;

    case BFD_RELOC_8:
      *buf++ = val;
      break;

    case BFD_RELOC_gaspard_10_PCREL:
      if (!val)
	break;
      if (val < -1024 || val > 1022)
	as_bad_where (fixP->fx_file, fixP->fx_line,
                      _("pcrel too far BFD_RELOC_gaspard_10"));
      /* 11 bit offset even numbered, so we remove right bit.  */
      val >>= 1;
      newval = md_chars_to_number (buf, 2);
      newval |= val & 0x03ff;
      md_number_to_chars (buf, newval, 2);
      break;

    default:
      abort ();
    }

  if (max != 0 && (val < min || val > max))
    as_bad_where (fixP->fx_file, fixP->fx_line, _("offset out of range"));

  if (fixP->fx_addsy == NULL && fixP->fx_pcrel == 0)
    fixP->fx_done = 1;
}

/* Put number into target byte order.  */

void
md_number_to_chars (char * ptr, valueT use, int nbytes)
{
 
    number_to_chars_littleendian (ptr, use, nbytes);
}

/* Convert from target byte order to host byte order.  */

static valueT
md_chars_to_number (char * buf, int n)
{
  valueT result = 0;
  unsigned char * where = (unsigned char *) buf;

  if (target_big_endian)
    {
      while (n--)
	{
	  result <<= 8;
	  result |= (*where++ & 255);
	}
    }
  else
    {
      while (n--)
	{
	  result <<= 8;
	  result |= (where[n] & 255);
	}
    }

  return result;
}

/* Generate a machine-dependent relocation.  */
arelent *
tc_gen_reloc (asection *section ATTRIBUTE_UNUSED, fixS *fixP)
{
  arelent *relP;
  bfd_reloc_code_real_type code;

  switch (fixP->fx_r_type)
    {
    case BFD_RELOC_32:
      code = fixP->fx_r_type;
      break;
    case BFD_RELOC_gaspard_10_PCREL:
      code = fixP->fx_r_type;
      break;
    default:
      as_bad_where (fixP->fx_file, fixP->fx_line,
		    _("Semantics error.  This type of operand can not be relocated, it must be an assembly-time constant"));
      return 0;
    }

  relP = XNEW (arelent);
  relP->sym_ptr_ptr = XNEW (asymbol *);
  *relP->sym_ptr_ptr = symbol_get_bfdsym (fixP->fx_addsy);
  relP->address = fixP->fx_frag->fr_address + fixP->fx_where;

  relP->addend = fixP->fx_offset;

  /* This is the standard place for KLUDGEs to work around bugs in
     bfd_install_relocation (first such note in the documentation
     appears with binutils-2.8).

     That function bfd_install_relocation does the wrong thing with
     putting stuff into the addend of a reloc (it should stay out) for a
     weak symbol.  The really bad thing is that it adds the
     "segment-relative offset" of the symbol into the reloc.  In this
     case, the reloc should instead be relative to the symbol with no
     other offset than the assembly code shows; and since the symbol is
     weak, any local definition should be ignored until link time (or
     thereafter).
     To wit:  weaksym+42  should be weaksym+42 in the reloc,
     not weaksym+(offset_from_segment_of_local_weaksym_definition)

     To "work around" this, we subtract the segment-relative offset of
     "known" weak symbols.  This evens out the extra offset.

     That happens for a.out but not for ELF, since for ELF,
     bfd_install_relocation uses the "special function" field of the
     howto, and does not execute the code that needs to be undone.  */

  if (OUTPUT_FLAVOR == bfd_target_aout_flavour
      && fixP->fx_addsy && S_IS_WEAK (fixP->fx_addsy)
      && ! bfd_is_und_section (S_GET_SEGMENT (fixP->fx_addsy)))
    {
      relP->addend -= S_GET_VALUE (fixP->fx_addsy);
    }

  relP->howto = bfd_reloc_type_lookup (stdoutput, code);
  if (! relP->howto)
    {
      const char *name;

      name = S_GET_NAME (fixP->fx_addsy);
      if (name == NULL)
	name = _("<unknown>");
      as_fatal (_("Cannot generate relocation type for symbol %s, code %s"),
		name, bfd_get_reloc_code_name (code));
    }

  return relP;
}

/* Decide from what point a pc-relative relocation is relative to,
   relative to the pc-relative fixup.  Er, relatively speaking.  */
long
md_pcrel_from (fixS *fixP)
{
  valueT addr = fixP->fx_where + fixP->fx_frag->fr_address;

  switch (fixP->fx_r_type)
    {
    case BFD_RELOC_32:
      return addr + 4;
    case BFD_RELOC_gaspard_10_PCREL:
      /* Offset is from the end of the instruction.  */
      return addr + 2;
    default:
      abort ();
      return addr;
    }
}
