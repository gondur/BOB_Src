	.386p
	model flat
	ifndef	??version
	?debug	macro
	endm
	endif
	?debug	S "c:\mig\src\meditor\tpaintwl.cpp"
	?debug	T "c:\mig\src\meditor\tpaintwl.cpp"
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
_DATA	segment dword public use32 'DATA'
_DATA	ends
_BSS	segment dword public use32 'BSS'
_BSS	ends
DGROUP	group	_BSS,_DATA
_DATA	segment dword public use32 'DATA'
	align	4
@_$DCI$@TPaintBoxWithWheel@$bctr$qqrp18Classes@TComponent	label	dword
	dd	@@$xt$p18TPaintBoxWithWheel
	dd	1029
	dd	-4
	dd	0
	align	4
@_$ECTJ$@TPaintBoxWithWheel@$bctr$qqrp18Classes@TComponent	label	dword
	dd	0
	dd	-40
	dw	0
	dw	5
	dd	0
	dd	@_$DCI$@TPaintBoxWithWheel@$bctr$qqrp18Classes@TComponent
_DATA	ends
_TEXT	segment dword public use32 'CODE'
	align	4
@TPaintBoxWithWheel@$bctr$qqrp18Classes@TComponent	proc	near
?live1@0:
	push      ebp
	mov       ebp,esp
	add       esp,-44
	push      ebx
	mov       byte ptr [ebp-8],dl
	test      dl,dl
	jle       short @1
	call      __ClassCreate
@1:
@2:
	mov       ebx,ecx
	mov       byte ptr [ebp-41],dl
	mov       dword ptr [ebp-4],eax
	mov       eax,offset @_$ECTJ$@TPaintBoxWithWheel@$bctr$qqrp18Classes@TComponent
	call      @__InitExceptBlockLDTC
?live1@16: ; EBX = Owner
	mov       word ptr [ebp-24],8
	mov       ecx,ebx
	xor       edx,edx
	mov       eax,dword ptr [ebp-4]
	call      @Extctrls@TPaintBox@$bctr$qqrp18Classes@TComponent
	add       dword ptr [ebp-12],12
?live1@32: ; 
	push      offset s@
	call      RegisterWindowMessageA
	mov       edx,dword ptr [ebp-4]
	mov       dword ptr [edx+188],eax
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,dword ptr [ebp-4]
@4:
@3:
	cmp       byte ptr [ebp-41],0
	je        short @5
	call      __AfterConstruction
@5:
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
@TPaintBoxWithWheel@$bctr$qqrp18Classes@TComponent	endp
	align	4
@TPaintBoxWithWheel@WndProc$qqrr17Messages@TMessage	proc	near
?live1@80:
@6:
	push      ebp
	mov       ebp,esp
?live1@96: ; EAX = this, EDX = Message
	mov       ecx,dword ptr [edx]
	cmp       ecx,dword ptr [eax+188]
	jne       short @7
	mov       dword ptr [edx],522
@7:
	call      @Controls@TControl@WndProc$qqrr17Messages@TMessage
?live1@144: ; 
@8:
	pop       ebp
	ret 
@TPaintBoxWithWheel@WndProc$qqrr17Messages@TMessage	endp
	align	4
@TPaintBoxWithWheel@OnMouseWheel$qqrp17Messages@TMessage	proc	near
?live1@160:
	push      ebp
	mov       ebp,esp
@9:
		int		3
@10:
	pop       ebp
	ret 
@TPaintBoxWithWheel@OnMouseWheel$qqrp17Messages@TMessage	endp
_TEXT	ends
_DATA	segment dword public use32 'DATA'
	align	4
$abdeceia	label	dword
	dd	@@TPaintBoxWithWheel@+64
	align	4
@Tpaintwl@@_$DCK$@Tpaintwl@Register$qqrv	label	dword
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	0
	align	4
@Tpaintwl@@_$ECTL$@Tpaintwl@Register$qqrv	label	dword
	dd	0
	dd	-40
	dw	0
	dw	5
	dd	0
	dd	@Tpaintwl@@_$DCK$@Tpaintwl@Register$qqrv
_DATA	ends
_TEXT	segment dword public use32 'CODE'
	align	4
@Tpaintwl@Register$qqrv	proc	near
?live1@208:
@11:
	push      ebp
	mov       ebp,esp
	add       esp,-44
	mov       eax,offset @Tpaintwl@@_$ECTL$@Tpaintwl@Register$qqrv
	call      @__InitExceptBlockLDTC
	mov       edx,dword ptr [$abdeceia]
	lea       eax,dword ptr [ebp-4]
	mov       dword ptr [ebp-44],edx
	mov       edx,offset s@+16
	mov       word ptr [ebp-24],8
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-12]
	mov       eax,dword ptr [eax]
	lea       edx,dword ptr [ebp-44]
	xor       ecx,ecx
	call      @Classes@RegisterComponents$qqrx17System@AnsiStringpxp17System@TMetaClassxi
	dec       dword ptr [ebp-12]
	lea       eax,dword ptr [ebp-4]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
@12:
	mov       esp,ebp
	pop       ebp
	ret 
