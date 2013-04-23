%option noyywrap nodefault reentrant
%{
struct pwc
{
  int chars;
  int words;
  int lines;
};
%}
%option extra-type="struct  pwc*"
%%

%{
  struct pwc* pp = yyextra;
%}

[a-zA-Z]++ { pp->words++; pp->chars += strlen(yytext); printf("echo %d %d %d\n", pp->chars, pp->words, pp->lines); }
\n         { pp->chars++;  pp->lines++;}
.          { pp->chars++; }
%%


main()
{
  struct pwc mypwc = {0,0,0};
  yyscan_t scanner;
  if(yylex_init_extra(&mypwc, &scanner))
  {
    fprintf(stderr, "init yylex extra fail.\n");
    exit(1);
  }

  yyset_in(stdin, scanner);
  yylex(scanner);
  printf("chars is %d.\t words is %d.\t lines is %d.\n", mypwc.chars, mypwc.words, mypwc.lines);
  yylex_destroy(scanner);
}

