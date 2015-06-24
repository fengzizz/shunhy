@echo on
set PATH=%PATH% ;..\..\..\..\tools\yacc-parser\flex-bison\bin
..\..\..\..\tools\yacc-parser\flex-bison\bin\flex -L -l -oShhShader_lex.cpp ShhShader_lex.lcc
..\..\..\..\tools\yacc-parser\flex-bison\bin\bison --yacc -l -d -k -oShhShader_yacc.cpp ShhShader_yacc.ycc

pause