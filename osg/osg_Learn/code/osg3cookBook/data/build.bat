
REM gdal_translate ps_height_16k.png ps_height_16k.tif

REM gdaladdo -r average ps_height_16k.tif 2 4 8 16 32

REM gdal_translate ps_texture_16k.png ps_texture_16k.tif

REM gdaladdo -r average ps_texture_16k.tif 2 4 8 16 32

REM ��������ִ�д��󣬲�������߳�����
REM osgdemd --xx 10 --yy 10 -t gcanyon_color_4k2k.tif --xx 10 --yy 10 -d gcanyon_height.tif -l 8 -v 0.1 -o new_old/new.osgb