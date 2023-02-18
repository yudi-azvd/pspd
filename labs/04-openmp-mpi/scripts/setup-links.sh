scripts=$(ls -1 scripts/)

for script in $scripts; do
    echo "script $script"
    ln -sf scripts/$script $script
done

