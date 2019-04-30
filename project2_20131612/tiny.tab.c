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
#line 7 "tiny.y" /* yacc.c:339  */

#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
//#include "parse.h"

#define YYSTYPE TreeNode *
static char * savedName; /* for use in assignments */
static int savedLineNo;  /* ditto */
static char * savedValue; /* for use declaration ADD PRJ2 */
static TreeNode * savedTree; /* stores syntax tree for later return */

int yyerror(char * message);
static int yylex(void);

#line 84 "tiny.tab.c" /* yacc.c:339  */

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
   by #include "tiny.tab.h".  */
#ifndef YY_YY_TINY_TAB_H_INCLUDED
# define YY_YY_TINY_TAB_H_INCLUDED
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
    IF = 258,
    ELSE = 259,
    INT = 260,
    VOID = 261,
    WHILE = 262,
    RETURN = 263,
    ID = 264,
    NUM = 265,
    ASSIGN = 266,
    EQ = 267,
    NOTEQ = 268,
    LTET = 269,
    GTET = 270,
    LT = 271,
    GT = 272,
    PLUS = 273,
    MINUS = 274,
    TIMES = 275,
    OVER = 276,
    LPAREN = 277,
    RPAREN = 278,
    LSQBRACKET = 279,
    RSQBRACKET = 280,
    LBRACE = 281,
    RBRACE = 282,
    STARTCOMMENT = 283,
    SEMI = 284,
    COMMA = 285,
    ERROR = 286,
    ENDFILE = 287
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TINY_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 168 "tiny.tab.c" /* yacc.c:358  */

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   112

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  111

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    33,    33,    36,    45,    47,    48,    49,    51,    51,
      60,    62,    60,    71,    72,    74,    74,    84,    85,    87,
      96,    98,   104,   104,   113,   123,   132,   134,   143,   145,
     146,   147,   148,   149,   150,   152,   153,   155,   160,   167,
     173,   176,   181,   186,   188,   193,   193,   202,   208,   210,
     211,   212,   213,   214,   215,   217,   223,   225,   226,   228,
     234,   236,   237,   239,   240,   241,   242,   247,   247,   256,
     257,   259,   268
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "INT", "VOID", "WHILE",
  "RETURN", "ID", "NUM", "ASSIGN", "EQ", "NOTEQ", "LTET", "GTET", "LT",
  "GT", "PLUS", "MINUS", "TIMES", "OVER", "LPAREN", "RPAREN", "LSQBRACKET",
  "RSQBRACKET", "LBRACE", "RBRACE", "STARTCOMMENT", "SEMI", "COMMA",
  "ERROR", "ENDFILE", "$accept", "program", "declaration_list",
  "declaration", "var_declaration", "$@1", "$@2", "$@3", "type_specifier",
  "fun_declaration", "$@4", "params", "param_list", "param", "$@5",
  "compound_stmt", "local_declarations", "statement_list", "statement",
  "expression_stmt", "selection_stmt", "iteration_stmt", "return_stmt",
  "expression", "var", "$@6", "simple_expression", "relop",
  "additive_expression", "addop", "term", "mulop", "factor", "call", "$@7",
  "args", "arg_list", YY_NULLPTR
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
     285,   286,   287
};
# endif

#define YYPACT_NINF -61

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-61)))

