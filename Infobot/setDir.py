import sonic
import time

def setDir():

    time.sleep(0.02)
    
    sncVar = printsonic()
    
    SS1 = int(sncVar/100)
    SS2 = int(sncVar/10)
    SS3 = int(sncVar%10)
    
    print("SS1 = "+SS1 +"SS2 = "+SS2 +"SS3 = " +SS3)
    
    res = 0
    
    if sncVar == 0 :
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