@Tpaintwl@Register$qqrv	endp
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@System@%SmallString$iuc$31%@$basg$qqrrx27System@%SmallString$iuc$31%	segment virtual
	align	2
@@System@%SmallString$iuc$31%@$basg$qqrrx27System@%SmallString$iuc$31%	proc	near
?live16387@0:
@13:
	push      ebp
	mov       ebp,esp
	push      ebx
	push      esi
?live16387@16: ; EAX = this, EDX = rhs
	cmp       edx,eax
	je        short @20
	mov       cl,byte ptr [edx]
	mov       byte ptr [eax],cl
@15:
	xor       esi,esi
	lea       ecx,dword ptr [eax+1]
	inc       edx
	jmp       short @17
?live16387@64: ; EAX = this, EDX = @temp1, ECX = @temp2, ESI = i
@16:
	mov       bl,byte ptr [edx]
	mov       byte ptr [ecx],bl
@18:
	inc       esi
	inc       ecx
	inc       edx
@17:
	xor       ebx,ebx
	mov       bl,byte ptr [eax]
	cmp       esi,ebx
	jl        short @16
?live16387@96: ; 
@21:
@20:
	pop       esi
	pop       ebx
	pop       ebp
	ret 
@@System@%SmallString$iuc$31%@$basg$qqrrx27System@%SmallString$iuc$31%	endp
@System@%SmallString$iuc$31%@$basg$qqrrx27System@%SmallString$iuc$31%	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
	align	4
@System@@_$DCM$@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv	label	dword
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	@@$xt$p17System@AnsiString
	dd	20
	dd	-8
	dd	0
	dd	@@$xt$p17System@AnsiString
	dd	52
	dd	-8
	dd	0
	align	4
@System@@_$ECTN$@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv	label	dword
	dd	0
	dd	-44
	dw	0
	dw	5
	dd	0
	dd	@System@@_$DCM$@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv
	dw	8
	dw	5
	dd	1
	dd	@System@@_$DCM$@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv+28
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv	segment virtual
	align	2
@@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv	proc	near
?live16388@0:
@22:
	push      ebp
	mov       ebp,esp
	add       esp,-44
	push      ebx
	mov       dword ptr [ebp-8],edx
	mov       ebx,eax
	mov       eax,offset @System@@_$ECTN$@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv
	call      @__InitExceptBlockLDTC
?live16388@16: ; EBX = this
	mov       word ptr [ebp-28],8
	lea       edx,dword ptr [ebx+1]
	lea       eax,dword ptr [ebp-4]
	mov       cl,byte ptr [ebx]
	call      @System@AnsiString@$bctr$qqrpxcuc
	mov       edx,eax
	inc       dword ptr [ebp-16]
	mov       eax,dword ptr [ebp-8]
	call      @System@AnsiString@$basg$qqrrx17System@AnsiString
	mov       eax,dword ptr [ebp-8]
	mov       edx,2
	mov       word ptr [ebp-28],20
	push      eax
	lea       eax,dword ptr [ebp-4]
	dec       dword ptr [ebp-16]
	call      @System@AnsiString@$bdtr$qqrv
	pop       eax
	mov       word ptr [ebp-28],8
	inc       dword ptr [ebp-16]
	mov       edx,dword ptr [ebp-44]
	mov       dword ptr fs:[0],edx
?live16388@32: ; 
@24:
@23:
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
@@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv	endp
@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@System@%SmallString$iuc$64%@$basg$qqrrx27System@%SmallString$iuc$64%	segment virtual
	align	2
@@System@%SmallString$iuc$64%@$basg$qqrrx27System@%SmallString$iuc$64%	proc	near
?live16390@0:
@25:
	push      ebp
	mov       ebp,esp
	push      ebx
	push      esi
?live16390@16: ; EAX = this, EDX = rhs
	cmp       edx,eax
	je        short @32
	mov       cl,byte ptr [edx]
	mov       byte ptr [eax],cl
@27:
	xor       esi,esi
	lea       ecx,dword ptr [eax+1]
	inc       edx
	jmp       short @29
?live16390@64: ; EAX = this, EDX = @temp1, ECX = @temp2, ESI = i
@28:
	mov       bl,byte ptr [edx]
	mov       byte ptr [ecx],bl
@30:
	inc       esi
	inc       ecx
	inc       edx
@29:
	xor       ebx,ebx
	mov       bl,byte ptr [eax]
	cmp       esi,ebx
	jl        short @28
?live16390@96: ; 
@33:
@32:
	pop       esi
	pop       ebx
	pop       ebp
	ret 
@@System@%SmallString$iuc$64%@$basg$qqrrx27System@%SmallString$iuc$64%	endp
@System@%SmallString$iuc$64%@$basg$qqrrx27System@%SmallString$iuc$64%	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
	align	4
@System@@_$DCO$@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv	label	dword
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	@@$xt$p17System@AnsiString
	dd	20
	dd	-8
	dd	0
	dd	@@$xt$p17System@AnsiString
	dd	52
	dd	-8
	dd	0
	align	4
