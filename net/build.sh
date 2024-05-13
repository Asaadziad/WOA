mkdir -p bin

gcc client/*.c utils/*.c -o bin/client
gcc server/*.c utils/*.c -o bin/server