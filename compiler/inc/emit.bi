''	FreeBASIC - 32-bit BASIC Compiler.
''	Copyright (C) 2004-2005 Andre Victor T. Vicentini (av1ctor@yahoo.com.br)
''
''	This program is free software; you can redistribute it and/or modify
''	it under the terms of the GNU General Public License as published by
''	the Free Software Foundation; either version 2 of the License, or
''	(at your option) any later version.
''
''	This program is distributed in the hope that it will be useful,
''	but WITHOUT ANY WARRANTY; without even the implied warranty of
''	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
''	GNU General Public License for more details.
''
''	You should have received a copy of the GNU General Public License
''	along with this program; if not, write to the Free Software
''	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA.


const EMIT_MAINPROC			= "fb_modulemain"
const EMIT_LOCALPREFIX		= "L"

const EMIT.VAR.OPENCHAR		= 91		'' [
const EMIT.VAR.CLOSECHAR	= 93		'' ]

const REG.MAXCLASSES%		= 2

enum EMITINTREG
	EMIT.INTREG.EDX
	EMIT.INTREG.EDI
	EMIT.INTREG.ESI
	EMIT.INTREG.ECX
	EMIT.INTREG.EBX
	EMIT.INTREG.EAX
end enum

'' section types
enum EMITSECTYPE
	EMIT.SECTYPE.CONST
	EMIT.SECTYPE.DATA
	EMIT.SECTYPE.BSS
	EMIT.SECTYPE.CODE
end enum


''
''
''
declare sub 		emitInit			( )
declare sub 		emitEnd				( )

declare function 	emitOpen			( )
declare sub 		emitClose			( )

declare function 	emitIsKeyword		( text as string ) as integer
declare sub 		emitASM				( s as string )

declare sub 		emitCOMMENT			( s as string )

declare sub 		emitALIGN			( byval bytes as integer )
declare sub 		emitSECTION			( byval section as integer )

declare sub 		emitDATABEGIN		( lname as string )
declare sub 		emitDATA			( litext as string, byval dtype as integer )
declare sub 		emitDATAEND			( )

declare function 	emitGetRegName		( byval dtype as integer, byval dclass as integer, byval reg as integer ) as string
declare function 	emitGetIDXName		( byval lgt as integer, byval ofs as integer, idxname as string, sname as string ) as string

declare function 	emitIsRegPreserved 	( byval dtype as integer, byval dclass as integer, byval reg as integer ) as integer
declare function 	emitGetResultReg 	( byval dtype as integer, byval dclass as integer ) as integer
declare function 	emitGetFreePreservReg( byval dtype as integer, byval dclass as integer ) as integer

declare function 	emitSave			( filename as string ) as integer

declare sub 		emitPROCBEGIN		( byval proc as integer, byval initlabel as integer, byval ispublic as integer )
declare sub 		emitPROCEND			( byval proc as integer, byval bytestopop as integer, byval initlabel as integer, byval exitlabel as integer )
declare function 	emitAllocLocal		( byval lgt as integer ) as string
declare sub 		emitFreeLocal		( byval lgt as integer )
declare function 	emitAllocArg		( byval lgt as integer ) as string
declare sub 		emitFreeArg			( byval lgt as integer )

declare sub 		emitCALL			( pname as string, byval bytestopop as integer, byval ispublic as integer )
declare sub 		emitCALLPTR			( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, byval bytestopop as integer )
declare sub 		emitBRANCHPTR		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer )
declare sub 		emitLABEL			( label as string, byval ispublic as integer )
declare sub 		emitJMP				( label as string, byval ispublic as integer )
declare sub 		emitJLE				( label as string, byval ispublic as integer )
declare sub 		emitRET				( byval bytestopop as integer )
declare sub 		emitPUBLIC			( label as string )

declare sub 		emitBRANCH			( mnemonic as string, label as string, byval ispublic as integer )

declare sub 		emitFXCHG			( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer )

declare sub 		emitMOV		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitSTORE	( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitLOAD	( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )

declare sub 		emitADD		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitSUB		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitMUL		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitDIV		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitINTDIV	( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitMOD		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )

declare sub 		emitSHL		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitSHR		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )

declare sub 		emitAND		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitOR		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitXOR		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitEQV		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitIMP		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )

declare sub 		emitADDROF	( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitDEREF	( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )


declare sub 		emitGT		( rname as string, label as string, _
								  dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitLT		( rname as string, label as string, _
								  dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitEQ		( rname as string, label as string, _
								  dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitNE		( rname as string, label as string, _
								  dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitLE		( rname as string, label as string, _
								  dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitGE		( rname as string, label as string, _
								  dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer, _
			 					  sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )

declare sub 		emitNEG		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer )
declare sub 		emitNOT		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer )
declare sub 		emitABS		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer )
declare sub 		emitSGN		( dname as string, byval ddtype as integer, byval ddclass as integer, byval dtype as integer )

declare sub 		emitPUSH	( sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )
declare sub 		emitPOP		( sname as string, byval sdtype as integer, byval sdclass as integer, byval stype as integer )


declare	sub 		emitDbgLine			( byval lnum as integer, lname as string )

declare	function 	emitGetPos 			( ) as long


declare sub 		hWriteStr			( byval f as integer, byval addtab as integer, s as string )

