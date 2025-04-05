/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    mc_end = 258,                  /* mc_end  */
    mc_data = 259,                 /* mc_data  */
    mc_code = 260,                 /* mc_code  */
    MC_VECTOR = 261,               /* MC_VECTOR  */
    mc_const = 262,                /* mc_const  */
    mc_if = 263,                   /* mc_if  */
    mc_else = 264,                 /* mc_else  */
    mc_for = 265,                  /* mc_for  */
    mc_or = 266,                   /* mc_or  */
    mc_not = 267,                  /* mc_not  */
    mc_ge = 268,                   /* mc_ge  */
    mc_l = 269,                    /* mc_l  */
    mc_di = 270,                   /* mc_di  */
    mc_le = 271,                   /* mc_le  */
    mc_read = 272,                 /* mc_read  */
    mc_display = 273,              /* mc_display  */
    idf = 274,                     /* idf  */
    INTEGER = 275,                 /* INTEGER  */
    FLOAT = 276,                   /* FLOAT  */
    CHAR = 277,                    /* CHAR  */
    STRING = 278,                  /* STRING  */
    pvg = 279,                     /* pvg  */
    sum = 280,                     /* sum  */
    mul = 281,                     /* mul  */
    minus = 282,                   /* minus  */
    PARAO = 283,                   /* PARAO  */
    PARAF = 284,                   /* PARAF  */
    colon = 285,                   /* colon  */
    dot = 286,                     /* dot  */
    DIV = 287,                     /* DIV  */
    eq = 288,                      /* eq  */
    virgule = 289,                 /* virgule  */
    arobase = 290,                 /* arobase  */
    left_bracket = 291,            /* left_bracket  */
    right_bracket = 292,           /* right_bracket  */
    mc_integer = 293,              /* mc_integer  */
    mc_float = 294,                /* mc_float  */
    mc_char = 295,                 /* mc_char  */
    mc_string = 296                /* mc_string  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 13 "parser.y"
 
   int entier;
   float real; 
   char *string;
   char caracter;

#line 112 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
