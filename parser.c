/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "symbolTable.h"
	#include <assert.h>
	#include "quads.h"
	
	int yyerror (char* yaccProvidedMessage);
	int alpha_yylex ();
	int inFunction = 0;

	extern int yylineno;
	extern char* yytext;
	extern FILE* yyin;
	extern FILE* out;

	extern struct node* top; // for functions!

#line 86 "parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INTCONST = 259,
    REALCONST = 260,
    STRING = 261,
    IF = 262,
    ELSE = 263,
    WHILE = 264,
    FOR = 265,
    FUNCTION = 266,
    RETURN = 267,
    BREAK = 268,
    CONTINUE = 269,
    AND = 270,
    NOT = 271,
    OR = 272,
    LOCAL = 273,
    TRUE = 274,
    FALSE = 275,
    NIL = 276,
    ASSIGN = 277,
    PLUS = 278,
    MINUS = 279,
    MULTIPLIES = 280,
    DIVIDES = 281,
    MODULUS = 282,
    EQUAL = 283,
    INEQUAL = 284,
    INCREMENT = 285,
    DECREMENT = 286,
    GREATER = 287,
    LESS = 288,
    GREATER_EQUAL = 289,
    LESS_EQUAL = 290,
    LEFT_BRACES = 291,
    RIGHT_BRACES = 292,
    LEFT_BRACKETS = 293,
    RIGHT_BRACKETS = 294,
    LEFT_PARENTHESIS = 295,
    RIGHT_PARENTHESIS = 296,
    SEMICOLON = 297,
    COMMA = 298,
    COLON = 299,
    DOUBLE_COLON = 300,
    DOT = 301,
    DOUBLE_DOT = 302
  };
#endif
/* Tokens.  */
#define ID 258
#define INTCONST 259
#define REALCONST 260
#define STRING 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define FOR 265
#define FUNCTION 266
#define RETURN 267
#define BREAK 268
#define CONTINUE 269
#define AND 270
#define NOT 271
#define OR 272
#define LOCAL 273
#define TRUE 274
#define FALSE 275
#define NIL 276
#define ASSIGN 277
#define PLUS 278
#define MINUS 279
#define MULTIPLIES 280
#define DIVIDES 281
#define MODULUS 282
#define EQUAL 283
#define INEQUAL 284
#define INCREMENT 285
#define DECREMENT 286
#define GREATER 287
#define LESS 288
#define GREATER_EQUAL 289
#define LESS_EQUAL 290
#define LEFT_BRACES 291
#define RIGHT_BRACES 292
#define LEFT_BRACKETS 293
#define RIGHT_BRACKETS 294
#define LEFT_PARENTHESIS 295
#define RIGHT_PARENTHESIS 296
#define SEMICOLON 297
#define COMMA 298
#define COLON 299
#define DOUBLE_COLON 300
#define DOT 301
#define DOUBLE_DOT 302

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 21 "parser.y" /* yacc.c:355  */

	char*			stringValue;
	int				intValue;
	double		realValue;

#line 226 "parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 243 "parser.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   633

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  185

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    97,    97,    98,   101,   102,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   134,   135,   136,   137,   138,   139,   140,   141,   144,
     170,   177,   178,   179,   180,   187,   226,   242,   252,   258,
     259,   260,   261,   264,   265,   266,   269,   270,   273,   276,
     279,   280,   283,   284,   287,   288,   291,   294,   295,   298,
     302,   301,   314,   331,   313,   336,   339,   335,   347,   346,
     359,   360,   361,   362,   363,   367,   366,   378,   382,   381,
     399,   402,   403,   406,   409,   412,   415,   416
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTCONST", "REALCONST", "STRING",
  "IF", "ELSE", "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE",
  "AND", "NOT", "OR", "LOCAL", "TRUE", "FALSE", "NIL", "ASSIGN", "PLUS",
  "MINUS", "MULTIPLIES", "DIVIDES", "MODULUS", "EQUAL", "INEQUAL",
  "INCREMENT", "DECREMENT", "GREATER", "LESS", "GREATER_EQUAL",
  "LESS_EQUAL", "LEFT_BRACES", "RIGHT_BRACES", "LEFT_BRACKETS",
  "RIGHT_BRACKETS", "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", "SEMICOLON",
  "COMMA", "COLON", "DOUBLE_COLON", "DOT", "DOUBLE_DOT", "$accept",
  "program", "stmts", "stmt", "expr", "term", "assignexpr", "primary",
  "lvalue", "member", "call", "callsuffix", "normcall", "methodcall",
  "elist", "elists", "objectdef", "indexed", "indexeds", "indexedelem",
  "block", "$@1", "funcdef", "$@2", "$@3", "$@4", "$@5", "funcblock",
  "$@6", "const", "idlist", "$@7", "ids", "$@8", "ifstmt", "ifprefix",
  "whilestmt", "forstmt", "returnstmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

