import re 

with open("shakespearever2.ged", "r") as rf:
	with open("pred.pl", "w") as wf:

		ID = {}
		for line in rf:
			if line[:4] == '0 @I':
				PID = line[2:9]
			elif line[2:6] == 'GIVN':
				givn = line[7:].rstrip()
			elif line[2:6] == 'SURN':
				surn = line[7:].rstrip()
				name = '\'' + surn + ' ' + givn + '\''
				ID[PID] = name
			elif line[2:5] == 'SEX':
				sex = line[6].lower()
				predicate = 'sex(' + name + ', ' + sex + ').\n'
				wf.write(predicate)

		rf.seek(0)
		for line in rf:
			if line[:4] == '0 @F':
				husb = ' '; wife = ' '
			elif line[2:6] == 'HUSB':
				HID = line[7:].rstrip()
				husb = ID.get(HID)
			elif line[2:6] == 'WIFE':
				WID = line[7:].rstrip()
				wife = ID.get(WID)
			elif line[2:6] == 'CHIL':
				CID = line[7:].rstrip()
				child = ID.get(CID)
				predicate1 = 'parent(' + husb + ', ' + child + ').\n'
				predicate2 = 'parent(' + wife + ', ' + child + ').\n'
				wf.write(predicate1)
				wf.write(predicate2)
       
wf.close() 
rf.close() 
