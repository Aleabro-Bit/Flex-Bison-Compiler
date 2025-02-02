/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "helper.h"
/*TODO: RETURN, SCOPE SISTEMARE IL PARSER */
int yydebug = 0;
extern FILE *yyin;
extern int yylineno;

void print_val(val_t val);

int yylex();

#line 87 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_STEP = 3,                       /* STEP  */
  YYSYMBOL_TO = 4,                         /* TO  */
  YYSYMBOL_FROM = 5,                       /* FROM  */
  YYSYMBOL_WHEN = 6,                       /* WHEN  */
  YYSYMBOL_OTHERWISE = 7,                  /* OTHERWISE  */
  YYSYMBOL_WHETHER = 8,                    /* WHETHER  */
  YYSYMBOL_RETURN = 9,                     /* RETURN  */
  YYSYMBOL_DEFINE = 10,                    /* DEFINE  */
  YYSYMBOL_UNTIL = 11,                     /* UNTIL  */
  YYSYMBOL_EOL = 12,                       /* EOL  */
  YYSYMBOL_THEN = 13,                      /* THEN  */
  YYSYMBOL_AND = 14,                       /* AND  */
  YYSYMBOL_OR = 15,                        /* OR  */
  YYSYMBOL_NOT = 16,                       /* NOT  */
  YYSYMBOL_PLUS = 17,                      /* PLUS  */
  YYSYMBOL_MINUS = 18,                     /* MINUS  */
  YYSYMBOL_MUL = 19,                       /* MUL  */
  YYSYMBOL_DIV = 20,                       /* DIV  */
  YYSYMBOL_POW = 21,                       /* POW  */
  YYSYMBOL_ASSIGN = 22,                    /* ASSIGN  */
  YYSYMBOL_ABS = 23,                       /* ABS  */
  YYSYMBOL_NUM = 24,                       /* NUM  */
  YYSYMBOL_BINARY = 25,                    /* BINARY  */
  YYSYMBOL_ROMAN = 26,                     /* ROMAN  */
  YYSYMBOL_STR = 27,                       /* STR  */
  YYSYMBOL_FUNC = 28,                      /* FUNC  */
  YYSYMBOL_DATA_TYPE = 29,                 /* DATA_TYPE  */
  YYSYMBOL_ID = 30,                        /* ID  */
  YYSYMBOL_CMP = 31,                       /* CMP  */
  YYSYMBOL_UMINUS = 32,                    /* UMINUS  */
  YYSYMBOL_33_ = 33,                       /* ';'  */
  YYSYMBOL_34_ = 34,                       /* '['  */
  YYSYMBOL_35_ = 35,                       /* ']'  */
  YYSYMBOL_36_ = 36,                       /* ':'  */
  YYSYMBOL_37_ = 37,                       /* '{'  */
  YYSYMBOL_38_ = 38,                       /* '}'  */
  YYSYMBOL_39_ = 39,                       /* '('  */
  YYSYMBOL_40_ = 40,                       /* ')'  */
  YYSYMBOL_41_ = 41,                       /* ','  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_START = 43,                     /* START  */
  YYSYMBOL_stmts = 44,                     /* stmts  */
  YYSYMBOL_stmt = 45,                      /* stmt  */
  YYSYMBOL_flow = 46,                      /* flow  */
  YYSYMBOL_declare = 47,                   /* declare  */
  YYSYMBOL_init = 48,                      /* init  */
  YYSYMBOL_assignment = 49,                /* assignment  */
  YYSYMBOL_whether = 50,                   /* whether  */
  YYSYMBOL_when = 51,                      /* when  */
  YYSYMBOL_from = 52,                      /* from  */
  YYSYMBOL_condition = 53,                 /* condition  */
  YYSYMBOL_expr = 54,                      /* expr  */
  YYSYMBOL_value = 55,                     /* value  */
  YYSYMBOL_list = 56,                      /* list  */
  YYSYMBOL_explist = 57,                   /* explist  */
  YYSYMBOL_symlist = 58,                   /* symlist  */
  YYSYMBOL_return = 59,                    /* return  */
  YYSYMBOL_ufunction = 60,                 /* ufunction  */
  YYSYMBOL_funcall = 61                    /* funcall  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   338

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  141

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      39,    40,     2,     2,    41,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    36,    33,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
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
static const yytype_uint8 yyrline[] =
{
       0,    50,    50,    51,    52,    53,    54,    57,    62,    63,
      69,    72,    73,    74,    75,    76,    79,    80,    81,    83,
      96,    97,    99,   101,   102,   105,   106,   110,   118,   119,
     120,   121,   122,   123,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   136,   137,   138,   139,   140,   141,
     142,   144,   145,   148,   149,   151,   152,   154,   156,   157,
     159,   160
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "STEP", "TO", "FROM",
  "WHEN", "OTHERWISE", "WHETHER", "RETURN", "DEFINE", "UNTIL", "EOL",
  "THEN", "AND", "OR", "NOT", "PLUS", "MINUS", "MUL", "DIV", "POW",
  "ASSIGN", "ABS", "NUM", "BINARY", "ROMAN", "STR", "FUNC", "DATA_TYPE",
  "ID", "CMP", "UMINUS", "';'", "'['", "']'", "':'", "'{'", "'}'", "'('",
  "')'", "','", "$accept", "START", "stmts", "stmt", "flow", "declare",
  "init", "assignment", "whether", "when", "from", "condition", "expr",
  "value", "list", "explist", "symlist", "return", "ufunction", "funcall", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-43)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-45)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -43,   133,   -43,     0,   -28,   -29,    16,   279,    23,   -43,
     279,   279,   -43,   -43,   -43,   -43,    18,    25,    -7,   261,
     279,    48,    33,   165,   -43,   -43,   -43,   -43,   -43,   223,
     -43,   -43,   -43,    64,    40,   -43,    54,   244,   227,   244,
      38,   302,   -43,    46,   -43,   196,   279,    67,   279,   279,
     -43,    22,    55,     6,   -43,   200,   -43,   279,   279,   279,
     279,   279,   -43,    94,   244,   244,    -4,   307,    62,    30,
     -43,     8,   -43,    65,   279,   -43,   223,    68,   279,   -43,
     -43,   -43,    -6,    -6,   -43,   -43,    -6,   279,     4,   -12,
      75,   244,   244,    72,   279,   100,   101,    76,    81,    73,
     -43,   223,   -43,   -43,    61,   -43,     4,     4,   227,   223,
      85,    86,    91,   227,    89,   279,    90,   244,    92,   -43,
      97,   227,   161,   -43,    37,   227,   -43,    98,    93,   -43,
     102,   -43,   227,   116,   106,    96,   -43,   109,   227,   110,
     -43
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,    44,     0,     6,
      44,    44,    45,    46,    47,    49,     0,     0,    48,    44,
      44,     0,     0,    44,    11,    12,    16,    17,    18,    15,
      42,    50,    14,     0,    43,     5,     0,    44,    44,    44,
      48,     0,    43,     0,    40,     0,    44,    21,    44,    44,
      51,    53,     0,     0,     3,    44,     9,    44,    44,    44,
      44,    44,     4,     0,    44,    44,     0,    33,     0,     0,
      57,     0,    39,     0,    44,    19,    22,     0,    44,    52,
      41,     7,    34,    35,    36,    37,    38,    44,    31,     0,
      33,    44,    44,     0,    44,     0,     0,    55,     0,     0,
      61,    20,    60,    54,     0,    32,    29,    30,    44,    28,
       0,     0,     0,    44,     0,    44,     0,    44,     0,    56,
       0,    44,     0,    25,     0,    44,    59,     0,     0,    26,
       0,    58,    44,    23,     0,     0,    27,     0,    44,     0,
      24
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -43,   -43,   -22,   -43,   -43,   111,   -43,   -43,   -43,   -43,
     -43,   -30,    10,   -43,   -43,   -42,    43,   -43,   -43,    -1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    21,    22,    23,    24,    75,    25,    26,    27,
      28,    66,    29,    30,    31,    52,    99,    32,    33,    42
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      34,    56,    91,    92,    73,    37,    36,    77,    38,    69,
      91,    92,    35,    59,    60,    48,    68,    41,    91,    92,
      44,    45,    34,    57,    58,    59,    60,    61,   105,    51,
      53,    93,    49,    81,    88,    89,   103,    34,    97,    57,
      58,    59,    60,    61,    91,    92,    80,    67,    98,    67,
      39,    91,    92,    43,    34,    47,    51,    46,    76,    51,
      54,   106,   107,    78,   115,    96,    55,    82,    83,    84,
      85,    86,   129,   -13,    67,    90,    62,    49,    57,    58,
      59,    60,    61,    17,   101,    71,   116,   124,    51,    74,
      79,   120,    57,    58,    59,    60,    61,   104,    87,   127,
      95,    67,    67,   130,   109,   100,    94,    34,   102,   108,
     134,   110,    34,   114,   111,    80,   139,   112,   113,   117,
      34,    97,   118,   135,    34,   122,   121,    67,   123,   125,
     132,    34,   137,     2,     3,   126,   131,    34,     4,     5,
     133,     6,     7,     8,   136,     9,   138,    63,   140,     0,
     -44,    10,   -44,   -44,   -44,   119,    11,    12,    13,    14,
      15,    16,    17,    18,     0,     0,   -44,    19,     0,     0,
       4,     5,    20,     6,     7,     0,     0,   -10,    57,    58,
      59,    60,    61,    10,     0,     0,     0,     0,    11,    12,
      13,    14,    15,    16,    17,    18,   128,     0,     0,    19,
       0,     0,     0,   -10,    20,     4,     5,     0,     6,     7,
       0,     0,    -8,    57,    58,    59,    60,    61,    10,    72,
       0,     0,     0,    11,    12,    13,    14,    15,    16,    17,
      18,     0,     4,     5,    19,     6,     7,     0,    -8,    20,
      57,    58,    59,    60,    61,    10,     0,     0,     0,     0,
      11,    12,    13,    14,    15,    16,    17,    18,     0,     0,
      64,    19,    10,     0,     0,     0,    20,    11,    12,    13,
      14,    15,    16,     0,    40,     0,     0,     0,    19,    10,
       0,     0,     0,    65,    11,    12,    13,    14,    15,    16,
       0,    40,     0,     0,     0,    19,    50,    10,     0,     0,
      20,     0,    11,    12,    13,    14,    15,    16,     0,    40,
       0,     0,     0,    19,     0,     0,     0,     0,    20,    57,
      58,    59,    60,    61,    57,    58,    59,    60,    61,     0,
       0,     0,     0,     0,     0,    70,     0,     0,    94
};

static const yytype_int16 yycheck[] =
{
       1,    23,    14,    15,    46,    34,    34,    49,    37,    39,
      14,    15,    12,    19,    20,    22,    38,     7,    14,    15,
      10,    11,    23,    17,    18,    19,    20,    21,    40,    19,
      20,    35,    39,    55,    64,    65,    78,    38,    30,    17,
      18,    19,    20,    21,    14,    15,    40,    37,    40,    39,
      34,    14,    15,    30,    55,    30,    46,    39,    48,    49,
      12,    91,    92,    41,     3,    35,    33,    57,    58,    59,
      60,    61,    35,    33,    64,    65,    12,    39,    17,    18,
      19,    20,    21,    29,    74,    39,   108,   117,    78,    22,
      35,   113,    17,    18,    19,    20,    21,    87,     4,   121,
      38,    91,    92,   125,    94,    40,    31,   108,    40,    37,
     132,    11,   113,    40,    13,    40,   138,    41,    37,    34,
     121,    30,    36,     7,   125,   115,    37,   117,    38,    37,
      37,   132,    36,     0,     1,    38,    38,   138,     5,     6,
      38,     8,     9,    10,    38,    12,    37,    36,    38,    -1,
      17,    18,    19,    20,    21,   112,    23,    24,    25,    26,
      27,    28,    29,    30,    -1,    -1,    33,    34,    -1,    -1,
       5,     6,    39,     8,     9,    -1,    -1,    12,    17,    18,
      19,    20,    21,    18,    -1,    -1,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    30,    35,    -1,    -1,    34,
      -1,    -1,    -1,    38,    39,     5,     6,    -1,     8,     9,
      -1,    -1,    12,    17,    18,    19,    20,    21,    18,    23,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      30,    -1,     5,     6,    34,     8,     9,    -1,    38,    39,
      17,    18,    19,    20,    21,    18,    -1,    -1,    -1,    -1,
      23,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
      16,    34,    18,    -1,    -1,    -1,    39,    23,    24,    25,
      26,    27,    28,    -1,    30,    -1,    -1,    -1,    34,    18,
      -1,    -1,    -1,    39,    23,    24,    25,    26,    27,    28,
      -1,    30,    -1,    -1,    -1,    34,    35,    18,    -1,    -1,
      39,    -1,    23,    24,    25,    26,    27,    28,    -1,    30,
      -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    39,    17,
      18,    19,    20,    21,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,    31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    43,     0,     1,     5,     6,     8,     9,    10,    12,
      18,    23,    24,    25,    26,    27,    28,    29,    30,    34,
      39,    44,    45,    46,    47,    49,    50,    51,    52,    54,
      55,    56,    59,    60,    61,    12,    34,    34,    37,    34,
      30,    54,    61,    30,    54,    54,    39,    30,    22,    39,
      35,    54,    57,    54,    12,    33,    44,    17,    18,    19,
      20,    21,    12,    47,    16,    39,    53,    54,    44,    53,
      33,    39,    23,    57,    22,    48,    54,    57,    41,    35,
      40,    44,    54,    54,    54,    54,    54,     4,    53,    53,
      54,    14,    15,    35,    31,    38,    35,    30,    40,    58,
      40,    54,    40,    57,    54,    40,    53,    53,    37,    54,
      11,    13,    41,    37,    40,     3,    44,    34,    36,    58,
      44,    37,    54,    38,    53,    37,    38,    44,    35,    35,
      44,    38,    37,    38,    44,     7,    38,    36,    37,    44,
      38
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    43,    43,    43,    43,    44,    44,    44,
      44,    45,    45,    45,    45,    45,    46,    46,    46,    47,
      48,    48,    49,    50,    50,    51,    51,    52,    53,    53,
      53,    53,    53,    53,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    55,    55,    55,    55,    55,    55,
      55,    56,    56,    57,    57,    58,    58,    59,    60,    60,
      61,    61
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     3,     3,     2,     3,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     0,     3,     9,    14,     7,     8,    11,     3,     3,
       3,     2,     3,     1,     3,     3,     3,     3,     3,     3,
       2,     3,     1,     1,     0,     1,     1,     1,     1,     1,
       1,     2,     3,     1,     3,     1,     3,     3,     8,     7,
       4,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 3: /* START: START stmts EOL  */
