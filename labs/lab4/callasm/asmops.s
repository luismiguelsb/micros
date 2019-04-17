/*
  asmops.s: sum and difference in Assembly.
  
  Copyright (c) 2016 Walter Fetter Lages <w.fetter@ieee.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   You can also obtain a copy of the GNU General Public License
    at <http://www.gnu.org/licenses>.
*/

	.intel_syntax noprefix

	.text
	
	.global	sum
	.global	diff
	.global printt

# int sum(int a,int b)
sum:
	push	ebp
	mov	ebp,esp

	mov	eax,[ebp+8]	# a
	add	eax,[ebp+12]	# b

	pop	ebp
	ret

# int diff(int &a,int &b)
diff:
	push	ebp
	mov	ebp,esp
	push	ebx

	mov	ebx,[ebp+8]	# &a
	mov	eax,[ebx]	# a
	mov	ebx,[ebp+12]	# &b
	sub	eax,[ebx]	# b

	pop	ebx
	pop	ebp
	ret
	
##troca pra maiuscula e printa e tem dois parametros q eh o ponteiro char e o tamanho
printt:
	push	ebp
	mov	ebp,esp
	push	ebx

	mov	ecx,[ebp+8]	# pointer to message to write
	mov	edx,[ebp+12]	# message length
	
loop:	
	mov     eax, [ecx+edx]
	mov 	bx, 0xdf
	and 	al,bl
	mov 	[ecx+edx],eax
	dec 	edx
	cmp     edx,0x00 
	jge	loop
	
	mov 	edx,[ebp+12]

	mov	ebx,1		# file handle (stdout)
	mov	eax,4		# system call number (sys_write)
	int	0x80		# call kernel

	pop	ebx
	pop	ebp
	ret

