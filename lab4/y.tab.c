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
#line 6 "tiger.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "symbol.h" 
#include "errormsg.h"
#include "absyn.h"

int yylex(void); /* function prototype */

A_exp absyn_root;

void yyerror(char *s)
{
 EM_error(EM_tokPos, "%s", s);
 exit(1);
}

#line 85 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    STRING = 259,
    INT = 260,
    COMMA = 261,
    COLON = 262,
    SEMICOLON = 263,
    LPAREN = 264,
    RPAREN = 265,
    LBRACK = 266,
    RBRACK = 267,
    LBRACE = 268,
    RBRACE = 269,
    DOT = 270,
    PLUS = 271,
    MINUS = 272,
    TIMES = 273,
    DIVIDE = 274,
    EQ = 275,
    NEQ = 276,
    LT = 277,
    LE = 278,
    GT = 279,
    GE = 280,
    AND = 281,
    OR = 282,
    ASSIGN = 283,
    ARRAY = 284,
    IF = 285,
    THEN = 286,
    ELSE = 287,
    WHILE = 288,
    FOR = 289,
    TO = 290,
    DO = 291,
    LET = 292,
    IN = 293,
    END = 294,
    OF = 295,
    BREAK = 296,
    NIL = 297,
    FUNCTION = 298,
    VAR = 299,
    TYPE = 300,
    UMINUS = 301
  };
#endif
/* Tokens.  */
#define ID 258
#define STRING 259
#define INT 260
#define COMMA 261
#define COLON 262
#define SEMICOLON 263
#define LPAREN 264
#define RPAREN 265
#define LBRACK 266
#define RBRACK 267
#define LBRACE 268
#define RBRACE 269
#define DOT 270
#define PLUS 271
#define MINUS 272
#define TIMES 273
#define DIVIDE 274
#define EQ 275
#define NEQ 276
#define LT 277
#define LE 278
#define GT 279
#define GE 280
#define AND 281
#define OR 282
#define ASSIGN 283
#define ARRAY 284
#define IF 285
#define THEN 286
#define ELSE 287
#define WHILE 288
#define FOR 289
#define TO 290
#define DO 291
#define LET 292
#define IN 293
#define END 294
#define OF 295
#define BREAK 296
#define NIL 297
#define FUNCTION 298
#define VAR 299
#define TYPE 300
#define UMINUS 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 26 "tiger.y" /* yacc.c:355  */

	int pos;
	int ival;
	string sval;
	A_var var;
	A_exp exp;
	A_expList expList;
	A_dec dec;
	A_decList decList;
	A_fundec fundec;
	A_fundecList fundecList;
	A_namety namety;
	A_nametyList nametyList;
	A_field field;
	A_fieldList fieldList;
	A_efield efield;
	A_efieldList efieldList;
	A_ty ty;

#line 237 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 254 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  40
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   350

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  148

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

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
      45,    46
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    87,    87,    90,    91,    92,    93,    94,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   106,   108,   109,
     110,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   124,   125,   127,   130,   131,   134,   135,   136,
     139,   142,   145,   146,   149,   150,   153,   156,   157,   158,
     161,   162,   163,   166,   169,   170,   173,   174,   177,   178,
     181,   182,   185,   186,   187,   190,   191,   192,   195,   196,
     197,   198
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "STRING", "INT", "COMMA", "COLON",
  "SEMICOLON", "LPAREN", "RPAREN", "LBRACK", "RBRACK", "LBRACE", "RBRACE",
  "DOT", "PLUS", "MINUS", "TIMES", "DIVIDE", "EQ", "NEQ", "LT", "LE", "GT",
  "GE", "AND", "OR", "ASSIGN", "ARRAY", "IF", "THEN", "ELSE", "WHILE",
  "FOR", "TO", "DO", "LET", "IN", "END", "OF", "BREAK", "NIL", "FUNCTION",
  "VAR", "TYPE", "UMINUS", "$accept", "program", "exp", "exps", "seqexp",
  "voidexp", "recorditem", "recorditems", "args", "tyfield", "tyfields",
  "ty", "tydec", "tydecs", "vardec", "fundec", "fundecs", "dec", "decs",
  "lvalue", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301
};
# endif

