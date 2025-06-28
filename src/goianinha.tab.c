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
#line 1 "goianinha.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "tabela_simbolos.h"
#include "semantic.h"
#include "mips_generator.h"

extern int yylex();
extern int yylineno;
extern FILE* yyin;

void yyerror(const char* s);
ASTNode* root = NULL;

#line 88 "goianinha.tab.c"

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

#include "goianinha.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAMA = 3,                   /* PROGRAMA  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_CAR = 5,                        /* CAR  */
  YYSYMBOL_SE = 6,                         /* SE  */
  YYSYMBOL_ENTAO = 7,                      /* ENTAO  */
  YYSYMBOL_SENAO = 8,                      /* SENAO  */
  YYSYMBOL_ENQUANTO = 9,                   /* ENQUANTO  */
  YYSYMBOL_EXECUTE = 10,                   /* EXECUTE  */
  YYSYMBOL_RETORNE = 11,                   /* RETORNE  */
  YYSYMBOL_LEIA = 12,                      /* LEIA  */
  YYSYMBOL_ESCREVA = 13,                   /* ESCREVA  */
  YYSYMBOL_NOVALINHA = 14,                 /* NOVALINHA  */
  YYSYMBOL_IGUAL = 15,                     /* IGUAL  */
  YYSYMBOL_IGUAL_IGUAL = 16,               /* IGUAL_IGUAL  */
  YYSYMBOL_DIFERENTE = 17,                 /* DIFERENTE  */
  YYSYMBOL_MENOR = 18,                     /* MENOR  */
  YYSYMBOL_MAIOR = 19,                     /* MAIOR  */
  YYSYMBOL_MENOR_IGUAL = 20,               /* MENOR_IGUAL  */
  YYSYMBOL_MAIOR_IGUAL = 21,               /* MAIOR_IGUAL  */
  YYSYMBOL_MAIS = 22,                      /* MAIS  */
  YYSYMBOL_MENOS = 23,                     /* MENOS  */
  YYSYMBOL_MULTIPLICA = 24,                /* MULTIPLICA  */
  YYSYMBOL_DIVIDE = 25,                    /* DIVIDE  */
  YYSYMBOL_NEGACAO = 26,                   /* NEGACAO  */
  YYSYMBOL_E = 27,                         /* E  */
  YYSYMBOL_OU = 28,                        /* OU  */
  YYSYMBOL_PONTO_VIRGULA = 29,             /* PONTO_VIRGULA  */
  YYSYMBOL_VIRGULA = 30,                   /* VIRGULA  */
  YYSYMBOL_ABRE_PAREN = 31,                /* ABRE_PAREN  */
  YYSYMBOL_FECHA_PAREN = 32,               /* FECHA_PAREN  */
  YYSYMBOL_ABRE_CHAVE = 33,                /* ABRE_CHAVE  */
  YYSYMBOL_FECHA_CHAVE = 34,               /* FECHA_CHAVE  */
  YYSYMBOL_ID = 35,                        /* ID  */
  YYSYMBOL_STRING_CONST = 36,              /* STRING_CONST  */
  YYSYMBOL_INT_CONST = 37,                 /* INT_CONST  */
  YYSYMBOL_CHAR_CONST = 38,                /* CHAR_CONST  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_programa = 40,                  /* programa  */
  YYSYMBOL_declaracoes = 41,               /* declaracoes  */
  YYSYMBOL_declaracao = 42,                /* declaracao  */
  YYSYMBOL_declaracoes_locais = 43,        /* declaracoes_locais  */
  YYSYMBOL_declaracao_local = 44,          /* declaracao_local  */
  YYSYMBOL_lista_id = 45,                  /* lista_id  */
  YYSYMBOL_funcao = 46,                    /* funcao  */
  YYSYMBOL_parametros = 47,                /* parametros  */
  YYSYMBOL_parametro = 48,                 /* parametro  */
  YYSYMBOL_bloco = 49,                     /* bloco  */
  YYSYMBOL_comandos = 50,                  /* comandos  */
  YYSYMBOL_comando = 51,                   /* comando  */
  YYSYMBOL_comando_simples = 52,           /* comando_simples  */
  YYSYMBOL_atribuicao = 53,                /* atribuicao  */
  YYSYMBOL_expressao = 54,                 /* expressao  */
  YYSYMBOL_termo = 55,                     /* termo  */
  YYSYMBOL_fator = 56,                     /* fator  */
  YYSYMBOL_chamada_funcao = 57,            /* chamada_funcao  */
  YYSYMBOL_argumentos = 58                 /* argumentos  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   291

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  139

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    47,    47,    52,    59,    63,    69,    73,    77,    83,
      87,    93,    97,   103,   107,   113,   117,   124,   127,   131,
     137,   141,   147,   151,   172,   175,   179,   185,   186,   187,
     191,   195,   199,   205,   209,   213,   217,   221,   225,   233,
     237,   245,   257,   261,   265,   269,   273,   277,   281,   285,
     289,   295,   299,   303,   309,   313,   317,   321,   325,   329,
     333,   337,   341,   347,   354,   357,   361
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAMA", "INT",
  "CAR", "SE", "ENTAO", "SENAO", "ENQUANTO", "EXECUTE", "RETORNE", "LEIA",
  "ESCREVA", "NOVALINHA", "IGUAL", "IGUAL_IGUAL", "DIFERENTE", "MENOR",
  "MAIOR", "MENOR_IGUAL", "MAIOR_IGUAL", "MAIS", "MENOS", "MULTIPLICA",
  "DIVIDE", "NEGACAO", "E", "OU", "PONTO_VIRGULA", "VIRGULA", "ABRE_PAREN",
  "FECHA_PAREN", "ABRE_CHAVE", "FECHA_CHAVE", "ID", "STRING_CONST",
  "INT_CONST", "CHAR_CONST", "$accept", "programa", "declaracoes",
  "declaracao", "declaracoes_locais", "declaracao_local", "lista_id",
  "funcao", "parametros", "parametro", "bloco", "comandos", "comando",
  "comando_simples", "atribuicao", "expressao", "termo", "fator",
  "chamada_funcao", "argumentos", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-42)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      35,   -20,   -14,    -9,    50,    83,   -42,   -42,    59,   -42,
      43,    49,    45,   117,   -42,   -20,   -42,    31,    31,    60,
      62,   138,    46,   122,    66,    84,    59,   -42,   -42,    18,
     -42,   113,   -42,   127,   -42,    67,   127,   -42,   -42,   -42,
     133,   161,   138,   138,   138,   138,   138,    76,   -42,   -42,
     181,   155,   163,   -42,    82,    99,   195,   -42,   148,   -42,
      71,   -42,   -42,   113,    78,    98,   -16,   -42,   -42,     4,
     -42,   -42,   -10,   102,   163,   -42,   123,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   -42,   138,   138,   138,
     138,   -42,   -42,   -42,    -3,   209,   -42,   -42,   -42,   127,
     -20,   -20,   128,   139,   -42,   251,    37,   147,   147,   -42,
     -42,   -42,   -42,    26,   264,   -42,   -42,   -42,   -42,   158,
     -42,   -42,   -42,   -42,   103,   103,   138,   -42,    10,   223,
     129,   -42,   251,   138,   -42,   103,   237,   -42,   -42
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     4,     8,    24,     3,
      13,     0,    13,     0,     1,     0,     5,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    24,     9,    32,     0,
      25,    28,    27,    17,     6,     0,    17,     7,     2,    13,
       0,     0,     0,     0,     0,     0,     0,    59,    60,    61,
       0,    50,    53,    62,     0,     0,     0,    37,     0,    10,
       0,    22,    26,    38,     0,     0,     0,    18,    14,     0,
      11,    12,     0,     0,    56,    57,     0,    64,     0,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,    34,    36,    35,    59,     0,    23,    20,    21,     0,
       0,     0,     0,     0,    58,    65,     0,    44,    45,    46,
      47,    48,    49,    43,    42,    51,    52,    54,    55,     0,
      39,    19,    15,    16,     0,     0,     0,    63,    59,     0,
      29,    31,    66,     0,    40,     0,     0,    30,    41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -42,   -42,   -42,   149,   -42,   126,    72,   -42,   120,    73,
       0,   144,   -27,   -26,   -42,   -23,   116,   -41,   -42,   -42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    26,    27,    11,     7,    66,    67,
      28,    29,    30,    31,    32,    50,    51,    52,    53,   106
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      56,     9,    62,    74,    75,    63,    78,    79,    80,    81,
      82,    83,   119,     8,    99,    38,   100,    84,    85,    72,
      73,    10,   102,    76,    19,   133,    12,    20,    77,    21,
      22,    23,    24,    62,    99,    95,   101,    63,     1,     2,
       3,    77,    78,    79,    80,    81,    82,    83,   117,   118,
      14,     8,    61,    25,   105,   107,   108,   109,   110,   111,
     112,   113,   114,    17,    18,    19,    39,   126,    20,   127,
      21,    22,    23,    24,    33,    13,    36,    19,    34,    35,
      20,    54,    21,    22,    23,    24,    15,     2,     3,    40,
      41,    42,     8,    43,    25,    57,   129,   130,   131,    58,
     122,   123,    68,   132,     8,    96,    25,    77,   137,    19,
     136,    91,    20,    97,    21,    22,    23,    24,    78,    79,
      80,    81,    82,    83,    21,    22,    23,    24,    92,    84,
      85,    64,    65,    98,   103,   124,     8,   135,    25,    78,
      79,    80,    81,    82,    83,    44,    37,    35,    45,   125,
      84,    85,    59,    46,    16,   104,    69,    47,    55,    48,
      49,    44,    70,    35,    45,    80,    81,    82,    83,    46,
      60,    44,   121,    47,    45,    48,    49,    87,    88,    46,
       0,    44,     0,    94,    45,    48,    49,    89,    90,    46,
      71,    35,     0,   128,     0,    48,    49,    78,    79,    80,
      81,    82,    83,   115,   116,     0,     0,     0,    84,    85,
      86,    78,    79,    80,    81,    82,    83,     0,     0,     0,
       0,     0,    84,    85,    93,    78,    79,    80,    81,    82,
      83,     0,     0,     0,     0,     0,    84,    85,   120,    78,
      79,    80,    81,    82,    83,     0,     0,     0,     0,     0,
      84,    85,   134,    78,    79,    80,    81,    82,    83,     0,
       0,     0,     0,     0,    84,    85,   138,    78,    79,    80,
      81,    82,    83,     0,     0,     0,     0,     0,    84,    85,
      78,    79,    80,    81,    82,    83,     0,     0,     0,     0,
       0,    84
};

static const yytype_int16 yycheck[] =
{
      23,     1,    29,    44,    45,    31,    16,    17,    18,    19,
      20,    21,    15,    33,    30,    15,    32,    27,    28,    42,
      43,    35,    32,    46,     6,    15,    35,     9,    31,    11,
      12,    13,    14,    60,    30,    58,    32,    63,     3,     4,
       5,    31,    16,    17,    18,    19,    20,    21,    89,    90,
       0,    33,    34,    35,    77,    78,    79,    80,    81,    82,
      83,    84,    85,     4,     5,     6,    35,    30,     9,    32,
      11,    12,    13,    14,    31,     3,    31,     6,    29,    30,
       9,    35,    11,    12,    13,    14,     3,     4,     5,    17,
      18,    31,    33,    31,    35,    29,   119,   124,   125,    15,
     100,   101,    35,   126,    33,    34,    35,    31,   135,     6,
     133,    29,     9,    35,    11,    12,    13,    14,    16,    17,
      18,    19,    20,    21,    11,    12,    13,    14,    29,    27,
      28,     4,     5,    35,    32,     7,    33,     8,    35,    16,
      17,    18,    19,    20,    21,    23,    29,    30,    26,    10,
      27,    28,    26,    31,     5,    32,    36,    35,    36,    37,
      38,    23,    29,    30,    26,    18,    19,    20,    21,    31,
      26,    23,    99,    35,    26,    37,    38,    22,    23,    31,
      -1,    23,    -1,    35,    26,    37,    38,    24,    25,    31,
      29,    30,    -1,    35,    -1,    37,    38,    16,    17,    18,
      19,    20,    21,    87,    88,    -1,    -1,    -1,    27,    28,
      29,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    27,    28,    29,    16,    17,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    -1,    27,    28,    29,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      27,    28,    29,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    27,    28,    29,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,    -1,    27,    28,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    40,    41,    42,    46,    33,    49,
      35,    45,    35,    45,     0,     3,    42,     4,     5,     6,
       9,    11,    12,    13,    14,    35,    43,    44,    49,    50,
      51,    52,    53,    31,    29,    30,    31,    29,    49,    35,
      45,    45,    31,    31,    23,    26,    31,    35,    37,    38,
      54,    55,    56,    57,    35,    36,    54,    29,    15,    44,
      50,    34,    51,    52,     4,     5,    47,    48,    35,    47,
      29,    29,    54,    54,    56,    56,    54,    31,    16,    17,
      18,    19,    20,    21,    27,    28,    29,    22,    23,    24,
      25,    29,    29,    29,    35,    54,    34,    35,    35,    30,
      32,    32,    32,    32,    32,    54,    58,    54,    54,    54,
      54,    54,    54,    54,    54,    55,    55,    56,    56,    15,
      29,    48,    49,    49,     7,    10,    30,    32,    35,    54,
      51,    51,    54,    15,    29,     8,    54,    51,    29
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    40,    41,    41,    42,    42,    42,    43,
      43,    44,    44,    45,    45,    46,    46,    47,    47,    47,
      48,    48,    49,    49,    50,    50,    50,    51,    51,    51,
      51,    51,    51,    52,    52,    52,    52,    52,    52,    53,
      53,    53,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    55,    55,    55,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    57,    58,    58,    58
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     1,     2,     3,     3,     1,     1,
       2,     3,     3,     1,     3,     6,     6,     0,     1,     3,
       2,     2,     3,     4,     0,     1,     2,     1,     1,     6,
       8,     6,     1,     3,     3,     3,     3,     2,     2,     4,
       6,     8,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     2,     2,     3,     1,
       1,     1,     1,     4,     0,     1,     3
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
  case 2: /* programa: declaracoes PROGRAMA bloco  */