#define YYPACT_NINF -59

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-59)))

#define YYTABLE_NINF -4

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-4)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,    10,   225,   -59,   -59,   -59,   -59,   -25,   -20,   -15,
      26,   256,   -11,    -5,   332,    40,   -59,   -59,   -59,   332,
       0,     0,   -59,   286,   309,   -59,    41,    48,   378,   -59,
     -59,   -59,   -14,   -59,   -19,   -59,   -59,   -59,   -59,   -59,
     225,   -59,   -59,   -59,   332,   332,   332,   -59,    12,   -59,
     399,   -59,   -59,   567,   -59,    97,    39,     9,   -19,     9,
     -59,   332,    65,    15,    18,    29,   441,    17,   -59,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   -59,   332,   -59,   -59,   332,   332,    71,    72,
     -59,   -59,   -59,   332,   332,    75,    73,   462,   483,    37,
      45,   -59,   -59,    46,   145,   356,   332,   -59,   -59,   -59,
      50,   -59,   -59,    55,    84,   -59,    97,    97,   588,   588,
     588,    13,    13,   598,   598,   598,   598,   -59,   504,    61,
     -59,    63,   525,    64,   -59,   225,   -59,   225,   332,   -59,
     101,    55,   -59,   -59,   332,    65,   -59,   332,   -59,   -59,
     332,   -59,   -59,   -59,   -59,   420,   101,   -59,    66,   546,
     -59,    69,    70,   332,    74,    76,    77,   -59,   -59,   -59,
      79,    77,   113,   -59,   -59,   -59,   225,   -59,   -59,   -59,
     -59,    76,   185,   -59,   -59
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     0,     1,    45,    80,    81,     0,     0,     0,
      75,     0,     0,     0,     0,     0,    83,    84,    82,     0,
       0,     0,    70,    61,     0,    15,     0,     4,     0,    30,
      16,    38,    40,    48,    41,    42,    13,    14,    44,     7,
       0,     8,     9,    10,     0,     0,    61,    72,     0,    97,
       0,    11,    12,    33,    46,    32,     0,    34,     0,    36,
       5,     0,    63,     0,     0,    68,     0,     0,    47,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,     0,    35,    37,     0,    61,     0,     0,
      54,    56,    57,     0,    61,     0,    91,     0,     0,     0,
       0,    76,    96,     0,     0,     0,     0,    60,    64,    65,
       0,    66,    31,    43,    28,    29,    17,    18,    19,    20,
      21,    26,    27,    22,    24,    23,    25,    39,     0,     0,
      49,     0,     0,     0,    51,     0,    93,     0,     0,    73,
      87,     0,    71,     4,     0,    63,    67,    61,    50,    58,
      61,    52,    53,    92,    94,     0,    87,    85,     0,     0,
      62,     0,     0,    61,     0,    90,     0,    69,    55,    59,
       0,     0,     0,    86,    78,    77,     0,    74,    88,     5,
      95,    90,     0,    89,    79
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -59,   -59,   -58,    -2,   -10,   -59,   -59,   -59,    -9,   -59,
       2,   -59,   -59,   -59,   -41,   -28,   -59,     8,   -59,   -59,
     -59,   -59,   -17,   -59,   -59,   -59,   -59,   -48,   -59,   -59,
     -32,   -59,   -54,   -59,   -59,   -59,   -59,   -59,   -59
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   143,    28,    29,    30,    31,    32,    33,
      34,    90,    91,    92,    63,   107,    35,    64,   111,    65,
      36,    60,    37,   100,   156,    48,   140,   175,   179,    38,
     158,   165,   173,   181,    39,    40,    41,    42,    43
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      27,    50,   104,     4,    53,    99,    -3,    67,    83,    55,
       3,    57,    59,    62,    66,    44,    84,    85,    15,    93,
      45,    94,    58,    58,    86,    46,    87,    95,    69,    47,
      70,    51,    88,    89,    97,    98,    62,    52,    96,   103,
      56,    -4,    -4,    54,    68,    26,   129,    86,    -2,    87,
      10,   105,   101,   133,   108,    88,    89,   109,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   110,   127,   130,   131,   128,    62,   134,   138,
      69,   135,    70,   132,    62,   139,    61,   141,    71,    72,
      73,    74,    75,    76,    77,   147,   145,    78,    79,    80,
      81,    70,   149,   150,   157,   152,   161,   166,   106,   162,
     168,   169,    69,   174,    70,   171,   178,   160,   146,   172,
     176,   182,   170,   177,   164,    76,    77,   183,   155,    78,
      79,    80,    81,   153,   159,   154,     0,    62,     0,     0,
      62,     0,     0,     0,     0,     0,     0,     0,     4,     5,
       0,     6,     7,    62,     8,     9,    10,    11,    12,    13,
       0,    14,     0,    15,    16,    17,    18,     0,     0,    19,
       0,     0,     0,     0,   180,    20,    21,     0,     0,     0,
       0,    22,   142,    23,     0,    24,     0,    25,     4,     5,
      26,     6,     7,     0,     8,     9,    10,    11,    12,    13,
       0,    14,     0,    15,    16,    17,    18,     0,     0,    19,
       0,     0,     0,     0,     0,    20,    21,     0,     0,     0,
       0,    22,   184,    23,     0,    24,     0,    25,     4,     5,
      26,     6,     7,     0,     8,     9,    10,    11,    12,    13,
       0,    14,     0,    15,    16,    17,    18,     0,     0,    19,
       0,     0,     0,     0,     0,    20,    21,     0,     0,     4,
       5,    22,     6,    23,     0,    24,     0,    25,     0,     0,
      26,     0,    14,     0,    15,    16,    17,    18,     0,     0,
      19,     0,     0,     0,     0,     0,    20,    21,     0,     4,
       5,     0,     6,     0,    23,     0,    24,     0,    49,     0,
       0,    26,    14,     0,    15,    16,    17,    18,     0,     0,
      19,     0,     4,     5,     0,     6,    20,    21,     0,     0,
      10,     0,    61,     0,    23,    14,    24,    15,    16,    17,
      18,    26,     0,    19,     0,     4,     5,     0,     6,    20,
      21,     0,     0,     0,     0,     0,     0,    23,    14,    24,
      15,    16,    17,    18,    26,     0,    19,     0,     0,     0,
       0,     0,    20,    21,     0,     0,     0,     0,     0,     0,
      23,    69,    24,    70,     0,     0,     0,    26,     0,    71,
      72,    73,    74,    75,    76,    77,     0,     0,    78,    79,
      80,    81,     0,    69,     0,    70,     0,     0,     0,     0,
     144,    71,    72,    73,    74,    75,    76,    77,     0,     0,
      78,    79,    80,    81,    69,     0,    70,     0,     0,     0,
      82,     0,    71,    72,    73,    74,    75,    76,    77,     0,
       0,    78,    79,    80,    81,    69,     0,    70,     0,     0,
       0,   102,     0,    71,    72,    73,    74,    75,    76,    77,
       0,     0,    78,    79,    80,    81,    69,     0,    70,     0,
       0,     0,   163,     0,    71,    72,    73,    74,    75,    76,
      77,     0,     0,    78,    79,    80,    81,    69,     0,    70,
       0,     0,   112,     0,     0,    71,    72,    73,    74,    75,
      76,    77,     0,     0,    78,    79,    80,    81,    69,     0,
      70,     0,     0,   136,     0,     0,    71,    72,    73,    74,
      75,    76,    77,     0,     0,    78,    79,    80,    81,    69,
       0,    70,     0,     0,   137,     0,     0,    71,    72,    73,
      74,    75,    76,    77,     0,     0,    78,    79,    80,    81,
      69,     0,    70,   148,     0,     0,     0,     0,    71,    72,
      73,    74,    75,    76,    77,     0,     0,    78,    79,    80,
      81,    69,     0,    70,   151,     0,     0,     0,     0,    71,
      72,    73,    74,    75,    76,    77,     0,     0,    78,    79,
      80,    81,    69,   167,    70,     0,     0,     0,     0,     0,
      71,    72,    73,    74,    75,    76,    77,     0,     0,    78,
      79,    80,    81,    69,     0,    70,     0,     0,     0,     0,
       0,    71,    72,    69,     0,    70,    76,    77,     0,     0,
      78,    79,    80,    81,     0,     0,    76,    77,     0,     0,
      -4,    -4,    -4,    -4
};

