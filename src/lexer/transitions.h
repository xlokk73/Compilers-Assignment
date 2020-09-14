#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include <string>

#define VALID 1
#define INVALID -1


enum classifier { digit, other, space, newline, dot, underscore, letter, mult_char, add_char, equals, greater_than, less_than, srb_char, erb_char, scb_char, ecb_char, comma_char, colon_char, s_colon_char, div_char, ssb_char, esb_char, eof_char };
enum state { S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S10b, S11, S12, S13, S14, S15, S16, S17, S18, S19, S20, S21, S22, S23, S24, S25, S26, SE, BAD };
enum token_type { invalid, number, float_num, identifier, keyword, mult_op, add_op, rel_op, var_type, boolean, automatic, srb, erb, scb, ecb, comma, colon, s_colon, comment, ssb, esb, eof };

std::string get_type(token_type e);

struct token {
    token_type type;
    std::string value;
};

/* Accapting state */
const state SA[] = { S1, S3, S4, S5, S6, S7, S8, S9, S10, S10b, S11, S12, S13, S14, S15, S16, S17, S18, S20, S23, S24, S25, S26 };
const int total_accepting_states = 23;

/* Transition table */
const int transitions[][29] = {
       /*digit*/ /*other*/ /*space*/ /*newline*/ /*dot*/ /*underscore*/ /*letter*/ /*mult_char*/ /*add_char*/ /*equals*/ /*greater_than*/ /*less_than*/ /*srb_char*/ /*erb_char*/ /*scb_char*/ /*ecb_char*/ /*comma_char*/ /*colon_char*/ /*s_colon_char*/ /*div_char*/ /*ssb_char*/ /*esb_char*/ /*eof_char*/
/*S0 */ { S1 ,      SE ,      S0 ,      S0 ,        SE ,    S4 ,           S4 ,       S5,           S6 ,         S7 ,       S9 ,             S10,         S11,         S12,         S13,         S14,         S15,           S16,           S17,             S18,         S24,         S25,         S26 },             
/*S1 */ { S1 ,      SE ,      SE ,      SE ,        S2 ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S2 */ { S3 ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S3 */ { S3 ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S4 */ { S4 ,      SE ,      SE ,      SE ,        SE ,    S4 ,           S4 ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S5 */ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S6 */ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S7 */ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S8 */ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         S8 ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S9 */ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         S8 ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  }, 
/*S10*/ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         S8 ,       S10b,            SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S10b*/{ SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S11*/ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S12*/ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  }, 
/*S13*/ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  }, 
/*S14*/ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  }, 
/*S15*/ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S16*/ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S17*/ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S18*/ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       S21,          SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             S19,         SE ,         SE ,         SE  },
/*S19*/ { S19,      S19,      S19,      S20,        S19,    S19,           S19,       S19,          S19,         S19,       S19,             S19,         S19,         S19,         S19,         S19,         S19,           S19,           S19,             S19,         SE ,         SE ,         SE  },
/*S20*/ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S21*/ { S21,      S21,      S21,      S21,        S21,    S21,           S21,       S22,          S21,         S21,       S21,             S21,         S21,         S21,         S21,         S21,         S21,           S21,           S21,             S21,         SE ,         SE ,         SE  },
/*S22*/ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE ,          SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             S23,         SE ,         SE ,         SE  },
/*S23*/ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },
/*S24*/ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },  
/*S25*/ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },  
/*S26*/ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  },  
/*SE */ { SE ,      SE ,      SE ,      SE ,        SE ,    SE ,           SE ,       SE,           SE ,         SE ,       SE ,             SE ,         SE ,         SE ,         SE ,         SE ,         SE ,           SE ,           SE ,             SE ,         SE ,         SE ,         SE  }
};

/* Classifier table */
classifier char_cat(int ch); 

/* Token type table */
token_type type(state* fin, std::string lexeme);

bool is_accepting(const state n);

#endif

