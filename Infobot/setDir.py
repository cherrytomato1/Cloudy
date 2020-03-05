import sonic
import time

def setDir():

    time.sleep(0.02)
    
    
    
    SS1 = printsonic(1)
    SS2 = printsonic(2)
    SS3 = printsonic(3)
    
    print("SS1 = "+SS1 +"SS2 = "+SS2 +"SS3 = " +SS3)
    
    res = 0
    
    if SS1+SS2+SS3 == 0 :
        res = 1
    
    else if SS2 <=5 and SS2!=0 :
        if SS3 <=5 and SS2!=0 :
            res = 3
        else :
            res = 4
    else if SS1 <=5 and SS1!=0 :
        res = 4
    else if SS3 <=5 and SS3!=0 :
        res = 3
    
    return res
    
def setDirTest():

    time.sleep(0.1)
    
    
    
    SS1 = printsonic(1)
    
    
    res = 0
    
    if SS1 == 0 :
        res = 1
    
    else
        res = 3
    
    return res