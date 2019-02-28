
utility spread "Spread objects" -- define the utility name and description string 
(
	local last_amt = 0 -- define and initialize local variable
	checkbox x "Spread in x"
	checkbox y "Spread in y"
	checkbox z "Spread in z"
	spinner spread "Spread amount:" range:[-1000, 1000,0] -- careate a spinner
	
	on spread changed amt do -- when spinner value changes
	(
		delta = amt - last_amt -- calculate diffrence in current and previous 
		for obj in selection do -- values for each selected object
		(
			-- calculate new position base on current position and selection center
			p = obj.pos + normalize(obj.pos - selection.center) * delta
			
			if x.checked then obj.pos.x = p.x 
			if y.checked then obj.pos.x = p.y 
			if z.checked then obj.pos.x = p.z
		)
		last_amt = amt
	)

)

