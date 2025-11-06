# SYSC4001_A2

for Part II, I used Win32 to develop the code, and then compiled it within WSL.

steps:

1. change to code directory
2. gcc -Wall -Wextra -O2 part2_#_101291890_101303925.c -o q# (replace code file name when needed)
3. ./q#

example:

gcc -Wall -Wextra -O2 part2_5_101291890_101303925.c -o q5 && gcc -Wall -Wextra -O2 part2_5.c -o part2_5
./q5

to get man pages in terminal:

man semget
man semctl
man #####

or access online: https://man7.org/linux/man-pages/dir_all_by_section.html