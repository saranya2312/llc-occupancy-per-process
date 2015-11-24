import curses, time
import operator 
from datetime import datetime
#w = curses.initscr()

import os
pids = [pid for pid in os.listdir('/proc') if pid.isdigit()]
pairs = []

def proct(pid):
    try:
        with open(os.path.join('/proc/', pid, 'stat'), 'r') as pidfile:
            proctimes = pidfile.readline()
            # get llc from /proc/<pid>/stat, 14 item
            llc = proctimes.split(' ')[-1]
            return(llc)
    except IOError as e:
         return 0

try:
  diff = 0
  prev = 0
  while True:
#    w.erase()
    pairs = []
    status = "" 
    print datetime.now().strftime("%H:%M:%S")
    print "PID    LLC"
    for pid in pids:
       llc =  proct(pid)
       pairs.append((int(pid),int(llc)))
#    w.addstr("LLC Occupancy status..\ncurrent time\n%s" % datetime.utcnow())
    pair =sorted(pairs,key=operator.itemgetter(1),reverse=True)
#    print "PID    LLC    DIFF"
    count =40
  
    for p in pair:
      count = count - 1
      if(count > 0):
#        diff = b - prev
#      w.addstr(" \n%s" % a)
         print "       ".join(str(e) for e in p)
#    w.refresh()
    time.sleep(1)
    os.system('clear') 
finally:
   print "not needed"
#   curses.endwin()
