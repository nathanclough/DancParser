# DanC Parser 
## Overview

This program parses the Danc Language described below and will output any errors in the input files

## DanC Description 
The DanC programming language is based upon the following grammar (in BNF):  

* P ::= S
* S ::= V:=E | read(V) | write(V) | while C do S od | S;S
* C ::= E < E | E > E | E = E | E <> E | E <= E | E >= E
* E ::= T | E + T | E - T
* T ::= F | T * F | T / F
* F ::= (E) | N | V
* V ::= a | b | … | y | z | aV | bV | … | yV | zV
* N ::= 0 | 1 | … | 8 | 9 | 0N | 1N | … | 8N | 9N

Lexeme Token Pairs for DanC language:

| Lexeme          |  Token
| --------------- | -----------
| :=              | ASSIGN_OP 
| +               |   ADD_OP
| Do              |  KEY_DO
| <               |  LESSER_OP 
| -               |  SUB_OP 
| Od              |  KEY_OD
| >               |  GREATER_OP 
| *               |  MULT_OP
| <variable name> |  IDENT
| =               |  EQUAL_OP
| /               |  DIV_OP
| <integer>       |  INT_LIT
| <>              |  NEQUAL_OP 
| read            |  KEY_READ
| (               |  LEFT_PAREN
| <=              |  LEQUAL_OP
| write           |  KEY_WRITE
| )               |  RIGHT_PAREN
| >=              |  GEQUAL_OP 
| while           |  KEY_WHILE 
| ;               |  SEMICOLON