@System@@_$ECTP$@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv	label	dword
	dd	0
	dd	-44
	dw	0
	dw	5
	dd	0
	dd	@System@@_$DCO$@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv
	dw	8
	dw	5
	dd	1
	dd	@System@@_$DCO$@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv+28
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv	segment virtual
	align	2
@@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv	proc	near
?live16391@0:
@34:
	push      ebp
	mov       ebp,esp
	add       esp,-44
	push      ebx
	mov       dword ptr [ebp-8],edx
	mov       ebx,eax
	mov       eax,offset @System@@_$ECTP$@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv
	call      @__InitExceptBlockLDTC
?live16391@16: ; EBX = this
	mov       word ptr [ebp-28],8
	lea       edx,dword ptr [ebx+1]
	lea       eax,dword ptr [ebp-4]
	mov       cl,byte ptr [ebx]
	call      @System@AnsiString@$bctr$qqrpxcuc
	mov       edx,eax
	inc       dword ptr [ebp-16]
	mov       eax,dword ptr [ebp-8]
	call      @System@AnsiString@$basg$qqrrx17System@AnsiString
	mov       eax,dword ptr [ebp-8]
	mov       edx,2
	mov       word ptr [ebp-28],20
	push      eax
	lea       eax,dword ptr [ebp-4]
	dec       dword ptr [ebp-16]
	call      @System@AnsiString@$bdtr$qqrv
	pop       eax
	mov       word ptr [ebp-28],8
	inc       dword ptr [ebp-16]
	mov       edx,dword ptr [ebp-44]
	mov       dword ptr fs:[0],edx
?live16391@32: ; 
@36:
@35:
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
@@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv	endp
@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$p17System@AnsiString	segment virtual
	align	2
@@$xt$p17System@AnsiString	label	dword
	dd	4
	dw	16
	dw	12
	dd	@@$xt$17System@AnsiString
	db	83
	db	121
	db	115
	db	116
	db	101
	db	109
	db	58
	db	58
	db	65
	db	110
	db	115
	db	105
	db	83
	db	116
	db	114
	db	105
	db	110
	db	103
	db	32
	db	42
	db	0
@$xt$p17System@AnsiString	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$17System@AnsiString	segment virtual
	align	2
@@$xt$17System@AnsiString	label	byte
	dd	4
	dw	3
	dw	48
	dd	-1
	dd	3
	dw	68
	dw	72
	dd	0
	dw	0
	dw	0
	dd	0
	dd	1
	dd	1
	dd	@System@AnsiString@$bdtr$qqrv
	dw	3
	dw	76
	db	83
	db	121
	db	115
	db	116
	db	101
	db	109
	db	58
	db	58
	db	65
	db	110
	db	115
	db	105
	db	83
	db	116
	db	114
	db	105
	db	110
	db	103
	db	0
	db	0
	dd	0
	dd	0
	dd	0
@$xt$17System@AnsiString	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$p18TPaintBoxWithWheel	segment virtual
	align	2
@@$xt$p18TPaintBoxWithWheel	label	dword
	dd	4
	dw	144
	dw	12
	dd	@@$xt$18TPaintBoxWithWheel
	db	84
	db	80
	db	97
	db	105
	db	110
	db	116
	db	66
	db	111
	db	120
	db	87
	db	105
	db	116
	db	104
	db	87
	db	104
	db	101
	db	101
	db	108
	db	32
	db	42
	db	0
@$xt$p18TPaintBoxWithWheel	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
@TPaintBoxWithWheel@	segment virtual
	align	2
