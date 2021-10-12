#include "lex.h"
#include "define.h"
#include "except.h"

#include <stdlib.h>

enum char_map
{ 
    BLANK=01, 
    NEWLINE=02, 
    LETTER=04,
    DIGIT=010,
    HEX=020,    
    OTHER=040 
};

static unsigned char chrmap[] = 
{ 
    /* 000 nul */	0,
    /* 001 soh */	0,
    /* 002 stx */	0,
    /* 003 etx */	0,
    /* 004 eot */	0,
    /* 005 enq */	0,
    /* 006 ack */	0,
    /* 007 bel */	0,
    /* 010 bs  */	0,
    /* 011 ht  */	BLANK,
    /* 012 nl  */	NEWLINE,
    /* 013 vt  */	BLANK,
    /* 014 ff  */	BLANK,
    /* 015 cr  */	0,
    /* 016 so  */	0,
    /* 017 si  */	0,
    /* 020 dle */	0,
    /* 021 dc1 */	0,
    /* 022 dc2 */	0,
    /* 023 dc3 */	0,
    /* 024 dc4 */	0,
    /* 025 nak */	0,
    /* 026 syn */	0,
    /* 027 etb */	0,
    /* 030 can */	0,
    /* 031 em  */	0,
    /* 032 sub */	0,
    /* 033 esc */	0,
    /* 034 fs  */	0,
    /* 035 gs  */	0,
    /* 036 rs  */	0,
    /* 037 us  */	0,
    /* 040 sp  */	BLANK,
    /* 041 !   */	OTHER,
    /* 042 "   */	OTHER,
    /* 043 #   */	OTHER,
    /* 044 $   */	0,
    /* 045 %   */	OTHER,
    /* 046 &   */	OTHER,
    /* 047 '   */	OTHER,
    /* 050 (   */	OTHER,
    /* 051 )   */	OTHER,
    /* 052 *   */	OTHER,
    /* 053 +   */	OTHER,
    /* 054 ,   */	OTHER,
    /* 055 -   */	OTHER,
    /* 056 .   */	OTHER,
    /* 057 /   */	OTHER,
    /* 060 0   */	DIGIT,
    /* 061 1   */	DIGIT,
    /* 062 2   */	DIGIT,
    /* 063 3   */	DIGIT,
    /* 064 4   */	DIGIT,
    /* 065 5   */	DIGIT,
    /* 066 6   */	DIGIT,
    /* 067 7   */	DIGIT,
    /* 070 8   */	DIGIT,
    /* 071 9   */	DIGIT,
    /* 072 :   */	OTHER,
    /* 073 ;   */	OTHER,
    /* 074 <   */	OTHER,
    /* 075 =   */	OTHER,
    /* 076 >   */	OTHER,
    /* 077 ?   */	OTHER,
    /* 100 @   */	0,
    /* 101 A   */	LETTER|HEX,
    /* 102 B   */	LETTER|HEX,
    /* 103 C   */	LETTER|HEX,
    /* 104 D   */	LETTER|HEX,
    /* 105 E   */	LETTER|HEX,
    /* 106 F   */	LETTER|HEX,
    /* 107 G   */	LETTER,
    /* 110 H   */	LETTER,
    /* 111 I   */	LETTER,
    /* 112 J   */	LETTER,
    /* 113 K   */	LETTER,
    /* 114 L   */	LETTER,
    /* 115 M   */	LETTER,
    /* 116 N   */	LETTER,
    /* 117 O   */	LETTER,
    /* 120 P   */	LETTER,
    /* 121 Q   */	LETTER,
    /* 122 R   */	LETTER,
    /* 123 S   */	LETTER,
    /* 124 T   */	LETTER,
    /* 125 U   */	LETTER,
    /* 126 V   */	LETTER,
    /* 127 W   */	LETTER,
    /* 130 X   */	LETTER,
    /* 131 Y   */	LETTER,
    /* 132 Z   */	LETTER,
    /* 133 [   */	OTHER,
    /* 134 \   */	OTHER,
    /* 135 ]   */	OTHER,
    /* 136 ^   */	OTHER,
    /* 137 _   */	LETTER,
    /* 140 `   */	0,
    /* 141 a   */	LETTER|HEX,
    /* 142 b   */	LETTER|HEX,
    /* 143 c   */	LETTER|HEX,
    /* 144 d   */	LETTER|HEX,
    /* 145 e   */	LETTER|HEX,
    /* 146 f   */	LETTER|HEX,
    /* 147 g   */	LETTER,
    /* 150 h   */	LETTER,
    /* 151 i   */	LETTER,
    /* 152 j   */	LETTER,
    /* 153 k   */	LETTER,
    /* 154 l   */	LETTER,
    /* 155 m   */	LETTER,
    /* 156 n   */	LETTER,
    /* 157 o   */	LETTER,
    /* 160 p   */	LETTER,
    /* 161 q   */	LETTER,
    /* 162 r   */	LETTER,
    /* 163 s   */	LETTER,
    /* 164 t   */	LETTER,
    /* 165 u   */	LETTER,
    /* 166 v   */	LETTER,
    /* 167 w   */	LETTER,
    /* 170 x   */	LETTER,
    /* 171 y   */	LETTER,
    /* 172 z   */	LETTER,
    /* 173 {   */	OTHER,
    /* 174 |   */	OTHER,
    /* 175 }   */	OTHER,
    /* 176 ~   */	OTHER, 
};

