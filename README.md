# MASA-OpenMP

<p align="justify">
The <b>MASA-OpenMP extension</b> is used with the <a href="https://github.com/edanssandes/MASA-Core">MASA architecture</a> to align DNA sequences of unrestricted size with the Smith-Waterman/Needleman-Wunsch algorithms combined with Myers-Miller. It uses the OpenMP framework to accelerate the computation time in CPU.
</p>

### Download

Latest Version: [masa-openmp-1.0.1.1024.tar.gz](releases/masa-openmp-1.0.1.1024.tar.gz?raw=true)

### Compiling (masa-openmp)

```
tar -xvzf masa-openmp-1.0.1.1024.tar.gz
cd masa-openmp-1.0.1.1024
./configure
make
```

### Executing

```
./masa-openmp [options] seq1.fasta seq2.fasta
```
All the command line arguments can be retrieved using the --help parameter. See the [wiki](https://github.com/edanssandes/MASA-Core/wiki/Command-line-examples) for a list of command line examples.

### License

MASA-OpenMP is an open source project with public license (GPLv3). A copy of the LICENSE is maintained in this repository.
