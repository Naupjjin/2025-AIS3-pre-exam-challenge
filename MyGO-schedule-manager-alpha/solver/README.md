# MyGO schedule manager α
> Author: 堇姬Naup

## analyze

We know std::string struct like this.
| offset | description |
|--------|-------------|
| 0x0    | data's pointer |
| 0x8    | vector size |
| 0x10   | vector capacity |
| 0x18   | unused padding or alignment space |

So if we can change data's pointer to anywhere, we will get arbitary write or read.
Use it to write got.
I overwrite 