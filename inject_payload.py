from sys import argv
 
binfileUS = "payloadUS.bin"
binfileEU = "payloadEU.bin"
savfileUS = "flawUS.sav"
savfileEU = "flawEU.sav"
 
binUS = open(binfileUS, "r+b")
binEU = open(binfileEU, "r+b")
savUS = open(savfileUS, "r+b")
savEU = open(savfileEU, "r+b")
 
bincontentUS = binUS.read()
bincontentEU = binEU.read()
 
savUS.seek(0x8C)
savUS.write(bincontentUS)

savEU.seek(0x8C)
savEU.write(bincontentEU)
 
binUS.close()
binEU.close()
savUS.close()
savEU.close()