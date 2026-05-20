REQUIREMENTS:

Library: OpenSSL 3.x (libcrypto)

Compiler: GCC 11.0+ (MinGW-w64)

Environment: Windows PowerShell / Command Prompt

Python: 3.10 or higher





Additional notes and compilation instructions:



All the implementations have the required additional libraries and modules mentioned at the top of the code (#include). The OpenSSL-Win64 must be installed.
The .ddl and .lib files must all be added in the same folder as the C code for the implementation. In this case, they are already provided in this folder.
There are also .exe files included for each hash function. The following commands can be used in powershell for the compilation and execution of the files (depending on where the OpneSSL-Win64 containing the headers is installed in your computer, the path might need to be modified accordingly):

!Note: if running the execution command in the powershell doesn't show a result, or the terminal closes immediately after it finished the hashing, you should run it the terminal of the application used to modify the code (ex: Visual Studio Code). The resulting hash will be visible there.

FOR SHA-256
Compilation: gcc SHA-256.c -o SHA-256.exe -I"C:\\Program Files\\OpenSSL-Win64\\include" libcrypto.lib libssl.lib -lws2\_32 -lgdi32 -ladvapi32 -lcrypt32 
Execution: .\\SHA-256.exe



FOR SHA-3
Compilation: gcc SHA-3.c -o SHA-3.exe -I"C:\\Program Files\\OpenSSL-Win64\\include" libcrypto.lib libssl.lib -lws2\_32 -lgdi32 -ladvapi32 -lcrypt32
Execution: .\\SHA-3.exe



FOR WHIRLPOOL
Compilation: gcc Whirlpool.c -o Whirlpool.exe -I"C:\\Program Files\\OpenSSL-Win64\\include" libcrypto.lib libssl.lib -lws2\_32 -lgdi32 -ladvapi32 -lcrypt32
Execution: .\\Whirlpool.exe



FOR BLAKE2b
Compilation: gcc Blake2b.c -o Blake2b.exe -I"C:\\Program Files\\OpenSSL-Win64\\include" libcrypto.lib libssl.lib -lws2\_32 -lgdi32 -ladvapi32 -lcrypt32
Execution: .\\Blake2b.exe



FOR RIPEMD
Compilation: gcc RIPEMD.c -o RIPEMD.exe -I"C:\\Program Files\\OpenSSL-Win64\\include" libcrypto.lib libssl.lib -lws2\_32 -lgdi32 -ladvapi32 -lcrypt32
Execution: .\\RIPEMD.exe



FOR the Hashing Engine:

Compilation: gcc adaptive\_engine.c -o engine.exe

Execution: ./adaptive\_engine.exe testfile.txt

