function Initialize()
	Scale = SKIN:GetVariable('Scale', 'n/a')
	Scroll = SKIN:GetVariable('Scroll', 'n/a')
	ScaleChange = SKIN:GetVariable('ScaleChange', 'n/a')
end
function Update()
	return tostring(Scale)
end
function Enlarge()

	Scale = Scale + ScaleChange
end
function Smaller()
	
	if Scroll == "true" then
		if Scale > 0.2 then
			Scale = Scale - ScaleChange
		end
	end
end