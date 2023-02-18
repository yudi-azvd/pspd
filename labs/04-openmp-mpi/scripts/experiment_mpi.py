#!/usr/bin/env python3

import re
import sys
from subprocess import check_output
from common import capture_time_records, stats
from args import mpi_args_parser


def format_hosts(nprocs: int, local=False):
    '''Sim, dá pra melhorar esse if/else, mas preguiça. 
    É o suficiente por agora.'''

    allowed_number_of_process = [1, 2, 4, 8, 12]
    assert nprocs in allowed_number_of_process

    if local:
        return ''

    if nprocs == 2:
        return ['-host', 'cm1,cm2']
    elif nprocs == 4:
        return ['-host', 'cm1:1,cm2:1,cm3:1,cm4:1']
    elif nprocs == 8:
        return ['-host', 'cm1:2,cm2:2,cm3:2,cm4:2']
    elif nprocs == 12:
        return ['-host', 'cm1:3,cm2:3,cm3:3,cm4:3']
    return ''


def build_subprocess_args(procs, hosts: str, program, lines):
    args = ['mpirun', '-n', f'{procs}']

    if type(hosts) == list:
        args.extend(hosts)

    args.extend([f'./{program}', f'{lines}'])
    return args


def run_trials(trials: int, subprocess_args: 'list[str]'):
    output = bytes()
    print(f'Running {trials} times: {" ".join(subprocess_args)}\n')
    for i in range(trials):
        print(f'iteration {i}/{trials} ... ', end='')
        output += check_output(subprocess_args, shell=False)
        print('done')
    return output


def main(argv: 'list[str]'):
    a = mpi_args_parser.parse_args(argv[1:])

    hosts = format_hosts(a.procs, a.local)
    subp_args = build_subprocess_args(a.procs, hosts, a.program, a.lines)
    output = run_trials(a.trials, subp_args).decode()
    records = capture_time_records(output)

    [avg, std_err] = stats(records)
    print()
    print(f'avg     {avg}')
    print(f'std_err {std_err}')


if __name__ == '__main__':
    main(sys.argv)