#define YYPACT_NINF -106

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-106)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     163,     6,   108,  -106,  -106,    57,   163,   163,   163,    23,
      28,  -106,  -106,    54,   292,  -106,  -106,    -6,   163,   103,
     163,     1,     2,  -106,    13,    18,  -106,   248,   165,    31,
      60,    61,    85,    44,  -106,  -106,    49,  -106,    28,    62,
    -106,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,    92,   163,   292,  -106,    59,    87,
     264,    81,  -106,    96,    89,  -106,   163,  -106,   163,   163,
     163,   100,    -5,    90,  -106,  -106,  -106,   121,    38,    38,
    -106,  -106,   315,   315,   315,   315,   315,   315,   325,   304,
     280,  -106,   292,   163,  -106,    76,   163,   115,  -106,  -106,
     231,   292,   211,   120,   124,   163,    -2,  -106,    95,  -106,
    -106,   163,   292,  -106,   163,   163,   122,   125,   118,   113,
     292,  -106,   120,   102,  -106,  -106,   292,   292,   190,   140,
     120,    -4,   163,   133,   145,   163,  -106,  -106,   146,   163,
     292,  -106,  -106,   292,   130,   292,   163,   292
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    68,     5,     4,     0,     0,     0,     0,     0,
      67,    12,    40,     0,     2,     7,     6,     3,     0,     0,
       0,     0,     0,    37,    35,     0,    21,     0,     0,     0,
       0,     0,     0,    54,    62,    63,    60,    64,    65,     0,
       1,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    15,    44,     0,
       0,     0,    19,    42,     0,    39,     0,    38,     0,     0,
       0,     0,     0,     0,    55,    61,    66,     0,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       0,    69,    17,     0,    16,    71,     0,     0,    20,    36,
       8,    10,     0,    49,     0,     0,     0,    14,     0,    70,
      45,     0,    41,    43,     0,     0,     0,    47,     0,     0,
      56,    50,    49,     0,    53,    13,    18,     9,     0,     0,
      49,     0,     0,     0,     0,     0,    46,    48,     0,     0,
      57,    52,    51,    11,     0,    58,     0,    59
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -106,  -106,     0,   -53,  -106,  -106,  -106,    55,    63,  -106,
    -105,  -106,  -106,   126,  -106,  -106,   117,  -106,   119,  -106
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    13,    24,    25,    15,    16,    63,    64,    59,   117,
     118,   124,    33,    34,    35,    36,    37,    38,    39,    17
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      14,   121,   104,   138,    61,    53,    26,    27,    28,    54,
      18,   122,    65,    99,    18,    62,   139,   133,    56,    58,
      60,    66,    55,   105,   108,   137,    29,   123,    67,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    40,    92,    43,    44,    22,    70,
       2,     3,     4,    71,    72,    93,     5,    23,   100,   101,
     102,    30,    31,    32,     6,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,     7,    73,    32,
       8,     9,    30,    58,    10,    91,   112,    94,    11,    12,
      77,    96,    97,    98,     1,   120,     2,     3,     4,   103,
     106,   126,     5,    57,   127,   128,   111,    19,    61,    20,
       6,    21,     1,   116,     2,     3,     4,   119,   131,   129,
       5,   130,   140,     7,   125,   143,     8,     9,     6,   145,
      10,   132,   134,   136,    11,    12,   147,   141,   142,   144,
     146,     7,   113,    75,     8,     9,   110,    76,    10,    74,
     107,     0,    11,    12,     1,     0,     2,     3,     4,     0,
       0,     0,     5,     0,     0,     0,     0,     0,     0,     0,
       6,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,     7,     0,     0,     8,     9,     0,     0,
      10,    69,     0,     0,    11,    12,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,     0,     0,
       0,     0,     0,     0,     0,     0,   135,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,     0,
       0,     0,     0,     0,     0,     0,   115,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,     0,
       0,     0,     0,   114,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    95,     0,     0,    68,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,   109,     0,     0,     0,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50
};

