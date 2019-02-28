fbx_files=getFiles "E:\\CRYENGINE\\test\\Assets\\objects\\guanmu\\*.fbx" 
for f in fbx_files 
do ( if(doesFileExist f) 
then ( importFile f 
select objects 
-- append myobjects f
--select f 
) 
--select myobjects
) 