#line 48 "goianinha.y"
        {
            (yyval.node) = create_program_node((yyvsp[-2].node), (yyvsp[0].node));
            root = (yyval.node);
        }
#line 1252 "goianinha.tab.c"
    break;

  case 3: /* programa: PROGRAMA bloco  */
#line 53 "goianinha.y"
        {
            (yyval.node) = create_program_node(NULL, (yyvsp[0].node));
            root = (yyval.node);
        }
#line 1261 "goianinha.tab.c"
    break;

  case 4: /* declaracoes: declaracao  */
#line 60 "goianinha.y"
           {
               (yyval.node) = create_decl_list_node((yyvsp[0].node));
           }
#line 1269 "goianinha.tab.c"
    break;

  case 5: /* declaracoes: declaracoes declaracao  */
#line 64 "goianinha.y"
           {
               (yyval.node) = add_to_decl_list((yyvsp[-1].node), (yyvsp[0].node));
           }
#line 1277 "goianinha.tab.c"
    break;

  case 6: /* declaracao: INT lista_id PONTO_VIRGULA  */
#line 70 "goianinha.y"
          {
              (yyval.node) = create_var_decl_node(TYPE_INT, (yyvsp[-1].node));
          }
#line 1285 "goianinha.tab.c"
    break;

  case 7: /* declaracao: CAR lista_id PONTO_VIRGULA  */
