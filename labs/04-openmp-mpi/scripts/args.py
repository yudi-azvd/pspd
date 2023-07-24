#!/usr/bin/env python3

import sys
from argparse import ArgumentParser

mpi_args_parser = ArgumentParser(
    description='Programa que executa experimentos MPI'
)
mpi_args_parser.add_argument(
    '-p',
    '--procs',
    required=True,
    type=int,
    help='number of processes'
)
mpi_args_parser.add_argument(
    '-l',
    '--lines',
    metavar='lines',
    required=True,
    type=int,
    help='number of lines for bmp file'
)
mpi_args_parser.add_argument(
    '-t',
    '--trials',
    help='number of trials for experiment',
    type=int,
    default=10,
)
mpi_args_parser.add_argument(
    '-m',
    '--program',
    metavar='program',
    required=True,
    help='name of the mpi program to be executed',
    type=str,
)
mpi_args_parser.add_argument(
    '--local',
    action='store_true',
    # default=False,
    help='if true, no hosts are passed to mpirun. otherwise "-hosts cm1,...,cm4 "'
    " will be passed",
)

if __name__ == '__main__':
    args = mpi_args_parser.parse_args(sys.argv[1:])

    print(args)
    print(args.local)
    print(args.program)
