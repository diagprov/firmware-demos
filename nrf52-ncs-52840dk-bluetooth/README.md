
# This sample doesn't yet work.

## West notes.

West is an attempt to make a package manager and version control system 
while failing at both.

West expects you to clone from a manifest repository possibly also 
containing sources. When you run `west init` it sets up a local `.west` 
directory and then clones various git repos into subdirectories.

However, it very much wants a git remote to exist, and if you try to 
initialize based on a _local_ `west.yml` it will insist, no matter what 
the manifest says, that this is a subdirectory of the overall working tree.

Hence in this example, `firmware/west.yml` exists and you must:

 1. `cd` into `firmware`.
 1. `west init --local`.
 1. `cd ..`
 1. `west build -b nrf52840dk_nrf52840`

Yes, this is stupid and unnecessary. However, nobody has time to learn how to 
make the nordic SDK work by hand.

Zephyr also insists on polluting your user's cmake directories, so please under 
no circumstances run `zephyr-export` commands of any kind, or cmake will 
start finding the wrong version of Zephyr all the time. Instead, run 

```
source env.sh
```

set to your properties. If you want to do zephyr by hand set `ZEPHYR_BASE`.
