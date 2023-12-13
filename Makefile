all: festive christmassy present_moshpit chimney happy_holidays

# no dependencies, don't need to deal with that right now. :shrug:

present_moshpit: present_moshpit.o
	gcc present_moshpit.o -o present_moshpit

present_moshpit.o: present_moshpit.c
	gcc -c present_moshpit.c

festive: festive.o
	gcc festive.o -o festive

festive.o: festive.c
	gcc -c festive.c

christmassy: christmassy.o
	gcc christmassy.o -o christmassy

christmassy.o: christmassy.c
	gcc -c christmassy.c

chimney: chimney.o
	gcc chimney.o -o chimney

chimney.o: chimney.c
	gcc -c chimney.c

happy_holidays: happy_holidays.o
	gcc happy_holidays.o -o happy_holidays

happy_holidays.o: happy_holidays.c
	gcc -c happy_holidays.c

# you don't need to run this, but it cleans out your directory if you want.
clean:
	rm -rf *.bin *.o