
@echo WYNIK > result.txt

@for /L %%i in (1,1,1) do @(
@echo TEST %%i
@echo TEST %%i >>result.txt
@"Debug\silnikcss.exe" <../mapa/%%i.in >output.txt
@fc /lb1 /n /w tests\%%i.out output.txt >> result.txt
)