#line 51 "parser.y"
                      {(yyval.a) = newast('L', (yyvsp[-2].a), (yyvsp[-1].a)); val_t result = eval((yyvsp[-1].a)); print_ast((yyvsp[-1].a), 0, " ");    }
#line 1528 "parser.tab.c"
    break;

  case 5: /* START: START error EOL  */
#line 53 "parser.y"
                      { yyerrok; printf("> "); }
#line 1534 "parser.tab.c"
    break;

  case 6: /* START: START EOL  */
#line 54 "parser.y"
                 { printf("> "); }
#line 1540 "parser.tab.c"
    break;

  case 7: /* stmts: stmt ';' stmts  */
#line 57 "parser.y"
                    { if ((yyvsp[0].a) == NULL) 
        (yyval.a) = (yyvsp[-2].a);
    else 
        (yyval.a) = newast('L', (yyvsp[-2].a), (yyvsp[0].a)); 
        }
#line 1550 "parser.tab.c"
    break;

  case 8: /* stmts: stmt ';'  */
#line 62 "parser.y"
               { (yyval.a) = (yyvsp[-1].a); }
#line 1556 "parser.tab.c"
    break;

  case 9: /* stmts: flow stmts  */
#line 63 "parser.y"
                 {  
        if ((yyvsp[0].a) == NULL) 
            (yyval.a) = (yyvsp[-1].a);
        else 
            (yyval.a) = newast('L', (yyvsp[-1].a), (yyvsp[0].a));
    }