static const yytype_int16 yycheck[] =
{
       0,     3,     7,     7,     3,    11,     6,     7,     8,    15,
       8,    13,    10,    66,     8,    14,    20,   122,    18,    19,
      20,     8,    28,    28,    77,   130,     3,    29,    10,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,     0,    55,    18,    19,     1,    28,
       3,     4,     5,     3,     3,     6,     9,    10,    68,    69,
      70,    43,    44,    45,    17,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    30,     3,    45,
      33,    34,    43,    93,    37,     3,    96,    10,    41,    42,
      38,    20,     6,    14,     1,   105,     3,     4,     5,     9,
      20,   111,     9,    10,   114,   115,    40,     9,     3,    11,
      17,    13,     1,     3,     3,     4,     5,     3,    10,     7,
       9,     6,   132,    30,    39,   135,    33,    34,    17,   139,
      37,    28,    40,     3,    41,    42,   146,    14,     3,     3,
      20,    30,    97,    36,    33,    34,    93,    38,    37,    33,
      39,    -1,    41,    42,     1,    -1,     3,     4,     5,    -1,
      -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    30,    -1,    -1,    33,    34,    -1,    -1,
      37,    36,    -1,    -1,    41,    42,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    -1,    -1,    32,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    12,    -1,    -1,    31,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    12,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     9,    17,    30,    33,    34,
      37,    41,    42,    48,    49,    51,    52,    66,     8,     9,
      11,    13,     1,    10,    49,    50,    49,    49,    49,     3,
      43,    44,    45,    59,    60,    61,    62,    63,    64,    65,
       0,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    11,    15,    28,    49,    10,    49,    55,
      49,     3,    14,    53,    54,    10,     8,    10,    31,    36,
      28,     3,     3,     3,    60,    63,    65,    38,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,     3,    49,     6,    10,    12,    20,     6,    14,    50,
      49,    49,    49,     9,     7,    28,    20,    39,    50,    12,
      55,    40,    49,    54,    32,    35,     3,    56,    57,     3,
      49,     3,    13,    29,    58,    39,    49,    49,    49,     7,
       6,    10,    28,    57,    40,    36,     3,    57,     7,    20,
      49,    14,     3,    49,     3,    49,    20,    49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    50,    50,    51,    51,    51,
      52,    53,    54,    54,    55,    55,    56,    57,    57,    57,
      58,    58,    58,    59,    60,    60,    61,    61,    62,    62,
      63,    63,    64,    64,    64,    65,    65,    65,    66,    66,
      66,    66
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     4,     6,
       4,     8,     1,     5,     4,     3,     4,     3,     6,     3,
       4,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     3,     2,     3,     3,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     0,
       1,     3,     3,     4,     1,     2,     4,     6,     7,     9,
       1,     2,     1,     1,     1,     1,     2,     0,     1,     3,
       4,     4
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
#line 87 "tiger.y" /* yacc.c:1646  */
    {absyn_root=(yyvsp[0].exp);}
#line 1470 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 90 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_VarExp(EM_tokPos,(yyvsp[0].var));}
#line 1476 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 91 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_IntExp(EM_tokPos,(yyvsp[0].ival));}
#line 1482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 92 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_StringExp(EM_tokPos,(yyvsp[0].sval)?(yyvsp[0].sval):"");}
#line 1488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 93 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=(yyvsp[0].exp);}
#line 1494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 94 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=(yyvsp[0].exp);}
#line 1500 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 96 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_IfExp(EM_tokPos,(yyvsp[-2].exp),(yyvsp[0].exp),A_NilExp(EM_tokPos));}
#line 1506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 97 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_IfExp(EM_tokPos,(yyvsp[-4].exp),(yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1512 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 98 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_WhileExp(EM_tokPos,(yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 99 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_ForExp(EM_tokPos,S_Symbol((yyvsp[-6].sval)),(yyvsp[-4].exp),(yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 100 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_BreakExp(EM_tokPos);}
#line 1530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 101 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_LetExp(EM_tokPos,(yyvsp[-3].decList),A_SeqExp(EM_tokPos,(yyvsp[-1].expList)));}
#line 1536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 102 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_LetExp(EM_tokPos,(yyvsp[-2].decList),A_SeqExp(EM_tokPos,NULL));}
#line 1542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 103 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_CallExp(EM_tokPos,S_Symbol((yyvsp[-2].sval)),NULL);}
#line 1548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 104 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_CallExp(EM_tokPos,S_Symbol((yyvsp[-3].sval)),(yyvsp[-1].expList));}
#line 1554 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 106 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_AssignExp(EM_tokPos,(yyvsp[-2].var),(yyvsp[0].exp));}
#line 1560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 108 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_ArrayExp(EM_tokPos,S_Symbol((yyvsp[-5].sval)),(yyvsp[-3].exp),(yyvsp[0].exp));}
#line 1566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 109 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_RecordExp(EM_tokPos,S_Symbol((yyvsp[-2].sval)),NULL);}
#line 1572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 110 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_RecordExp(EM_tokPos,S_Symbol((yyvsp[-3].sval)),(yyvsp[-1].efieldList));}
#line 1578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 112 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp) = A_OpExp(EM_tokPos, A_minusOp, A_IntExp(EM_tokPos, 0), (yyvsp[0].exp));}
#line 1584 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 113 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_OpExp(EM_tokPos,A_plusOp,(yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 114 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_OpExp(EM_tokPos,A_minusOp,(yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 115 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_OpExp(EM_tokPos,A_timesOp,(yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 116 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_OpExp(EM_tokPos,A_divideOp,(yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1608 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 117 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_OpExp(EM_tokPos,A_eqOp,(yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 118 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_OpExp(EM_tokPos,A_neqOp,(yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 119 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_OpExp(EM_tokPos,A_ltOp,(yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 120 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_OpExp(EM_tokPos,A_leOp,(yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 121 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_OpExp(EM_tokPos,A_gtOp,(yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 122 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_OpExp(EM_tokPos,A_geOp,(yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 124 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_IfExp(EM_tokPos,(yyvsp[-2].exp),(yyvsp[0].exp),A_IntExp(EM_tokPos,0));}
#line 1650 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 125 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_IfExp(EM_tokPos,(yyvsp[-2].exp),A_IntExp(EM_tokPos,1),(yyvsp[0].exp));}
#line 1656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 127 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=(yyvsp[0].exp);}
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 130 "tiger.y" /* yacc.c:1646  */
    {(yyval.expList)=A_ExpList((yyvsp[0].exp),NULL);}
#line 1668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 131 "tiger.y" /* yacc.c:1646  */
    {(yyval.expList)=A_ExpList((yyvsp[-2].exp),(yyvsp[0].expList));}
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 134 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_SeqExp(EM_tokPos,NULL);}
#line 1680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 135 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_SeqExp(EM_tokPos,(yyvsp[-1].expList));}
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 136 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_SeqExp(EM_tokPos,NULL);}
#line 1692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 139 "tiger.y" /* yacc.c:1646  */
    {(yyval.exp)=A_NilExp(EM_tokPos);}
