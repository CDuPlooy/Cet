# Cet ( Retarded spelling of cat ):

Cet is a program for concatenating two files.

The name comes from using the code below to concatenate two
files.
````shell
cat file1 >> file2
````

# Results:
````shell
cp 50MB.zip file1:
real	0m0.374s
user	0m0.000s
sys	0m0.372s

cat file1 >> file2:
real	0m0.373s
user	0m0.000s
sys	0m0.368s

cet file1 file2:
real	0m0.418s
user	0m0.000s
sys	0m0.416s
````

## Todo:
* Add system profiling.
* Figure out what's the largest chunk of memory read can read without being ineffective.