#define YYTABLE_NINF -68

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      46,   -61,   -61,   -61,     9,    63,   -61,   -61,     7,   -61,
     -61,   -61,   -17,    -1,    11,    20,   -61,    21,    44,   -61,
      54,    56,    55,    49,   -61,    58,    60,    59,    66,    51,
      62,   -61,   -61,   -61,   -61,    64,    66,   -61,   -61,    72,
       3,    67,   -61,    65,    68,    24,    17,   -61,    -8,   -61,
     -61,   -61,   -61,   -61,   -61,   -61,   -61,    69,    71,   -61,
      42,    53,   -61,   -61,    -8,    -8,   -61,    70,    73,    74,
      77,   -61,    -8,   -61,   -61,   -61,   -61,   -61,   -61,   -61,
     -61,    -8,    -8,   -61,   -61,    -8,    78,    79,   -61,    -8,
      -8,   -61,   -61,   -61,    57,    53,   -61,    14,    14,    80,
     -61,    81,    76,    84,   -61,   -61,   -61,    -8,    14,   -61,
     -61
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,    13,    14,     0,     0,     4,     5,     0,     6,
       1,     3,     8,     0,     0,     0,     9,     0,     0,    11,
      14,     0,     0,    17,    20,     0,    21,     0,     0,     0,
       0,    26,    16,    19,    12,     0,    28,    23,    25,     0,
       0,     8,    34,     0,     0,     0,    44,    66,     0,    24,
      36,    30,    27,    29,    31,    32,    33,     0,    64,    43,
      48,    56,    60,    65,     0,     0,    40,     0,     0,     0,
       0,    35,     0,    53,    54,    49,    52,    50,    51,    57,
      58,     0,     0,    61,    62,     0,     0,     0,    41,     0,
      70,    63,    42,    64,    47,    55,    59,     0,     0,     0,
      72,     0,    69,    37,    39,    46,    68,     0,     0,    71,
      38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -61,   -61,   -61,    87,    75,   -61,   -61,   -61,   -10,   -61,
     -61,   -61,   -61,    82,   -61,    85,   -61,   -61,   -60,   -61,
     -61,   -61,   -61,   -45,   -15,   -61,   -61,   -61,    12,   -61,
      13,   -61,    18,   -61,   -61,   -61,   -61
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    13,    14,    25,     8,     9,
      15,    22,    23,    24,    30,    51,    36,    40,    52,    53,
      54,    55,    56,    57,    58,    68,    59,    81,    60,    82,
      61,    85,    62,    63,    69,   101,   102
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      67,    46,    47,    70,    42,   -15,    43,   -10,    21,    10,
      44,    45,    46,    47,    48,    42,    12,    43,    21,    86,
      87,    44,    45,    46,    47,    48,    39,    92,    16,    31,
      49,    19,    50,    46,    47,    17,    48,   103,   104,   -67,
      31,   -45,    18,    50,    99,   100,    48,     1,   110,     2,
      20,     2,     3,    66,    73,    74,    75,    76,    77,    78,
      79,    80,   109,    -2,     1,    26,    93,    93,     2,     3,
      93,     2,     3,    83,    84,    79,    80,   -18,    27,    28,
      34,    41,    72,    29,   -22,    31,    35,    64,   108,    37,
      65,   -10,    11,    94,     0,    95,    90,    89,    71,    88,
      91,    97,    98,    96,   106,   105,   107,     0,     0,     0,
      33,    38,    32
};

static const yytype_int8 yycheck[] =
{
      45,     9,    10,    48,     1,    22,     3,    24,    18,     0,
       7,     8,     9,    10,    22,     1,     9,     3,    28,    64,
      65,     7,     8,     9,    10,    22,    36,    72,    29,    26,
      27,    10,    29,     9,    10,    24,    22,    97,    98,    22,
      26,    24,    22,    29,    89,    90,    22,     1,   108,     5,
       6,     5,     6,    29,    12,    13,    14,    15,    16,    17,
      18,    19,   107,     0,     1,     9,    81,    82,     5,     6,
      85,     5,     6,    20,    21,    18,    19,    23,    23,    30,
      29,     9,    11,    25,    24,    26,    24,    22,     4,    25,
      22,    24,     5,    81,    -1,    82,    22,    24,    29,    29,
      23,    23,    23,    85,    23,    25,    30,    -1,    -1,    -1,
      28,    36,    27
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     5,     6,    34,    35,    36,    37,    41,    42,
       0,    36,     9,    38,    39,    43,    29,    24,    22,    10,
       6,    41,    44,    45,    46,    40,     9,    23,    30,    25,
      47,    26,    48,    46,    29,    24,    49,    25,    37,    41,
      50,     9,     1,     3,     7,     8,     9,    10,    22,    27,
      29,    48,    51,    52,    53,    54,    55,    56,    57,    59,
      61,    63,    65,    66,    22,    22,    29,    56,    58,    67,
      56,    29,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    60,    62,    20,    21,    64,    56,    56,    29,    24,
      22,    23,    56,    57,    61,    63,    65,    23,    23,    56,
      56,    68,    69,    51,    51,    25,    23,    30,     4,    56,
      51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    36,    38,    37,
      39,    40,    37,    41,    41,    43,    42,    44,    44,    45,
      45,    46,    47,    46,    48,    49,    49,    50,    50,    51,
      51,    51,    51,    51,    51,    52,    52,    53,    53,    54,
      55,    55,    56,    56,    57,    58,    57,    59,    59,    60,
      60,    60,    60,    60,    60,    61,    61,    62,    62,    63,
      63,    64,    64,    65,    65,    65,    65,    67,    66,    68,
      68,    69,    69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     0,     4,
       0,     0,     8,     1,     1,     0,     7,     1,     1,     3,
       1,     2,     0,     5,     4,     2,     0,     2,     0,     1,
       1,     1,     1,     1,     1,     2,     1,     5,     7,     5,
       2,     3,     3,     1,     1,     0,     5,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     0,     5,     1,
       0,     3,     1
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
#line 34 "tiny.y" /* yacc.c:1646  */
    { savedTree = (yyvsp[0]);}
#line 1331 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 37 "tiny.y" /* yacc.c:1646  */
    { YYSTYPE t = (yyvsp[-1]);
                   	 	if (t != NULL)
                   	 		{ while (t->sibling != NULL)
                        		t = t->sibling;
                     		t->sibling = (yyvsp[0]);
                     		(yyval) = (yyvsp[-1]); }
                     	else (yyval) = (yyvsp[0]);
                 	}
#line 1344 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 45 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1350 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 47 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1356 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 48 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1362 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 49 "tiny.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1368 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 51 "tiny.y" /* yacc.c:1646  */
    { savedName = copyString(tokenString);
				   						savedLineNo = lineno; }
#line 1375 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 54 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newDecNode(SimpleK);
                   		(yyval)->attr.name = savedName;
						(yyval)->lineno = savedLineNo;
						if( (yyvsp[-3]) == INT )
							(yyval)->expType = Integer;
                 	}
