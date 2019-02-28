-- animation
resetMaxFile #noprompt

mybox = box()
	
mybox.lengthsegs = 10
mybox.widthsegs = 10
mybox.heightsegs = 10
mybox.mapCoords = true

animate on
(
  at time 0 (mybox.pos = [-100, 0, 0]; mybox.scale = [1, 1, 0.25])
  at time 100 (mybox.pos = [100, 0, 0]; mybox.scale = [1, 1, 3])
)

2.5s-- 2.5 seconds
20f-- 20 frames
4800t-- 4800 ticks = 1 sec
1m3s5f-- 1 min, 3 seconds, 5 frames
1:15.5-- SMPTE: 1 min, 15 seconds, 5 frames 