#line 1567 "parser.tab.c"
    break;

  case 10: /* stmts: flow  */
#line 69 "parser.y"
            { (yyval.a) = (yyvsp[0].a); }
#line 1573 "parser.tab.c"
    break;

  case 11: /* stmt: declare  */
#line 72 "parser.y"
             { (yyval.a) = (yyvsp[0].a); }
#line 1579 "parser.tab.c"
    break;

  case 12: /* stmt: assignment  */
#line 73 "parser.y"
                 { (yyval.a) = (yyvsp[0].a); }
#line 1585 "parser.tab.c"
    break;

  case 13: /* stmt: funcall  */
#line 74 "parser.y"
              { (yyval.a) = (yyvsp[0].a); }
#line 1591 "parser.tab.c"
    break;

  case 14: /* stmt: return  */
#line 75 "parser.y"
             { (yyval.a) = (yyvsp[0].a); }
#line 1597 "parser.tab.c"
    break;

  case 15: /* stmt: expr  */
#line 76 "parser.y"
           { (yyval.a) = (yyvsp[0].a); }
#line 1603 "parser.tab.c"
    break;

  case 19: /* declare: DATA_TYPE ID init  */
#line 83 "parser.y"
                           {
     struct symbol *sym = lookup((yyvsp[-1].s)->name);
     if (sym->type != 0) {
         yyerror("Variable '%s' already declared", (yyvsp[-1].s)->name);
     } else {
         sym->type = (yyvsp[-2].dt); // Assegna il tipo dalla regola DATA_TYPE
     }
     struct ast *declare = newdeclare(sym, NULL, NULL);
     struct ast *assign = newasgn(sym, (yyvsp[0].a));
     (yyval.a) = newast('L', declare, assign);
    }