@@TPaintBoxWithWheel@	label	byte
	dd	0
	dd	0
	dd	@@$xp$18TPaintBoxWithWheel
	dd	0
	dd	0
	dd	0
	dd	@@TPaintBoxWithWheel@+252
	dd	192
	dd	@@Extctrls@TPaintBox@+64
	dd	@System@TObject@AfterConstruction$qqrv
	dd	@System@TObject@BeforeDestruction$qqrv
	dd	@@TPaintBoxWithWheel@Dispatch$qqrpv
	dd	@Controls@TControl@DefaultHandler$qqrpv
	dd	@System@TObject@NewInstance$qqrp17System@TMetaClass
	dd	@System@TObject@FreeInstance$qqrv
	dd	@@TPaintBoxWithWheel@$bdtr$qqrv
	dd	@Classes@TPersistent@AssignTo$qqrp19Classes@TPersistent
	dd	@Controls@TControl@DefineProperties$qqrp14Classes@TFiler
	dd	@Classes@TPersistent@Assign$qqrp19Classes@TPersistent
	dd	@Classes@TComponent@GetChildren$qqrynpqqrp18Classes@TComponent$v
	dd	@Classes@TComponent@GetChildOwner$qqrv
	dd	@Classes@TComponent@GetChildParent$qqrv
	dd	@Classes@TComponent@Loaded$qqrv
	dd	@Controls@TControl@Notification$qqrp18Classes@TComponent18Classes@TOperation
	dd	@Controls@TControl@ReadState$qqrp15Classes@TReader
	dd	@Controls@TControl@SetName$qqrx17System@AnsiString
	dd	@Classes@TComponent@SetChildOrder$qqrp18Classes@TComponenti
	dd	@Controls@TControl@SetParentComponent$qqrp18Classes@TComponent
	dd	@Classes@TComponent@Updating$qqrv
	dd	@Classes@TComponent@Updated$qqrv
	dd	@Classes@TComponent@ValidateRename$qqrp18Classes@TComponentx17System@AnsiStringxt2
	dd	@Classes@TComponent@WriteState$qqrp15Classes@TWriter
	dd	@TPaintBoxWithWheel@$bctr$qqrp18Classes@TComponent
	dd	@Controls@TControl@GetParentComponent$qqrv
	dd	@Controls@TControl@HasParent$qqrv
	dd	@Controls@TControl@ChangeScale$qqrii
	dd	@Controls@TControl@Click$qqrv
	dd	@Controls@TControl@DblClick$qqrv
	dd	@Controls@TControl@DragCanceled$qqrv
	dd	@Controls@TControl@DragOver$qqrp14System@TObjectii19Controls@TDragStater4bool
	dd	@Controls@TControl@DoEndDrag$qqrp14System@TObjectii
	dd	@Controls@TControl@DoStartDrag$qqrrp20Controls@TDragObject
	dd	@Controls@TControl@GetClientOrigin$qqrv
	dd	@Controls@TControl@GetClientRect$qqrv
	dd	@Controls@TControl@GetDeviceContext$qqrrpv
	dd	@Controls@TControl@GetDragImages$qqrv
	dd	@Controls@TControl@GetPalette$qqrv
	dd	@Controls@TControl@GetPopupMenu$qqrv
	dd	@Controls@TControl@MouseDown$qqr21Controls@TMouseButton45System@%Set$t17Classes@Classes_1$iuc$0$iuc$6%ii
	dd	@Controls@TControl@MouseMove$qqr45System@%Set$t17Classes@Classes_1$iuc$0$iuc$6%ii
	dd	@Controls@TControl@MouseUp$qqr21Controls@TMouseButton45System@%Set$t17Classes@Classes_1$iuc$0$iuc$6%ii
	dd	@Controls@TControl@PaletteChanged$qqr4bool
	dd	@Controls@TControl@SetDragMode$qqr18Controls@TDragMode
	dd	@Controls@TControl@SetParent$qqrp20Controls@TWinControl
	dd	@Controls@TControl@SetZOrder$qqr4bool
	dd	@Controls@TControl@VisibleChanging$qqrv
	dd	@TPaintBoxWithWheel@WndProc$qqrr17Messages@TMessage
	dd	@Controls@TControl@DragDrop$qqrp14System@TObjectii
	dd	@Controls@TControl@Invalidate$qqrv
	dd	@Controls@TControl@Repaint$qqrv
	dd	@Controls@TControl@SetBounds$qqriiii
	dd	@Controls@TControl@Update$qqrv
	dd	@Extctrls@TPaintBox@Paint$qqrv
	db	18
	db        84,80,97,105,110,116,66,111,120,87,105,116,104,87,104,101
	db        101,108
@TPaintBoxWithWheel@	ends
_DATA	ends
_DATA	segment dword public use32 'DATA'
@System@TObject@	segment virtual
	align	2
@@System@TObject@	label	byte
	dd	0
	dd	0
	dd	@@$xp$14System@TObject
	dd	0
	dd	0
	dd	0
	dd	@@System@TObject@+64
	dd	4
	dd	0
	dd	@System@TObject@AfterConstruction$qqrv
	dd	@System@TObject@BeforeDestruction$qqrv
	dd	@System@TObject@Dispatch$qqrpv
	dd	@System@TObject@DefaultHandler$qqrpv
	dd	@System@TObject@NewInstance$qqrp17System@TMetaClass
	dd	@System@TObject@FreeInstance$qqrv
	dd	@@System@TObject@$bdtr$qqrv
	db	7
	db        84,79,98,106,101,99,116
@System@TObject@	ends
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@$xp$14System@TObject	segment virtual
	align	2
@@$xp$14System@TObject	label	byte
	db	7
	db	7
	db        84,79,98,106,101,99,116
	dd	@@System@TObject@+64
	dd	0
	dw	0
	db	8
	db        116,112,97,105,110,116,119,108
	dw	0
@$xp$14System@TObject	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xp$18TPaintBoxWithWheel	segment virtual
	align	2
@@$xp$18TPaintBoxWithWheel	label	byte
	db	7
	db	18
	db        84,80,97,105,110,116,66,111,120,87,105,116,104,87,104,101
	db        101,108
	dd	@@TPaintBoxWithWheel@+64
	dd	@$xp$18Extctrls@TPaintBox
	dw	30
	db	8
	db        116,112,97,105,110,116,119,108
	dw	0
@$xp$18TPaintBoxWithWheel	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$18TPaintBoxWithWheel	segment virtual
	align	2
