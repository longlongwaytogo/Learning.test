

resetMaxFile #noprompt -- reset the scene
mybox = box length:10 width:10 height:10 wirecolor:red -- new box 
for i = 1 to 40 do -- repeat 40 times for each iteration do:
(
	box_copy = copy mybox -- create a copy of the original box
	box_copy.pos = [i*20,0,0] -- move pos
	box_copy.wirecolor = [i*25,i*50,(5-i)*50]
)