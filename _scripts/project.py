# -*- coding: utf-8 -*-
# !/usr/bin/env python3

import os
import sys
from os import path

from arch import PROJARCH

if len(sys.argv) <= 1:
    print("project name is empty")
    exit(-1)

proj = sys.argv[1]
if not path.exists(proj):
    os.mkdir(proj)


# 遍历目录结构
def traverse_arch(arch, prnt) -> None:
    """
    :type prnt: str
    :type arch: dict
    """
    os.chdir(prnt)
    for i in arch:
        v: dict = arch[i]
        if v["type"] == "file":
            fd = os.open(i, os.O_WRONLY | os.O_CREAT)
            if v.__contains__("content"):
                os.write(fd, bytes(v["content"], encoding="utf-8"))
            os.close(fd)
        elif v["type"] == "dir":
            if not path.exists(i):
                os.mkdir(i)
            traverse_arch(arch[i]["children"], i)
    os.chdir("..")


traverse_arch(PROJARCH, proj)
