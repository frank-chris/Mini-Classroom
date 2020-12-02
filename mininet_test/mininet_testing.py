

from mininet.net import Mininet
from mininet.cli import CLI
from mininet.util import pmonitor
from mininet.link import TCLink
import time

# bandwidth 
BW = 1000

popens = {}

# topology
net = Mininet(link=TCLink)

# client hosts
h = {}
for i in range(1,17):
    h[i] = net.addHost('h'+str(i))

# server host
h17 = net.addHost('h17')

s = {}
# switches
for i in range(1,5):
    s[i] = net.addHost('s'+str(i))

# controller
c0 = net.addController('c0')

# links
for i in range(1,5):
    net.addLink(h17, s[i], bw=BW)
    for j in range(1,5):
        net.addLink(h[(4*(i-1))+j], s[i], bw=BW/4)

net.start()

# run scripts on hosts

popens[h17] = h17.popen("./server_src/server")

for i in range(1,17):
    popens[h[i]] = h[i].popen("./client_src/client " + str(h17.IP()) + " 8080 workload" + str(i-1) + ".txt")


time.sleep(13)

# monitoring outputs of scripts
for hst, line in pmonitor(popens, timeoutms=500):
    if hst:
        print(str(hst.name) +": " + str(line), end = '')
    else:
        break

# stopping
net.stop()