#line 1619 "parser.tab.c"
    break;

  case 20: /* init: ASSIGN expr  */
#line 96 "parser.y"
                  { (yyval.a) = (yyvsp[0].a); }
#line 1625 "parser.tab.c"
    break;

  case 21: /* init: %empty  */
#line 97 "parser.y"
      { (yyval.a) = NULL; }
#line 1631 "parser.tab.c"
    break;

  case 22: /* assignment: ID ASSIGN expr  */
#line 99 "parser.y"
                           { (yyval.a) = newasgn((yyvsp[-2].s), (yyvsp[0].a)); }
#line 1637 "parser.tab.c"
    break;

  case 23: /* whether: WHETHER '[' condition ']' THEN ':' '{' stmts '}'  */
#line 101 "parser.y"
                                                          { (yyval.a) = newflow('I', (yyvsp[-6].a), (yyvsp[-1].a), NULL); }
#line 1643 "parser.tab.c"
    break;

  case 24: /* whether: WHETHER '[' condition ']' THEN ':' '{' stmts '}' OTHERWISE ':' '{' stmts '}'  */
#line 102 "parser.y"
                                                                                  { (yyval.a) = newflow('I', (yyvsp[-11].a), (yyvsp[-6].a), (yyvsp[-1].a)); }
#line 1649 "parser.tab.c"
    break;

  case 25: /* when: WHEN '[' condition ']' '{' stmts '}'  */
