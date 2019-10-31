#ifndef PARSER_H_
#define PARSER_H_

#include <stdint.h>

#define OPCODE_ADD 0b10001011000
#define OPCODE_ADDI 0b1001000100
#define OPCODE_AND 0b10001010000
#define OPCODE_ANDI 0b1001001000
#define OPCODE_B 0b000101
#define OPCODE_B_COND 0b01010100
#define OPCODE_BL 0b100101
#define OPCODE_BR 0b11010110000
#define OPCODE_CBNZ 0b10110101
#define OPCODE_CBZ 0b10110100
#define OPCODE_DUMP 0b11111111110
#define OPCODE_EOR 0b11001010000
#define OPCODE_EORI 0b1101001000
#define OPCODE_HALT 0b11111111111
#define OPCODE_LDUR 0b11111000010
#define OPCODE_LDURB 0b00111000010
#define OPCODE_LDURH 0b01111000010
#define OPCODE_LDURSW 0b10111000100
#define OPCODE_LSL 0b11010011011
#define OPCODE_LSR 0b11010011010
#define OPCODE_MUL 0b10011011000
#define OPCODE_ORR 0b10101010000
#define OPCODE_ORRI 0b1011001000
#define OPCODE_PRNL 0b11111111100
#define OPCODE_PRNT 0b1111111101
#define OPCODE_SDIV 0b10011010110
#define OPCODE_SMULH 0b10011011010
#define OPCODE_STUR 0b11111000000
#define OPCODE_STURB 0b00111000000
#define OPCODE_STURH 0b01111000000
#define OPCODE_STURW 0b10111000000
#define OPCODE_SUB 0b11001011000
#define OPCODE_SUBI 0b1101000100
#define OPCODE_SUBIS 0b1111000100
#define OPCODE_SUBS 0b11101011000
#define OPCODE_UDIV 0b10011010110
#define OPCODE_UMULH 0b10011011110

typedef struct r_format {
  uint16_t opcode : 11;
  uint8_t Rm : 5;
  uint8_t shamt : 6;
  uint8_t Rn : 5;
  uint8_t Rd : 5;
} r_format_t;

typedef struct i_format {
  uint16_t opcode : 10;
  uint16_t ALU_immediate : 12;
  uint8_t Rn : 5;
  uint8_t Rd : 5;
} i_format_t;

typedef struct d_format {
  uint16_t opcode : 11;
  uint16_t DT_address : 9;
  uint8_t op : 2;
  uint8_t Rn : 5;
  uint8_t Rt : 5;
} d_format_t;

typedef struct b_format {
  uint8_t opcode : 6;
  uint32_t BR_address : 26;
} b_format_t;

typedef struct cb_format {
  uint8_t opcode : 8;
  uint32_t COND_BR_address : 19;
  uint16_t Rt : 5;
} cb_format_t;

typedef struct iw_format {
  uint16_t opcode : 11;
  uint16_t MOV_immediate : 16;
  uint8_t Rd : 5;
} iw_format_t;

union instruction {
  r_format_t r;
  i_format_t i;
  d_format_t d;
  b_format_t b;
  cb_format_t cb;
  iw_format_t iw;
};

typedef enum instruction_format {
  format_NA,
  format_R,
  format_I,
  format_D,
  format_B,
  format_CB,
  format_IW
} instruction_format_t;

union instruction parse(uint32_t* word);

#endif