@@$xt$18TPaintBoxWithWheel	label	byte
	dd	192
	dw	3
	dw	48
	dd	0
	dd	183
	dw	68
	dw	84
	dd	0
	dw	0
	dw	0
	dd	0
	dd	13
	dd	13
	dd	@@TPaintBoxWithWheel@$bdtr$qqrv
	dw	3
	dw	88
	db	84
	db	80
	db	97
	db	105
	db	110
	db	116
	db	66
	db	111
	db	120
	db	87
	db	105
	db	116
	db	104
	db	87
	db	104
	db	101
	db	101
	db	108
	db	0
	db	0
	dd	@@$xt$18Extctrls@TPaintBox
	dd	0
	dd	3
	dd	0
	dd	0
	dd	0
@$xt$18TPaintBoxWithWheel	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@TPaintBoxWithWheel@Dispatch$qqrpv	segment virtual
	align	2
@@TPaintBoxWithWheel@Dispatch$qqrpv	proc	near
?live16395@0:
@37:
	push      ebp
	mov       ebp,esp
	mov       ecx,dword ptr [edx]
	sub       ecx,522
	jne       short @38
?live16395@16: ; EAX = this, EDX = Message
	mov       edx,dword ptr [edx]
	call      @TPaintBoxWithWheel@OnMouseWheel$qqrp17Messages@TMessage
@43:
	pop       ebp
	ret 
@38:
	call      @System@TObject@Dispatch$qqrpv
?live16395@48: ; 
@41:
@42:
	pop       ebp
	ret 
@@TPaintBoxWithWheel@Dispatch$qqrpv	endp
@TPaintBoxWithWheel@Dispatch$qqrpv	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
	align	4
@_$ECTQ$@TPaintBoxWithWheel@$bdtr$qqrv	label	dword
	dd	0
	dd	-36
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@TPaintBoxWithWheel@$bdtr$qqrv	segment virtual
	align	2
@@TPaintBoxWithWheel@$bdtr$qqrv	proc	near
?live16396@0:
@44:
	push      ebp
	mov       ebp,esp
	add       esp,-40
	push      ebx
	call      __BeforeDestruction
	mov       byte ptr [ebp-37],dl
	mov       ebx,eax
	mov       eax,offset @_$ECTQ$@TPaintBoxWithWheel@$bdtr$qqrv
	call      @__InitExceptBlockLDTC
	cmp       byte ptr [ebp-37],0
	jl        short @45
	add       dword ptr [ebp-8],13
	sub       dword ptr [ebp-8],12
	xor       edx,edx
	mov       eax,ebx
	call      @@Extctrls@TPaintBox@$bdtr$qqrv
@45:
@46:
	mov       edx,dword ptr [ebp-36]
	mov       dword ptr fs:[0],edx
@48:
@47:
	cmp       byte ptr [ebp-37],0
	jle       short @49
	mov       eax,ebx
	call      __ClassDestroy
@49:
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
@@TPaintBoxWithWheel@$bdtr$qqrv	endp
@TPaintBoxWithWheel@$bdtr$qqrv	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@System@TObject@$bdtr$qqrv	segment virtual
	align	2
@@System@TObject@$bdtr$qqrv	proc	near
?live16399@0:
@50:
	push      ebp
	mov       ebp,esp
	call      __BeforeDestruction
	test      dl,dl
@53:
	test      dl,dl
	jle       short @54
	call      __ClassDestroy
@54:
	pop       ebp
	ret 
@@System@TObject@$bdtr$qqrv	endp
@System@TObject@$bdtr$qqrv	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
	align	4
@Extctrls@@_$DCR$@Extctrls@TPaintBox@$bdtr$qqrv	label	dword
	dd	@@$xt$p18Extctrls@TPaintBox
	dd	1029
	dd	-4
	dd	0
	align	4
@Extctrls@@_$ECTS$@Extctrls@TPaintBox@$bdtr$qqrv	label	dword
	dd	0
	dd	-40
	dw	0
	dw	5
	dd	0
	dd	@Extctrls@@_$DCR$@Extctrls@TPaintBox@$bdtr$qqrv
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@Extctrls@TPaintBox@$bdtr$qqrv	segment virtual
	align	2
@@Extctrls@TPaintBox@$bdtr$qqrv	proc	near
?live16401@0:
@55:
	push      ebp
	mov       ebp,esp
	add       esp,-40
	push      ebx
	call      __BeforeDestruction
	mov       ebx,edx
	mov       dword ptr [ebp-4],eax
	mov       eax,offset @Extctrls@@_$ECTS$@Extctrls@TPaintBox@$bdtr$qqrv
	call      @__InitExceptBlockLDTC
	mov       dword ptr [ebp-12],11
	test      bl,bl
	jl        short @56
	mov       word ptr [ebp-24],8
	sub       dword ptr [ebp-12],11
	xor       edx,edx
	mov       eax,dword ptr [ebp-4]
	call      @Controls@TGraphicControl@$bdtr$qqrv
@56:
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
@57:
	test      bl,bl
	jle       short @58
	mov       eax,dword ptr [ebp-4]
	call      __ClassDestroy
@58:
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
@@Extctrls@TPaintBox@$bdtr$qqrv	endp
@Extctrls@TPaintBox@$bdtr$qqrv	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$p18Extctrls@TPaintBox	segment virtual
	align	2
