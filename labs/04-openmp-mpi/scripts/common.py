#!/usr/bin/env python3

import re


def capture_time_records(output: str):
    records = []
    times_as_str = re.findall(
        '^(.*)Time elapsed\s+(.*)$', output, re.MULTILINE)
    records = [float(t[1]) for t in times_as_str]
    return records


def avg_of(nums: 'list[float]'):
    length = len(nums)
    total = sum(nums)
    return total/length


def stats(nums: 'list[float]'):
    length = len(nums)
    avg = avg_of(nums)
    deviations_sqr = [(n-avg)**2 for n in nums]
    variance = avg_of(deviations_sqr)
    std_deviation = variance**.5
    std_error = std_deviation/length**.5
    return [avg, std_error]
