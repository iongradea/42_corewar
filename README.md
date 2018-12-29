# COREWAR

Core War was inspired by a malicious virus written in the 80’s. To deal with the self-replicating virus, a white hat hacker invented Reaper. It was a virus designed to spread and eliminate the malware. He fought fire with fire.<br/>

This inspired A. K. Dewdney to coin the idea for Core War.<br/>

The idea was simple. You compete by designing viruses to overtake a computer. You win by protecting your own program and overwriting your opponent's programs. This is all happening on a virtual computer. Think, a simple computer within your computer.<br/>

In this project, we code the virtual machine (VM) that manages the game and the assembler (ASM) that compiles the assembly code to binary.<br/>

## Links 

For a great explanation of the corewar VM part of the corewar project, follow this link :
[emilwallner_corewar](https://github.com/emilwallner/Corewar)

See project subject (in french) : 
[corewar](../corewar.pdf)

# ASM

## Launch

`git clone https://github.com/iongradea/10_corewar.git; cd 10_corewar/ASM/; make re; ./asm junk/zork.s`

## Goal

The goal of this project is to write an assembly language compiler named ASM. It takes asm codes and compiles it to binary. 

## Program explanation

This is an assembly code inside zork.s :<br/>

![Alt text](./img/s_file.png?raw=true "Title")

This code will be compiled in the following binary :<br/>

![Alt text](./img/bin_file.png?raw=true "Title")

Several asm files can be compiled at the same time.<br/>

## Data structure

The t_inst structure is the main data structure of the program. It is used from the parsing steps to the encryption steps. For every line in the assembly file, this structure collects the relevant data to identify the instruction.<br/>
These structure are linked following the order of the instruction in the file by "n" (next) and "p" (previous). When the parsing is completed its a double linked data structure that saved all the instructions.<br/>

Description of the instruction type :
<-- parsing & checking errors steps --> 
- opcode : indicates the instruction code 
- args : saved arguments of the instruction including the instruction name
- label : labels can be used inside the .s file to redirect the programming flow. Here it is detected if a label is present at this instruction
- n : next instruction
- p : previous instruction
<-- output calculation steps -->
- ocp : value of the ocp byte if present for this instruction
- param : value of each argument for this instruction
- size : size of this instruction including opcode, ocp (if exists) and arguments

![Alt text](./img/asm_inst_struct.png?raw=true "Title")

This op structure is used for the table in ./src/op.c file where all the data concerning the instruction are stored.<br/>

op structure details :
- opcode : the operation code
- mmeno : the name of the operation code used in the .s file (assembly file)
- nb_param : the number of parameters for this instruction
- param : this table details the type of allowed parameter type for each parameters (between T_DIR, T_REG, T_IND)
- cycle : indicates the number of cycles it takes to do this instruction
- desc : a small description of what the instruction does
- set_carry : an instruction can set a flag to true, set_carry indicates if the flag carry is set for this instruction (the carry is not used in the ASM, only in the VM)
- ocp_param : the ocp is a byte that indicates the type of the different parameters encoded in one byte. This flag indicates if there is an ocp for this instruction.
- dir_size : the parameter type T_DIR can have different sizes depending on the instruction, dir_size indicates the parameter size if it is a T_DIR for this instruction

![Alt text](./img/asm_op_struct.png?raw=true "Title")


## Program architecture

File tree structure :
- parse_inst.c & parse_inst_2.c : parses the lines from the file
- ft_inst_size.c : computes the size of each instruction when written to output file
- ft_ch_args.c & ft_ch_calc_args.c : check the argument for errors
- calc_args.c : computes the value of the arguments to be encrypted to the output file
- ft_create_out_file.c : creates the output file
- op.c : where the op_tab global variable with all the instruction operation details is written


![Alt text](./img/asm_file_struct.png?raw=true "Title")


# VM

## Launch 

`git clone https://github.com/iongradea/10_corewar.git; cd 10_corewar/VM/; make re; ./corewar champions/zork.cor champions/big_life.cor`

## Goal & Program explanation 

For a great explanation of the corewar VM part of the corewar project, follow this link :
[emilwallner_corewar](https://github.com/emilwallner/Corewar)

See project subject (in french) : 
[corewar](../corewar.pdf)


## Data structure

t_vm_mem structure is the structure that manages the workflow of the instruction and processes and the memory. 
Details :
- men : the circular memory of the virtual machine
- cycle : number of cycles before the beginning of the game
- cycle_to_die : variable that identifies after how many cycles all processes are tested to see if they have executed the instruction live at least once
- ch_decr : ...
- check : ...
- opt : option byte, set during parsing. See usage for more details on options
- dump : ...
- display : ...
<-- used for graphic display -->
- mem_uid : identifies wh
- mem_color_size : ...
- mem_color_ind : ...
- last_live : the last process that executed the instruction live, this is used to identify the winner.

![Alt text](./img/vm_mem_struct.png?raw=true "Title")

t_ps is a structure that saves all the details relative to a process being launched. A the beginning of the game there is only one process for each player but as time goes on, each process can fork itself (ie create a new process).
Details of each component :
- playr : name of the playr that is launching the process
- uid : playr number
- code : original binary code of the program
- code_size : length of the code
- reg : registers that can save values inside the process, each process has REG_NUMBER registers
- pc : program counter, identifies where the process is when launched
- carry : identifies the value of the carry for this process, this will impact the workflow
- next : all process are linked in a chained list
- op_size : current operation size including the opcode, ocp and arguments
- live : after a certain number of cycles, the VM determines which process is still alive. To be alive, a process must have launched the instruction live before this check. This flag identifies if this instruction has been launched for this process
- color : used during printing the arena with a different color for each process

![Alt text](./img/vm_ps_struct.png?raw=true "Title")

See explanation above in the ASM part for the explanation of the structure below.
Only the pointer to function has been added that saves the function that is executing the instruction while the VM works.

![Alt text](./img/vm_op_struct.png?raw=true "Title")


## Program architecture

File tree structure details :
- get_playr.c : parses all players information saves them into processes
- vm_mem.c : initiales the virtual machine arena
- parse_opt.c : parses option
- cpu.c & cpu_2.c : file where the "cpu" architecture for the vm is located
- exec_op.c : where every instruction is executed
- ft_aff_sti_ldi_lldi.c : contains instruction aff, sti, ldi, lldi
- ft_bin_add_sub_ld_st.c : contains binary instruction (and, or, xor), add, sub, ld, st
- ft_live_zjmp_fork_lfork.c : contains live, zjmp, fork, lfork
- ft_op_fun.c & ft_op_fun_2.c : general functions used by all instructions
- op.c : contains all details for all instruction inside global variable

![Alt text](./img/vm_file_struct.png?raw=true "Title")

## Options

1. Verbose: -v <verbosity-number>
	- 1	: show essentials
	- 2	: show lives
	- 3	: show cyles
	- 4	: show operations
	- 5	: show deaths

2. Graphical mode (Ncurse library)

3. Simple graphical mode (display memory dump): -g <nbr-cycles>

4. Dump memory after N cycle: -dump <cycle-number>
A script has been write to use this options easly

5. Set player number: -n <nbr>

## Execution

When a hero has been compiled to .cor, we need to launch `corewar` binary.
No mandatory options are set.
`./corewar some-champion.cor`

- First the map is charged in memory with `MEM_SIZE` and struct `t_vm_mem` is initialized
- Options are parsed and just after players (champions) are saved in `t_ps` struct
- Max champion number (`MAX_PLAYERS`) is set in `VM/inc/op.h`

Champion UID is automaticaly set to 999 (each following champions will have 998, 997 and 996)
- Player data is now charged in current map
- Game start, each operations are executed in order they are read
Operations are execute when all the needed cycle have been done.
If `ps->opcode` is no more valid when cycle are done, we jump to 2 bytes.

Lives are accepted from :
 - current process
 - forked process