static const yytype_int16 yycheck[] =
{
       2,    11,    60,     3,    14,    46,     0,    24,    22,    19,
       0,    20,    21,    23,    24,    40,    30,    31,    18,    38,
      40,    40,    20,    21,    38,    40,    40,    46,    15,     3,
      17,    42,    46,    47,    44,    45,    46,    42,    40,    56,
      40,    28,    29,     3,     3,    45,    87,    38,     0,    40,
      11,    61,    40,    94,    39,    46,    47,    39,    41,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    43,    83,     3,     3,    86,    87,     3,    42,
      15,     8,    17,    93,    94,    40,    36,    41,    23,    24,
      25,    26,    27,    28,    29,    40,   106,    32,    33,    34,
      35,    17,    41,    40,     3,    41,   147,    41,    43,   150,
      41,    41,    15,    36,    17,    41,     3,   145,   110,    43,
      41,   179,   163,   171,   156,    28,    29,   181,   138,    32,
      33,    34,    35,   135,   144,   137,    -1,   147,    -1,    -1,
     150,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
      -1,     6,     7,   163,     9,    10,    11,    12,    13,    14,
      -1,    16,    -1,    18,    19,    20,    21,    -1,    -1,    24,
      -1,    -1,    -1,    -1,   176,    30,    31,    -1,    -1,    -1,
      -1,    36,    37,    38,    -1,    40,    -1,    42,     3,     4,
      45,     6,     7,    -1,     9,    10,    11,    12,    13,    14,
      -1,    16,    -1,    18,    19,    20,    21,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,    -1,
      -1,    36,    37,    38,    -1,    40,    -1,    42,     3,     4,
      45,     6,     7,    -1,     9,    10,    11,    12,    13,    14,
      -1,    16,    -1,    18,    19,    20,    21,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,     3,
       4,    36,     6,    38,    -1,    40,    -1,    42,    -1,    -1,
      45,    -1,    16,    -1,    18,    19,    20,    21,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,     3,
       4,    -1,     6,    -1,    38,    -1,    40,    -1,    42,    -1,
      -1,    45,    16,    -1,    18,    19,    20,    21,    -1,    -1,
      24,    -1,     3,     4,    -1,     6,    30,    31,    -1,    -1,
      11,    -1,    36,    -1,    38,    16,    40,    18,    19,    20,
      21,    45,    -1,    24,    -1,     3,     4,    -1,     6,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    38,    16,    40,
      18,    19,    20,    21,    45,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    15,    40,    17,    -1,    -1,    -1,    45,    -1,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    32,    33,
      34,    35,    -1,    15,    -1,    17,    -1,    -1,    -1,    -1,
      44,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    15,    -1,    17,    -1,    -1,    -1,
      42,    -1,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    15,    -1,    17,    -1,    -1,
      -1,    42,    -1,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    32,    33,    34,    35,    15,    -1,    17,    -1,
      -1,    -1,    42,    -1,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    15,    -1,    17,
      -1,    -1,    41,    -1,    -1,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    32,    33,    34,    35,    15,    -1,
      17,    -1,    -1,    41,    -1,    -1,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    15,
      -1,    17,    -1,    -1,    41,    -1,    -1,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    32,    33,    34,    35,
      15,    -1,    17,    39,    -1,    -1,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    32,    33,    34,
      35,    15,    -1,    17,    39,    -1,    -1,    -1,    -1,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    32,    33,
      34,    35,    15,    37,    17,    -1,    -1,    -1,    -1,    -1,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35,    15,    -1,    17,    -1,    -1,    -1,    -1,
      -1,    23,    24,    15,    -1,    17,    28,    29,    -1,    -1,
      32,    33,    34,    35,    -1,    -1,    28,    29,    -1,    -1,
      32,    33,    34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    49,    50,     0,     3,     4,     6,     7,     9,    10,
      11,    12,    13,    14,    16,    18,    19,    20,    21,    24,
      30,    31,    36,    38,    40,    42,    45,    51,    52,    53,
      54,    55,    56,    57,    58,    64,    68,    70,    77,    82,
      83,    84,    85,    86,    40,    40,    40,     3,    73,    42,
      52,    42,    42,    52,     3,    52,    40,    56,    58,    56,
      69,    36,    52,    62,    65,    67,    52,    70,     3,    15,
      17,    23,    24,    25,    26,    27,    28,    29,    32,    33,
      34,    35,    42,    22,    30,    31,    38,    40,    46,    47,
      59,    60,    61,    38,    40,    46,    51,    52,    52,    62,
      71,    40,    42,    70,    50,    52,    43,    63,    39,    39,
      43,    66,    41,    41,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    62,
       3,     3,    52,    62,     3,     8,    41,    41,    42,    40,
      74,    41,    37,    51,    44,    52,    65,    40,    39,    41,
      40,    39,    41,    51,    51,    52,    72,     3,    78,    52,
      63,    62,    62,    42,    78,    79,    41,    37,    41,    41,
      62,    41,    43,    80,    36,    75,    41,    75,     3,    76,
      51,    81,    50,    80,    37
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    49,    50,    50,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    53,    53,    53,    53,    53,    53,    53,    53,    54,
      55,    55,    55,    55,    55,    56,    56,    56,    56,    57,
      57,    57,    57,    58,    58,    58,    59,    59,    60,    61,
      62,    62,    63,    63,    64,    64,    65,    66,    66,    67,
      69,    68,    71,    72,    70,    73,    74,    70,    76,    75,
      77,    77,    77,    77,    77,    79,    78,    78,    81,    80,
      80,    82,    82,    83,    84,    85,    86,    86
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     0,     2,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     3,     2,     2,     2,     2,     2,     2,     1,     3,
       1,     1,     1,     3,     1,     1,     2,     2,     1,     3,
       4,     3,     4,     4,     2,     6,     1,     1,     3,     5,
       2,     0,     3,     0,     3,     3,     2,     2,     0,     5,
       0,     4,     0,     0,     8,     0,     0,     7,     0,     4,
       1,     1,     1,     1,     1,     0,     3,     0,     0,     4,
       0,     2,     4,     4,     5,     9,     3,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 97 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "program -> stmts stmt\n");}