#line 74 "goianinha.y"
          {
              (yyval.node) = create_var_decl_node(TYPE_CHAR, (yyvsp[-1].node));
          }
#line 1293 "goianinha.tab.c"
    break;

  case 8: /* declaracao: funcao  */
#line 78 "goianinha.y"
          {
              (yyval.node) = (yyvsp[0].node);
          }
#line 1301 "goianinha.tab.c"
    break;

  case 9: /* declaracoes_locais: declaracao_local  */
#line 84 "goianinha.y"
                  {
                      (yyval.node) = create_stmt_list_node((yyvsp[0].node));
                  }
#line 1309 "goianinha.tab.c"
    break;

  case 10: /* declaracoes_locais: declaracoes_locais declaracao_local  */
#line 88 "goianinha.y"
                  {
                      (yyval.node) = add_to_stmt_list((yyvsp[-1].node), (yyvsp[0].node));
                  }
#line 1317 "goianinha.tab.c"
    break;

  case 11: /* declaracao_local: INT lista_id PONTO_VIRGULA  */
#line 94 "goianinha.y"
                {
                    (yyval.node) = create_var_decl_node(TYPE_INT, (yyvsp[-1].node));
                }
#line 1325 "goianinha.tab.c"
    break;

  case 12: /* declaracao_local: CAR lista_id PONTO_VIRGULA  */
