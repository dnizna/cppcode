%option noyywrap nodefault reentrant
%{
struct pwc
{
  int chars;
  int words;
  int lines;
};
%}
// 用户数据类型
%option extra-type="struct  pwc*"
%%

// 传入用户数据实例，yyextra是一个宏
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
  // 初始化用户数据和scanner
  if(yylex_init_extra(&mypwc, &scanner))
  {
    fprintf(stderr, "init yylex extra fail.\n");
    exit(1);
  }

  yyset_in(stdin, scanner);
  yylex(scanner);
  yylex_destroy(scanner);
}