#line 1542 "parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 98 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "program -> empty\n");}
#line 1548 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 101 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "stmts -> stmts stmt\n");}
#line 1554 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 102 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "stmts -> empty\n");}
#line 1560 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 105 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "stmt -> expr ;\n");}
#line 1566 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 106 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "stmt -> ifstmt\n");}
#line 1572 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 107 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "stmt -> whilestmt\n");}
#line 1578 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 108 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "stmt -> forstmt\n");}
#line 1584 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 109 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "stmt -> returnstmt\n");}
#line 1590 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 110 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "stmt -> break ;\n");}
#line 1596 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 111 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "stmt -> continue ;\n");}
#line 1602 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 112 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "stmt -> block\n");}
#line 1608 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 113 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "stmt -> funcdef\n");}
#line 1614 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 114 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "stmt -> ;\n");}
#line 1620 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 117 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "expr -> assignexpr\n");}
#line 1626 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 118 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "expr -> expr + expr\n");}
#line 1632 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 119 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "expr -> expr - expr\n");}
#line 1638 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 120 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "expr -> expr * expr\n");}
#line 1644 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 121 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "expr -> expr / expr\n");}
#line 1650 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 122 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "expr -> expr mod expr\n");}
#line 1656 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 123 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "expr -> expr > expr\n");}
#line 1662 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 124 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "expr -> expr >= expr\n");}
#line 1668 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 125 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "expr -> expr < expr\n");}
#line 1674 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 126 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "expr -> expr <= expr\n");}
#line 1680 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 127 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "expr -> expr == expr\n");}
#line 1686 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 128 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "expr -> expr != expr\n");}
#line 1692 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 129 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "expr -> expr AND expr\n");}
#line 1698 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 130 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "expr -> expr OR expr\n");}
#line 1704 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 131 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "expr -> term\n");}
#line 1710 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 134 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "term -> (expr)\n");}
#line 1716 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 135 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "term -> - expr\n");}
#line 1722 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 136 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "term -> (expr)\n");}
#line 1728 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 137 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "term -> ++lvalue\n");}
#line 1734 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 138 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "term -> lvalue++\n");}
#line 1740 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 139 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "term -> --lvalue\n");}
#line 1746 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 140 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "term -> lvalue--\n");}
#line 1752 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 141 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "term -> primary\n");}
#line 1758 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 144 "parser.y" /* yacc.c:1646  */
    {
				int i;
				
				fprintf(stderr, "assignexpr -> lvalue = expr\n");
				
				if ((yyvsp[-2].stringValue)) {
					if (isLibraryFunction((yyvsp[-2].stringValue))) {
						fprintf (stderr, "Error at line %d: cannot overwrite libfunc: %s\n", yylineno, (yyvsp[-2].stringValue));
						exit(-1);
					}
				}

				for (i=0; i <= getScope() && (yyvsp[-2].stringValue); i++) {
					SymbolTableEntry* tmp = lookUp(i,(yyvsp[-2].stringValue));
					if ( tmp && tmp->type == E_USERFUNC) {
						fprintf (stderr, "Error at line %d: cannot redifine user function: %s\n", yylineno, (yyvsp[-2].stringValue));
						exit(-1);
					}
					
				}

				free((yyvsp[-2].stringValue));
				(yyvsp[-2].stringValue) = NULL;
			}