#line 98 "goianinha.y"
                {
                    (yyval.node) = create_var_decl_node(TYPE_CHAR, (yyvsp[-1].node));
                }
#line 1333 "goianinha.tab.c"
    break;

  case 13: /* lista_id: ID  */
#line 104 "goianinha.y"
        {
            (yyval.node) = create_id_list_node((yyvsp[0].str));
        }
#line 1341 "goianinha.tab.c"
    break;

  case 14: /* lista_id: lista_id VIRGULA ID  */
#line 108 "goianinha.y"
        {
            (yyval.node) = add_to_id_list((yyvsp[-2].node), (yyvsp[0].str));
        }
#line 1349 "goianinha.tab.c"
    break;

  case 15: /* funcao: INT ID ABRE_PAREN parametros FECHA_PAREN bloco  */
#line 114 "goianinha.y"
      {
          (yyval.node) = create_func_decl_node(TYPE_INT, (yyvsp[-4].str), (yyvsp[-2].node), (yyvsp[0].node));
      }
#line 1357 "goianinha.tab.c"
    break;

  case 16: /* funcao: CAR ID ABRE_PAREN parametros FECHA_PAREN bloco  */
#line 118 "goianinha.y"
      {
          (yyval.node) = create_func_decl_node(TYPE_CHAR, (yyvsp[-4].str), (yyvsp[-2].node), (yyvsp[0].node));
      }
