%{
/* Lab2 Attention: You are only allowed to add code in this file and start at Line 26.*/
#include <string.h>
#include "util.h"
#include "tokens.h"
#include "errormsg.h"

int charPos=1;

int yywrap(void)
{
 charPos=1;
 return 1;
}

void adjust(void)
{
 EM_tokPos=charPos;
 charPos+=yyleng;
}

/*
* Please don't modify the lines above.
* You can add C declarations of your own below.
*/

/* @function: getstr
 * @input: a string literal
 * @output: the string value for the input which has all the escape sequences 
 * translated into their meaning.
 */
char *tstr = NULL;
int str_block = 256;
int str_max = 256;
int str_len = 0;
int str_off = 1;//adjust of EM_tokPos
char *getstr(const char *str)
{
	//optional: implement this function if you need it
  tstr[str_len] = '\0';
  if (str_len==0){
    yylval.sval = NULL;
  }else{
    yylval.sval = String(tstr);
  }
	return NULL;
}

void str_begin(void){
  tstr = checked_malloc(str_block);
  str_max = str_block;
  str_len = 0;
  str_off = 1;
}

void add_char(char c){
  if (str_len==str_max-3){
    tstr = realloc(tstr,str_max+str_block);
    str_max += str_block;
    if (!tstr){
      printf("error in malloc\n");
      exit(1);
    }
  }
  tstr[str_len]=c;
  str_len++;
}

void str_end(void){
  free(tstr);
  tstr = NULL;
}

%}
  /* You can add lex definitions here. */
%x COMMENT STR VSTR

%%
  /* 
  * Below is an example, which you can wipe out
  * and write reguler expressions and actions of your own.
  */ 
  int comment_count = 0;
  bool flag;

<COMMENT>{
  "/*" {adjust();comment_count++;}
  "*/" {adjust();comment_count--;if (comment_count==0)BEGIN(INITIAL);}
  \n {adjust();EM_newline();continue;}
  . {adjust();}
  <<EOF>> {adjust();EM_error(EM_tokPos,"EOF during COMM");return 0;}
}

<STR>{
  \" {adjust();getstr(NULL);str_end();BEGIN(INITIAL);EM_tokPos-=str_len+str_off;if(flag)return STRING;}
  \\\n[ \t]*\\ {adjust();str_off+=yyleng;}
  \\\^[A-Z] {adjust();add_char(yytext[2]-'A'+1);str_off+=2;}
  \\f {adjust();BEGIN(VSTR);}
  \\n {adjust();add_char('\n');str_off++;}
  \\t {adjust();add_char('\t');str_off++;}
  \\^[a-zA-Z] {adjust();str_off++;}
  \\[0-9]{3} {adjust();add_char(atoi(yytext+1));str_off+=3;}
  \\\" {adjust();add_char('\"');str_off++;}
  \\\\ {adjust();add_char('\\');str_off++;}
  \\[^ntfl\"\\\n] {adjust(); flag=FALSE; EM_error(EM_tokPos,"unknown escape sequence: '\\%c'",yytext[1]);str_off++;}
  \n {adjust();EM_newline();add_char('\n');str_off++;}
  \r
  . {adjust();add_char(yytext[0]);}
  <<EOF>> {adjust(); EM_error(EM_tokPos,"EOF during STR");str_end();return 0;}
}

<VSTR>{
  f\\ {adjust();BEGIN(STR);}
  \n {adjust();EM_newline();str_off++;}
  \r
  . {adjust();}
  <<EOF>> {adjust();EM_error(EM_tokPos,"EOF during VSTR");str_end();return 0;}
}


"/*" {adjust();comment_count++;BEGIN(COMMENT);}
\" {adjust();str_begin();flag=TRUE;BEGIN(STR);}
[ \t]* {adjust();continue;}
"\n" {adjust(); EM_newline(); continue;}
"\r"
","  {adjust(); return COMMA;}
":"  {adjust(); return COLON;}
";"  {adjust(); return SEMICOLON;}
"("  {adjust(); return LPAREN;}
")"  {adjust(); return RPAREN;}
"["  {adjust(); return LBRACK;}
"]"  {adjust(); return RBRACK;}
"{"  {adjust(); return LBRACE;}
"}"  {adjust(); return RBRACE;}
"."  {adjust(); return DOT;}
"+"  {adjust(); return PLUS;}
"-"  {adjust(); return MINUS;}
"*"  {adjust(); return TIMES;}
"/"  {adjust(); return DIVIDE;}
"="  {adjust(); return EQ;}
"<>" {adjust(); return NEQ;}
"<"  {adjust(); return LT;}
"<=" {adjust(); return LE;}
">"  {adjust(); return GT;}
">=" {adjust(); return GE;}
"&"  {adjust(); return AND;}
"|"  {adjust(); return OR;}
":=" {adjust(); return ASSIGN;}
array   {adjust(); return ARRAY;}
if      {adjust(); return IF;}
then    {adjust(); return THEN;}
else    {adjust(); return ELSE;}
while   {adjust(); return WHILE;}
for     {adjust(); return FOR;}
to      {adjust(); return TO;}
do      {adjust(); return DO;}
let     {adjust(); return LET;}
in      {adjust(); return IN;}
end     {adjust(); return END;}
of      {adjust(); return OF;}
break   {adjust(); return BREAK;}
nil     {adjust(); return NIL;}
function {adjust(); return FUNCTION;}
var     {adjust(); return VAR;}
type    {adjust(); return TYPE;}
[a-zA-Z]+[a-zA-Z0-9_]*  {adjust(); yylval.sval = String(yytext); return ID;}
[0-9]+   {adjust(); yylval.ival=atoi(yytext); return INT;}
.    {adjust(); EM_error(EM_tokPos,"illegal token");}