#line 1698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 142 "tiger.y" /* yacc.c:1646  */
    {(yyval.efield)=A_Efield(S_Symbol((yyvsp[-2].sval)),(yyvsp[0].exp));}
#line 1704 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 145 "tiger.y" /* yacc.c:1646  */
    {(yyval.efieldList)=A_EfieldList((yyvsp[0].efield),NULL);}
#line 1710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 146 "tiger.y" /* yacc.c:1646  */
    {(yyval.efieldList)=A_EfieldList((yyvsp[-2].efield),(yyvsp[0].efieldList));}
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 149 "tiger.y" /* yacc.c:1646  */
    {(yyval.expList)=A_ExpList((yyvsp[0].exp),NULL);}
#line 1722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 150 "tiger.y" /* yacc.c:1646  */
    {(yyval.expList)=A_ExpList((yyvsp[-2].exp),(yyvsp[0].expList));}
#line 1728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 153 "tiger.y" /* yacc.c:1646  */
    {(yyval.field)=A_Field(EM_tokPos,S_Symbol((yyvsp[-2].sval)),S_Symbol((yyvsp[0].sval)));}
#line 1734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 156 "tiger.y" /* yacc.c:1646  */
    {(yyval.fieldList)=A_FieldList((yyvsp[0].field),NULL);}
#line 1740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 157 "tiger.y" /* yacc.c:1646  */
    {(yyval.fieldList)=A_FieldList((yyvsp[-2].field),(yyvsp[0].fieldList));}
#line 1746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 158 "tiger.y" /* yacc.c:1646  */
    {(yyval.fieldList)=NULL;}
#line 1752 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 161 "tiger.y" /* yacc.c:1646  */
    {(yyval.ty)=A_NameTy(EM_tokPos,S_Symbol((yyvsp[0].sval)));}