@@$xt$p18Extctrls@TPaintBox	label	dword
	dd	4
	dw	144
	dw	12
	dd	@@$xt$18Extctrls@TPaintBox
	db	69
	db	120
	db	116
	db	99
	db	116
	db	114
	db	108
	db	115
	db	58
	db	58
	db	84
	db	80
	db	97
	db	105
	db	110
	db	116
	db	66
	db	111
	db	120
	db	32
	db	42
	db	0
@$xt$p18Extctrls@TPaintBox	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$18Extctrls@TPaintBox	segment virtual
	align	2
@@$xt$18Extctrls@TPaintBox	label	byte
	dd	188
	dw	3
	dw	48
	dd	0
	dd	183
	dw	68
	dw	84
	dd	0
	dw	0
	dw	0
	dd	0
	dd	12
	dd	12
	dd	@@Extctrls@TPaintBox@$bdtr$qqrv
	dw	3
	dw	88
	db	69
	db	120
	db	116
	db	99
	db	116
	db	114
	db	108
	db	115
	db	58
	db	58
	db	84
	db	80
	db	97
	db	105
	db	110
	db	116
	db	66
	db	111
	db	120
	db	0
	dd	@@$xt$24Controls@TGraphicControl
	dd	0
	dd	3
	dd	0
	dd	0
	dd	0
@$xt$18Extctrls@TPaintBox	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$24Controls@TGraphicControl	segment virtual
	align	2
@@$xt$24Controls@TGraphicControl	label	byte
	dd	180
	dw	3
	dw	48
	dd	0
	dd	183
	dw	76
	dw	92
	dd	0
	dw	0
	dw	0
	dd	0
	dd	11
	dd	11
	dd	@Controls@TGraphicControl@$bdtr$qqrv
	dw	3
	dw	96
	db	67
	db	111
	db	110
	db	116
	db	114
	db	111
	db	108
	db	115
	db	58
	db	58
	db	84
	db	71
	db	114
	db	97
	db	112
	db	104
	db	105
	db	99
	db	67
	db	111
	db	110
	db	116
	db	114
	db	111
	db	108
	db	0
	db	0
	db	0
	dd	@@$xt$17Controls@TControl
	dd	0
	dd	3
	dd	0
	dd	0
	dd	0
@$xt$24Controls@TGraphicControl	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$17Controls@TControl	segment virtual
	align	2
@@$xt$17Controls@TControl	label	byte
	dd	176
	dw	3
	dw	48
	dd	0
	dd	183
	dw	68
	dw	84
	dd	0
	dw	0
	dw	0
	dd	0
	dd	10
	dd	10
	dd	@Controls@TControl@$bdtr$qqrv
	dw	3
	dw	88
	db	67
	db	111
	db	110
	db	116
	db	114
	db	111
	db	108
	db	115
	db	58
	db	58
	db	84
	db	67
	db	111
	db	110
	db	116
	db	114
	db	111
	db	108
	db	0
	db	0
	dd	@@$xt$18Classes@TComponent
	dd	0
	dd	3
	dd	0
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	92
	dd	@@$xt$17System@AnsiString
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	0
	dd	0
@$xt$17Controls@TControl	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$18Classes@TComponent	segment virtual
	align	2
@@$xt$18Classes@TComponent	label	byte
	dd	32
	dw	3
	dw	48
	dd	0
	dd	183
	dw	68
	dw	84
	dd	0
	dw	0
	dw	0
	dd	0
	dd	5
	dd	5
	dd	@Classes@TComponent@$bdtr$qqrv
	dw	3
	dw	88
	db	67
	db	108
	db	97
	db	115
	db	115
	db	101
	db	115
	db	58
	db	58
	db	84
	db	67
	db	111
	db	109
	db	112
	db	111
	db	110
	db	101
	db	110
	db	116
	db	0
	dd	@@$xt$19Classes@TPersistent
	dd	0
	dd	3
	dd	0
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	8
	dd	@@$xt$17System@AnsiString
	dd	0
	dd	0
@$xt$18Classes@TComponent	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$19Classes@TPersistent	segment virtual
	align	2
@@$xt$19Classes@TPersistent	label	byte
	dd	4
	dw	3
	dw	48
	dd	0
	dd	183
	dw	72
	dw	88
	dd	0
	dw	0
	dw	0
	dd	0
	dd	2
	dd	2
	dd	@@Classes@TPersistent@$bdtr$qqrv
	dw	3
	dw	92
	db	67
	db	108
	db	97
	db	115
	db	115
	db	101
	db	115
	db	58
	db	58
	db	84
	db	80
	db	101
	db	114
	db	115
	db	105
	db	115
	db	116
	db	101
	db	110
	db	116
	db	0
	db	0
	db	0
	db	0
	dd	@@$xt$14System@TObject
	dd	0
	dd	3
	dd	0
	dd	0
	dd	0
@$xt$19Classes@TPersistent	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
	align	4
@Classes@@_$DCT$@Classes@TPersistent@$bdtr$qqrv	label	dword
	dd	@@$xt$p19Classes@TPersistent
	dd	1029
	dd	-4
	dd	0
	align	4
