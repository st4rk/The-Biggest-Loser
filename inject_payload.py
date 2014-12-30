from sys import argv
 
binfile = "exploit.bin"
savfile = "flaw.sav"
 
bin = open(binfile, "r+b")
sav = open(savfile, "r+b")
 
bincontent = bin.read()
 
sav.seek(0x108)
sav.write(bincontent)
 
bin.close()
sav.close()