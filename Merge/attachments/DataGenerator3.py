Table1 = open('Table1_3.txt','w')
Table2 = open('Table2_3.txt','w')
Alpha = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
count=0;
for letter1 in Alpha:
	for letter2 in Alpha:
		for letter3 in Alpha:
			Table1.write(letter1+letter2+letter3+'|'+str(count)+'\n');#+'|1'\n')#+letter4+letter5+letter6+'|1\n')
			Table2.write(letter1+letter2+letter3+'|'+str(count)+'\n');#+'|2'\n')#+letter4+letter5+letter6+'|2\n')
			count = count+1;
Table1.close()
Table2.close()
