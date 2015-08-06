echo parameter 1 is the required language = %1
copy common\boblang.zip %1.zip
pkzip %1.zip ..\%1\bob.rc