#line 1365 "goianinha.tab.c"
    break;

  case 17: /* parametros: %empty  */
#line 124 "goianinha.y"
          {
              (yyval.node) = NULL;
          }
#line 1373 "goianinha.tab.c"
    break;

  case 18: /* parametros: parametro  */
#line 128 "goianinha.y"
          {
              (yyval.node) = create_param_list_node((yyvsp[0].node));
          }
#line 1381 "goianinha.tab.c"
    break;

  case 19: /* parametros: parametros VIRGULA parametro  */
#line 132 "goianinha.y"
          {
              (yyval.node) = add_to_param_list((yyvsp[-2].node), (yyvsp[0].node));
          }
#line 1389 "goianinha.tab.c"
    break;

  case 20: /* parametro: INT ID  */
#line 138 "goianinha.y"
         {
             (yyval.node) = create_param_node(TYPE_INT, (yyvsp[0].str));
         }
#line 1397 "goianinha.tab.c"
    break;

  case 21: /* parametro: CAR ID  */
#line 142 "goianinha.y"
         {
             (yyval.node) = create_param_node(TYPE_CHAR, (yyvsp[0].str));
         }
#line 1405 "goianinha.tab.c"
    break;

  case 22: /* bloco: ABRE_CHAVE comandos FECHA_CHAVE  */
#line 148 "goianinha.y"
     {
         (yyval.node) = create_block_node((yyvsp[-1].node));
     }
#line 1413 "goianinha.tab.c"
    break;

  case 23: /* bloco: ABRE_CHAVE declaracoes_locais comandos FECHA_CHAVE  */
#line 152 "goianinha.y"
     {
         // Bloco com declarações locais (para suportar declarações dentro de programa{})
         ASTNode* combined = (yyvsp[-2].node);
         if ((yyvsp[-1].node)) {
             // Adiciona comandos após declarações
             ASTNode* current = combined;
             while (current && current->data.list.next) {
                 current = current->data.list.next;
             }
             if (current) {
                 current->data.list.next = (yyvsp[-1].node);
             } else {
                 combined = (yyvsp[-1].node);
             }
         }
         (yyval.node) = create_block_node(combined);
     }
#line 1435 "goianinha.tab.c"
    break;

  case 24: /* comandos: %empty  */
#line 172 "goianinha.y"
        {
            (yyval.node) = NULL;
        }
