-- exprot fbx to cgf   
 -- cryMaxTools.export.object.fnExport
 --sceneName = maxFilePath + maxFileName
 --messagebox(maxFileName)
fn shape_filt obj =  obj.name -- isKindOf obj Shape
--Then you can call the Select By Name function to select multiple shapes including hidden ones:
theShapes =selectByName title:"Select Shapes" buttonText:"GET 'EM!" filter:shape_filt showHidden:true single:true


for i = 1 to GetNumberSelectFilters() do --go through all
format "%: %\n"i (GetSelectFilterName i) --print index and name --result: