
REM gdal_translate ps_height_16k.png ps_height_16k.tif

REM gdaladdo -r average ps_height_16k.tif 2 4 8 16 32

REM gdal_translate ps_texture_16k.png ps_texture_16k.tif

REM gdaladdo -r average ps_texture_16k.tif 2 4 8 16 32


vpbmasterd  -t gcanyon_color_4k2k.tif -d gcanyon_height.tif    -o new-path/new.osgb