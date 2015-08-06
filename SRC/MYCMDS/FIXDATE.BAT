@echo off
dir /sb /[d%_date@%_time,+10000]>%tmp%\tmp_fl.err
echo FOLLOWING FILES FOUND:
type %tmp%\tmp_fl.err
for %i in (@%tmp%\tmp_fl.err) touch %i>NUL
del %tmp%\tmp_fl.err>NUL
