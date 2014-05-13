LEX    = flex
BISON  = bison
BFLAGS = --defines=elene_parser.tab.hh --output=elene_parser.tab.cc

elene:	lex.yy.c elene_parser.tab.cc arbol2.hh elene.cc elene_driver.cc
		g++ $^ -o $@

elene_parser.tab.cc:	elene_parser.yy
		bison -d $<

lex.yy.c:	elene_lexer.ll
		flex $<

clean:
		rm elene elene_parser.tab.* lex.yy.c location.hh position.hh stack.hh

