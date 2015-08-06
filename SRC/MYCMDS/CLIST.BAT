set /r s:\projects\bob\admin\version\%user%.ver
except (obj\*.* tmp\*.* bob.* install.* demo.*) dir /sb /a-d /a-h %& /[d%DateForUp@%TimeForUp] >m:poo
type m:poo