CLex::CLex(void)
: m_cp(NULL)
, m_syms(NULL)
{
}

CLex::~CLex(void)
{
}

//获取下一个单词
void CLex::GetTok(void) 
{
    for (;;) 
    {
        register unsigned char *rcp = m_cp;

        while (chrmap[*rcp]&BLANK)
            rcp++;

        m_cp=rcp+1;

        switch (*rcp++) 
        {
        case '<':
            *rcp == '=' ? m_cp++,  m_code=LEQ_SYM    :  m_code= '<';
            return;
        case '>':
            *rcp == '=' ? m_cp++,  m_code=GEQ_SYM    :  m_code='>';
            return;
        case '=': 
            *rcp == '=' ? m_cp++,  m_code=EQL_SYM    :  m_code='=';
            return;
        case '!': 
            *rcp == '=' ? m_cp++,  m_code=NEQ_SYM    :  m_code='!';
            return;
        case '&':
            if(*rcp == '&')
            {
                m_cp++;
                m_code=ANDAND_SYM;
                return;
            }
            goto error;
        case '|':
            if(*rcp == '|')
            {
                m_cp++;
                m_code=OROR_SYM;
                return;
            }

            goto error;

        case ';': case ',': case '/': case '-': case '+': case '*': 
        case '{': case '}': case '(': case ')': 
            m_code=rcp[-1];
            return;

        case '\n': case '\v': case '\r': case '\f':
            continue;

        case 'i':
            if (rcp[0] == 'f' && !(chrmap[rcp[1]]&(DIGIT|LETTER))) 
            {
                m_cp = rcp + 1;
                m_code=IF_SYM;
                return;
            }
            goto id;
        case 'h': case 'j': case 'k': case 'm': case 'n': case 'o':
        case 'p': case 'q': case 'x': case 'y': case 'z': case '_':
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        case 'G': case 'H': case 'I': case 'J': case 'K': case 'w':
        case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
        case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
        case 'Y': case 'Z': case 's': case 't': case 'u': case 'v':
        case 'f': case 'g': case 'l': case 'L': case 'a': case 'b':
        case 'c': case 'd':
id:
            m_precp=(unsigned char*)rcp - 1;
            while (chrmap[*rcp]&(DIGIT|LETTER))
                rcp++;
            m_token.assign(( char*)m_precp,(unsigned char*)rcp - m_precp);
            m_tsym  = m_syms->Lookup(m_token);
            m_cp = rcp;
            m_code=ID_SYM;
            return;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': 
            m_precp = (unsigned char*)rcp - 1;
            for (; chrmap[*rcp]&DIGIT; rcp++)
                ;

            if(*rcp=='.')
            {
                for (rcp++; chrmap[*rcp]&DIGIT; rcp++)
                    ;
            }

            m_token.assign(( char*)m_precp,(unsigned char*)rcp - m_precp);

            m_tval.m_type=CType::_doubletype;
            m_tval.m_value=atof(m_token.c_str());
            m_tsym=&m_tval;

            m_cp = rcp;

            m_code=FCON_SYM;
            return;

        case 'e':
            if (rcp[0] == 'l'
                &&  rcp[1] == 's'
                &&  rcp[2] == 'e'
                && !(chrmap[rcp[3]]&(DIGIT|LETTER))) 
            {
                m_cp = rcp + 3;
                m_code=ELSE_SYM;
                return;
            }
            goto id;
        case 'r':
            if (rcp[0] == 'e'
                &&  rcp[1] == 't'
                &&  rcp[2] == 'u'
                &&  rcp[3] == 'r'
                &&  rcp[4] == 'n'
                && !(chrmap[rcp[5]]&(DIGIT|LETTER)))
            {
                m_cp = rcp + 5;
                m_code=RETURN_SYM;
                return;
            }
            goto id;
        case '\0':
            m_code=EOI_SYM;
            return;
        default:
error:
            throw CExcept("input invalid symbol");
        }
    }
}

//获取下一个字符
void CLex::GetChar(void) 
{
    for (;;) 
    {
        while ((chrmap[*m_cp]&BLANK)||(chrmap[*m_cp]&NEWLINE))
            m_cp++;

        if (m_cp[0] == '\0')
            m_code=EOI_SYM;
    }
}

//期望函数
void  CLex::ExpectChar(int tok)
{
    if(m_code==tok)
        GetTok();
    else
        throw CExcept("expect valid symbol");
}