#line 1787 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 171 "parser.y" /* yacc.c:1646  */
    {
				fprintf(stderr, "primary -> lvalue\n");
				if((yyvsp[0].stringValue)) {		
					(yyval.stringValue) = strdup((yyvsp[0].stringValue));
				}
			}
#line 1798 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 177 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "primary -> call\n");}
#line 1804 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 178 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "primary -> objectdef\n");}
#line 1810 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 179 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "primary -> (funcdef)\n");}
#line 1816 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 181 "parser.y" /* yacc.c:1646  */
    {
				fprintf(stderr, "primary -> const\n");
				(yyval.stringValue) = NULL;
			}
#line 1825 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 188 "parser.y" /* yacc.c:1646  */
    {
				SymbolTableEntry* tmp = lookUp(getScope(),yylval.stringValue);
				int i;
				int toBeInserted = 1;
				int localvar = 0;

				if (top_e() != -1) {
					SymbolTableEntry* lvar = lookUp(getScope(), yylval.stringValue);
					if (lvar && lvar->isActive) {
						localvar = 1;
					}
					for (i=1; i<top_e(); i++){ 
						SymbolTableEntry* tmp = lookUp(i, yylval.stringValue);
						if (tmp && !localvar) {
							fprintf(stderr, "Error at line %d: cannot access var: %s\n", yylineno, yylval.stringValue);
							exit (-1);
						}
					}
				}

				for (i=0; i<=getScope(); i++) {
					SymbolTableEntry* tmp1 = lookUp(i, yylval.stringValue);
					if (tmp1 && tmp1->isActive && (tmp1->type==E_USERFUNC)) {
						toBeInserted = 0;
					}
				}
				(yyval.stringValue) = strdup(yylval.stringValue);
				if (!isLibraryFunction(yylval.stringValue) && toBeInserted) {
					if (!tmp) {
						insert(getScope(), yylval.stringValue, yylineno, getScope() == 0 ? E_GLOBAL : E_LOCAL);
					} else if (!tmp->isActive) {
						insert(getScope(), yylval.stringValue, yylineno, getScope() == 0 ? E_GLOBAL : E_LOCAL);
					}
				}


				fprintf(stderr, "lvalue -> ID %s \n", yylval.stringValue);
			}