#line 1443 "goianinha.tab.c"
    break;

  case 25: /* comandos: comando  */
#line 176 "goianinha.y"
        {
            (yyval.node) = create_stmt_list_node((yyvsp[0].node));
        }
#line 1451 "goianinha.tab.c"
    break;

  case 26: /* comandos: comandos comando  */
#line 180 "goianinha.y"
        {
            (yyval.node) = add_to_stmt_list((yyvsp[-1].node), (yyvsp[0].node));
        }
#line 1459 "goianinha.tab.c"
    break;

  case 29: /* comando: SE ABRE_PAREN expressao FECHA_PAREN ENTAO comando  */
#line 188 "goianinha.y"
       {
           (yyval.node) = create_if_node((yyvsp[-3].node), (yyvsp[0].node), NULL);
       }
#line 1467 "goianinha.tab.c"
    break;

  case 30: /* comando: SE ABRE_PAREN expressao FECHA_PAREN ENTAO comando SENAO comando  */
#line 192 "goianinha.y"
       {
           (yyval.node) = create_if_node((yyvsp[-5].node), (yyvsp[-2].node), (yyvsp[0].node));
       }
#line 1475 "goianinha.tab.c"
    break;

  case 31: /* comando: ENQUANTO ABRE_PAREN expressao FECHA_PAREN EXECUTE comando  */
#line 196 "goianinha.y"
       {
           (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[0].node));
       }
#line 1483 "goianinha.tab.c"
    break;

  case 32: /* comando: bloco  */
#line 200 "goianinha.y"
       {
           (yyval.node) = (yyvsp[0].node);
       }
#line 1491 "goianinha.tab.c"
    break;

  case 33: /* comando_simples: RETORNE expressao PONTO_VIRGULA  */
#line 206 "goianinha.y"
               {
                   (yyval.node) = create_return_node((yyvsp[-1].node));
               }
#line 1499 "goianinha.tab.c"
    break;

  case 34: /* comando_simples: LEIA ID PONTO_VIRGULA  */
#line 210 "goianinha.y"
               {
                   (yyval.node) = create_read_node((yyvsp[-1].str));
               }
#line 1507 "goianinha.tab.c"
    break;

  case 35: /* comando_simples: ESCREVA expressao PONTO_VIRGULA  */
#line 214 "goianinha.y"
               {
                   (yyval.node) = create_write_node((yyvsp[-1].node));
               }
#line 1515 "goianinha.tab.c"
    break;

  case 36: /* comando_simples: ESCREVA STRING_CONST PONTO_VIRGULA  */
#line 218 "goianinha.y"
               {
                   (yyval.node) = create_write_string_node((yyvsp[-1].str));
               }
#line 1523 "goianinha.tab.c"
    break;

  case 37: /* comando_simples: NOVALINHA PONTO_VIRGULA  */
#line 222 "goianinha.y"
               {
                   (yyval.node) = create_newline_node();
               }
#line 1531 "goianinha.tab.c"
    break;

  case 38: /* comando_simples: comando_simples comando_simples  */
#line 226 "goianinha.y"
               {
                   // Múltiplos comandos na mesma linha
                   ASTNode* list = create_stmt_list_node((yyvsp[-1].node));
                   (yyval.node) = add_to_stmt_list(list, (yyvsp[0].node));
               }
#line 1541 "goianinha.tab.c"
    break;

  case 39: /* atribuicao: ID IGUAL expressao PONTO_VIRGULA  */
#line 234 "goianinha.y"
          {
              (yyval.node) = create_assign_node((yyvsp[-3].str), (yyvsp[-1].node));
          }
#line 1549 "goianinha.tab.c"
    break;

  case 40: /* atribuicao: ID IGUAL ID IGUAL expressao PONTO_VIRGULA  */
#line 238 "goianinha.y"
          {
              // Múltipla atribuição: x = y = expr
              ASTNode* assign2 = create_assign_node((yyvsp[-3].str), (yyvsp[-1].node));
              ASTNode* assign1 = create_assign_node((yyvsp[-5].str), (yyvsp[-1].node));
              ASTNode* list = create_stmt_list_node(assign2);
              (yyval.node) = add_to_stmt_list(list, assign1);
          }
