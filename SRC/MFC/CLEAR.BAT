goto M_%1
:M_
:M_all
del bob.opt bob.ncb *.pdb bob.clw bob.aps
:M_quick
del bob.ncb
copy oldbob.opt bob.opt
