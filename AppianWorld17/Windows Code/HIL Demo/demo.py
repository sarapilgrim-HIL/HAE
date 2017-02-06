'''
Created on Feb 5, 2017

@author: Brett
'''

'''
TODO
- fix bug - sometimes data comes in as 5 then 0 instead of 50, so it inserts those 2 rows.
- implement newGame insert as its own method?
'''


import MySQLdb
import serial
import time
import datetime

db = MySQLdb.connect(host="localhost",    # your host, usually localhost
                     user="root",         # your username
                     passwd="Password1!",  # your password
                     db="aw_test")        # name of the data base

cur = db.cursor()

timestamp = datetime.datetime.fromtimestamp(time.time()).strftime('%Y-%m-%d %H:%M:%S')
print(timestamp)
cur.execute("INSERT INTO GAME (START_TIME) values (%s)", (timestamp, ))
db.commit()
newGameNumber = cur.execute("SELECT MAX(ID) FROM GAME GROUP BY ID") + 0

ser = serial.Serial('COM3', 9600, timeout=0)
sleepTime = .1

print(newGameNumber)
 
while True:
    try:
        data = ser.readline().decode("utf-8")     
        if data == '': continue                   

        print(data)
        time.sleep(sleepTime)

        if data == 'NewGame':
            pass
        else: 
            cur.execute('INSERT INTO SHOT (GAME_ID, POINTS) values (%s, %s)', (newGameNumber, data))
            db.commit()

    except:
        time.sleep(sleepTime)