#line 1868 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 227 "parser.y" /* yacc.c:1646  */
    {
				SymbolTableEntry* tmp = lookUp(getScope(), yylval.stringValue);
				if (isLibraryFunction(yylval.stringValue) && getScope() != 0) {
					fprintf (stderr, "Error at line %d: try to shadow libfunc: %s\n", yylineno, yylval.stringValue);
					exit(-1);
				}
				if (!tmp) {
					insert(getScope(), yylval.stringValue, yylineno, getScope() == 0 ? E_GLOBAL : E_LOCAL);
				}else if (tmp->type == E_LIBFUNC && getScope() != 0) {
					fprintf (stderr, "Error at line %d: cannot redifine library function %s \n", yylineno, yylval.stringValue);
					exit(-1);
				}
				(yyval.stringValue) = strdup(yylval.stringValue);
				fprintf(stderr, "lvalue -> LOCAL ID\n");
			}
#line 1888 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 243 "parser.y" /* yacc.c:1646  */
    {
				SymbolTableEntry* tmp = lookUp(0,yylval.stringValue);
				if (!tmp) {
					fprintf (stderr, "Error at line %d: undefined reference to global variable %s \n", yylineno, yylval.stringValue);
					exit(-1);
				}
				fprintf(stderr, "lvalue -> ::ID\n");
				(yyval.stringValue) = NULL;
			}