#line 1561 "goianinha.tab.c"
    break;

  case 41: /* atribuicao: ID IGUAL ID IGUAL ID IGUAL expressao PONTO_VIRGULA  */
#line 246 "goianinha.y"
          {
              // Múltipla atribuição: z = y = x = expr
              ASTNode* assign3 = create_assign_node((yyvsp[-3].str), (yyvsp[-1].node));
              ASTNode* assign2 = create_assign_node((yyvsp[-5].str), (yyvsp[-1].node));
              ASTNode* assign1 = create_assign_node((yyvsp[-7].str), (yyvsp[-1].node));
              ASTNode* list = create_stmt_list_node(assign3);
              list = add_to_stmt_list(list, assign2);
              (yyval.node) = add_to_stmt_list(list, assign1);
          }
#line 1575 "goianinha.tab.c"
    break;

  case 42: /* expressao: expressao OU expressao  */
#line 258 "goianinha.y"
         {
             (yyval.node) = create_binary_op_node(OP_OR, (yyvsp[-2].node), (yyvsp[0].node));
         }
#line 1583 "goianinha.tab.c"
    break;

  case 43: /* expressao: expressao E expressao  */
#line 262 "goianinha.y"
         {
             (yyval.node) = create_binary_op_node(OP_AND, (yyvsp[-2].node), (yyvsp[0].node));
         }
#line 1591 "goianinha.tab.c"
    break;

  case 44: /* expressao: expressao IGUAL_IGUAL expressao  */
#line 266 "goianinha.y"
         {
             (yyval.node) = create_binary_op_node(OP_EQ, (yyvsp[-2].node), (yyvsp[0].node));
         }
#line 1599 "goianinha.tab.c"
    break;

  case 45: /* expressao: expressao DIFERENTE expressao  */
#line 270 "goianinha.y"
         {
             (yyval.node) = create_binary_op_node(OP_NE, (yyvsp[-2].node), (yyvsp[0].node));
         }
#line 1607 "goianinha.tab.c"
    break;

  case 46: /* expressao: expressao MENOR expressao  */
#line 274 "goianinha.y"
         {
             (yyval.node) = create_binary_op_node(OP_LT, (yyvsp[-2].node), (yyvsp[0].node));
         }
#line 1615 "goianinha.tab.c"
    break;

  case 47: /* expressao: expressao MAIOR expressao  */
#line 278 "goianinha.y"
         {
             (yyval.node) = create_binary_op_node(OP_GT, (yyvsp[-2].node), (yyvsp[0].node));
         }
#line 1623 "goianinha.tab.c"
    break;

  case 48: /* expressao: expressao MENOR_IGUAL expressao  */
#line 282 "goianinha.y"
         {
             (yyval.node) = create_binary_op_node(OP_LE, (yyvsp[-2].node), (yyvsp[0].node));
         }
#line 1631 "goianinha.tab.c"
    break;

  case 49: /* expressao: expressao MAIOR_IGUAL expressao  */
#line 286 "goianinha.y"
         {
             (yyval.node) = create_binary_op_node(OP_GE, (yyvsp[-2].node), (yyvsp[0].node));
         }
#line 1639 "goianinha.tab.c"
    break;

  case 50: /* expressao: termo  */
#line 290 "goianinha.y"
         {
             (yyval.node) = (yyvsp[0].node);
         }
#line 1647 "goianinha.tab.c"
    break;

  case 51: /* termo: termo MAIS termo  */
#line 296 "goianinha.y"
     {
         (yyval.node) = create_binary_op_node(OP_ADD, (yyvsp[-2].node), (yyvsp[0].node));
     }
#line 1655 "goianinha.tab.c"
    break;

  case 52: /* termo: termo MENOS termo  */
#line 300 "goianinha.y"
     {
         (yyval.node) = create_binary_op_node(OP_SUB, (yyvsp[-2].node), (yyvsp[0].node));
     }
#line 1663 "goianinha.tab.c"
    break;

  case 53: /* termo: fator  */
#line 304 "goianinha.y"
     {
         (yyval.node) = (yyvsp[0].node);
     }
#line 1671 "goianinha.tab.c"
    break;

  case 54: /* fator: fator MULTIPLICA fator  */
