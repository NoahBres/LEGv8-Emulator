#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "legv8emul.h"
#include "debug.h"
#include "instruction_impl.h"
#include "parser.h"
#include "reader.h"

machine_state_t machine_state;

/*
Print out the usage for this program
*/
void usage() {
  printf("USAGE: ./legv8emul <assembled legv8asm .machine file>\n");
}

void setup(machine_state_t *machine_state){
  machine_state->X[SP] = STACK_SIZE;
  machine_state->X[FP] = STACK_SIZE;
  machine_state->X[XZR] = 0;
}

int main(int argc, char* argv[]) {

  if (argc == 2) {
    setup(&machine_state);
    machine_state.instructions = read_instructions(argv[1]);

#ifdef DEBUG_MODE
    // Print bits of each instruction
    for (int i = 0; machine_state.instructions[i]; i++) {
      printf("%s\n", DEBUG_bits(machine_state.instructions[i]));

      /* Parse Instruction */
      instruction_t instruction = parse(&machine_state.instructions[i]);

      /* Execute Instruction */
      instruction.instruction_func(&machine_state, &instruction);
    }

#endif

  } else {
    usage();
    return 0;
  }

  DUMP(&machine_state, NULL);

  for(int i = 0; i < 8; i ++){
    printf("%02hhx", machine_state.stack[504 + i]);
  }
  printf("\n");
  return 0;
}
