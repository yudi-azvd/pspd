input=$1
ext="${input##*.}"

if [ "$ext" != "md" ]; then
  echo "input should have the .md extension"
  exit 1
fi

filename="${input%.*}"
filename_with_ext="$(basename -- $input)"
filename="${filename_with_ext%.*}"
pdf_output="$filename.pdf"

# echo "input: $input"
# echo "filename: $filename"
# echo "pdf_output: $pdf_output"
# echo "filename_with_ext: $filename_with_ext"

pandoc --no-tex-ligatures \
  -H ./disable_float.tex \
  --template ./template.tex \
  $filename_with_ext \
  -o $pdf_output \
  --highlight-style=kate

rm -rf pspd-lab01-rpc-grpc-yudi-yamane.zip
zip -q pspd-lab01-rpc-grpc-yudi-yamane.zip * -x *.png -x *.tex -x *.md *.sh -x ./simple/\* -x ./lib/\* -x ./\*-rpc\* 
