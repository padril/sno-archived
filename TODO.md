# TODO:

---
## Error Handling
This one is really important

---
## Types
- [ ] Administrative
	- [x] Null
	- [ ] Identifier
- [ ] Ordinal
	- [x] Boolean
	- [x] Countable
		- [x] Integer
		- [x] Rational
	- [ ] Uncountable
		- [x] Real
		- [ ] Complex
- [x] Categorical
	- [x] String
- [ ] Array-like
	- [ ] List
    	- [ ] Lists are created as lists of numbers `1 2 3 4`
	- [ ] Vector/Matrix
    	- [ ] Vectors are created as lists of numbers in square brackets `[1 2 3]`
	- [ ] Lists by default are created in rows. e.g. `1 2 3` creates a rank 1 list.
    - [ ] Vectors are created in columns. e.g. in `[[1 2][3 4]]`, `[1 2]`
	is the only entry in the first row, and then we move down one row to `[3 4]`
	- [ ] To clarify `#1 2 3 = 3`, `#[1 2 3] = 3 1`
    	- [ ] For irregular matrices things get filled in `[1 [2 3]] = [[1 0][2 3]]`
		- [ ] Lists can have vectors as items `#1 [2 3] = 2`
	- [ ] Interval
- [ ] Set
	- [x] Filter
	- [ ] Multiset
		- [ ] Sequence
		- [ ] Function
			- [ ] Derivatives
			- [ ] Integrals
