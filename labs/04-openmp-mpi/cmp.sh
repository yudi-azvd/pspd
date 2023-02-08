# https://superuser.com/questions/125376/how-do-i-compare-binary-files-in-linux

file1=$1
file2=$2

# pra BMPs com dimensões iguais é possível ignorar os bytes do header
cmp -l -i 17 $file1 $file2 |
    mawk 'function oct2dec(oct, dec) {
              for (i = 1; i <= length(oct); i++) {
                  dec *= 8;
                  dec += substr(oct, i, 1)
              };
              return dec
          }
          {
              printf "%08X %02X %02X\n", $1, oct2dec($2), oct2dec($3)
          }'