#line 1902 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 252 "parser.y" /* yacc.c:1646  */
    {
				fprintf(stderr, "lvalue -> member\n");
				(yyval.stringValue) = NULL;
			}
#line 1911 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 258 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "member -> lvalue.id\n");}
#line 1917 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 259 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "member -> lvalue [expr]\n");}
#line 1923 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 260 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "member -> call.id\n");}
#line 1929 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 261 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "member -> call [expr]\n");}
#line 1935 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 264 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "call -> call (elist)\n");}
#line 1941 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 265 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "call -> lvalue callsuffix\n");}
#line 1947 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 266 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "call -> (functdef) (elist)\n");}
#line 1953 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 269 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "callsuffix -> normcall\n");}
#line 1959 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 270 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "callsuffix -> methodcall\n");}
#line 1965 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 273 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "normcall -> (elist)\n");}
#line 1971 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 276 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "methodcall -> ..id (elist)\n");}
#line 1977 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 279 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "elist -> expr elists\n");}
#line 1983 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 283 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "elists -> ,expr elists\n");}
#line 1989 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 284 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "elists -> empty\n");}
#line 1995 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 287 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "objectdef -> 	[elist]\n");}
#line 2001 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 288 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "objectdef -> [indexed]\n");}
#line 2007 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 291 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "indexed -> indexedelem\n");}
#line 2013 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 294 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "indexeds -> ,indexed\n");}
#line 2019 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 295 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "indexeds -> empty\n");}
#line 2025 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 298 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "indexdelem -> {expr : expr}\n");}
#line 2031 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 302 "parser.y" /* yacc.c:1646  */
    {
				scopeUp();
			}
#line 2039 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 306 "parser.y" /* yacc.c:1646  */
    {
				deactivateScope (getScope());
				scopeDown();
				fprintf(stderr, "block -> [stmts] \n");
			}
#line 2049 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 314 "parser.y" /* yacc.c:1646  */
    {
				SymbolTableEntry* tmp = lookUp(getScope(), yylval.stringValue);
				if (isLibraryFunction(yylval.stringValue)) {
					fprintf (stderr, "Error at line %d: cannot overwrite libfunc: %s\n", yylineno, yylval.stringValue);
					exit(-1);
				}
				if (!tmp) {
					insert(getScope(), yylval.stringValue, yylineno, E_USERFUNC);
				} else if (!tmp->isActive) {
					insert(getScope(), yylval.stringValue, yylineno, E_USERFUNC);
				} else {

					fprintf (stderr, "Error at line %d: cannot redifine var: %s\n", yylineno, yylval.stringValue);
					exit(-1);
				}

			}
#line 2071 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 331 "parser.y" /* yacc.c:1646  */
    {scopeUp();}