#line 1386 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 60 "tiny.y" /* yacc.c:1646  */
    { savedName = copyString(tokenString);
				 						savedLineNo = lineno; }
#line 1393 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 62 "tiny.y" /* yacc.c:1646  */
    { savedValue = copyString(tokenString); }
#line 1399 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 64 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newDecNode(ArrayK);
                   		(yyval)->attr.name = savedName;
						(yyval)->lineno = savedLineNo;
						(yyval)->attr.val = atoi(savedValue);
						(yyval)->expType = (yyvsp[-7]);
                 	}
#line 1410 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 71 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1416 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 72 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1422 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 74 "tiny.y" /* yacc.c:1646  */
    { savedName = copyString(tokenString);
					   					savedLineNo = lineno; }
#line 1429 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 77 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newDecNode(FunctionK);
						(yyval)->attr.name = savedName;
						(yyval)->lineno = savedLineNo;
						(yyval)->child[0] = (yyvsp[-2]);
						(yyval)->child[1] = (yyvsp[0]);
					}
#line 1440 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 84 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1446 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 85 "tiny.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1452 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 88 "tiny.y" /* yacc.c:1646  */
    { YYSTYPE t = (yyvsp[-2]);
						if( t != NULL ){
							while( t->sibling != NULL )
								t = t->sibling;
							t->sibling = (yyvsp[0]);
							(yyval) = (yyvsp[-2]);}
						else (yyval) = (yyvsp[0]);
					}
#line 1465 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 96 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1471 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 99 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newDecNode(ParamK);
						(yyval)->attr.name = copyString(tokenString);
						(yyval)->lineno = lineno;
						(yyval)->expType = (yyvsp[-1]);
					}
#line 1481 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 104 "tiny.y" /* yacc.c:1646  */
    { savedName = copyString(tokenString);
				 						savedLineNo = lineno; }
#line 1488 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 107 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newDecNode(ParamK);
						(yyval)->attr.name = savedName;
						(yyval)->lineno = savedLineNo;
						(yyval)->expType = (yyvsp[-4]);
					}
#line 1498 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 114 "tiny.y" /* yacc.c:1646  */
    { YYSTYPE t = (yyvsp[-2]);
						if( t != NULL ){
							while( t->sibling != NULL )
								t = t->sibling;
							t->sibling = (yyvsp[-1]);
							(yyval) = (yyvsp[-2]); }
						else (yyval) = (yyvsp[-1]);
					}
#line 1511 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 124 "tiny.y" /* yacc.c:1646  */
    { YYSTYPE t = (yyvsp[-1]);
							if( t != NULL ){
								while( t->sibling != NULL )
									t = t->sibling;
								t->sibling = (yyvsp[0]);
								(yyval) = (yyvsp[-1]); }
							else (yyval) = (yyvsp[0]);
						}
