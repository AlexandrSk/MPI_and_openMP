# MPI and openMP
MPI and OpenMP Example (computing an exponent using a Taylor series)

В ході лабораторної роботи була обчислена експонента за допомогою ряду Тейлора. Для відчутного покращення у швидкості, взято n = 100000. При низьких значеннях n паралельні обчислення можуть давати гірший результат ніж послідовне.

Число процесів
	
MPI
Число процесів | Час рішення
4	- 6.37
3 - 7.14
2 -	9.43
1 -	17

OpenMP
Число процесів | Час рішення
4 -	3.37
3	- 4.32
2 -	6.66
1 -	8.93