#line 2077 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 332 "parser.y" /* yacc.c:1646  */
    {
				fprintf(stderr, "funcdef -> function id (idlist) funcblock\n" );
			}
#line 2085 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 336 "parser.y" /* yacc.c:1646  */
    {
				insert(getScope(), getAFunctionName(), yylineno, E_USERFUNC);
			}
#line 2093 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 339 "parser.y" /* yacc.c:1646  */
    {scopeUp();}
#line 2099 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 340 "parser.y" /* yacc.c:1646  */
    {
				
				fprintf(stderr, "block -> function (idlist) funcblock  \n");
			}
#line 2108 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 347 "parser.y" /* yacc.c:1646  */
    {
				push(getScope());
			}
#line 2116 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 351 "parser.y" /* yacc.c:1646  */
    {
				deactivateScope (getScope());
				scopeDown();
				pop();
				fprintf(stderr, "funcblock -> [stmts] \n");
			}
#line 2127 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 359 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "const -> intconst\n");}
#line 2133 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 360 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "const -> string\n");}
#line 2139 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 361 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "const -> nil\n");}
#line 2145 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 362 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "const -> true\n");}
#line 2151 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 363 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "const -> false\n");}
#line 2157 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 367 "parser.y" /* yacc.c:1646  */
    {
				SymbolTableEntry* t = insert(getScope(), yylval.stringValue, yylineno, E_FORMAL);
				if(isLibraryFunction(yylval.stringValue)){
					fprintf (stderr, "Error at line %d: formal shadows libfunc: %s\n", yylineno, yylval.stringValue);
					exit(-1);
				}
			}
#line 2169 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 374 "parser.y" /* yacc.c:1646  */
    {
				fprintf(stderr, "idlist -> ID ids\n"); 

			}
#line 2178 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 378 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "idlist -> empty\n");}
#line 2184 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 382 "parser.y" /* yacc.c:1646  */
    {
				SymbolTableEntry* tmp = lookUp(getScope(),yylval.stringValue);
				if(isLibraryFunction(yylval.stringValue)){
					fprintf (stderr, "Error at line %d: formal shadows libfunc: %s\n", yylineno, yylval.stringValue);
					exit(-1);
				}
				if(tmp && tmp->isActive){
					fprintf (stderr, "Error at line %d: formal redeclaration of var: %s\n", yylineno, yylval.stringValue);
					exit(-1);
				}
				SymbolTableEntry* t = insert(getScope(), yylval.stringValue, yylineno, E_FORMAL);
				assert(t);
			}
#line 2202 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 396 "parser.y" /* yacc.c:1646  */
    {
				fprintf(stderr, "ids -> COMMA ID ids\n");
			}
#line 2210 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 399 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "ids -> empty\n");}
#line 2216 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 402 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "ifstmt -> ifprefix stmt\n");}
#line 2222 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 403 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "ifstmt -> ifprefix stmt ELSE stmt\n");}
#line 2228 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 406 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "ifprefix -> IF (expr)\n");}
#line 2234 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 409 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "whilestmt -> WHILE (expr) stmt\n");}
#line 2240 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 412 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "forstmt -> FOR (elist; expr; elist) stmt\n");}
#line 2246 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 415 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "returnstmt -> return expr;\n");}
#line 2252 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 416 "parser.y" /* yacc.c:1646  */
    {fprintf(stderr, "returnstmt -> return; \n");}
#line 2258 "parser.c" /* yacc.c:1646  */
    break;


#line 2262 "parser.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 418 "parser.y" /* yacc.c:1906  */


int yyerror (char* yaccProvidedMessage) {
	fprintf(stderr, "%s: at line %d, before token %s\n", yaccProvidedMessage, yylineno, yytext);
	fprintf(stderr, "INPUT NOT VALID\n");
	//exit(-1);
}

int main (int argc, char** argv) {
	out = fopen("lex.log", "w");
	if (argc > 1) {
		if (!(yyin = fopen(argv[1], "r"))) {
			fprintf(stderr, "Cannot read file: %s \n", argv[1]);
			return 1;
		}

	}else 
		yyin = stdin;
	init();
	yyparse();
	printSymbolTable();
	return 0;
}
