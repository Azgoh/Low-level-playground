#include <stdio.h>

/*
A simple stack visualizer. We can see that the stack grows towards lower addresses.
In my case the output is:
RBP: 0x7ffd3ee4df40
RSP: 0x7ffd3ee4df10
Address of x: 0x7ffd3ee4df1c
Address of local1: 0x7ffd3ee4df20
Address of local2: 0x7ffd3ee4df24
Let's analyze:
- 0x7ffd3ee4df40 - 0x7ffd3ee4df10 = 0x30 (48 bytes) so the compiler reserved 48bytes for the stack frame (sub rsp, 0x30)
- 0x7ffd3ee4df40 - 0x7ffd3ee4df1c = 0x24 (36 bytes) so x = [rbp - 0x24]
- 0x7ffd3ee4df40 - 0x7ffd3ee4df20 = 0x20 (32 bytes) so local1 = [rbp - 0x20]
- 0x7ffd3ee4df40 - 0x7ffd3ee4df24 = 0x1c (28 bytes) so local2 = [rbp - 0x1c]

We notice that even though we wrote:
int local1 = 10;
int local2 = 20;
local2 is at a higher address(0x7ffd3ee4df24) than local1(0x7ffd3ee4df20).
This happens because the exact layout of local variables in memory is not strictly defined by the C standard and is decided by the compiler. 
The compiler may reorder variables or insert padding to satisfy alignment and optimization requirements.

Let's now compare with the assembly we get by running objdump -d bin/stack_visualizer | grep -A20 "<foo>". The default syntax is AT&T, 
if you want the output to be in Intel syntax run objdump -d -M intel bin/stack_visualizer | grep -A20 "<foo>":
    1169:       f3 0f 1e fa             endbr64
    116d:       55                      push   %rbp                 old rbp saved on the stack
    116e:       48 89 e5                mov    %rsp,%rbp            new stack frame starts
    1171:       48 83 ec 30             sub    $0x30,%rsp           reserve 48 bytes
    1175:       89 7d dc                mov    %edi,-0x24(%rbp)     x = [rbp - 0x24] = 0x7ffd3ee4df1c
    1178:       64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
    117f:       00 00 
    1181:       48 89 45 f8             mov    %rax,-0x8(%rbp)
    1185:       31 c0                   xor    %eax,%eax
    1187:       c7 45 e0 0a 00 00 00    movl   $0xa,-0x20(%rbp)     local1 = [rbp - 0x20] = 0x7ffd3ee4df20
    118e:       c7 45 e4 14 00 00 00    movl   $0x14,-0x1c(%rbp)    local2 = [rbp - 0x1c] = 0x7ffd3ee4df24
    1195:       48 89 e8                mov    %rbp,%rax
    1198:       48 89 45 e8             mov    %rax,-0x18(%rbp)
    119c:       48 89 e0                mov    %rsp,%rax
    119f:       48 89 45 f0             mov    %rax,-0x10(%rbp)
    11a3:       48 8b 45 e8             mov    -0x18(%rbp),%rax
    11a7:       48 89 c6                mov    %rax,%rsi
    11aa:       48 8d 05 53 0e 00 00    lea    0xe53(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    11b1:       48 89 c7                mov    %rax,%rdi
    11b4:       b8 00 00 00 00          mov    $0x0,%eax
--
    1259:       e8 0b ff ff ff          call   1169 <foo>
    125e:       b8 00 00 00 00          mov    $0x0,%eax
    1263:       c9                      leave
    1264:       c3                      ret

Disassembly of section .fini:

0000000000001268 <_fini>:
    1268:       f3 0f 1e fa             endbr64
    126c:       48 83 ec 08             sub    $0x8,%rsp
    1270:       48 83 c4 08             add    $0x8,%rsp
    1274:       c3                      ret

Note: Not all of the 48 bytes are used for local variables. Some of the space is used for:
- Stack alignment (16-byte alignment requirement on x86-64)
- The stack canary (stored at [rbp - 0x8]) for security. A stack canary is a hidden value placed on the stack 
to detect if memory corruption (e.g. buffer overflow) happened.
- Temporary storage for variables like rbp and rsp used in this program

Stack frame layout:
[rsp]                ← top of stack (lowest address of this frame)
...
[rbp - 0x24]         ← x
[rbp - 0x20]         ← local1
[rbp - 0x1c]         ← local2
[rbp - 0x18]         ← saved rbp
[rbp - 0x10]         ← saved rsp
[rbp - 0x8]          ← stack canary
[rbp]                ← base pointer
*/


void foo(int x){
    int local1 = 10;
    int local2 = 20;

    void *rbp;
    void *rsp;

   /*
    Inline assembly explanation:

    asm("mov %%rbp, %0" : "=r"(rbp));

    1) "mov %%rbp, %0"
        - Moves the value of the RBP register into a placeholder (%0)
        - %% is used because % has special meaning in GCC inline assembly

    2) "=r"(rbp)
        - "=r" means output into a register
        - (rbp) means store the result into the C variable rbp

    So effectively:
    rbp = value of the RBP register
    */

    asm("mov %%rbp, %0" : "=r"(rbp)); // copy RBP register into C variable rbp
    asm("mov %%rsp, %0" : "=r"(rsp)); // copy RSP register into C variable rsp

    printf("RBP: %p\n", rbp);
    printf("RSP: %p\n", rsp);

    printf("Address of x: %p\n", &x);
    printf("Address of local1: %p\n", &local1);
    printf("Address of local2: %p\n", &local2);
}

int main(void){

    int a = 5;

    foo(a);

    return 0;
}