#line 1524 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 135 "tiny.y" /* yacc.c:1646  */
    { YYSTYPE t = (yyvsp[-1]);
							if( t != NULL ){
								while( t->sibling != NULL )
									t = t->sibling;
								t->sibling = (yyvsp[0]);
								(yyval) = (yyvsp[-1]); }
							else (yyval) = (yyvsp[0]);
						}
#line 1537 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 145 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1543 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 146 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1549 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 147 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1555 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 148 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1561 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 149 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1567 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 150 "tiny.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1573 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 152 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1579 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 153 "tiny.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1585 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 156 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(IfK);
							(yyval)->child[0] = (yyvsp[-2]);
							(yyval)->child[1] = (yyvsp[0]);
						}
#line 1594 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 161 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(IfK);
							(yyval)->child[0] = (yyvsp[-4]);
							(yyval)->child[1] = (yyvsp[-2]);
							(yyval)->child[2] = (yyvsp[0]);
						}
#line 1604 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 168 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(WhileK);
							(yyval)->child[0] = (yyvsp[-2]);
							(yyval)->child[1] = (yyvsp[0]);
						}
#line 1613 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 174 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(ReturnK);
						}
#line 1620 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 177 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(ReturnK);
							(yyval)->child[0] = (yyvsp[-1]);
						}
#line 1628 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 182 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(AssignK);
							(yyval)->child[0] = (yyvsp[-2]);
							(yyval)->child[1] = (yyvsp[0]);
						}
#line 1637 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 186 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1643 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 189 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(IdK);
							(yyval)->attr.name = copyString(tokenString);
							(yyval)->lineno = lineno; 
						}
#line 1652 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 193 "tiny.y" /* yacc.c:1646  */
    { savedName = copyString(tokenString);
						 	savedLineNo = lineno; }
#line 1659 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 196 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(IdK);
							(yyval)->attr.name = savedName;
							(yyval)->lineno = savedLineNo;
							(yyval)->child[0] = (yyvsp[-1]);
						}
#line 1669 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 203 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(OpK);
							(yyval)->child[0] = (yyvsp[-2]);
							(yyval)->child[1] = (yyvsp[0]);
							(yyval)->attr.op = (yyvsp[-1]);
						}
#line 1679 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 208 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1685 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 210 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1691 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 211 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1697 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 212 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1703 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 213 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1709 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 214 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1715 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 215 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1721 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 218 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(OpK);
							(yyval)->child[0] = (yyvsp[-2]);
							(yyval)->child[1] = (yyvsp[0]);
							(yyval)->attr.op = (yyvsp[-1]);
						}
#line 1731 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 223 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1737 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 225 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1743 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 226 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1749 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 229 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(OpK);
							(yyval)->child[0] = (yyvsp[-2]);
							(yyval)->child[1] = (yyvsp[0]);
							(yyval)->attr.op = (yyvsp[-1]);
						}
#line 1759 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 234 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1765 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 236 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1771 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 237 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1777 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 239 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1783 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 240 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1789 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 241 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1795 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 243 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(ConstK);
							(yyval)->attr.val = atoi(tokenString);
						}
#line 1803 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 247 "tiny.y" /* yacc.c:1646  */
    { savedName = copyString(tokenString); 
						    savedLineNo = lineno; }
#line 1810 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 250 "tiny.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(FuncCallK);
							(yyval)->attr.name = savedName;
							(yyval)->lineno = savedLineNo;
							(yyval)->child[0] = (yyvsp[-1]);
						}
#line 1820 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 256 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1826 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 260 "tiny.y" /* yacc.c:1646  */
    { YYSTYPE t = (yyvsp[-2]);
							if( t != NULL ){
								while( t->sibling != NULL )
									t = t->sibling;
								t->sibling = (yyvsp[0]);
								(yyval) = (yyvsp[-2]);}
							else (yyval) = (yyvsp[0]);
						}
#line 1839 "tiny.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 268 "tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1845 "tiny.tab.c" /* yacc.c:1646  */
    break;


#line 1849 "tiny.tab.c" /* yacc.c:1646  */
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
#line 270 "tiny.y" /* yacc.c:1906  */


int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");
  printToken(yychar,tokenString);
  Error = TRUE;
  return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{ return getToken(); }

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}

