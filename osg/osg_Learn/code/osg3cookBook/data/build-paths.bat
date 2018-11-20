
REM gdal_translate ps_height_16k.png ps_height_16k.tif

REM gdaladdo -r average ps_height_16k.tif 2 4 8 16 32

REM gdal_translate ps_texture_16k.png ps_texture_16k.tif

REM gdaladdo -r average ps_texture_16k.tif 2 4 8 16 32


vpbmasterd --patch build_master.source -d sub_gcanyon_height.tif