# Notes from the x86 reverse engineering course on github

## Introduction

- Reverse engineering or back engineering is the process by which an artificial object is deconstructed to reveal its designs, architecture, code, or to extract knowledge from the object. 

## Part 1: Goals

- **Malware analysis** is the understanding and examination of information necessary to respond to a network intrusion.
- Break-down the respective suspected malware binary, find it on your network and ultimately contain it.
- **Host-based signatures** are utilized to find malicious code in a target machine. They are also refered to as indicators, which can identify files created or edited by the infected code which can make hidden changes to a computer's registry.
- On the other hand, **antivirus signatures** concentrate on what the malware actually does, rather than the make-up of the malware. This makes them more effective in finding malware that can migrate or has been removed from the media.
- **Network signatures** are used to find malicious code by examining network traffic. 

## Part 2: Techniques

- **Static analysis** uses software tools to examine the executable without running the actual decompiled instructions in Assembly. 
- **Dynamic analysis** uses disassemblers and debuggers to analyze malware binaries while actually running them. 
- **IDA**, a multi-platform, multi-processor disassembler and debugger, is the most popular tool in the market today.
- A **disassembler** converts an executable binary written in Assembly, C, C++, etc., into Assembly instructions that we can debug and manipulate.

## Part 3: Types Of Malware

- A **backdoor** is malicious code that embeds itself into a computer to allow a remote attacker access with very little or sometimes no authority to execute various commands on any respective local computer.
- A **botnet** is a network of compromised computers (bots or zombies) that are infected with malware and controlled remotely by an attacker.
- A **downloader** is malicious code whose purpose is ti install other malicious software. They are frequently installed when a hacker initially gains access to a system. The downloader then installs additional software to control the system.
- **Information-stealing** malware (infostealers) is malware designed to collect sensitive data from an infected system and transmit it to an attacker-controlled server.
- There are malicious programs that launch other malicious programs which use non-standard options to get increased access or a greater cloaking.hiding technique when penetrating a system.
- A **rootkit** is one of the most dangerous forms of malware. It hides its existence and the existence of additional malware from the user, something that makes it extremely hard to locate. A rootkit can manipulate processes such as hiding their IP in an IP scan, so that the user may never know they have a direct socker to a botnet or other remote computer.
- **Scareware** is used to trick a user into purchasing additional software to falsely protect them when there is no real threat whatsoever. Once a user pays to have the tricked software removed from the computer, it then can stay resident and later emerge in an altered form.
- Various kind of malware send **spam** from a target machine which generates income for the attacker by allowing them to sell various services to other users.
- A traditional **worm** or **virus** copies itself and goes after other computers.
- Something that isn't mentioned in the tutorial is a **bootkit**. A bootkit is an advanced type of malware that infects a computer's boot process (specifically the Master Boot Record (MBR) or UEFI firmware) to load before the operating system. By operating at this low level, bootkits gain stealthy, persistent, and high-level control, allowing them to bypass security software and evade detection. To remove them, specialized scanning tools or directly flashing the SPI BIOS/UEFI chip may be required.

## Part 4: x86 Assembly Intro

- x86 Assembly is a family of backward-compatible Assembly Languages which provide compatibility back to the Intel 8000 series of microprocessors. x86 Assembly Languages are used to produce object code for the for the aforementioned series of processors. It uses mnemonics to represent the instructions that the CPU can execute.
- Assembly Language for the x86 microprocessor works in conjunction with various OS.
- x86 Assembly Language has two choices of syntax. The AT&T syntax which was dominant in the UNIX world and the Intel syntax which was originally used for the documentation of the x86 platform and was dominant in the MS-DOS and Windows environments.
- In the AT&T syntax, the source comes before the destination. 
- In the Intel syntax, the destination comes before the source.
- This tutorial focus on Linux Assembly and specifically the 32-bit architecture as most malware will be written for such in order to affect as many systems as possible. 32-bit malware will work on 64-bit systems.

## Part 5: Binary Number System

- No comments necessary

## Part 6: Hexadecimal Number System

- 8 bits = 1 byte.
- 8 bits = top 4 bits + low 4 bits.
- 4 bits is a nibble.
- 4 bits gives us the possible range from 0-15 so a base 16 system is easier to work with.
- In x86 Assembly, it is much easier to express binary number representations in hex than it is in any other numbering system.
- Decimal goes 0-15.
- Hex goes 0-F.
- A hex number is 4 bits long (called a nibble).
- Examples about converting, adding and subtracting hex numbers can be found in the tutorial.

## Part 7: Transistors and Memory

- Computers are made of transistor switches.
- Transistors are microscopic crystals of silicon that use electrical properties of silicon to act as switches. Modern computers have field-effect transistors.
- Voltage presence idnicates a binary 1 and the absence of voltage indicates a binary 0, therefore a **memory cell** hold one binary digit or bit which is either 1 or 0.

## Part 8: Bytes, Words, Double Words, etc...

- Memory is measured in bytes
- A byte is 8 bits. (DB == Define Byte in Assembly)
- Two bytes are called a word (2 bytes - 16bits, DW == Define Word in Assembly).
- Two words are called a double word (4 bytes - 32bits, DD == Define Double Word in Assembly).
- A byte (8bits) can take a value of up to 2^8 == 256. 
- Every byte of memory has its own unique address.  
- 0xffffd040 is 4 bytes and is a double word. Every hex digit is 4 bits long. The 0x at the beginning indicates the number is a hex value.
- A computer program is just machine instructions stored in memory. A 32-bit CPU fetches a double word from a memory address. Its read from memory and loaded into the CPU. As soon as it finishes executing, the CPU fetches the next machine instruction in memory from the instruction pointer.

## Part 9: x86 Basic Architecture

- A computer application is a table of machine instructions stored in memory to which the binary numbers which make up the program are unique only in the way the CPU deals with them.
- The basic architecture is made up of a CPU, memory and I/O devices which are input/output devices which are all connected by a system bus as detailed in the picture provided in the tutorial.
- The CPU consists of 4 parts which are:
    - **Control Unit** - Retrieves and decodes instructions from the CPU and then stores them in the memory or retrives them from the memory.
    - **Execution Unit** - Where the execution of fetching and retrieving instructions occurs.
    - **Registers** - Internal CPU memory locations used as a temporary data storage.
    - **Flags** - Indicate events when execution occurs.
- In 32-bit x86, a 32-bit CPU first fetches a double word (4 bytes or 32-bits in length) from a specific address in memory and is read from memory and loaded into the CPU. At this point the CPU looks at the binary pattern of bits within the double word and begins executing the procedure that the fetched machine instruction directs it to do.
- Upon completion of executing an instruction, the CPU goes to memory and fetches the next machine instruction in sequence. The CPU has a **register** called the **EIP** or **Extended Instruction Pointer**, that contains the address of the next instruction to be fetched from memory and then executed.
- If we controlled the flow EIP, we can alter the program to do things it was not intended to do. This is a popular technique upon which malware operates. 
- The entire fetch and execute process is tied to the system clock which is an oscillator that emits square-wave pulses at precise intervals.