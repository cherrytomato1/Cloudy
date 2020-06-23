import obj_detection as dtct
#import cloudy as cldy
while True :
    pos, size = dtct.obj_dtct()

    print(pos,size)
dtct.stop_dtct()

