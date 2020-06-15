import obj_detection as dtct
#import cloudy as cldy
while True :
    x, size = dtct.obj_dtct()

    print(x,size)
dtct.stop_dtct()