#line 1758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 162 "tiger.y" /* yacc.c:1646  */
    {(yyval.ty)=A_ArrayTy(EM_tokPos,S_Symbol((yyvsp[0].sval)));}
#line 1764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 163 "tiger.y" /* yacc.c:1646  */
    {(yyval.ty)=A_RecordTy(EM_tokPos,(yyvsp[-1].fieldList));}
#line 1770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 166 "tiger.y" /* yacc.c:1646  */
    {(yyval.namety)=A_Namety(S_Symbol((yyvsp[-2].sval)),(yyvsp[0].ty));}
#line 1776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 169 "tiger.y" /* yacc.c:1646  */
    {(yyval.nametyList)=A_NametyList((yyvsp[0].namety),NULL);}
#line 1782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 170 "tiger.y" /* yacc.c:1646  */
    {(yyval.nametyList)=A_NametyList((yyvsp[-1].namety),(yyvsp[0].nametyList));}
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 173 "tiger.y" /* yacc.c:1646  */
    {(yyval.dec)=A_VarDec(EM_tokPos,S_Symbol((yyvsp[-2].sval)),NULL,(yyvsp[0].exp));}
#line 1794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 174 "tiger.y" /* yacc.c:1646  */
    {(yyval.dec)=A_VarDec(EM_tokPos,S_Symbol((yyvsp[-4].sval)),S_Symbol((yyvsp[-2].sval)),(yyvsp[0].exp));}
#line 1800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 177 "tiger.y" /* yacc.c:1646  */
    {(yyval.fundec)=A_Fundec(EM_tokPos,S_Symbol((yyvsp[-5].sval)),(yyvsp[-3].fieldList),NULL,(yyvsp[0].exp));}
#line 1806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 178 "tiger.y" /* yacc.c:1646  */
    {(yyval.fundec)=A_Fundec(EM_tokPos,S_Symbol((yyvsp[-7].sval)),(yyvsp[-5].fieldList),S_Symbol((yyvsp[-2].sval)),(yyvsp[0].exp));}
#line 1812 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 181 "tiger.y" /* yacc.c:1646  */
    {(yyval.fundecList)=A_FundecList((yyvsp[0].fundec),NULL);}
#line 1818 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 182 "tiger.y" /* yacc.c:1646  */
    {(yyval.fundecList)=A_FundecList((yyvsp[-1].fundec),(yyvsp[0].fundecList));}
#line 1824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 185 "tiger.y" /* yacc.c:1646  */
    {(yyval.dec)=A_TypeDec(EM_tokPos,(yyvsp[0].nametyList));}
#line 1830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 186 "tiger.y" /* yacc.c:1646  */
    {(yyval.dec)=(yyvsp[0].dec);}
#line 1836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 187 "tiger.y" /* yacc.c:1646  */
    {(yyval.dec)=A_FunctionDec(EM_tokPos,(yyvsp[0].fundecList));}
#line 1842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 190 "tiger.y" /* yacc.c:1646  */
    {(yyval.decList)=A_DecList((yyvsp[0].dec),NULL);}
#line 1848 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 191 "tiger.y" /* yacc.c:1646  */
    {(yyval.decList)=A_DecList((yyvsp[-1].dec),(yyvsp[0].decList));}
#line 1854 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 192 "tiger.y" /* yacc.c:1646  */
    {(yyval.decList)=NULL;}
#line 1860 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 195 "tiger.y" /* yacc.c:1646  */
    {(yyval.var)=A_SimpleVar(EM_tokPos,S_Symbol((yyvsp[0].sval)));}
#line 1866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 196 "tiger.y" /* yacc.c:1646  */
    {(yyval.var)=A_FieldVar(EM_tokPos,(yyvsp[-2].var),S_Symbol((yyvsp[0].sval)));}
#line 1872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 197 "tiger.y" /* yacc.c:1646  */
    {(yyval.var)=A_SubscriptVar(EM_tokPos,(yyvsp[-3].var),(yyvsp[-1].exp));}
#line 1878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 198 "tiger.y" /* yacc.c:1646  */
    {(yyval.var) = A_SubscriptVar(EM_tokPos, A_SimpleVar(EM_tokPos, S_Symbol((yyvsp[-3].sval))), (yyvsp[-1].exp));}
#line 1884 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1888 "y.tab.c" /* yacc.c:1646  */
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
