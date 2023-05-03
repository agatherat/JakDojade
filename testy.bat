
@echo WYNIK > result.txt

@for /L %%i in (1,1,13) do @(
@echo TEST %%i
@echo TEST %%i >>result.txt
@"Debug\JakDojade.exe" <../mapa/%%i.in >output.txt
@fc /lb1 /n /w ..\mapa\%%i.out output.txt >> result.txt
)
pause