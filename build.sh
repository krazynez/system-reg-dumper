#!/usr/bin/env bash

make clean && make
rm -rf PSP SYSTEM_REG_DUMPER.zip
mkdir -p PSP/GAME/SYSTEM_REG_DUMPER
mv EBOOT.PBP PSP/GAME/SYSTEM_REG_DUMPER/

zip -r SYSTEM_REG_DUMPER.zip PSP README*

pandoc README.md -t plain -o README.txt

echo Done

