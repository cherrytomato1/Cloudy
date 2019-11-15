import RPi.GPIO as IO
import time

M1_N=17
M1_P=27
M2_N=5
M2_P=7

IO.setwarning(False)
IO.setmode(IO.BCM)
IO.setup(M1_N, IO.OUT)
IO.setup(M1_p, IO.OUT)
IO.setup(M2_N, IO.OUT)
IO.setup(M2_p, IO.OUT)

