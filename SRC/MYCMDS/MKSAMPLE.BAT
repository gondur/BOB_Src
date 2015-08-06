fmake2
resamplw sounds.fil -d11000 -a1 -npo -i BOB

copy /b h\sndtop.g + h\f_sounds.g + h\sndbot.g h\sounds.g

resamplw sounds.fil -d22050 -a1 -no ..\game\samplehi -i BOB
