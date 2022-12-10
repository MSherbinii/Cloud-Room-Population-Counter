import urllib.request
import requests
import threading
import json
import random

def thingspeak_post():
    threading.Timer(15,thingspeak_post).start()
    val=random.randint(1,30)
    URl='https://api.thingspeak.com/update?api_key='
    KEY=' DRPDM0NNF9SW69QK'
    HEADER='&field1={}&field2={}'.format(val,val)
    NEW_URL = URl+KEY+HEADER
    print(NEW_URL)
    data=urllib.request.urlopen(NEW_URL)
    print(data)
    w_key = 'F21KBECTNOL98KIK
    r_key = 'LK8PJOFYYL6AC669'
    channel_id = 1628198                  # replace with channel id

    ob = Thingspeak(write_api_key=w_key, read_api_key=r_key, channel_id=channel_id)
    print(ob.read_cloud(result=3))
    
if _name_ == '_main_':

    thingspeak_post()