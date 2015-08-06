if exist mfcbad\*.*	wipe mfcbad
ren mfc mfcbad
md mfc
md mfc\res
copy mfcbad\*.* mfc\
copy mfcbad\res\*.* mfc\res\
wipe mfcbad