- [ ] Operations
- [ ] interpreter
	- [ ] input stream
		- [ ] figure out notation
		- [ ] tokenizer
		- [ ] text editor? or just in console for now
	- [ ] output stream
		- [ ] dynamic output
		- [ ] graphing capability?
			- [ ] how to show complex numbers, higher dimensional numbers, real numbers
			- [ ] i want to be able to graph the mandlebrot set in less than 50 characters
				``M := {c @ `C : |z_N| < N, z_(i+1) := z_i^2 + c, z_0 := 0}, N -> `inf ``
---
## Example phrases
```a
>>> S := {x @ !C : |x| < 3}
>>> S = (-3, 3)
True
>>> S = [-3, 3)
False
>>> S - 1
(-4, 2)
>>> S - 1 ;= -3 (0.1)
[-3.1, -2.9]
>>> ~ X @ `R : X < 1000000
False	(Note: It would show a probability
		 as it seaches. if i properly program
		 expressions, maybe will show false
		 immediately)
```

---
## Tokens

| Check | Token	| Symbol | Example | Result |
|:---------------------:|-----------------------|:-----:|---------------|-----------|
|						| **CONTROL**			|		|				|			|
| :heavy_check_mark:	| End phrase			| \n	|				|			|
| :x:					| Seperate				| SPACE | 1/3x=1/(3x), 1/3 x=(1/3)x||
| :heavy_check_mark:	| Begin priority		| (		| 2 * (3 + 4)	| 14		|
| :heavy_check_mark:	| End priority			| )		| 				|			|
| :x:					| Variant				| ;		| 2 ; 1 = 2		| True		|
| :x:					| Set default variant	| =;	| =; 0.1		|			|
| :x:					| Default variant		| ;		| 1 ;= 2		| False		|
| :x:					| Over/Between (axis)	| _		| 0_+[1 2 3]	| []		|
| :x:					| Set default over		| =_	| =_ 0			|			|
| :x:					| Default over			| _		| _+[1 2 3]
|						| **DATA**				|		|				|			|
| :heavy_check_mark:	| Rational				| /		| 1/2			|			|
| :heavy_check_mark:	| Decimal				| .		| 1.3			|			|
| :x:					| Begin set				| {		| {1, 2, 3}		|			|
| :x:					| End set				| }		|				|			|
| :x:					| Begin open interval	| (		| (1, 3)		|			|
| :x:					| Begin closed interval	| [		| [1, 6]		|			|
| :x:					| End closed interavl	| ]		| (-5, 0]		|			|
| :x:					| Begin vector			| [		| [1 2]			|			|
| :x:					| End vector			| ]		|				|			|
|						| **OPERATORS**			|		|				|			|
|						| *ARITHMETIC*			|		|				|			|
| :heavy_check_mark:	| Plus (Monad)			| +		| +3			| 3			|
| :x:					| ; Sum	(iterator)		| ;+	| n ; (1, 3) + 2n | 12		|
| :heavy_check_mark:	| Plus (Dyad)			| +		| 1 + 2.5		| 3			|
| :heavy_check_mark:	| Minus (Monad)			| -		| -3			| -3		|
| :x:					| Plus/minus			| +-	| +-3			|			|
| :heavy_check_mark:	| Minus (Dyad)			| -		| 1 - 2.5		| -1		|
| :heavy_check_mark:	| Times					| *		| 1 * 2.5		| 2.5		|
| :x:					| ; Product				| ;*	| n ; (1, 3) * 2n | 2.5		|
| :x:					| Power				    | ^		| 2 ^ 3			| 8			|
| :x:					| ; Square root (/)		| ;^	| ;^9			| 3			|
| :x:					| ; Matrix transpose	| ;^	| ;^[[1 2][3 4]]| [[1 3][2 4]]|
| :x:					| ; Function inverse	| ;^	| ;\^(x^2)		| +-;^x		|
| :x:					| Power				    | ^		| 2 ^ 3			| 8			|
| :x:					| Length			    | #		| #[1 2 3]		| 3			|
| :x:					| ; Cardinality			| ;#	| ;#{1,2,3,...}	| 1			|
| :x:					| Reshape				| #		| 2 2#[1 2 3 4] | [[1 2][3 4]]
| :heavy_check_mark:	| Slash					| /		| 1 / 2.5		| 0.4		|
| :x:					| ; Integer division	| ;/	| 6 / 2.5		| 2			|	
| :x:					| Modulus				| %		| 7 % 3			| 1			|
| :x:					| ; Remainder division	| ;%	| 7 ;% 3		| 2 1		|
| :x:					| Absolute				| \|	| \|-5			| 5			|
| :x:					| ; Signum				| ;\|	| ;\|-5			| -1		|
| :x:					| Union					| \|	| {3,4} \| {1,3}| {3}		|
| :x:					| Intersection			| &		| {1,2} & {3,4} | {1,2,3,4}	|
| :x:					| Set difference		| \\	| {1,2,3} \ {1}	| {2,3}		|
| :x:					| Derivative			| '		| (x^2)'dx		| 2x		|
| :x:					| ; Integral			| ;'	| (x^2);'dx		| 1/3 x^3	|
| :x:					| ; Integral (eval)		| ;'	| [1 2];(x^2)'dx| 7/3		|
|						| *COMPARISON*			|		|				|			|
|						| ; Approx. (tolerance)	| ;=	| 0.2 ; 3 = 3.1	| True		|
|						| ; Approx. (interval)	| ;=	| [1, 3) ; 1 = 1| False		|
| :x:					| Equal				    | =		| 7 = 3 + 4		| True		|
| :x:					| Not equal				| !=	| 7 != 3 + 4	| False		|
| :x:					| Less than				| <		| 7 < 3			| False		|
| :x:					| Greater				| >		| 7 > 3			| True		|
| :x:					| Less than or equal	| \<=	|				|			|
| :x:					| Greater than or equal | >=	|				|			|
|						| *SPECIAL SET*			|		|				|			|
| :x:					| Element of			| @		| 3 @ [1 3 6]	| True		|
| :x:					| ; Index of (origin)	| ;@	| 1 ; 3 @ [3]	| 2			|
| :x:					| Such that				| :		| x/2 : x^2 > 9	| (3, `inf) |
| :x:					| Such that	(for all)	| ,		|				|			|
| :x:					| And Statement			| ,		| 1 - 3, 2 - 3	| -2, -1	|
| :x:					| Etc					| ...	| {0, 1, 2,...} |			|
| :x:					| Print					| \$	| \$ "Hello"	| Hello		|
| :x:					| ; Graph (axes)		| ; \$	| (x,y) ; \$ y = 2x |		|
| :x:					| There exists			| ?		| ? x : x = 3 	| True		|
| :x:					| For all				| ~		| ~ x, x = 3	| False		|
| :x:					| Define / Let			| :=	| x := 3, $x	| 3			|
