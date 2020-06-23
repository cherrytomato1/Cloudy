import os

f = os.popen('ls /dev/tty*').read().strip().split()[1]

print(f)