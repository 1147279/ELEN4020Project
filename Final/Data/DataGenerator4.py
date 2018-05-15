Table1 = open('Table1_4.txt','w')
Table2 = open('Table2_4.txt','w')
Alpha = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
count = 0;
for letter1 in Alpha:
	for letter2 in Alpha:
		for letter3 in Alpha:
			for letter4 in Alpha:		
				Table1.write(letter1+letter2+letter3+letter4+'|'+str(count)+'\n');#+letter5+letter6+'|1\n')
				Table2.write(letter1+letter2+letter3+letter4+'|'+str(count)+'\n');#+letter5+letter6+'|2\n')
				count = count +1;

Table1.close()
Table2.close()
