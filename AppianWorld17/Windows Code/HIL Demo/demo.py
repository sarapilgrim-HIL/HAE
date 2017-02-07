'''
Created on Feb 5, 2017

@author: Brett Rojas
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

global newGameNumber
ser = serial.Serial('COM3', 9600, timeout=.1)
sleepTime = .1

def newGame():
    timestamp = datetime.datetime.fromtimestamp(time.time()).strftime('%Y-%m-%d %H:%M:%S')
    cur.execute("INSERT INTO GAME (START_TIME) values (%s)", (timestamp, ))
    db.commit()
    newGameNumber = cur.execute("SELECT MAX(ID) FROM GAME GROUP BY ID") + 0
    print('New Game: ' + str(newGameNumber) + '\n')
    return newGameNumber

newGameNumber = newGame()

while True:
    try:
        data = ser.readline().decode("utf-8")     
        if data == '': continue
        time.sleep(sleepTime)

        if data.strip() == 'NewGame':
            newGameNumber = newGame()
        else: 
            print('Target Hit! ' + str(data.strip()) + ' points!' + '\n')
            cur.execute('INSERT INTO SHOT (GAME_ID, POINTS) values (%s, %s)', (newGameNumber, data))
            db.commit()

    except:
        time.sleep(sleepTime)