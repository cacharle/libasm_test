import os
import sys
import re
import argparse


def green(*strings):
    return "".join([f"\033[32m{s}\033[0m" for s in strings])


def red(*strings):
    return "".join([f"\033[31m{s}\033[0m" for s in strings])


def parse_args():
    parser = argparse.ArgumentParser( prog="ft_printf test", description="A ~quicker tester for ft_printf")
    parser.add_argument("-v", "--verbose",
                        help="increase verbosity", action="store_true")
    parser.add_argument("-q", "--quiet",
                        help="decrease vebosity", action="store_true")
    parser.add_argument("-l", "--no-log",
                        help="disable result log", action="store_true")
    parser.add_argument("-c", "--no-clear", help="disable terminal clear before output")
    parser.add_argument("-i", "--interactive", help="print fail as them come",
                        action="store_true")
    parser.add_argument("-f", "--output-file", help="output file name")
    return vars(parser.parse_args(sys.argv[1:]))


def print_log_ko(ko, options):
    print(f"- [{red(ko['type'])}] ft_printf({ko['args']})")
    if options["verbose"]:
        print("   expected: ", ko["expected"])
        print("   actual:   ", ko["actual"])
        print()

def create_logs_entry(logs, key):
    logs[key] = {}
    logs[key]["ok_counter"] = 0
    logs[key]["ko_counter"] = 0
    logs[key]["ko_info"] = []

def parse():
    logs = {}
    for line in sys.stdin:
        line = line.strip()
        if line[:2] == "OK":
            l = logs.get(line[4:])
            if l is None:
                print("\n\n", line[4:], ": ", sep="", end="")
                create_logs_entry(logs, line[4:])
            logs[line[4:]]["ok_counter"] += 1
            if (logs[line[4:]]["ok_counter"] + logs[line[4:]]["ko_counter"]) % 10 == 0:
                print("\n", ''.join([" " for _ in range(1 + len(line[4:]))]), end="")
            print(green("[OK] "), end="")
            continue
        m = re.search("^KO: \[(SEGFAULT|COMPARE)\]: (.*): expected: (.*) got: (.*)$", line)
        if m is None:
            print(line)
            print("PARSING ERROR")
            continue
        l = logs.get(m.group(2))
        if l is None:
            print("\n")
            create_logs_entry(logs, m.group(2))
        l["ko_counter"] += 1
        l["ko_info"].append({
            "type": m.group(1),
            "expected": m.group(3),
            "actual": m.group(4),
        })
        if (l["ok_counter"] + l["ko_counter"]) % 10 == 0:
            print("\n", ''.join([" " for _ in range(1 + len(m.group(2)))]), end="")
        print(red("[KO] "), end="")
    return logs

if __name__ == "__main__":
    os.system("clear")
    logs = parse()
    print("\n")
    for k, v in logs.items():
        for e in v["ko_info"]:
            if e['type'] == "SEGFAULT":
                print(f"{k} : {red(SEGFAULT)}")
            elif e['type'] == "COMPARE":
                print(f"{k}:\n    {green('expected: ', e['expected'])}\n    {red('actual: ', e['actual'])}")
