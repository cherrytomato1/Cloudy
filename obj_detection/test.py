import obj_detection as dtct
#import cloudy as cldy
while True :
    pos, size = dtct.obj_dtct()
    
    if(size>100) :
        size = '9'
    else :
        size = str(int(size/10))
        
    
    print('1',size,pos)
dtct.stop_dtct()