@Classes@@_$ECTU$@Classes@TPersistent@$bdtr$qqrv	label	dword
	dd	0
	dd	-40
	dw	0
	dw	5
	dd	0
	dd	@Classes@@_$DCT$@Classes@TPersistent@$bdtr$qqrv
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@Classes@TPersistent@$bdtr$qqrv	segment virtual
	align	2
@@Classes@TPersistent@$bdtr$qqrv	proc	near
?live16407@0:
@59:
	push      ebp
	mov       ebp,esp
	add       esp,-40
	push      ebx
	call      __BeforeDestruction
	mov       ebx,edx
	mov       dword ptr [ebp-4],eax
	mov       eax,offset @Classes@@_$ECTU$@Classes@TPersistent@$bdtr$qqrv
	call      @__InitExceptBlockLDTC
	mov       dword ptr [ebp-12],1
	test      bl,bl
	jl        short @60
	mov       word ptr [ebp-24],8
	dec       dword ptr [ebp-12]
	xor       edx,edx
	mov       eax,dword ptr [ebp-4]
	call      @@System@TObject@$bdtr$qqrv
@60:
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
@61:
	test      bl,bl
	jle       short @62
	mov       eax,dword ptr [ebp-4]
	call      __ClassDestroy
@62:
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
@@Classes@TPersistent@$bdtr$qqrv	endp
@Classes@TPersistent@$bdtr$qqrv	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$p19Classes@TPersistent	segment virtual
	align	2
@@$xt$p19Classes@TPersistent	label	dword
	dd	4
	dw	144
	dw	12
	dd	@@$xt$19Classes@TPersistent
	db	67
	db	108
	db	97
	db	115
	db	115
	db	101
	db	115
	db	58
	db	58
	db	84
	db	80
	db	101
	db	114
	db	115
	db	105
	db	115
	db	116
	db	101
	db	110
	db	116
	db	32
	db	42
	db	0
@$xt$p19Classes@TPersistent	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$14System@TObject	segment virtual
	align	2
@@$xt$14System@TObject	label	byte
	dd	4
	dw	3
	dw	48
	dd	0
	dd	179
	dw	64
	dw	68
	dd	0
	dw	0
	dw	0
	dd	0
	dd	1
	dd	1
	dd	@@System@TObject@$bdtr$qqrv
	dw	3
	dw	72
	db	83
	db	121
	db	115
	db	116
	db	101
	db	109
	db	58
	db	58
	db	84
	db	79
	db	98
	db	106
	db	101
	db	99
	db	116
	db	0
	dd	0
	dd	0
	dd	0
@$xt$14System@TObject	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
s@	label	byte
	;	s@+0:
	db	"MSWHEEL_ROLLMSG",0
	;	s@+16:
	db	"Samples",0
	align	4
_DATA	ends
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
	?debug	C FB0416526567697374657257696E646F774D6573736167654102000000
	public	@TPaintBoxWithWheel@$bctr$qqrp18Classes@TComponent
	extrn	@Extctrls@TPaintBox@$bctr$qqrp18Classes@TComponent:near
	extrn	RegisterWindowMessageA:near
	extrn	__Exception_list:dword
	extrn	@__InitExceptBlockLDTC:near
	extrn	__ClassCreate:near
	extrn	__AfterConstruction:near
	public	@TPaintBoxWithWheel@WndProc$qqrr17Messages@TMessage
	extrn	@Controls@TControl@WndProc$qqrr17Messages@TMessage:near
	public	@TPaintBoxWithWheel@OnMouseWheel$qqrp17Messages@TMessage
	public	@Tpaintwl@Register$qqrv
	extrn	@Classes@RegisterComponents$qqrx17System@AnsiStringpxp17System@TMetaClassxi:near
	extrn	@System@AnsiString@$bctr$qqrpxc:near
	extrn	@System@AnsiString@$bdtr$qqrv:near
	extrn	@System@AnsiString@$basg$qqrrx17System@AnsiString:near
	extrn	@System@AnsiString@$bctr$qqrpxcuc:near
