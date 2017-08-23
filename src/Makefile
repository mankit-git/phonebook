SRC = $(wildcard *.c)

CC=arm-none-linux-gnueabi-gcc

CPPFLAGS += -I /mnt/hgfs/winshare/linux/project/phone/inc/
CPPFLAGS += -I /home/gec/armsqlite/include/
LDFLAGS += -L /home/gec/armsqlite/lib/
LDFLAGS += -lsqlite3
#ENVFLAGS += -Wl,-rpath=/mnt/hgfs/winshare/linux/project/lib

main:$(SRC)
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS) $(ENVFLAGS)

	