#line 310 "goianinha.y"
     {
         (yyval.node) = create_binary_op_node(OP_MUL, (yyvsp[-2].node), (yyvsp[0].node));
     }
#line 1679 "goianinha.tab.c"
    break;

  case 55: /* fator: fator DIVIDE fator  */
#line 314 "goianinha.y"
     {
         (yyval.node) = create_binary_op_node(OP_DIV, (yyvsp[-2].node), (yyvsp[0].node));
     }
#line 1687 "goianinha.tab.c"
    break;

  case 56: /* fator: MENOS fator  */
#line 318 "goianinha.y"
     {
         (yyval.node) = create_unary_op_node(OP_NEG, (yyvsp[0].node));
     }
#line 1695 "goianinha.tab.c"
    break;

  case 57: /* fator: NEGACAO fator  */
#line 322 "goianinha.y"
     {
         (yyval.node) = create_unary_op_node(OP_NOT, (yyvsp[0].node));
     }
#line 1703 "goianinha.tab.c"
    break;

  case 58: /* fator: ABRE_PAREN expressao FECHA_PAREN  */
#line 326 "goianinha.y"
     {
         (yyval.node) = (yyvsp[-1].node);
     }
#line 1711 "goianinha.tab.c"
    break;

  case 59: /* fator: ID  */
#line 330 "goianinha.y"
     {
         (yyval.node) = create_id_node((yyvsp[0].str));
     }
#line 1719 "goianinha.tab.c"
    break;

  case 60: /* fator: INT_CONST  */
#line 334 "goianinha.y"
     {
         (yyval.node) = create_int_node((yyvsp[0].num));
     }
#line 1727 "goianinha.tab.c"
    break;

  case 61: /* fator: CHAR_CONST  */
#line 338 "goianinha.y"
     {
         (yyval.node) = create_char_node((yyvsp[0].chr));
     }
#line 1735 "goianinha.tab.c"
    break;

  case 62: /* fator: chamada_funcao  */
#line 342 "goianinha.y"
     {
         (yyval.node) = (yyvsp[0].node);
     }
#line 1743 "goianinha.tab.c"
    break;

  case 63: /* chamada_funcao: ID ABRE_PAREN argumentos FECHA_PAREN  */
#line 348 "goianinha.y"
              {
                  (yyval.node) = create_func_call_node((yyvsp[-3].str), (yyvsp[-1].node));
              }
#line 1751 "goianinha.tab.c"
    break;

  case 64: /* argumentos: %empty  */
#line 354 "goianinha.y"
          {
              (yyval.node) = NULL;
          }
#line 1759 "goianinha.tab.c"
    break;

  case 65: /* argumentos: expressao  */
#line 358 "goianinha.y"
          {
              (yyval.node) = create_arg_list_node((yyvsp[0].node));
          }
#line 1767 "goianinha.tab.c"
    break;

  case 66: /* argumentos: argumentos VIRGULA expressao  */
#line 362 "goianinha.y"
          {
              (yyval.node) = add_to_arg_list((yyvsp[-2].node), (yyvsp[0].node));
          }
#line 1775 "goianinha.tab.c"
    break;


#line 1779 "goianinha.tab.c"

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
      yyerror (YY_("syntax error"));
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

  return yyresult;
}

#line 367 "goianinha.y"


void yyerror(const char* s) {
    fprintf(stderr, "Erro na linha %d: %s\n", yylineno, s);
}

int main(int argc, char** argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Erro ao abrir arquivo: %s\n", argv[1]);
            return 1;
        }
    }
    
    if (yyparse() == 0) {
        printf("Análise sintática concluída com sucesso!\n");
        
        // Análise semântica
        if (semantic_analyze(root)) {
            printf("Análise semântica concluída com sucesso!\n");
            
            // Geração de código MIPS
            generate_mips_code(root, "saida.asm");
            printf("Código MIPS gerado em saida.asm\n");
        } else {
            printf("Erro na análise semântica!\n");
            return 1;
        }
    } else {
        printf("Erro na análise sintática!\n");
        return 1;
    }
    
    if (yyin != stdin) {
        fclose(yyin);
    }
    
    return 0;
} 