@@Extctrls@TPaintBox@	equ	@Extctrls@TPaintBox@
	extrn	@Extctrls@TPaintBox@:byte
	extrn	@System@TObject@AfterConstruction$qqrv:near
	extrn	@System@TObject@BeforeDestruction$qqrv:near
	extrn	@Controls@TControl@DefaultHandler$qqrpv:near
	extrn	@System@TObject@NewInstance$qqrp17System@TMetaClass:near
	extrn	@System@TObject@FreeInstance$qqrv:near
	extrn	@Classes@TPersistent@AssignTo$qqrp19Classes@TPersistent:near
	extrn	@Controls@TControl@DefineProperties$qqrp14Classes@TFiler:near
	extrn	@Classes@TPersistent@Assign$qqrp19Classes@TPersistent:near
	extrn	@Classes@TComponent@GetChildren$qqrynpqqrp18Classes@TComponent$v:near
	extrn	@Classes@TComponent@GetChildOwner$qqrv:near
	extrn	@Classes@TComponent@GetChildParent$qqrv:near
	extrn	@Classes@TComponent@Loaded$qqrv:near
	extrn	@Controls@TControl@Notification$qqrp18Classes@TComponent18Classes@TOperation:near
	extrn	@Controls@TControl@ReadState$qqrp15Classes@TReader:near
	extrn	@Controls@TControl@SetName$qqrx17System@AnsiString:near
	extrn	@Classes@TComponent@SetChildOrder$qqrp18Classes@TComponenti:near
	extrn	@Controls@TControl@SetParentComponent$qqrp18Classes@TComponent:near
	extrn	@Classes@TComponent@Updating$qqrv:near
	extrn	@Classes@TComponent@Updated$qqrv:near
	extrn	@Classes@TComponent@ValidateRename$qqrp18Classes@TComponentx17System@AnsiStringxt2:near
	extrn	@Classes@TComponent@WriteState$qqrp15Classes@TWriter:near
	extrn	@Controls@TControl@GetParentComponent$qqrv:near
	extrn	@Controls@TControl@HasParent$qqrv:near
	extrn	@Controls@TControl@ChangeScale$qqrii:near
	extrn	@Controls@TControl@Click$qqrv:near
	extrn	@Controls@TControl@DblClick$qqrv:near
	extrn	@Controls@TControl@DragCanceled$qqrv:near
	extrn	@Controls@TControl@DragOver$qqrp14System@TObjectii19Controls@TDragStater4bool:near
	extrn	@Controls@TControl@DoEndDrag$qqrp14System@TObjectii:near
	extrn	@Controls@TControl@DoStartDrag$qqrrp20Controls@TDragObject:near
	extrn	@Controls@TControl@GetClientOrigin$qqrv:near
	extrn	@Controls@TControl@GetClientRect$qqrv:near
	extrn	@Controls@TControl@GetDeviceContext$qqrrpv:near
	extrn	@Controls@TControl@GetDragImages$qqrv:near
	extrn	@Controls@TControl@GetPalette$qqrv:near
	extrn	@Controls@TControl@GetPopupMenu$qqrv:near
	extrn	@Controls@TControl@MouseDown$qqr21Controls@TMouseButton45System@%Set$t17Classes@Classes_1$iuc$0$iuc$6%ii:near
	extrn	@Controls@TControl@MouseMove$qqr45System@%Set$t17Classes@Classes_1$iuc$0$iuc$6%ii:near
	extrn	@Controls@TControl@MouseUp$qqr21Controls@TMouseButton45System@%Set$t17Classes@Classes_1$iuc$0$iuc$6%ii:near
	extrn	@Controls@TControl@PaletteChanged$qqr4bool:near
	extrn	@Controls@TControl@SetDragMode$qqr18Controls@TDragMode:near
	extrn	@Controls@TControl@SetParent$qqrp20Controls@TWinControl:near
	extrn	@Controls@TControl@SetZOrder$qqr4bool:near
	extrn	@Controls@TControl@VisibleChanging$qqrv:near
	extrn	@Controls@TControl@DragDrop$qqrp14System@TObjectii:near
	extrn	@Controls@TControl@Invalidate$qqrv:near
	extrn	@Controls@TControl@Repaint$qqrv:near
	extrn	@Controls@TControl@SetBounds$qqriiii:near
	extrn	@Controls@TControl@Update$qqrv:near
	extrn	@Extctrls@TPaintBox@Paint$qqrv:near
	extrn	@System@TObject@Dispatch$qqrpv:near
	extrn	@System@TObject@DefaultHandler$qqrpv:near
	extrn	@$xp$18Extctrls@TPaintBox:byte
	extrn	__BeforeDestruction:near
	extrn	__ClassDestroy:near
	extrn	@Controls@TGraphicControl@$bdtr$qqrv:near
	extrn	@Controls@TControl@$bdtr$qqrv:near
	extrn	@Classes@TComponent@$bdtr$qqrv:near
	?debug	D "C:\MIG\SRC\MEDITOR\TPaintWl.h" 10089 43618
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\Bde.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\DB.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\DBTables.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\Mask.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\StdCtrls.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\ExtCtrls.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\Buttons.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\dbctrls.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\commdlg.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\Commdlg.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\CommDlg.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\dialogs.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\forms.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\ctl3d.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\Menus.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\pshpack8.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\prsht.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\Commctrl.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\CommCtrl.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\Imm.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\Imm.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\controls.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\graphics.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\classes.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\sysutils.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\messages.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\iostream.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\dstring.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\_nfile.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\stdio.h" 10089 30349
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\stdlib.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\sysdefs.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\System.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\imm.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\mcx.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winsvc.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winsvc.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winnetwk.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winnetwk.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winreg.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winreg.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winver.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winver.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\wincon.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\wincon.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winnls.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winnls.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winuser.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winuser.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\pshpack1.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\wingdi.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\wingdi.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winerror.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winbase.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winbase.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\stddef.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\string.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\pshpack2.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\poppack.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\pshpack4.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\ctype.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winnt.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winnt.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\windef.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\_defs.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\stdarg.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\excpt.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\windows.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\windows.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\windows.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\vcldb.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\VCL.H" 8781 2048
	?debug	D "c:\mig\src\meditor\tpaintwl.cpp" 10089 43588
	end