#line 105 "parser.y"
                                            { (yyval.a) = newflow('W', (yyvsp[-4].a), (yyvsp[-1].a), NULL); }
#line 1655 "parser.tab.c"
    break;

  case 26: /* when: WHEN '{' stmts '}' UNTIL '[' condition ']'  */
#line 106 "parser.y"
                                                 { (yyval.a) = newflow('W', (yyvsp[-1].a), (yyvsp[-5].a), (yyvsp[-1].a)); }
#line 1661 "parser.tab.c"
    break;

  case 27: /* from: FROM '[' declare TO expr STEP expr ']' '{' stmts '}'  */
#line 111 "parser.y"
     {
         struct ast *add = newast('+', newref((yyvsp[-8].a)->l->data.sym), (yyvsp[-4].a));
         struct ast *ass = newasgn((yyvsp[-8].a)->l->data.sym, add);
         struct ast *cmp = newast('6', newref((yyvsp[-8].a)->l->data.sym), (yyvsp[-6].a));
         (yyval.a) = newfor((yyvsp[-8].a), cmp, ass, (yyvsp[-1].a));
     }
#line 1672 "parser.tab.c"
    break;

  case 28: /* condition: expr CMP expr  */
#line 118 "parser.y"
                         { (yyval.a) = newcmp((yyvsp[-1].fn), (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1678 "parser.tab.c"
    break;

  case 29: /* condition: condition AND condition  */
#line 119 "parser.y"
                              { (yyval.a) = newast('&', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1684 "parser.tab.c"
    break;

  case 30: /* condition: condition OR condition  */
#line 120 "parser.y"
                             { (yyval.a) = newast('O', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1690 "parser.tab.c"
    break;

  case 31: /* condition: NOT condition  */
#line 121 "parser.y"
                    { (yyval.a) = newast('!', (yyvsp[0].a), NULL); }
#line 1696 "parser.tab.c"
    break;

  case 32: /* condition: '(' condition ')'  */
#line 122 "parser.y"
                        { (yyval.a) = (yyvsp[-1].a); }
#line 1702 "parser.tab.c"
    break;

  case 33: /* condition: expr  */
#line 123 "parser.y"
           { (yyval.a) = (yyvsp[0].a); }
#line 1708 "parser.tab.c"
    break;

  case 34: /* expr: expr PLUS expr  */
#line 125 "parser.y"
                     { (yyval.a) = newast('+', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1714 "parser.tab.c"
    break;

  case 35: /* expr: expr MINUS expr  */
#line 126 "parser.y"
                      { (yyval.a) = newast('-', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1720 "parser.tab.c"
    break;

  case 36: /* expr: expr MUL expr  */
#line 127 "parser.y"
                    { (yyval.a) = newast('*', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1726 "parser.tab.c"
    break;

  case 37: /* expr: expr DIV expr  */
#line 128 "parser.y"
                    { (yyval.a) = newast('/', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1732 "parser.tab.c"
    break;

  case 38: /* expr: expr POW expr  */
#line 129 "parser.y"
                    { (yyval.a) = newast('^', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1738 "parser.tab.c"
    break;

  case 39: /* expr: ABS expr ABS  */
#line 130 "parser.y"
                   { (yyval.a) = newast('|', (yyvsp[-1].a), NULL); }
#line 1744 "parser.tab.c"
    break;

  case 40: /* expr: MINUS expr  */
#line 131 "parser.y"
                             { (yyval.a) = newast('M', (yyvsp[0].a), NULL); }
#line 1750 "parser.tab.c"
    break;

  case 41: /* expr: '(' expr ')'  */
#line 132 "parser.y"
                   { (yyval.a) = (yyvsp[-1].a); }
#line 1756 "parser.tab.c"
    break;

  case 42: /* expr: value  */
#line 133 "parser.y"
            { (yyval.a) = (yyvsp[0].a); }
#line 1762 "parser.tab.c"
    break;

  case 43: /* expr: funcall  */
#line 134 "parser.y"
              { (yyval.a) = (yyvsp[0].a); }
#line 1768 "parser.tab.c"
    break;

  case 44: /* value: %empty  */
#line 136 "parser.y"
       {(yyval.a) = NULL;}
#line 1774 "parser.tab.c"
    break;

  case 45: /* value: NUM  */
#line 137 "parser.y"
          { (yyval.a) = newnum((yyvsp[0].num));}
#line 1780 "parser.tab.c"
    break;

  case 46: /* value: BINARY  */
#line 138 "parser.y"
             { (yyval.a) = newnum((yyvsp[0].num)); }
#line 1786 "parser.tab.c"
    break;

  case 47: /* value: ROMAN  */
#line 139 "parser.y"
            { (yyval.a) = newnum((yyvsp[0].num)); }
#line 1792 "parser.tab.c"
    break;

  case 48: /* value: ID  */
#line 140 "parser.y"
         { (yyval.a) = newref((yyvsp[0].s)); }
#line 1798 "parser.tab.c"
    break;

  case 49: /* value: STR  */
#line 141 "parser.y"
          { (yyval.a) = newstr((yyvsp[0].st)); }
#line 1804 "parser.tab.c"
    break;

  case 50: /* value: list  */
#line 142 "parser.y"
           { (yyval.a) = (yyvsp[0].a); }
#line 1810 "parser.tab.c"
    break;

  case 51: /* list: '[' ']'  */
#line 144 "parser.y"
              { (yyval.a) = NULL; }
#line 1816 "parser.tab.c"
    break;

  case 52: /* list: '[' explist ']'  */
#line 145 "parser.y"
                      { (yyval.a) = (yyvsp[-1].a); }
#line 1822 "parser.tab.c"
    break;

  case 54: /* explist: expr ',' explist  */
#line 149 "parser.y"
                       { (yyval.a) = newast('L', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1828 "parser.tab.c"
    break;

  case 55: /* symlist: ID  */
#line 151 "parser.y"
                     { (yyval.sl) = newsymlist((yyvsp[0].s), NULL); }
#line 1834 "parser.tab.c"
    break;

  case 56: /* symlist: ID ',' symlist  */
#line 152 "parser.y"
                     { (yyval.sl) = newsymlist((yyvsp[-2].s), (yyvsp[0].sl)); }
#line 1840 "parser.tab.c"
    break;

  case 57: /* return: RETURN expr ';'  */
#line 154 "parser.y"
                        { (yyval.a) = newast('R', (yyvsp[-1].a), NULL); }
#line 1846 "parser.tab.c"
    break;

  case 58: /* ufunction: DEFINE ID '(' symlist ')' '{' stmts '}'  */
#line 156 "parser.y"
                                                    { dodef((yyvsp[-6].s),(yyvsp[-4].sl),(yyvsp[-1].a)); printf("Function %s defined\n", (yyvsp[-6].s)->name); }
#line 1852 "parser.tab.c"
    break;

  case 59: /* ufunction: DEFINE ID '(' ')' '{' stmts '}'  */
#line 157 "parser.y"
                                        { dodef((yyvsp[-5].s),NULL,(yyvsp[-1].a)); printf("Function %s defined\n", (yyvsp[-5].s)->name); }
#line 1858 "parser.tab.c"
    break;

  case 60: /* funcall: ID '(' explist ')'  */
#line 159 "parser.y"
                            { (yyval.a) = newcall((yyvsp[-3].s), (yyvsp[-1].a)); }
#line 1864 "parser.tab.c"
    break;

  case 61: /* funcall: FUNC '(' explist ')'  */
#line 160 "parser.y"
                           { (yyval.a) = newfunc((yyvsp[-3].fn), (yyvsp[-1].a)); }
#line 1870 "parser.tab.c"
    break;


#line 1874 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 163 "parser.y"


int main(int argc, char **argv) {

    if(argc < 2) { /* just read stdin */
        yyparse();
        return 0;
    }
    for(int i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if(!f) {
            perror(argv[i]);
            return (1);
        }
        yyparse();
        fclose(f);
    }
    return 0;
}
