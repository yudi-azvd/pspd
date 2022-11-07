struct operands {
    int x;
    int y;
};

program calculate {
    version VER {
        int add(operands) = 1;
        int sub(operands) = 2;
    } = 100;
} = 55555555;