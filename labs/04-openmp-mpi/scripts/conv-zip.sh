filename="README.md"
pdf_output="PSPD-Experimentos-OpenMP-MPI-Yudi-Yamane.pdf"

pandoc --no-tex-ligatures \
  -H ../disable_float.tex \
  --template ../template.tex \
  $filename \
  -o $pdf_output \
  --highlight-style=kate

rm -rf pspd-experimentos-openmp-mpi-yudi-yamane.zip
zip -q pspd-experimentos-openmp-mpi-yudi-yamane.zip -r ./ \
  -x *.png *.sh *.out *.bmp runtimes tmp report.txt\
  fractalmpi_io\
  fractalmpi_io-slow\
  fractalmpiserial\
  fractalmpiserial-slow\
  fractalomp\
  f\
  diff
